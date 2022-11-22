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

#include <gtest/gtest.h>
#include <map>

#include "account_error_no.h"
#include "os_account_constants.h"

#include "os_account_delete_user_idm_callback.h"
#include "os_account_subscribe_death_recipient.h"
#define private public
#include "os_account_subscribe_manager.h"
#undef private
#include "os_account_manager_service.h"
#include "os_account_interface.h"
#include "mock_account_mgr_service.h"
#include "os_account_info.h"

namespace OHOS {
namespace AccountSA {
using namespace testing::ext;
using namespace OHOS::AccountSA;
using namespace OHOS;
using namespace AccountSA;
class OsAccountCoverageTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};


void OsAccountCoverageTest::SetUpTestCase(void)
{}

void OsAccountCoverageTest::TearDownTestCase(void)
{}

void OsAccountCoverageTest::SetUp(void)
{}

void OsAccountCoverageTest::TearDown(void)
{}


/*
 * @tc.name: OnRemoteDiedTest_0100
 * @tc.desc: test if OsAccountSubscribeDeathRecipient's OnRemoteDied function executed as expected in normal case.
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(OsAccountCoverageTest, OnRemoteDiedTest_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO)
        << "OsAccountCoverageTest, OnRemoteDiedTest_0100, TestSize.Level1";
    OsAccountSubscribeInfo subscribeInfo;
    sptr<MockAccountMgrService> listener = new (std::nothrow) MockAccountMgrService();
    ASSERT_NE(nullptr, listener);

    auto subscribeInfoPtr = std::make_shared<OsAccountSubscribeInfo>(subscribeInfo);

    DelayedSingleton<OsAccountSubscribeManager>::GetInstance()->SubscribeOsAccount(subscribeInfoPtr, listener);
    
    int size = DelayedSingleton<OsAccountSubscribeManager>::GetInstance()->subscribeRecords_.size();
    EXPECT_EQ(size, 1);

    std::shared_ptr<OsAccountSubscribeDeathRecipient> recipient = std::make_shared<OsAccountSubscribeDeathRecipient>();
    ASSERT_NE(nullptr, recipient);
    recipient->OnRemoteDied(listener);
    size = DelayedSingleton<OsAccountSubscribeManager>::GetInstance()->subscribeRecords_.size();
    EXPECT_EQ(size, 0);
}

/*
 * @tc.name: OnRemoteDiedTest_0200
 * @tc.desc: test if OsAccountSubscribeDeathRecipient's OnRemoteDied function executed
 * as expected when param is nullptr.
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(OsAccountCoverageTest, OnRemoteDiedTest_0200, TestSize.Level1)
{
    GTEST_LOG_(INFO)
        << "OsAccountCoverageTest, OnRemoteDiedTest_0200, TestSize.Level1";
    std::shared_ptr<OsAccountSubscribeDeathRecipient> recipient = std::make_shared<OsAccountSubscribeDeathRecipient>();
    ASSERT_NE(nullptr, recipient);
    wptr<IRemoteObject> wptrDeath = nullptr;
    recipient->OnRemoteDied(wptrDeath);
    int size = DelayedSingleton<OsAccountSubscribeManager>::GetInstance()->subscribeRecords_.size();
    EXPECT_EQ(size, 0);
}

/*
 * @tc.name: OnRemoteDiedTest_0200
 * @tc.desc: test if OsAccountSubscribeDeathRecipient's OnRemoteDied function executed as expected when
 *           sptr param is nullptr.
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(OsAccountCoverageTest, OnRemoteDiedTest_0300, TestSize.Level1)
{
    GTEST_LOG_(INFO)
        << "OsAccountCoverageTest, OnRemoteDiedTest_0300, TestSize.Level1";
    std::shared_ptr<OsAccountSubscribeDeathRecipient> recipient = std::make_shared<OsAccountSubscribeDeathRecipient>();
    ASSERT_NE(nullptr, recipient);
    const sptr<IRemoteObject> sptrDeath = nullptr;
    wptr<IRemoteObject> wptrDeath = sptrDeath;
    recipient->OnRemoteDied(wptrDeath);
    int size = DelayedSingleton<OsAccountSubscribeManager>::GetInstance()->subscribeRecords_.size();
    EXPECT_EQ(size, 0);
}

}  // namespace AccountSA
}  // namespace OHOS