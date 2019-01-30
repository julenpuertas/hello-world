#pragma once
#include <memory>
#include "Message.h"

namespace Engine
{
	class GameObject;

	namespace Messages
	{
		class GameObjectDestroyed
			: public Message
		{
			std::weak_ptr<GameObject> p_destroyed_gameobject_;

		public:

			explicit GameObjectDestroyed(GameObject& destroyed_gameobject);
			std::shared_ptr<GameObject> get_destroyed_gameobject() const;
		};
	}
}
