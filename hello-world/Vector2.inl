#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 2> Vector<T, 2>::RIGHT(1, 0);
		template <typename T> const Vector<T, 2> Vector<T, 2>::UP(0, 1);

		template <typename T> template <typename ... Args> Vector<T, 2>::Vector(Args&& ... args)
			: glm::tvec2<T>(std::forward<Args>(args)...)
		{}

		template <typename T> Vector<T, 2>::Vector(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <typename T> template <typename U, glm::precision P> Vector<T, 2>::Vector(glm::tvec2<U, P>&& rhs)
			: glm::tvec2<T>(std::forward<glm::tvec2<U, P> >(rhs))
		{}

		template <typename T> T& Vector<T, 2>::operator[](size_t index)
		{
			glm::tvec2<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> const T& Vector<T, 2>::operator[](size_t index) const
		{
			const glm::tvec2<T>& this_ref = *this;
			return this_ref[index];
		}

		template <typename T> T& Vector<T, 2>::operator[](Axis axis)
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> const T& Vector<T, 2>::operator[](Axis axis) const
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <typename T> T Vector<T, 2>::get_square_length() const
		{
			const glm::tvec2<T>& this_ref = *this;
			return glm::length2(this_ref);
		}

		template <typename T> T Vector<T, 2>::get_length() const
		{
			const glm::tvec2<T>& this_ref = *this;
			return glm::length(this_ref);
		}

		template <typename T> T Vector<T, 2>::dot(const Vector<T, 2>& rhs) const
		{
			const glm::tvec2<T>& this_ref = *this;
			return glm::dot(this_ref, rhs);
		}

		template <typename T> void Vector<T, 2>::normalize()
		{
			const T length = this->get_length();
			if (length != static_cast<T>(0))
				*this /= length;
		}

		template <typename T> Vector<T, 2> Vector<T, 2>::get_normalized() const
		{
			Vector<T, 2> result = *this;
			result.normalize();
			return result;
		}

		template<typename T> bool Vector<T, 2>::is_all_true() const
		{
			return glm::all(*this);
		}

		template<typename T> bool Vector<T, 2>::is_zero(const T& epsilon) const
		{
			const Vector<bool, 2> result = glm::epsilonEqual(*this, glm::zero<glm::tvec2<T> >(), epsilon);
			return result.is_all_true();
		}

		template<typename T> bool Vector<T, 2>::is_equal(const Vector<T, 2>& rhs, const T& epsilon) const
		{
			const Vector<bool, 2> result = glm::epsilonEqual(*this, rhs, epsilon);
			return result.is_all_true();
		}

		template <typename T> typename Vector<T, 2>::iterator Vector<T, 2>::begin()
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 2>::iterator Vector<T, 2>::end()
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::begin() const
		{
			return &this->x;
		}

		template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::end() const
		{
			return begin() + SIZE;
		}

		template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::cbegin() const
		{
			return begin();
		}

		template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::cend() const
		{
			return end();
		}
	}
}
