#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::instance = nullptr;

void TextureManager::ExtractFileData(const std::filesystem::path& path)
{
    if (!FileExist(path.generic_u8string().c_str()))
    {
        std::cout << path.generic_u8string().c_str() << " not found.";
        exit(EXIT_FAILURE);
    }

    std::string png_path = path.parent_path().u8string() + "/" + path.stem().u8string() + ".png";
    std::cout << png_path << "\n";

    sf::Texture texture;
    texture.loadFromFile(png_path);

    return;

    textures.insert({ path.stem().u8string(), texture });

    // Filename
    std::string path_string{ path.stem().u8string() };

    dataXml.insert({ path_string, map<std::string, map<std::string, float>>() });

    xml_document<> doc;
    file<> file(path.generic_u8string().c_str());
    doc.parse<0>(file.data());
    rapidxml::xml_node<>* node = doc.first_node("Animations");

    if (node)
    {
        node = node->first_node("Animation");
    }
    else
    {
        node = doc.first_node("Backgrounds")->first_node("Tile");
    }

    while (node)
    {
        std::string nameIndex = node->first_attribute("Name")->value();

        dataXml[path_string].insert({ nameIndex, map<std::string, float>() });

        if (node->first_node("X"))
            dataXml[path_string][nameIndex].insert({ "X", stof(node->first_node("X")->value()) });

        if (node->first_node("Y"))
            dataXml[path_string][nameIndex].insert({ "Y", stof(node->first_node("Y")->value()) });

        if (node->first_node("SizeX"))
            dataXml[path_string][nameIndex].insert({ "SizeX", stof(node->first_node("SizeX")->value()) });

        if (node->first_node("SizeY"))
            dataXml[path_string][nameIndex].insert({ "SizeY", stof(node->first_node("SizeY")->value()) });

        if (node->first_node("OffsetX"))
            dataXml[path_string][nameIndex].insert({ "OffsetX", stof(node->first_node("OffsetX")->value()) });

        if (node->first_node("OffsetY"))
            dataXml[path_string][nameIndex].insert({ "OffsetY", stof(node->first_node("OffsetY")->value()) });

        if (node->first_node("SpriteNum"))
            dataXml[path_string][nameIndex].insert({ "SpriteNum", stof(node->first_node("SpriteNum")->value()) });

        if (node->first_node("SptitesOnLine"))
            dataXml[path_string][nameIndex].insert({ "SptitesOnLine", stof(node->first_node("SptitesOnLine")->value()) });

        if (node->first_node("Reverted"))
            dataXml[path_string][nameIndex].insert({ "Reverted", stof(node->first_node("Reverted")->value()) });

        if (node->first_node("RevertedX"))
            dataXml[path_string][nameIndex].insert({ "RevertedX", stof(node->first_node("RevertedX")->value()) });

        if (node->first_node("RevertedY"))
            dataXml[path_string][nameIndex].insert({ "RevertedY", stof(node->first_node("RevertedY")->value()) });

        if (node->first_node("TimeBetweenAnimation"))
        {
            dataXml[path_string][nameIndex].insert({ "TimeBetweenAnimation", stof(node->first_node("TimeBetweenAnimation")->value()) });
        }

        node = node->next_sibling();
    }
}


// Private 

bool TextureManager::FileExist(std::string fileSrc)
{
    fs::path pathToShow(fileSrc);
    return fs::exists(pathToShow);
}

