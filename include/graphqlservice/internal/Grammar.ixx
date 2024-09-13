// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

module;

#include "Grammar.h"

export module GraphQL.Internal.Grammar;

export namespace graphql::peg {

// clang-format off
using namespace tao::graphqlpeg;

using peg::for_each_child;
using peg::on_first_child;
using peg::on_first_child_if;

using peg::alias;
using peg::alias_name;
using peg::argument;
using peg::argument_content;
using peg::argument_name;
using peg::arguments;
using peg::arguments_content;
using peg::backslash_token;
using peg::block_escape_sequence;
using peg::block_quote;
using peg::block_quote_character;
using peg::block_quote_content;
using peg::block_quote_content_lines;
using peg::block_quote_empty_line;
using peg::block_quote_line;
using peg::block_quote_line_content;
using peg::block_quote_token;
using peg::bool_value;
using peg::comment;
using peg::default_value;
using peg::default_value_content;
using peg::directive;
using peg::directive_content;
using peg::directive_name;
using peg::directives;
using peg::enum_value;
using peg::escaped_char;
using peg::escaped_unicode;
using peg::escaped_unicode_codepoint;
using peg::escaped_unicode_content;
using peg::exponent_indicator;
using peg::exponent_part;
using peg::exponent_part_content;
using peg::false_keyword;
using peg::field;
using peg::field_arguments;
using peg::field_content;
using peg::field_directives;
using peg::field_name;
using peg::field_selection_set;
using peg::field_start;
using peg::float_value;
using peg::fractional_part;
using peg::fractional_part_content;
using peg::fragment_name;
using peg::fragment_spread;
using peg::fragment_token;
using peg::ignored;
using peg::inline_fragment;
using peg::input_value;
using peg::input_value_content;
using peg::integer_part;
using peg::integer_value;
using peg::list_entry;
using peg::list_type;
using peg::list_type_content;
using peg::list_value;
using peg::list_value_content;
using peg::name;
using peg::named_type;
using peg::negative_sign;
using peg::nonnull_type;
using peg::nonzero_digit;
using peg::null_keyword;
using peg::object_field;
using peg::object_field_content;
using peg::object_field_name;
using peg::object_value;
using peg::object_value_content;
using peg::on_keyword;
using peg::operation_type;
using peg::quote_token;
using peg::sign;
using peg::source_character;
using peg::string_escape_sequence;
using peg::string_escape_sequence_content;
using peg::string_quote;
using peg::string_quote_character;
using peg::string_quote_content;
using peg::string_value;
using peg::true_keyword;
using peg::type_condition;
using peg::type_condition_content;
using peg::type_name;
using peg::type_name_content;
using peg::variable;
using peg::variable_content;
using peg::variable_definitions;
using peg::variable_definitions_content;
using peg::variable_name;
using peg::variable_name_content;
using peg::variable_value;
using peg::zero_digit;
using peg::fragement_spread_or_inline_fragment_content;
using peg::fragement_spread_or_inline_fragment;
using peg::operation_name;
using peg::selection;
using peg::selection_set;
using peg::selection_set_content;
using peg::operation_definition_operation_type_content;
using peg::arguments_definition;
using peg::arguments_definition_content;
using peg::arguments_definition_start;
using peg::description;
using peg::executable_definition;
using peg::field_definition;
using peg::field_definition_content;
using peg::field_definition_start;
using peg::fields_definition;
using peg::fields_definition_content;
using peg::fragment_definition;
using peg::fragment_definition_content;
using peg::implements_interfaces;
using peg::implements_interfaces_content;
using peg::interface_type;
using peg::object_name;
using peg::object_type_definition_object_name;
using peg::object_type_definition_start;
using peg::operation_definition;
using peg::root_operation_definition;
using peg::root_operation_definition_content;
using peg::scalar_keyword;
using peg::scalar_name;
using peg::scalar_type_definition;
using peg::scalar_type_definition_content;
using peg::scalar_type_definition_start;
using peg::schema_definition;
using peg::schema_definition_content;
using peg::schema_definition_start;
using peg::schema_keyword;
using peg::type_keyword;
using peg::object_type_definition_implements_interfaces;
using peg::interface_keyword;
using peg::interface_name;
using peg::interface_type_definition_interface_name;
using peg::interface_type_definition_start;
using peg::object_type_definition;
using peg::object_type_definition_content;
using peg::object_type_definition_directives;
using peg::object_type_definition_fields_definition;
using peg::interface_type_definition_implements_interfaces;
using peg::interface_type_definition_directives;
using peg::interface_type_definition_fields_definition;
using peg::enum_keyword;
using peg::enum_name;
using peg::enum_type_definition_directives;
using peg::enum_type_definition_name;
using peg::enum_type_definition_start;
using peg::enum_value_definition;
using peg::enum_value_definition_content;
using peg::enum_value_definition_start;
using peg::enum_values_definition;
using peg::enum_values_definition_content;
using peg::enum_values_definition_start;
using peg::interface_type_definition;
using peg::interface_type_definition_content;
using peg::union_keyword;
using peg::union_member_types;
using peg::union_member_types_content;
using peg::union_member_types_start;
using peg::union_name;
using peg::union_type;
using peg::union_type_definition;
using peg::union_type_definition_content;
using peg::union_type_definition_directives;
using peg::union_type_definition_start;
using peg::enum_type_definition_enum_values_definition;
using peg::enum_type_definition;
using peg::enum_type_definition_content;
using peg::input_field_definition;
using peg::input_field_definition_content;
using peg::input_field_definition_default_value;
using peg::input_field_definition_directives;
using peg::input_field_definition_start;
using peg::input_field_definition_type_name;
using peg::input_fields_definition;
using peg::input_fields_definition_content;
using peg::input_fields_definition_start;
using peg::input_keyword;
using peg::input_object_type_definition_directives;
using peg::input_object_type_definition_object_name;
using peg::input_object_type_definition_start;
using peg::input_object_type_definition_fields_definition;
using peg::directive_definition;
using peg::directive_definition_content;
using peg::directive_definition_start;
using peg::directive_location;
using peg::directive_locations;
using peg::executable_directive_location;
using peg::extend_keyword;
using peg::input_object_type_definition;
using peg::input_object_type_definition_content;
using peg::operation_type_definition;
using peg::repeatable_keyword;
using peg::schema_extension_start;
using peg::type_definition;
using peg::type_system_definition;
using peg::type_system_directive_location;
using peg::schema_extension_operation_type_definitions;
using peg::object_type_extension_start;
using peg::scalar_type_extension;
using peg::scalar_type_extension_content;
using peg::scalar_type_extension_start;
using peg::schema_extension;
using peg::schema_extension_content;
using peg::object_type_extension_implements_interfaces;
using peg::interface_type_extension_start;
using peg::object_type_extension;
using peg::object_type_extension_content;
using peg::object_type_extension_directives;
using peg::object_type_extension_fields_definition;
using peg::interface_type_extension_implements_interfaces;
using peg::interface_type_extension_directives;
using peg::interface_type_extension_fields_definition;
using peg::enum_type_extension;
using peg::enum_type_extension_content;
using peg::enum_type_extension_start;
using peg::executable_document;
using peg::executable_document_content;
using peg::input_object_type_extension;
using peg::input_object_type_extension_content;
using peg::input_object_type_extension_start;
using peg::interface_type_extension;
using peg::interface_type_extension_content;
using peg::mixed_definition;
using peg::mixed_document;
using peg::mixed_document_content;
using peg::schema_document;
using peg::schema_document_content;
using peg::schema_type_definition;
using peg::type_extension;
using peg::type_system_extension;
using peg::union_type_extension;
using peg::union_type_extension_content;
using peg::union_type_extension_start;
// clang-format on

} // namespace graphql::peg
