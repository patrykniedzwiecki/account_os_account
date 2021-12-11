/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#ifndef OS_ACCOUNT_FRAMEWORK_OSACCOUNT_CORE_INCLUDE_OS_ACCOUNT_H
#define OS_ACCOUNT_FRAMEWORK_OSACCOUNT_CORE_INCLUDE_OS_ACCOUNT_H
#include "ios_account.h"
#include "os_account_event_listener.h"
namespace OHOS {
namespace AccountSA {
class OsAccount {
public:
    enum SubscribeState { ALREADY_SUBSCRIBED = 0, INITIAL_SUBSCRIPTION, SUBSCRIBE_FAILD };
    ErrCode CreateOsAccount(
        const std::string &name, const int &type, OsAccountInfo &osAccountInfo);
    ErrCode RemoveOsAccount(const int id);
    ErrCode IsOsAccountExists(const int id, bool &isOsAccountExists);
    ErrCode IsOsAccountActived(const int id, bool &isOsAccountActived);
    ErrCode IsOsAccountConstraintEnable(const int id, const std::string &constraint, bool &isConstraintEnable);
    ErrCode IsOsAccountVerified(const int id, bool &isOsAccountVerified);
    ErrCode GetCreatedOsAccountsCount(int &osAccountsCount);
    ErrCode GetOsAccountLocalIdFromProcess(int &id);
    ErrCode GetOsAccountLocalIdFromUid(const int uid, int &id);
    ErrCode QueryMaxOsAccountNumber(int &maxOsAccountNumber);
    ErrCode GetOsAccountAllConstraints(const int id, std::vector<std::string> &constraints);
    ErrCode QueryAllCreatedOsAccounts(std::vector<OsAccountInfo> &osAccountInfos);
    ErrCode QueryCurrentOsAccount(OsAccountInfo &osAccountInfo);
    ErrCode QueryOsAccountById(const int id, OsAccountInfo &osAccountInfo);
    ErrCode GetOsAccountTypeFromProcess(int &type);
    ErrCode GetOsAccountProfilePhoto(const int id, std::string &photo);
    ErrCode IsMultiOsAccountEnable(bool &isMultiOsAccountEnable);
    ErrCode SetOsAccountName(const int id, const std::string &localName);
    ErrCode SetOsAccountConstraints(const int id, const std::vector<std::string> &constraints, const bool enable);
    ErrCode SetOsAccountProfilePhoto(const int id, const std::string &photo);
    ErrCode GetDistributedVirtualDeviceId(std::int32_t &deviceId);
    ErrCode ActivateOsAccount(const int id);
    ErrCode StartOsAccount(const int id);
    ErrCode StopOsAccount(const int id);
    ErrCode SubscribeOsAccount(const std::shared_ptr<OsAccountSubscriber> &subscriber);
    ErrCode UnsubscribeOsAccount(const std::shared_ptr<OsAccountSubscriber> &subscriber);
    ErrCode GetOsAccountLocalIdForSerialNumber(const int64_t serialNumber, int &id);
    ErrCode GetSerialNumberForOsAccount(const int &id, int64_t &serialNumber);
    OS_ACCOUNT_SWITCH_MOD GetOsAccountSwitchMod();
    ErrCode IsCurrentOsAccountVerified(bool &isOsAccountVerified);
    ErrCode IsOsAccountCompleted(const int id, bool &isOsAccountCompleted);
    ErrCode SetCurrentOsAccountIsVerified(const bool isOsAccountVerified);
    ErrCode SetOsAccountIsVerified(const int id, const bool isOsAccountVerified);
    ErrCode ResetOsAccountProxy();

private:
    ErrCode GetOsAccountProxy();
    ErrCode CreateOsAccountEventListener(
        const std::shared_ptr<OsAccountSubscriber> &subscriber, sptr<IRemoteObject> &osAccountEventListener);

private:
    std::mutex mutex_;
    sptr<IOsAccount> osAccountProxy_;
    std::mutex eventListenersMutex_;
    std::map<std::shared_ptr<OsAccountSubscriber>, sptr<OsAccountEventListener>> eventListeners_;
    sptr<IRemoteObject::DeathRecipient> deathRecipient_;
};
}  // namespace AccountSA
}  // namespace OHOS
#endif /* OS_ACCOUNT_FRAMEWORK_OSACCOUNT_CORE_INCLUDE_OS_ACCOUNT_H */
