#pragma once

namespace Engine
{
	class Updateable
	{
		bool active_ = true;
		bool alive_ = false;

	public:
		Updateable();
		~Updateable();

		bool is_alive() const;
		void set_alive(bool alive);

		bool is_active() const;
		void set_active(bool active);

		virtual void on_activation();
		virtual void on_deactivation();

		virtual void on_update();
		virtual void on_destroy();
	};
}
