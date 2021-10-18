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
    if (sockfd < 0)
    {
        perror("socket:");
        return -1;
    }

    struct sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = inet_addr("192.168.126.135");
    clientAddress.sin_port = htons(0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("192.168.126.135");
    serverAddress.sin_port = htons(8888);

    if (-1 == bind(sockfd, (struct sockaddr*)&clientAddress, sizeof(struct sockaddr_in)))
    {
        perror("bind:");
        return -1;
    }

    if (-1 == connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)))
    {
        perror("connect:");
        return -1;
    }

    cSSL_CTX = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_set_options(cSSL_CTX, SSL_OP_SINGLE_DH_USE);
    cSSL = SSL_new(cSSL_CTX);
    SSL_set_fd(cSSL, sockfd);

    int iRet = SSL_connect(cSSL);
    if (iRet == -1)
    {
        ERR_print_errors_fp(stdout);
    }


    while (true)
    {
        sleep(1);

        char cBuf[256] = "123456";
        if (-1 == SSL_write(cSSL, cBuf, strlen(cBuf)))
        {
            printf("send failed\n");
            ERR_print_errors_fp(stdout);
        }
        else
        {
            printf("CLIENT->SERVER:%s\n", cBuf);
        }

        printf("prepare recv\n");
        memset(cBuf, 0, sizeof(cBuf));
        if (0 > SSL_read(cSSL, cBuf, 255))
        {
            printf("Client recv error\n");
        }
        else
        {
            printf("SERVER->CLIENT:%s\n", cBuf);
        }

    }

    return 0;
}
