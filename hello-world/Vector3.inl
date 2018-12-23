#include <glm/gtx/norm.hpp>

template <typename T> template <typename ... Args> Vector<T, 3>::Vector(Args&& ... args)
	: glm::tvec3<T>(std::forward<Args>(args)...)
{}

template <typename T> template <typename U, glm::precision P> Vector<T, 3>::Vector(glm::tvec3<U, P>&& rhs)
	: glm::tvec3<T>(std::forward<glm::tvec3<U, P> >(rhs))
{}

template <typename T> T Vector<T, 3>::square_modulus() const
{
	const glm::tvec3<T>& this_ref = *this;
	return glm::length2(this_ref);
}

template <typename T> T Vector<T, 3>::modulus() const
{
	const glm::tvec3<T>& this_ref = *this;
	return glm::length(this_ref);
}

template <typename T> T Vector<T, 3>::dot(const Vector<T, 3>& rhs) const
{
	const glm::tvec3<T>& this_ref = *this;
	return glm::dot(this_ref, rhs);
}

template <typename T> Vector<T, 3> Vector<T, 3>::cross(const Vector<T, 3>& rhs) const
{
	const glm::tvec3<T>& this_ref = *this;
	return glm::cross(this_ref, rhs);
}

template <typename T> typename Vector<T, 3>::iterator Vector<T, 3>::begin()
{
	return &this->x;
}

template <typename T> typename Vector<T, 3>::iterator Vector<T, 3>::end()
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::begin() const
{
	return &this->x;
}

template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::end() const
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::cbegin() const
{
	return begin();
}

template <typename T> typename Vector<T, 3>::const_iterator Vector<T, 3>::cend() const
{
	return end();
}
