#pragma once
#include "UsesRtti.h"
#include "Rtti.h"
#include "ShareableFromThis.h"
#include "Clonable.h"

namespace Engine
{
	class GameObject;

	class Component
		: public ShareableFromThis
		, public IUsesRtti
		, public IClonable
	{
		bool active_ = true;
		bool alive_ = false;
		std::weak_ptr<GameObject> p_owner_;

	public:
		RTTI_DECLARATION;

		Component() = default;
		Component(const Component&);

		bool is_alive() const;
		void set_alive(bool alive);

		bool is_active() const;
		void set_active(bool active);

		std::shared_ptr<GameObject> get_owner() const;
		void set_owner(GameObject& owner);

		virtual void on_activation();
		virtual void on_deactivation();

		virtual void on_update();
		virtual void on_destroy();

		virtual void attach();
	};
}
