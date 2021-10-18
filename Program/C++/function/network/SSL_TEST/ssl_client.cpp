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

    struct sockaddr_in cAddress;
    cAddress.sin_family = AF_INET;
    cAddress.sin_addr.s_addr = inet_addr("192.168.126.135");
    cAddress.sin_port = htons(0);

    if (-1 == bind(sockfd, (struct sockaddr*)&cAddress, sizeof(struct sockaddr_in)))
    {
        perror("bind:");
        return -1;
    }

    connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in));


    cSSL_CTX = SSL_CTX_new( SSLv23_client_method());
    SSL_CTX_set_options(cSSL_CTX, SSL_OP_SINGLE_DH_USE);


    cSSL = SSL_new(cSSL_CTX);
    SSL_set_fd(cSSL, sockfd);

    printf("2222\n");

    int iRet = SSL_connect(cSSL);
    if (iRet == -1)
    {
	printf("3333\n");
        ERR_print_errors_fp(stdout);
        return -1;
    }

    while (1)
    {
//
	sleep(1);

        char cBuf1[256] = "ha start\n";
        //char cBuf1[256] = "12321sdjasdlfkj\n";
        //char cBuf1[256] = "ha start\n";
        //char cBuf1[256] = "ha start\n";

	//for (int i=0; i<strlen(cBuf1); i++)
	//{
        //if (0 > SSL_write(cSSL, &(cBuf1[i]), 1))
        printf("send len:%d\n", strlen(cBuf1));
        int iCount = SSL_write(cSSL, cBuf1, strlen(cBuf1));
	if (iCount < 0)
        {
            printf("send failed\n");
        }
	if (iCount == 0)
		printf("connect over");
            
	printf("SERVER->CLIENT:%s\n", cBuf1);
	printf("send success:%d\n", iCount);
//}
	//iCount = SSL_write(cSSL, cBuf1, strlen(cBuf1));

	while(1)
	{
	
	printf("123\n");

        char cBuf[655350] = {0};
        int iLen = SSL_read(cSSL, cBuf, 655349);
        if (0 >= iLen)
        {
            printf("nothing...\n");
        }
        else
        {
            printf("CLIENT->SERVER:%s\n", cBuf);
        }
	if ((cBuf[iLen-3]) == '}')
		break;
	
	}
    }

	ShutdownSSL();
	DestroySSL();


    return 0;
}
