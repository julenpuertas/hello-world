#pragma once
#include <memory>

namespace Engine
{
	class ShareableFromThis : public std::enable_shared_from_this<ShareableFromThis>
	{
	public:
		template <typename T> std::shared_ptr<T> get_shared_this();
		template <typename T> std::shared_ptr<const T> get_shared_this() const;
		template <typename T> std::shared_ptr<T> get_weak_this();
		template <typename T> std::shared_ptr<const T> get_weak_this() const;
	};
}

#include "ShareableFromThis.inl"
