#pragma once
#include <memory>

namespace Engine
{
	class IClonable
	{
	public:
		template <typename T> std::shared_ptr<T> get_clone_shared() const;
		template <typename T> std::unique_ptr<T> get_clone_unique() const;
	};
}

#include "Clonable.inl"
