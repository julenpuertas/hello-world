#include <SDL/SDL.h>
#include "Vector2.h"
#include "Vector3.h"
#include <iostream>

int main(int argc, char* argv[])
{
	{
		Vector<float, 2> default_constructed;

		Vector<float, 2> vectora(5.f);
		const Vector<float, 2> vectorb(3.f);
		Vector<float, 2> vectorc = vectora + vectorb;
		float a = vectora.dot(vectorc);
		float b = vectora.modulus();
		float c = vectora.square_modulus();

		auto d = vectora.begin();
		auto e = vectora.end();

		auto f = vectorb.begin();
		auto g = vectorb.end();

		auto h = vectora.cbegin();
		auto i = vectora.cend();
	}
	{
		Vector<float, 3> default_constructed;

		Vector<float, 3> vectora(5.f);
		const Vector<float, 3> vectorb(3.f);
		Vector<float, 3> vectorc = vectora + vectorb;
		float a = vectora.dot(vectorc);
		float b = vectora.modulus();
		float c = vectora.square_modulus();

		auto j = vectora.cross(vectorb);
		auto k = 3.f * vectora;

		auto d = vectora.begin();
		auto e = vectora.end();

		auto f = vectorb.begin();
		auto g = vectorb.end();

		auto h = vectora.cbegin();
		auto i = vectora.cend();
	}
	return 0;
}
