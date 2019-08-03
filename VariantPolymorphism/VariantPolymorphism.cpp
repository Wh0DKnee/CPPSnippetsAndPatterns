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

struct Circle 
{ 
	void Draw() { std::cout << "I'm a circle." << std::endl; } 
};

struct Rectangle 
{ 
	void Draw() { std::cout << "I'm a rectangle." << std::endl; } 
};

using ShapeVariant = std::variant<Circle, Rectangle>;

int main() 
{
	std::vector<ShapeVariant> vars = { Circle(), Rectangle() };

	for (auto& v : vars) 
	{
		std::visit(Overloaded{
			[](Circle& c) { c.Draw(); },
			[](Rectangle& r) { r.Draw(); },
			}, v);
	}

	return 0;
}