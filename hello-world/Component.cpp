#include "Component.h"

namespace Engine
{
	const Rtti Component::TYPE = typeid(Component);

	Component::Component(const Component &)
	{}

	bool Component::is_alive() const
	{
		return alive_;
	}

	void Component::set_alive(bool alive)
	{
		alive_ = alive;
	}

	bool Component::is_active() const
	{
		return false;
	}

	void Component::set_active(bool active)
	{
	}

	std::shared_ptr<GameObject> Component::get_owner() const
	{
		return p_owner_.lock();
	}

	void Component::set_owner(GameObject & owner)
	{

	}

	void Component::on_activation()
	{}

	void Component::on_deactivation()
	{}

	void Component::on_update()
	{}

	void Component::on_destroy()
	{}

	void Component::attach()
	{}
}
