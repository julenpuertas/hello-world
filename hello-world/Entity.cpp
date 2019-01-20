#include "Entity.h"

namespace Engine
{
	Entity::Entity(bool alive)
		: alive_(alive)
	{}

	Entity::Entity(const Entity&)
	{}

	bool Entity::is_alive() const
	{
		return alive_;
	}

	void Entity::set_alive(bool alive)
	{
		alive_ = alive;
	}

	bool Entity::is_active() const
	{
		return active_;
	}

	void Entity::set_active(bool active)
	{
		active_ = active;
	}

	void Entity::on_activation()
	{}

	void Entity::on_deactivation()
	{}

	void Entity::on_update()
	{}

	void Entity::on_destroy()
	{}
}
