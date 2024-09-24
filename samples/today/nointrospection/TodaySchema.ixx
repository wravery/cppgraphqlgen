// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "TodaySchema.h"

export module GraphQL.Today.TodaySchema;

export import GraphQL.Today.TodaySharedTypes;

export import GraphQL.Today.NodeObject;
export import GraphQL.Today.UnionTypeObject;
export import GraphQL.Today.QueryObject;
export import GraphQL.Today.PageInfoObject;
export import GraphQL.Today.AppointmentEdgeObject;
export import GraphQL.Today.AppointmentConnectionObject;
export import GraphQL.Today.TaskEdgeObject;
export import GraphQL.Today.TaskConnectionObject;
export import GraphQL.Today.FolderEdgeObject;
export import GraphQL.Today.FolderConnectionObject;
export import GraphQL.Today.CompleteTaskPayloadObject;
export import GraphQL.Today.MutationObject;
export import GraphQL.Today.SubscriptionObject;
export import GraphQL.Today.AppointmentObject;
export import GraphQL.Today.TaskObject;
export import GraphQL.Today.FolderObject;
export import GraphQL.Today.NestedTypeObject;
export import GraphQL.Today.ExpensiveObject;

export namespace graphql::today {

using today::Operations;

using today::AddNodeDetails;
using today::AddUnionTypeDetails;
using today::AddQueryDetails;
using today::AddPageInfoDetails;
using today::AddAppointmentEdgeDetails;
using today::AddAppointmentConnectionDetails;
using today::AddTaskEdgeDetails;
using today::AddTaskConnectionDetails;
using today::AddFolderEdgeDetails;
using today::AddFolderConnectionDetails;
using today::AddCompleteTaskPayloadDetails;
using today::AddMutationDetails;
using today::AddSubscriptionDetails;
using today::AddAppointmentDetails;
using today::AddTaskDetails;
using today::AddFolderDetails;
using today::AddNestedTypeDetails;
using today::AddExpensiveDetails;

using today::GetSchema;

} // namespace graphql::today
