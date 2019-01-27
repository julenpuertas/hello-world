#include <glm/gtx/norm.hpp>
#include "GLMVectorWrapper.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		template <typename ... Args> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::GLMVectorWrapper(Args&& ... args)
			: vector_(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::GLMVectorWrapper(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](size_t index)
		{
			return vector_[index];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](size_t index) const
		{
			return vector_[index];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](Axis axis)
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](Axis axis) const
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator==(const VectorT<T, N>& rhs) const
		{
			return vector_ == rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator!=(const VectorT<T, N>& rhs) const
		{
			return !(*this == rhs);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-() const
		{
			return -vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+(const VectorT<T, N>& rhs) const
		{
			return vector_ + rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+=(const VectorT<T, N>& rhs)
		{
			vector_ += rhs.vector_;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+(const T & rhs) const
		{
			return vector_ + rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+=(const T & rhs)
		{
			vector_ += rhs;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-(const VectorT<T, N>& rhs) const
		{
			return vector_ - rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-=(const VectorT<T, N>& rhs)
		{
			vector_ -= rhs.vector_;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-(const T & rhs) const
		{
			return vector_ - rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-=(const T & rhs)
		{
			vector_ -= rhs;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*(const VectorT<T, N>& rhs) const
		{
			return vector_ * rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*=(const VectorT<T, N>& rhs)
		{
			vector_ *= rhs.vector_;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*(const T & rhs) const
		{
			return vector_ * rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*=(const T & rhs)
		{
			vector_ *= rhs;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/(const VectorT<T, N>& rhs) const
		{
			return vector_ / rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/=(const VectorT<T, N>& rhs)
		{
			vector_ /= rhs.vector_;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/(const T & rhs) const
		{
			return vector_ / rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/=(const T & rhs)
		{
			vector_ /= rhs;
			return *reinterpret_cast<const VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_square_length() const
		{
			return glm::length2(vector_);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_length() const
		{
			return glm::length(vector_);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::dot(const VectorT<T, N>& rhs) const
		{
			return glm::dot(vector_, rhs.vector_);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		void GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::normalize()
		{
			const T length = get_length();
			if (length != static_cast<T>(0))
				*this /= length;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_normalized() const
		{
			VectorT<T, N> result(vector_);
			result.normalize();
			return result;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_absolute() const
		{
			return glm::abs(vector_);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::is_all_true() const
		{
			return glm::all(vector_);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::is_zero(const T& epsilon) const
		{
			return is_equal(glm::zero<GLMVectorT<T, P> >(), epsilon);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::equals(const VectorT<T, N>& rhs, const T& epsilon) const
		{
			return glm::all(glm::epsilonEqual(vector_, rhs.vector_, epsilon));
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::begin()
		{
			return &vector_.x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::end()
		{
			return begin() + N;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::begin() const
		{
			return &vector_.x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::end() const
		{
			return begin() + N;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::cend() const
		{
			return end();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorT<T, P> operator+(const GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs + rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const GLMVectorT<T, P>& operator+=(GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs += rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorT<T, P> operator-(const GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs - rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const GLMVectorT<T, P>& operator-=(GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs -= rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorT<T, P> operator*(const GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs * rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const GLMVectorT<T, P>& operator*=(GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs *= rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorT<T, P> operator/(const GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs / rhs.vector_;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const GLMVectorT<T, P>& operator/=(GLMVectorT<T, P>& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return lhs /= rhs.vector_;
		}
	}
}
