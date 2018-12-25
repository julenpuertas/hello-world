#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 4> Vector<T, 4>::RIGHT(1, 0, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::UP(0, 1, 0, 0);
		template <typename T> const Vector<T, 4> Vector<T, 4>::FORWARD(0, 0, 1, 0);

		template <typename T> template <typename ... Args> Vector<T, 4>::Vector(Args&& ... args)
			: glm::tvec4<T>(std::forward<Args>(args)...)
		{}

		template <typename T> Vector<T, 4>::Vector(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <typename T> template <typename U, glm::precision P> Vector<T, 4>::Vector(glm::tvec4<U, P>&& rhs)
			: glm::tvec4<T>(std::forward<glm::tvec4<U, P> >(rhs))
		{}

		template <typename T> T& Vector<T, 4>::operator[](size_t index)
		{
			glm::tvec4<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> const T& Vector<T, 4>::operator[](size_t index) const
		{
			const glm::tvec4<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> T& Vector<T, 4>::operator[](Axis axis)
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> const T& Vector<T, 4>::operator[](Axis axis) const
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> T Vector<T, 4>::get_square_length() const
		{
			const glm::tvec4<T>& this_ref = *this;
			return glm::length4(this_ref);
		}

		template <typename T> T Vector<T, 4>::get_length() const
		{
			const glm::tvec4<T>& this_ref = *this;
			return glm::length(this_ref);
		}

		template <typename T> T Vector<T, 4>::dot(const Vector<T, 4>& rhs) const
		{
			const glm::tvec4<T>& this_ref = *this;
			return glm::dot(this_ref, rhs);
		}

		template <typename T> void Vector<T, 4>::normalize()
		{
			const T length = this->get_length();
			if (length != static_cast<T>(0))
				*this /= length;
		}

		template <typename T> Vector<T, 4> Vector<T, 4>::get_normalized() const
		{
			Vector<T, 4> result = *this;
			result.normalize();
			return result;
		}

		template<typename T> bool Vector<T, 4>::is_all_true() const
		{
			return glm::all(*this);
		}

		template<typename T> bool Vector<T, 4>::is_zero(const T& epsilon) const
		{
			const Vector<bool, 4> result = glm::epsilonEqual(*this, glm::zero<glm::tvec4<T> >(), epsilon);
			return result.is_all_true();
		}

		template<typename T> bool Vector<T, 4>::is_equal(const Vector<T, 4>& rhs, const T& epsilon) const
		{
			const Vector<bool, 4> result = glm::epsilonEqual(*this, rhs, epsilon);
			return result.is_all_true();
		}

		template <typename T> typename Vector<T, 4>::iterator Vector<T, 4>::begin()
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 4>::iterator Vector<T, 4>::end()
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::begin() const
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::end() const
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::cbegin() const
		{
			return begin();
		}

		template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::cend() const
		{
			return end();
		}
	}
}
