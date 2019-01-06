#include "Hasheable.h"

namespace std
{
	size_t hash<Engine::IHasheable>::operator()(const Engine::IHasheable& element) const
	{
		return element.get_hash();
	}
}
