#include "GameObject.h"
#include "GameObjectDestroyed.h"

namespace Engine
{
	namespace Messages
	{
		GameObjectDestroyed::GameObjectDestroyed(GameObject& destroyed_object)
			: p_destroyed_gameobject_(&destroyed_object)
		{}

		GameObject& GameObjectDestroyed::get_destroyed_gameobject() const
		{
			return *p_destroyed_gameobject_;
		}
	}
}
