// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "TaskEdgeObject.h"
#include "TaskObject.h"

#include "graphqlservice/internal/Schema.h"

#include "graphqlservice/introspection/IntrospectionSchema.h"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::today {
namespace object {

TaskEdge::TaskEdge(std::unique_ptr<const Concept> pimpl) noexcept
	: service::Object{ getTypeNames(), getResolvers() }
	, _pimpl { std::move(pimpl) }
{
}

service::TypeNames TaskEdge::getTypeNames() const noexcept
{
	return {
		R"gql(TaskEdge)gql"sv
	};
}

service::ResolverMap TaskEdge::getResolvers() const noexcept
{
	return {
		{ R"gql(node)gql"sv, [this](service::ResolverParams&& params) { return resolveNode(std::move(params)); } },
		{ R"gql(cursor)gql"sv, [this](service::ResolverParams&& params) { return resolveCursor(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	};
}

void TaskEdge::beginSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->beginSelectionSet(params);
}

void TaskEdge::endSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->endSelectionSet(params);
}

service::AwaitableResolver TaskEdge::resolveNode(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getNode(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<Task>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver TaskEdge::resolveCursor(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getCursor(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<response::Value>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver TaskEdge::resolve_typename(service::ResolverParams&& params) const
{
	return service::Result<std::string>::convert(std::string{ R"gql(TaskEdge)gql" }, std::move(params));
}

} // namespace object

void AddTaskEdgeDetails(const std::shared_ptr<schema::ObjectType>& typeTaskEdge, const std::shared_ptr<schema::Schema>& schema)
{
	typeTaskEdge->AddFields({
		schema::Field::Make(R"gql(node)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(Task)gql"sv)),
		schema::Field::Make(R"gql(cursor)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(ItemCursor)gql"sv)))
	});
}

} // namespace graphql::today
