#include <glm/gtx/norm.hpp>

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		template <typename ... Args> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::GLMVectorWrapper(Args&& ... args)
			: GLMVectorT<T, P>(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::GLMVectorWrapper(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](size_t index)
		{
			GLMVectorT<T, P>& vector = *this;
			return vector[index];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		const T& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator[](size_t index) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return vector[index];
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
			const GLMVectorT<T, P>& vector = *this;
			return vector == rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator!=(const VectorT<T, N>& rhs) const
		{
			return !(*this == rhs);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-() const
		{
			const GLMVectorT<T, P>& vector = *this;
			return -vector;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+(const VectorT<T, N>& rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<T, P>& rhs_vector = rhs;
			return vector + rhs_vector;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P> template <typename U>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+=(const VectorT<U, N>& rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<U, P>& rhs_vector = rhs;
			vector += rhs_vector;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+(const T & rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return vector + rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator+=(const T & rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			vector += rhs;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-(const VectorT<T, N>& rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<T, P>& rhs_vector = rhs;
			return vector - rhs_vector;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P> template <typename U>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-=(const VectorT<U, N>& rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<U, P>& rhs_vector = rhs;
			vector -= rhs_vector;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-(const T & rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return vector - rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator-=(const T & rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			vector -= rhs;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*(const VectorT<T, N>& rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<T, P>& rhs_vector = rhs;
			return vector * rhs_vector;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P> template <typename U>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*=(const VectorT<U, N>& rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<U, P>& rhs_vector = rhs;
			vector *= rhs_vector;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*(const T & rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return vector * rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator*=(const T & rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			vector *= rhs;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/(const VectorT<T, N>& rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<T, P>& rhs_vector = rhs;
			return vector / rhs_vector;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P> template <typename U>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/=(const VectorT<U, N>& rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<U, P>& rhs_vector = rhs;
			vector /= rhs_vector;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/(const T & rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return vector / rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N>& GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::operator/=(const T & rhs)
		{
			GLMVectorT<T, P>& vector = *this;
			vector /= rhs;
			return *reinterpret_cast<VectorT<T, N>*>(this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_square_length() const
		{
			const GLMVectorT<T, P>& vector = *this;
			return glm::length2(vector);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_length() const
		{
			const GLMVectorT<T, P>& vector = *this;
			return glm::length(vector);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		T GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::dot(const VectorT<T, N>& rhs) const
		{
			const GLMVectorT<T, P>& vector = *this;
			const GLMVectorT<T, P>& rhs_vector = rhs;
			return glm::dot(vector, rhs_vector);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		void GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::normalize()
		{
			const T square_length = get_square_length();
			if (square_length != static_cast<T>(0))
				*this /= sqrt(square_length);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_normalized() const
		{
			VectorT<T, N> result(*this);
			result.normalize();
			return result;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::get_absolute() const
		{
			const GLMVectorT<T, P>& vector = *this;
			return glm::abs(vector);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::is_all_true() const
		{
			const GLMVectorT<T, P>& vector = *this;
			return glm::all(vector);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::is_zero(const T& epsilon) const
		{
			return equals(glm::zero<GLMVectorT<T, P> >(), epsilon);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		bool GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::equals(const VectorT<T, N>& rhs, const T& epsilon) const
		{
			const GLMVectorT<T, P>& vector = *this;
			return glm::all(glm::epsilonEqual(vector, rhs, epsilon));
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::begin()
		{
			return &this->x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::end()
		{
			return begin() + N;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::begin() const
		{
			return &this->x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::end() const
		{
			return begin() + N;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		constexpr typename GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::const_iterator GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>::cend() const
		{
			return end();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator+(const T & lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return rhs + lhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator-(const T & lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			const GLMVectorT<T, P>& glm_rhs = rhs;
			return lhs - glm_rhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator*(const T & lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			return rhs * lhs;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator/(const T & lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs)
		{
			const GLMVectorT<T, P>& glm_rhs = rhs;
			return lhs / glm_rhs;
		}
	}
}
