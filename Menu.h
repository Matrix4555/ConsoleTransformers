#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <set>
#include <functional>
#include <stdlib.h>
#include <fstream>
#include "Transformer.h"
#include "Weapon.h"

static std::set<std::string> namesOfTransformers;

Transformer* createTransformer(const std::vector<Weapon*>& weapons);
Weapon* createWeapon();
void addAltform(std::vector<std::shared_ptr<Altform>>* const vec, const int number);
void showTransformersList(const std::vector<Transformer*>& list, const Transformer* const current = nullptr);
void showWeaponsList(const std::vector<Weapon*>& list);
void controlTransformer(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
void deleteTransformer(std::vector<Transformer*>& transformers);
void deleteWeapon(std::vector<Weapon*>& weapons, std::vector<Transformer*>& transformers);
void saveToFile(const std::vector<Transformer*>& transformers, const std::vector<Weapon*>& weapons);
void loadFromFile(std::vector<Transformer*>& transformers, std::vector<Weapon*>& weapons);
