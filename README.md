#TODO
* Create two modules with cryptopp library and gRPC.
* The server
  * Create a simple private-public key generator.
  * Store and retrieve keys from a file.
  * Create a service that will provide access to a node's public keys (RSA/DSA)
  * Additional code to sign respond with signed data blocks.
* The client
  * Client code to request for public keys.
  * Client should also be able to validate signature on a data block.