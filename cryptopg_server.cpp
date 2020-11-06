//
// Created by alfredd on 11/6/20.
//

#include <grpcpp/grpcpp.h>
#include "cryptopg.pb.h"
#include "cryptopg.grpc.pb.h"


#include <iostream>
#include <memory>


using namespace cryptopg;
using namespace grpc;

class CryptoPGServiceImpl : public CryptoPG::Service {
public:
	Status GetPKCS8PublicKey (ServerContext *context, const Dummy *request, PublicKey *response) override {
		std::string responseKey("100100");
		response->set_pkcs8publickey(responseKey);
		return Status::OK;
	}
};

void RunServer() {
	string address ("0.0.0.0:45000");
	CryptoPGServiceImpl service;
	ServerBuilder serverBuilder;
	serverBuilder.AddListeningPort(address, InsecureServerCredentials());
	serverBuilder.RegisterService(&service);
	std::unique_ptr<Server> server(serverBuilder.BuildAndStart());
	std::cout<<"Server listening on " << address << std::endl;
	server->Wait();
}


int main(int argc, char **argv)
{
	std::cout<<"GRPC CryptoPG Server"<<std::endl;
	RunServer();
}