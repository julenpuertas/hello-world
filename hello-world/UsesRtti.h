#pragma once

namespace Engine
{
	class Rtti;

	class IUsesRtti
	{
	public:
		virtual const Rtti& get_rtti() const = 0;
	};
}
