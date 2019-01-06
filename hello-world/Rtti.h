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

		String get_name() const;
		bool is_derived_from(const Rtti& other_type) const;
		bool is_base_of(const Rtti& other_type) const;
	};
}
