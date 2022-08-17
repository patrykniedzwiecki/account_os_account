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

#ifndef OS_ACCOUNT_INTERFACES_INNERKITS_ACCOUNT_IAM_NATIVE_INCLUDE_ACCOUNT_IAM_CALLBACK_SERVICE_H
#define OS_ACCOUNT_INTERFACES_INNERKITS_ACCOUNT_IAM_NATIVE_INCLUDE_ACCOUNT_IAM_CALLBACK_SERVICE_H

#include "account_iam_callback_stub.h"
#include "account_iam_client_callback.h"

namespace OHOS {
namespace AccountSA {
class IDMCallbackService : public IDMCallbackStub {
public:
    explicit IDMCallbackService(std::shared_ptr<IDMCallback> callback);
    void OnAcquireInfo(int32_t module, uint32_t acquireInfo, const Attributes &extraInfo) override;
    void OnResult(int32_t result, const Attributes &extraInfo) override;

private:
    std::shared_ptr<IDMCallback> callback_;
    DISALLOW_COPY_AND_MOVE(IDMCallbackService);
};

class GetCredInfoCallbackService : public GetCredInfoCallbackStub {
public:
    explicit GetCredInfoCallbackService(std::shared_ptr<GetCredInfoCallback> callback);
    void OnCredentialInfo(const std::vector<CredentialInfo> &infoList) override;

private:
    std::shared_ptr<GetCredInfoCallback> callback_;
    DISALLOW_COPY_AND_MOVE(GetCredInfoCallbackService);
};

class GetSetPropCallbackService : public GetSetPropCallbackStub {
public:
    explicit GetSetPropCallbackService(std::shared_ptr<GetSetPropCallback> callback);
    void OnResult(int32_t result, const Attributes &extraInfo) override;

private:
    std::shared_ptr<GetSetPropCallback> callback_;
    DISALLOW_COPY_AND_MOVE(GetSetPropCallbackService);
};

class GetDataCallbackService : public GetDataCallbackStub {
public:
    explicit GetDataCallbackService(const std::shared_ptr<GetDataCallback> &callback);
    void OnGetData(int32_t authSubType, const sptr<ISetDataCallback> &inputerSetData) override;

private:
    std::shared_ptr<GetDataCallback> callback_;
    DISALLOW_COPY_AND_MOVE(GetDataCallbackService);
};
}  // namespace AccountSA
}  // namespace OHOS
#endif  // OS_ACCOUNT_INTERFACES_INNERKITS_ACCOUNT_IAM_NATIVE_INCLUDE_ACCOUNT_IAM_CALLBACK_SERVICE_H