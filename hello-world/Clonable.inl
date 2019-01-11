
namespace Engine
{
	template<typename T> std::shared_ptr<T> IClonable::get_clone_shared() const
	{
		return std::make_shared<T>(dynamic_cast<const T&>(*this));
	}

	template<typename T> std::unique_ptr<T> IClonable::get_clone_unique() const
	{
		return std::make_unique<T>(dynamic_cast<const T&>(*this));
	}
}
