#pragma once
#include "MessagesListener.h"
#include "Entity.h"
#include "Transform.h"

namespace Engine
{
	class Component;

	class GameObject
		: public Entity
		, public Messages::Listener
	{
		Transform local_transform_;
		Transform world_transform_;
		Transform::Concatenator::Policy attachment_to_parent_policy_;

		std::weak_ptr<GameObject> p_parent_;
		DynamicArray<std::shared_ptr<GameObject> > children_;
		DynamicArray<std::weak_ptr<Component> > components_;

		void remove_child(const GameObject& posible_child);
		void update_children_transforms() const;

	public:
		template <typename ... Args> explicit GameObject(Args&& ... arguments);
		GameObject(const Transform& world_transform, GameObject& parent, const Transform::Concatenator::Policy& attachment_to_parent_policy);

		bool is_descendant_of(const GameObject& posible_ancestor) const;
		std::shared_ptr<GameObject> get_ancestor(size_t ancestor_index = 0) const;
		void set_parent(GameObject& new_parent);
		void remove_parent();

		const Transform& get_local_transform() const;
		void set_local_transform(const Transform& local_transform);

		const Transform& get_world_transform() const;
		void set_world_transform(const Transform& world_transform);

		const Transform::Concatenator::Policy& get_attachment_to_parent_policy() const;
		void set_attachment_to_parent_policy(const Transform::Concatenator::Policy& attachment_to_parent_policy);

		template <typename T, typename ... Args> std::shared_ptr<T> add(Args&& ... arguments);
		void remove(const Rtti& comp_type);

		template <typename T> std::shared_ptr<T> get() const;
		template <typename T> DynamicArray<std::shared_ptr<T> > get_all() const;

		bool is_active() const override;
		void set_active(bool active) override;

		void on_activation() override;
		void on_deactivation() override;

		void on_destroy() override;
	};
}

#include "GameObject.inl"
