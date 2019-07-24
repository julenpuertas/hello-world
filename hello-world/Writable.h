#pragma once
#include <ostream>
#include "String.h"

namespace Engine
{
	namespace IO
	{
		class IWritable
		{
		public:
			virtual void write(std::ostream& os) const = 0;
			String to_string() const;
			String operator+(const String& rhs) const;
		};

		std::ostream& operator<<(std::ostream& lhs, const IWritable& rhs);
		String& operator+=(String& lhs, const IWritable& rhs);
		String operator+(const String& lhs, const IWritable& rhs);
	}
}
