/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <cerrno>
#include <fstream>
#include <iostream>
#include <vector>
#ifdef WITH_SELINUX
#include <policycoreutils.h>
#endif // WITH_SELINUX
#include "account_error_no.h"
#include "account_info.h"
#include "account_log_wrapper.h"
#include "directory_ex.h"
#include "file_ex.h"
#include "hisysevent_adapter.h"
#include "ohos_account_data_deal.h"
namespace OHOS {
namespace AccountSA {
namespace {
const std::string ACCOUNT_CFG_FILE_NAME = "/account.json";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_NAME = "account_name";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_UID = "open_id";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_STATUS = "bind_status";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_NICKNAME = "account_nickname";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_AVATAR = "account_avatar";
const std::string DATADEAL_JSON_KEY_OHOSACCOUNT_SCALABLEDATA = "account_scalableData";
const std::string DATADEAL_JSON_KEY_USERID = "user_id";
const std::string DATADEAL_JSON_KEY_BIND_TIME = "bind_time";
} // namespace

OhosAccountDataDeal::OhosAccountDataDeal(const std::string &configFileDir) : configFileDir_(configFileDir)
{
    initOk_ = false;
}

ErrCode OhosAccountDataDeal::Init(std::int32_t userId)
{
    std::string configFile = configFileDir_ + std::to_string(userId) + ACCOUNT_CFG_FILE_NAME;
    if (!FileExists(configFile)) {
        ACCOUNT_LOGI("file %{public}s not exist, create!", configFile.c_str());
        BuildJsonFileFromScratch(userId);
#ifdef WITH_SELINUX
        Restorecon(configFile.c_str());
#endif // WITH_SELINUX
    }

    std::ifstream fin(configFile);
    if (!fin) {
        ACCOUNT_LOGE("Failed to open config file %{public}s, errno %{public}d.", configFile.c_str(), errno);
        ReportOhosAccountOperationFail(userId, OPERATION_INIT_OPEN_FILE_TO_READ, errno, configFile);
        return ERR_ACCOUNT_DATADEAL_INPUT_FILE_ERROR;
    }

    // NOT-allow exceptions when parse json file
    std::lock_guard<std::mutex> lock(mutex_);
    jsonData_ = json::parse(fin, nullptr, false);
    fin.close();
    if (!jsonData_.is_structured()) {
        ACCOUNT_LOGE("Invalid json file, remove");
        if (RemoveFile(configFile)) {
            ACCOUNT_LOGE("Remove invalid json file %{public}s failed, errno %{public}d.", configFile.c_str(), errno);
            ReportOhosAccountOperationFail(userId, OPERATION_REMOVE_FILE, errno, configFile);
        }
        return ERR_ACCOUNT_DATADEAL_JSON_FILE_CORRUPTION;
    }

    initOk_ = true;
    return ERR_OK;
}

ErrCode OhosAccountDataDeal::AccountInfoFromJson(AccountInfo &accountInfo, const std::int32_t userId)
{
    if (!initOk_) {
        ACCOUNT_LOGE("not init yet!");
        return ERR_ACCOUNT_DATADEAL_NOT_READY;
    }
    return GetAccountInfo(accountInfo, userId);
}

ErrCode OhosAccountDataDeal::AccountInfoToJson(const AccountInfo &accountInfo) const
{
    if (!initOk_) {
        ACCOUNT_LOGE("Not init ok");
        return ERR_ACCOUNT_DATADEAL_NOT_READY;
    }
    return SaveAccountInfo(accountInfo);
}

int32_t OhosAccountDataDeal::SaveAccountInfo(const AccountInfo &accountInfo) const
{
    std::string scalableDataStr = (accountInfo.ohosAccountInfo_.scalableData_).ToString();
    nlohmann::json jsonData = json {
        {DATADEAL_JSON_KEY_BIND_TIME, accountInfo.bindTime_},
        {DATADEAL_JSON_KEY_USERID, accountInfo.userId_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_NAME, accountInfo.ohosAccountInfo_.name_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_UID, accountInfo.ohosAccountInfo_.uid_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_STATUS, accountInfo.ohosAccountInfo_.status_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_NICKNAME, accountInfo.ohosAccountInfo_.nickname_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_AVATAR, accountInfo.ohosAccountInfo_.avatar_},
        {DATADEAL_JSON_KEY_OHOSACCOUNT_SCALABLEDATA, scalableDataStr}
    };
    std::string configFile = configFileDir_ + std::to_string(accountInfo.userId_) + ACCOUNT_CFG_FILE_NAME;
    std::ofstream out(configFile);
    if (!out) {
        ACCOUNT_LOGE("Failed to open file %{public}s, errno %{public}d.", configFile.c_str(), errno);
        ReportOhosAccountOperationFail(accountInfo.userId_, OPERATION_OPEN_FILE_TO_WRITE, errno, configFile);
        return ERR_ACCOUNT_DATADEAL_FILE_PARSE_FAILED;
    }
    out << jsonData;
    out.close();

    // change mode
    if (!ChangeModeFile(configFile, S_IRUSR | S_IWUSR)) {
        ACCOUNT_LOGW("failed to change mode for file %{public}s, errno %{public}d.", configFile.c_str(), errno);
        ReportOhosAccountOperationFail(accountInfo.userId_, OPERATION_CHANGE_MODE_FILE, errno, configFile);
        return ERR_OHOSACCOUNT_SERVICE_FILE_CHANGE_DIR_MODE_ERROR;
    }
    return ERR_OK;
}

int32_t OhosAccountDataDeal::GetAccountInfo(AccountInfo &accountInfo, const std::int32_t userId)
{
    std::string configFile = configFileDir_ + std::to_string(userId) + ACCOUNT_CFG_FILE_NAME;
    if (!FileExists(configFile)) {
        ACCOUNT_LOGI("file %{public}s not exist, create!", configFile.c_str());
        BuildJsonFileFromScratch(userId); // create default config file for first login
#ifdef WITH_SELINUX
        Restorecon(configFile.c_str());
#endif // WITH_SELINUX
    }
    std::ifstream fin(configFile);
    if (!fin) {
        ACCOUNT_LOGE("Failed to open config file %{public}s, errno %{public}d.", configFile.c_str(), errno);
        ReportOhosAccountOperationFail(userId, OPERATION_OPEN_FILE_TO_READ, errno, configFile);
        return ERR_ACCOUNT_DATADEAL_INPUT_FILE_ERROR;
    }

    // NOT-allow exceptions when parse json file
    std::lock_guard<std::mutex> lock(mutex_);
    jsonData_ = json::parse(fin, nullptr, false);
    fin.close();
    if (!jsonData_.is_structured()) {
        ACCOUNT_LOGE("Invalid json file,  %{public}s, remove", configFile.c_str());
        return ERR_ACCOUNT_DATADEAL_JSON_FILE_CORRUPTION;
    }

    const auto &jsonObjectEnd = jsonData_.end();
    if (jsonData_.find(DATADEAL_JSON_KEY_BIND_TIME) != jsonObjectEnd) {
        accountInfo.bindTime_ = jsonData_.at(DATADEAL_JSON_KEY_BIND_TIME).get<std::time_t>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_NAME) != jsonObjectEnd) {
        accountInfo.ohosAccountInfo_.name_ = jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_NAME).get<std::string>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_UID) != jsonObjectEnd) {
        accountInfo.ohosAccountInfo_.uid_ = jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_UID).get<std::string>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_STATUS) != jsonObjectEnd) {
        accountInfo.ohosAccountInfo_.status_ = jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_STATUS).get<std::int32_t>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_NICKNAME) != jsonObjectEnd) {
        accountInfo.ohosAccountInfo_.nickname_ =
            jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_NICKNAME).get<std::string>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_AVATAR) != jsonObjectEnd) {
        accountInfo.ohosAccountInfo_.avatar_ = jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_AVATAR).get<std::string>();
    }

    if (jsonData_.find(DATADEAL_JSON_KEY_OHOSACCOUNT_SCALABLEDATA) != jsonObjectEnd) {
        auto scalableDataJson = jsonData_.at(DATADEAL_JSON_KEY_OHOSACCOUNT_SCALABLEDATA).get<std::string>();
        sptr<AAFwk::Want> want = AAFwk::Want::FromString(scalableDataJson);
        if (want == nullptr) {
            return ERR_ACCOUNT_COMMON_NULL_PTR_ERROR;
        }
        accountInfo.ohosAccountInfo_.scalableData_ = *want;
    }
    accountInfo.userId_ = userId;
    return ERR_OK;
}

void OhosAccountDataDeal::BuildJsonFileFromScratch(std::int32_t userId) const
{
    AccountInfo accountInfo;
    accountInfo.userId_ = userId;
    accountInfo.bindTime_ = 0;
    accountInfo.ohosAccountInfo_.uid_ = DEFAULT_OHOS_ACCOUNT_UID;
    accountInfo.ohosAccountInfo_.name_ = DEFAULT_OHOS_ACCOUNT_NAME;
    accountInfo.ohosAccountInfo_.status_ = ACCOUNT_STATE_UNBOUND;
    accountInfo.digest_ = "";
    SaveAccountInfo(accountInfo);
}
} // namespace AccountSA
} // namespace OHOS