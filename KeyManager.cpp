//
// Created by alfredd on 11/6/20.
//

#include "cryptopp/cryptlib.h"
#include "cryptopp/dsa.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"

#include "KeyManager.h"
#include "Signer.hpp"

#include <fstream>
#include <iostream>

using namespace CryptoPP;

KeyManager::KeyManager()
{
	std::ifstream privKeyFile;
	privKeyFile.open(this->PRIVATE_KEY_FILE_NAME, std::ios::binary);

	if (!privKeyFile.is_open()) {
		this->createNewPrivateKey();
	}
	else {
		std::cout << "Loading existing private key from file." << std::endl;
		DSA::PrivateKey decodedPrivateKey;
		decodedPrivateKey.Load(FileStore(privKeyFile).Ref());
		this->privateKey = decodedPrivateKey;
		this->publicKey.AssignFrom(privateKey);
	}
	privKeyFile.close();
}
KeyManager::~KeyManager()
{
}
std::string KeyManager::sign(std::string message)
{
	cryptopg::Signer signer;
	std::string signedMessage = signer.Sign(message, this->privateKey);

	return signedMessage;
}

std::string KeyManager::getPublicKey()
{
	std::string encodedPublicKey;
	publicKey.Save(StringSink(encodedPublicKey).Ref());
	return encodedPublicKey;
}
void KeyManager::storeKeys()
{
	std::ofstream privateKeyFile(this->PRIVATE_KEY_FILE_NAME, std::ios::binary);
	this->privateKey.Save(FileSink(privateKeyFile).Ref());
	privateKeyFile.close();

	std::ofstream publicKeyFile(this->PUBLIC_KEY_FILE_NAME, std::ios::binary);
	this->publicKey.Save(FileSink(publicKeyFile).Ref());
	publicKeyFile.close();
}
void KeyManager::createNewPrivateKey()
{
	AutoSeededRandomPool rng;
	DSA::PrivateKey localPrivateKey;
	localPrivateKey.GenerateRandomWithKeySize(rng, 2048);
	DSA::PublicKey localPublicKey;
	localPublicKey.AssignFrom(localPrivateKey);
	if (!localPrivateKey.Validate(rng, 3) || !localPublicKey.Validate(rng, 3)) {
		std::cout << "DSA Generation Failed" << std::endl;
		throw "Error while generating DSA keys.";
	}
	this->privateKey = localPrivateKey;
	this->publicKey = localPublicKey;

	this->storeKeys();
}
