#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(long A[10^6], int p, int r){

	long temp;
	long ran = rand() % (r - p) + p;	
	temp = A[ran];
	A[ran] = A[r];
	A[r] = temp;

	long x = A[r];
	int i = p - 1;
	for(int j = p; j <= r - 1; j++){
		if(A[j] <= x){
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i+1];
	A[i+1] = A[r];
	A[r] = temp;
	return i + 1;
}

void quicksort(long A[10^6], int p, int r){
	if(p < r){
		int q = partition(A, p, r);
		quicksort(A, p, q-1);
		quicksort(A, q+1, r);
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));

	if(argc != 2){
		printf("invalid arg count!\n");
		return(-1);
	}

	FILE *fp = fopen(argv[1], "r");

	if( fp == NULL ){
		printf("unable to open file\n");
		return(-1);
	}

	long len;
	long len21;
	long data[10^6];
	long len22;
	long data2[10^6];

	fscanf(fp, "%ld", &len);

	for(long i = 0; i < len; i++){
		fscanf(fp, "%ld", &len21);
		for(int j = 0; j < len21; j++){
			fscanf(fp, "%ld", &data[j]);
		}

		fscanf(fp, "%ld", &len22);
		for(int j = 0; j < len22; j++){
			fscanf(fp, "%ld", &data2[j]);
		}
		quicksort(data2, 0, len22-1);
		long i2 = 0;
		long j2 = 0;
		long count = 0;
		while(i2 < len21){
			if(data[i2] < data2[j2]){
				i2++;
			}
			if(data[i2] == data2[j2]){
				count++;
				j2++;
			}
			if(data[i2] > data2[j2]){
				if(j2 == len22)
					break;
				j2++;
			}
		}
		printf("Case %ld: %ld\n", i+1, count);
	}

	return(0);
}
