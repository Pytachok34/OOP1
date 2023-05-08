#include "List.h"
#include <fstream>
int main()
{
	std::ifstream file("input.txt"),file2("input.txt");
	LIST l,l2;
	l.create_by_queue(file);
	l.print();
	std::cout << '\n';
	l2.create_by_stack(file2);
	l2.print();
	std::cout << '\n';
	LIST l3 = l - l2;
	std::cout <<l3<< '\n';
	std::cin.get();
	return 0;
}