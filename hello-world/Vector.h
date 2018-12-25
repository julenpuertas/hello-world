#pragma once

#include "Array.h"
#include <glm/gtc/vec1.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T, size_t N> class Vector : public Array<T, N>
		{
			explicit Vector(glm::ctor uninitialize_flag);

		public:
			template <typename U> explicit Vector(const U& default_value = U());
			Vector operator+(const Vector& rhs) const;
		};
	}
}

#include "Vector.inl"
