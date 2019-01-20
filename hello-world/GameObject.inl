#include "GameObject.h"

namespace Engine
{
	template<typename ... Args> GameObject::GameObject(Args&& ... arguments)
		: Entity(true)
		, local_transform_(std::forward<Args>(arguments) ...)
		, world_transform_(local_transform_)
	{}

	template<typename T, typename ...Args> std::shared_ptr<T> GameObject::add(Args&& ... arguments)
	{
		return std::shared_ptr<T>();
	}

	template<typename T> std::shared_ptr<T> GameObject::get() const
	{
		return std::shared_ptr<T>();
	}

	template<typename T> DynamicArray<std::shared_ptr<T> > GameObject::get_all() const
	{
		return DynamicArray<std::shared_ptr<T> >();
	}
}
