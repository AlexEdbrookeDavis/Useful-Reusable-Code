#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEARN_RATE 0.1

//training and testing data
double train[60000][785];
double test[10000][785];

int main(){
	srand(time(NULL));

	FILE *fp = fopen("mnist_train.csv", "r");
	FILE *fp2 = fopen("mnist_test.csv", "r");
	FILE *fp3 = fopen("output.csv", "w");
	FILE *fp4 = fopen("confusion.csv", "w");
	int confusion[10][10];


	//perceptrons
	double per[10][785];

	//weight update variables
	int actual;
	int calc;

	//accuracy variables
	double totalw[10];
	int max;
	float maxval;
	float acc;

	char dump[1];

	if( fp == NULL ){
		printf("unable to open file\n");
		return(-1);
	}
	if( fp2 == NULL ){
		printf("unable to open file\n");
		return(-1);
	}

	//read in data sets
	for(int i = 0; i < 60000; i++){
		for(int j = 0; j < 785; j++){
			fscanf(fp, "%lf", &train[i][j]);
			if(j != 0){
				train[i][j] = train[i][j] / 255;
			}
			fscanf(fp, "%c", &dump[0]);
		}
	}
	for(int i = 0; i < 10000; i++){
		for(int j = 0; j < 785; j++){
			fscanf(fp2, "%lf", &test[i][j]);
			if(j != 0){
				test[i][j] = test[i][j] / 255;
			}
			fscanf(fp2, "%c", &dump[0]);
		}
	}

	//generate random weights
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 785; j++){
			per[i][j] = (double)rand() / (double)RAND_MAX - 0.5;
		}
	}
	printf("done loading\n");

	//accuracy calculations
	acc = 0.0;
	//iterate over all training data
	for(int k = 0; k < 60000; k++){
		//init
		for(int i = 0; i < 10; i++){
			totalw[i] = 0;
		}
		max = -1;
		maxval = -99999;

		//find weight total for each perceptron output
		for(int i = 0; i < 10; i++){
			//bias
			totalw[i] += per[i][0];
			//rest * input data
			for(int j = 1; j < 785; j++){
				totalw[i] += per[i][j] * train[k][j];
			}
		}

		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(totalw[i] > maxval){
				max = i;
				maxval = totalw[i];
			}
		}

		//add to accuracy if percetron best guess is correct
		if(max == train[k][0])
			acc = acc + 1;
	}
	printf("accuracy train set: %lf\n", acc / 60000.0);
	fprintf(fp3, "%f,", acc/60000.0);
	acc = 0.0;
	//iterate over all test data
	for(int k = 0; k < 10000; k++){
		//init
		for(int i = 0; i < 10; i++){
			totalw[i] = 0;
		}
		max = -1;
		maxval = -99999;

		//find weight total for each perceptron output
		for(int i = 0; i < 10; i++){
			//bias
			totalw[i] += per[i][0];
			//rest * input data
			for(int j = 1; j < 785; j++){
				totalw[i] += per[i][j] * test[k][j];
			}
		}

		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(totalw[i] > maxval){
				max = i;
				maxval = totalw[i];
			}
		}

		//add to accuracy if percetron best guess is correct
		if(max == test[k][0])
			acc = acc + 1;
	}
	printf("accuracy test set: %lf\n",  acc / 10000.0);
	fprintf(fp3, "%f\n", acc/10000.0);

	//run epochs
	for(int e = 1; e <= 50;e++){
		//iterate over training data
		for(int k = 0; k < 60000; k++){
			//update each perceptron
			for(int p = 0; p < 10; p++){
				//update perceptron total weight
				//bias weight
				totalw[p] = per[p][0] * 1;
				//rest of the weights
				for(int w = 1; w < 785; w++){
					totalw[p] += per[p][w] * train[k][w];
				}
				//is it the right perceptron?
				if(p == train[k][0]){
					actual = 1;
				} else {
					actual = 0;
				}

				//is it considered right by the perceptron?
				if(totalw[p] > 0){
					calc = 1;
				} else {
					calc = 0;
				}

				per[p][0] = per[p][0] + LEARN_RATE * (actual - calc) * 1;
				for(int w = 1; w < 785; w++){
					per[p][w] = per[p][w] + LEARN_RATE * (actual - calc) * train[k][w];
				}
			}
			//printf("per: %lf\n", per[0][0]);
		}
		//accuracy calculations
		acc = 0.0;
		//iterate accuracy over all training data
		for(int k = 0; k < 60000; k++){
			//init
			for(int i = 0; i < 10; i++){
				totalw[i] = 0;
			}
			max = -1;
			maxval = -99999;
	
			//find weight total for each perceptron output
			for(int i = 0; i < 10; i++){
				//bias
				totalw[i] += per[i][0];
				//rest * input data
				for(int j = 1; j < 785; j++){
					totalw[i] += per[i][j] * train[k][j];
				}
			}
	
			//find best guess over perceptrons
			for(int i = 0; i < 10; i++){
				if(totalw[i] > maxval){
					max = i;
					maxval = totalw[i];
				}
			}
	
			//add to accuracy if percetron best guess is correct
			if(max == train[k][0])
				acc = acc + 1;
		}
		printf("accuracy train set: %lf\n", acc / 60000.0);
		fprintf(fp3, "%f,", acc/60000.0);
		acc = 0.0;
		//iterate accuracy over all test data
		for(int k = 0; k < 10000; k++){
			//init
			for(int i = 0; i < 10; i++){
				totalw[i] = 0;
			}
			max = -1;
			maxval = -99999;
	
			//find weight total for each perceptron output
			for(int i = 0; i < 10; i++){
				//bias
				totalw[i] += per[i][0];
				//rest * input data
				for(int j = 1; j < 785; j++){
					totalw[i] += per[i][j] * test[k][j];
				}
			}
	
			//find best guess over perceptrons
			for(int i = 0; i < 10; i++){
				if(totalw[i] > maxval){
					max = i;
					maxval = totalw[i];
				}
			}
	
			//add to accuracy if percetron best guess is correct
			if(max == test[k][0])
				acc = acc + 1;
		}
		printf("accuracy test set: %lf\n", acc / 10000.0);
		fprintf(fp3, "%f\n", acc/10000.0);
	
		printf("epoc\n");
	}

	//confusion matrix
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			confusion[i][j] = 0;
		}
	}
	//iterate confusion over all test data
	for(int k = 0; k < 10000; k++){
		//init
		for(int i = 0; i < 10; i++){
			totalw[i] = 0;
		}
		max = -1;
		maxval = -99999;
	
		//find weight total for each perceptron output
		for(int i = 0; i < 10; i++){
			//bias
			totalw[i] += per[i][0];
			//rest * input data
			for(int j = 1; j < 785; j++){
				totalw[i] += per[i][j] * test[k][j];
			}
		}
	
		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(totalw[i] > maxval){
				max = i;
				maxval = totalw[i];
			}
		}
		//increment confusion matrix for predicted vs actual
		confusion[max][(int)test[k][0]]++;
	}
	//output matrix
	for(int i = 0; i < 10; i++){
		fprintf(fp4, "%d", confusion[i][0]);
		for(int j = 1; j < 10; j++){
			fprintf(fp4, ",%d", confusion[i][j]);
		}
		fprintf(fp4, "\n");
	}
	return(0);
}
