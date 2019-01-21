#include "Rtti.h"

namespace Engine
{
	Rtti::Rtti(const type_info& type, const Rtti& parent_type)
		: type_index_(type)
		, parent_types_(1, &parent_type)
	{}

	Rtti::Rtti(const type_info& type, const std::initializer_list<const Rtti*>& parent_types)
		: type_index_(type)
		, parent_types_(parent_types)
	{}

	String::View Rtti::get_name() const
	{
		const char* const type_name = type_index_.name();
		const char* const prefixes_to_erase[] = { "Engine::", "class " };
		for (const char* type_prefix_to_erase : prefixes_to_erase)
		{
			const char* found_prefix = strstr(type_name, type_prefix_to_erase);
			if (found_prefix)
				return found_prefix + strlen(type_prefix_to_erase);
		}

		return type_name;
	}

	bool Rtti::is_same_or_derived_from(const Rtti& other_type) const
	{
		bool found = this == &other_type;

		const DynamicArray<const Rtti*>::const_iterator end = parent_types_.cend();
		for (DynamicArray<const Rtti*>::const_iterator it = parent_types_.cbegin(); !found && it != end; ++it)
			found = (*it)->is_same_or_derived_from(other_type);

		return found;
	}
}
