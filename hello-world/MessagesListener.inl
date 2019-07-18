#include "MessagesListener.h"

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

		template<typename T> void Listener::handle(const T & message) const
		{
			handle(typeid(T), message);
		}

		template<typename T> Handler* Listener::add_private_handler(const Callback<T>& callback)
		{
			std::unique_ptr<Handler> p_handler = std::make_unique<THandler<T> >(callback);
			Handler* rp_handler = p_handler.get();
			private_handlers_.emplace(typeid(T), std::move(p_handler));
			return rp_handler;
		}

		template<typename T, typename LambdaT> Handler* Listener::add_private_handler(LambdaT&& callback)
		{
			return add_private_handler(Callback<T>(std::forward<LambdaT>(callback)));
		}

		template<typename T> Handler* Listener::add_private_handler(const GlobalFunction<T>& callback)
		{
			return add_private_handler(Callback<T>(callback));
		}

		template<typename T, typename InstanceT> Handler* Listener::add_private_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback)
		{
			return add_private_handler(make_callback(instance, callback));
		}

		template<typename T> Handler* Listener::add_public_handler(const Callback<T>& callback)
		{
			std::unique_ptr<Handler> p_handler = std::make_unique<THandler<T> >(callback);
			Handler* rp_handler = p_handler.get();
			const std::type_info& type = typeid(T);

			public_handlers_.emplace_back(type, rp_handler);
			add_public_handler(type, p_handler);
			return rp_handler;
		}

		template<typename T, typename LambdaT> Handler* Listener::add_public_handler(LambdaT&& callback)
		{
			return add_public_handler(Callback<T>(std::forward<LambdaT>(callback)));
		}

		template<typename T> Handler* Listener::add_public_handler(const GlobalFunction<T>& callback)
		{
			return add_public_handler(Callback<T>(callback));
		}

		template<typename T, typename InstanceT> Handler* Listener::add_public_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback)
		{
			return add_public_handler(make_callback(instance, callback));
		}

		template<typename T> void dispatch(const T& message)
		{
			dispatch(typeid(T), message);
		}
	}
}
