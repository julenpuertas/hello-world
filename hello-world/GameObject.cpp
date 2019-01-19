#include "GameObjectDestroyed.h"
#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	void GameObject::remove_child(const GameObject& posible_child)
	{
		const GameObject* const p_posible_child = &posible_child;
		children_.erase_fast([&p_posible_child](const std::shared_ptr<GameObject>& wp_child)
		{
			if (wp_child)
				return p_posible_child == wp_child.get();

			return false;
		});
	}

	void GameObject::update_children_transforms() const
	{
		const Transform::Concatenator relative_to_local = world_transform_.get_relative_to_local();
		for (const std::shared_ptr<GameObject>& p_child : children_)
		{
			GameObject& child = *p_child;
			child.world_transform_ = relative_to_local.concatenate(child.local_transform_, child.attachment_to_parent_policy_);
			child.update_children_transforms();
		}
	}

	GameObject::GameObject(const Transform& world_transform, GameObject& parent, const Transform::Concatenator::Policy& attachment_to_parent_policy)
		: Entity(true)
		, world_transform_(world_transform)
		, attachment_to_parent_policy_(attachment_to_parent_policy)
	{}

	bool GameObject::is_descendant_of(const GameObject& posible_ancestor) const
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

	void GameObject::set_parent(GameObject& new_parent)
	{
		GameObject& this_ref = *this;
		if (this == &new_parent || new_parent.is_descendant_of(this_ref))
			return;

		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
			p_parent->remove_child(this_ref);

		p_parent_ = new_parent.get_this<GameObject>();
		new_parent.children_.push_back(get_this<GameObject>());
		const Transform::Concatenator local_to_relative = new_parent.world_transform_.get_local_to_relative();
		local_transform_ = local_to_relative.concatenate(world_transform_, attachment_to_parent_policy_);
	}

	void GameObject::remove_parent()
	{
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
		{
			p_parent->remove_child(*this);
			p_parent_.reset();
			local_transform_ = world_transform_;
		}
	}

	const Transform& GameObject::get_local_transform() const
	{
		return local_transform_;
	}

	void GameObject::set_local_transform(const Transform& local_transform)
	{
		local_transform_ = local_transform;

		Transform parent_world_transform;
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
			parent_world_transform = p_parent->world_transform_;

		const Transform::Concatenator relative_to_local_concatenator = parent_world_transform.get_relative_to_local();
		world_transform_ = relative_to_local_concatenator.concatenate(local_transform, attachment_to_parent_policy_);

		update_children_transforms();
	}

	const Transform& GameObject::get_world_transform() const
	{
		return world_transform_;
	}

	void GameObject::set_world_transform(const Transform& world_transform)
	{
		world_transform_ = world_transform;

		Transform parent_world_transform;
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
			parent_world_transform = p_parent->world_transform_;

		const Transform::Concatenator local_to_relative_concatenator = parent_world_transform.get_local_to_relative();
		local_transform_ = local_to_relative_concatenator.concatenate(world_transform, attachment_to_parent_policy_);

		update_children_transforms();
	}

	const Transform::Concatenator::Policy& GameObject::get_attachment_to_parent_policy() const
	{
		return attachment_to_parent_policy_;
	}

	void GameObject::set_attachment_to_parent_policy(const Transform::Concatenator::Policy& attachment_to_parent_policy)
	{
		attachment_to_parent_policy_ = attachment_to_parent_policy;
	}

	void GameObject::remove(const Rtti& comp_type)
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

		for (const std::shared_ptr<GameObject>& p_child : children_)
		{
			GameObject& child = *p_child;
			child.on_destroy();
			child.set_alive(false);
		}

		for (const std::weak_ptr<Component>& p_component : components_)
		{
			if (p_component.expired())
				continue;

			Component& component = *p_component.lock();
			component.on_destroy();
			component.set_alive(false);
		}
	}
}
