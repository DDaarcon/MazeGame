#include "pch.h"
#include "FakeTextureLoader.h"

std::unique_ptr<sf::Texture> FakeTextureLoader::load(const std::string path)
{
    return std::make_unique<sf::Texture>();
}
