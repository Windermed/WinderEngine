#include "CharacterTable.h"

std::vector<CharacterTable> CharacterTable::LoadFromFile(const std::string& filePath)
{
	// stores all entries found in this vector.
	std::vector<CharacterTable> entries;

	ifstream file(filePath);

	if (!file.is_open())
	{
		Message("[CharacterTable] Error. The File " + filePath + "Was unable to be opened.\n ensure that the file is valid and try again.")
			return entries;
	}

	try
	{
		// start parsing data from json.
		json data = json::parse(file);

		auto& characters = data["CharacterTable"]["Characters"];

		// go through all entries
		for (auto& entry : characters)
		{
			// start grabbing data from json.
			for (auto& [id, charData] : entry.items())
			{
				string displayName = charData.value("DisplayName", "Unknown");
				string description = charData.value("Description", "");
				int level = charData.value("Level", -1);
				int baseHP = charData.value("BaseHP", -1);
				int baseMP = charData.value("BaseMP", -1);
				int baseAttack = charData.value("BaseAttack", -1);
				string spritePath = charData.value("SpritePath", "content/textures/player/spr_character_base_overworld.png"); // use a placeholder sprite just in case.
				int baseDefense = charData.value("BaseDefense", -1);

				CharacterStats foundStats;
				if (charData.contains("Stats"))
				{
					auto& s = charData.at("Stats");
					foundStats = CharacterStats(s.value("Strength", -1), s.value("Magic", -1), s.value("Vitality", -1), s.value("Agility", -1), s.value("Luck", -1));
				}

				entries.emplace_back(id, displayName, description, level, baseHP, baseMP, baseAttack, baseDefense, spritePath, foundStats);

			}
		}

		Message("[CharacterTable] Successfully loaded " << entries.size() << " entries from " << filePath << endl)
	}
	catch (const json::parse_error& e)
	{
		Message("ERROR: There was a parsing error: " << e.what() << endl)
	}

	return entries;
}