// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "ProxySchema.h"

export module GraphQL.Proxy.ProxySchema;

export import GraphQL.Proxy.QueryObject;
export import GraphQL.Proxy.ResultsObject;

export namespace graphql::proxy {

using proxy::Operations;

using proxy::AddQueryDetails;
using proxy::AddResultsDetails;

using proxy::GetSchema;

} // namespace graphql::proxy
