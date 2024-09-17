// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "NestedInputClient.h"

export module GraphQL.NestedInput.NestedInputClient;

export namespace graphql::client {

namespace nestedinput {

using nestedinput::GetRequestText;
using nestedinput::GetRequestObject;

using nestedinput::InputA;
using nestedinput::InputB;
using nestedinput::InputABCD;
using nestedinput::InputBC;

} // namespace nestedinput

namespace query::testQuery {

using nestedinput::GetRequestText;
using nestedinput::GetRequestObject;
using testQuery::GetOperationName;

using nestedinput::InputA;
using nestedinput::InputB;
using nestedinput::InputABCD;
using nestedinput::InputBC;

using testQuery::Variables;
using testQuery::serializeVariables;

using testQuery::Response;
using testQuery::parseResponse;

using testQuery::Traits;

} // namespace query::testQuery

} // namespace graphql::client