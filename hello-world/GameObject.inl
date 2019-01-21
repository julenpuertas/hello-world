#include "ComponentTraits.h"

namespace Engine
{
	template<typename ... Args> GameObject::GameObject(Args&& ... arguments)
		: world_transform_(std::forward<Args>(arguments) ...)
	{}

	template<typename T, typename ...Args> std::shared_ptr<T> GameObject::add(Args&& ... arguments)
	{
		const DynamicArray<std::weak_ptr<Component> >::const_iterator it = get_iterator_to_type(T::TYPE);
		if (it != components_.cend())
			return std::dynamic_pointer_cast<T>(it->lock());

		GameObject& this_ref = *this;
		if (!ComponentTraits::can_have_component_of_type<T>(this_ref))
			return nullptr;

		const std::shared_ptr<T> p_component = std::make_shared<T>(std::forward<Args>(arguments) ...);
		components_.emplace_back(p_component);
		p_component->set_owner(this_ref);

		return p_component;
	}

	template<typename T> std::shared_ptr<T> GameObject::get() const
	{
		const DynamicArray<std::weak_ptr<Component> >::const_iterator it_end = components_.cend();
		const DynamicArray<std::weak_ptr<Component> >::const_iterator it = std::find_if(components_.cbegin(), it_end, [](const std::weak_ptr<Component>& wp_component)
		{
			if (const std::shared_ptr<Component> p_component = wp_component.lock())
			{
				const Rtti& component_type = p_component->get_rtti();
				return component_type.is_same_or_derived_from(T::TYPE);
			}

			return false;
		});

		if (it == it_end)
			return nullptr;

		return std::dynamic_pointer_cast<T>(it->lock());
	}

	template<typename T> DynamicArray<std::shared_ptr<T> > GameObject::get_all() const
	{
		DynamicArray<std::shared_ptr<T> > result;
		result.reserve(components_.size());
		for (const std::weak_ptr<Component>& wp_component : components_)
		{
			const std::shared_ptr<Component> p_component = wp_component.lock();
			if (!p_component)
				continue;

			const Rtti& component_type = p_component->get_rtti();
			if (component_type.is_same_or_derived_from(T::TYPE))
				result.push_back(std::dynamic_pointer_cast<T>(p_component));
		}

		return result;
	}
}
