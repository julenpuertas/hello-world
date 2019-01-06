
namespace Engine
{
	namespace Math
	{
		template <typename T> template <typename ... Args> Matrix<T, 3, 3>::Matrix(Args&& ... args)
			: ExtendedGLMMatrix<Engine::Math::Matrix, T, 3, 3, glm::tmat3x3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Matrix<T, 3, 3>::Matrix(glm::tmat3x3<T, P>&& rhs)
			: ExtendedGLMMatrix<Engine::Math::Matrix, T, 3, 3, glm::tmat3x3>(std::forward<glm::tmat3x3<T, P> >(rhs))
		{}

		template <typename T> template <typename ... Args> Matrix<T, 3, 4>::Matrix(Args&& ... args)
			: ExtendedGLMMatrix<Engine::Math::Matrix, T, 3, 4, glm::tmat4x3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Matrix<T, 3, 4>::Matrix(glm::tmat4x3<T, P>&& rhs)
			: ExtendedGLMMatrix<Engine::Math::Matrix, T, 3, 4, glm::tmat4x3>(std::forward<glm::tmat4x3<T, P> >(rhs))
		{}

		template <typename T> Vector<T, 3> Matrix<T, 3, 4>::operator*(const Vector<T, 3>& rhs) const
		{
			return *this * Vector<T, 4>(rhs, 1);
		}
	}
}
