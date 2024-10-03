// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "AppointmentObject.h"

#include "graphqlservice/internal/Schema.h"

#include "graphqlservice/introspection/IntrospectionSchema.h"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::today {
namespace object {

Appointment::Appointment(std::unique_ptr<const Concept> pimpl) noexcept
	: service::Object{ getTypeNames(), getResolvers() }
	, _pimpl { std::move(pimpl) }
{
}

service::TypeNames Appointment::getTypeNames() const noexcept
{
	return {
		R"gql(Node)gql"sv,
		R"gql(UnionType)gql"sv,
		R"gql(Appointment)gql"sv
	};
}

service::ResolverMap Appointment::getResolvers() const noexcept
{
	return {
		{ R"gql(id)gql"sv, [this](service::ResolverParams&& params) { return resolveId(std::move(params)); } },
		{ R"gql(when)gql"sv, [this](service::ResolverParams&& params) { return resolveWhen(std::move(params)); } },
		{ R"gql(isNow)gql"sv, [this](service::ResolverParams&& params) { return resolveIsNow(std::move(params)); } },
		{ R"gql(subject)gql"sv, [this](service::ResolverParams&& params) { return resolveSubject(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } },
		{ R"gql(forceError)gql"sv, [this](service::ResolverParams&& params) { return resolveForceError(std::move(params)); } }
	};
}

void Appointment::beginSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->beginSelectionSet(params);
}

void Appointment::endSelectionSet(const service::SelectionSetParams& params) const
{
	_pimpl->endSelectionSet(params);
}

service::AwaitableResolver Appointment::resolveId(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getId(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<response::IdType>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver Appointment::resolveWhen(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getWhen(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<response::Value>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Appointment::resolveSubject(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getSubject(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Appointment::resolveIsNow(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getIsNow(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<bool>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver Appointment::resolveForceError(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	service::SelectionSetParams selectionSetParams { static_cast<const service::SelectionSetParams&>(params) };
	auto directives = std::move(params.fieldData->fieldDirectives);
	auto result = _pimpl->getForceError(service::FieldParams { std::move(selectionSetParams), std::move(directives) });
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver Appointment::resolve_typename(service::ResolverParams&& params) const
{
	return service::Result<std::string>::convert(std::string{ R"gql(Appointment)gql" }, std::move(params));
}

} // namespace object

void AddAppointmentDetails(const std::shared_ptr<schema::ObjectType>& typeAppointment, const std::shared_ptr<schema::Schema>& schema)
{
	typeAppointment->AddInterfaces({
		std::static_pointer_cast<const schema::InterfaceType>(schema->LookupType(R"gql(Node)gql"sv))
	});
	typeAppointment->AddFields({
		schema::Field::Make(R"gql(id)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(ID)gql"sv))),
		schema::Field::Make(R"gql(when)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(DateTime)gql"sv)),
		schema::Field::Make(R"gql(subject)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(String)gql"sv)),
		schema::Field::Make(R"gql(isNow)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(Boolean)gql"sv))),
		schema::Field::Make(R"gql(forceError)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(String)gql"sv))
	});
}

} // namespace graphql::today
