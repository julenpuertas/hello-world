#include <algorithm>
#include "Vector.h"

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 2> Vector<T, 2>::RIGHT(1, 0);
		template <typename T> const Vector<T, 2> Vector<T, 2>::UP(0, 1);

		template <typename T> template <typename ... Args> Vector<T, 2>::Vector(Args&& ... args)
			: GLMVectorWrapper<Engine::Math::Vector, T, 2, glm::tvec2>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Vector<T, 2>::Vector(const glm::tvec2<T, P>& rhs)
			: GLMVectorWrapper<Engine::Math::Vector, T, 2, glm::tvec2>(rhs)
		{}

		//template<typename T> const T& Vector<T, 2>::get_x() const
		//{
		//	return this->vector_.x;
		//}

		//template<typename T> void Vector<T, 2>::set_x(const T& x) const
		//{
		//	this->vector_.x = x;
		//}

		//template<typename T> const T & Vector<T, 2>::get_y() const
		//{
		//	return this->vector_.y;
		//}

		//template<typename T> void Vector<T, 2>::set_y(const T& y) const
		//{
		//	this->vector_.y = y;
		//}

		template <typename T> const Vector<T, 3> Vector<T, 3>::RIGHT(1, 0, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::UP(0, 1, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::FORWARD(0, 0, 1);

		template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
			: GLMVectorWrapper<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Vector<T, 3>::Vector(const glm::tvec3<T, P>& rhs)
			: GLMVectorWrapper<Engine::Math::Vector, T, 3, glm::tvec3>(rhs)
		{}

		//template<typename T> const T& Vector<T, 3>::get_x() const
		//{
		//	return this->vector_.x;
		//}

		//template<typename T> void Vector<T, 3>::set_x(const T& x) const
		//{
		//	this->vector_.x = x;
		//}

		//template<typename T> const T & Vector<T, 3>::get_y() const
		//{
		//	return this->vector_.y;
		//}

		//template<typename T> void Vector<T, 3>::set_y(const T& y) const
		//{
		//	this->vector_.y = y;
		//}

		//template<typename T> const T & Vector<T, 3>::get_z() const
		//{
		//	return this->vector_.z;
		//}

		//template<typename T> void Vector<T, 3>::set_z(const T& z) const
		//{
		//	this->vector_.z = z;
		//}

		template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
		{
			return glm::cross(this->vector_, rhs.vector_);
		}

		template <typename T> const Vector<T, 4> Vector<T, 4>::RIGHT(1, 0, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::UP(0, 1, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::FORWARD(0, 0, 1, 0);

		template <typename T> template <typename ... Args> Vector<T, 4>::Vector(Args&& ... args)
			: GLMVectorWrapper<Engine::Math::Vector, T, 4, glm::tvec4>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Vector<T, 4>::Vector(const glm::tvec4<T, P>& rhs)
			: GLMVectorWrapper<Engine::Math::Vector, T, 4, glm::tvec4>(rhs)
		{}

		//template<typename T> const T& Vector<T, 4>::get_x() const
		//{
		//	return this->vector_.x;
		//}

		//template<typename T> void Vector<T, 4>::set_x(const T& x) const
		//{
		//	this->vector_.x = x;
		//}

		//template<typename T> const T & Vector<T, 4>::get_y() const
		//{
		//	return this->vector_.y;
		//}

		//template<typename T> void Vector<T, 4>::set_y(const T& y) const
		//{
		//	this->vector_.y = y;
		//}

		//template<typename T> const T & Vector<T, 4>::get_z() const
		//{
		//	return this->vector_.z;
		//}

		//template<typename T> void Vector<T, 4>::set_z(const T& z) const
		//{
		//	this->vector_.z = z;
		//}

		//template<typename T> const T & Vector<T, 4>::get_w() const
		//{
		//	return this->vector_.w;
		//}

		//template<typename T> void Vector<T, 4>::set_w(const T& w) const
		//{
		//	this->vector_.w = w;
		//}
	}
}
