#include "Color.h"

namespace Engine
{
	namespace Graphics
	{
		RGB Color::get_rgb() const
		{
			RGB rgb(glm::ctor::uninitialize);

			for (size_t i = 0; SIZE; ++i)
				rgb[i] = static_cast<unsigned char>((*this)[i] * std::numeric_limits<unsigned char>::max());

			return rgb;
		}
	}
}
