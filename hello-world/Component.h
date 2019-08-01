#pragma once
#include <functional>
#include <typeindex>
#include "String.h"
#include "Hasheable.h"
#include "Entity.h"

namespace Engine
{
	class GameObject;

	class Component
		: public Entity
	{
		GameObject* p_owner_ = nullptr;

	protected:
		constexpr Component() = default;
		constexpr Component(const Component&);

		virtual void attach();
		virtual void on_owner_set();

	public:
		class TypeInfo
			: public IHasheable
		{
			std::type_index type_;

		public:
			TypeInfo(const std::type_info& type, const std::function<bool(const GameObject&)>& requirement_to_be_instantiated_in = nullptr);
			TypeInfo(const std::type_info& type, const TypeInfo& parent_type, const std::function<bool(const GameObject&)>& requirement_to_be_instantiated_in = nullptr);
			TypeInfo(const std::type_info& type, const std::initializer_list<TypeInfo>& parent_types, const std::function<bool(const GameObject&)>& requirement_to_be_instantiated_in = nullptr);

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

		GameObject* get_owner() const;
		void set_owner(GameObject& owner);

		virtual Component* clone() const = 0;
		virtual TypeInfo get_type_info() const = 0;
	};
}
