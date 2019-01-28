#pragma once
#include "Vector.h"

namespace Engine
{
	namespace Graphics
	{
		using RGB = Math::Vector<unsigned char, 3>;

		class Color : public FVector3
		{
		public:
			template <typename ... Args> explicit Color(Args&& ... args);
			RGB get_rgb() const;
		};
	}
}

#include "Color.inl"
