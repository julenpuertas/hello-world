#pragma once
#include "ShareableFromThis.h"

namespace Engine
{
	class Entity
	{
		bool active_ = true;
		bool alive_ = true;

	protected:
		Entity() = default;
		explicit Entity(const Entity&);

	public:
		virtual ~Entity() = default;

		virtual bool is_alive() const;
		void destroy();

		virtual bool is_active() const = 0;
		virtual void set_active(bool active) = 0;

		virtual void on_activation();
		virtual void on_deactivation();

		virtual void on_update();
		virtual void on_destroy();
	};
}
