#include "Transform.h"
#include "DynamicArray.h"
#include "String.h"
#include "Rtti.h"
#include "Component.h"
#include <iostream>
#include "Hasheable.h"

class Foo : std::enable_shared_from_this<Foo>
{
public:
	void on_int(const Foo&)
	{

	}
};

void gfn(const Foo&)
{

}

template <typename ... Args> std::function<void(const Foo&)> make_fn(Args&& ... args)
{
	return std::function<void(const Foo&)>(std::forward<Args>(args) ...);
}

int main(int argc, char* argv[])
{
	using namespace Engine;

	Foo foo;

	std::function<void(const Foo&)> fn = make_fn(std::bind(&Foo::on_int, &foo, std::placeholders::_1));
	std::function<void(const Foo&)> fn2 = make_fn(&gfn);
	std::function<void(const Foo&)> fn3 = make_fn([](const Foo&)
	{
	});

	fn(foo);
	fn2(foo);
	fn3(foo);

	return 0;
}
