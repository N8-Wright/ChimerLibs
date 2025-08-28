#include "EqualTests.hpp"
#include "NotEqualTests.hpp"

int main(int argc, const char** argv)
{
	return EqualTests.Run(argc, argv) +
		NotEqualTests.Run(argc, argv);
}