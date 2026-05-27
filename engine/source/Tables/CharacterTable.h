#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Core/Constants.h"
#include "CharacterStats.h"
#include <nlohmann/json.hpp>

//using namespace sf;
using namespace std;
using json = nlohmann::json;

class CharacterTable
{
public:
	// character table.
	CharacterTable() {}

	CharacterTable(std::string id, std::string displayName, std::string description, int level, int baseHP, int baseMP, int baseAttack, int baseDefense, std::string spritePath, CharacterStats stats)
	: ItemDefinition(id), DisplayName(displayName), Description(description), Level(level), BaseHP(baseHP), BaseMP(baseMP), BaseAttack(baseAttack), BaseDefense(baseDefense), SpritePath(spritePath), Stats(stats) {}

	 // getters
	 string GetItemDefinition() const { return ItemDefinition; }
	 string GetDisplayName() const { return DisplayName; }
	 string GetDescription() const { return Description; }
	 int GetLevel() const { return Level; }
	 int GetBaseHP() const { return BaseHP; }
	 int GetBaseMP() const { return BaseMP; }
	 int GetBaseAttack() const { return BaseAttack; }
	 int GetBaseDefense() const { return BaseDefense; }
	 std::string GetSpritePath() const { return SpritePath; }
	 CharacterStats GetStats() const { return Stats; }

	// This is to load the json file.
	static std::vector<CharacterTable> LoadFromFile(const std::string& filePath);

protected:
	string ItemDefinition;
	string DisplayName;
	string Description;
	int Level = -1;
	int BaseHP = -1;
	int BaseMP = -1;
	int BaseAttack = -1;
	int BaseDefense = -1;
	string SpritePath;
	CharacterStats Stats;
};