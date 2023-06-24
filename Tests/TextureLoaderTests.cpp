#include "pch.h"

#include "../src/TextureLoader.h"

TEST(TextureLoaderTests, WHEN_file_does_not_exist_THEN_exception_is_thrown) {
    TextureLoader loader("fake_loader_path");
    EXPECT_ANY_THROW(loader.load("more_fake_loader_path"));
}


