#pragma once
#include <memory>

namespace Engine
{
	template <typename T> class ISingleton
	{
		static std::shared_ptr<T> g_p_instance;

	public:
		ISingleton(const ISingleton&) = delete;
		ISingleton& operator=ISingleton(const ISingleton&) = delete;

		static T& get_instance();
		static void destroy();
	};
}

#include "Singleton.inl"
