#include "Rtti.h"

namespace
{
	const char* TYPE_PREFIXES_TO_ERASE[] = { "Engine::", "class " };
}

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
		const char* type_name = type_index_.name();
		for (const char* type_prefix_to_erase : TYPE_PREFIXES_TO_ERASE)
		{
			const char* found_prefix = strstr(type_name, type_prefix_to_erase);
			if (found_prefix)
				return found_prefix + strlen(type_prefix_to_erase);
		}

		return type_name;
	}

	bool Rtti::is_derived_from(const Rtti& other_type) const
	{
		bool found = this == &other_type;

		const DynamicArray<const Rtti*>::const_iterator end = parent_types_.cend();
		for (DynamicArray<const Rtti*>::const_iterator it = parent_types_.cbegin(); !found && it != end; ++it)
			found = (*it)->is_derived_from(other_type);

		return found;
	}

	bool Rtti::is_base_of(const Rtti & other_type) const
	{
		return other_type.is_derived_from(*this);
	}
}
