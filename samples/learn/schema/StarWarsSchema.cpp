// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "QueryObject.h"
#include "MutationObject.h"

#include "graphqlservice/internal/Schema.h"

#include "graphqlservice/introspection/IntrospectionSchema.h"

#include <algorithm>
#include <array>
#include <functional>
#include <sstream>
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
service::AwaitableResolver Result<learn::Episode>::convert(service::AwaitableScalar<learn::Episode> result, ResolverParams params)
{
	return ModifiedResult<learn::Episode>::resolve(std::move(result), std::move(params),
		[](learn::Episode value, const ResolverParams&)
		{
			response::Value result(response::Type::EnumValue);

			result.set<std::string>(std::string { s_namesEpisode[static_cast<size_t>(value)] });

			return result;
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
		std::move(valueStars),
		std::move(valueCommentary)
	};
}

} // namespace service

namespace learn {

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

Operations::Operations(std::shared_ptr<object::Query> query, std::shared_ptr<object::Mutation> mutation)
	: service::Request({
		{ service::strQuery, query },
		{ service::strMutation, mutation }
	}, GetSchema())
	, _query(std::move(query))
	, _mutation(std::move(mutation))
{
}

void AddTypesToSchema(const std::shared_ptr<schema::Schema>& schema)
{
	auto typeEpisode = schema::EnumType::Make(R"gql(Episode)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Episode)gql"sv, typeEpisode);
	auto typeReviewInput = schema::InputObjectType::Make(R"gql(ReviewInput)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(ReviewInput)gql"sv, typeReviewInput);
	auto typeCharacter = schema::InterfaceType::Make(R"gql(Character)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Character)gql"sv, typeCharacter);
	auto typeHuman = schema::ObjectType::Make(R"gql(Human)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Human)gql"sv, typeHuman);
	auto typeDroid = schema::ObjectType::Make(R"gql(Droid)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Droid)gql"sv, typeDroid);
	auto typeQuery = schema::ObjectType::Make(R"gql(Query)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Query)gql"sv, typeQuery);
	auto typeReview = schema::ObjectType::Make(R"gql(Review)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Review)gql"sv, typeReview);
	auto typeMutation = schema::ObjectType::Make(R"gql(Mutation)gql"sv, R"md()md"sv);
	schema->AddType(R"gql(Mutation)gql"sv, typeMutation);

	typeEpisode->AddEnumValues({
		{ service::s_namesEpisode[static_cast<size_t>(learn::Episode::NEW_HOPE)], R"md()md"sv, std::nullopt },
		{ service::s_namesEpisode[static_cast<size_t>(learn::Episode::EMPIRE)], R"md()md"sv, std::nullopt },
		{ service::s_namesEpisode[static_cast<size_t>(learn::Episode::JEDI)], R"md()md"sv, std::nullopt }
	});

	typeReviewInput->AddInputValues({
		schema::InputValue::Make(R"gql(stars)gql"sv, R"md()md"sv, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(Int)gql"sv)), R"gql()gql"sv),
		schema::InputValue::Make(R"gql(commentary)gql"sv, R"md()md"sv, schema->LookupType(R"gql(String)gql"sv), R"gql()gql"sv)
	});

	AddCharacterDetails(typeCharacter, schema);

	AddHumanDetails(typeHuman, schema);
	AddDroidDetails(typeDroid, schema);
	AddQueryDetails(typeQuery, schema);
	AddReviewDetails(typeReview, schema);
	AddMutationDetails(typeMutation, schema);

	schema->AddQueryType(typeQuery);
	schema->AddMutationType(typeMutation);
}

std::shared_ptr<schema::Schema> GetSchema()
{
	static std::weak_ptr<schema::Schema> s_wpSchema;
	auto schema = s_wpSchema.lock();

	if (!schema)
	{
		schema = std::make_shared<schema::Schema>(false, R"md()md"sv);
		introspection::AddTypesToSchema(schema);
		AddTypesToSchema(schema);
		s_wpSchema = schema;
	}

	return schema;
}

} // namespace learn
} // namespace graphql
