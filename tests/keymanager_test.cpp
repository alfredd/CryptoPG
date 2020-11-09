//
// Created by alfredd on 11/8/20.
//

#include "gtest/gtest.h"
#include "../KeyManager.h"
#include <cstdio>

TEST(KeyManager, Test1) {
	EXPECT_EQ(1,1);
}

/*TEST(KeyManager, Test2) {
	KeyManager keyManager;
	std::string publicKey = keyManager.getPublicKey();
	EXPECT_TRUE(publicKey.size()!=0);
}*/

void cleanup_files() {
	std::remove("Key.priv");
	std::remove("Key.pub");
}

TEST(KeyManager, Test3) {
	cleanup_files();

	KeyManager keyManager1;
	std::string publicKey1 = keyManager1.getPublicKey();

	KeyManager keyManager2;
	std::string publicKey2 = keyManager2.getPublicKey();
	EXPECT_TRUE(publicKey1==publicKey2);

	cleanup_files();

}