#pragma once
#include <memory>

namespace Engine
{
	class ShareableFromThis : public std::enable_shared_from_this<ShareableFromThis>
	{
	public:
		virtual ~ShareableFromThis() = default;
		template <typename T> std::shared_ptr<T> get_this();
		template <typename T> std::shared_ptr<const T> get_this() const;
	};
}

#include "ShareableFromThis.inl"
