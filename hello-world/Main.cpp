#include <SDL/SDL.h>
#include "Matrix3x4.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Matrix<float, 3, 4> m;
	m[3] = Vector<float, 3>(1.f);
	Vector<float, 3> v(4.f);
	Vector<float, 3> v2 = m * v;

	return 0;
}
