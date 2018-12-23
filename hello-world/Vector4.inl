#include <glm/gtx/norm.hpp>

template <typename T> template <typename ... Args> Vector<T, 4>::Vector(Args&& ... args)
	: glm::tvec4<T>(std::forward<Args>(args)...)
{}

template <typename T> template <typename U, glm::precision P> Vector<T, 4>::Vector(glm::tvec4<U, P>&& rhs)
	: glm::tvec4<T>(std::forward<glm::tvec4<U, P> >(rhs))
{}

template <typename T> T Vector<T, 4>::square_modulus() const
{
	const glm::tvec4<T>& this_ref = *this;
	return glm::length2(this_ref);
}

template <typename T> T Vector<T, 4>::modulus() const
{
	const glm::tvec4<T>& this_ref = *this;
	return glm::length(this_ref);
}

template <typename T> T Vector<T, 4>::dot(const Vector<T, 4>& rhs) const
{
	const glm::tvec4<T>& this_ref = *this;
	return glm::dot(this_ref, rhs);
}

template <typename T> Vector<T, 4> Vector<T, 4>::cross(const Vector<T, 4>& rhs) const
{
	const glm::tvec4<T>& this_ref = *this;
	return glm::cross(this_ref, rhs);
}

template <typename T> typename Vector<T, 4>::iterator Vector<T, 4>::begin()
{
	return &this->x;
}

template <typename T> typename Vector<T, 4>::iterator Vector<T, 4>::end()
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::begin() const
{
	return &this->x;
}

template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::end() const
{
	return begin() + this->length();
}

template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::cbegin() const
{
	return begin();
}

template <typename T> typename Vector<T, 4>::const_iterator Vector<T, 4>::cend() const
{
	return end();
}
