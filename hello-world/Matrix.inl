
namespace Engine
{
	namespace Math
	{
		template <typename T> template <typename ... Args> Matrix<T, 3, 3>::Matrix(Args&& ... args)
			: GLMMatrixWrapper<Engine::Math::Matrix, T, 3, 3, glm::tmat3x3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Matrix<T, 3, 3>::Matrix(const glm::tmat3x3<T, P>& rhs)
			: GLMMatrixWrapper<Engine::Math::Matrix, T, 3, 3, glm::tmat3x3>(rhs)
		{}

		template <typename T> template <typename ... Args> Matrix<T, 3, 4>::Matrix(Args&& ... args)
			: GLMMatrixWrapper<Engine::Math::Matrix, T, 3, 4, glm::tmat4x3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <glm::precision P> Matrix<T, 3, 4>::Matrix(const glm::tmat4x3<T, P>& rhs)
			: GLMMatrixWrapper<Engine::Math::Matrix, T, 3, 4, glm::tmat4x3>(rhs)
		{}

		template <typename T> Vector<T, 3> Matrix<T, 3, 4>::operator*(const Vector<T, 3>& rhs) const
		{
			return this->matrix_ * Vector<T, 4>(rhs, 1).vector_;
		}
	}
}
