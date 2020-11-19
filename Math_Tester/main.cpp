#include <iostream>
#include <chrono>

#include "vec3.h"
#include "Constants.h"
#include "angle.h"



using namespace Math;

int main()
{
	angle<rad> a(constants<float>::pi / 2.0f);
	angle<deg> b(120.0f);
	angle<rev> c(0.75f);

	angle<rad> result = c + a + b;

	std::cout << "Sinus " << result.value() << " rad = " << sinf(result.value());

	std::cin.get();

	getchar();
	return 0;
}