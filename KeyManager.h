//
// Created by alfredd on 11/6/20.
//

#ifndef KEYMANAGER_H
#define KEYMANAGER_H
#include <string>
#include "cryptopp/dsa.h"
class KeyManager
{
public:
	KeyManager();
	virtual ~KeyManager();
	std::string sign(std::string message);
	std::string getPublicKey();

private:
	void storeKeys();
	void createNewPrivateKey();

	const std::string PUBLIC_KEY_FILE_NAME = "Key.pub";
	const std::string PRIVATE_KEY_FILE_NAME = "Key.priv";

	CryptoPP::DSA::PrivateKey privateKey;
	CryptoPP::DSA::PublicKey publicKey;
};


#endif //KEYMANAGER_H
