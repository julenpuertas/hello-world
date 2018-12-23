
template <typename T> template <typename ... Args> Matrix<T, 3, 3>::Matrix(Args&& ... args)
	: glm::tmat3x3<T>(std::forward<Args>(args)...)
{}

template <typename T> template <typename U, glm::precision P> Matrix<T, 3, 3>::Matrix(glm::tmat3x3<U, P>&& rhs)
	: glm::tmat3x3<T>(std::forward<glm::tmat3x3<U, P> >(rhs))
{}
