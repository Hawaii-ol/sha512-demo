/* Requires OpenSSL version >= 1.1.0 */
#include<stdio.h>
#include<string.h>
#include<openssl/evp.h>

#define SHA512_BYTES 64

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        exit(1);
    }

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    if (ctx == NULL) {
        fprintf(stderr, "Failed to initialize context\n");
        exit(2);
    }

    if (EVP_DigestInit(ctx, EVP_sha512())) {
        if (EVP_DigestUpdate(ctx, (void*)argv[1], strlen(argv[1]))) {
            unsigned char buffer[SHA512_BYTES];
            int i;
            if (EVP_DigestFinal_ex(ctx, buffer, NULL)) {
                for(i = 0; i < SHA512_BYTES; i++) {
                    printf("%x", buffer[i]);
                }
                EVP_MD_CTX_free(ctx);
                exit(0);
            }
        }
    }

    fprintf(stderr, "Some error happened while calculating the digest\n");
    EVP_MD_CTX_free(ctx);
    exit(3);
}
