#include <iostream>
#include <vector>

/*
	Execute some functionality before and/or after each function call on an object by using the "->" operator overload.

	See https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Execute-Around_Pointer
*/

template<typename T>
class SizeVisualizer
{
	class Scoped
	{
	public:
		Scoped(T* data) : data_(data)
		{
			std::cout << "Size before: " << data_->size() << std::endl;
		}

		T* operator -> ()
		{
			return data_;
		}

		~Scoped()
		{
			std::cout << "Size after: " << data_->size() << std::endl;
		}
	private:
		T* data_;
	};

public:
	SizeVisualizer(T* data) : data_(data) {}

	Scoped operator -> ()
	{
		return Scoped(data_);
	}

private:
	T* data_;
};

int main()
{
	std::vector<int> vi;
	SizeVisualizer vi_vis(&vi);

	vi_vis->push_back(10);
	vi_vis.operator->().operator->()->push_back(10);	// equivalent to line above as defined in C++98 standard §13.5.6/1
	vi_vis->push_back(20);
}