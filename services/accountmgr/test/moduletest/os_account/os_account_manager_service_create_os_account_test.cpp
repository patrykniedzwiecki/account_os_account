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

#include <gtest/gtest.h>
#include <thread>
#include "account_error_no.h"
#include "account_log_wrapper.h"
#include "os_account_constants.h"
#define private public
#include "os_account_control_file_manager.h"
#include "os_account_manager_service.h"
#undef private

namespace OHOS {
namespace AccountSA {
using namespace testing::ext;
using namespace OHOS::AccountSA;
using namespace OHOS;
using namespace AccountSA;

namespace {
const std::string STRING_TEST_NAME = "name";
const std::int32_t DELAY_FOR_OPERATION = 250;
}  // namespace
class OsAccountManagerServiceCreateOsAccountTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();

public:
    std::shared_ptr<OsAccountManagerService> osAccountManagerService_;
};
void OsAccountManagerServiceCreateOsAccountTest::SetUpTestCase(void)
{}

void OsAccountManagerServiceCreateOsAccountTest::TearDownTestCase(void)
{}

void OsAccountManagerServiceCreateOsAccountTest::SetUp(void)
{
    osAccountManagerService_ = std::make_shared<OsAccountManagerService>();
}

void OsAccountManagerServiceCreateOsAccountTest::TearDown(void)
{}

/**
 * @tc.name: OsAccountManagerServiceCreateOsAccountTest001
 * @tc.desc: Test CreateOsAccount when create max accounts.
 * @tc.type: FUNC
 * @tc.require: SR000GGVFN
 */
HWTEST_F(OsAccountManagerServiceCreateOsAccountTest, OsAccountManagerServiceCreateOsAccountTest001, TestSize.Level1)
{
    ErrCode errCode;
    for (auto i = Constants::START_USER_ID + 1; i < Constants::MAX_USER_ID; i++) {
        OsAccountInfo osAccountInfoOne;
        ACCOUNT_LOGI("before CreateOsAccount, i = %{public}d.", i);
        GTEST_LOG_(INFO) << "before CreateOsAccount, i = " << i;
        errCode = osAccountManagerService_->CreateOsAccount(STRING_TEST_NAME, OsAccountType::ADMIN, osAccountInfoOne);
        EXPECT_EQ(errCode, ERR_OK);
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_FOR_OPERATION));
    }

    OsAccountInfo osAccountInfoOne;
    errCode = osAccountManagerService_->CreateOsAccount(STRING_TEST_NAME, OsAccountType::ADMIN, osAccountInfoOne);
    EXPECT_NE(errCode, ERR_OK);

    for (auto i = Constants::START_USER_ID + 1; i < Constants::MAX_USER_ID; i++) {
        ACCOUNT_LOGI("before DelOsAccount, i = %{public}d.", i);
        GTEST_LOG_(INFO) << "before DelOsAccount, i = " << i;
        osAccountManagerService_->RemoveOsAccount(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_FOR_OPERATION));
    }
}
}  // namespace AccountSA
}  // namespace OHOS