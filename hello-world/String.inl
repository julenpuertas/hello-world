
namespace Engine
{
	template<typename ...Args> String::String(Args&& ...arguments)
		: std::string(std::forward<Args>(arguments) ...)
	{}
}
