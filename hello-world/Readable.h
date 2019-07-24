#pragma once
#include <istream>

namespace Engine
{
	namespace IO
	{
		class IReadable
		{
		public:
			virtual void read(std::istream& is) = 0;
		};
	}
}
