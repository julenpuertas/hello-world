#pragma once
#include "UsesRtti.h"
#include <memory>

namespace Engine
{
	class GameObject;

	class Component : public IUsesRtti
	{
		bool active_ = true;
		bool alive_ = false;
		std::weak_ptr<GameObject> p_owner_;

	public:
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
