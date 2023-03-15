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

#include "os_account_subscribe_death_recipient.h"

#include "account_log_wrapper.h"
#include "os_account_subscribe_manager.h"

namespace OHOS {
namespace AccountSA {
void OsAccountSubscribeDeathRecipient::OnRemoteDied(const wptr<IRemoteObject> &remote)
{
    ACCOUNT_LOGI("enter");
    if (remote == nullptr) {
        ACCOUNT_LOGE("remote object is nullptr");
        return;
    }

    sptr<IRemoteObject> object = remote.promote();
    if (object == nullptr) {
        ACCOUNT_LOGE("object is nullptr");
        return;
    }

    OsAccountSubscribeManager::GetInstance().UnsubscribeOsAccount(object);

    ACCOUNT_LOGI("end");
}
}  // namespace AccountSA
}  // namespace OHOS
