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

	public:
		RTTI_DECLARATION;

		Component();
		Component(const Component&);

		bool is_active() const;
		void set_active(bool active);

		std::shared_ptr<GameObject> get_owner() const;
		void set_owner(GameObject& owner);

		virtual void on_activation();
		virtual void on_deactivation();

		virtual void attach();
	};
}
