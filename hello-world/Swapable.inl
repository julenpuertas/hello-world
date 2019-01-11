
namespace std
{
	template <typename T> void swap(Engine::ISwapable<T>& lhs, Engine::ISwapable<T>& rhs)
	{
		lhs.swap(dynamic_cast<T&>(rhs));
	}
}
