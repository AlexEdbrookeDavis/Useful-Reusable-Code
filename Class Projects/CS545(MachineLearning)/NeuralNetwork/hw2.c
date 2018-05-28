#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <unistd.h>

#define LEARN_RATE 0.1
#define MOMENTUM 0.9
#define HIDDEN_COUNT 100
#define TRAIN_COUNT 30000

//training and testing data
double train[60000][785];
double test[10000][785];


double sigmoid(double in){
	return (1/(1 + exp(-in)));
}

void forwardprop(int k, double neu[785][100], double neuh[100][10], double train[60000][785], double hid[101], double out[10]){
	double inputsum;
	//find activation for each hidden node
	hid[0] = 1;
	for(int i = 1; i < HIDDEN_COUNT+1; i++){
		inputsum = 0.0;
		//bias to hidden node
		inputsum = neu[0][i];
		//rest to hidden node
		for(int j = 1; j < 785; j++){
			inputsum += neu[j][i] * train[k][j];
		}
		//apply sigmoid  and store for next layer
		hid[i] = sigmoid(inputsum);
	}

	//find activation for each output node
	for(int i = 0; i < 10; i++){
		inputsum = 0.0;
		//bias
		inputsum += neuh[0][i];
		//rest hidden data
		for(int j = 1; j < HIDDEN_COUNT + 1; j++){
			inputsum += neuh[j][i] * hid[j];
		}
		//apply sigmoid and store
		out[i] = sigmoid(inputsum);
	}
}

void backprop(int k, double neu[785][100], double neuh[100][10], double train[60000][785], double hid[101], double out[10], double momentumh[785], double momentum[101]){
	double error[10];
	double temp;
	double errsum;
	double errorh[101];
	//calc the output error
	for(int i = 0; i < 10; i++){
		if(i == train[k][0])
			error[i] = out[i] * (1 - out[i]) * (0.9 - out[i]);
		else
			error[i] = out[i] * (1 - out[i]) * (0.1 - out[i]);
	}

	//calc the hidden error
	for(int i = 0; i < HIDDEN_COUNT+1; i++){
		errsum = 0;
		for(int j = 0; j < 10; j++){
			errsum += neuh[i][j] * error[j];
		}
		errorh[i] = hid[i] * (1 - hid[i]) * errsum;
	}

	//update hidden to out weights
	for(int i = 0; i < HIDDEN_COUNT+1; i++){
		for(int j = 0; j < 10; j++){
			temp = LEARN_RATE * error[j] * hid[i];
			temp += MOMENTUM * momentum[i];
			neuh[i][j] += temp;
			momentum[i] = temp;
		}
	}

	//update input to hidden weights
	for(int i = 1; i < 785; i++){
		for(int j = 1; j < HIDDEN_COUNT+1; j++){
			temp = LEARN_RATE * errorh[j] * train[k][i];
			temp += MOMENTUM * momentumh[i];
			neu[i][j] += temp;
			momentumh[i] = temp;
		}
	}
}
int main(){
	srand(time(NULL));

	FILE *fp = fopen("mnist_train.csv", "r");
	FILE *fp2 = fopen("mnist_test.csv", "r");
	FILE *fp3 = fopen("output.csv", "w");
	FILE *fp4 = fopen("confusion.csv", "w");
	int confusion[10][10];


	//neural networki
	//785 input to n hidden weights
	double neu[785][100];
	//n hidden to 10 out weights
	double neuh[100][10];

	//activation values
	double hid[101];
	double out[10];

	//weight update variables
	int inputsum;
	int actual;
	int calc;
	double momentum[785];
	double momentumh[101];

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
	for(int i = 0; i < TRAIN_COUNT; i++){
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
	//input weights including bias
	for(int i = 1; i < HIDDEN_COUNT+1; i++){
		for(int j = 0; j < 785; j++){
			neu[j][i] = (double)rand() / (double)RAND_MAX - 0.5;
		}
	}
	//hidden weights including bias
	for(int i = 0; i < HIDDEN_COUNT+1; i++){
		for(int j = 0; j < 10; j++){
			neuh[i][j] = (double)rand() / (double)RAND_MAX - 0.5;
		}
	}
	printf("done loading\n");

	//accuracy calculations
	acc = 0.0;
	//iterate over all training data
	for(int k = 0; k < TRAIN_COUNT; k++){
		max = -1;
		maxval = -99999;

		//find weight total for each hidden node
		forwardprop(k, neu, neuh, train, hid, out);

		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(out[i] > maxval){
				max = i;
				maxval = out[i];
			}
		}

		//add to accuracy if percetron best guess is correct
		if(max == train[k][0])
			acc = acc + 1;
	}
	printf("accuracy train set: %lf\n", acc / TRAIN_COUNT);
	fprintf(fp3, "%f,", acc/TRAIN_COUNT);
	acc = 0.0;
	//iterate over all test data
	for(int k = 0; k < 10000; k++){
		max = -1;
		maxval = -99999;

		//find weight total for each perceptron output
		forwardprop(k, neu, neuh, test, hid, out);

		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(out[i] > maxval){
				max = i;
				maxval = out[i];
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
		for(int i = 0; i < 785; i++){
			momentum[i] = 0;
		}
		for(int i = 0; i < HIDDEN_COUNT+1; i++){
			momentumh[i] = 0;
		}
		for(int k = 0; k < TRAIN_COUNT; k++){

			//forwardpropagate
			forwardprop(k, neu, neuh, train, hid, out);
			//backpropagate
			//printf("outtestforward: %lf\n", out[5]);
			backprop(k, neu, neuh, train, hid, out, momentumh, momentum);
			if(out[5] != out[5]){
				printf("Fail\n");
			}
			//sleep(1);
		}
		//accuracy calculations
		acc = 0.0;
		//iterate accuracy over all training data
		for(int k = 0; k < TRAIN_COUNT; k++){
			max = -1;
			maxval = -99999;
	
			//find weight total for each perceptron output
			forwardprop(k, neu, neuh, train, hid, out);
	
			//find best guess over perceptrons
			for(int i = 0; i < 10; i++){
				if(out[i] > maxval){
					max = i;
					maxval = out[i];
				}
			}
	
			//add to accuracy if percetron best guess is correct
			if(max == train[k][0])
				acc = acc + 1;
		}
		printf("accuracy train set: %lf\n", acc / TRAIN_COUNT);
		fprintf(fp3, "%f,", acc/TRAIN_COUNT);
		acc = 0.0;
		//iterate accuracy over all test data
		for(int k = 0; k < 10000; k++){
			max = -1;
			maxval = -99999;
	
			//find total for each output
			forwardprop(k, neu, neuh, test, hid, out);
	
			//find best guess over perceptrons
			for(int i = 0; i < 10; i++){
				if(out[i] > maxval){
					max = i;
					maxval = out[i];
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
		max = -1;
		maxval = -99999;
	
		//find weight total for each perceptron output
		forwardprop(k, neu, neuh, test, hid, out);
	
		//find best guess over perceptrons
		for(int i = 0; i < 10; i++){
			if(out[i] > maxval){
				max = i;
				maxval = out[i];
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
