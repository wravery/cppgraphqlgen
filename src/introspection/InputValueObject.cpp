// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "InputValueObject.h"
#include "TypeObject.h"

#include "graphqlservice/internal/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::introspection {
namespace object {

InputValue::InputValue(std::shared_ptr<introspection::InputValue> pimpl) noexcept
	: service::Object{ getTypeNames(), getResolvers() }
	, _pimpl { std::make_unique<Model<introspection::InputValue>>(std::move(pimpl)) }
{
}

InputValue::~InputValue()
{
	// This is empty, but explicitly defined here so that it can access the un-exported destructor
	// of the implementation type.
}

service::TypeNames InputValue::getTypeNames() const noexcept
{
	return {
		R"gql(__InputValue)gql"sv
	};
}

service::ResolverMap InputValue::getResolvers() const noexcept
{
	return {
		{ R"gql(name)gql"sv, [this](service::ResolverParams&& params) { return resolveName(std::move(params)); } },
		{ R"gql(type)gql"sv, [this](service::ResolverParams&& params) { return resolveType(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } },
		{ R"gql(description)gql"sv, [this](service::ResolverParams&& params) { return resolveDescription(std::move(params)); } },
		{ R"gql(defaultValue)gql"sv, [this](service::ResolverParams&& params) { return resolveDefaultValue(std::move(params)); } }
	};
}

service::AwaitableResolver InputValue::resolveName(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto result = _pimpl->getName();
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver InputValue::resolveDescription(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto result = _pimpl->getDescription();
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver InputValue::resolveType(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto result = _pimpl->getType();
	resolverLock.unlock();

	return service::ModifiedResult<Type>::convert(std::move(result), std::move(params));
}

service::AwaitableResolver InputValue::resolveDefaultValue(service::ResolverParams&& params) const
{
	std::unique_lock resolverLock(_resolverMutex);
	auto result = _pimpl->getDefaultValue();
	resolverLock.unlock();

	return service::ModifiedResult<std::string>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::AwaitableResolver InputValue::resolve_typename(service::ResolverParams&& params) const
{
	return service::Result<std::string>::convert(std::string{ R"gql(__InputValue)gql" }, std::move(params));
}

} // namespace object

void AddInputValueDetails(const std::shared_ptr<schema::ObjectType>& typeInputValue, const std::shared_ptr<schema::Schema>& schema)
{
	typeInputValue->AddFields({
		schema::Field::Make(R"gql(name)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(String)gql"sv))),
		schema::Field::Make(R"gql(description)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(String)gql"sv)),
		schema::Field::Make(R"gql(type)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType(R"gql(__Type)gql"sv))),
		schema::Field::Make(R"gql(defaultValue)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType(R"gql(String)gql"sv))
	});
}

} // namespace graphql::introspection
