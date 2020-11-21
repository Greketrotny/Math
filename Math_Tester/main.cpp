#include <iostream>
#include <chrono>

#include "vec3.h"
#include "Constants.h"
#include "angle.h"


struct MyStruct
{
	int i;
};


using namespace Math;

int main()
{
	//MyStruct s;
	//int i = (int)s;


	angle<Math::angle_unit::deg, float> d = 90.0_degf;

	angle<Math::angle_unit::rad, float> r;
	r = d;

	std::cout << r.value();

	std::cin.get();

	getchar();
	return 0;
}