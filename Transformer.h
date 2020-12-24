#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <ctime>
#include <stdlib.h>
#include "OwnFunctions.h"
#include "Weapon.h"

enum class Altform { Car, SportCar, Motorcycle, Truck, Pickup, Tank, Plane, MilitaryFighter, DumpTruck, CybertronMachine };
enum class Faction { AUTOBOT, DECEPTICON };

class Weapon;

class Transformer
{
public:
	Transformer() = delete;
	Transformer(const Transformer& t) = delete;
	Transformer(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w = nullptr);
	virtual ~Transformer() = 0;
	virtual void getInformation() const;
	virtual void getFastInfo() const;
	const std::string getName() const;
	Faction getFaction() const;
	int getHp() const;
	int getPower() const;
	const int getId() const;
	bool isAlive() const;
	bool hasWeapon() const;
	bool hasNativeGun() const;
	void transform();
	void shoot(Transformer& to);
	void shootByNativeGun(Transformer& to);
	void takeGun(Weapon* const g);
	void dropGun();
	void restoreHp();
	void rest();
	void changeHp(const int ch);
	friend void compareTransformers(const Transformer& a, const Transformer& b);
	friend void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
	friend void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
	friend std::ostream& operator<<(std::ostream& os, const Transformer& t);
protected:
	const std::string name;
	int hp;
	int power;
	bool alive;
private:
	const std::string speciality;
	const int initialPower;
	const int mind;
	const int firePowerOfNativeGun;
	const int id;
	bool isInAltform;
	bool nativeGun;
	std::vector<std::shared_ptr<Altform>> altform;
	Weapon* weapon;
	void setNativeGun(const int pow);
	std::string getAltforms() const;
	std::string getWeaponInfo() const;
	static int numberOfCreated;
};

class Autobot : public Transformer
{
public:
	Autobot() = delete;
	Autobot(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w = nullptr);
	virtual void getInformation() const override;
	virtual void getFastInfo() const override;
	void getOptimusHelp();
	void getAutobotHp();
	void believeInSpirit();
	void examineArea(const std::vector<Transformer*>& all) const;
	friend void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
	friend void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
private:
	void operator+=(const int a);
	int spirit;
};

class Decepticon : public Transformer
{
public:
	Decepticon() = delete;
	Decepticon(const std::string& n, const int hp, const int power, const std::vector<std::shared_ptr<Altform>>& a, const std::string& s, const int inp, const int m, const int fpng, Weapon* const w = nullptr);
	virtual void getInformation() const override;
	virtual void getFastInfo() const override;
	void getMegatronHelp();
	void getDecepticonPower();
	void useEnergon();
	void executeAutobotFast(Autobot& to);
	friend void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
	friend void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
private:
	void operator*=(const int a);
	int energon;
};
