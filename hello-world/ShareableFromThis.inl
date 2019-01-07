
namespace Engine
{
	template <typename T> std::shared_ptr<T> ShareableFromThis::get_shared_this()
	{
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}

	template <typename T> std::shared_ptr<const T> ShareableFromThis::get_shared_this() const
	{
		return std::dynamic_pointer_cast<const T>(shared_from_this());
	}

	template <typename T> std::shared_ptr<T> ShareableFromThis::get_weak_this()
	{
		return std::dynamic_pointer_cast<T>(weak_from_this());
	}

	template <typename T> std::shared_ptr<const T> ShareableFromThis::get_weak_this() const
	{
		return std::dynamic_pointer_cast<const T>(weak_from_this());
	}
}
