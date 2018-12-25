#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 2> Vector<T, 2>::RIGHT(1, 0);
		template <typename T> const Vector<T, 2> Vector<T, 2>::UP(0, 1);

		template <typename T> template <typename ... Args> Vector<T, 2>::Vector(Args&& ... args)
			: VectorAdapter<Engine::Math::Vector, T, 2, glm::tvec2>(std::forward<Args>(args)...)
		{}

		template <typename T> template <typename U, glm::precision P> Vector<T, 2>::Vector(glm::tvec2<U, P>&& rhs)
			: VectorAdapter<Engine::Math::Vector, T, 2, glm::tvec2>(std::forward<glm::tvec2<U, P> >(rhs))
		{}
	}
}
