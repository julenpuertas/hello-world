#include "MessagesListener.h"

namespace
{
	Engine::MultiHashMap<const Engine::Rtti*, std::shared_ptr<Engine::Messages::Handler> > g_public_handlers;

	void deliver(const Engine::MultiHashMap<const Engine::Rtti*, std::shared_ptr<Engine::Messages::Handler> >& handlers, const Engine::Messages::Message& message)
	{
		using namespace Engine;
		using namespace Engine::Messages;

		for (Pair<MultiHashMap<const Rtti*, std::shared_ptr<Handler> >::const_iterator> range = handlers.equal_range(&message.get_rtti()); range.first != range.second; ++range.first)
		{
			if (const std::shared_ptr<Handler>& p_handler = range.first->second)
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

		void Listener::add_public_handler(const Rtti& type, const std::shared_ptr<Handler>& p_handler)
		{
			g_public_handlers.emplace(&type, p_handler);
		}

		Listener::~Listener()
		{
			for (const Pair<const Rtti* const, std::weak_ptr<Handler> >& type_handler_pair : public_handlers_)
			{
				const std::shared_ptr<Handler> p_handler = type_handler_pair.second.lock();
				if (!p_handler)
					continue;

				for (Pair<MultiHashMap<const Rtti*, std::shared_ptr<Handler> >::const_iterator> range = g_public_handlers.equal_range(type_handler_pair.first); range.first != range.second; ++range.first)
				{
					const MultiHashMap<const Rtti*, std::shared_ptr<Handler> >::const_iterator it = std::find_if(range.first, range.second, [&p_handler](const Pair<const Rtti* const, std::shared_ptr<Handler> >& element)
					{
						return p_handler == element.second;
					});

					if (it != range.second)
						g_public_handlers.erase(it);
				}
			}
		}

		void Listener::handle(const Message& message) const
		{
			deliver(private_handlers_, message);
		}

		void dispatch(const Message& message)
		{
			deliver(g_public_handlers, message);
		}
	}
}
