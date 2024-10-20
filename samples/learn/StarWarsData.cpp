// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "StarWarsData.h"

#include "DroidData.h"
#include "HumanData.h"
#include "MutationData.h"
#include "QueryData.h"
#include "ReviewData.h"
#include "SubscriptionData.h"

using namespace std::literals;

namespace graphql::star_wars {

std::shared_ptr<learn::object::Query> MakeQuery() noexcept
{
	auto luke = std::make_shared<learn::Human>("1000"s,
		std::make_optional("Luke Skywalker"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::make_optional("Tatooine"s));

	auto vader = std::make_shared<learn::Human>("1001"s,
		std::make_optional("Darth Vader"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::make_optional("Tatooine"s));

	auto han = std::make_shared<learn::Human>("1002"s,
		std::make_optional("Han Solo"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::nullopt);

	auto leia = std::make_shared<learn::Human>("1003"s,
		std::make_optional("Leia Organa"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::make_optional("Alderaan"s));

	auto tarkin = std::make_shared<learn::Human>("1004"s,
		std::make_optional("Wilhuff Tarkin"s),
		std::vector { learn::Episode::NEW_HOPE },
		std::nullopt);

	auto threepio = std::make_shared<learn::Droid>("2000"s,
		std::make_optional("C-3PO"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::make_optional("Protocol"s));

	auto artoo = std::make_shared<learn::Droid>("2001"s,
		std::make_optional("R2-D2"s),
		std::vector { learn::Episode::NEW_HOPE, learn::Episode::EMPIRE, learn::Episode::JEDI },
		std::make_optional("Astromech"s));

	luke->addFriends({
		{ han },
		{ leia },
		{ threepio },
		{ artoo },
	});

	vader->addFriends({
		{ tarkin },
	});

	han->addFriends({
		{ luke },
		{ leia },
		{ artoo },
	});

	leia->addFriends({
		{ luke },
		{ han },
		{ threepio },
		{ artoo },
	});

	tarkin->addFriends({
		{ vader },
	});

	threepio->addFriends({
		{ luke },
		{ han },
		{ leia },
		{ artoo },
	});

	artoo->addFriends({
		{ luke },
		{ han },
		{ leia },
	});

	std::map<learn::Episode, learn::SharedHero> heroes {
		{ learn::Episode::NEW_HOPE, { artoo } },
		{ learn::Episode::EMPIRE, { luke } },
		{ learn::Episode::JEDI, { artoo } },
	};

	std::map<response::IdType, std::shared_ptr<learn::Human>> humans {
		{ luke->getId(), luke },
		{ vader->getId(), vader },
		{ han->getId(), han },
		{ leia->getId(), leia },
		{ tarkin->getId(), tarkin },
	};

	std::map<response::IdType, std::shared_ptr<learn::Droid>> droids {
		{ threepio->getId(), threepio },
		{ artoo->getId(), artoo },
	};

	return std::make_shared<learn::object::Query>(
		std::make_shared<learn::Query>(std::move(heroes), std::move(humans), std::move(droids)));
}

std::shared_ptr<service::Object> GetQueryObject() noexcept
{
	return MakeQuery();
}

std::shared_ptr<learn::object::Mutation> MakeMutation() noexcept
{
	return std::make_shared<learn::object::Mutation>(std::make_shared<learn::Mutation>());
}

std::shared_ptr<service::Object> GetMutationObject() noexcept
{
	return MakeMutation();
}

std::shared_ptr<service::Object> GetSubscriptionObject() noexcept
{
	return {};
}

std::shared_ptr<service::Request> GetService() noexcept
{
	return std::make_shared<learn::Operations>(MakeQuery(),
		MakeMutation(),
		std::shared_ptr<learn::object::Subscription> {});
}

} // namespace graphql::star_wars
