//
// Created by alfredd on 11/9/20.
//

#include <iostream>
#include <memory>
#include <string>
#include <z3.h>

#include "grpcpp/grpcpp.h"
#include "cryptopg.grpc.pb.h"
#include "cryptopg.pb.h"

using namespace grpc;
using namespace cryptopg;

class CryptoPGClient {
public:

	CryptoPGClient(std::shared_ptr<Channel> channel) : stub_(CryptoPG::NewStub(channel)) {}
	bool getPKCS8PublicKey(PublicKey &response) {
		Dummy request;
		ClientContext context;
		Status status = stub_->GetPKCS8PublicKey(&context, request, &response);
		return  status.ok();
	}
private:
	std::unique_ptr<CryptoPG::Stub> stub_;
};

int main(int argc, char **argv)
{
	std::string server("localhost:55001");
	CryptoPGClient client(CreateChannel(server, InsecureChannelCredentials()));
	PublicKey publicKey;
	bool status = client.getPKCS8PublicKey(publicKey);
	if (status) {
		std::cout<< "Received public key from server. Key size is: "<< publicKey.pkcs8publickey().size() <<std::endl;
	} else {
		std::cout<< "Could not receive public key from server." << std::endl;
	}
	return 0;
}