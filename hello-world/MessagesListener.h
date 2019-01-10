#pragma once
#include "HashMap.h"
#include "Pair.h"
#include "Message.h"

namespace Engine
{
	namespace Messages
	{
		class Handler
		{
			bool active_ = true;

		public:
			bool is_active() const;
			void set_active(bool active);

			virtual void operator()(const Message& message) const = 0;
		};

		class Listener
		{
			template <typename T> using Callback = std::function<void(const T&)>;
			template <typename T> using GlobalFunction = void(*)(const T&);
			template <typename T, typename InstanceT> using MemberFunction = void (InstanceT::*)(const T&);

			template <typename T> class THandler : public Handler
			{
				Callback<T> callback_;

			public:

				explicit THandler(const Callback<T>& callback);
				void operator()(const Message& message) const override;
			};

			MultiHashMap<const Rtti*, std::shared_ptr<Handler> > private_handlers_;
			DynamicArray<Pair<const Rtti*, std::weak_ptr<Handler> > > public_handlers_;

			static void listen_publicly(const Rtti& type, const std::shared_ptr<Handler>& p_handler);
			template <typename T, typename InstanceT> static Callback<T> make_callback(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);

		public:
			~Listener();
			void handle(const Message& evn) const;

			template <typename T> std::weak_ptr<Handler> listen_privately(const Callback<T>& callback);
			template <typename T, typename LambaT> std::weak_ptr<Handler> listen_privately(LambaT&& callback);
			template <typename T> std::weak_ptr<Handler> listen_privately(const GlobalFunction<T>& callback);
			template <typename T, typename InstanceT> std::weak_ptr<Handler> listen_privately(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);

			template <typename T> std::weak_ptr<Handler> listen_publicly(const Callback<T>& callback);
			template <typename T, typename LambaT> std::weak_ptr<Handler> listen_publicly(LambaT&& callback);
			template <typename T> std::weak_ptr<Handler> listen_publicly(const GlobalFunction<T>& callback);
			template <typename T, typename InstanceT> std::weak_ptr<Handler> listen_publicly(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);
		};

		void dispatch(const Message& message);
	}
}

#include "MessagesListener.inl"
