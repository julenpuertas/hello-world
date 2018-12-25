#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

int main(int argc, char* argv[])
{
	{
		Engine::Math::Vector<float, 2> v(Engine::Math::Axis::X);
		Engine::Math::Vector<float, 2> v1 = v + v;
		v1[0];
		v1[Engine::Math::Axis::X];
	}
	{
		Engine::Math::Vector<float, 3> v2(Engine::Math::Axis::X);
		Engine::Math::Vector<float, 3> v3 = v2 + v2;
		v3[0];
		v3[Engine::Math::Axis::X];
	}
	{
		Engine::Math::Vector<float, 4> v2(Engine::Math::Axis::X);
		Engine::Math::Vector<float, 4> v3 = v2 + v2;
		v3[0];
		v3[Engine::Math::Axis::X];
	}
	return 0;
}
