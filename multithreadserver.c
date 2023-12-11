#include <sys/socket.h>
#include <pthread.h>
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
void *startfunc(void *id);
int check(int exp, const char *msg);

int r1=0,c1=0,r2=0,c2=0;
int mat1[100][100],mat2[100][100],result[100][100];


int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];

    check(listenfd = socket(AF_INET, SOCK_STREAM, 0),"Socket Error");
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

/*    struct timeval timeout;
    timeout.tv_sec = 5;  // 5 seconds
    timeout.tv_usec = 0;
   if (setsockopt(listenfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("setsockopt");
        exit(1);
    	}
*/

   int enable = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    check(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)),"Bind Error"); 

    listen(listenfd, 10); 
	
    pthread_t connthread;
    while(1)
    {
        check(connfd = accept(listenfd, (struct sockaddr*)NULL, NULL),"Accept Error"); 
	
	//pthread_t connthread;
	check(pthread_create(&connthread, NULL, startfunc, (void*)&connfd),"Pthread create Error");

    }
        check(pthread_join(connthread, NULL),"Pthread join Error");

        close(connfd);
     //   sleep(1);
     
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

void *startfunc(void *id){

	int connfd=*(int*)id;
	check(recv(connfd, &r1, sizeof(r1),0),"Receive error");
       	check(recv(connfd, &c1, sizeof(c1),0),"Receive error");
        check(recv(connfd, &mat1, sizeof(mat1),0),"Receive error");
        printf("mat1\n");
        display (mat1,r1,c1);

        check(recv(connfd, &r2, sizeof(r1),0),"Receive error");
        check(recv(connfd, &c2, sizeof(c1),0),"Receive error");
        check(recv(connfd, &mat2, sizeof(mat1),0),"Receive error");
        printf("mat2\n");
        display (mat2,r2,c2);

        pthread_t tid[r1];
        int i,tno[r1];
        for(i=0;i<r1;i++)
        {
            tno[i]=i;
            check(pthread_create(&tid[i],NULL,matMul,(void*)&tno[i]),"Pthread create Error StartFunction");
        }

        for(i=0;i<r1;i++)
        {
            pthread_join(tid[i],NULL);
        }

       check(send(connfd, result, sizeof(result),0),"Send Error");

}

int check(int exp, const char *msg){
	if(exp==-1){
		perror(msg);
		exit(1);
	}
}
