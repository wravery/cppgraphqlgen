// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef RESOURCEOBJECT_H
#define RESOURCEOBJECT_H

#include "ValidationSchema.h"

namespace graphql::validation::object {

class [[nodiscard]] Resource final
	: public service::Object
{
private:
	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		[[nodiscard]] virtual service::TypeNames getTypeNames() const noexcept = 0;
		[[nodiscard]] virtual service::ResolverMap getResolvers() const noexcept = 0;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;
	};

	template <class T>
	struct [[nodiscard]] Model final
		: Concept
	{
		explicit Model(std::shared_ptr<T> pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard]] service::TypeNames getTypeNames() const noexcept override
		{
			return _pimpl->getTypeNames();
		}

		[[nodiscard]] service::ResolverMap getResolvers() const noexcept override
		{
			return _pimpl->getResolvers();
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const override
		{
			_pimpl->beginSelectionSet(params);
		}

		void endSelectionSet(const service::SelectionSetParams& params) const override
		{
			_pimpl->endSelectionSet(params);
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	explicit Resource(std::unique_ptr<const Concept> pimpl) noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const override;
	void endSelectionSet(const service::SelectionSetParams& params) const override;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	explicit Resource(std::shared_ptr<T> pimpl) noexcept
		: Resource { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
		static_assert(T::template implements<Resource>(), "Resource is not implemented");
	}
};

} // namespace graphql::validation::object

#endif // RESOURCEOBJECT_H
