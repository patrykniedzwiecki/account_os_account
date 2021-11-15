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

#ifndef BASE_ACCOUNT_INCLUDE_ACCOUNT_ERROR_NO_H
#define BASE_ACCOUNT_INCLUDE_ACCOUNT_ERROR_NO_H

#include "errors.h"

namespace OHOS {
enum {
    ACCOUNT_MODULE_COMMON = 0x00,
    ACCOUNT_MODULE_ACCOUNTMGR,
    ACCOUNT_MODULE_DATADEAL,
    ACCOUNT_MODULE_IACCOUNT,
    ACCOUNT_MODULE_APPACCOUNT_KIT,
    ACCOUNT_MODULE_APPACCOUNT_SERVICE,
    ACCOUNT_MODULE_OSACCOUNT_KIT,
    ACCOUNT_MODULE_OSACCOUNT_SERVICE
};

/* Error code for common */
constexpr ErrCode ACCOUNT_COMMON_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_COMMON);

/* Error code for AccountMgr */
constexpr ErrCode ACCOUNT_ACCOUNTMGR_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_ACCOUNTMGR);
enum {
    ERR_ACCOUNT_MGR_DUMP_ERROR = ACCOUNT_ACCOUNTMGR_ERR_OFFSET + 0x0001,
    ERR_ACCOUNT_MGR_GET_REMOTE_SA_ERROR,
    ERR_ACCOUNT_MGR_CONNECT_SA_ERROR,
    ERR_ACCOUNT_MGR_ADD_TO_SA_ERROR
};

/* Error code for DataDeal module */
constexpr ErrCode ACCOUNT_DATADEAL_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_DATADEAL);
enum {
    ERR_ACCOUNT_DATADEAL_INPUT_FILE_ERROR = ACCOUNT_DATADEAL_ERR_OFFSET + 0x0001,
    ERR_ACCOUNT_DATADEAL_FILE_PARSE_FAILED,
    ERR_ACCOUNT_DATADEAL_DIGEST_ERROR,
    ERR_ACCOUNT_DATADEAL_FILE_WRITE_FAILED,
    ERR_ACCOUNT_DATADEAL_JSON_KEY_NOT_EXIST,
    ERR_ACCOUNT_DATADEAL_NOT_READY,
    ERR_ACCOUNT_DATADEAL_JSON_FILE_CORRUPTION
};

/* Error code for IAccount */
constexpr ErrCode ACCOUNT_IACCOUNT_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_IACCOUNT);
enum {
    ERR_ACCOUNT_ZIDL_ACCOUNT_INFO_CHECK_ERROR = ACCOUNT_IACCOUNT_ERR_OFFSET + 0x0001,
    ERR_ACCOUNT_ZIDL_WRITE_DESCRIPTOR_ERROR,
    ERR_ACCOUNT_ZIDL_READ_RESULT_ERROR,
    ERR_ACCOUNT_ZIDL_WRITE_RESULT_ERROR,
    ERR_ACCOUNT_ZIDL_ACCOUNT_STUB_ERROR,
    ERR_ACCOUNT_ZIDL_ACCOUNT_SEND_REQUEST_ERROR,
    ERR_ACCOUNT_ZIDL_WRITE_NAME_ERROR,
    ERR_ACCOUNT_ZIDL_WRITE_UID_ERROR,
    ERR_ACCOUNT_ZIDL_WRITE_ACCOUNT_STATUS_ERROR,
    ERR_ACCOUNT_ZIDL_MGR_NOT_READY_ERROR,
    ERR_ACCOUNT_ZIDL_CHECK_PERMISSION_ERROR,
    ERR_ACCOUNT_ZIDL_WRITE_PARCEL_DATA_ERROR,
    ERR_ACCOUNT_ZIDL_INVALID_RESULT_ERROR
};

/* Error code for APPACCOUNT_KIT */
constexpr ErrCode APPACCOUNT_KIT_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_APPACCOUNT_KIT);
enum {
    /* AppAccount::GetAppAccountProxy */
    /* 4456449 */
    ERR_APPACCOUNT_KIT_GET_SYSTEM_ABILITY_MANAGER = APPACCOUNT_KIT_ERR_OFFSET + 0x0001,
    ERR_APPACCOUNT_KIT_GET_ACCOUNT_SYSTEM_ABILITY,
    ERR_APPACCOUNT_KIT_CAST_ACCOUNT_PROXY,
    ERR_APPACCOUNT_KIT_GET_APP_ACCOUNT_SERVICE,
    ERR_APPACCOUNT_KIT_GET_APP_ACCOUNT_PROXY,
    ERR_APPACCOUNT_KIT_CREATE_APP_ACCOUNT_DEATH_RECIPIENT,
    /* AppAccount */
    /* 4456455 */
    ERR_APPACCOUNT_KIT_NAME_IS_EMPTY,
    ERR_APPACCOUNT_KIT_NAME_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_NAME_CONTAINS_BLANK_SPACES,
    ERR_APPACCOUNT_KIT_EXTRA_INFO_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_AUTHORIZED_APP_IS_EMPTY,
    ERR_APPACCOUNT_KIT_AUTHORIZED_APP_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_ASSOCIATED_KEY_IS_EMPTY,
    ERR_APPACCOUNT_KIT_ASSOCIATED_KEY_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_ASSOCIATED_VALUE_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_CREDENTIAL_TYPE_IS_EMPTY,
    ERR_APPACCOUNT_KIT_CREDENTIAL_TYPE_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_CREDENTIAL_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_TOKEN_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_OWNER_IS_EMPTY,
    ERR_APPACCOUNT_KIT_OWNER_OUT_OF_RANGE,
    ERR_APPACCOUNT_KIT_SUBSCRIBER_IS_NULLPTR,
    ERR_APPACCOUNT_KIT_GET_SUBSCRIBE_INFO,
    ERR_APPACCOUNT_KIT_GET_OWNERS,
    ERR_APPACCOUNT_KIT_SUBSCRIBER_HAS_NO_OWNER,
    ERR_APPACCOUNT_KIT_APP_ACCOUNT_PROXY_IS_NULLPTR,
    ERR_APPACCOUNT_KIT_SUBSCRIBE,
    ERR_APPACCOUNT_KIT_NO_SPECIFIED_SUBSCRIBER_HAS_BEEN_REGISTERED,
    /* AppAccountProxy & AppAccountEventProxy */
    /* 4456477 */
    ERR_APPACCOUNT_KIT_WRITE_STRING_NAME,
    ERR_APPACCOUNT_KIT_WRITE_STRING_OWNER,
    ERR_APPACCOUNT_KIT_WRITE_STRING_EXTRA_INFO,
    ERR_APPACCOUNT_KIT_WRITE_STRING_AUTHORIZED_APP,
    ERR_APPACCOUNT_KIT_WRITE_STRING_KEY,
    ERR_APPACCOUNT_KIT_WRITE_STRING_VALUE,
    ERR_APPACCOUNT_KIT_WRITE_BOOL_SYNC_ENABLE,
    ERR_APPACCOUNT_KIT_WRITE_STRING_ASSOCIATEKEY,
    ERR_APPACCOUNT_KIT_WRITE_STRING_CREDENTIAL_TYPE,
    ERR_APPACCOUNT_KIT_WRITE_STRING_CREDENTIAL,
    ERR_APPACCOUNT_KIT_WRITE_STRING_TOKEN,
    ERR_APPACCOUNT_KIT_READ_PARCELABLE_APP_ACCOUNT_INFO,
    ERR_APPACCOUNT_KIT_WRITE_PARCELABLE_SUBSCRIBE_INFO,
    ERR_APPACCOUNT_KIT_WRITE_PARCELABLE_EVENT_LISTENER,
    ERR_APPACCOUNT_KIT_REMOTE_IS_NULLPTR,
    ERR_APPACCOUNT_KIT_SEND_REQUEST,
    /* AppAccountStub */
    /* 4456493 */
    ERR_APPACCOUNT_KIT_READ_STRING_NAME,
    ERR_APPACCOUNT_KIT_READ_STRING_OWNER,
    ERR_APPACCOUNT_KIT_READ_STRING_AUTHORIZED_APP,
    ERR_APPACCOUNT_KIT_READ_STRING_ASSOCIATED_DATA,
    ERR_APPACCOUNT_KIT_READ_STRING_CREDENTIAL_TYPE,
    /* AppAccountEventStub */
    ERR_APPACCOUNT_KIT_READ_PARCELABLE_VECTOR_ACCOUNT_INFO,
};

/* Error code for APPACCOUNT_SERVICE */
constexpr ErrCode APPACCOUNT_SERVICE_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_APPACCOUNT_SERVICE);
enum {
    /* 4521985 */
    ERR_APPACCOUNT_SERVICE_NAME_IS_EMPTY = APPACCOUNT_SERVICE_ERR_OFFSET + 0x0001,
    ERR_APPACCOUNT_SERVICE_NAME_OUT_OF_RANGE,
    ERR_APPACCOUNT_SERVICE_NAME_INVALID,
    ERR_APPACCOUNT_SERVICE_EXTRA_INFO_OUT_OF_RANGE,
    ERR_APPACCOUNT_SERVICE_OWNERS_ARE_EMPTY,
    ERR_APPACCOUNT_SERVICE_PERMISSION_DENIED,
    /* InnerAppAccountManager */
    /* 4521991 */
    ERR_APPACCOUNT_SERVICE_CONTROL_MANAGER_PTR_IS_NULLPTR,
    ERR_APPACCOUNT_SERVICE_SUBSCRIBE_MANAGER_PTR_IS_NULLPTR,
    /* AppAccountControlManager */
    ERR_APPACCOUNT_SERVICE_CREATE_EVENT_HANDLER,
    ERR_APPACCOUNT_SERVICE_DATA_STORAGE_PTR_IS_NULLPTR,
    ERR_APPACCOUNT_SERVICE_ACCOUNT_MAX_SIZE,
    ERR_APPACCOUNT_SERVICE_GET_ACCOUNT_INFO_BY_ID,
    ERR_APPACCOUNT_SERVICE_GET_IACCOUNT_INFO_BY_OWNER,
    ERR_APPACCOUNT_SERVICE_GET_SYNC_ENABLE,
    ERR_APPACCOUNT_SERVICE_GET_ASSOCIATED_DATA,
    ERR_APPACCOUNT_SERVICE_SET_ASSOCIATED_DATA,
    ERR_APPACCOUNT_SERVICE_GET_ACCOUNT_CREDENTIAL,
    ERR_APPACCOUNT_SERVICE_SET_ACCOUNT_CREDENTIAL,
    ERR_APPACCOUNT_SERVICE_ADD_ACCOUNT_INFO,
    ERR_APPACCOUNT_SERVICE_SAVE_ACCOUNT_INFO,
    ERR_APPACCOUNT_SERVICE_ADD_EXISTING_ACCOUNT,
    ERR_APPACCOUNT_SERVICE_REMOVE_INFO_BY_KEY,
    ERR_APPACCOUNT_SERVICE_GET_EXTRA_INFO,
    ERR_APPACCOUNT_SERVICE_SET_EXTRA_INFO,
    ERR_APPACCOUNT_SERVICE_GET_OWNER,
    ERR_APPACCOUNT_SERVICE_GET_BUNDLE_NAME,
    ERR_APPACCOUNT_SERVICE_GET_AUTHORIZED_APPS,
    ERR_APPACCOUNT_SERVICE_BUNDLE_NAME_IS_THE_SAME,
    ERR_APPACCOUNT_SERVICE_ENABLE_APP_ACCESS_ALREADY_EXISTS,
    ERR_APPACCOUNT_SERVICE_DISABLE_APP_ACCESS_NOT_EXISTED,
    ERR_APPACCOUNT_SERVICE_GET_ACCOUNT_CACHE,
    ERR_APPACCOUNT_SERVICE_GET_OAUTH_TOKEN,
    ERR_APPACCOUNT_SERVICE_SET_OAUTH_TOKEN,
    ERR_APPACCOUNT_SERVICE_CLEAR_OAUTH_TOKEN,
    /* AppAccountSubscribeManager */
    /* 4522019 */
    ERR_APPACCOUNT_SERVICE_SUBSCRIBE_INFO_PTR_IS_NULLPTR,
    ERR_APPACCOUNT_SERVICE_EVENT_LISTENER_IS_NULLPTR,
    ERR_APPACCOUNT_SERVICE_GET_OWNERS,
    ERR_APPACCOUNT_SERVICE_OWNERS_SIZE_IS_ZERO,
    ERR_APPACCOUNT_SERVICE_SUBSCRIBE_RECORD_PTR_IS_NULLPTR,
    ERR_APPACCOUNT_SERVICE_SUBSCRIBE_PERMISSON_DENIED,
    ERR_APPACCOUNT_SERVICE_OTHER,
};

/* Error code for OSACCOUNT_KIT */
constexpr ErrCode ACCOUNT_OSACCOUNT_KIT_ERR_OFFSET = ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_OSACCOUNT_KIT);
enum {
    CHECK_ADMIN_ACCOUNT_FAILED = ACCOUNT_OSACCOUNT_KIT_ERR_OFFSET + 0x0001,
    CHECK_CURRENT_ACCOUNT_FAILED,
    CONNECT_ACCOUNT_SERVICE_FAILED,
    ERR_OS_ACCOUNT_KIT_WRITE_LOCALNAME_ERROR,
    ERR_OS_ACCOUNT_KIT_WRITE_OSACCOUNT_TYPE_ERROR,
    ERR_OS_ACCOUNT_KIT_CREATE_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_INT_LOCALID_ERROR,
    ERR_OSACCOUNT_KIT_READ_LOCALNAME_ERROR,
    ERR_OSACCOUNT_KIT_REMOVE_OSACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_READ_OSACCOUNTTYPE_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_REPLY_ERROR,
    ERR_OSACCOUNT_KIT_READ_IN_LOCALID_ERROR,
    ERR_OSACCOUNT_KIT_REMOTE_IS_NULLPTR,
    ERR_OSACCOUNT_KIT_SEND_REQUEST_ERROR,
    ERR_OSACCOUNT_KIT_GET_SYSTEM_ABILITY_MANAGER_ERROR,
    ERR_OSACCOUNT_KIT_GET_ACCOUNT_SYSTEM_ABILITY_ERROR,
    ERR_OSACCOUNT_KIT_CAST_ACCOUNT_PROXY_ERROR,
    ERR_OSACCOUNT_KIT_GET_APP_ACCOUNT_SERVICE_ERROR,
    ERR_OSACCOUNT_KIT_GET_APP_ACCOUNT_PROXY_ERROR,
    ERR_OSACCOUNT_KIT_CREATE_APP_ACCOUNT_DEATH_RECIPIENT_ERROR,
    ERR_OSACCOUNT_KIT_IS_OS_ACCOUNT_EXISTS_ERROR,
    ERR_OSACCOUNT_KIT_IS_OS_ACCOUNT_ACTIVED_ERROR,
    ERR_OSACCOUNT_KIT_IS_OS_ACCOUNT_CONSTRAINT_ENABLE_ERROR,
    ERR_OSACCOUNT_KIT_IS_TEST_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_IS_OS_ACCOUNT_VERIFIED_ERROR,
    ERR_OSACCOUNT_KIT_GET_CREATED_OS_ACCOUNT_COUNT_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_LOCAL_ID_FROM_PROCESS_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_LOCAL_ID_FROM_UID_ERROR,
    ERR_OSACCOUNT_KIT_QUERY_MAX_OS_ACCOUNT_NUMBER_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_ALL_CONSTRAINTS_ERROR,
    ERR_OSACCOUNT_KIT_QUERY_ALL_CREATED_OS_ACCOUNTS_ERROR,
    ERR_OSACCOUNT_KIT_QUERY_CURRENT_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_QUERY_OS_ACCOUNT_BY_ID_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_TYPE_FROM_PROCESS_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_PROFILE_PHOTO_ERROR,
    ERR_OSACCOUNT_KIT_IS_MULTI_OS_ACCOUNT_ENABLE_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_STRING_CONSTRAINT_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_INT_UID_ERROR,
    ERR_OSACCOUNT_KIT_READ_CONSTRAINTS_ERROR,
    ERR_OSACCOUNT_KIT_READ_IN_UID_ERROR,
    ERR_OSACCOUNT_KIT_SET_OS_ACCOUNT_NAME_ERROR,
    ERR_OSACCOUNT_KIT_SET_OS_ACCOUNT_CONSTRAINTS_ERROR,
    ERR_OSACCOUNT_KIT_SET_OS_ACCOUNT_PROFILE_PHOTO_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_STRING_LOACLNAME_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_STRING_PHOTO_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_STRINGVECTOR_CONSTRAINTS_ERROR,
    ERR_OSACCOUNT_KIT_READ_STRINGVECTOR_CONSTRAINTS_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_BOOL_ENABLE_ERROR,
    ERR_OSACCOUNT_KIT_GET_DISTRIBUTED_VIRTUAL_DEVICE_ID_ERROR,
    ERR_OSACCOUNT_KIT_ACTIVATE_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_START_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_STOP_OS_ACCOUNT_ERROR,
    ERR_OSACCOUNT_KIT_LOCAL_NAME_OUTFLOW_ERROR,
    ERR_OSACCOUNT_KIT_PHOTO_OUTFLOW_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_PARCELABLE_SUBSCRIBE_INFO_ERROR,
    ERR_OSACCOUNT_KIT_WRITE_PARCELABLE_EVENT_LISTENER_ERROR,
    ERR_OSACCOUNT_KIT_SUBSCRIBE_ERROR,
    ERR_OSACCOUNT_KIT_UNSUBSCRIBE_ERROR,
    ERR_OSACCOUNT_KIT_SUBSCRIBER_IS_NULLPTR,
    ERR_OSACCOUNT_KIT_GET_SUBSCRIBE_INFO_ERROR,
    ERR_OSACCOUNT_KIT_GET_OS_ACCOUNT_SUBSCRIBE_TYPE_ERROR,
    ERR_OSACCOUNT_KIT_GET_NAME_ERROR,
    ERR_OSACCOUNT_KIT_NO_SPECIFIED_SUBSCRIBER_HAS_BEEN_REGESITERED,
};

/* Error code for OSACCOUNT_SERVICE */
constexpr ErrCode ACCOUNT_OSACCOUNT_SERVICE_ERR_OFFSET =
    ErrCodeOffset(SUBSYS_ACCOUNT, ACCOUNT_MODULE_OSACCOUNT_SERVICE);
enum {
    CREATE_OSACCOUNT_DB_FAILED = ACCOUNT_OSACCOUNT_SERVICE_ERR_OFFSET + 0x0001,
    SET_DATABASE_AUTHORITY_FAILED,
    ACCOUNT_TYPE_ERR,
    MAXINUM_NUMBER_EXCEEDED_ERR,
    ACCOUNT_VERIFIED_ERR,
    DATA_EMPTY_ERR,
    LOAD_DATABACE_FAILED,
    SERIALIZE_ERR,
    DESERIALIZE_ERR,
    PHOTO_DATA_OVERSIZE_ERR,
    ACCOUNT_NAME_OVERSIZE_ERR,
    BATAIN_UID_ERR,
    QUERY_DISTRIBUTE_DATA_FAILED,
    ERR_OS_ACCOUNT_SERVICE_INNER_SELECT_OSACCOUNT_BYID_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CREATE_OVERFLOW_OSACCOUNTMAX_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CANNOT_CREATE_ADMIN_ACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_OS_ACCOUNT_TYPE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_UPDATE_CONFIG_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CANNOT_FIND_OSACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CANNOT_ADMIN_OSACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_PHOTO_OUTFLOW_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_LOCAL_NAME_OUTFLOW_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_VISITOR_ACCOUNT_EXIST_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CREATE_ACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CANNOT_DELETE_ADMIN_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_CANNOT_DELE_OSACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_UPDATE_ACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_INNER_FIND_ACCOUNT_IN_ACTIVE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_FIND_AVAILABLE_ID_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_UPDATE_OSACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_CREATE_OSACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_SELECT_OS_ACCOUNT_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_SELECT_CONSTRAINTS_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_GET_CONSTRAINTS_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_GET_TYPE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_INSERT_FILE_EXISTS_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_INSERT_OS_ACCOUNT_INFO_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_INSERT_OS_ACCOUNT_LIST_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_GET_OS_ACCOUNT_LIST_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_DEL_OS_ACCOUNT_INFO_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_UPDATE_FILE_NOT_EXISTS_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_UPDATE_FILE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_MAX_CAN_CREATE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_SELECT_CAN_USE_ID_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_DELE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_FIND_DIR_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_FIND_FILE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_CREATE_DIR_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_CHANGE_DIR_MODE_ERROR,
    ERR_OS_ACCOUNT_SERVICE_FILE_CREATE_FILE_FAILED_ERROR,
    ERR_OS_ACCOUNT_SERVICE_CONTROL_GET_ACCOUNT_LIST_ERROR,
    ERR_OSACCOUNT_SERVICE_CREATE_EVENT_HANDLER,
    ERR_ACCOUNT_SERVICE_DATA_STORAGE_KEY_NOT_EXISTS_ERROR,
    ERR_ACCOUNT_SERVICE_DATA_STORAGE_KEY_EXISTED_ERROR,
};
}  // namespace OHOS

#endif /* BASE_ACCOUNT_INCLUDE_ACCOUNT_ERROR_NO_H */