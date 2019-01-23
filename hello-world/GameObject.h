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
		Transform world_transform_;
		Transform::Concatenator::Policy attachment_to_parent_policy_;

		std::weak_ptr<GameObject> p_parent_;
		DynamicArray<std::shared_ptr<GameObject> > children_;
		DynamicArray<std::weak_ptr<Component> > components_;

		void for_each_component(const std::function<void(Component&)>& predicate) const;
		void for_each_child(const std::function<void(GameObject&)>& predicate) const;
		void remove_child(const GameObject& posible_child);
		Transform get_local_transform(const Transform& parent_world_transform) const;
		void update_children_transforms(const Transform& old_world_transform) const;
		DynamicArray<std::weak_ptr<Component> >::const_iterator get_iterator_to_type(const Rtti& type);
		void destroy_children() const;
		void destroy_components() const;
		bool remove_parent_if_it_has();
		void add_to_global_gameobject_list();
		void remove_from_global_gameobject_list();

	public:
		static bool update_or_destroy(const std::shared_ptr<GameObject>& p_gameobject);

		enum class Uninitialize : Byte
		{};

		GameObject(Uninitialize);
		template <typename ... Args> explicit GameObject(Args&& ... arguments);
		GameObject(const Transform& world_transform, GameObject& parent, const Transform::Concatenator::Policy& attachment_to_parent_policy = Transform::Concatenator::Policy());
		GameObject(GameObject& parent, const Transform& local_transform, const Transform::Concatenator::Policy& attachment_to_parent_policy = Transform::Concatenator::Policy());
		GameObject(const GameObject& rhs) = delete;

		GameObject& operator=(const GameObject& rhs);
		GameObject& operator=(GameObject&& rhs);

		bool is_descendant_of(const GameObject& posible_ancestor) const;
		std::shared_ptr<GameObject> get_ancestor(size_t ancestor_index = 0) const;
		void set_parent(GameObject& new_parent);
		void remove_parent();

		Transform get_local_transform() const;
		void set_local_transform(const Transform& local_transform);

		const Transform& get_world_transform() const;
		void set_world_transform(const Transform& world_transform);

		const Transform::Concatenator::Policy& get_attachment_to_parent_policy() const;
		void set_attachment_to_parent_policy(const Transform::Concatenator::Policy& attachment_to_parent_policy);

		template <typename T, typename ... Args> std::shared_ptr<T> add(Args&& ... arguments);
		bool remove(const Rtti& type);

		template <typename T> std::shared_ptr<T> get() const;
		template <typename T> DynamicArray<std::shared_ptr<T> > get_all() const;

		bool is_active() const override;
		void set_active(bool active) override;

		void on_activation() override;
		void on_deactivation() override;

		void on_update() override;
		void on_destroy() override;
	};
}

#include "GameObject.inl"
