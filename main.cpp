#include <iostream>
#include <vector>
#include "OwnFunctions.h"
#include "Menu.h"
#include "Transformer.h"
#include "Weapon.h"

int main()
{
	std::vector<Transformer*> transformers;
	std::vector<Weapon*> weapons;

	int select;
	bool quit = false;
	auto miniMenu = []()->void
	{
		std::cout << "\t/////////////\n"
			"\t__Main Menu__\n"
			"\t1) Create a Transformer\n"
			"\t2) Create a Weapon\n"
			"\t3) Take Control of the Transformer\n"
			"\t4) Delete a Transformer\n"
			"\t5) Delete a Weapon\n"
			"\t6) Save to File\n"
			"\t7) Load from File\n"
			"\t8) Exit\n"
			"\t/////////////\n";
	};

	miniMenu();
	while (!quit)
	{
		std::cout << "\tEnter (0 is menu call): ";
		select = own::setChoice(0, 8);
		switch (select)
		{
		case 0:
			miniMenu();
			break;
		case 1:
			transformers.push_back(createTransformer(weapons));
			break;
		case 2:
			weapons.push_back(createWeapon());
			break;
		case 3:
			controlTransformer(transformers, weapons);
			break;
		case 4:
			deleteTransformer(transformers);
			break;
		case 5:
			deleteWeapon(weapons, transformers);
			break;
		case 6:
			saveToFile(transformers, weapons);
			break;
		case 7:
			loadFromFile(transformers, weapons);
			break;
		case 8:
			quit = true;
			break;
		}
	}

	return 0;
}
