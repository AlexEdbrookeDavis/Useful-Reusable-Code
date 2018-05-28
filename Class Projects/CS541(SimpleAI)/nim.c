#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <utility>
#include <cmath>

#define GRID_SIZE 3
int ABMIN(int pileCount, int pile[999], int a, int b);
int ABMAX(int action[2], int pileCount, int pile[999], int a, int b);

int victoryTest(int pileCount, int pile[999]) {
	for(int i = 0; i < pileCount; i++) {
		if(pile[i] != 0) {
			return 0;
		}
	}
	return 1;
}

int ABMIN(int pileCount, int pile[999], int a, int b) {
	int min;
	int newpile[999];
	int blanks[2];

	for(int i = 0; i < pileCount; i++) {
		newpile[i] = pile[i];
	}

	if(victoryTest(pileCount, pile) == 1) {
		return 0;
	}

	int v = 5000;

	for(int i = 0; i < pileCount; i++) {
		for(int j = 1; j <= pile[i]; j++) {
			newpile[i] -= j;
			min = ABMAX(blanks, pileCount, newpile, a, b);
			newpile[i] += j;

			if(min < v) {
				v = min;
			}
			if(v <= a) {
				return v;
			}
			if(v < b) {
				b = v;
			}
		}
	}
	return v;
}

int ABMAX(int action[2], int pileCount, int pile[999], int a, int b) {
	int min;
	int newpile[999];
	for(int i = 0; i < pileCount; i++) {
		newpile[i] = pile[i];
	}

	if(victoryTest(pileCount, pile) == 1) {
		return 1;
	}

	int v = -5000;

	//printf("startingloop pilecount: %d\n", pileCount);
	for(int i = 0; i < pileCount; i++) {
		for(int j = 1; j <= pile[i]; j++) {
			//printf("i: %d, j: %d\n", i, j);
			newpile[i] -= j;
			min = ABMIN(pileCount, newpile, a, b);
			//printf("min: %d\n", min);
			newpile[i] += j;

			if(min > v) {
				action[0] = i;
				action[1] = j;
				v = min;
			}
			if(v >= b) {
				return v;
			}
			if(v > a) {
				a = v;
			}
		}
	}
	return v;
}

void AB(int action[2], int pileCount, int pile[999]){
	int value = ABMAX(action, pileCount, pile, -5000, 5000);
}

int main() {
        int pileCount;
	int pile[999];
	int turn;
	int err;
	char temp, temp2;
	int action[2];

	printf("\nHow many piles?:");
	err = scanf("%d%c", &pileCount, &temp);
	while (err !=2 || temp!='\n') {
		while((temp2 = getchar()) != '\n' && temp2 != EOF);
		printf("\nHow many piles?:");
		err = scanf("%d%c", &pileCount, &temp);
	}

        for(int i = 0; i < pileCount; i++) {
		printf("\nHow many in pile %d?:", i + 1);
		err = scanf("%d%c", &pile[i], &temp);
		while (err !=2 || temp!='\n') {
			while((temp2 = getchar()) != '\n' && temp2 != EOF);
			printf("\nHow many in pile %d?:", i + 1);
			err = scanf("%d%c", &pile[i], &temp);
		}
        }

	printf("\nwho first (0 computer, 1 player)?:");
	err = scanf("%d%c", &turn, &temp);
	while (err !=2 || temp!='\n') {
		while((temp2 = getchar()) != '\n' && temp2 != EOF);
		printf("\nwho first?:");
		err = scanf("%d%c", &turn, &temp);
	}

        //5 test iterations
	while(true) {
		if(turn == 0) {
			AB(action, pileCount, pile);

			pile[action[0]] -= action[1];

			printf("Computers turn!\n");
			printf("Removing %d from pile %d\n", action[1], action[0] + 1);
			for(int i = 0; i < pileCount; i++) {
				printf("Pile %d: %d\n", i+1, pile[i]);
			}

			
			if(victoryTest(pileCount, pile) == 1) {
				printf("The computer lost!\n");
				return 0;
			}
			turn = 1;
		}
		if(turn == 1) {
			//collent legal action
			while(true) {
				printf("Players turn!\n");
				printf("\nwhat pile?:");
				err = scanf("%d%c", &action[0], &temp);
				while (err !=2 || temp!='\n') {
					while((temp2 = getchar()) != '\n' && temp2 != EOF);
					printf("\nwhat pile?:");
					err = scanf("%d%c", &action[0], &temp);
				}
				action[0]--;
				if((action[0] < 0) || (action[0] > pileCount)) {
					printf("Illigal pile!\n");
					continue;
				}

				printf("\nhow much from pile?:");
				err = scanf("%d%c", &action[1], &temp);
				while (err !=2 || temp!='\n') {
					while((temp2 = getchar()) != '\n' && temp2 != EOF);
					printf("\nhow much from pile?:");
					err = scanf("%d%c", &action[1], &temp);
				}
				if((action[1] < 0) || (action[1] > pile[action[0]])) {
					printf("Illigal pile grab count!\n");
					continue;
				}

				printf("Removing %d from pile %d\n", action[1], action[0] + 1);
				pile[action[0]] -= action[1];

				//test for complete
				
				if(victoryTest(pileCount, pile) == 1) {
					printf("The computer won!\n");
					return 0;
				}

        			for(int i = 0; i < pileCount; i++) {
					printf("Pile %d: %d\n", i+1, pile[i]);
				}

				break;
			}
			turn = 0;
		}
        }
	return 1;
}
