#include "Hasheable.h"

namespace std
{
	size_t hash<Engine::IHasheable>::operator()(const Engine::IHasheable& hasheable) const
	{
		return hasheable.get_hash();
	}
}
