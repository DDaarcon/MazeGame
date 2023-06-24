#include "pch.h"
#include "FakeTextureLoader.h"

#include "../src/TexturePack.h"

TEST(TexturePackTests, WHEN_instance_in_uninitialized_THEN_should_throw_an_exception) {
    EXPECT_ANY_THROW(TexturePack::instance());
}

TEST(TexturePackTests, WHEN_requesting_not_loaded_texture_THEN_nullptr_is_returned) {
    TexturePack::initializeSingleton(nullptr);
    auto pack = TexturePack::instance();

    auto texture = pack->getTexture(TextureType::Pown);

    EXPECT_EQ(nullptr, texture);
}



TEST(TexturePackTests, WHEN_requesting_texture_loaded_by_loadOne_THEN_texture_is_returned) {
    auto loader = std::make_shared<FakeTextureLoader>([](const std::string& path) {
        return std::make_unique<sf::Texture>();
    });
    TexturePack::initializeSingleton(loader);

    auto pack = TexturePack::instance();

    pack->loadOne(TextureType::Pown, "some_path");

    auto texture = pack->getTexture(TextureType::Pown);

    EXPECT_NE(nullptr, texture);
}


TEST(TexturePackTests, WHEN_requesting_textures_loaded_by_loadMany_THEN_texture_is_returned) {
    auto loader = std::make_shared<FakeTextureLoader>([](const std::string& path) {
        return std::make_unique<sf::Texture>();
    });
    TexturePack::initializeSingleton(loader);

    auto pack = TexturePack::instance();

    std::vector<TextureLoadData> loadData{
        { TextureType::Pown, "some_path" },
        { TextureType::LargePot, "some_path" }
    };

    pack->loadMany(loadData);

    auto texture = pack->getTexture(TextureType::Pown);

    EXPECT_NE(nullptr, texture);
}
