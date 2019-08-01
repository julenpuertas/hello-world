
namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		template <typename ... Args> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::GLMMatrixWrapper(Args&& ... args)
			: GLMMatrixT<T, P>(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		Vector<T, M>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator[](size_t column_index)
		{
			GLMMatrixT<T, P>& matrix = *this;
			return *reinterpret_cast<Vector<T, M>*>(&matrix[column_index]);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		const Vector<T, M>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator[](size_t column_index) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return *reinterpret_cast<const Vector<T, M>*>(&matrix[column_index]);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-() const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return -matrix;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator+(const MatrixT<T, M, N>& rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			return matrix + rhs_matrix;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator+=(const MatrixT<T, M, N>& rhs)
		{
			GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			matrix += rhs_matrix;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-(const MatrixT<T, M, N>& rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			return matrix - rhs_matrix;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-=(const MatrixT<T, M, N>& rhs)
		{
			GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			matrix -= rhs_matrix;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		template<size_t O> MatrixT<T, M, O> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const MatrixT<T, N, O>& rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			return matrix * rhs_matrix;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*=(const MatrixT<T, M, N>& rhs)
		{
			GLMMatrixT<T, P>& matrix = *this;
			const GLMMatrixT<T, P>& rhs_matrix = rhs;
			matrix *= rhs_matrix;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const T & rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return matrix * rhs;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*=(const T & rhs)
		{
			GLMMatrixT<T, P>& matrix = *this;
			matrix *= rhs;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		Vector<T, M> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const Vector<T, N>& rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return matrix * rhs;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		T GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_trace() const
		{
			const GLMMatrixT<T, P>& matrix = *this;

			T trace(0);
			for (size_t i = 0; i < WIDTH; ++i)
				trace += matrix[i][i];

			return trace;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		T GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_determinant() const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return glm::determinant(matrix);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::scalar_product(const MatrixT<T, M, N>& rhs) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return glm::matrixCompMult(matrix, rhs);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, N, M> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_transpose() const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return glm::transpose(matrix);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_inverse() const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return glm::inverse(matrix);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_absolute() const
		{
			const MatrixT<T, M, N>& matrix = *reinterpret_cast<const MatrixT<T, M, N>*>(this);
			MatrixT<T, M, N> result(glm::ctor::uninitialize);

			for (size_t i = 0; i < WIDTH; ++i)
				result[i] = matrix[i].get_absolute();

			return result;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		bool GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::is_zero(const T& epsilon) const
		{
			return equals(glm::zero<GLMMatrixT<T, P> >(), epsilon);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		bool GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::equals(const MatrixT<T, M, N>& rhs, const T& epsilon) const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			bool equal = true;
			for (size_t i = 0; equal && i < WIDTH; ++i)
				equal &= matrix[i].equals(rhs[i], epsilon);

			return equal;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::begin()
		{
			GLMMatrixT<T, P>& matrix = *this;
			return &matrix[0][0];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::end()
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::begin() const
		{
			const GLMMatrixT<T, P>& matrix = *this;
			return &matrix[0][0];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::end() const
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		constexpr typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::cend() const
		{
			return end();
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> operator*(const T & lhs, const GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>& rhs)
		{
			return rhs * lhs;
		}
	}
}
