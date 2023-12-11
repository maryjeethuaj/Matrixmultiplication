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

int check(int exp, const char *msg);
void fill(int mat[][100],int r,int c);
void display(int mat[][100],int r,int c);

int r1,c1,r2,c2;
int mat1[100][100],mat2[100][100],result[100][100];

int main()
{
    int sockfd = 0, connfd=0;
    check(sockfd=socket(AF_INET, SOCK_STREAM, 0),"Socket Error");
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0',sizeof(recvBuff));
    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    check(connfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)),"Connect Error");
 /*   if(connfd<0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
*/
    	printf("enter the number of rows of first matrix\n");
        scanf("%d",&r1);
	check(send(sockfd, &r1, sizeof(r1),0),"Send Error");
        printf("enter the number of columns in first matrix\n");
        scanf("%d",&c1);
	check(send(sockfd, &c1, sizeof(c1),0),"Send Error");

        printf("enter mat1 elements\n");
        fill(mat1,r1,c1);
	display(mat1,r1,c1);
	check(send(sockfd, &mat1, sizeof(mat1),0),"Send Error");

	printf("enter the number of rows of first matrix\n");
        scanf("%d",&r2);
        check(send(sockfd, &r2, sizeof(r2),0),"Send Error");
        printf("enter the number of columns in first matrix\n");
        scanf("%d",&c2);
        check(send(sockfd, &c2, sizeof(c1),0),"Send Error");

        printf("enter mat2 elements\n");
        fill(mat2,r2,c2);
	display(mat2,r2,c2);
	check(send(sockfd, &mat2, sizeof(mat2),0),"Send Error");

	if(r1!=c2){
		printf("Invalid dimension\n");
	}

//	display(mat1,r1,c1);
//	display(mat2,r2,c2);
	check(recv(sockfd, result, sizeof(result),0),"Receive Error");
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

int check(int exp, const char *msg){
	if(exp==-1){
		perror(msg);
		exit(1);
	}
}

