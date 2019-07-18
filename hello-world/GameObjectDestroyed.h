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
			GameObject* p_destroyed_gameobject_;

		public:

			explicit GameObjectDestroyed(GameObject& destroyed_gameobject);
			GameObject& get_destroyed_gameobject() const;
		};
	}
}
