#include <iostream>

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <unistd.h>

void generate_rsa_keys()
{
	EVP_PKEY_CTX  *ctx;
	EVP_PKEY * pkey = nullptr;
	ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
	if (!ctx)
		std::cout<< "Error Occurred" <<std::endl;
	if (EVP_PKEY_keygen_init(ctx) <= 0)
		std::cout<< "init Error"<< std::endl;
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 4096) <=0)
		std::cout<< "Error in generating 2048 bits" <<std::endl;

	const auto status = EVP_PKEY_keygen(ctx, &pkey);
	if (status<=0)
		std::cout<< "Error generating key: "<<status<<std::endl;
	FILE* fp = fopen("mykey.pem", "w+");
	auto rval = PEM_write_PKCS8PrivateKey(fp, pkey, EVP_aes_128_cbc_hmac_sha256(), "none", 4, nullptr, nullptr);
	std::cout<<rval<<std::endl;
	fclose(fp);
}

int main()
{
	std::cout << "Hello, World!" << std::endl;
	generate_rsa_keys();
	return 0;
}
