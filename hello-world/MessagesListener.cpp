#include "MessagesListener.h"

namespace
{
	Engine::MultiHashMap<std::type_index, std::unique_ptr<Engine::Messages::Handler> > g_public_handlers;

	void deliver(const Engine::MultiHashMap<std::type_index, std::unique_ptr<Engine::Messages::Handler> >& handlers, const std::type_info& type, const Engine::Messages::Message& message)
	{
		using namespace Engine;
		using namespace Engine::Messages;

		for (Pair<MultiHashMap<std::type_index, std::unique_ptr<Handler> >::const_iterator> range = handlers.equal_range(type); range.first != range.second; ++range.first)
		{
			if (const std::unique_ptr<Handler>& p_handler = range.first->second)
				(*p_handler)(message);
		}
	}
}

namespace Engine
{
	namespace Messages
	{
		bool Handler::is_active() const
		{
			return active_;
		}

		void Handler::set_active(bool active)
		{
			active_ = active;
		}

		void Listener::add_public_handler(const std::type_info& type, std::unique_ptr<Handler>&& p_handler)
		{
			g_public_handlers.emplace(type, std::move(p_handler));
		}

		void Listener::handle(const std::type_info& type, const Message& message) const
		{
			deliver(private_handlers_, type, message);
		}

		Listener::~Listener()
		{
			for (const Pair<const std::type_index, Handler*>& type_handler_pair : public_handlers_)
			{
				const Pair<MultiHashMap<std::type_index, std::unique_ptr<Handler> >::const_iterator> range = g_public_handlers.equal_range(type_handler_pair.first);
				const MultiHashMap<std::type_index, std::unique_ptr<Handler> >::const_iterator it = std::find_if(range.first, range.second, [&type_handler_pair](const Pair<const std::type_index, std::unique_ptr<Handler> >& element)
				{
					return type_handler_pair.second == element.second.get();
				});

				if (it != range.second)
					g_public_handlers.erase(it);
			}
		}

		void dispatch(const std::type_info& type, const Message& message)
		{
			deliver(g_public_handlers, type, message);
		}
	}
}
