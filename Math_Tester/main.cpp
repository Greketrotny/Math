#include <iostream>
#include <chrono>

#include "vec3.h"
#include "constants.h"
#include "angle.h"

using namespace Math;

void PrintVec(const Math::vec3f& v)
{
	std::cout << "[" << v.x << ", " << v.y << ", " << v.z << "]" << std::endl;
}

int main()
{
	vec3f a(1.0f, 0.0f, 4.0f);
	vec3f b(1.0f, 0.0f, 4.0f);
	PrintVec(a);
	PrintVec(b);
	std::cout << (a != b);

	std::cin.get();

	return 0;
}