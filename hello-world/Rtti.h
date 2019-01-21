#pragma once
#include <typeindex>
#include "String.h"
#include "DynamicArray.h"

namespace Engine
{
	class Rtti
	{
		const std::type_index type_index_;
		const DynamicArray<const Rtti*> parent_types_;

	public:
		Rtti(const std::type_info& type, const Rtti& parent_type);
		Rtti(const std::type_info& type, const std::initializer_list<const Rtti*>& parent_types = {});

		String::View get_name() const;
		bool is_same_or_derived_from(const Rtti& other_type) const;
	};
}

#define RTTI_DECLARATION static const Rtti TYPE
