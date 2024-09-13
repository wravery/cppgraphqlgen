// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "MutateClient.h"

export module GraphQL.Mutate.MutateClient;

namespace included = graphql::client;

export namespace graphql::client {

namespace exported {

namespace mutate {

using TaskState = included::mutate::TaskState;

using CompleteTaskInput = included::mutate::CompleteTaskInput;

} // namespace mutate

namespace mutation::CompleteTaskMutation {

using Traits = included::mutation::CompleteTaskMutation::Traits;

} // namespace mutation::CompleteTaskMutation

} // namespace exported

using namespace exported;

} // namespace graphql::client
