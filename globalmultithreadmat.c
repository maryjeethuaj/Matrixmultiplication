#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int rows1, col1,rows2,col2;
int **mat1, **mat2, **result;

pthread_mutex_t mut;
void fillmatrix(int **mat,int r,int c);
void printmatrix(int **mat,int r,int c);
void multiply(void *args);

void fillmatrix(int **mat,int r,int c){
        int i,j;
	printf("Enter the matrix elements");
        for(i=0;i<r;i++){
                for(j=0;j<c;j++)
                {
                        printf("Enter the elements:");
                        scanf("%d",&mat[i][j]);
                }
        }
}


void printmatrix(int **mat,int r,int c){
        int i,j;
	printf("Displaying the matrix\n");
        for(i=0;i<r;i++){
                for(j=0;j<c;j++){
                        printf("%d\t",mat[i][j]);
                }
		printf("\n");
        }
}

void multiply(void *args){

	int t=*(int *) args;
	int i,j,k;
//	pthread_mutex_lock(&mut);
        for(i=t;i<t+1;i++){
                for(j=0;j<col2;j++){
                        result[i][j]=0;
                        for(k=0;k<rows2;k++){
                                result[i][j]+=mat1[i][k]*mat2[k][j];
                        }
                
                }
                printf("\n");
        }
 //       printf("Resultant matrix of thread %d is:\n",t);
//	printmatrix(result, rows1, col2);

//        pthread_mutex_lock(&mut);

}
	

int main(){

	printf("Enter the num of rows in matrix1:");
	scanf("%d", &rows1);
	printf("Enter the num of column in matrix1:");
        scanf("%d", &col1);
	printf("Enter the num of rows in matrix2:");
        scanf("%d", &rows2);
        printf("Enter the num of column in matrix2:");
        scanf("%d", &col2);


//	int **mat1, **mat2, **result;
	mat1=(int **)malloc(rows1*sizeof(int*));
	int i,j,k;
	for(i=0;i<rows1;i++)
		mat1[i]=(int*)malloc(col1*sizeof(int));

        mat2=(int **)malloc(rows2*sizeof(int*));
        for(i=0;i<rows2;i++)
                mat2[i]=(int*)malloc(col2*sizeof(int));

	result=(int **)malloc(rows1*sizeof(int*));
        for(i=0;i<rows1;i++)
                result[i]=(int*)malloc(col2*sizeof(int));


	fillmatrix(mat1, rows1, col1);
	fillmatrix(mat2, rows2, col2);
	printmatrix(mat1, rows1, col1);
	printmatrix(mat2, rows2, col2);

	pthread_t t_id[rows1];
	int threadno[rows1];
	for(int i=0; i<rows1; i++){
			threadno[i]=i;
                        pthread_create(&t_id[i], NULL, multiply, (void*)&threadno[i]);
                }

	for(int i=0;i<rows1;i++){
		pthread_join(t_id[i], NULL);
	}


	printmatrix(result, rows1, col2);
//	pthread_mutex_destroy(&mat);
}


