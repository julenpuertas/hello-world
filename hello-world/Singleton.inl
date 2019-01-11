
namespace Engine
{
	template <typename T> std::shared_ptr<T> ISingleton<T>::g_p_instance = std::make_shared<T>();

	template<typename T> T & ISingleton<T>::get_instance()
	{
		return *g_p_instance;
	}

	template<typename T> void ISingleton<T>::destroy()
	{
		g_p_instance.reset();
	}
}
