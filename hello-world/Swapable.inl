
namespace std
{
	template <typename T> void swap(Engine::ISwapable<T>& lhs, T& rhs)
	{
		lhs.swap(rhs);
	}
}
