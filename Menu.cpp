#include "Menu.h"

using altPtr = std::shared_ptr<Altform>;

Transformer* createTransformer(const std::vector<Weapon*>& weapons)
{
	char fact;
	std::string name, speciality;
	int initialPower, mind, powerNativeGun, altform;
	auto* alts = new std::vector<altPtr>;

	std::cout << "/////////////////////\nCreating Transformer:\n/////////////////////\nSelect the faction (a/d): ";
	std::cin >> fact;
	while (fact != 'a' && fact != 'd')
	{
		std::cout << "Incorrect Input. Please Repeat: ";
		std::cin >> fact;
	}

	while (true)
	{
		std::cout << "Name: ";
		std::cin >> name;
		std::string* temp = new std::string();
		getline(std::cin, *temp);
		name += *temp;
		delete temp;
		bool again = false;
		for (auto n : namesOfTransformers)
			if (n == name)
			{
				std::cout << "This transformer is already created" << std::endl;
				again = true;
				break;
			}
		if (again)
			continue;
		namesOfTransformers.emplace(name);
		break;
	}

	std::cout << "Speciality: ";
	std::cin >> speciality;
	std::cout << "Initial Power (10-100): ";
	initialPower = own::setChoice(10, 100);
	std::cout << "Mind (0-100): ";
	mind = own::setChoice(0, 100);

	char* choice = new char;
	std::cout << "Has Native Gun (y/n): ";
	std::cin >> *choice;
	while (*choice != 'y' && *choice != 'n')
	{
		std::cout << "Incorrect Input. Please Repeat: ";
		std::cin >> *choice;
	}
	if (*choice == 'y')
	{
		std::cout << "Power of Native Gun (3-10): ";
		powerNativeGun = own::setChoice(3, 10);
	}
	else
		powerNativeGun = 0;
	delete choice;

	std::cout << "Altforms:\n1. Car\n2. SportCar\n3. Motorcycle\n4. Truck\n5. Pickup\n6. Tank\n7. Plane\n8. Military Fighter\n9. Dump Truck\n10. Cybertron Machine\nSelect an Altform: ";
	altform = own::setChoice(1, 10);
	addAltform(alts, altform);
	auto* used = new std::shared_ptr<std::array<int, 10>>(new std::array<int, 10>);
	int* countArray = new int(0);
	(**used)[(*countArray)++] = altform;
	while (altform != 0)
	{
		std::cout << "Add More (0 is no): ";
		altform = own::setChoice(0, 10);
		if (altform == 0)
			break;
		bool repeat = false;
		for (auto i : **used)
			if (i == altform)
			{
				std::cout << "You already chose this altform. Select another." << std::endl;
				repeat = true;
				break;;
			}
		if (repeat)
			continue;
		addAltform(alts, altform);
		(**used)[(*countArray)++] = altform;
	}
	std::vector<altPtr> v = *alts;
	delete used;
	delete countArray;
	delete alts;

	auto endFoo = [=](Weapon* const www)->Transformer*
	{
		if (www)
		{
			if (fact == 'a')
			{
				std::cout << "Autobot " << name << " created" << std::endl;
				return new Autobot(name, 100, 100, v, speciality, initialPower, mind, powerNativeGun, www);
			}
			else if (fact == 'd')
			{
				std::cout << "Decepticon " << name << " created" << std::endl;
				return new Decepticon(name, 100, 100, v, speciality, initialPower, mind, powerNativeGun, www);
			}
		}
		if (fact == 'a')
		{
			std::cout << "Autobot " << name << " created" << std::endl;
			return new Autobot(name, 100, 100, v, speciality, initialPower, mind, powerNativeGun);
		}
		else if (fact == 'd')
		{
			std::cout << "Decepticon " << name << " created" << std::endl;
			return new Decepticon(name, 100, 100, v, speciality, initialPower, mind, powerNativeGun);
		}
	};

	if (!weapons.empty())
	{
		int selectWeapon;
		std::cout << "Select a weapon for this transformer:" << std::endl;
		showWeaponsList(weapons);

		int* countUsed = new int(0);
		for (auto w : weapons)
			if (w->isUsed())
				(*countUsed)++;
		if (*countUsed == weapons.size())
		{
			std::cout << "All of the weapons are used by other transformers. No spare." << std::endl;
			delete countUsed;
			return endFoo(nullptr);
		}
		delete countUsed;

		std::cout << "Enter (0 means not to take): ";
		std::cin >> selectWeapon;
		while (true)
		{
			if (selectWeapon < 0 || selectWeapon > weapons.size())
				std::cout << "Incorrect Input. Please Repeat: ";
			else if (selectWeapon == 0)
				return endFoo(nullptr);
			else if (weapons[selectWeapon - 1]->isUsed())
				std::cout << "This weapon is used by other transformer. Repeat: ";
			else
				break;
			std::cin >> selectWeapon;
		}
		return endFoo(weapons[selectWeapon - 1]);
	}
	return endFoo(nullptr);
}

Weapon* createWeapon()
{
	std::string title;
	std::cout << "Creating a Weapon:\nGuns:\n1. Machine Gun\n2. Shotgun\n3. Assault Rifle\n4. Sniper Rifle\nCold Weapons:\n5. Knife\n6. Sword\n7. Sledgehammer\nSelect a kind: ";
	int kind = own::setChoice(1, 7);
	std::cout << "Enter the title of this weapon: ";
	std::cin >> title;
	std::string* temp = new std::string();
	getline(std::cin, *temp);
	title += *temp;
	delete temp;
	switch (kind)
	{
	case 1:
		return new MachineGun(title);
	case 2:
		return new Shotgun(title);
	case 3:
		return new AssaultRifle(title);
	case 4:
		return new SniperRifle(title);
	case 5:
		return new Knife(title);
	case 6:
		return new Sword(title);
	case 7:
		return new Sledgehammer(title);
	}
}

void addAltform(std::vector<altPtr>* const vec, const int number)
{
	auto append = [vec](const Altform& a)
	{
		altPtr temp(new Altform(a));
		vec->push_back(temp);
	};
	switch (number)
	{
	case 1:
		append(Altform::Car);
		break;
	case 2:
		append(Altform::SportCar);
		break;
	case 3:
		append(Altform::Motorcycle);
		break;
	case 4:
		append(Altform::Truck);
		break;
	case 5:
		append(Altform::Pickup);
		break;
	case 6:
		append(Altform::Tank);
		break;
	case 7:
		append(Altform::Plane);
		break;
	case 8:
		append(Altform::MilitaryFighter);
		break;
	case 9:
		append(Altform::DumpTruck);
		break;
	case 10:
		append(Altform::CybertronMachine);
		break;
	}
}

void showTransformersList(const std::vector<Transformer*>& list, const Transformer* const current)
{
	int shift = 1;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == current)
		{
			shift = 0;
			continue;
		}
		std::cout << i + shift << ". " << list[i]->getName() << "\t _";
		switch (list[i]->getFaction())
		{
		case Faction::AUTOBOT:
			std::cout << "Autobot";
			break;
		case Faction::DECEPTICON:
			std::cout << "Decepticon";
			break;
		}
		std::cout << "_\tstatus: ";
		if (list[i]->isAlive())
		{
			if (list[i]->getHp() < 8)
				std::cout << "in danger\t";
			else
				std::cout << "alive\t";
		}
		else
			std::cout << "dead\t";
		std::cout << "id: " << list[i]->getId() << std::endl;
	}
}

void showWeaponsList(const std::vector<Weapon*>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << i + 1 << ". " << list[i]->getType() << " " << list[i]->getTitle();
		if (list[i]->getOwner() != "nobody")
			std::cout << "\t\tis using by " << list[i]->getOwner();
		else
			std::cout << "\t\tno owner";
		std::cout << std::endl;
	}
}

void controlTransformer(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons)
{
	if (transformers.empty())
	{
		std::cout << "No transformers" << std::endl;
		return;
	}

	showTransformersList(transformers);
	std::cout << "Select transformer (0 is back): ";
	int controllingNumber = own::setChoice(0, transformers.size());
	if (controllingNumber == 0)
		return;
	Transformer* protagonist = transformers[controllingNumber - 1];

	auto convertToAutobot = [](Transformer* const t)->Autobot*
	{
		Autobot* a = dynamic_cast<Autobot*>(t);
		if (!a)
		{
			std::cout << "An Error Occurred: Unsuccessful converting of pointers" << std::endl;
			exit(0);
		}
		return a;
	};
	auto convertToDecepticon = [](Transformer* const t)->Decepticon*
	{
		Decepticon* d = dynamic_cast<Decepticon*>(t);
		if (!d)
		{
			std::cout << "An Error Occurred: Unsuccessful converting of pointers" << std::endl;
			exit(0);
		}
		return d;
	};

	auto showActions = [protagonist]()->void
	{
		std::cout << "////////////////////////////////////////" << std::endl;
		std::cout << "Controlling by ";
		switch (protagonist->getFaction())
		{
		case Faction::AUTOBOT:
			std::cout << "Autobot ";
			break;
		case Faction::DECEPTICON:
			std::cout << "Decepticon ";
			break;
		}
		std::cout << protagonist->getName() << "\n1. Get Fast Info\n2. Get Full Info\n3. Compare with Another Transformer\n"
			"4. Transform\n5. Use the Weapon\n6. Use the Native Gun";
		if (!protagonist->hasNativeGun())
			std::cout << " (absents)";
		std::cout << "\n7. Take a Gun\n8. Drop a Gun\n9. Restore HP\n10. Rest\n";
		switch (protagonist->getFaction())
		{
		case Faction::AUTOBOT:
			std::cout << "11. Get Optimus Prime's Help\n12. Use the Ability of the Autobots\n13. Believe in the Spirit\n14. Examine an Area\n";
			break;
		case Faction::DECEPTICON:
			std::cout << "11. Get Megatron's Help\n12. Use the Ability of the Decepticons\n13. Use an Energon\n14. Execute an Autobot\n";
			break;
		}
		std::cout << "15. Show Actions Again\n16. Quit\n";
		std::cout << "////////////////////////////////////////\n";
	};

	showActions();
	int action;
	bool quit = false;
	while (!quit)
	{
		std::cout << "//// Enter: ";
		action = own::setChoice(1, 16);
		switch (action)
		{
		case 1:
			protagonist->getFastInfo();
			break;
		case 2:
			protagonist->getInformation();
			break;
		case 3:
		{
			showTransformersList(transformers, protagonist);
			std::cout << "Select who to compare with: ";
			int compareWith = own::setChoice(1, transformers.size() - 1);
			if (compareWith < controllingNumber)
				compareWith--;
			compareTransformers(*protagonist, *(transformers[compareWith]));
			break;
		}
		case 4:
			protagonist->transform();
			break;
		case 5:
		case 6:
		{
			if (!protagonist->isAlive())
			{
				std::cout << protagonist->getName() << " ain't alive" << std::endl;
				break;
			}
			if (action == 5 && !protagonist->hasWeapon())
			{
				std::cout << protagonist->getName() << " hasn't the hand weapon right now" << std::endl;
				break;
			}
			if (action == 6 && !protagonist->hasNativeGun())
			{
				std::cout << protagonist->getName() << " has not the native gun" << std::endl;
				break;
			}
			if (!protagonist->getPower())
			{
				std::cout << protagonist->getName() << " lost all of its energy. You should rest" << std::endl;
				break;
			}

			auto enemies = new std::vector<Transformer*>;
			int* number = new int(0);
			for (auto t : transformers)
				if (t->getFaction() != protagonist->getFaction())
				{
					std::cout << ++(*number) << ". " << t->getName() << std::endl;
					enemies->push_back(t);
				}
			delete number;
			if (!enemies->size())
			{
				if (protagonist->getFaction() == Faction::AUTOBOT)
					std::cout << "No decepticons" << std::endl;
				else
					std::cout << "No autobots" << std::endl;
				delete enemies;
				break;
			}

			std::cout << "Select who to use against: ";
			int shootTo = own::setChoice(1, enemies->size());
			shootTo--;
			if (!(*enemies)[shootTo]->isAlive())
			{
				std::cout << (*enemies)[shootTo]->getName() << " is dead" << std::endl;
				break;
			}
			auto use = [](std::function<void()> f)->void
			{
				f();
			};
			auto handWeapon = [protagonist, enemies, shootTo]()->void
			{
				protagonist->shoot(*((*enemies)[shootTo]));
			};
			auto nativeGun = [protagonist, enemies, shootTo]()->void
			{
				protagonist->shootByNativeGun(*((*enemies)[shootTo]));
			};
			if (action == 5)
				use(handWeapon);
			else if (action == 6)
				use(nativeGun);
			delete enemies;
			break;
		}
		case 7:
		{
			if (!protagonist->isAlive())
			{
				std::cout << protagonist->getName() << " ain't alive" << std::endl;
				break;
			}
			if (weapons.empty())
			{
				std::cout << "No weapons" << std::endl;
				break;
			}
			if (protagonist->hasWeapon())
			{
				std::cout << protagonist->getName() << " already has a weapon" << std::endl;
				break;
			}
			showWeaponsList(weapons);
			std::cout << "Select what to take: ";
			int take;
			while (true)
			{
				take = own::setChoice(1, weapons.size());
				if (weapons[take - 1]->getOwner() != "nobody")
				{
					std::cout << "This weapon is using by another transformer. Repeat: ";
					continue;
				}
				break;
			}
			protagonist->takeGun(weapons[take - 1]);
			break;
		}
		case 8:
			protagonist->dropGun();
			break;
		case 9:
			protagonist->restoreHp();
			break;
		case 10:
			protagonist->rest();
			break;
		case 11:
			switch (protagonist->getFaction())
			{
			case Faction::AUTOBOT:
				convertToAutobot(protagonist)->getOptimusHelp();
				break;
			case Faction::DECEPTICON:
				convertToDecepticon(protagonist)->getMegatronHelp();
				break;
			}
			break;
		case 12:
			switch (protagonist->getFaction())
			{
			case Faction::AUTOBOT:
				convertToAutobot(protagonist)->getAutobotHp();
				break;
			case Faction::DECEPTICON:
				convertToDecepticon(protagonist)->getDecepticonPower();
				break;
			}
			break;
		case 13:
			switch (protagonist->getFaction())
			{
			case Faction::AUTOBOT:
				convertToAutobot(protagonist)->believeInSpirit();
				break;
			case Faction::DECEPTICON:
				convertToDecepticon(protagonist)->useEnergon();
				break;
			}
			break;
		case 14:
			if (protagonist->getFaction() == Faction::AUTOBOT)
				convertToAutobot(protagonist)->examineArea(transformers);
			else if (protagonist->getFaction() == Faction::DECEPTICON)
			{
				if (!protagonist->isAlive())
				{
					std::cout << protagonist->getName() << " ain't alive" << std::endl;
					break;
				}
				std::cout << "Autobots:" << std::endl;
				auto* autobots = new std::vector<Transformer*>;
				int decepticons = 0;
				for (int i = 0; i < transformers.size(); i++)
				{
					if (transformers[i]->getFaction() == Faction::DECEPTICON)
					{
						decepticons++;
						continue;
					}
					std::cout << i + 1 - decepticons << ". " << transformers[i]->getName() << std::endl;
					autobots->push_back(transformers[i]);
				}
				if (decepticons == transformers.size())
				{
					std::cout << "No autobots" << std::endl;
					break;
				}
				std::cout << "Select who to execute: ";
				int execute = own::setChoice(1, transformers.size() - decepticons);
				Autobot* temp = dynamic_cast<Autobot*>((*autobots)[execute - 1]);
				delete autobots;
				if (!temp->isAlive())
				{
					std::cout << temp->getName() << " is dead" << std::endl;
					break;
				}
				if (!temp)
				{
					std::cout << "An Error Occurred: Unsuccessful converting of pointers" << std::endl;
					exit(0);
				}
				convertToDecepticon(protagonist)->executeAutobotFast(*temp);
			}
			break;
		case 15:
			showActions();
			break;
		case 16:
			quit = true;
			break;
		}
	}
}

void deleteTransformer(std::vector<Transformer*>& transformers)
{
	if (transformers.empty())
	{
		std::cout << "No transformers" << std::endl;
		return;
	}
	showTransformersList(transformers);
	std::cout << "Select (0 is back): ";
	int select = own::setChoice(0, transformers.size());
	if (select == 0)
		return;
	switch (transformers[select - 1]->getFaction())
	{
	case Faction::AUTOBOT:
		std::cout << "Autobot ";
		break;
	case Faction::DECEPTICON:
		std::cout << "Decepticon ";
		break;
	}
	std::cout << transformers[select - 1]->getName() << " deleted" << std::endl;
	namesOfTransformers.erase(transformers[select - 1]->getName());
	delete transformers[select - 1];
	transformers.erase(transformers.begin() + select - 1);
}

void deleteWeapon(std::vector<Weapon*>& weapons, std::vector<Transformer*>& transformers)
{
	if (weapons.empty())
	{
		std::cout << "No weapons" << std::endl;
		return;
	}
	showWeaponsList(weapons);
	std::cout << "Select (0 is back): ";
	int select = own::setChoice(0, weapons.size());
	if (select == 0)
		return;
	select--;

	if (weapons[select]->getOwner() != "nobody")
		for (auto t : transformers)
			if (t->getName() == weapons[select]->getOwner())
			{
				t->dropGun();
				break;
			}

	std::cout << weapons[select]->getType() << " " << weapons[select]->getTitle() << " deleted" << std::endl;
	delete weapons[select];
	weapons.erase(weapons.begin() + select);
}

void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons)
{
	if (!transformers.size() && !weapons.size())
	{
		std::cout << "You has not data" << std::endl;
		return;
	}

	std::ofstream file;
	file.open("SaveData.txt", std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "An Error Occurred: The file couldn't open" << std::endl;
		file.close();
		exit(0);
	}

	auto writeString = [&file](const std::string& word)->void
	{
		int* size = new int(word.size() + 1);
		file.write(reinterpret_cast<char*>(size), sizeof(*size));
		file.write((char*)word.c_str(), *size);
		delete size;
	};

	int amount = transformers.size();
	file.write(reinterpret_cast<char*>(&amount), sizeof(amount));
	for (int i = 0; i < amount; i++)
	{
		auto current = transformers[i];

		Faction* f = new Faction(current->getFaction());
		file.write(reinterpret_cast<char*>(f), sizeof(*f));

		writeString(current->name);
		writeString(current->speciality);
		file.write(reinterpret_cast<char*>(&current->hp), sizeof(current->hp));
		file.write(reinterpret_cast<char*>(&current->power), sizeof(current->power));
		file.write((char*)&current->initialPower, sizeof(current->initialPower));
		file.write((char*)&current->mind, sizeof(current->mind));
		file.write((char*)&current->firePowerOfNativeGun, sizeof(current->firePowerOfNativeGun));
		file.write(reinterpret_cast<char*>(&current->isInAltform), sizeof(current->isInAltform));

		if (*f == Faction::AUTOBOT)
		{
			Autobot* temp = dynamic_cast<Autobot*>(current);
			file.write(reinterpret_cast<char*>(&temp->spirit), sizeof(temp->spirit));
		}
		else
		{
			Decepticon* temp = dynamic_cast<Decepticon*>(current);
			file.write(reinterpret_cast<char*>(&temp->energon), sizeof(temp->energon));
		}
		delete f;

		int amountOfAltforms = current->altform.size();
		file.write(reinterpret_cast<char*>(&amountOfAltforms), sizeof(amountOfAltforms));
		int* next = new int(0);
		while (*next < amountOfAltforms)
		{
			file.write(reinterpret_cast<char*>(current->altform[*next].get()), sizeof(*(current->altform[*next])));
			(*next)++;
		}
		delete next;
	}

	amount = weapons.size();
	file.write(reinterpret_cast<char*>(&amount), sizeof(amount));
	for (int i = 0; i < amount; i++)
	{
		auto current = weapons[i];
		writeString(current->getType());
		writeString(current->title);
		writeString(current->owner);
		file.write(reinterpret_cast<char*>(&current->strength), sizeof(current->strength));

		if (current->getType() == "Machine Gun" || current->getType() == "Shotgun" || current->getType() == "Assault Rifle" || current->getType() == "Sniper Rifle")
		{
			Gun* firegun = dynamic_cast<Gun*>(current);
			file.write(reinterpret_cast<char*>(&firegun->ammo), sizeof(firegun->ammo));
		}
	}

	file.close();
	std::cout << "Data Saved Successfully" << std::endl;
}

void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons)
{
	std::ifstream file;
	file.open("SaveData.txt", std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "The file doesn't exist" << std::endl;
		file.close();
		return;
	}

	if (transformers.size() && weapons.size())
	{
		char way;
		std::cout << "You have some data. After loading data from the file you will lose them. Are you sure about this? (y/n): ";
		std::cin >> way;
		while (way != 'y' && way != 'n')
		{
			std::cout << "Incorrect Input. Please Repeat: ";
			std::cin >> way;
		}
		if (way == 'n')
			return;
	}

	for (auto t : transformers)
		delete t;
	for (auto w : weapons)
		delete w;
	transformers.clear();
	weapons.clear();
	Transformer::numberOfCreated = 0;

	auto readString = [&file]()->std::string
	{
		int size;
		char* buf;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		buf = new char[size];
		file.read(buf, size);
		std::string r = buf;
		delete[] buf;
		return r;
	};

	int amount;
	file.read(reinterpret_cast<char*>(&amount), sizeof(amount));
	for (int i = 0; i < amount; i++)
	{
		Faction f;
		std::string name, speciality, weaponTitle;
		int hp, power, initialPower, mind, firePowerOfNativeGun, spiritOrEnergon;
		std::vector<altPtr> altForms;
		bool isInAltform;

		file.read(reinterpret_cast<char*>(&f), sizeof(f));
		name = readString();
		speciality = readString();
		file.read(reinterpret_cast<char*>(&hp), sizeof(hp));
		file.read(reinterpret_cast<char*>(&power), sizeof(power));
		file.read(reinterpret_cast<char*>(&initialPower), sizeof(initialPower));
		file.read(reinterpret_cast<char*>(&mind), sizeof(mind));
		file.read(reinterpret_cast<char*>(&firePowerOfNativeGun), sizeof(firePowerOfNativeGun));
		file.read(reinterpret_cast<char*>(&isInAltform), sizeof(isInAltform));
		file.read(reinterpret_cast<char*>(&spiritOrEnergon), sizeof(spiritOrEnergon));
		int* amountOfAltforms = new int(0);
		file.read(reinterpret_cast<char*>(amountOfAltforms), sizeof(*amountOfAltforms));
		while ((*amountOfAltforms)-- != 0)
		{
			Altform temp;
			file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
			altForms.push_back(std::shared_ptr<Altform>(new Altform(temp)));
		}
		delete amountOfAltforms;

		switch (f)
		{
		case Faction::AUTOBOT:
		{
			transformers.push_back(new Autobot(name, hp, power, altForms, speciality, initialPower, mind, firePowerOfNativeGun));
			Autobot* a = dynamic_cast<Autobot*>(transformers.back());
			a->spirit = spiritOrEnergon;
			break;
		}
		case Faction::DECEPTICON:
		{
			transformers.push_back(new Decepticon(name, hp, power, altForms, speciality, initialPower, mind, firePowerOfNativeGun));
			Decepticon* d = dynamic_cast<Decepticon*>(transformers.back());
			d->energon = spiritOrEnergon;
			break;
		}
		}

		if (!hp)
			transformers.back()->alive = false;
		transformers.back()->isInAltform = isInAltform;
		namesOfTransformers.emplace(name);
	}

	file.read(reinterpret_cast<char*>(&amount), sizeof(amount));
	for (int i = 0; i < amount; i++)
	{
		std::string type, title, owner;
		int strength, ammo;

		type = readString();
		title = readString();
		owner = readString();
		file.read(reinterpret_cast<char*>(&strength), sizeof(strength));

		auto setWithAmmo = [&file, &weapons, &ammo, title](Weapon* const w)
		{
			file.read(reinterpret_cast<char*>(&ammo), sizeof(ammo));
			weapons.push_back(w);
			Gun* g = dynamic_cast<Gun*>(weapons.back());
			g->ammo = ammo;
		};

		if (type == "Machine Gun")
			setWithAmmo(new MachineGun(title));
		else if (type == "Shotgun")
			setWithAmmo(new Shotgun(title));
		else if (type == "Assault Rifle")
			setWithAmmo(new AssaultRifle(title));
		else if (type == "Sniper Rifle")
			setWithAmmo(new SniperRifle(title));
		else if (type == "Knife")
			weapons.push_back(new Knife(title));
		else if (type == "Sword")
			weapons.push_back(new Sword(title));
		else if (type == "Sledgehammer")
			weapons.push_back(new Sledgehammer(title));

		weapons.back()->strength = strength;
		weapons.back()->getOwner() = owner;
		if (owner != "nobody")
			weapons.back()->isUsed() = true;
	}

	file.close();

	for (int i = 0; i < amount; i++)
	{
		if (weapons[i]->getOwner() == "nobody")
			continue;
		for (auto one : transformers)
			if (one->getName() == weapons[i]->getOwner())
			{
				one->takeGun(weapons[i]);
				break;
			}
	}

	std::cout << "Data Loaded Successfully" << std::endl;
}
