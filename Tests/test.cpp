#include "pch.h"

#include "../src/TextureManager.h"

TEST(TestCaseName, TestName) {

    TextureManager::getTextureAddress("pionek", "png");
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}