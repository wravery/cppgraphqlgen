// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "graphqlservice/GraphQLService.h"

#include "ValidationSharedTypes.h"

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

static const auto s_namesDogCommand = validation::getDogCommandNames();
static const auto s_valuesDogCommand = validation::getDogCommandValues();

template <>
validation::DogCommand Argument<validation::DogCommand>::convert(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid DogCommand value)ex" } };
	}

	const auto result = internal::sorted_map_lookup<internal::shorter_or_less>(
		s_valuesDogCommand,
		std::string_view { value.get<std::string>() });

	if (!result)
	{
		throw service::schema_exception { { R"ex(not a valid DogCommand value)ex" } };
	}

	return *result;
}

template <>
service::AwaitableResolver Result<validation::DogCommand>::convert(service::AwaitableScalar<validation::DogCommand> result, ResolverParams&& params)
{
	return ModifiedResult<validation::DogCommand>::resolve(std::move(result), std::move(params),
		[](validation::DogCommand value, const ResolverParams&)
		{
			response::Value resolvedResult(response::Type::EnumValue);

			resolvedResult.set<std::string>(std::string { s_namesDogCommand[static_cast<std::size_t>(value)] });

			return resolvedResult;
		});
}

template <>
void Result<validation::DogCommand>::validateScalar(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid DogCommand value)ex" } };
	}

	const auto [itr, itrEnd] = internal::sorted_map_equal_range<internal::shorter_or_less>(
		s_valuesDogCommand.begin(),
		s_valuesDogCommand.end(),
		std::string_view { value.get<std::string>() });

	if (itr == itrEnd)
	{
		throw service::schema_exception { { R"ex(not a valid DogCommand value)ex" } };
	}
}

static const auto s_namesCatCommand = validation::getCatCommandNames();
static const auto s_valuesCatCommand = validation::getCatCommandValues();

template <>
validation::CatCommand Argument<validation::CatCommand>::convert(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid CatCommand value)ex" } };
	}

	const auto result = internal::sorted_map_lookup<internal::shorter_or_less>(
		s_valuesCatCommand,
		std::string_view { value.get<std::string>() });

	if (!result)
	{
		throw service::schema_exception { { R"ex(not a valid CatCommand value)ex" } };
	}

	return *result;
}

template <>
service::AwaitableResolver Result<validation::CatCommand>::convert(service::AwaitableScalar<validation::CatCommand> result, ResolverParams&& params)
{
	return ModifiedResult<validation::CatCommand>::resolve(std::move(result), std::move(params),
		[](validation::CatCommand value, const ResolverParams&)
		{
			response::Value resolvedResult(response::Type::EnumValue);

			resolvedResult.set<std::string>(std::string { s_namesCatCommand[static_cast<std::size_t>(value)] });

			return resolvedResult;
		});
}

template <>
void Result<validation::CatCommand>::validateScalar(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid CatCommand value)ex" } };
	}

	const auto [itr, itrEnd] = internal::sorted_map_equal_range<internal::shorter_or_less>(
		s_valuesCatCommand.begin(),
		s_valuesCatCommand.end(),
		std::string_view { value.get<std::string>() });

	if (itr == itrEnd)
	{
		throw service::schema_exception { { R"ex(not a valid CatCommand value)ex" } };
	}
}

template <>
validation::ComplexInput Argument<validation::ComplexInput>::convert(const response::Value& value)
{
	auto valueName = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("name", value);
	auto valueOwner = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("owner", value);

	return validation::ComplexInput {
		std::move(valueName),
		std::move(valueOwner)
	};
}

} // namespace service

namespace validation {

ComplexInput::ComplexInput() noexcept
	: name {}
	, owner {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ComplexInput::ComplexInput(
		std::optional<std::string> nameArg,
		std::optional<std::string> ownerArg) noexcept
	: name { std::move(nameArg) }
	, owner { std::move(ownerArg) }
{
}

ComplexInput::ComplexInput(const ComplexInput& other)
	: name { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.name) }
	, owner { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.owner) }
{
}

ComplexInput::ComplexInput(ComplexInput&& other) noexcept
	: name { std::move(other.name) }
	, owner { std::move(other.owner) }
{
}

ComplexInput::~ComplexInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ComplexInput& ComplexInput::operator=(const ComplexInput& other)
{
	ComplexInput value { other };

	std::swap(*this, value);

	return *this;
}

ComplexInput& ComplexInput::operator=(ComplexInput&& other) noexcept
{
	name = std::move(other.name);
	owner = std::move(other.owner);

	return *this;
}

} // namespace validation
} // namespace graphql