#pragma once
#include <utility>

namespace Engine
{
	template <typename T> class ISwapable
	{
	public:
		virtual void swap(T& rhs) = 0;
	};
}

namespace std
{
	template <typename T> void swap(Engine::ISwapable<T>& lhs, Engine::ISwapable<T>& rhs);
}

#include "Swapable.inl"
