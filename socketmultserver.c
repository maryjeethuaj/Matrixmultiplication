#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

void* matMul(void* args);

int r1,c1,r2,c2;
int mat1[100][100],mat2[100][100],result[100][100];


int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	
	recv(connfd, &r1, sizeof(r1),0);
	recv(connfd, &c1, sizeof(c1),0);
	recv(connfd, &mat1, sizeof(mat1),0);
	printf("mat1\n");
        display (mat1,r1,c1);
	
	recv(connfd, &r2, sizeof(r1),0);
        recv(connfd, &c2, sizeof(c1),0);
        recv(connfd, &mat2, sizeof(mat1),0);
        printf("mat2\n");
        display (mat2,r2,c2);

	pthread_t tid[r1];
        int i,tno[r1];
        for(i=0;i<r1;i++)
        {
            tno[i]=i;
            pthread_create(&tid[i],NULL,matMul,(void*)&tno[i]);
        }
 
        for(i=0;i<r1;i++)
        {
            pthread_join(tid[i],NULL);
        }
	
	send(connfd, result, sizeof(result),0);

	
        close(connfd);
        sleep(1);
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


void* matMul(void* args)
{
 
        int t=*(int*)args;
        for (int i = t; i < t+1; i++)
        {
                for (int j = 0; j < c2; j++)
                {
                        result[i][j] = 0;
                        for (int k = 0; k < c1; k++)
                        {
                                result[i][j] += mat1[i][k] * mat2[k][j];
                        }
                }
        }
}
/*
void *startfunc(){
	recv(connfd, &r1, sizeof(r1),0);
        recv(connfd, &c1, sizeof(c1),0);
        recv(connfd, &mat1, sizeof(mat1),0);
        printf("mat1\n");
        display (mat1,r1,c1);

        recv(connfd, &r2, sizeof(r1),0);
        recv(connfd, &c2, sizeof(c1),0);
        recv(connfd, &mat2, sizeof(mat1),0);
        printf("mat2\n");
        display (mat2,r2,c2);

        pthread_t tid[r1];
        int i,tno[r1];
        for(i=0;i<r1;i++)
        {
            tno[i]=i;
            pthread_create(&tid[i],NULL,matMul,(void*)&tno[i]);
        }

        for(i=0;i<r1;i++)
        {
            pthread_join(tid[i],NULL);
        }

        send(connfd, result, sizeof(result),0);

}
*/
