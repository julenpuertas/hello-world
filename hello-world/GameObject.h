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

		std::weak_ptr<GameObject> p_parent_;
		DynamicArray<std::weak_ptr<GameObject> > children_;
		DynamicArray<std::weak_ptr<Component> > components_;

		void clear_components();
		void remove_child(const GameObject& child);

	public:
		template <typename ... Args> explicit GameObject(Args&& ... arguments);
		template <typename ... Args> GameObject(GameObject& parent, Args&& ... arguments);

		bool is_descendant(const GameObject& descendant) const;
		std::shared_ptr<GameObject> get_ancestor(size_t ancestor_index = 0) const;
		void set_parent(GameObject& parent);
		void remove_parent();

		const Transform& get_local_transform() const;
		void set_local_transform(const Transform& transform);

		const Transform& get_world_transform() const;
		void set_world_transform(const Transform& transform);

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
