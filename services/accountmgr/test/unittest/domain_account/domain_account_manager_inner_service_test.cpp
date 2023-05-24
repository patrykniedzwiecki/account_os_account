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

#include <gtest/gtest.h>
#include <thread>
#include "account_error_no.h"
#include "account_log_wrapper.h"
#define private public
#include "domain_account_plugin_death_recipient.h"
#include "domain_account_plugin_service.h"
#include "domain_auth_callback_proxy.h"
#include "domain_has_domain_info_callback.h"
#include "inner_domain_account_manager.h"
#undef private
#include "mock_domain_account_callback_stub.h"
#include "mock_inner_os_account_manager.h"

namespace OHOS {
namespace AccountSA {
using namespace testing;
using namespace testing::ext;
using namespace OHOS::AccountSA;
using namespace OHOS;
using namespace AccountSA;

namespace {
const std::string STRING_TEST_NAME = "name";
const std::string TEST_NO_DOUND_NAME = "test_no_bound_name";
const std::string TEST_DOMAIN_ACCOUNT_NAME = "test_domain_account_name";
const std::string TEST_DOMAIN = "test_domain";
const std::string TEST_ACCOUNT_ID = "test_account_id";
const std::int32_t MAIN_ACCOUNT_ID = 100;
const std::vector<uint8_t> TEST_TOKEN = {0};
const std::vector<uint8_t> TEST_PASSWORD = {0};
}  // namespace

class DomainAccountManagerInnerServiceTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void DomainAccountManagerInnerServiceTest::SetUpTestCase(void)
{}

void DomainAccountManagerInnerServiceTest::TearDownTestCase(void)
{}

void DomainAccountManagerInnerServiceTest::SetUp(void)
{}

void DomainAccountManagerInnerServiceTest::TearDown(void)
{}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest001
 * @tc.desc: Test Auth func with no loical id bound domain info.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest001, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_NO_DOUND_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;

    EXPECT_EQ(InnerDomainAccountManager::GetInstance().Auth(domainInfo, TEST_PASSWORD, nullptr), ERR_OK);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest002
 * @tc.desc: Test Auth func with loical id has domain info.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest002, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;

    EXPECT_EQ(InnerDomainAccountManager::GetInstance().Auth(domainInfo, TEST_PASSWORD, nullptr), ERR_OK);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest003
 * @tc.desc: Test AuthWithPopup with current activated id is not exist.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest003, TestSize.Level1)
{
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().AuthWithPopup(0, nullptr),
        ERR_OSACCOUNT_SERVICE_INNER_CANNOT_FIND_OSACCOUNT_ERROR);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest004
 * @tc.desc: Test AuthWithToken.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest004, TestSize.Level1)
{
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().AuthWithToken(MAIN_ACCOUNT_ID, TEST_TOKEN), ERR_OK);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest005
 * @tc.desc: Test StartAuth with callback is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest005, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().StartAuth(
        nullptr, domainInfo, TEST_TOKEN, nullptr, AUTH_WITH_CREDENTIAL_MODE), ERR_ACCOUNT_COMMON_INVALID_PARAMETER);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest006
 * @tc.desc: Test StartAuth with auth mode is invalid.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest006, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    sptr<IDomainAccountPlugin> testPlugin = new (std::nothrow) DomainAccountPluginService(nullptr);
    ASSERT_NE(testPlugin, nullptr);
    sptr<IDomainAuthCallback> innerCallback = new (std::nothrow) InnerDomainAuthCallback(MAIN_ACCOUNT_ID, nullptr);
    ASSERT_NE(innerCallback, nullptr);
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().StartAuth(testPlugin,
        domainInfo, TEST_TOKEN, innerCallback, AUTH_MODE_END), ERR_ACCOUNT_COMMON_INVALID_PARAMETER);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest007
 * @tc.desc: Test RegisterPlugin with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest007, TestSize.Level1)
{
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().RegisterPlugin(nullptr), ERR_ACCOUNT_COMMON_INVALID_PARAMETER);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest008
 * @tc.desc: Test GetAuthStatusInfo with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest008, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().GetAuthStatusInfo(domainInfo, nullptr),
        ERR_DOMAIN_ACCOUNT_SERVICE_PLUGIN_NOT_EXIST);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest009
 * @tc.desc: Test GetAuthStatusInfo with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest009, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    EXPECT_EQ(InnerDomainAccountManager::GetInstance().StartHasDomainAccount(nullptr, domainInfo, nullptr),
        ERR_ACCOUNT_COMMON_INVALID_PARAMETER);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest010
 * @tc.desc: Test StartOnAccountBound with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest010, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    auto callback = std::make_shared<MockDomainAccountCallback>();
    ASSERT_NE(callback, nullptr);
    EXPECT_CALL(*callback, OnResult(ERR_DOMAIN_ACCOUNT_SERVICE_PLUGIN_NOT_EXIST, _)).Times(Exactly(1));
    sptr<MockDomainAccountCallbackStub> testCallback = new (std::nothrow) MockDomainAccountCallbackStub(callback);
    ASSERT_NE(testCallback, nullptr);
    InnerDomainAccountManager::GetInstance().StartOnAccountBound(nullptr, domainInfo, MAIN_ACCOUNT_ID, testCallback);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest011
 * @tc.desc: Test StartOnAccountUnBound with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest011, TestSize.Level1)
{
    DomainAccountInfo domainInfo;
    domainInfo.accountName_ = TEST_DOMAIN_ACCOUNT_NAME;
    domainInfo.domain_ = TEST_DOMAIN;
    domainInfo.accountId_ = TEST_ACCOUNT_ID;
    auto callback = std::make_shared<MockDomainAccountCallback>();
    ASSERT_NE(callback, nullptr);
    EXPECT_CALL(*callback, OnResult(ERR_DOMAIN_ACCOUNT_SERVICE_PLUGIN_NOT_EXIST, _)).Times(Exactly(1));
    sptr<MockDomainAccountCallbackStub> testCallback = new (std::nothrow) MockDomainAccountCallbackStub(callback);
    ASSERT_NE(testCallback, nullptr);
    InnerDomainAccountManager::GetInstance().StartOnAccountUnBound(nullptr, domainInfo, testCallback);
}

/**
 * @tc.name: DomainAccountManagerInnerServiceTest012
 * @tc.desc: Test StartGetDomainAccountInfo with plugin is nullptr.
 * @tc.type: FUNC
 * @tc.require: issueI64KAM
 */
HWTEST_F(DomainAccountManagerInnerServiceTest, DomainAccountManagerInnerServiceTest012, TestSize.Level1)
{
    auto callback = std::make_shared<MockDomainAccountCallback>();
    ASSERT_NE(callback, nullptr);
    EXPECT_CALL(*callback, OnResult(ERR_DOMAIN_ACCOUNT_SERVICE_PLUGIN_NOT_EXIST, _)).Times(Exactly(1));
    sptr<MockDomainAccountCallbackStub> testCallback = new (std::nothrow) MockDomainAccountCallbackStub(callback);
    ASSERT_NE(testCallback, nullptr);
    InnerDomainAccountManager::GetInstance().StartGetDomainAccountInfo(
        nullptr, TEST_DOMAIN, TEST_DOMAIN_ACCOUNT_NAME, testCallback);
}
}  // namespace AccountSA
}  // namespace OHOS