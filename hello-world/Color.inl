
namespace Engine
{
	namespace Graphics
	{
		template <typename ... Args> Color::Color(Args&& ... args)
			: FVector3(std::forward<Args>(args) ...)
		{}
	}
}
