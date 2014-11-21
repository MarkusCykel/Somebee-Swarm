#include "Entity.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Wall derp{std::make_pair(10,10)};
	
	std::cout << (derp.get_position()).first;
}