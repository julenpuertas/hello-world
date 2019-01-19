#include "GameObjectDestroyed.h"
#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	void GameObject::clear_components()
	{
		for (const std::weak_ptr<Component>& p_component : components_)
		{
			if (p_component.expired())
				continue;

			Component& component = *p_component.lock();
			component.on_destroy();
			component.set_alive(false);
		}

		components_.clear();
	}

	void GameObject::remove_child(const GameObject& child)
	{
		Comparator<std::weak_ptr<GameObject>, GameObject> func = [](const std::weak_ptr<GameObject>& lhs, const GameObject& rhs)
		{
			if (lhs.expired())
				return false;
			return lhs.lock().get() == &rhs;
		};

		children_.erase_fast(std::weak_ptr<GameObject>());
	}

	bool GameObject::is_descendant(const GameObject& posible_ancestor) const
	{
		const GameObject* const p_posible_ancestor = &posible_ancestor;
		std::shared_ptr<GameObject> sp_ancestor = p_parent_.lock();
		while (sp_ancestor)
		{
			const GameObject* const p_ancestor = sp_ancestor.get();
			if (p_posible_ancestor == p_ancestor)
				return true;

			sp_ancestor = p_ancestor->p_parent_.lock();
		}

		return false;
	}

	std::shared_ptr<GameObject> GameObject::get_ancestor(size_t ancestor_index) const
	{
		std::shared_ptr<GameObject> p_ancestor = p_parent_.lock();

		if (p_ancestor)
		{
			bool loop = true;
			while (loop && ancestor_index--)
			{
				if (std::shared_ptr<GameObject> p_prev_ancestor = p_ancestor->p_parent_.lock())
					p_ancestor = p_prev_ancestor;

				else loop = false;
			}
		}

		return p_ancestor;
	}

	void GameObject::set_parent(GameObject& parent)
	{
	}

	void GameObject::remove_parent()
	{
	}

	const Transform& GameObject::get_local_transform() const
	{
		return local_transform_;
	}

	void GameObject::set_local_transform(const Transform& transform)
	{
	}

	const Transform& GameObject::get_world_transform() const
	{
		return world_transform_;
	}

	void GameObject::set_world_transform(const Transform& transform)
	{
	}

	void GameObject::remove(const Rtti & comp_type)
	{
	}

	bool GameObject::is_active() const
	{
		return false;
	}

	void GameObject::set_active(bool active)
	{
	}

	void GameObject::on_activation()
	{
	}

	void GameObject::on_deactivation()
	{
	}

	void GameObject::on_destroy()
	{
		Messages::GameObjectDestroyed message(*this);
		handle(message);
		clear_components();
	}
}
