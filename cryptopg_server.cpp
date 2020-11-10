//
// Created by alfredd on 11/6/20.
//

#include <grpcpp/grpcpp.h>
#include "cryptopg.pb.h"
#include "cryptopg.grpc.pb.h"
#include "KeyManager.h"


#include <iostream>
#include <memory>


using namespace cryptopg;
using namespace grpc;

class CryptoPGServiceImpl: public CryptoPG::Service
{

private:
	KeyManager keyManager;
	string publicKey;
public:

	CryptoPGServiceImpl()
	{

		std::string publicKey = keyManager.getPublicKey();
		if (publicKey.size() == 0) {
			std::cout<< "No public key found" << std::endl;
		}
		this->publicKey = publicKey;
		std::cout << "Size of public key is " << this->publicKey.size() << " bytes" << std::endl;

	}
	Status GetPKCS8PublicKey(ServerContext *context, const Dummy *request, PublicKey *response) override
	{
//		std::string responseKey("100100");
		response->set_pkcs8publickey(this->publicKey);
		return Status::OK;
	}

	virtual ~CryptoPGServiceImpl()
	{
//		if (keyManager) {
//			std::cout <<"Deleting key manager" << std::endl;
//			keyManager.reset();
//		}
	}
};

void RunServer()
{
	string address("0.0.0.0:55001");
	CryptoPGServiceImpl service;
	ServerBuilder serverBuilder;
	serverBuilder.AddListeningPort(address, InsecureServerCredentials());
	serverBuilder.RegisterService(&service);
	std::unique_ptr<Server> server(serverBuilder.BuildAndStart());
	std::cout << "Server listening on " << address << std::endl;
	server->Wait();
}

int main(int argc, char **argv)
{
	std::cout << "GRPC CryptoPG Server" << std::endl;
	RunServer();
}