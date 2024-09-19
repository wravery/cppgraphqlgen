// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "ProxyClient.h"

#include "graphqlservice/internal/SortedMap.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string_view>
#include <utility>

using namespace std::literals;

namespace graphql {
namespace proxy {
namespace client {

const std::string& GetRequestText() noexcept
{
	static const auto s_request = R"gql(
		# Copyright (c) Microsoft Corporation. All rights reserved.
		# Licensed under the MIT License.
		
		query relayQuery($input: QueryInput!) {
		  relay(input: $input) {
		    data
		    errors
		  }
		}
	)gql"s;

	return s_request;
}

const peg::ast& GetRequestObject() noexcept
{
	static const auto s_request = []() noexcept {
		auto ast = peg::parseString(GetRequestText());

		// This has already been validated against the schema by clientgen.
		ast.validated = true;

		return ast;
	}();

	return s_request;
}

} // namespace client
} // namespace proxy

namespace client {

using namespace proxy;

template <>
response::Value Variable<OperationType>::serialize(OperationType&& value)
{
	static const std::array<std::string_view, 3> s_names = {
		R"gql(QUERY)gql"sv,
		R"gql(MUTATION)gql"sv,
		R"gql(SUBSCRIPTION)gql"sv
	};

	response::Value result { response::Type::EnumValue };

	result.set<std::string>(std::string { s_names[static_cast<std::size_t>(value)] });

	return result;
}

template <>
response::Value Variable<QueryInput>::serialize(QueryInput&& inputValue)
{
	response::Value result { response::Type::Map };

	result.emplace_back(R"js(type)js"s, ModifiedVariable<OperationType>::serialize(std::move(inputValue.type)));
	result.emplace_back(R"js(query)js"s, ModifiedVariable<std::string>::serialize(std::move(inputValue.query)));
	result.emplace_back(R"js(operationName)js"s, ModifiedVariable<std::string>::serialize<TypeModifier::Nullable>(std::move(inputValue.operationName)));
	result.emplace_back(R"js(variables)js"s, ModifiedVariable<std::string>::serialize<TypeModifier::Nullable>(std::move(inputValue.variables)));

	return result;
}

template <>
OperationType Response<OperationType>::parse(response::Value&& value)
{
	if (!value.maybe_enum())
	{
		throw std::logic_error { R"ex(not a valid OperationType value)ex" };
	}

	static const std::array<std::pair<std::string_view, OperationType>, 3> s_values = {
		std::make_pair(R"gql(QUERY)gql"sv, OperationType::QUERY),
		std::make_pair(R"gql(MUTATION)gql"sv, OperationType::MUTATION),
		std::make_pair(R"gql(SUBSCRIPTION)gql"sv, OperationType::SUBSCRIPTION)
	};

	const auto result = internal::sorted_map_lookup<internal::shorter_or_less>(
		s_values,
		std::string_view { value.get<std::string>() });

	if (!result)
	{
		throw std::logic_error { R"ex(not a valid OperationType value)ex" };
	}

	return *result;
}

template <>
graphql::proxy::client::query::relayQuery::Response::relay_QueryResults Response<graphql::proxy::client::query::relayQuery::Response::relay_QueryResults>::parse(response::Value&& response)
{
	graphql::proxy::client::query::relayQuery::Response::relay_QueryResults result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(data)js"sv)
			{
				result.data = ModifiedResponse<std::string>::parse<TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
			if (member.first == R"js(errors)js"sv)
			{
				result.errors = ModifiedResponse<std::string>::parse<TypeModifier::Nullable, TypeModifier::List, TypeModifier::Nullable>(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

} // namespace client

namespace proxy::client::query::relayQuery {

const std::string& GetOperationName() noexcept
{
	static const auto s_name = R"gql(relayQuery)gql"s;

	return s_name;
}

response::Value serializeVariables(Variables&& variables)
{
	using namespace graphql::client;

	response::Value result { response::Type::Map };

	result.emplace_back(R"js(input)js"s, ModifiedVariable<QueryInput>::serialize(std::move(variables.input)));

	return result;
}

Response parseResponse(response::Value&& response)
{
	using namespace graphql::client;

	Response result;

	if (response.type() == response::Type::Map)
	{
		auto members = response.release<response::MapType>();

		for (auto& member : members)
		{
			if (member.first == R"js(relay)js"sv)
			{
				result.relay = ModifiedResponse<query::relayQuery::Response::relay_QueryResults>::parse(std::move(member.second));
				continue;
			}
		}
	}

	return result;
}

[[nodiscard("unnecessary call")]] const std::string& Traits::GetRequestText() noexcept
{
	return client::GetRequestText();
}

[[nodiscard("unnecessary call")]] const peg::ast& Traits::GetRequestObject() noexcept
{
	return client::GetRequestObject();
}

[[nodiscard("unnecessary call")]] const std::string& Traits::GetOperationName() noexcept
{
	return relayQuery::GetOperationName();
}

[[nodiscard("unnecessary conversion")]] response::Value Traits::serializeVariables(Traits::Variables&& variables)
{
	return relayQuery::serializeVariables(std::move(variables));
}

[[nodiscard("unnecessary conversion")]] Traits::Response Traits::parseResponse(response::Value&& response)
{
	return relayQuery::parseResponse(std::move(response));
}

} // namespace proxy::client::query::relayQuery
} // namespace graphql
