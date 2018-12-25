
namespace Engine
{
	template<typename T> Pair<T> make_pair(const T & value)
	{
		return Pair<T>(value, value);
	}
}
