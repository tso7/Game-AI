#include <iostream>
#include "SimpleBT.h"
#include "DetailedBT.h"

int main(void)
{
	int choice;
	std::cout << "1. Simple BT" << std::endl;
	std::cout << "2. Detailed BT" << std::endl;
	std::cout << "Choose a Behavior Tree implmentation: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1: 
		return Simple::main();
	case 2:
		return Detailed::main();
	default:
		std::cout << "\nInvalid option!";
	}
	return 0;
}