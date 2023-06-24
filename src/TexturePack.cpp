#include <exception>
#include "TexturePack.h"


TexturePack::TexturePack(std::shared_ptr<ITextureLoader> loader) : _loader(loader), _storage() {

}


std::shared_ptr<sf::Texture> TexturePack::getTexture(TextureType type) {
    auto storageItem = _storage.find(type);
    if (storageItem == _storage.end())
        return nullptr;

    return storageItem->second;
}


void TexturePack::loadOne(TextureType type, const std::string& path) {
    _storage[type] = _loader->load(path);
}

void TexturePack::loadMany(std::vector<TextureLoadData> loadData) {
    for (auto oneLoadData : loadData) {
        _storage[oneLoadData.type] = _loader->load(oneLoadData.path);
    }
}









std::shared_ptr<TexturePack> TexturePack::s_instance = nullptr;

void TexturePack::initializeSingleton(std::shared_ptr<ITextureLoader> loader) {
    s_instance = std::make_shared<TexturePack>(loader);
}

std::shared_ptr<TexturePack> TexturePack::instance() {
    ensureInitialized();
    return s_instance;
}

void TexturePack::ensureInitialized() {
    if (!s_instance)
        throw std::exception("Singleton instance not initialized");
}
