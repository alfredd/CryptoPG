//
// Created by alfredd on 11/9/20.
//

#ifndef SIGNER_HPP
#define SIGNER_HPP

#include <string>

#include "cryptopp/dsa.h"
#include "cryptopp/osrng.h"
//#include "cryptopp/cryptlib.h"

namespace cryptopg
{

class Signer
{
public:
	std::string Sign(std::string message, CryptoPP::DSA::PrivateKey privateKey)
	{
		CryptoPP::DSA::Signer signer(privateKey);
		CryptoPP::AutoSeededRandomPool rng;
		std::string signature;
		CryptoPP::StringSource ss(message,
							true,
							new CryptoPP::SignerFilter(
								rng, signer, new CryptoPP::StringSink(signature)));
		return signature;
	}
};

}


#endif //SIGNER_HPP
