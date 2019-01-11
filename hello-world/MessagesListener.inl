
namespace Engine
{
	namespace Messages
	{
		template<typename T> Listener::THandler<T>::THandler(const Callback<T>& callback)
			: callback_(callback)
		{}

		template<typename T> void Listener::THandler<T>::operator()(const Message& message) const
		{
			if (active_ && callback_)
				callback_(dynamic_cast<const T&>(message));
		}

		template<typename T, typename InstanceT> Listener::Callback<T> Listener::make_callback(InstanceT& instance, const MemberFunction<T, InstanceT>& callback)
		{
			return Callback<T>([&instance, callback](const T& message)
			{
				(instance.*callback)(message);
			});
		}

		template<typename T> std::weak_ptr<Handler> Listener::add_private_handler(const Callback<T>& callback)
		{
			const std::shared_ptr<Handler> p_handler = std::make_shared<THandler<T> >(callback);
			private_handlers_.emplace(&T::TYPE, p_handler);
			return p_handler;
		}

		template<typename T, typename LambaT> std::weak_ptr<Handler> Listener::add_private_handler(LambaT&& callback)
		{
			return add_private_handler(Callback<T>(std::forward<LambaT>(callback)));
		}

		template<typename T> std::weak_ptr<Handler> Listener::add_private_handler(const GlobalFunction<T>& callback)
		{
			return add_private_handler(Callback<T>(callback));
		}

		template<typename T, typename InstanceT> std::weak_ptr<Handler> Listener::add_private_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback)
		{
			return add_private_handler(make_callback(instance, callback));
		}

		template<typename T> std::weak_ptr<Handler> Listener::add_public_handler(const Callback<T>& callback)
		{
			const std::shared_ptr<Handler> p_handler = std::make_shared<THandler<T> >(callback);
			add_public_handler(T::TYPE, p_handler);

			const std::weak_ptr<Handler> wp_handler = p_handler;
			public_handlers_.emplace_back(&T::TYPE, wp_handler);
			return wp_handler;
		}

		template<typename T, typename LambdaT> std::weak_ptr<Handler> Listener::add_public_handler(LambdaT&& callback)
		{
			return add_public_handler(Callback<T>(std::forward<LambdaT>(callback)));
		}

		template<typename T> std::weak_ptr<Handler> Listener::add_public_handler(const GlobalFunction<T>& callback)
		{
			return add_public_handler(Callback<T>(callback));
		}

		template<typename T, typename InstanceT> std::weak_ptr<Handler> Listener::add_public_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback)
		{
			return add_public_handler(make_callback(instance, callback));
		}
	}
}
