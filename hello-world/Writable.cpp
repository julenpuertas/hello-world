#include <sstream>
#include "Writable.h"

namespace Engine
{
	String IWritable::to_string() const
	{
		std::ostringstream ss;
		ss << *this;
		return ss.str();
	}

	String IWritable::operator+(const String& rhs) const
	{
		return to_string() + rhs;
	}

	std::ostream& operator<<(std::ostream& lhs, const IWritable& rhs)
	{
		rhs.write(lhs);
		return lhs;
	}

	String& operator+=(String& lhs, const IWritable& rhs)
	{
		return lhs += rhs.to_string();
	}

	String operator+(const String& lhs, const IWritable& rhs)
	{
		return lhs + rhs.to_string();
	}
}
