#include <algorithm>

namespace Engine
{
	namespace Math
	{
		template<typename T, size_t N> Vector<T, N>::Vector(glm::ctor)
		{}

		template<typename T, size_t N> template <typename U> Vector<T, N>::Vector(const U& default_value)
		{
			this->fill(static_cast<T>(default_value));
		}

		template<typename T, size_t N> Vector<T, N> Vector<T, N>::operator+(const Vector& rhs) const
		{
			Vector<T, N> result(glm::uninitialize);
			std::transform(this->cbegin(), this->cend(), rhs.cbegin(), result.begin(), std::plus<T>());
			return result;
		}

		template <typename T> const Vector<T, 2> Vector<T, 2>::RIGHT(1, 0);
		template <typename T> const Vector<T, 2> Vector<T, 2>::UP(0, 1);

		template <typename T> template <typename ... Args> Vector<T, 2>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 2, glm::tvec2>(std::forward<Args>(args)...)
		{}

		template <typename T> template <typename U, glm::precision P> Vector<T, 2>::Vector(glm::tvec2<U, P>&& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 2, glm::tvec2>(std::forward<glm::tvec2<U, P> >(rhs))
		{}

		template <typename T> const Vector<T, 3> Vector<T, 3>::RIGHT(1, 0, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::UP(0, 1, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::FORWARD(0, 0, 1);

		template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <typename U, glm::precision P> Vector<T, 3>::Vector(glm::tvec3<U, P>&& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<glm::tvec3<U, P> >(rhs))
		{}

		template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
		{
			return glm::cross(*this, rhs);
		}

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
