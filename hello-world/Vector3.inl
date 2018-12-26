
namespace Engine
{
	namespace Math
	{
		template <typename T> const Vector<T, 3> Vector<T, 3>::RIGHT(1, 0, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::UP(0, 1, 0);
		template <typename T> const Vector<T, 3> Vector<T, 3>::FORWARD(0, 0, 1);

		template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<Args>(args)...)
		{}

		template <typename T> template <typename U, glm::precision P> Vector<T, 3>::Vector(glm::tvec3<U, P>&& rhs)
			: ExtendedGLMVector<Engine::Math::Vector, T, 3, glm::tvec3>(std::forward<glm::tvec3<U, P> >(rhs))
		{}

		template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
		{
			return glm::cross(*this, rhs);
		}
	}
}
