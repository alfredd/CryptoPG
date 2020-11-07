//
// Created by alfredd on 11/6/20.
//

#ifndef KEYMANAGER_H
#define KEYMANAGER_H
#include <string>

class KeyManager
{
public:
	KeyManager();
	~KeyManager();
	char* sign(char* data, int len);
	bool validate(char* signedData);
	char* getPublicKey();

private:
	void loadKeys();
	const std::string PUBLIC_KEY_FILE_NAME = "Key.pub";
	const std::string PRIVATE_KEY_FILE_NAME = "Key.priv";
};


#endif //KEYMANAGER_H
