
namespace Engine
{
	template<typename ... Args> GameObject::GameObject(Args&& ... arguments)
		: world_transform_(std::forward<Args>(arguments) ...)
	{
		add_to_global_gameobject_list();
	}

	template<typename T, typename ...Args> T* GameObject::add(Args&& ... arguments)
	{
		const std::type_info& type = typeid(T);
		const DynamicArray<Component*>::const_iterator it = get_iterator_to_type(type);
		if (it != components_.cend())
			return reinterpret_cast<T*>(*it);

		GameObject& this_ref = *this;
		const Component::TypeInfo component_type = type;
		if (!component_type.can_be_instantiated_in(this_ref))
			return nullptr;

		T* p_component = new T(std::forward<Args>(arguments) ...);
		components_.emplace_back(p_component);
		p_component->set_owner(this_ref);

		return p_component;
	}

	template<typename T> T* GameObject::get() const
	{
		const DynamicArray<Component*>::const_iterator it_end = components_.cend();
		const DynamicArray<Component*>::const_iterator it = std::find_if(components_.cbegin(), it_end, [](const Component* p_component)
		{
			const Component::TypeInfo component_type = p_component->get_type_info();
			return component_type.is_same_or_derived_from(typeid(T));
		});

		if (it == it_end)
			return nullptr;

		return reinterpret_cast<T*>(*it);
	}

	template<typename T> DynamicArray<T*> GameObject::get_all() const
	{
		DynamicArray<T*> result;
		result.reserve(components_.size());
		for (const Component* p_component : components_)
		{
			const Component::TypeInfo component_type = p_component->get_type_info();
			if (component_type.is_same_or_derived_from(typeid(T)))
				result.push_back(reinterpret_cast<T*>(p_component));
		}

		return result;
	}
}
