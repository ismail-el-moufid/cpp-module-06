#include <iostream>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
	int randNum = rand() % 3;
	if (randNum == 0)
		return new A();
	else if (randNum == 1)
		return new B();
	else
		return new C();
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
}

void identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
	}
	catch (std::bad_cast &) {}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
	}
	catch (std::bad_cast &) {}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
	}
	catch (std::bad_cast &) {}
}

int main()
{

	srand(static_cast<unsigned int>(time(0)));

	Base *basePtr = generate();

	std::cout << "Identifying using pointer: ";
	identify(basePtr);

	std::cout << "Identifying using reference: ";
	identify(*basePtr);

	delete basePtr;

	return 0;
}