#include <variant>
#include <iostream>
#include <vector>

/*
	Achieving polymorphism without inheritance and virtual functions. Requires C++17 as it uses std::variant
	and class template argument deduction.

	See https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17
*/

template<class... Ts> struct Overloaded : Ts...
{
	using Ts::operator()...;
};

template<class... Ts> Overloaded(Ts...)->Overloaded<Ts...>;

struct Circle {};
struct Rectangle {};

using ShapeVariant = std::variant<Circle, Rectangle>;

int main() 
{
	std::vector<ShapeVariant> shapes = { Circle(), Rectangle() };

	for (auto& shape : shapes) 
	{
		std::visit(Overloaded{
			[](Circle& c) { std::cout << "I'm a circle." << std::endl; },
			[](Rectangle& r) { std::cout << "I'm a rectangle." << std::endl; },
			}, shape);
	}

	return 0;
}