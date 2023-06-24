#pragma once

#include <functional>
#include "../src/TextureLoader.h"

class FakeTextureLoader : public ITextureLoader
{
public:
    FakeTextureLoader() = delete;
    FakeTextureLoader(std::function<std::unique_ptr<sf::Texture>(const std::string)> load) : _loadMocked(load)
    { }

    std::unique_ptr<sf::Texture> load(const std::string path);

private :
    std::function<std::unique_ptr<sf::Texture>(const std::string)> _loadMocked;
};

