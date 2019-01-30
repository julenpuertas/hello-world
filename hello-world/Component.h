#pragma once
#include <typeindex>
#include "String.h"
#include "Entity.h"
#include "Hasheable.h"

namespace Engine
{
	class GameObject;

	class Component
		: public Entity
	{
		std::weak_ptr<GameObject> p_owner_;

	protected:
		Component() = default;
		Component(const Component&);

		virtual void attach();
		virtual void on_owner_set();

	public:
		class TypeInfo
			: public IHasheable
		{
			std::type_index type_;

		public:
			TypeInfo(const std::type_info& type, const Requirement<GameObject>& requirement_to_be_instantiated_in = nullptr);
			TypeInfo(const std::type_info& type, const TypeInfo& parent_type, const Requirement<GameObject>& requirement_to_be_instantiated_in = nullptr);
			TypeInfo(const std::type_info& type, const std::initializer_list<TypeInfo>& parent_types, const Requirement<GameObject>& requirement_to_be_instantiated_in = nullptr);

			bool operator==(const TypeInfo& rhs) const;
			bool operator!=(const TypeInfo& rhs) const;
			bool operator<(const TypeInfo& rhs) const;
			bool operator>(const TypeInfo& rhs) const;
			bool operator<=(const TypeInfo& rhs) const;
			bool operator>=(const TypeInfo& rhs) const;

			String::View get_name() const;
			bool is_same_or_derived_from(const std::type_info& other_type) const;
			bool can_be_instantiated_in(const GameObject& gameobject) const;

			size_t get_hash() const override;
		};

		virtual void assign(const Component& rhs);

		bool is_alive() const override;

		bool is_active() const;
		void set_active(bool active);

		std::shared_ptr<GameObject> get_owner() const;
		void set_owner(GameObject& owner);

		virtual std::shared_ptr<Component> clone() const = 0;
		virtual TypeInfo get_type_info() const = 0;
	};
}
