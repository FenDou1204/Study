#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static int sockfd, newsockfd;
static SSL_CTX* cSSL_CTX;
static SSL* cSSL;

void InitializeSSL()
{
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void DestroySSL()
{
    ERR_free_strings();
    EVP_cleanup();
}

void ShutdownSSL()
{
    SSL_shutdown(cSSL);
    SSL_free(cSSL);
}

int main(void)
{
    InitializeSSL();
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket:");
        return -1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("192.168.126.135");
    serverAddress.sin_port = htons(8888);

    if (-1 == bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)))
    {
        perror("bind:");
        return -1;
    }

    if (-1 ==  listen(sockfd, 1))
    {
        perror("listen:");
        return -1;
    }
    printf("Max connect count is 1\n");

    struct sockaddr_in connClientAddr;
    memset(&connClientAddr, 0, sizeof(struct sockaddr_in));
    unsigned int iAddrLen = sizeof(struct sockaddr_in);
    newsockfd = accept(sockfd, (struct sockaddr*)&connClientAddr, &iAddrLen);
    if (-1 == newsockfd)
    {
        perror("accept:");
        return -1;
    }

    printf("CLIENT IP:%s\n", inet_ntoa(connClientAddr.sin_addr));
    printf("CLIENT Port:%d\n", ntohs(connClientAddr.sin_port));

    cSSL_CTX = SSL_CTX_new( SSLv23_server_method());
    SSL_CTX_set_options(cSSL_CTX, SSL_OP_SINGLE_DH_USE);
    SSL_CTX_use_certificate_file(cSSL_CTX, "./cacert.pem" , SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(cSSL_CTX, "./privkey.pem", SSL_FILETYPE_PEM);

    if (!SSL_CTX_check_private_key(cSSL_CTX))
    {
        ERR_print_errors_fp(stdout);
        return -1;
    }

    cSSL = SSL_new(cSSL_CTX);
    SSL_set_fd(cSSL, newsockfd);

    int iRet = SSL_accept(cSSL);
    if (iRet == -1)
    {
        ERR_print_errors_fp(stdout);
        return -1;
    }

    while (1)
    {
        char cBuf[655350] = {0};
        if (0 >= SSL_read(cSSL, cBuf, 655349))
        {
            printf("nothing...\n");
        }
        else
        {
            printf("CLIENT->SERVER:%s\n", cBuf);
        }

        char cBuf1[256] = "age:1234567890";
        if (0 > SSL_write(cSSL, cBuf1, strlen(cBuf1)))
        {
            printf("send failed\n");
        }
        else
        {
            printf("SERVER->CLIENT:%s\n", cBuf1);
        }

    }


    return 0;
}
