#include <glm/gtx/norm.hpp>

template <typename T> template <typename ... Args> Vector<T, 2>::Vector(Args&& ... args)
	: glm::tvec2<T>(std::forward<Args>(args)...)
{}

template <typename T> template <typename U, glm::precision P> Vector<T, 2>::Vector(glm::tvec2<U, P>&& rhs)
	: glm::tvec2<T>(std::forward<glm::tvec2<U, P> >(rhs))
{}

template <typename T> T Vector<T, 2>::square_modulus() const
{
	const glm::tvec2<T>& this_ref = *this;
	return glm::length2(this_ref);
}

template <typename T> T Vector<T, 2>::modulus() const
{
	const glm::tvec2<T>& this_ref = *this;
	return glm::length(this_ref);
}

template <typename T> T Vector<T, 2>::dot(const Vector<T, 2>& rhs) const
{
	const glm::tvec2<T>& this_ref = *this;
	return glm::dot(this_ref, rhs);
}

template <typename T> typename Vector<T, 2>::iterator Vector<T, 2>::begin()
{
	return &this->x;
}

template <typename T> typename Vector<T, 2>::iterator Vector<T, 2>::end()
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::begin() const
{
	return &this->x;
}

template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::end() const
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::cbegin() const
{
	return begin();
}

template <typename T> typename Vector<T, 2>::const_iterator Vector<T, 2>::cend() const
{
	return end();
}
