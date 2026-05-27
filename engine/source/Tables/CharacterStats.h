#pragma once

// taken from another project I was working on.
struct CharacterStats
{
	int Strength = -1;
	int Magic = -1;
	int Vitality = -1;
	int Agility = -1;
	int Luck = -1;

	CharacterStats() {}
	
	CharacterStats(int strength, int magic, int vitality, int agility, int luck) : Strength(strength), Magic(magic), Vitality(vitality), Agility(agility), Luck(luck) {}
	
};