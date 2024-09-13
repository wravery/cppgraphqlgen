// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "ValidationSchema.h"

export module GraphQL.Validation.ValidationSchema;

namespace included = graphql::validation;

export namespace graphql::validation {

using validation::DogCommand;
using validation::getDogCommandNames;
using validation::getDogCommandValues;

using validation::CatCommand;
using validation::getCatCommandNames;
using validation::getCatCommandValues;

using validation::ComplexInput;

using validation::Operations;

using validation::AddSentientDetails;
using validation::AddPetDetails;
using validation::AddNodeDetails;
using validation::AddResourceDetails;
using validation::AddCatOrDogDetails;
using validation::AddDogOrHumanDetails;
using validation::AddHumanOrAlienDetails;
using validation::AddQueryDetails;
using validation::AddDogDetails;
using validation::AddAlienDetails;
using validation::AddHumanDetails;
using validation::AddCatDetails;
using validation::AddMutationDetails;
using validation::AddMutateDogResultDetails;
using validation::AddSubscriptionDetails;
using validation::AddMessageDetails;
using validation::AddArgumentsDetails;

using validation::GetSchema;

} // namespace graphql::validation
