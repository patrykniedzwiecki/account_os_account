/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "inner_account_iam_manager.h"

#include "account_iam_callback.h"
#include "account_log_wrapper.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"
#include "user_auth_client.h"
#include "user_auth_client_impl.h"
#include "user_idm_client.h"

namespace OHOS {
namespace AccountSA {
namespace {
#ifdef HAS_STORAGE_PART
const int32_t ERROR_STORAGE_KEY_NOT_EXIST = -2;
#endif
}
using UserIDMClient = UserIam::UserAuth::UserIdmClient;
using UserAuthClient = UserIam::UserAuth::UserAuthClient;
using UserAuthClientImpl = UserIam::UserAuth::UserAuthClientImpl;

InnerAccountIAMManager::InnerAccountIAMManager()
{
    userStateMap_[0] = IDLE;
}

void InnerAccountIAMManager::OpenSession(int32_t userId, std::vector<uint8_t> &challenge)
{
    challenge = UserIDMClient::GetInstance().OpenSession(userId);
    std::lock_guard<std::mutex> lock(mutex_);
    userStateMap_[userId] = AFTER_OPEN_SESSION;
    userChallengeMap_[userId] = challenge;
}

void InnerAccountIAMManager::CloseSession(int32_t userId)
{
    UserIDMClient::GetInstance().CloseSession(userId);
    std::lock_guard<std::mutex> lock(mutex_);
    if (userId == 0) {
        userStateMap_[0] = IDLE;
    } else {
        userStateMap_.erase(userId);
    }
    userChallengeMap_.erase(userId);
}

void InnerAccountIAMManager::AddCredential(
    int32_t userId, const CredentialParameters &credInfo, const sptr<IIDMCallback> &callback)
{
    if (callback == nullptr) {
        ACCOUNT_LOGD("callback is nullptr");
        return;
    }
    auto idmCallback = std::make_shared<AddCredCallback>(userId, credInfo, callback);
    UserIDMClient::GetInstance().AddCredential(userId, credInfo, idmCallback);
}

void InnerAccountIAMManager::UpdateCredential(
    int32_t userId, const CredentialParameters &credInfo, const sptr<IIDMCallback> &callback)
{
    if (callback == nullptr) {
        ACCOUNT_LOGD("callback is nullptr");
        return;
    }
    if (credInfo.token.empty()) {
        ACCOUNT_LOGD("token is empty");
        Attributes emptyResult;
        callback->OnResult(ResultCode::INVALID_PARAMETERS, emptyResult);
        return;
    }
    auto idmCallback = std::make_shared<UpdateCredCallback>(userId, credInfo, callback);
    UserIDMClient::GetInstance().UpdateCredential(userId, credInfo, idmCallback);
}

void InnerAccountIAMManager::DelCred(
    int32_t userId, uint64_t credentialId, const std::vector<uint8_t> &authToken, const sptr<IIDMCallback> &callback)
{
    if (callback == nullptr) {
        ACCOUNT_LOGD("callback is nullptr");
        return;
    }
    Attributes errResult;
    if (authToken.empty()) {
        ACCOUNT_LOGD("token is empty");
        callback->OnResult(ResultCode::INVALID_PARAMETERS, errResult);
        return;
    }
    std::vector<uint8_t> secret;
    ErrCode result = UpdateUserKey(userId, credentialId, authToken, secret);
    if (result != ERR_OK) {
        callback->OnResult(result, errResult);
        return;
    }
    auto idmCallback = std::make_shared<DelCredCallback>(userId, credentialId, authToken, callback);
    UserIDMClient::GetInstance().DeleteCredential(userId, credentialId, authToken, idmCallback);
}

void InnerAccountIAMManager::DelUser(
    int32_t userId, const std::vector<uint8_t> &authToken, const sptr<IIDMCallback> &callback)
{
    if (callback == nullptr) {
        ACCOUNT_LOGD("callback is nullptr");
        return;
    }
    Attributes errResult;
    if (authToken.empty()) {
        ACCOUNT_LOGD("token is empty");
        callback->OnResult(ResultCode::INVALID_PARAMETERS, errResult);
        return;
    }
    ErrCode result = RemoveUserKey(userId, authToken);
    if (result != ERR_OK) {
        callback->OnResult(result, errResult);
        return;
    }
    auto idmCallback = std::make_shared<DelCredCallback>(userId, 0, authToken, callback);
    UserIDMClient::GetInstance().DeleteUser(userId, authToken, idmCallback);
}

void InnerAccountIAMManager::GetCredentialInfo(
    int32_t userId, AuthType authType, const sptr<IGetCredInfoCallback> &callback)
{
    auto getCallback = std::make_shared<GetCredInfoCallbackWrapper>(callback);
    UserIDMClient::GetInstance().GetCredentialInfo(userId, authType, getCallback);
}

int32_t InnerAccountIAMManager::Cancel(int32_t userId, uint64_t challenge)
{
    return UserIDMClient::GetInstance().Cancel(userId);
}

uint64_t InnerAccountIAMManager::AuthUser(int32_t userId, const std::vector<uint8_t> &challenge, AuthType authType,
    AuthTrustLevel authTrustLevel, const sptr<IIDMCallback> &callback)
{
    if (callback == nullptr) {
        ACCOUNT_LOGD("callback is nullptr");
        return ERR_ACCOUNT_COMMON_NULL_PTR_ERROR;
    }
    auto userAuthCallback = std::make_shared<AuthCallback>(userId, authType, callback);
    return UserAuthClient::GetInstance().BeginAuthentication(
        userId, challenge, authType, authTrustLevel, userAuthCallback);
}

int32_t InnerAccountIAMManager::CancelAuth(uint64_t contextId)
{
    return UserAuthClient::GetInstance().CancelAuthentication(contextId);
}

int32_t InnerAccountIAMManager::GetAvailableStatus(
    AuthType authType, AuthTrustLevel authTrustLevel)
{
    return UserAuthClientImpl::Instance().GetAvailableStatus(authType, authTrustLevel);
}

void InnerAccountIAMManager::GetProperty(
    int32_t userId, const GetPropertyRequest &request, const sptr<IGetSetPropCallback> &callback)
{
    auto getCallback = std::make_shared<GetPropCallbackWrapper>(callback);
    UserAuthClient::GetInstance().GetProperty(userId, request, getCallback);
}

void InnerAccountIAMManager::SetProperty(
    int32_t userId, const SetPropertyRequest &request, const sptr<IGetSetPropCallback> &callback)
{
    auto setCallback = std::make_shared<SetPropCallbackWrapper>(callback);
    UserAuthClient::GetInstance().SetProperty(userId, request, setCallback);
}

IAMState InnerAccountIAMManager::GetState(int32_t userId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = userStateMap_.find(userId);
    if (it != userStateMap_.end()) {
        return it->second;
    }
    return userStateMap_[0];
}

void InnerAccountIAMManager::SetState(int32_t userId, IAMState state)
{
    std::lock_guard<std::mutex> lock(mutex_);
    userStateMap_[userId] = state;
}

void InnerAccountIAMManager::GetChallenge(int32_t userId, std::vector<uint8_t> &challenge)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = userChallengeMap_.find(userId);
    if (it != userChallengeMap_.end()) {
        challenge = it->second;
    } else {
        challenge = userChallengeMap_[0];
    }
}

ErrCode InnerAccountIAMManager::ActivateUserKey(
    int32_t userId, const std::vector<uint8_t> &token, const std::vector<uint8_t> &secret)
{
#ifdef HAS_STORAGE_PART
    ErrCode result = GetStorageManagerProxy();
    if (result != ERR_OK) {
        ACCOUNT_LOGD("fail to get storage proxy");
        return result;
    }
    result = storageMgrProxy_->ActiveUserKey(userId, token, secret);
    if (result != ERR_OK && result != ERROR_STORAGE_KEY_NOT_EXIST) {
        ACCOUNT_LOGD("fail to active user key, error code: %{public}d", result);
        return result;
    }
    storageMgrProxy_->PrepareStartUser(userId);
#endif
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = credInfoMap_.find(userId);
    if (it != credInfoMap_.end()) {
        it->second.secret = secret;
    } else {
        credInfoMap_[userId] = {
            .secret = secret
        };
    }
    return ERR_OK;
}

ErrCode InnerAccountIAMManager::UpdateUserKey(int32_t userId, uint64_t credentialId,
    const std::vector<uint8_t> &token, const std::vector<uint8_t> &newSecret)
{
    ErrCode result = ERR_OK;
    AccountCredentialInfo oldCredInfo;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = credInfoMap_.find(userId);
    if (it != credInfoMap_.end()) {
        oldCredInfo = it->second;
    }
    if (newSecret.empty() && credentialId != oldCredInfo.credentialId) {
        ACCOUNT_LOGD("the key do not need to be removed");
        return ERR_OK;
    }
#ifdef HAS_STORAGE_PART
    result = GetStorageManagerProxy();
    if (result != ERR_OK) {
        ACCOUNT_LOGD("fail to get storage proxy");
        return result;
    }
    result = storageMgrProxy_->UpdateUserAuth(userId, token, oldCredInfo.secret, newSecret);
    if (result != ERR_OK && result != ERROR_STORAGE_KEY_NOT_EXIST) {
        ACCOUNT_LOGD("fail to update user auth");
        return result;
    }
    result = storageMgrProxy_->UpdateKeyContext(userId);
#endif
    credInfoMap_[userId] = {
        .credentialId = credentialId,
        .oldSecret = oldCredInfo.secret,
        .secret = newSecret
    };
    return result;
}

ErrCode InnerAccountIAMManager::RemoveUserKey(int32_t userId, const std::vector<uint8_t> &token)
{
    ErrCode result = ERR_OK;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = credInfoMap_.find(userId);
    if (it == credInfoMap_.end()) {
        return ERR_OK;
    }
    AccountCredentialInfo oldCredInfo = it->second;
    std::vector<uint8_t> newSecret;
#ifdef HAS_STORAGE_PART
    result = GetStorageManagerProxy();
    if (result != ERR_OK) {
        ACCOUNT_LOGD("fail to get storage proxy");
        return result;
    }
    result = storageMgrProxy_->UpdateUserAuth(userId, token, oldCredInfo.secret, newSecret);
    if (result != ERR_OK && result != ERROR_STORAGE_KEY_NOT_EXIST) {
        ACCOUNT_LOGD("fail to update user auth");
        return result;
    }
    result = storageMgrProxy_->UpdateKeyContext(userId);
#endif
    credInfoMap_[userId] = {
        .oldSecret = oldCredInfo.secret,
        .secret = newSecret
    };
    return result;
}

ErrCode InnerAccountIAMManager::RestoreUserKey(int32_t userId, uint64_t credentialId,
    const std::vector<uint8_t> &token)
{
    ErrCode result = ERR_OK;
    AccountCredentialInfo credInfo;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = credInfoMap_.find(userId);
    if (it != credInfoMap_.end()) {
        credInfo = it->second;
    }
    if (credentialId != 0 && credInfo.credentialId != credentialId) {
        return ERR_OK;
    }
#ifdef HAS_STORAGE_PART
    result = GetStorageManagerProxy();
    if (result != ERR_OK) {
        ACCOUNT_LOGD("fail to get storage proxy");
        return result;
    }
    result = storageMgrProxy_->UpdateUserAuth(userId, token, credInfo.secret, credInfo.oldSecret);
    if (result != ERR_OK && result != ERROR_STORAGE_KEY_NOT_EXIST) {
        ACCOUNT_LOGD("fail to update user auth");
        return result;
    }
    result = storageMgrProxy_->UpdateKeyContext(userId);
#endif
    credInfoMap_[userId] = {
        .secret = credInfo.oldSecret
    };
    return result;
}

ErrCode InnerAccountIAMManager::GetStorageManagerProxy()
{
#ifdef HAS_STORAGE_PART
    if (storageMgrProxy_ != nullptr) {
        return ERR_OK;
    }
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGD("failed to get system ability mgr");
        return ERR_ACCOUNT_IAM_SERVICE_GET_STORAGE_SYSTEM_ABILITY;
    }
    auto remote = systemAbilityManager->GetSystemAbility(STORAGE_MANAGER_MANAGER_ID);
    if (!remote) {
        ACCOUNT_LOGD("failed to get STORAGE_MANAGER_MANAGER_ID service");
        return ERR_ACCOUNT_IAM_SERVICE_REMOTE_IS_NULLPTR;
    }
    storageMgrProxy_ = iface_cast<StorageManager::IStorageManager>(remote);
    if (!storageMgrProxy_) {
        ACCOUNT_LOGD("failed to get STORAGE_MANAGER_MANAGER_ID proxy");
        return ERR_ACCOUNT_IAM_SERVICE_REMOTE_IS_NULLPTR;
    }
#endif
    return ERR_OK;
}
}  // namespace AccountSA
}  // namespace OHOS