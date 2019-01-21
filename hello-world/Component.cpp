#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	const Rtti Component::TYPE = typeid(Component);

	Component::Component(const Component&)
	{}

	void Component::attach()
	{}

	bool Component::is_active() const
	{
		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
			return Entity::is_active() && p_owner->is_active();

		return false;
	}

	void Component::set_active(bool active)
	{
		if (Entity::is_active() == active)
			return;

		Entity::set_active(active);

		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
		{
			if (!p_owner->is_active())
				return;

			if (active)
				on_activation();

			else on_deactivation();
		}
	}

	std::shared_ptr<GameObject> Component::get_owner() const
	{
		return p_owner_.lock();
	}

	void Component::set_owner(GameObject& owner)
	{
		if (const std::shared_ptr<GameObject> p_owner = p_owner_.lock())
			p_owner->remove(get_rtti());

		p_owner_ = owner.get_this<GameObject>();

		const bool was_alive = is_alive();
		set_alive(true);

		if(was_alive)
			attach();
	}
}
