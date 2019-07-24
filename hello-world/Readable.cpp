#include "Readable.h"

namespace Engine
{
	namespace IO
	{
		std::istream& operator>>(std::istream& lhs, IReadable& rhs)
		{
			rhs.read(lhs);
			return lhs;
		}
	}
}
