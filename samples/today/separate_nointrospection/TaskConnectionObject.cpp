// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "TodayObjects.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::today {
namespace object {

TaskConnection::TaskConnection(std::unique_ptr<Concept>&& pimpl) noexcept
	: service::Object{ getTypeNames(), getResolvers() }
	, _pimpl { std::move(pimpl) }
{
}

service::TypeNames TaskConnection::getTypeNames() const noexcept
{
	return {
		R"gql(TaskConnection)gql"sv
	};
}

service::ResolverMap TaskConnection::getResolvers() const noexcept
{
	return {
		{ R"gql(edges)gql"sv, [this](service::ResolverParams&& params) { return resolveEdges(std::move(params)); } },
		{ R"gql(pageInfo)gql"sv, [this](service::ResolverParams&& params) { return resolvePageInfo(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	};
}

void TaskConnection::beginSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->beginSelectionSet(params);
}

void TaskConnection::endSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->endSelectionSet(params);
}

service::AwaitableResolver TaskConnection::resolvePageInfo(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getPageInfo(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<PageInfo>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver TaskConnection::resolveEdges(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = _pimpl->getEdges(service::FieldParams(service::SelectionSetParams{ params }, std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<TaskEdge>::convert<service::TypeModifier::Nullable, service::TypeModifier::List, service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver TaskConnection::resolve_typename(service::ResolverParams&& params) const
{
	return service::ModifiedResult<std::string>::convert(std::string{ R"gql(TaskConnection)gql" }, std::move(params));
}

} // namespace object

void AddTaskConnectionDetails(const std::shared_ptr<schema::ObjectType>& typeTaskConnection, const std::shared_ptr<schema::Schema>& schema)
{
	typeTaskConnection->AddFields({
		schema::Field::Make(R"gql(pageInfo)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(PageInfo)gql"sv))),
		schema::Field::Make(R"gql(edges)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::LIST, schema->LookupType(R"gql(TaskEdge)gql"sv)))
	});
}

} // namespace graphql::today
