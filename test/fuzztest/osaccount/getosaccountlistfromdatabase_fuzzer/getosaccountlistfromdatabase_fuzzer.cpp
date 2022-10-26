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

#include "getosaccountlistfromdatabase_fuzzer.h"

#include <string>
#include <vector>
#include "os_account_manager.h"
#include "account_log_wrapper.h"
#undef private
#include "os_account_constants.h"

using namespace std;
using namespace OHOS::AccountSA;
namespace OHOS {
    bool GetOsAccountListFromDatabaseFuzzTest(const uint8_t* data, size_t size)
    {
        bool result = false;
        if (size > 0) {
            std::vector<OsAccountInfo> TEST_LIST{};
            std::string randomId(reinterpret_cast<const char*>(data), size);
            result = OsAccountManager::GetOsAccountListFromDatabase(randomId, TEST_LIST);
        }
        return result;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::GetOsAccountListFromDatabaseFuzzTest(data, size);
    return 0;
}