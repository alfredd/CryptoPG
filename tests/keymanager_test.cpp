//
// Created by alfredd on 11/8/20.
//

#include "gtest/gtest.h"
#include "../KeyManager.h"

TEST(KeyManager, Test1) {
	EXPECT_EQ(1,1);
}

TEST(KeyManager, Test2) {
	KeyManager keyManager;
	std::string publicKey = keyManager.getPublicKey();
	EXPECT_TRUE(publicKey.size()!=0);
}