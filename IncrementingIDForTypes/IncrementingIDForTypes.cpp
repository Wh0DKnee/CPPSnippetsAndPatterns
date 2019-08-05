#include <iostream>

/*
	Generates an incrementing unique ID for types.

	See https://github.com/Wh0DKnee/ezECS/blob/master/ezECS/Component.h for example usage.
*/

struct BaseIDGenerator
{
protected:
	static inline unsigned int incrementing_id = 0; // requires C++17 for static inline variable
};

// Assigns each type that this is templated with a unique id.
template<typename T>
struct IDGenerator : BaseIDGenerator
{
	static unsigned int GetID()
	{
		static unsigned int id = incrementing_id++;
		return id;
	}
};

struct SomeType {};
struct OtherType{};

int main()
{
	std::cout << IDGenerator<SomeType>::GetID() << std::endl;	// 0 
	std::cout << IDGenerator<OtherType>::GetID() << std::endl;	// 1
	std::cout << IDGenerator<SomeType>::GetID() << std::endl;	// still 0
}