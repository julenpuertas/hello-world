#pragma once
#include "ShareableFromThis.h"
#include "Clonable.h"

namespace Engine
{
	class Entity
		: public ShareableFromThis
		, public IClonable
	{
		bool active_ = true;
		bool alive_ = true;

	protected:
		Entity() = default;
		explicit Entity(const Entity&);

	public:
		bool is_alive() const;
		void set_alive(bool alive);

		virtual bool is_active() const = 0;
		virtual void set_active(bool active) = 0;

		virtual void on_activation();
		virtual void on_deactivation();

		virtual void on_update();
		virtual void on_destroy();
	};
}
