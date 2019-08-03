#include <iostream>

/*
	C++ has public members that can be accessed by anyone. It also has friend declarations, which give a function or class access to all
	members of a class. However, there is no built-in keyword to only give access to some private members. This little pattern achieves
	just that.

	See: https://stackoverflow.com/questions/3217390/clean-c-granular-friend-equivalent-answer-attorney-client-idiom/3217430#3217430
*/

template <typename T>
class PassKey
{
	friend T;
	PassKey() {}
	PassKey(PassKey const&) {}
};

struct Access;

class SomeClass
{
public:
	// Only Access can call this, as only Access can construct an object of type PassKey,
	// because by templating PassKey with Access, it can then access the private ctor.
	void DoSomething(PassKey<Access> dummy) { std::cout << "Doing something." << std::endl; }

private:
	// Private members that Access has no access to.
};

struct Access
{
	void SomeFunc() { SomeClass().DoSomething({}); }
	void EquivalentSomeFunc() { SomeClass().DoSomething(PassKey<Access>()); }
};


/*struct NoAccess
{
void SomeFunc(SomeClass& someClass) { someClass.DoSomething({}); } // compile error, only Access can call SomeClass::DoSomething.
};*/

int main()
{
	Access().SomeFunc();

	return 0;
}
