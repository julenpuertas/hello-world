
namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		template <typename ... Args> ExtendedGLMVector<VectorT, T, N, BaseT, P>::ExtendedGLMVector(Args&& ... args)
			: BaseT<T, P>(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		ExtendedGLMVector<VectorT, T, N, BaseT, P>::ExtendedGLMVector(Axis axis)
		{
			(*this)[axis] = static_cast<T>(1);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T& ExtendedGLMVector<VectorT, T, N, BaseT, P>::operator[](size_t index)
		{
			BaseT<T, P>& this_ref = *this;
			return this_ref[index];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		const T& ExtendedGLMVector<VectorT, T, N, BaseT, P>::operator[](size_t index) const
		{
			const BaseT<T, P>& this_ref = *this;
			return this_ref[index];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T& ExtendedGLMVector<VectorT, T, N, BaseT, P>::operator[](Axis axis)
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		const T& ExtendedGLMVector<VectorT, T, N, BaseT, P>::operator[](Axis axis) const
		{
			return (*this)[static_cast<size_t>(axis)];
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T ExtendedGLMVector<VectorT, T, N, BaseT, P>::get_square_length() const
		{
			const BaseT<T, P>& this_ref = *this;
			return glm::length2(this_ref);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T ExtendedGLMVector<VectorT, T, N, BaseT, P>::get_length() const
		{
			const BaseT<T, P>& this_ref = *this;
			return glm::length(this_ref);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		T ExtendedGLMVector<VectorT, T, N, BaseT, P>::dot(const VectorT<T, N>& rhs) const
		{
			const BaseT<T, P>& this_ref = *this;
			return glm::dot(this_ref, rhs);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		void ExtendedGLMVector<VectorT, T, N, BaseT, P>::normalize()
		{
			const T length = get_length();
			if (length != static_cast<T>(0))
				*this /= length;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		VectorT<T, N> ExtendedGLMVector<VectorT, T, N, BaseT, P>::get_normalized() const
		{
			ExtendedGLMVector<VectorT, T, N, BaseT, P> result = *this;
			result.normalize();
			return VectorT<T, N>(result);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		bool ExtendedGLMVector<VectorT, T, N, BaseT, P>::is_all_true() const
		{
			return glm::all(*this);
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		bool ExtendedGLMVector<VectorT, T, N, BaseT, P>::is_zero(const T& epsilon) const
		{
			const VectorT<bool, N> result = glm::epsilonEqual(*this, glm::zero<BaseT<T, P> >(), epsilon);
			return result.is_all_true();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		bool ExtendedGLMVector<VectorT, T, N, BaseT, P>::is_equal(const VectorT<T, N>& rhs, const T& epsilon) const
		{
			const ExtendedGLMVector<VectorT, bool, N, BaseT> result = glm::epsilonEqual(*this, rhs, epsilon);
			return result.is_all_true();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::begin()
		{
			return &this->x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::end()
		{
			return begin() + SIZE;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::const_iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::begin() const
		{
			return &this->x;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::const_iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::end() const
		{
			return begin() + SIZE;
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::const_iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P>
		typename ExtendedGLMVector<VectorT, T, N, BaseT, P>::const_iterator ExtendedGLMVector<VectorT, T, N, BaseT, P>::cend() const
		{
			return end();
		}
	}
}
