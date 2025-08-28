#include "test.hpp"

namespace chimer::test
{
}

class Test : Chimer::Test::TestClass<Test>
{
	CHIMER_CLASS_BOILERPLATE(Test);

protected:
	void Foo()
	{

	}
};

CHIMER_REGISTER_TEST_CLASS(Test);