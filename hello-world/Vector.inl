#include <algorithm>

template<typename T, size_t N> Vector<T, N>::Vector(glm::ctor)
{}

template<typename T, size_t N> template <typename U> Vector<T, N>::Vector(const U& default_value)
{
	this->fill(static_cast<T>(default_value));
}

template<typename T, size_t N> Vector<T, N> Vector<T, N>::operator+(const Vector& rhs) const
{
	Vector<T, N> result(glm::uninitialize);
	std::transform(this->cbegin(), this->cend(), rhs.cbegin(), result.begin(), std::plus<T>());
	return result;
}
