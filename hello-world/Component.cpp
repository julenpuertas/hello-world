#include "GameObject.h"
#include "Component.h"

namespace
{
	Engine::IHasheable::MultiMap<Engine::Component::TypeInfo> g_types;
	Engine::IHasheable::Map<Engine::Component::TypeInfo, Engine::Requirement<Engine::GameObject> > g_requirements_to_be_instantiated_in;
}

namespace Engine
{
	Component::TypeInfo::TypeInfo(const std::type_info& type, const Requirement<GameObject>& requirement_to_be_instantiated_in)
		: type_(type)
	{
		if (requirement_to_be_instantiated_in)
			g_requirements_to_be_instantiated_in.emplace(*this, requirement_to_be_instantiated_in);
	}

	Component::TypeInfo::TypeInfo(const std::type_info& type, const TypeInfo& parent_type, const Requirement<GameObject>& requirement_to_be_instantiated_in)
		: type_(type)
	{
		const TypeInfo& ref_this = *this;
		g_types.emplace(ref_this, parent_type);

		if (requirement_to_be_instantiated_in)
			g_requirements_to_be_instantiated_in.emplace(ref_this, requirement_to_be_instantiated_in);
	}

	Component::TypeInfo::TypeInfo(const std::type_info& type, const std::initializer_list<TypeInfo>& parent_types, const Requirement<GameObject>& requirement_to_be_instantiated_in)
		: type_(type)
	{
		const TypeInfo& ref_this = *this;
		for (const TypeInfo& parent_type : parent_types)
			g_types.emplace(ref_this, parent_type);

		if (requirement_to_be_instantiated_in)
			g_requirements_to_be_instantiated_in.emplace(ref_this, requirement_to_be_instantiated_in);
	}

	bool Component::TypeInfo::operator==(const TypeInfo& rhs) const
	{
		return type_ == rhs.type_;
	}

	bool Component::TypeInfo::operator!=(const TypeInfo& rhs) const
	{
		return !(*this == rhs);
	}

	bool Component::TypeInfo::operator<(const TypeInfo& rhs) const
	{
		return type_ < rhs.type_;
	}

	bool Component::TypeInfo::operator>(const TypeInfo& rhs) const
	{
		return rhs < *this;
	}

	bool Component::TypeInfo::operator<=(const TypeInfo& rhs) const
	{
		return !(*this > rhs);
	}

	bool Component::TypeInfo::operator>=(const TypeInfo& rhs) const
	{
		return !(*this < rhs);
	}

	String::View Component::TypeInfo::get_name() const
	{
		const char* const type_name = type_.name();
		const char* const prefixes_to_erase[] = { "Engine::", "class " };
		for (const char* type_prefix_to_erase : prefixes_to_erase)
		{
			const char* const found_prefix = strstr(type_name, type_prefix_to_erase);
			if (found_prefix)
				return found_prefix + strlen(type_prefix_to_erase);
		}

		return type_name;
	}

	bool Component::TypeInfo::is_same_or_derived_from(const std::type_info& other_type) const
	{
		if (type_ == other_type)
			return true;

		bool found = false;
		for (Pair<IHasheable::MultiMap<TypeInfo>::const_iterator> range = g_types.equal_range(*this); !found && range.first != range.second; ++range.first)
		{
			const TypeInfo& parent_type = range.first->second;
			found = parent_type.is_same_or_derived_from(other_type);
		}

		return found;
	}

	bool Component::TypeInfo::can_be_instantiated_in(const GameObject& game_object) const
	{
		const TypeInfo& ref_this = *this;
		const IHasheable::Map<TypeInfo, Requirement<GameObject> >::const_iterator it = g_requirements_to_be_instantiated_in.find(ref_this);

		if (it == g_requirements_to_be_instantiated_in.cend() || it->second(game_object))
		{
			bool can_be_instantiated = true;
			for (Pair<IHasheable::MultiMap<TypeInfo>::const_iterator> range = g_types.equal_range(ref_this); can_be_instantiated && range.first != range.second; ++range.first)
			{
				const TypeInfo& parent_type = range.first->second;
				can_be_instantiated = parent_type.can_be_instantiated_in(game_object);
			}

			return can_be_instantiated;
		}

		return false;
	}

	size_t Component::TypeInfo::get_hash() const
	{
		return std::hash<std::type_index>()(type_);
	}

	Component::Component(const Component&)
	{}

	void Component::attach()
	{}

	void Component::on_owner_set()
	{}

	void Component::assign(const Component & rhs)
	{}

	bool Component::is_alive() const
	{
		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
			return Entity::is_alive() && p_owner->is_alive();

		return false;
	}

	bool Component::is_active() const
	{
		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
			return Entity::is_active() && p_owner->is_active();

		return false;
	}

	void Component::set_active(bool active)
	{
		if (Entity::is_active() == active)
			return;

		Entity::set_active(active);

		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
		{
			if (!p_owner->is_active())
				return;

			if (active)
				on_activation();

			else on_deactivation();
		}
	}

	std::shared_ptr<GameObject> Component::get_owner() const
	{
		return p_owner_.lock();
	}

	void Component::set_owner(GameObject& owner)
	{
		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
			p_owner->remove(get_type_info());

		const bool was_free = p_owner_.expired();
		p_owner_ = owner.get_this<GameObject>();

		if(was_free)
			attach();

		on_owner_set();
	}
}
