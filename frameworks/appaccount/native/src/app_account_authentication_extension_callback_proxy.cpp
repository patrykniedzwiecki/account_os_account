/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "app_account_authentication_extension_callback_proxy.h"

#include <securec.h>
#include "account_error_no.h"
#include "account_log_wrapper.h"
#include "want.h"

namespace OHOS {
namespace AccountSA {
AppAccountAuthenticationExtensionCallbackProxy::AppAccountAuthenticationExtensionCallbackProxy(
    const sptr<IRemoteObject> &object)
    : IRemoteProxy<IAppAccountAuthenticationExtensionCallback>(object)
{}

AppAccountAuthenticationExtensionCallbackProxy::~AppAccountAuthenticationExtensionCallbackProxy()
{}

ErrCode AppAccountAuthenticationExtensionCallbackProxy::SendRequest(
    IAppAccountAuthenticationExtensionCallback::Message code, MessageParcel &data)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        ACCOUNT_LOGE("remote is nullptr, code = %{public}d", code);
        return ERR_ACCOUNT_COMMON_NULL_PTR_ERROR;
    }
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    return remote->SendRequest(static_cast<uint32_t>(code), data, reply, option);
}

void AppAccountAuthenticationExtensionCallbackProxy::OnResult(
    const int32_t errCode, const AAFwk::WantParams &parameters)
{
    MessageParcel data;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        ACCOUNT_LOGE("failed to write descriptor");
        return;
    }
    if (!data.WriteInt32(errCode)) {
        ACCOUNT_LOGE("failed to write errCode");
        return;
    }
    if (!data.WriteParcelable(&parameters)) {
        ACCOUNT_LOGE("failed to write write request parameters");
        return;
    }
    ErrCode result = SendRequest(
        IAppAccountAuthenticationExtensionCallback::Message::APP_ACCOUNT_AUTHENTICATION_EXTENSION_CALLBACK_ON_RESULT,
        data);
    if (result != ERR_OK) {
        ACCOUNT_LOGE("failed to send request, error code: %{public}d", result);
    }
}
} // namespace AccountSA
} // namespace OHOS