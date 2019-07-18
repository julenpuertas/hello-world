#pragma once
#include <memory>
#include <typeindex>
#include "DynamicArray.h"
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

			MultiHashMap<std::type_index, std::unique_ptr<Handler> > private_handlers_;
			DynamicArray<Pair<std::type_index, Handler*> > public_handlers_;

			static void add_public_handler(const std::type_info& type, std::unique_ptr<Handler>&& p_handler);
			template <typename T, typename InstanceT> static Callback<T> make_callback(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);
			void handle(const std::type_info& type, const Message& evn) const;

		public:
			~Listener();

			template <typename T> void handle(const T& message) const;

			template <typename T> Handler* add_private_handler(const Callback<T>& callback);
			template <typename T, typename LambdaT> Handler* add_private_handler(LambdaT&& callback);
			template <typename T> Handler* add_private_handler(const GlobalFunction<T>& callback);
			template <typename T, typename InstanceT> Handler* add_private_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);

			template <typename T> Handler* add_public_handler(const Callback<T>& callback);
			template <typename T, typename LambdaT> Handler* add_public_handler(LambdaT&& callback);
			template <typename T> Handler* add_public_handler(const GlobalFunction<T>& callback);
			template <typename T, typename InstanceT> Handler* add_public_handler(InstanceT& instance, const MemberFunction<T, InstanceT>& callback);
		};

		void dispatch(const std::type_info& type, const Message& message);
		template <typename T> void dispatch(const T& message);
	}
}

#include "MessagesListener.inl"
