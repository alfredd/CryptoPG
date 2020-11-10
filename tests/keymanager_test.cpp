//
// Created by alfredd on 11/8/20.
//

#include "gtest/gtest.h"
#include "../KeyManager.h"
#include "../Verifier.hpp"
#include <cstdio>



void cleanup_files() {
	std::remove("Key.priv");
	std::remove("Key.pub");
}

TEST(KeyManager, Test2) {
	cleanup_files();
	KeyManager keyManager;
	std::string publicKey = keyManager.getPublicKey();
	EXPECT_TRUE(publicKey.size()!=0);
	cleanup_files();
}

TEST(KeyManager, MultipleInstancesOfKeyManagerUseSameKeysFromFile) {
	cleanup_files();

	KeyManager keyManager1;
	std::string publicKey1 = keyManager1.getPublicKey();

	KeyManager keyManager2;
	std::string publicKey2 = keyManager2.getPublicKey();
	EXPECT_TRUE(publicKey1==publicKey2);

	cleanup_files();

}

TEST(DigitalSignature, SignatureVerification)
{
	cleanup_files();

	KeyManager keyManager1;
	std::string publicKey1 = keyManager1.getPublicKey();

	std::string message = "Random Message";
	std::string signedMessage = keyManager1.sign(message);

	cryptopg::Verifier verifier;
	bool result = verifier.verify(message,signedMessage, publicKey1);

	EXPECT_TRUE(result);

	cleanup_files();
}

TEST(DigitalSignature, FailureTesting)
{
	cleanup_files();

	KeyManager keyManager1;
	std::string publicKey1 = keyManager1.getPublicKey();

	std::string message = "Random Message";
	std::string signedMessage = keyManager1.sign(message);

	cleanup_files();
	KeyManager keyManager2;
	publicKey1 = keyManager2.getPublicKey();
	cryptopg::Verifier verifier;
	bool result = verifier.verify(message,signedMessage, publicKey1);

	EXPECT_FALSE(result);

	cleanup_files();
}