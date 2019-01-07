#pragma once

#include "Rtti.h"
#include "UsesRtti.h"

namespace Engine
{
	class Message : public IUsesRtti
	{
	public:
		RTTI_DECLARATION;
	};
}

