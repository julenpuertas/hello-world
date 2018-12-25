#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 4> Vector<T, 4>::RIGHT(1, 0, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::UP(0, 1, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::FORWARD(0, 0, 1, 0);

		template <typename T> template <typename ... Args> Vector<T, 4>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 4, glm::tvec4>(std::forward<Args>(args)...)
		{}

		template <typename T> template <typename U, glm::precision P> Vector<T, 4>::Vector(glm::tvec4<U, P>&& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 4, glm::tvec4>(std::forward<glm::tvec4<U, P> >(rhs))
		{}
	}
}
