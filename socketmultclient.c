#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int r1,c1,r2,c2;
int mat1[100][100],mat2[100][100],result[100][100];

int main()
{
    int sockfd = 0;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0',sizeof(recvBuff));
    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    int connfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(connfd<0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    	printf("enter the number of rows of first matrix\n");
        scanf("%d",&r1);
	send(sockfd, &r1, sizeof(r1),0);
        printf("enter the number of columns in first matrix\n");
        scanf("%d",&c1);
	send(sockfd, &c1, sizeof(c1),0);

        printf("enter mat1 elements\n");
        fill(mat1,r1,c1);
	send(sockfd, &mat1, sizeof(mat1),0);

	printf("enter the number of rows of first matrix\n");
        scanf("%d",&r2);
        send(sockfd, &r2, sizeof(r2),0);
        printf("enter the number of columns in first matrix\n");
        scanf("%d",&c2);
        send(sockfd, &c2, sizeof(c1),0);

        printf("enter mat2 elements\n");
        fill(mat2,r2,c2);
	send(sockfd, &mat2, sizeof(mat2),0);

	if(r1!=c2){
		printf("Invalid dimension\n");
	}

	recv(sockfd, result, sizeof(result),0);
	printf("Result matrix\n");
	display(result, r1, c2);
    	

}

void fill(int mat[][100],int r,int c){
        for (int i=0;i<r;i++)
                for(int j=0;j<c;j++){
                        scanf("%d",&mat[i][j]);
                }
        }


void display(int mat[][100],int r,int c){
        for(int i=0;i<r;i++){
                for (int j=0;j<c;j++){

                        printf("%d\t",mat[i][j]);
                }
                printf("\n");
        }
}


