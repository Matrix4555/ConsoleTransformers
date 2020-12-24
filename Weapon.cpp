#include "Weapon.h"

const std::string Weapon::getTitle() const
{
	return title;
}

const std::string Weapon::getType() const
{
	std::string temp = typeid(*this).name();
	temp.erase(0, 6);
	bool second = false;
	for (unsigned int i = 0; i < temp.size(); i++)
		if (temp[i] >= 'A' && temp[i] <= 'Z')
		{
			if (second)
			{
				temp.insert(i, " ");
				break;
			}
			second = true;
		}
	return temp;
}

std::string& Weapon::getOwner()
{
	return owner;
}

bool& Weapon::isUsed()
{
	return used;
}

Weapon::Weapon(const std::string& t, const int d) : title(t), damage(d), strength(100), owner("nobody"), used(false)
{
	std::cout << "Weapon " << title << " created" << std::endl;
}

void Weapon::operator-=(const int a)
{
	strength -= a;
}

Gun::Gun(const std::string& t, const int d, const int rt, const int ma) : Weapon(t, d), reloadTime(rt), maxAmmo(ma), ammo(ma)
{ }

int Gun::getAmmo() const
{
	return ammo;
}

void Gun::fire(Transformer& to, const int minusAmmo, const int minusStrength)
{
	if (strength < 0)
	{
		std::cout << "The weapon " << title << " is worn out" << std::endl;
		return;
	}
	to.changeHp(-damage);
	ammo -= minusAmmo;
	*this -= minusStrength;
	reload();
}

void Gun::reload()
{
	if (ammo <= 0)
	{
		int count = reloadTime;
		while (count)
		{
			Sleep(1000);
			std::cout << "(" << count-- << ")\t" << getType() << " is reloading" << std::endl;
		}
		ammo = maxAmmo;
	}
}

ColdWeapon::ColdWeapon(const std::string t, const int d) : Weapon(t, d)
{ }

void ColdWeapon::beat(Transformer& to, const int minusStrength)
{
	if (strength < 0)
	{
		std::cout << "The weapon " << title << " is worn out" << std::endl;
		return;
	}
	to.changeHp(-damage);
	*this -= minusStrength;
}

//---------------------------------------------------------------------

MachineGun::MachineGun(const std::string& t) : Gun(t, 5, 3, 20)
{ }

void MachineGun::use(Transformer& to)
{
	fire(to, 5, 3);
}

Shotgun::Shotgun(const std::string& t) : Gun(t, 15, 8, 8)
{ }

void Shotgun::use(Transformer& to)
{
	fire(to, 2, 5);
}

AssaultRifle::AssaultRifle(const std::string& t) : Gun(t, 5, 3, 30)
{ }

void AssaultRifle::use(Transformer& to)
{
	fire(to, 6, 4);
}

SniperRifle::SniperRifle(const std::string& t) : Gun(t, 21, 5, 6)
{ }

void SniperRifle::use(Transformer& to)
{
	fire(to, 1, 7);
}

//---------------------------------------------------------------------

Knife::Knife(const std::string& t) : ColdWeapon(t, 6)
{ }

void Knife::use(Transformer& to)
{
	beat(to, 4);
}

Sword::Sword(const std::string& t) : ColdWeapon(t, 11)
{ }

void Sword::use(Transformer& to)
{
	beat(to, 6);
}

Sledgehammer::Sledgehammer(const std::string& t) : ColdWeapon(t, 15)
{ }

void Sledgehammer::use(Transformer& to)
{
	beat(to, 8);
}
