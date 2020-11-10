#include <iostream>
#include <string>

#include "cryptopp/cryptlib.h"
#include "cryptopp/dsa.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include "cryptopp/base64.h"

using namespace CryptoPP;


void keyValidation(const std::string &encodedPrivateKey, const std::string &validationKey)
{
	const auto encodedPrivateKeySize = encodedPrivateKey.size();
	const auto validationKeySize = validationKey.size();
	bool sameSize = encodedPrivateKeySize == validationKeySize;
	bool equal = true;
	if (sameSize) {
		for (int i = 0; i < encodedPrivateKeySize; ++i) {
			if (encodedPrivateKey.data()[i] != validationKey.data()[i]) {
				equal = false;
				break;
			}

		}
	}
	if (sameSize && equal) {
		std::cout << "Decoded private key is the same as the encoded private key." << std::endl;
	}
	else {
		std::cout << "Decoded private key is NOT the same as the encoded private key." << std::endl;
	}
}
void generate_dsa()
{
	AutoSeededRandomPool rng;
	DSA::PrivateKey privateKey;
	privateKey.GenerateRandomWithKeySize(rng, 2048);

	DSA::PublicKey publicKey;
	publicKey.AssignFrom(privateKey);
	if (!privateKey.Validate(rng, 3) || !publicKey.Validate(rng, 3)) {
		std::cout << "DSA Generation Failed" << std::endl;
	}

	std::cout << "Hex encoded private key: \n";
	HexEncoder hex(new FileSink(std::cout));
	privateKey.Save(hex);
	std::cout << std::endl;

	std::string encodedPrivateKey, encodedPublicKey;
	privateKey.Save(StringSink(encodedPrivateKey).Ref());
	publicKey.Save(StringSink(encodedPublicKey).Ref());
	std::cout << "PKCS #8 Encoded public key: \n" << encodedPublicKey << std::endl;

	DSA::PrivateKey decodedPrivateKey;
	decodedPrivateKey.Load(StringStore(encodedPrivateKey).Ref());
	std::string validationKey;
	decodedPrivateKey.Save(StringSink(validationKey).Ref());
	std::cout << "\n\n" << std::endl;
	keyValidation(encodedPrivateKey, validationKey);


	std::cout << "Base64 encoded private key: \n";
	std::string base64EncodedString;
	Base64Encoder base64Encoder(new StringSink(base64EncodedString));
	privateKey.Save(base64Encoder);
	std::cout << base64EncodedString << std::endl;

	/*
	Base64Decoder base64Decoder;
	base64Decoder.Put((byte *)base64EncodedString.data(), base64EncodedString.size());
	base64Decoder.MessageEnd();

	std::string base64DecodedString;

	word64 size = base64Decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX) {
		base64DecodedString.resize(size);
		base64Decoder.Get((byte*)base64DecodedString.data(), base64DecodedString.size());
		keyValidation(encodedPrivateKey, base64DecodedString);
	}
	*/

	std::string base64DecodedString;
	StringSource stringSource(base64EncodedString, true,
							  new Base64Decoder(
								  new StringSink(base64DecodedString)
							  )
	);
	DSA::PrivateKey decodedPrivateKey2;
	decodedPrivateKey2.Load(StringStore(base64DecodedString).Ref());
	decodedPrivateKey2.Save(StringSink(validationKey).Ref());
	keyValidation(encodedPrivateKey, validationKey);
/*

	DSA::PrivateKey decodedB64PrivateKey;
	decodedB64PrivateKey.Load(base64Decoder);
	std::string validationKeyString;
	decodedB64PrivateKey.Save(StringSink(validationKeyString).Ref());

	keyValidation(encodedPrivateKey, validationKeyString);
*/

}

/**
 * From https://www.cryptopp.com/wiki/Base64Decoder
 */
void exampleCode()
{
	std::string encoded = "/+7dzLuqmYh3ZlVEMyIRAA==";
	std::string decoded;

	Base64Decoder decoder;
	decoder.Put((byte *)encoded.data(), encoded.size());
	decoder.MessageEnd();

	word64 size = decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX) {
		decoded.resize(size);
		decoder.Get((byte *)&decoded[0], decoded.size());
	}

}

int main()
{
	std::cout << "Hello, World!" << std::endl;
	generate_dsa();
//	exampleCode();
	return 0;
}
