#include "GameObjectDestroyed.h"
#include "GameObject.h"

namespace
{
	Engine::DynamicArray<std::unique_ptr<Engine::GameObject> > g_gameobjects;

	void remove_gameobject(Engine::DynamicArray<std::unique_ptr<Engine::GameObject> >& gameobjects, const Engine::GameObject* p_gameobject)
	{
		using Engine::DynamicArray;
		using Engine::GameObject;

		const DynamicArray<std::unique_ptr<GameObject> >::iterator it_end = gameobjects.end();
		const DynamicArray<std::unique_ptr<GameObject> >::iterator it = std::find_if(gameobjects.begin(), it_end, [&p_gameobject](const std::unique_ptr<GameObject>& p_child)
		{
			if (p_child)
				return p_gameobject == p_child.get();

			return false;
		});

		if (it == it_end)
			return;

		it->release();
		gameobjects.erase(it);
	}
}

namespace Engine
{
	void GameObject::for_each_component(const std::function<void(Component&)>& predicate) const
	{
		if (!predicate)
			return;

		for (Component* p_comopnent : components_)
			predicate(*p_comopnent);
	}

	void GameObject::for_each_child(const std::function<void(GameObject&)>& predicate) const
	{
		if (!predicate)
			return;

		for (const std::unique_ptr<GameObject>& p_child : children_)
		{
			if (p_child)
				predicate(*p_child);
		}
	}

	void GameObject::remove_child(const GameObject& posible_child)
	{
		remove_gameobject(children_, &posible_child);
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

	DynamicArray<Component*>::const_iterator GameObject::get_iterator_to_type(const Component::TypeInfo& type) const
	{
		return std::find_if(components_.cbegin(), components_.cend(), [&type](const Component* p_component)
		{
			const Component::TypeInfo component_type = p_component->get_type_info();
			return type == component_type;
		});
	}

	void GameObject::destroy_children() const
	{
		for_each_child([](GameObject& child)
		{
			child.on_destroy();
			child.destroy();
		});
	}

	void GameObject::destroy_components() const
	{
		for_each_component([](Component& component)
		{
			component.on_destroy();
			component.destroy();
		});
	}

	bool GameObject::remove_parent_if_it_has()
	{
		if (!p_parent_)
			return false;

		p_parent_->remove_child(*this);
		p_parent_ = nullptr;
		return true;
	}

	void GameObject::add_to_global_gameobject_list()
	{
		g_gameobjects.emplace_back(this);
	}

	void GameObject::remove_from_global_gameobject_list()
	{
		remove_gameobject(g_gameobjects, this);
	}

	void GameObject::copy_children(const GameObject& rhs)
	{
		children_.reserve(rhs.children_.size());
		const Transform::Concatenator relative_to_local = world_transform_.get_relative_to_local();
		for (const std::unique_ptr<GameObject>& p_rhs_child : rhs.children_)
		{
			if (!p_rhs_child)
				continue;

			const GameObject& rhs_child = *p_rhs_child;
			const Transform rhs_child_local_transform = rhs_child.get_local_transform();

			GameObject* p_child = new GameObject(Uninitialize());
			children_.emplace_back(p_child);

			p_child->p_parent_ = this;
			p_child->world_transform_ = relative_to_local.concatenate(rhs_child_local_transform, p_child->attachment_to_parent_policy_);
			p_child->attachment_to_parent_policy_ = rhs_child.attachment_to_parent_policy_;

			p_child->copy_children(rhs_child);
			p_child->copy_components(rhs_child);
		}
	}

	void GameObject::copy_components(const GameObject& rhs)
	{
		components_.reserve(rhs.components_.size());
		const DynamicArray<Component*>::const_iterator it_rhs_end = rhs.components_.cend();
		DynamicArray<Component*>::const_iterator it = components_.cbegin();
		while (it != components_.cend())
		{
			if (Component* p_component = *it)
			{
				if (rhs.get_iterator_to_type(p_component->get_type_info()) == it_rhs_end)
				{
					p_component->destroy();
					it = components_.erase(it);
				}

				else ++it;
			}

			else it = components_.erase(it);
		}

		rhs.for_each_component([this](Component& component)
		{
			const DynamicArray<Component*>::const_iterator it = get_iterator_to_type(component.get_type_info());
			if (it == components_.cend())
			{
				Component* p_component = component.clone();
				components_.emplace_back(p_component);
				p_component->set_owner(*this);
			}

			else
			{
				// assign component
			}
		});
	}

	void GameObject::move_parent(GameObject&& rhs)
	{
		const bool had_parent = remove_parent_if_it_has();
		if (rhs.p_parent_)
		{
			p_parent_ = rhs.p_parent_;
			rhs.p_parent_ = nullptr;
			p_parent_->children_.emplace_back(this);

			if (!had_parent)
				remove_from_global_gameobject_list();
		}

		else if (had_parent)
			add_to_global_gameobject_list();
	}

	void GameObject::move_children(GameObject&& rhs)
	{
		children_ = std::move(rhs.children_);
		for (const std::unique_ptr<GameObject>& p_child : children_)
			p_child->p_parent_ = this;

		update_children_transforms(rhs.world_transform_);
	}

	void GameObject::move_components(GameObject&& rhs)
	{
		GameObject& this_ref = *this;
		components_.clear();
		components_.reserve(rhs.components_.size());
		while (!rhs.components_.empty())
		{
			if (Component* p_component = rhs.components_.back())
				p_component->set_owner(this_ref);

			rhs.components_.pop_back();
		}
	}

	bool GameObject::update_or_destroy(const std::unique_ptr<GameObject>& p_gameobject)
	{
		if (!p_gameobject)
			return true;

		GameObject& gameobject = *p_gameobject;
		const bool alive = gameobject.is_alive();
		if (alive)
			gameobject.on_update();

		else gameobject.on_destroy();

		return !alive;
	}

	GameObject::GameObject(Uninitialize)
	{}

	GameObject::GameObject(const Transform& world_transform, const Transform::Concatenator::Policy& attachment_to_parent_policy)
		: world_transform_(world_transform)
		, attachment_to_parent_policy_(attachment_to_parent_policy)
	{}

	GameObject& GameObject::operator=(const GameObject& rhs)
	{
		if (this != &rhs)
		{
			destroy_children();
			children_.clear();
			world_transform_.set_scale(rhs.world_transform_.get_scale());

			copy_children(rhs);
			copy_components(rhs);
		}

		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& rhs)
	{
		if (this != &rhs)
		{
			destroy_children();
			destroy_components();

			world_transform_ = rhs.world_transform_;
			attachment_to_parent_policy_ = rhs.attachment_to_parent_policy_;

			move_parent(std::move(rhs));
			move_children(std::move(rhs));
			move_components(std::move(rhs));

			rhs.destroy();
		}

		return *this;
	}

	bool GameObject::is_descendant_of(const GameObject& posible_ancestor) const
	{
		const GameObject* const p_posible_ancestor = &posible_ancestor;
		for (const GameObject* p_ancestor = p_parent_; p_ancestor; p_ancestor = p_ancestor->p_parent_)
		{
			if (p_posible_ancestor == p_ancestor)
				return true;
		}

		return false;
	}

	GameObject* GameObject::get_ancestor(size_t ancestor_index) const
	{
		GameObject* p_ancestor = p_parent_;

		while (p_ancestor && ancestor_index--)
			p_ancestor = p_ancestor->p_parent_;

		return p_ancestor;
	}

	void GameObject::set_parent(GameObject& new_parent)
	{
		GameObject& this_ref = *this;
		GameObject* const p_new_parent = &new_parent;
		if (this == p_new_parent || new_parent.is_descendant_of(this_ref))
			return;

		if (p_parent_)
			p_parent_->remove_child(this_ref);

		// remove releases the object
		else remove_from_global_gameobject_list();

		p_parent_ = p_new_parent;
		p_parent_->children_.emplace_back(this);
	}

	void GameObject::remove_parent()
	{
		// add attaches the object to unique ptr
		if (remove_parent_if_it_has())
			add_to_global_gameobject_list();
	}

	Transform GameObject::get_local_transform() const
	{
		if (p_parent_)
			get_local_transform(p_parent_->world_transform_);

		return world_transform_;
	}

	void GameObject::set_local_transform(const Transform& local_transform)
	{
		const Transform old_world_transform = world_transform_;

		Transform parent_world_transform;
		if (p_parent_)
			parent_world_transform = p_parent_->world_transform_;

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

	bool GameObject::remove(const Component::TypeInfo& type, bool destroy_component)
	{
		const DynamicArray<Component*>::const_iterator it = get_iterator_to_type(type);

		const bool erased = it != components_.cend();
		if (erased)
		{
			Component* const p_component = *it;

			if (p_component && destroy_component)
			{
				p_component->on_destroy();
				p_component->destroy();
			}
				
			components_.erase(it);
		}

		return erased;
	}

	bool GameObject::is_active() const
	{
		bool active = Entity::is_active();
		const GameObject* p_ancestor = p_parent_;

		while (p_ancestor && active)
		{
			active = p_ancestor->Entity::is_active();
			p_ancestor = p_ancestor->p_parent_;
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
		const Messages::GameObjectDestroyed message(*this);
		handle(message);

		destroy_children();
		destroy_components();
	}
}
