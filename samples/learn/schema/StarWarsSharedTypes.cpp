// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "graphqlservice/GraphQLService.h"

#include "StarWarsSharedTypes.h"

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

static const auto s_namesEpisode = learn::getEpisodeNames();
static const auto s_valuesEpisode = learn::getEpisodeValues();

template <>
learn::Episode Argument<learn::Episode>::convert(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid Episode value)ex" } };
	}

	const auto result = internal::sorted_map_lookup<internal::shorter_or_less>(
		s_valuesEpisode,
		std::string_view { value.get<std::string>() });

	if (!result)
	{
		throw service::schema_exception { { R"ex(not a valid Episode value)ex" } };
	}

	return *result;
}

template <>
service::AwaitableResolver Result<learn::Episode>::convert(service::AwaitableScalar<learn::Episode> result, ResolverParams&& params)
{
	return ModifiedResult<learn::Episode>::resolve(std::move(result), std::move(params),
		[](learn::Episode value, const ResolverParams& params)
		{
			params.resolverVisitor->add_enum(std::string { s_namesEpisode[static_cast<std::size_t>(value)] });
		});
}

template <>
void Result<learn::Episode>::validateScalar(const response::Value& value)
{
	if (!value.maybe_enum())
	{
		throw service::schema_exception { { R"ex(not a valid Episode value)ex" } };
	}

	const auto [itr, itrEnd] = internal::sorted_map_equal_range<internal::shorter_or_less>(
		s_valuesEpisode.begin(),
		s_valuesEpisode.end(),
		std::string_view { value.get<std::string>() });

	if (itr == itrEnd)
	{
		throw service::schema_exception { { R"ex(not a valid Episode value)ex" } };
	}
}

template <>
learn::ReviewInput Argument<learn::ReviewInput>::convert(const response::Value& value)
{
	auto valueStars = service::ModifiedArgument<int>::require("stars", value);
	auto valueCommentary = service::ModifiedArgument<std::string>::require<service::TypeModifier::Nullable>("commentary", value);

	return learn::ReviewInput {
		valueStars,
		std::move(valueCommentary)
	};
}

} // namespace service

namespace learn {

ReviewInput::ReviewInput() noexcept
	: stars {}
	, commentary {}
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ReviewInput::ReviewInput(
		int starsArg,
		std::optional<std::string> commentaryArg) noexcept
	: stars { std::move(starsArg) }
	, commentary { std::move(commentaryArg) }
{
}

ReviewInput::ReviewInput(const ReviewInput& other)
	: stars { service::ModifiedArgument<int>::duplicate(other.stars) }
	, commentary { service::ModifiedArgument<std::string>::duplicate<service::TypeModifier::Nullable>(other.commentary) }
{
}

ReviewInput::ReviewInput(ReviewInput&& other) noexcept
	: stars { std::move(other.stars) }
	, commentary { std::move(other.commentary) }
{
}

ReviewInput::~ReviewInput()
{
	// Explicit definition to prevent ODR violations when LTO is enabled.
}

ReviewInput& ReviewInput::operator=(const ReviewInput& other)
{
	ReviewInput value { other };

	std::swap(*this, value);

	return *this;
}

ReviewInput& ReviewInput::operator=(ReviewInput&& other) noexcept
{
	stars = std::move(other.stars);
	commentary = std::move(other.commentary);

	return *this;
}

} // namespace learn
} // namespace graphql
