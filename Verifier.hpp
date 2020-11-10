//
// Created by alfredd on 11/9/20.
//

#ifndef VERIFIER_HPP
#define VERIFIER_HPP

#include <string>

#include "cryptopp/dsa.h"
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

namespace cryptopg {
class Verifier {
public:
	bool verify(std::string message, std::string signature, std::string encodedPublicKey) {
		CryptoPP::DSA::PublicKey publicKey;
		publicKey.Load(CryptoPP::StringStore(encodedPublicKey).Ref());

		CryptoPP::DSA::Verifier verifier(publicKey);
		bool result = false;
		CryptoPP::StringSource ss(message+signature, true,
							new CryptoPP::SignatureVerificationFilter(verifier,
												 new CryptoPP::ArraySink((CryptoPP::byte*)&result, sizeof(result)),
												 CryptoPP::SignatureVerificationFilter::PUT_RESULT|
												 CryptoPP::SignatureVerificationFilter::SIGNATURE_AT_END));
		return result;
	}
};
}
#endif //VERIFIER_HPP
