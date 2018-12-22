#include <SDL/SDL.h>
#include "Vector.h"

int main(int argc, char* argv[])
{
	Vector<float, 5> vector1;
	Vector<float, 5> vector2;
	Vector<float, 5> vector3 = vector1 + vector2;

	return 0;
}
