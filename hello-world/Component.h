#pragma once
#include "UsesRtti.h"
#include "Rtti.h"
#include "Entity.h"

namespace Engine
{
	class GameObject;

	class Component
		: public Entity
		, public IUsesRtti
	{
		std::weak_ptr<GameObject> p_owner_;

	protected:
		Component() = default;
		Component(const Component&);

		virtual void attach();
		virtual void on_owner_set();

	public:
		RTTI_DECLARATION;

		virtual void assign(const Component& rhs);

		bool is_active() const;
		void set_active(bool active);

		std::shared_ptr<GameObject> get_owner() const;
		void set_owner(GameObject& owner);

		virtual std::shared_ptr<Component> clone() const = 0;
	};
}
