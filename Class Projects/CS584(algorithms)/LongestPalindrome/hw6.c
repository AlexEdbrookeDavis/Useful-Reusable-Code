#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char string[100000];


int max(long a, long b){
	if(a < b)
		return b;
	else 
		return a;
}

void pali(long itr){
	char out[100000];
	long len = strlen(string);
	int L[len][len];  

	int path[len][len];


	for (long i = 0; i < len; i++) {
		L[i][i] = 1;
		path[i][i]=0;
	}


	long j;
	for (long cl = 2; cl <= len; cl++) {
		for (long i = 0; i < len - cl + 1; i++) {
			j = i + cl - 1;
			if (string[i] == string[j] && cl == 2) {
				L[i][j] = 2;
				path[i][j] = 0;     
			}
			else if (string[i] == string[j]) {
				L[i][j] = L[i + 1][j - 1] + 2;
				path[i][j] = 0;
			}
			else {
				if(L[i][j - 1] > L[i + 1][j]) {
					L[i][j] = L[i][j - 1];
					path[i][j] = 1;                    
				}
				else {
					L[i][j] = L[i + 1][j];
					path[i][j] = 2;  
				}
			}
		}
	}

	long loc = 0;
	long x = 0;
	long y = len - 1;

	while(x <= y) {
		if(path[x][y] == 0) {
			out[loc++] = string[x];
			x += 1;
			y -= 1;
		}
		else if(path[x][y] == 1)
			y -= 1;
		else if(path[x][y] == 2)
			x += 1;     
	}
	int loc2;
	if (L[0][len - 1] % 2 == 0)
		loc2 = loc;
	else
		loc2 = loc - 1;

	for(long k = 0; k < loc2; ++k)
		out[L[0][len - 1] - 1 - k] = out[k];

	out[loc + loc2] = '\0';


	printf("Case %ld: %s\n", itr, out);
}

int main(int argc, char *argv[]){
	long close;

	if(argc != 2){
		printf("invalid arg count!\n");
		return(-1);
	}

	FILE *fp = fopen(argv[1], "r");

	if( fp == NULL ){
		printf("unable to open file\n");
		return(-1);
	}

	long testcount;

	//read in number of test cases
	fscanf(fp, "%ld", &testcount);

	//read in and run each case
	for(long k = 0; k < testcount; k++){
		//salt
		fscanf(fp, "%s", &string);
		pali(k + 1);
	}
	return(0);
}
