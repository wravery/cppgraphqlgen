// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef NESTEDINPUTCLIENT_H
#define NESTEDINPUTCLIENT_H

#include "graphqlservice/GraphQLClient.h"
#include "graphqlservice/GraphQLParse.h"
#include "graphqlservice/GraphQLResponse.h"

#include "graphqlservice/internal/Version.h"

#include <optional>
#include <string>
#include <vector>

// Check if the library version is compatible with clientgen 5.0.0
static_assert(graphql::internal::MajorVersion == 5, "regenerate with clientgen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 0, "regenerate with clientgen: minor version mismatch");

namespace graphql::client {

/// <summary>
/// Operation: query testQuery
/// </summary>
/// <code class="language-graphql">
/// query testQuery($stream: InputABCD!) {
///   control {
///     test(new: $stream) {
///       id
///     }
///   }
/// }
/// </code>
namespace nestedinput {

// Return the original text of the request document.
[[nodiscard("unnecessary call")]] const std::string& GetRequestText() noexcept;

// Return a pre-parsed, pre-validated request object.
[[nodiscard("unnecessary call")]] const peg::ast& GetRequestObject() noexcept;

struct [[nodiscard("unnecessary construction")]] InputA
{
	explicit InputA() noexcept;
	explicit InputA(
		bool aArg) noexcept;
	InputA(const InputA& other);
	InputA(InputA&& other) noexcept;
	~InputA();

	InputA& operator=(const InputA& other);
	InputA& operator=(InputA&& other) noexcept;

	bool a;
};

struct [[nodiscard("unnecessary construction")]] InputB
{
	explicit InputB() noexcept;
	explicit InputB(
		double bArg) noexcept;
	InputB(const InputB& other);
	InputB(InputB&& other) noexcept;
	~InputB();

	InputB& operator=(const InputB& other);
	InputB& operator=(InputB&& other) noexcept;

	double b;
};

struct InputBC;

struct [[nodiscard("unnecessary construction")]] InputABCD
{
	explicit InputABCD() noexcept;
	explicit InputABCD(
		std::string dArg,
		InputA aArg,
		InputB bArg,
		std::vector<InputBC> bcArg,
		int valueArg) noexcept;
	InputABCD(const InputABCD& other);
	InputABCD(InputABCD&& other) noexcept;
	~InputABCD();

	InputABCD& operator=(const InputABCD& other);
	InputABCD& operator=(InputABCD&& other) noexcept;

	std::string d;
	InputA a;
	InputB b;
	std::vector<InputBC> bc;
	int value;
};

struct [[nodiscard("unnecessary construction")]] InputBC
{
	explicit InputBC() noexcept;
	explicit InputBC(
		response::IdType cArg,
		InputB bArg) noexcept;
	InputBC(const InputBC& other);
	InputBC(InputBC&& other) noexcept;
	~InputBC();

	InputBC& operator=(const InputBC& other);
	InputBC& operator=(InputBC&& other) noexcept;

	response::IdType c;
	InputB b;
};

} // namespace nestedinput

namespace query::testQuery {

using nestedinput::GetRequestText;
using nestedinput::GetRequestObject;

// Return the name of this operation in the shared request document.
[[nodiscard("unnecessary call")]] const std::string& GetOperationName() noexcept;

using nestedinput::InputA;
using nestedinput::InputB;
using nestedinput::InputABCD;
using nestedinput::InputBC;

struct [[nodiscard("unnecessary construction")]] Variables
{
	InputABCD stream {};
};

[[nodiscard("unnecessary conversion")]] response::Value serializeVariables(Variables&& variables);

struct [[nodiscard("unnecessary construction")]] Response
{
	struct [[nodiscard("unnecessary construction")]] control_Control
	{
		struct [[nodiscard("unnecessary construction")]] test_Output
		{
			std::optional<bool> id {};
		};

		std::optional<test_Output> test {};
	};

	control_Control control {};
};

[[nodiscard("unnecessary conversion")]] Response parseResponse(response::Value&& response);

struct Traits
{
	[[nodiscard("unnecessary call")]] static const std::string& GetRequestText() noexcept;
	[[nodiscard("unnecessary call")]] static const peg::ast& GetRequestObject() noexcept;
	[[nodiscard("unnecessary call")]] static const std::string& GetOperationName() noexcept;

	using Variables = testQuery::Variables;

	[[nodiscard("unnecessary conversion")]] static response::Value serializeVariables(Variables&& variables);

	using Response = testQuery::Response;

	[[nodiscard("unnecessary conversion")]] static Response parseResponse(response::Value&& response);
};

} // namespace query::testQuery
} // namespace graphql::client

#endif // NESTEDINPUTCLIENT_H
