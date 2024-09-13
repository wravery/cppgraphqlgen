// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

module;

#include "StarWarsSchema.h"

export module GraphQL.StarWars.StarWarsSchema;

namespace included = graphql::learn;

export namespace graphql::learn {

using learn::Episode;
using learn::getEpisodeNames;
using learn::getEpisodeValues;

using learn::ReviewInput;

using learn::Operations;

using learn::AddCharacterDetails;
using learn::AddHumanDetails;
using learn::AddDroidDetails;
using learn::AddQueryDetails;
using learn::AddReviewDetails;
using learn::AddMutationDetails;

using learn::GetSchema;

} // namespace graphql::learn
