#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct matrix{
	int **mat1;
	int **mat2;
	int rows;
	int col;
	int **result;
	int threadno;
};

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
	
	struct matrix *mat=(struct matrix*)args;
	int i,j,k;

	pthread_mutex_lock(&mut);
	for(i=mat->threadno;i<mat->threadno+1;i++){
		for(j=0;j<mat->col;j++){
			mat->result[i][j]=0;
			for(k=0;k<mat->rows;k++){
				mat->result[i][j]+=mat->mat1[i][k]*mat->mat2[k][j];
			}
		
		}
		printf("\n");
	}
	printf("Resultant matrix of thread %d is:\n",mat->threadno);
	pthread_mutex_lock(&mut);
}



/*
void multiply(int **mat1, int **mat2,int rows, int col,int **result){
	int i,j,k,product;
	for(i=0;i<rows;i++){
		for(j=0;j<col;j++){
			result[i][j]=0;
			for(k=0;k<rows;k++){
				result[i][j]+=mat1[i][k]*mat2[k][j];	
			}	
		}
	}
	//result[i][j]=product;
}
*/

int main(){

	int rows, col;
	printf("Enter the num of rows:");
	scanf("%d", &rows);
	printf("Enter the num of col:");
        scanf("%d", &col);

	int **mat1, **mat2, **result;
	mat1=(int **)malloc(rows*sizeof(int*));
	int i,j,k;
	for(i=0;i<rows;i++)
		mat1[i]=(int*)malloc(col*sizeof(int));

        mat2=(int **)malloc(rows*sizeof(int*));
        for(i=0;i<rows;i++)
                mat2[i]=(int*)malloc(col*sizeof(int));

	result=(int **)malloc(rows*sizeof(int*));
        for(i=0;i<rows;i++)
                result[i]=(int*)malloc(col*sizeof(int));


	fillmatrix(mat1, rows, col);
	fillmatrix(mat2, rows, col);
	printmatrix(mat1, rows, col);
	printmatrix(mat2, rows, col);

	pthread_t t_id[rows];
	struct matrix mat;
	for(int i=0; i<rows; i++){
			mat.threadno=i;
                        pthread_create(&t_id[i], NULL, multiply, &mat);
                }

	for(int i=0;i<rows;i++){
		pthread_join(t_id[i], NULL);
	}


	printmatrix(result, rows, col);
	pthread_mutex_destroy(&mat);
}


