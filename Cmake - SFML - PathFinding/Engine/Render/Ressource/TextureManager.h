#pragma once

#include <map>
#include <filesystem>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace rapidxml;
namespace fs = std::filesystem;

class TextureManager
{
public:
	void ExtractFileData(const std::filesystem::path& path);

	map<std::string, map<std::string, map<std::string, float>>> dataXml;
	map<std::string, sf::Texture> textures;

#pragma region Singleton

	static TextureManager* Instance()
	{
		if (!instance)
		{
			instance = new TextureManager();
		}

		return instance;
	}

	static void DeleteInstance()
	{
		if (!instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	static TextureManager* instance;
#pragma endregion

private:

	bool FileExist(std::string fileSrc);
};

