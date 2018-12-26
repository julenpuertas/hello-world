
namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		template <typename ... Args> ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::ExtendedGLMMatrix(Args&& ... args)
			: BaseT<T, P>(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::get_trace() const
		{
			const BaseT<T, P>& this_ref = *this;

			T trace(0);
			for (size_t i = 0; i < WIDTH; ++i)
				trace += this_ref[i][i];

			return trace;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::get_determinant() const
		{
			return glm::determinant(*this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		MatrixT<T, M, N> ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::scalar_product(const MatrixT<T, M, N>& rhs) const
		{
			return glm::matrixCompMult(*this, rhs);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		MatrixT<T, N, M> ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::get_transpose() const
		{
			return glm::transpose(*this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		MatrixT<T, M, N> ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::get_inverse() const
		{
			return glm::inverse(*this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		MatrixT<T, M, N> ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::get_absolute() const
		{
			BaseT<T, P> result;

			for (size_t i = 0; i < WIDTH; ++i)
				result[i] = glm::abs(x[i]);

			return result;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		bool ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::is_zero(const T& epsilon) const
		{
			return is_equal(glm::zero<BaseT<T, P> >(), epsilon);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		bool ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::is_equal(const MatrixT<T, M, N>& rhs, const T& epsilon) const
		{
			const BaseT<T, P>& this_ref = *this;

			bool equal = true;
			for (size_t i = 0; equal && i < WIDTH; ++i)
				equal &= glm::all(glm::epsilonEqual(this_ref[i], rhs[i], epsilon));

			return equal;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::begin()
		{
			return &(*this)[0][0];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::end()
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::const_iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::begin() const
		{
			return &(*this)[0][0];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::const_iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::end() const
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::const_iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::const_iterator ExtendedGLMMatrix<MatrixT, T, M, N, BaseT, P>::cend() const
		{
			return end();
		}
	}
}
