#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>

unsigned long data[1000000000];

unsigned long lpow(unsigned long base, unsigned long exp){
	unsigned long long counter = 1;
	for(unsigned long i = 0; i < exp; i++){
		counter *= base;
	}
	return counter;
}

void hash(unsigned long salt, unsigned long l, unsigned long n, long k){
	std::map<int,int> output;
	std::map<int,int>::iterator it;
	std::map<int,int> count;
	long maxval;
	long maxloc;
	unsigned long dest;
	unsigned long long pow1 = lpow(2, 32);
	unsigned long long pow2 = lpow(2, 32 - l);
	unsigned long long pow3 = lpow(2, l);
	unsigned long long saltl = salt;
	//place data into hashed slots
	for(long i = 0; i < n; i++){
		dest = ((saltl * data[i]) % pow1)/(pow2);
		output[dest]++;
		//printf("dest: %lu\n", dest);
	}
	//count the number of slots with each count
	for(it = output.begin(); it != output.end(); it++){
		count[it->second]++;
	}
	//print counts
	printf("Case %ld:", k+1);
	while(true){
		//find highest count
		maxval = -1;
		for(it = count.begin(); it != count.end(); it++){
			if(maxval < it->second){
				maxloc = it->first;
				maxval = it->second;
			}
		}
		if(maxval == -1)
			break;
		count[maxloc] = -1;
		printf(" %ld %ld", maxloc, maxval);
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	srand(time(NULL));
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
	unsigned long salt;
	unsigned long l;
	unsigned long n;


	//read in number of test cases
	fscanf(fp, "%ld", &testcount);

	//read in and run each case
	for(long k = 0; k < testcount; k++){
		//salt
		fscanf(fp, "%lu", &salt);
		//printf("%lu\n", salt);
		//hash table 2^l size
		fscanf(fp, "%lu", &l);
		//printf("%lu\n", l);
		//hashing count
		fscanf(fp, "%ld", &n);
		//printf("%lu\n", n);
		
		for(int j = 0; j < n; j++){
			fscanf(fp, "%lu", &data[j]);
			//printf("%lu ", data[j]);
		}
		//printf("\n");
		//test alg
		hash(salt, l, n, k);
	}
	return(0);
}
