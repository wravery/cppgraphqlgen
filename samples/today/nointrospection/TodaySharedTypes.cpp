// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "graphqlservice/GraphQLService.h"

#include "TodaySharedTypes.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

using namespace std::literals;

namespace graphql {
namespace service {

static const auto s_namesTaskState = today::getTaskStateNames();
static const auto s_valuesTaskState = today::getTaskStateValues();

template <>
today::TaskState Argument<today::TaskState>::convert(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid TaskState value)ex" } };
	}

	const auto result = internal::sorted_map_lookup<internal::shorter_or_less>(
		s_valuesTaskState,
		std::string_view { value.get<std::string>() });

	if (!result)
	{
		throw service::schema_exception { { R"ex(not a valid TaskState value)ex" } };
	}

	return *result;
}

template <>
service::AwaitableResolver Result<today::TaskState>::convert(service::AwaitableScalar<today::TaskState> result, ResolverParams&& params)
{
	return ModifiedResult<today::TaskState>::resolve(std::move(result), std::move(params),
		[](today::TaskState value, const ResolverParams&)
		{
			response::Value resolvedResult(response::Type::EnumValue);

			resolvedResult.set<std::string>(std::string { s_namesTaskState[static_cast<std::size_t>(value)] });

			return resolvedResult;
		});
}

template <>
void Result<today::TaskState>::validateScalar(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid TaskState value)ex" } };
	}

	const auto [itr, itrEnd] = internal::sorted_map_equal_range<internal::shorter_or_less>(
		s_valuesTaskState.begin(),
		s_valuesTaskState.end(),
		std::string_view { value.get<std::string>() });

	if (itr == itrEnd)
	{
		throw service::schema_exception { { R"ex(not a valid TaskState value)ex" } };
	}
}

template <>
today::CompleteTaskInput Argument<today::CompleteTaskInput>::convert(const response::Value& value)
{
	const auto defaultValue = []()
	{
		response::Value values(response::Type::Map);
		response::Value entry;

		entry = response::Value(true);
		values.emplace_back("isComplete", std::move(entry));

		return values;
	}();

	auto valueId = service::ModifiedArgument<response::IdType>::require("id", value);
	auto valueTestTaskState = service::ModifiedArgument<today::TaskState>::require<service::TypeModifier::Nullable>("testTaskState", value);
	auto pairIsComplete = service::ModifiedArgument<bool>::find<service::TypeModifier::Nullable>("isComplete", value);
	auto valueIsComplete = (pairIsComplete.second
		? std::move(pairIsComplete.first)
		: service::ModifiedArgument<bool>::require<service::TypeModifier::Nullable>("isComplete", defaultValue));
	auto valueClientMutationId = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("clientMutationId", value);

	return today::CompleteTaskInput {
		std::move(valueId),
		valueTestTaskState,
		std::move(valueIsComplete),
		std::move(valueClientMutationId)
	};
}

template <>
today::ThirdNestedInput Argument<today::ThirdNestedInput>::convert(const response::Value& value)
{
	auto valueId = service::ModifiedArgument<response::IdType>::require("id", value);
	auto valueSecond = service::ModifiedArgument<today::SecondNestedInput>::require<service::TypeModifier::Nullable>("second", value);

	return today::ThirdNestedInput {
		std::move(valueId),
		std::move(valueSecond)
	};
}

template <>
today::FourthNestedInput Argument<today::FourthNestedInput>::convert(const response::Value& value)
{
	auto valueId = service::ModifiedArgument<response::IdType>::require("id", value);

	return today::FourthNestedInput {
		std::move(valueId)
	};
}

template <>
today::IncludeNullableSelfInput Argument<today::IncludeNullableSelfInput>::convert(const response::Value& value)
{
	auto valueSelf = service::ModifiedArgument<today::IncludeNullableSelfInput>::require<service::TypeModifier::Nullable>("self", value);

	return today::IncludeNullableSelfInput {
		std::move(valueSelf)
	};
}

template <>
today::IncludeNonNullableListSelfInput Argument<today::IncludeNonNullableListSelfInput>::convert(const response::Value& value)
{
	auto valueSelves = service::ModifiedArgument<today::IncludeNonNullableListSelfInput>::require<service::TypeModifier::List>("selves", value);

	return today::IncludeNonNullableListSelfInput {
		std::move(valueSelves)
	};
}

template <>
today::StringOperationFilterInput Argument<today::StringOperationFilterInput>::convert(const response::Value& value)
{
	auto valueAnd_ = service::ModifiedArgument<today::StringOperationFilterInput>::require<service::TypeModifier::Nullable, service::TypeModifier::List>("and", value);
	auto valueOr_ = service::ModifiedArgument<today::StringOperationFilterInput>::require<service::TypeModifier::Nullable, service::TypeModifier::List>("or", value);
	auto valueEqual = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("equal", value);
	auto valueNotEqual = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("notEqual", value);
	auto valueContains = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("contains", value);
	auto valueNotContains = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("notContains", value);
	auto valueIn = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable, service::TypeModifier::List>("in", value);
	auto valueNotIn = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable, service::TypeModifier::List>("notIn", value);
	auto valueStartsWith = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("startsWith", value);
	auto valueNotStartsWith = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("notStartsWith", value);
	auto valueEndsWith = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("endsWith", value);
	auto valueNotEndsWith = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("notEndsWith", value);

	return today::StringOperationFilterInput {
		std::move(valueAnd_),
		std::move(valueOr_),
		std::move(valueEqual),
		std::move(valueNotEqual),
		std::move(valueContains),
		std::move(valueNotContains),
		std::move(valueIn),
		std::move(valueNotIn),
		std::move(valueStartsWith),
		std::move(valueNotStartsWith),
		std::move(valueEndsWith),
		std::move(valueNotEndsWith)
	};
}

template <>
today::SecondNestedInput Argument<today::SecondNestedInput>::convert(const response::Value& value)
{
	auto valueId = service::ModifiedArgument<response::IdType>::require("id", value);
	auto valueThird = service::ModifiedArgument<today::ThirdNestedInput>::require("third", value);

	return today::SecondNestedInput {
		std::move(valueId),
		std::move(valueThird)
	};
}

template <>
today::ForwardDeclaredInput Argument<today::ForwardDeclaredInput>::convert(const response::Value& value)
{
	auto valueNullableSelf = service::ModifiedArgument<today::IncludeNullableSelfInput>::require<service::TypeModifier::Nullable>("nullableSelf", value);
	auto valueListSelves = service::ModifiedArgument<today::IncludeNonNullableListSelfInput>::require("listSelves", value);

	return today::ForwardDeclaredInput {
		std::move(valueNullableSelf),
		std::move(valueListSelves)
	};
}

template <>
today::FirstNestedInput Argument<today::FirstNestedInput>::convert(const response::Value& value)
{
	auto valueId = service::ModifiedArgument<response::IdType>::require("id", value);
	auto valueSecond = service::ModifiedArgument<today::SecondNestedInput>::require("second", value);
	auto valueThird = service::ModifiedArgument<today::ThirdNestedInput>::require("third", value);

	return today::FirstNestedInput {
		std::move(valueId),
		std::move(valueSecond),
		std::move(valueThird)
	};
}

} // namespace service

namespace today {

CompleteTaskInput::CompleteTaskInput() noexcept
	: id {}
	, testTaskState {}
	, isComplete {}
	, clientMutationId {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

CompleteTaskInput::CompleteTaskInput(
		response::IdType idArg,
		std::optional<TaskState> testTaskStateArg,
		std::optional<bool> isCompleteArg,
		std::optional<std::string> clientMutationIdArg) noexcept
	: id { std::move(idArg) }
	, testTaskState { std::move(testTaskStateArg) }
	, isComplete { std::move(isCompleteArg) }
	, clientMutationId { std::move(clientMutationIdArg) }
{
}

CompleteTaskInput::CompleteTaskInput(const CompleteTaskInput& other)
	: id { service::ModifiedArgument<response::IdType>::duplicate(other.id) }
	, testTaskState { service::ModifiedArgument<TaskState>::duplicate<service::TypeModifier::Nullable>(other.testTaskState) }
	, isComplete { service::ModifiedArgument<bool>::duplicate<service::TypeModifier::Nullable>(other.isComplete) }
	, clientMutationId { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.clientMutationId) }
{
}

CompleteTaskInput::CompleteTaskInput(CompleteTaskInput&& other) noexcept
	: id { std::move(other.id) }
	, testTaskState { std::move(other.testTaskState) }
	, isComplete { std::move(other.isComplete) }
	, clientMutationId { std::move(other.clientMutationId) }
{
}

CompleteTaskInput::~CompleteTaskInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

CompleteTaskInput& CompleteTaskInput::operator=(const CompleteTaskInput& other)
{
	CompleteTaskInput value { other };

	std::swap(*this, value);

	return *this;
}

CompleteTaskInput& CompleteTaskInput::operator=(CompleteTaskInput&& other) noexcept
{
	id = std::move(other.id);
	testTaskState = std::move(other.testTaskState);
	isComplete = std::move(other.isComplete);
	clientMutationId = std::move(other.clientMutationId);

	return *this;
}


ThirdNestedInput::ThirdNestedInput() noexcept
	: id {}
	, second {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ThirdNestedInput::ThirdNestedInput(
		response::IdType idArg,
		std::unique_ptr<SecondNestedInput> secondArg) noexcept
	: id { std::move(idArg) }
	, second { std::move(secondArg) }
{
}

ThirdNestedInput::ThirdNestedInput(const ThirdNestedInput& other)
	: id { service::ModifiedArgument<response::IdType>::duplicate(other.id) }
	, second { service::ModifiedArgument<SecondNestedInput>::duplicate<service::TypeModifier::Nullable>(other.second) }
{
}

ThirdNestedInput::ThirdNestedInput(ThirdNestedInput&& other) noexcept
	: id { std::move(other.id) }
	, second { std::move(other.second) }
{
}

ThirdNestedInput::~ThirdNestedInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ThirdNestedInput& ThirdNestedInput::operator=(const ThirdNestedInput& other)
{
	ThirdNestedInput value { other };

	std::swap(*this, value);

	return *this;
}

ThirdNestedInput& ThirdNestedInput::operator=(ThirdNestedInput&& other) noexcept
{
	id = std::move(other.id);
	second = std::move(other.second);

	return *this;
}


FourthNestedInput::FourthNestedInput() noexcept
	: id {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

FourthNestedInput::FourthNestedInput(
		response::IdType idArg) noexcept
	: id { std::move(idArg) }
{
}

FourthNestedInput::FourthNestedInput(const FourthNestedInput& other)
	: id { service::ModifiedArgument<response::IdType>::duplicate(other.id) }
{
}

FourthNestedInput::FourthNestedInput(FourthNestedInput&& other) noexcept
	: id { std::move(other.id) }
{
}

FourthNestedInput::~FourthNestedInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

FourthNestedInput& FourthNestedInput::operator=(const FourthNestedInput& other)
{
	FourthNestedInput value { other };

	std::swap(*this, value);

	return *this;
}

FourthNestedInput& FourthNestedInput::operator=(FourthNestedInput&& other) noexcept
{
	id = std::move(other.id);

	return *this;
}


IncludeNullableSelfInput::IncludeNullableSelfInput() noexcept
	: self {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

IncludeNullableSelfInput::IncludeNullableSelfInput(
		std::unique_ptr<IncludeNullableSelfInput> selfArg) noexcept
	: self { std::move(selfArg) }
{
}

IncludeNullableSelfInput::IncludeNullableSelfInput(const IncludeNullableSelfInput& other)
	: self { service::ModifiedArgument<IncludeNullableSelfInput>::duplicate<service::TypeModifier::Nullable>(other.self) }
{
}

IncludeNullableSelfInput::IncludeNullableSelfInput(IncludeNullableSelfInput&& other) noexcept
	: self { std::move(other.self) }
{
}

IncludeNullableSelfInput::~IncludeNullableSelfInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

IncludeNullableSelfInput& IncludeNullableSelfInput::operator=(const IncludeNullableSelfInput& other)
{
	IncludeNullableSelfInput value { other };

	std::swap(*this, value);

	return *this;
}

IncludeNullableSelfInput& IncludeNullableSelfInput::operator=(IncludeNullableSelfInput&& other) noexcept
{
	self = std::move(other.self);

	return *this;
}


IncludeNonNullableListSelfInput::IncludeNonNullableListSelfInput() noexcept
	: selves {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

IncludeNonNullableListSelfInput::IncludeNonNullableListSelfInput(
		std::vector<IncludeNonNullableListSelfInput> selvesArg) noexcept
	: selves { std::move(selvesArg) }
{
}

IncludeNonNullableListSelfInput::IncludeNonNullableListSelfInput(const IncludeNonNullableListSelfInput& other)
	: selves { service::ModifiedArgument<IncludeNonNullableListSelfInput>::duplicate<service::TypeModifier::List>(other.selves) }
{
}

IncludeNonNullableListSelfInput::IncludeNonNullableListSelfInput(IncludeNonNullableListSelfInput&& other) noexcept
	: selves { std::move(other.selves) }
{
}

IncludeNonNullableListSelfInput::~IncludeNonNullableListSelfInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

IncludeNonNullableListSelfInput& IncludeNonNullableListSelfInput::operator=(const IncludeNonNullableListSelfInput& other)
{
	IncludeNonNullableListSelfInput value { other };

	std::swap(*this, value);

	return *this;
}

IncludeNonNullableListSelfInput& IncludeNonNullableListSelfInput::operator=(IncludeNonNullableListSelfInput&& other) noexcept
{
	selves = std::move(other.selves);

	return *this;
}


StringOperationFilterInput::StringOperationFilterInput() noexcept
	: and_ {}
	, or_ {}
	, equal {}
	, notEqual {}
	, contains {}
	, notContains {}
	, in {}
	, notIn {}
	, startsWith {}
	, notStartsWith {}
	, endsWith {}
	, notEndsWith {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

StringOperationFilterInput::StringOperationFilterInput(
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
		std::optional<std::string> notEndsWithArg) noexcept
	: and_ { std::move(and_Arg) }
	, or_ { std::move(or_Arg) }
	, equal { std::move(equalArg) }
	, notEqual { std::move(notEqualArg) }
	, contains { std::move(containsArg) }
	, notContains { std::move(notContainsArg) }
	, in { std::move(inArg) }
	, notIn { std::move(notInArg) }
	, startsWith { std::move(startsWithArg) }
	, notStartsWith { std::move(notStartsWithArg) }
	, endsWith { std::move(endsWithArg) }
	, notEndsWith { std::move(notEndsWithArg) }
{
}

StringOperationFilterInput::StringOperationFilterInput(const StringOperationFilterInput& other)
	: and_ { service::ModifiedArgument<StringOperationFilterInput>::duplicate<service::TypeModifier::Nullable, service::TypeModifier::List>(other.and_) }
	, or_ { service::ModifiedArgument<StringOperationFilterInput>::duplicate<service::TypeModifier::Nullable, service::TypeModifier::List>(other.or_) }
	, equal { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.equal) }
	, notEqual { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.notEqual) }
	, contains { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.contains) }
	, notContains { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.notContains) }
	, in { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable, service::TypeModifier::List>(other.in) }
	, notIn { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable, service::TypeModifier::List>(other.notIn) }
	, startsWith { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.startsWith) }
	, notStartsWith { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.notStartsWith) }
	, endsWith { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.endsWith) }
	, notEndsWith { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.notEndsWith) }
{
}

StringOperationFilterInput::StringOperationFilterInput(StringOperationFilterInput&& other) noexcept
	: and_ { std::move(other.and_) }
	, or_ { std::move(other.or_) }
	, equal { std::move(other.equal) }
	, notEqual { std::move(other.notEqual) }
	, contains { std::move(other.contains) }
	, notContains { std::move(other.notContains) }
	, in { std::move(other.in) }
	, notIn { std::move(other.notIn) }
	, startsWith { std::move(other.startsWith) }
	, notStartsWith { std::move(other.notStartsWith) }
	, endsWith { std::move(other.endsWith) }
	, notEndsWith { std::move(other.notEndsWith) }
{
}

StringOperationFilterInput::~StringOperationFilterInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

StringOperationFilterInput& StringOperationFilterInput::operator=(const StringOperationFilterInput& other)
{
	StringOperationFilterInput value { other };

	std::swap(*this, value);

	return *this;
}

StringOperationFilterInput& StringOperationFilterInput::operator=(StringOperationFilterInput&& other) noexcept
{
	and_ = std::move(other.and_);
	or_ = std::move(other.or_);
	equal = std::move(other.equal);
	notEqual = std::move(other.notEqual);
	contains = std::move(other.contains);
	notContains = std::move(other.notContains);
	in = std::move(other.in);
	notIn = std::move(other.notIn);
	startsWith = std::move(other.startsWith);
	notStartsWith = std::move(other.notStartsWith);
	endsWith = std::move(other.endsWith);
	notEndsWith = std::move(other.notEndsWith);

	return *this;
}


SecondNestedInput::SecondNestedInput() noexcept
	: id {}
	, third {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

SecondNestedInput::SecondNestedInput(
		response::IdType idArg,
		ThirdNestedInput thirdArg) noexcept
	: id { std::move(idArg) }
	, third { std::move(thirdArg) }
{
}

SecondNestedInput::SecondNestedInput(const SecondNestedInput& other)
	: id { service::ModifiedArgument<response::IdType>::duplicate(other.id) }
	, third { service::ModifiedArgument<ThirdNestedInput>::duplicate(other.third) }
{
}

SecondNestedInput::SecondNestedInput(SecondNestedInput&& other) noexcept
	: id { std::move(other.id) }
	, third { std::move(other.third) }
{
}

SecondNestedInput::~SecondNestedInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

SecondNestedInput& SecondNestedInput::operator=(const SecondNestedInput& other)
{
	SecondNestedInput value { other };

	std::swap(*this, value);

	return *this;
}

SecondNestedInput& SecondNestedInput::operator=(SecondNestedInput&& other) noexcept
{
	id = std::move(other.id);
	third = std::move(other.third);

	return *this;
}


ForwardDeclaredInput::ForwardDeclaredInput() noexcept
	: nullableSelf {}
	, listSelves {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ForwardDeclaredInput::ForwardDeclaredInput(
		std::unique_ptr<IncludeNullableSelfInput> nullableSelfArg,
		IncludeNonNullableListSelfInput listSelvesArg) noexcept
	: nullableSelf { std::move(nullableSelfArg) }
	, listSelves { std::move(listSelvesArg) }
{
}

ForwardDeclaredInput::ForwardDeclaredInput(const ForwardDeclaredInput& other)
	: nullableSelf { service::ModifiedArgument<IncludeNullableSelfInput>::duplicate<service::TypeModifier::Nullable>(other.nullableSelf) }
	, listSelves { service::ModifiedArgument<IncludeNonNullableListSelfInput>::duplicate(other.listSelves) }
{
}

ForwardDeclaredInput::ForwardDeclaredInput(ForwardDeclaredInput&& other) noexcept
	: nullableSelf { std::move(other.nullableSelf) }
	, listSelves { std::move(other.listSelves) }
{
}

ForwardDeclaredInput::~ForwardDeclaredInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ForwardDeclaredInput& ForwardDeclaredInput::operator=(const ForwardDeclaredInput& other)
{
	ForwardDeclaredInput value { other };

	std::swap(*this, value);

	return *this;
}

ForwardDeclaredInput& ForwardDeclaredInput::operator=(ForwardDeclaredInput&& other) noexcept
{
	nullableSelf = std::move(other.nullableSelf);
	listSelves = std::move(other.listSelves);

	return *this;
}


FirstNestedInput::FirstNestedInput() noexcept
	: id {}
	, second {}
	, third {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

FirstNestedInput::FirstNestedInput(
		response::IdType idArg,
		SecondNestedInput secondArg,
		ThirdNestedInput thirdArg) noexcept
	: id { std::move(idArg) }
	, second { std::move(secondArg) }
	, third { std::move(thirdArg) }
{
}

FirstNestedInput::FirstNestedInput(const FirstNestedInput& other)
	: id { service::ModifiedArgument<response::IdType>::duplicate(other.id) }
	, second { service::ModifiedArgument<SecondNestedInput>::duplicate(other.second) }
	, third { service::ModifiedArgument<ThirdNestedInput>::duplicate(other.third) }
{
}

FirstNestedInput::FirstNestedInput(FirstNestedInput&& other) noexcept
	: id { std::move(other.id) }
	, second { std::move(other.second) }
	, third { std::move(other.third) }
{
}

FirstNestedInput::~FirstNestedInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

FirstNestedInput& FirstNestedInput::operator=(const FirstNestedInput& other)
{
	FirstNestedInput value { other };

	std::swap(*this, value);

	return *this;
}

FirstNestedInput& FirstNestedInput::operator=(FirstNestedInput&& other) noexcept
{
	id = std::move(other.id);
	second = std::move(other.second);
	third = std::move(other.third);

	return *this;
}

} // namespace today
} // namespace graphql