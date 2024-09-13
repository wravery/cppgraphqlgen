// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "CatOrDogObject.h"

export module GraphQL.Validation.CatOrDogObject;

namespace included = graphql::validation::object;

export namespace graphql::validation::object {

namespace exported {

using CatOrDog = included::CatOrDog;

} // namespace exported

using namespace exported;

} // namespace graphql::validation::object
