// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TODAYSCHEMA_H
#define TODAYSCHEMA_H

#include "graphqlservice/internal/Schema.h"

// Check if the library version is compatible with schemagen 4.5.0
static_assert(graphql::internal::MajorVersion == 4, "regenerate with schemagen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 5, "regenerate with schemagen: minor version mismatch");

#include <array>
#include <memory>
#include <string>
#include <string_view>

namespace graphql {
namespace today {

enum class [[nodiscard]] TaskState
{
	Unassigned,
	New,
	Started,
	Complete
};

[[nodiscard]] constexpr auto getTaskStateNames() noexcept
{
	using namespace std::literals;

	return std::array<std::string_view, 4> {
		R"gql(Unassigned)gql"sv,
		R"gql(New)gql"sv,
		R"gql(Started)gql"sv,
		R"gql(Complete)gql"sv
	};
}

[[nodiscard]] constexpr auto getTaskStateValues() noexcept
{
	using namespace std::literals;

	return std::array<std::pair<std::string_view, TaskState>, 4> {
		std::make_pair(R"gql(New)gql"sv, TaskState::New),
		std::make_pair(R"gql(Started)gql"sv, TaskState::Started),
		std::make_pair(R"gql(Complete)gql"sv, TaskState::Complete),
		std::make_pair(R"gql(Unassigned)gql"sv, TaskState::Unassigned)
	};
}

struct [[nodiscard]] CompleteTaskInput
{
	explicit CompleteTaskInput() noexcept;
	explicit CompleteTaskInput(
		response::IdType idArg,
		std::optional<TaskState> testTaskStateArg,
		std::optional<bool> isCompleteArg,
		std::optional<std::string> clientMutationIdArg) noexcept;
	CompleteTaskInput(const CompleteTaskInput& other);
	CompleteTaskInput(CompleteTaskInput&& other) noexcept;
	~CompleteTaskInput();

	CompleteTaskInput& operator=(const CompleteTaskInput& other);
	CompleteTaskInput& operator=(CompleteTaskInput&& other) noexcept;

	response::IdType id {};
	std::optional<TaskState> testTaskState {};
	std::optional<bool> isComplete {};
	std::optional<std::string> clientMutationId {};
};

struct SecondNestedInput;

struct [[nodiscard]] ThirdNestedInput
{
	explicit ThirdNestedInput() noexcept;
	explicit ThirdNestedInput(
		response::IdType idArg,
		std::unique_ptr<SecondNestedInput> secondArg) noexcept;
	ThirdNestedInput(const ThirdNestedInput& other);
	ThirdNestedInput(ThirdNestedInput&& other) noexcept;
	~ThirdNestedInput();

	ThirdNestedInput& operator=(const ThirdNestedInput& other);
	ThirdNestedInput& operator=(ThirdNestedInput&& other) noexcept;

	response::IdType id {};
	std::unique_ptr<SecondNestedInput> second {};
};

struct [[nodiscard]] FourthNestedInput
{
	explicit FourthNestedInput() noexcept;
	explicit FourthNestedInput(
		response::IdType idArg) noexcept;
	FourthNestedInput(const FourthNestedInput& other);
	FourthNestedInput(FourthNestedInput&& other) noexcept;
	~FourthNestedInput();

	FourthNestedInput& operator=(const FourthNestedInput& other);
	FourthNestedInput& operator=(FourthNestedInput&& other) noexcept;

	response::IdType id {};
};

struct [[nodiscard]] IncludeNullableSelfInput
{
	explicit IncludeNullableSelfInput() noexcept;
	explicit IncludeNullableSelfInput(
		std::unique_ptr<IncludeNullableSelfInput> selfArg) noexcept;
	IncludeNullableSelfInput(const IncludeNullableSelfInput& other);
	IncludeNullableSelfInput(IncludeNullableSelfInput&& other) noexcept;
	~IncludeNullableSelfInput();

	IncludeNullableSelfInput& operator=(const IncludeNullableSelfInput& other);
	IncludeNullableSelfInput& operator=(IncludeNullableSelfInput&& other) noexcept;

	std::unique_ptr<IncludeNullableSelfInput> self {};
};

struct [[nodiscard]] IncludeNonNullableListSelfInput
{
	explicit IncludeNonNullableListSelfInput() noexcept;
	explicit IncludeNonNullableListSelfInput(
		std::vector<IncludeNonNullableListSelfInput> selvesArg) noexcept;
	IncludeNonNullableListSelfInput(const IncludeNonNullableListSelfInput& other);
	IncludeNonNullableListSelfInput(IncludeNonNullableListSelfInput&& other) noexcept;
	~IncludeNonNullableListSelfInput();

	IncludeNonNullableListSelfInput& operator=(const IncludeNonNullableListSelfInput& other);
	IncludeNonNullableListSelfInput& operator=(IncludeNonNullableListSelfInput&& other) noexcept;

	std::vector<IncludeNonNullableListSelfInput> selves {};
};

struct [[nodiscard]] StringOperationFilterInput
{
	explicit StringOperationFilterInput() noexcept;
	explicit StringOperationFilterInput(
		std::optional<std::vector<StringOperationFilterInput>> and_Arg,
		std::optional<std::vector<StringOperationFilterInput>> or_Arg,
		std::optional<std::string> equalArg,
		std::optional<std::string> notEqualArg,
		std::optional<std::string> containsArg,
		std::optional<std::string> notContainsArg,
		std::optional<std::vector<std::string>> inArg,
		std::optional<std::vector<std::string>> notInArg,
		std::optional<std::string> startsWithArg,
		std::optional<std::string> notStartsWithArg,
		std::optional<std::string> endsWithArg,
		std::optional<std::string> notEndsWithArg) noexcept;
	StringOperationFilterInput(const StringOperationFilterInput& other);
	StringOperationFilterInput(StringOperationFilterInput&& other) noexcept;
	~StringOperationFilterInput();

	StringOperationFilterInput& operator=(const StringOperationFilterInput& other);
	StringOperationFilterInput& operator=(StringOperationFilterInput&& other) noexcept;

	std::optional<std::vector<StringOperationFilterInput>> and_ {};
	std::optional<std::vector<StringOperationFilterInput>> or_ {};
	std::optional<std::string> equal {};
	std::optional<std::string> notEqual {};
	std::optional<std::string> contains {};
	std::optional<std::string> notContains {};
	std::optional<std::vector<std::string>> in {};
	std::optional<std::vector<std::string>> notIn {};
	std::optional<std::string> startsWith {};
	std::optional<std::string> notStartsWith {};
	std::optional<std::string> endsWith {};
	std::optional<std::string> notEndsWith {};
};

struct [[nodiscard]] SecondNestedInput
{
	explicit SecondNestedInput() noexcept;
	explicit SecondNestedInput(
		response::IdType idArg,
		ThirdNestedInput thirdArg) noexcept;
	SecondNestedInput(const SecondNestedInput& other);
	SecondNestedInput(SecondNestedInput&& other) noexcept;
	~SecondNestedInput();

	SecondNestedInput& operator=(const SecondNestedInput& other);
	SecondNestedInput& operator=(SecondNestedInput&& other) noexcept;

	response::IdType id {};
	ThirdNestedInput third {};
};

struct [[nodiscard]] ForwardDeclaredInput
{
	explicit ForwardDeclaredInput() noexcept;
	explicit ForwardDeclaredInput(
		std::unique_ptr<IncludeNullableSelfInput> nullableSelfArg,
		IncludeNonNullableListSelfInput listSelvesArg) noexcept;
	ForwardDeclaredInput(const ForwardDeclaredInput& other);
	ForwardDeclaredInput(ForwardDeclaredInput&& other) noexcept;
	~ForwardDeclaredInput();

	ForwardDeclaredInput& operator=(const ForwardDeclaredInput& other);
	ForwardDeclaredInput& operator=(ForwardDeclaredInput&& other) noexcept;

	std::unique_ptr<IncludeNullableSelfInput> nullableSelf {};
	IncludeNonNullableListSelfInput listSelves {};
};

struct [[nodiscard]] FirstNestedInput
{
	explicit FirstNestedInput() noexcept;
	explicit FirstNestedInput(
		response::IdType idArg,
		SecondNestedInput secondArg,
		ThirdNestedInput thirdArg) noexcept;
	FirstNestedInput(const FirstNestedInput& other);
	FirstNestedInput(FirstNestedInput&& other) noexcept;
	~FirstNestedInput();

	FirstNestedInput& operator=(const FirstNestedInput& other);
	FirstNestedInput& operator=(FirstNestedInput&& other) noexcept;

	response::IdType id {};
	SecondNestedInput second {};
	ThirdNestedInput third {};
};

namespace object {

class Node;

class UnionType;

class Query;
class PageInfo;
class AppointmentEdge;
class AppointmentConnection;
class TaskEdge;
class TaskConnection;
class FolderEdge;
class FolderConnection;
class CompleteTaskPayload;
class Mutation;
class Subscription;
class Appointment;
class Task;
class Folder;
class NestedType;
class Expensive;

} // namespace object

class [[nodiscard]] Operations final
	: public service::Request
{
public:
	explicit Operations(std::shared_ptr<object::Query> query, std::shared_ptr<object::Mutation> mutation, std::shared_ptr<object::Subscription> subscription);

	template <class TQuery, class TMutation, class TSubscription = service::SubscriptionPlaceholder>
	explicit Operations(std::shared_ptr<TQuery> query, std::shared_ptr<TMutation> mutation, std::shared_ptr<TSubscription> subscription = {})
		: Operations {
			std::make_shared<object::Query>(std::move(query)),
			std::make_shared<object::Mutation>(std::move(mutation)),
			subscription ? std::make_shared<object::Subscription>(std::move(subscription)) : std::shared_ptr<object::Subscription> {}
		}
	{
	}

private:
	std::shared_ptr<object::Query> _query;
	std::shared_ptr<object::Mutation> _mutation;
	std::shared_ptr<object::Subscription> _subscription;
};

void AddNodeDetails(const std::shared_ptr<schema::InterfaceType>& typeNode, const std::shared_ptr<schema::Schema>& schema);

void AddUnionTypeDetails(const std::shared_ptr<schema::UnionType>& typeUnionType, const std::shared_ptr<schema::Schema>& schema);

void AddQueryDetails(const std::shared_ptr<schema::ObjectType>& typeQuery, const std::shared_ptr<schema::Schema>& schema);
void AddPageInfoDetails(const std::shared_ptr<schema::ObjectType>& typePageInfo, const std::shared_ptr<schema::Schema>& schema);
void AddAppointmentEdgeDetails(const std::shared_ptr<schema::ObjectType>& typeAppointmentEdge, const std::shared_ptr<schema::Schema>& schema);
void AddAppointmentConnectionDetails(const std::shared_ptr<schema::ObjectType>& typeAppointmentConnection, const std::shared_ptr<schema::Schema>& schema);
void AddTaskEdgeDetails(const std::shared_ptr<schema::ObjectType>& typeTaskEdge, const std::shared_ptr<schema::Schema>& schema);
void AddTaskConnectionDetails(const std::shared_ptr<schema::ObjectType>& typeTaskConnection, const std::shared_ptr<schema::Schema>& schema);
void AddFolderEdgeDetails(const std::shared_ptr<schema::ObjectType>& typeFolderEdge, const std::shared_ptr<schema::Schema>& schema);
void AddFolderConnectionDetails(const std::shared_ptr<schema::ObjectType>& typeFolderConnection, const std::shared_ptr<schema::Schema>& schema);
void AddCompleteTaskPayloadDetails(const std::shared_ptr<schema::ObjectType>& typeCompleteTaskPayload, const std::shared_ptr<schema::Schema>& schema);
void AddMutationDetails(const std::shared_ptr<schema::ObjectType>& typeMutation, const std::shared_ptr<schema::Schema>& schema);
void AddSubscriptionDetails(const std::shared_ptr<schema::ObjectType>& typeSubscription, const std::shared_ptr<schema::Schema>& schema);
void AddAppointmentDetails(const std::shared_ptr<schema::ObjectType>& typeAppointment, const std::shared_ptr<schema::Schema>& schema);
void AddTaskDetails(const std::shared_ptr<schema::ObjectType>& typeTask, const std::shared_ptr<schema::Schema>& schema);
void AddFolderDetails(const std::shared_ptr<schema::ObjectType>& typeFolder, const std::shared_ptr<schema::Schema>& schema);
void AddNestedTypeDetails(const std::shared_ptr<schema::ObjectType>& typeNestedType, const std::shared_ptr<schema::Schema>& schema);
void AddExpensiveDetails(const std::shared_ptr<schema::ObjectType>& typeExpensive, const std::shared_ptr<schema::Schema>& schema);

std::shared_ptr<schema::Schema> GetSchema();

} // namespace today
} // namespace graphql

#endif // TODAYSCHEMA_H
