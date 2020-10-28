#include <iostream>

#include <openssl/evp.h>
#include <openssl/rsa.h>

void generate_rsa_keys()
{
	EVP_PKEY_CTX  *ctx;
	EVP_PKEY * pkey = nullptr;
	ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
	if (!ctx)
		std::cout<< "Error Occurred" <<std::endl;
	if (EVP_PKEY_keygen_init(ctx) <= 0)
		std::cout<< "init Error"<< std::endl;
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <=0)
		std::cout<< "Error in generating 2048 bits" <<std::endl;

	const auto status = EVP_PKEY_keygen(ctx, &pkey);
	if (status<=0)
		std::cout<< "Error generating key: "<<status<<std::endl;

}

int main()
{
	std::cout << "Hello, World!" << std::endl;
	generate_rsa_keys();
	return 0;
}
