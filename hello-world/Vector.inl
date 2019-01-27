#include <algorithm>
#include "Vector.h"

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

		template <typename T> template <glm::precision P> Vector<T, 2>::Vector(const glm::tvec2<T, P>& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 2, glm::tvec2>(rhs)
		{}

		template<typename T> const T& Vector<T, 2>::get_x() const
		{
			return vector_.x;
		}

		template<typename T> void Vector<T, 2>::set_x(const T& x) const
		{
			vector_.x = x;
		}

		template<typename T> const T & Vector<T, 2>::get_y() const
		{
			return vector_.y;
		}

		template<typename T> void Vector<T, 2>::set_y(const T& y) const
		{
			vector_.y = y;
		}

		template <typename T> const Vector<T, 3> Vector<T, 3>::RIGHT(1, 0, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::UP(0, 1, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::FORWARD(0, 0, 1);

		template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Vector<T, 3>::Vector(const glm::tvec3<T, P>& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(rhs)
		{}

		template<typename T> const T& Vector<T, 3>::get_x() const
		{
			return vector_.x;
		}

		template<typename T> void Vector<T, 3>::set_x(const T& x) const
		{
			vector_.x = x;
		}

		template<typename T> const T & Vector<T, 3>::get_y() const
		{
			return vector_.y;
		}

		template<typename T> void Vector<T, 3>::set_y(const T& y) const
		{
			vector_.y = y;
		}

		template<typename T> const T & Vector<T, 3>::get_z() const
		{
			return vector_.z;
		}

		template<typename T> void Vector<T, 3>::set_z(const T& z) const
		{
			vector_.z = z;
		}

		template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
		{
			return glm::cross(vector_, rhs.vector_);
		}

		template <typename T> const Vector<T, 4> Vector<T, 4>::RIGHT(1, 0, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::UP(0, 1, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::FORWARD(0, 0, 1, 0);

		template <typename T> template <typename ... Args> Vector<T, 4>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 4, glm::tvec4>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Vector<T, 4>::Vector(const glm::tvec4<T, P>& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 4, glm::tvec4>(rhs)
		{}

		template<typename T> const T& Vector<T, 4>::get_x() const
		{
			return vector_.x;
		}

		template<typename T> void Vector<T, 4>::set_x(const T& x) const
		{
			vector_.x = x;
		}

		template<typename T> const T & Vector<T, 4>::get_y() const
		{
			return vector_.y;
		}

		template<typename T> void Vector<T, 4>::set_y(const T& y) const
		{
			vector_.y = y;
		}

		template<typename T> const T & Vector<T, 4>::get_z() const
		{
			return vector_.z;
		}

		template<typename T> void Vector<T, 4>::set_z(const T& z) const
		{
			vector_.z = z;
		}

		template<typename T> const T & Vector<T, 4>::get_w() const
		{
			return vector_.w;
		}

		template<typename T> void Vector<T, 4>::set_w(const T& w) const
		{
			vector_.w = w;
		}
	}
}
