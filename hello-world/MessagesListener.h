#pragma once
#include "Message.h"

/*namespace Engine
{
	namespace Messages
	{
		class Handler
		{
			bool active_;
		public:
			bool is_active() const;
			void set_active(bool active) const;

			virtual void operator()(const Message& evn) const = 0;
		};

		class Listener
		{

		public:
		};
	}
}*/

#include "MessagesListener.inl"
