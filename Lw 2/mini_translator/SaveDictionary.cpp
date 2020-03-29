#include "SaveDictionary.h"

bool StreamFile(const Dictionary& dictionary, std::ostream& file)
{
	for (auto it = dictionary.dictionaryWords.begin(); it != dictionary.dictionaryWords.end(); ++it)
	{
		file << (*it).first << ": ";
		for (size_t i = 0; i < (*it).second.size(); i++)
		{
			file << (*it).second.at(i);
			if (i < (*it).second.size() - 1)
			{
				file << ", ";
			}
		}
		file << "\n";
	}

	return true;
}

bool SaveDictionaryFile(const Dictionary& dictionary)
{
	std::cout << "enter the name of the file where you want to save the dictionary. For example \"resultDictionary.txt \"";
	std::string fileName;
	getline(std::cin, fileName);

	std::ofstream file(fileName, std::ios::out | std::ios::trunc);
	if (!file.is_open())
	{
		std::cout << "Faile to open '" << fileName << "' for writing" << std::endl;
		return false;
	}

	//גûגוסעט סכמגאנü ג פאיכ
	return StreamFile(dictionary, file);
}

void SaveDictionary(const Dictionary& dictionary)
{
	std::cout << "New words found in dictionary! Save to specified file? Y/N" << std::endl;

	int key;
	bool record;

	do
	{
		key = _getch();
		if (key == YES)
		{
			record = !SaveDictionaryFile(dictionary);
		}

		if (key != YES && key != NO)
		{
			std::cout << "\nWrong command! Try again" << std::endl;
			record = true;
		}

	} while (record);
	//key = _getch();

	//std::cout << key << std::endl;
}