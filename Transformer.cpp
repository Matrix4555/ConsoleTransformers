#include "Transformer.h"

Transformer::Transformer(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w) :
	name(n), altform(a), speciality(s), hp(100), power(100), initialPower(inp), mind(m), firePowerOfNativeGun(fpng), alive(true), isInAltform(false), weapon(w), id(++numberOfCreated)
{
	this->hp = hp;
	this->power = power;
	setNativeGun(fpng);
	if (weapon)
	{
		weapon->getOwner() = name;
		weapon->isUsed() = true;
	}
	std::cout << "Transformer " << name << " created" << std::endl;
}

Transformer::~Transformer()
{
	if (weapon)
		dropGun();
	std::cout << "Cybertron accepted " << name << std::endl;
}

int Transformer::numberOfCreated = 0;

void Transformer::getInformation() const
{
	std::cout << *this;
}

void Transformer::getFastInfo() const
{
	std::cout << "[HP]:< " << hp << " > [Power]:< " << power << " > [Hand Weapon]:< ";
	if (!weapon)
		std::cout << "no > ";
	else
	{
		std::cout << weapon->getType() << " > ";
		Gun* g = dynamic_cast<Gun*>(weapon);
		if (!g)
			return;
		std::cout << "[Ammo]:< " << g->getAmmo() << " > ";
	}
}

const std::string Transformer::getName() const
{
	return name;
}

Faction Transformer::getFaction() const
{
	std::string temp = typeid(*this).name();
	temp.erase(0, 6);
	if (temp == "Autobot")
		return Faction::AUTOBOT;
	else if (temp == "Decepticon")
		return Faction::DECEPTICON;
	else
	{
		std::cout << "An Error Occurred: Fraction definition failed" << std::endl;
		exit(0);
	}
}

int Transformer::getHp() const
{
	return hp;
}

int Transformer::getPower() const
{
	return power;
}

const int Transformer::getId() const
{
	return id;
}

bool Transformer::isAlive() const
{
	return alive;
}

bool Transformer::hasWeapon() const
{
	return weapon == nullptr ? false : true;
}

bool Transformer::hasNativeGun() const
{
	return nativeGun;
}

void Transformer::transform()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (isInAltform)
	{
		isInAltform = false;
		std::cout << name << " transformed to robot mode" << std::endl;
	}
	else
	{
		isInAltform = true;
		if (altform.size() > 1)
		{
			std::string alt = getAltforms();
			std::cout << "Altforms: " << alt << "\nKind of altform to transform in: ";
			std::cout << name << " transformed to alternative form - " << own::takeWord(alt, own::setChoice(1, altform.size())) << std::endl;
			return;
		}
		std::cout << name << " transformed to alternative form - " << getAltforms() << std::endl;
	}
}

void Transformer::shoot(Transformer& to)
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!weapon)
	{
		std::cout << name << " hasn't the hand weapon right now" << std::endl;
		return;
	}
	if (!power)
	{
		std::cout << name << " lost all of its energy. You should rest" << std::endl;
		return;
	}
	if (isInAltform)
	{
		std::cout << name << " uses the alternative form";
		if (nativeGun)
			std::cout << " but it has native gun and you can use only this gun in this mode" << std::endl;
		else
			std::cout << ". This transformer hasn't native gun then fire from altform impossible" << std::endl;
		return;
	}
	std::cout << name << " ";
	ColdWeapon* isColdWeapon = dynamic_cast<ColdWeapon*>(weapon);
	if (!isColdWeapon)
		std::cout << "fires from " << weapon->getType() << " (" << weapon->getTitle() << ") to " << to.getName() << std::endl;
	else
		std::cout << "beats " << to.getName() << " with a " << weapon->getType() << " (" << weapon->getTitle() << ")" << std::endl;
	weapon->use(to);
	power -= 3;
	if (power < 0)
		power = 0;
}

void Transformer::shootByNativeGun(Transformer& to)
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!nativeGun)
	{
		std::cout << name << " has not the native gun" << std::endl;
		return;
	}
	if (!power)
	{
		std::cout << name << " lost all of its energy. You should rest" << std::endl;
		return;
	}
	std::cout << name << " fires by native gun to " << to.getName() << std::endl;
	to.changeHp(-firePowerOfNativeGun);
	power -= 4;
	if (power < 0)
		power = 0;
}

void Transformer::changeHp(const int ch)
{
	if (hp <= 0)
		std::cout << "Resurrection of " << name << " is going" << std::endl;
	hp += ch;
	if (ch < 0 && hp <= 0)
	{
		hp = 0;
		if (weapon)
		{
			weapon->isUsed() = false;
			weapon->getOwner() = "nobody";
			weapon = nullptr;
		}
		alive = false;
		std::cout << name << " lost whole of Hp points. This transformer died" << std::endl;
	}
	else if (hp < 8)
		std::cout << name << " dies (" << hp << " hp)" << std::endl;
}

void Transformer::takeGun(Weapon* const g)
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	weapon = g;
	weapon->isUsed() = true;
	weapon->getOwner() = name;
	std::cout << name << " took weapon (" << g->getType() << " " << g->getTitle() << ")" << std::endl;
}

void Transformer::dropGun()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!weapon)
	{
		std::cout << name << " already has not a weapon" << std::endl;
		return;
	}
	std::cout << name << " dropped weapon (" << weapon->getType() << " " << weapon->getTitle() << ")" << std::endl;
	weapon->isUsed() = false;
	weapon->getOwner() = "nobody";
	weapon = nullptr;
}

void Transformer::restoreHp()
{
	if (hp == 100)
	{
		std::cout << name << " is full of health" << std::endl;
		return;
	}
	changeHp(50);
	if (hp > 100)
		hp = 100;
	std::cout << name << " restored own health" << std::endl;
	alive = true;
}

void Transformer::rest()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (power == 100)
	{
		std::cout << name << " is full of energy" << std::endl;
		return;
	}
	power += 20;
	if (power > 100)
		power = 100;
	std::cout << name << " restored its energy" << std::endl;
}

void Transformer::setNativeGun(const int pow)
{
	pow > 0 ? nativeGun = true : nativeGun = false;
}

std::string Transformer::getAltforms() const
{
	std::string temp;
	bool* comma = new bool(false);
	for (auto alt : altform)
	{
		if (*comma == true)
			temp += ", ";
		switch (*alt)
		{
		case Altform::Car:
			temp += "Car";
			break;
		case Altform::SportCar:
			temp += "Sport Car";
			break;
		case Altform::Motorcycle:
			temp += "Motorcycle";
			break;
		case Altform::Truck:
			temp += "Truck";
			break;
		case Altform::Pickup:
			temp += "Pickup";
			break;
		case Altform::Tank:
			temp += "Tank";
			break;
		case Altform::Plane:
			temp += "Plane";
			break;
		case Altform::MilitaryFighter:
			temp += "Military Fighter";
			break;
		case Altform::DumpTruck:
			temp += "Dump Truck";
			break;
		case Altform::CybertronMachine:
			temp += "Cybertron Machine";
			break;
		}
		*comma = true;
	}
	delete comma;
	return temp;
}

std::string Transformer::getWeaponInfo() const
{
	if (weapon)
		return weapon->getType() + " " + weapon->getTitle();
	else
		return "has not";
}

std::ostream& operator<<(std::ostream& os, const Transformer& t)
{
	os << "Information:\n"
		"Name:\t\t\t" << t.name << std::endl <<
		"[HP]:\t\t\t" << t.hp << std::endl <<
		"[Power]:\t\t" << t.power << std::endl <<
		"[Weapon]:\t\t" << t.getWeaponInfo() << std::endl <<
		"Faction:\t\t";
	switch (t.getFaction())
	{
	case Faction::AUTOBOT:
		os << "Autobot" << std::endl;
		break;
	case Faction::DECEPTICON:
		os << "Decepticon" << std::endl;
		break;
	}
	os << "Altform(s):\t\t" << t.getAltforms() << std::endl <<
		"Speciality:\t\t" << t.speciality << std::endl <<
		"Initial Power:\t\t" << t.initialPower << std::endl <<
		"Mind:\t\t\t" << t.mind << std::endl <<
		"Native Gun:\t\t";
	if (t.nativeGun)
		os << "has\nPower of Native Gun:\t" + std::to_string(t.firePowerOfNativeGun) << std::endl;
	else
		os << "has not" << std::endl;
	return os;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// AUTOBOTS___

Autobot::Autobot(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w) :
	Transformer(n, hp, power, a, s, inp, m, fpng, w), spirit(0)
{ }

void Autobot::getInformation() const
{
	Transformer::getInformation();
	std::cout << "Spirit:\t\t\t" << spirit << std::endl;
}

void Autobot::getFastInfo() const
{
	Transformer::getFastInfo();
	std::cout << "[Spirit]:< " << spirit << " >" << std::endl;
}

void Autobot::getOptimusHelp()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	spirit += 70;
	if (getName() == "Optimus Prime")
	{
		std::cout << "You are Optimus Prime =)" << std::endl;
		return;
	}
	hp = 150;
	std::cout << "The Leader of Autobots Optimus Prime restored " << getName() << "'s HP to 150 points and gave it 70 spirit points" << std::endl;
}

void Autobot::getAutobotHp()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	*this += 400;
	std::cout << getName() << " got 400 HP points using autobots ability" << std::endl;
	if (hp > 2000)
		hp = 2000;
}

void Autobot::believeInSpirit()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!spirit)
	{
		std::cout << "No spirit" << std::endl;
		return;
	}
	*this += spirit;
	std::cout << getName() << " got " << spirit << " HP believing in Optimus Prime" << std::endl;
	spirit = 0;
	if (hp > 2000)
		hp = 2000;
}

void Autobot::examineArea(const std::vector<Transformer*>& all) const
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	srand(time(0));
	int way = rand() % 2 + 1;
	try
	{
		switch (way)
		{
		case 1:
			std::cout << getName() << " has examined an area and didn't detected nobody of decepticon (although they are)" << std::endl;
			break;
		case 2:
		{
			bool decepticonsAreThere = false;
			for (auto t : all)
				if (t->getFaction() == Faction::DECEPTICON)
				{
					decepticonsAreThere = true;
					break;
				}
			if (decepticonsAreThere)
				while (true)
				{
					int robot = rand() % all.size() + 0;
					if (all[robot]->getFaction() == Faction::AUTOBOT)
						continue;
					std::cout << getName() << " has examined an area and detected a decepticon " << all[robot]->getName() << std::endl;
					break;
				}
			else
				std::cout << getName() << " has examined an area and didn't detected nobody of decepticon" << std::endl;
			break;
		}
		default:
			throw own::MyException("An Error Occurred: Incorrect value while randomization");
		}
	}
	catch (const own::MyException& exc)
	{
		exc.getMessage();
		exit(0);
	}
}

void Autobot::operator+=(const int a)
{
	hp += a;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// DECEPTICONS___

Decepticon::Decepticon(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w) :
	Transformer(n, hp, power, a, s, inp, m, fpng, w), energon(0)
{ }

void Decepticon::getInformation() const
{
	Transformer::getInformation();
	std::cout << "Energon:\t\t" << energon << std::endl;
}

void Decepticon::getFastInfo() const
{
	Transformer::getFastInfo();
	std::cout << "[Energon]:< " << energon << " >" << std::endl;
}

void Decepticon::getMegatronHelp()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	energon++;
	if (getName() == "Megatron")
	{
		std::cout << "You are Megatron =)" << std::endl;
		return;
	}
	std::cout << "The Lord of Decepticons Megatron got angry and damages " << getName() << " but gave it an energon" << std::endl;
	hp -= 40;
	if (hp < 10)
		hp = 10;
}

void Decepticon::getDecepticonPower()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (power >= 1500)
	{
		std::cout << name << " already has max energy" << std::endl;
		return;
	}
	*this *= 3;
	std::cout << name << " increases own power 3 time more points using decepticons ability" << std::endl;
	if (power > 1500)
		power = 1500;
}

void Decepticon::useEnergon()
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!energon)
	{
		std::cout << "No energon" << std::endl;
		return;
	}
	energon--;
	hp += 200;
	*this *= 2;
	std::cout << getName() << " applies an enegron and get 200 HP points and increases power 2 time more" << std::endl;
	if (power > 1500)
		power = 1500;
	if (hp > 2000)
		hp = 2000;
}

void Decepticon::executeAutobotFast(Autobot& to)
{
	if (!alive)
	{
		std::cout << name << " ain't alive" << std::endl;
		return;
	}
	if (!hasNativeGun())
	{
		std::cout << name << " has not native gun and can not use fast execution" << std::endl;
		return;
	}
	to.changeHp(-1000);
	std::cout << name << " performed fast execution against " << to.getName() << std::endl;
}

void Decepticon::operator*=(const int a)
{
	power *= a;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void compareTransformers(const Transformer& a, const Transformer& b)
{
	std::cout << "Comparison:" << std::endl <<
		"Name:\t\t\t" << a.name << "\t\t\t" << b.name << std::endl <<
		"[HP]:\t\t\t" << a.hp << "\t\t\t" << b.hp << std::endl <<
		"[Power]:\t\t" << a.power << "\t\t\t" << b.power << std::endl <<
		"[Weapon]:\t\t" << a.getWeaponInfo() << "\t\t" << b.getWeaponInfo() << std::endl <<
		"Fraction:\t\t";

	auto factionString = [](const Transformer& t)
	{
		switch (t.getFaction())
		{
		case Faction::AUTOBOT:
			std::cout << "Autobot";
			break;
		case Faction::DECEPTICON:
			std::cout << "Decepticon";
			break;
		}
	};
	factionString(a);
	std::cout << "\t\t\t";
	factionString(b);

	auto aboutNativeGun = [](const Transformer* const t)->std::string
	{
		if (t->nativeGun)
			return "has";
		else
			return "has not";
	};
	std::cout << "\nSpeciality:\t\t" << a.speciality << "\t\t\t" << b.speciality << std::endl <<
		"Initial Power:\t\t" << a.initialPower << "\t\t\t" << b.initialPower << std::endl <<
		"Mind:\t\t\t" << a.mind << "\t\t\t" << b.mind << std::endl <<
		"Native Gun:\t\t" << aboutNativeGun(&a) << "\t\t\t" << aboutNativeGun(&b) << std::endl <<
		"Power of Native Gun:\t" << a.firePowerOfNativeGun << "\t\t\t" << b.firePowerOfNativeGun << std::endl <<
		a.name << "'s altforms: " << a.getAltforms() << std::endl <<
		b.name << "'s altforms: " << b.getAltforms() << std::endl;
}
