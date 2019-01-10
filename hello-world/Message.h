#pragma once

#include "Rtti.h"
#include "UsesRtti.h"

namespace Engine
{
	namespace Messages
	{
		class Message : public IUsesRtti
		{
		public:
			RTTI_DECLARATION;
		};
	}
}
