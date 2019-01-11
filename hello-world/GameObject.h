#pragma once
#include "MessagesListener.h"

namespace Engine
{
	class GameObject
		: public Messages::Listener
	{
	public:
		GameObject();
		~GameObject();
	};
}

#include "GameObject.inl"
