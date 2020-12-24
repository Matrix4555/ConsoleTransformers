#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <Windows.h>
#include "Transformer.h"

class Transformer;

class Weapon
{
public:
	const std::string getTitle() const;
	const std::string getType() const;
	std::string& getOwner();
	bool& isUsed();
	virtual void use(Transformer& to) = 0;
	friend void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
	friend void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
protected:
	Weapon() = delete;
	Weapon(const std::string& t, const int d);
	const std::string title;
	std::string owner;
	const int damage;
	int strength;
	bool used;
	void operator-=(const int a);
};

class Gun : public Weapon
{
public:
	int getAmmo() const;
protected:
	Gun() = delete;
	Gun(const std::string& t, const int d, const int rt, const int ma);
	virtual void use(Transformer& to) = 0;
	void fire(Transformer& to, const int minusAmmo, const int minusStrength);
	void reload();
	friend void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
	friend void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
private:
	const int reloadTime;
	const int maxAmmo;
	int ammo;
};

class ColdWeapon : public Weapon
{
protected:
	ColdWeapon() = delete;
	ColdWeapon(const std::string t, const int d);
	virtual void use(Transformer& to) = 0;
	void beat(Transformer& to, const int minusStrength);
};

//---------------------------------------------------------------------------------------------------------------------

class MachineGun : public Gun
{
public:
	MachineGun(const std::string& t);
	virtual void use(Transformer& to) override;
};

class Shotgun : public Gun
{
public:
	Shotgun(const std::string& t);
	virtual void use(Transformer& to) override;
};

class AssaultRifle : public Gun
{
public:
	AssaultRifle(const std::string& t);
	virtual void use(Transformer& to) override;
};

class SniperRifle : public Gun
{
public:
	SniperRifle(const std::string& t);
	virtual void use(Transformer& to) override;
};

//---------------------------------------------------------------------------------------------------------------------

class Knife : public ColdWeapon
{
public:
	Knife(const std::string& t);
	virtual void use(Transformer& to) override;
};

class Sword : public ColdWeapon
{
public:
	Sword(const std::string& t);
	virtual void use(Transformer& to) override;
};

class Sledgehammer : public ColdWeapon
{
public:
	Sledgehammer(const std::string& t);
	virtual void use(Transformer& to) override;
};
