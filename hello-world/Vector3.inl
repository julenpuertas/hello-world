#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 3> Vector<T, 3>::RIGHT(1, 0, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::UP(0, 1, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::FORWARD(0, 0, 1);

		template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
			: glm::tvec3<T>(std::forward<Args>(args)...)
		{}

		template <typename T> Vector<T, 3>::Vector(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <typename T> template <typename U, glm::precision P> Vector<T, 3>::Vector(glm::tvec3<U, P>&& rhs)
			: glm::tvec3<T>(std::forward<glm::tvec3<U, P> >(rhs))
		{}

		template <typename T> T& Vector<T, 3>::operator[](size_t index)
		{
			glm::tvec3<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> const T& Vector<T, 3>::operator[](size_t index) const
		{
			const glm::tvec3<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> T& Vector<T, 3>::operator[](Axis axis)
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> const T& Vector<T, 3>::operator[](Axis axis) const
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> T Vector<T, 3>::get_square_length() const
		{
			const glm::tvec3<T>& this_ref = *this;
			return glm::length2(this_ref);
		}

		template <typename T> T Vector<T, 3>::get_length() const
		{
			const glm::tvec3<T>& this_ref = *this;
			return glm::length(this_ref);
		}

		template <typename T> T Vector<T, 3>::dot(const Vector<T, 3>& rhs) const
		{
			const glm::tvec3<T>& this_ref = *this;
			return glm::dot(this_ref, rhs);
		}

		template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
		{
			return glm::cross(*this, rhs);
		}

		template <typename T> void Vector<T, 3>::normalize()
		{
			const T length = this->get_length();
			if (length != static_cast<T>(0))
				*this /= length;
		}

		template <typename T> Vector<T, 3> Vector<T, 3>::get_normalized() const
		{
			Vector<T, 3> result = *this;
			result.normalize();
			return result;
		}

		template<typename T> bool Vector<T, 3>::is_all_true() const
		{
			return glm::all(*this);
		}

		template<typename T> bool Vector<T, 3>::is_zero(const T& epsilon) const
		{
			const Vector<bool, 3> result = glm::epsilonEqual(*this, glm::zero<glm::tvec3<T> >(), epsilon);
			return result.is_all_true();
		}

		template<typename T> bool Vector<T, 3>::is_equal(const Vector<T, 3>& rhs, const T& epsilon) const
		{
			const Vector<bool, 3> result = glm::epsilonEqual(*this, rhs, epsilon);
			return result.is_all_true();
		}

		template <typename T> typename Vector<T, 3>::iterator Vector<T, 3>::begin()
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 3>::iterator Vector<T, 3>::end()
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::begin() const
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::end() const
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::cbegin() const
		{
			return begin();
		}

		template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::cend() const
		{
			return end();
		}
	}
}
