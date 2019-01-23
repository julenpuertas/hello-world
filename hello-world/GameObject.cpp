#include "GameObjectDestroyed.h"
#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	void GameObject::for_each_component(const std::function<void(Component&)>& predicate) const
	{
		if (!predicate)
			return;

		for (const std::weak_ptr<Component>& p_comopnent : components_)
		{
			if (!p_comopnent.expired())
				predicate(*p_comopnent.lock());
		}
	}

	void GameObject::for_each_child(const std::function<void(GameObject&)>& predicate) const
	{
		if (!predicate)
			return;

		for (const std::shared_ptr<GameObject>& p_child : children_)
		{
			if (p_child)
				predicate(*p_child);
		}
	}

	void GameObject::remove_child(const GameObject& posible_child)
	{
		const GameObject* const p_posible_child = &posible_child;
		children_.erase_fast([&p_posible_child](const std::shared_ptr<GameObject>& p_child)
		{
			if (p_child)
				return p_posible_child == p_child.get();

			return false;
		});
	}

	Transform GameObject::get_local_transform(const Transform& parent_world_transform) const
	{
		const Transform::Concatenator local_to_relative = parent_world_transform.get_local_to_relative();
		return local_to_relative.concatenate(world_transform_, attachment_to_parent_policy_);
	}

	void GameObject::update_children_transforms(const Transform& old_world_transform) const
	{
		const Transform::Concatenator relative_to_local = world_transform_.get_relative_to_local();
		for_each_child([&old_world_transform, &relative_to_local](GameObject& child)
		{
			const Transform child_old_world_transform = child.world_transform_;
			const Transform child_local_transform = child.get_local_transform(old_world_transform);
			child.world_transform_ = relative_to_local.concatenate(child_local_transform, child.attachment_to_parent_policy_);
			child.update_children_transforms(child_old_world_transform);
		});
	}

	DynamicArray<std::weak_ptr<Component> >::const_iterator GameObject::get_iterator_to_type(const Rtti& type)
	{
		return std::find_if(components_.cbegin(), components_.cend(), [&type](const std::weak_ptr<Component>& wp_component)
		{
			if (const std::shared_ptr<Component> p_component = wp_component.lock())
			{
				const Rtti& component_type = p_component->get_rtti();
				return &type == &component_type;
			}

			return false;
		});
	}

	void GameObject::destroy_children() const
	{
		for_each_child([](GameObject& child)
		{
			child.on_destroy();
			child.set_alive(false);
		});
	}

	void GameObject::destroy_components() const
	{
		for_each_component([](Component& component)
		{
			component.on_destroy();
			component.set_alive(false);
		});
	}

	bool GameObject::remove_parent_if_it_has()
	{
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
		{
			p_parent->remove_child(*this);
			p_parent_.reset();
			return true;
		}
		return false;
	}

	void GameObject::add_to_global_gameobject_list()
	{}

	void GameObject::remove_from_global_gameobject_list()
	{}

	bool GameObject::update_or_destroy(const std::shared_ptr<GameObject>& p_gameobject)
	{
		GameObject& gameobject = *p_gameobject;
		const bool alive = gameobject.is_alive();
		if (alive)
			gameobject.on_update();

		else gameobject.on_destroy();

		return !alive;
	}

	GameObject::GameObject(Uninitialize)
	{}

	GameObject::GameObject(const Transform& world_transform, GameObject& parent, const Transform::Concatenator::Policy& attachment_to_parent_policy)
		: world_transform_(world_transform)
		, attachment_to_parent_policy_(attachment_to_parent_policy)
	{
		set_parent(parent);
	}

	GameObject::GameObject(GameObject& parent, const Transform& local_transform, const Transform::Concatenator::Policy& attachment_to_parent_policy)
		: attachment_to_parent_policy_(attachment_to_parent_policy)
	{
	}

	GameObject& GameObject::operator=(const GameObject& rhs)
	{
		destroy_children();
		children_.clear();
		children_.reserve(rhs.children_.size());
		world_transform_.set_scale(rhs.world_transform_.get_scale());
		const Transform::Concatenator relative_to_local = world_transform_.get_relative_to_local();
		const std::weak_ptr<GameObject> p_this = get_this<GameObject>();
		for (const std::shared_ptr<GameObject>& p_rhs_child : rhs.children_)
		{
			if (!p_rhs_child)
				continue;

			const GameObject& rhs_child = *p_rhs_child;
			const Transform rhs_child_local_transform = rhs_child.get_local_transform();

			const std::shared_ptr<GameObject> p_child = std::make_shared<GameObject>(Uninitialize());
			children_.push_back(p_child);
			GameObject& child = *p_child;
			child = rhs_child;
			child.p_parent_ = p_this;
			child.world_transform_ = relative_to_local.concatenate(rhs_child_local_transform, child.attachment_to_parent_policy_);
		}

		components_.reserve_for(rhs.components_.size());
		DynamicArray<std::weak_ptr<Component> >::const_iterator it_end = rhs.components_.cend();
		for_each_component([](Component& component)
		{
			const Rtti& type = component.get_rtti();
			//if()
		});

		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& rhs)
	{
		destroy_children();
		destroy_components();

		world_transform_ = rhs.world_transform_;
		attachment_to_parent_policy_ = rhs.attachment_to_parent_policy_;



		const bool had_parent = remove_parent_if_it_has();
		if (const std::shared_ptr<GameObject> p_rhs_parent = rhs.p_parent_.lock())
		{
			p_rhs_parent->remove_child(rhs);
			p_parent_ = std::move(rhs.p_parent_);
			if (!had_parent)
				remove_from_global_gameobject_list();
		}

		else if (had_parent)
			add_to_global_gameobject_list();



		children_ = std::move(rhs.children_);
		const std::weak_ptr<GameObject> p_this = get_this<GameObject>();
		for (const std::shared_ptr<GameObject>& p_child : children_)
			p_child->p_parent_ = p_this;


		GameObject& this_ref = *this;
		components_.clear();
		components_.reserve(rhs.components_.size());
		while (!rhs.components_.empty())
		{
			const std::weak_ptr<Component>& wp_component = components_.back();
			if (const std::shared_ptr<Component> p_component = wp_component.lock())
				p_component->set_owner(this_ref);
		}

		rhs.set_alive(false);
		return this_ref;
	}

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

		else remove_from_global_gameobject_list();

		p_parent_ = new_parent.get_this<GameObject>();
		new_parent.children_.push_back(get_this<GameObject>());
	}

	void GameObject::remove_parent()
	{
		if(remove_parent_if_it_has())
			add_to_global_gameobject_list();
	}

	Transform GameObject::get_local_transform() const
	{
		Transform parent_world_transform;
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
			parent_world_transform = p_parent->world_transform_;

		return get_local_transform(parent_world_transform);
	}

	void GameObject::set_local_transform(const Transform& local_transform)
	{
		const Transform old_world_transform = world_transform_;

		Transform parent_world_transform;
		if (const std::shared_ptr<GameObject> p_parent = p_parent_.lock())
			parent_world_transform = p_parent->world_transform_;

		const Transform::Concatenator concatenator = parent_world_transform.get_relative_to_local();
		world_transform_ = concatenator.concatenate(local_transform, attachment_to_parent_policy_);

		update_children_transforms(old_world_transform);
	}

	const Transform& GameObject::get_world_transform() const
	{
		return world_transform_;
	}

	void GameObject::set_world_transform(const Transform& world_transform)
	{
		const Transform old_world_transform = world_transform_;
		world_transform_ = world_transform;
		update_children_transforms(old_world_transform);
	}

	const Transform::Concatenator::Policy& GameObject::get_attachment_to_parent_policy() const
	{
		return attachment_to_parent_policy_;
	}

	void GameObject::set_attachment_to_parent_policy(const Transform::Concatenator::Policy& attachment_to_parent_policy)
	{
		attachment_to_parent_policy_ = attachment_to_parent_policy;
	}

	bool GameObject::remove(const Rtti& type)
	{
		const DynamicArray<std::weak_ptr<Component> >::const_iterator it = get_iterator_to_type(type);

		const bool erased = it != components_.cend();
		if (erased)
			components_.erase(it);

		return erased;
	}

	bool GameObject::is_active() const
	{
		bool active = Entity::is_active();
		std::shared_ptr<GameObject> p_ancestor = p_parent_.lock();

		while (p_ancestor && active)
		{
			GameObject& ancestor = *p_ancestor;
			active = ancestor.Entity::is_active();
			p_ancestor = ancestor.p_parent_.lock();
		}

		return active;
	}

	void GameObject::set_active(bool active)
	{
		const bool was_active = is_active();
		Entity::set_active(active);
		const bool now_is_active = is_active();

		if (!was_active && now_is_active)
			on_activation();

		else if (was_active && !now_is_active)
			on_deactivation();
	}

	void GameObject::on_activation()
	{
		for_each_component([](Component& component)
		{
			if (component.Entity::is_active())
				component.on_activation();
		});

		for_each_child([](GameObject& child)
		{
			if (child.Entity::is_active())
				child.on_activation();
		});
	}

	void GameObject::on_deactivation()
	{
		for_each_component([](Component& component)
		{
			if (component.Entity::is_active())
				component.on_deactivation();
		});

		for_each_child([](GameObject& child)
		{
			if (child.Entity::is_active())
				child.on_deactivation();
		});
	}

	void GameObject::on_update()
	{
		children_.erase_multiple(&GameObject::update_or_destroy);
	}

	void GameObject::on_destroy()
	{
		Messages::GameObjectDestroyed message(*this);
		handle(message);

		destroy_children();
		destroy_components();
	}
}
