#include "SaveDictionary.h"
#include "pch.h"

bool FlushStreamBuffer(std::ostream& output)
{
	if (!output.flush())
	{
		return false;
	}

	return true;
}

void SendPairStream(const std::string& word, const std::vector<std::string>& transfer, std::ostream& file)
{
	file << word << ": ";
	for (size_t i = 0; i < transfer.size(); i++)
	{
		file << transfer.at(i);
		if (i < transfer.size() - 1)
		{
			file << ", ";
		}
	}
	file << "\n";
}

bool IterateOverDictionary(const Dictionary& dictionary, std::ostream& file)
{
	for (auto it = dictionary.dictionaryWords.begin(); it != dictionary.dictionaryWords.end(); ++it)
	{
		if ((*it).first.statusWord == Status::NEW)
		{
			SendPairStream((*it).first.keyWord, (*it).second, file);
		}
	}

	return FlushStreamBuffer(file);
}

void SaveDictionaryExistingFile(const Dictionary& dictionary, const std::string fileName)
{
	std::ofstream file(fileName, std::ios::app);

	if (file.is_open())
	{
		if (!IterateOverDictionary(dictionary, file))
		{
			std::cout << "Не удалось записать данные в выходной файл" << std::endl;
		}
	}
	else
	{
		std::cout << "Не удалось открыть файл \"" << fileName << "\" для записи" << std::endl;
	}
}

bool WriteToSpecifiedFile(const Dictionary& dictionary, std::ostream& file)
{
	for (auto it = dictionary.dictionaryWords.begin(); it != dictionary.dictionaryWords.end(); ++it)
	{
		file << (*it).first.keyWord << ": ";
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

	return FlushStreamBuffer(file);
}

void SaveDictionaryToSpecifiedFile(const Dictionary& dictionary)
{
	do
	{
		std::string fileName;
		std::cout << "Введите имя файла или пропустите этот шаг для отмены" << std::endl;
		std::cout << "Имя файла: ";
		getline(std::cin, fileName);

		if (fileName.empty())
		{
			std::cout << "Отмена!" << std::endl;
			break;
		}

		std::ofstream file(fileName, std::ios::out | std::ios::trunc);

		if (!file.is_open())
		{
			std::cout << "Не удалось открыть фаил! " << std::endl;
			continue;
		}

		if (!WriteToSpecifiedFile(dictionary, file))
		{
			std::cout << "Не удалось записать данные в выходной файл" << std::endl;
		}
		
		break;
	} while (true);


	//std::cout << "Введите имя файла, в котором будет сохранен словарь: ";
	//getline(std::cin, fileName);

	//std::ofstream file(fileName, std::ios::out | std::ios::trunc);

	//if (file.is_open())
	//{
	//	if (!WriteToSpecifiedFile(dictionary, file))
	//	{
	//		std::cout << "Не удалось записать данные в выходной файл" << std::endl;
	//	}
	//}
	//else
	//{
	//	std::cout << "Не удалось открыть файл \"" << fileName << "\" для записи" << std::endl;
	//}
}

void SaveDictionary(const Dictionary& dictionary, std::string fileName)
{
	if (!(fileName.empty()) && dictionary.statusDictionary == Status::NEW)
	{
		std::cout << "Добавленны новые слова, записываем их в указанный файл: " << fileName << std::endl;
		SaveDictionaryExistingFile(dictionary, fileName);
	}

	if (fileName.empty() && dictionary.statusDictionary == Status::NEW)
	{
		std::cout << "Добавленны новые слова, но не указан файл словаря." << std::endl;
		SaveDictionaryToSpecifiedFile(dictionary);
	}

	std::cout << "Выход" << std::endl;
}