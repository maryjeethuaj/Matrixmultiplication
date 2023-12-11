#include<stdio.h>
#include<stdlib.h>
/*
	int rows, col;
        printf("Enter the num of rows:");
        scanf("%d", &rows);
        printf("Enter the num of col:");
        scanf("%d", &col);
        int mat1[rows][col], mat2[rows][col],result[rows][col];
*/

void fillmatrix(int **mat,int r,int c);
void printmatrix(int **mat,int r,int c);
void multiply(int **mat1, int **mat2,int rows, int co,int **result);

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

int main(){

	int rows, col;
	printf("Enter the num of rows:");
	scanf("%d", &rows);
	printf("Enter the num of col:");
        scanf("%d", &col);
//	int mat1[rows][col], mat2[rows][col],result[rows][col];

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
	multiply(mat1, mat2, rows, col, result);
	printmatrix(result, rows, col);

}

