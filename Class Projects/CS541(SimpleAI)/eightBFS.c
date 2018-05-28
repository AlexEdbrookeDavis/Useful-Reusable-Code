#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <utility>
#include <cmath>

#define GRID_SIZE 3

int dist(int loc, int val) {
	int dist = abs((loc % GRID_SIZE) - (val % GRID_SIZE)) + abs((loc / GRID_SIZE) - (val / GRID_SIZE));
	//printf("loc: %d\n", loc);
	//printf("val: %d\n", val);
	//printf("dist: %d\n", dist);
	return dist;
}

int displaceHuristic1(const int grid[GRID_SIZE*GRID_SIZE]) {
        int h = 0;
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
		if(grid[i] != i) {
    			h++; 
		}
        }
	return h;
}

int displaceHuristic2(const int grid[GRID_SIZE*GRID_SIZE]) {
        int h = 0;
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
		h += dist(i, grid[i]);
        }
	//printf("h: %d\n", h);
	return h;
}

int displaceHuristic3(const int grid[GRID_SIZE*GRID_SIZE]) {
        int h = 0;
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
		h += abs((i % GRID_SIZE) - (grid[i] % GRID_SIZE));
        }
	//printf("h: %d\n", h);
	return h;
}

struct node {
	int grid[GRID_SIZE * GRID_SIZE];
	int loc;

	bool operator<(const node &o) const {
		return displaceHuristic3(grid) > displaceHuristic3(o.grid);
	}
};

void swap(int *i, int *j) {
        int tmp = *i;
        *i = *j;
        *j = tmp;
}

int comp(int grid1[GRID_SIZE * GRID_SIZE], int grid2[GRID_SIZE * GRID_SIZE]) {
	for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
		if(grid1[i] != grid2[i]) {
			return 0;
		}
	}
	return 1;
}

void sucFinder(int sucVals[4][GRID_SIZE * GRID_SIZE], int grid[GRID_SIZE * GRID_SIZE]) {
        int swaploc1;
	int tmp;
	//printf("suc finder Code!\n");
   	//for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++) {
	//	printf("%d ", grid[i]);
	//}
	//printf("\n");
   
	 //init sucs
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
                for(int j = 0; j < 4; j++) {
                        sucVals[j][i] = grid[i];
                }
        }



        //find the blank
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
                if(sucVals[0][i] == (GRID_SIZE * GRID_SIZE) - 1) {
                        swaploc1 = i;
                }
        }
	//printf("swaploc: %d\n", swaploc1);
        //suc0: down move
        //test for validity
        if(swaploc1 < GRID_SIZE) {
                //failure marker
                sucVals[0][0] = -1;
        } else {
        	//swap for suc
        	swap(&sucVals[0][swaploc1], &sucVals[0][swaploc1 - GRID_SIZE]);
	}

        //suc0: up move
        //test for validity
        if(swaploc1 >= (GRID_SIZE * GRID_SIZE) - GRID_SIZE) {
                //failure marker
                sucVals[1][0] = -1;
        } else {
        	//swap for suc
        	swap(&sucVals[1][swaploc1], &sucVals[1][swaploc1 + GRID_SIZE]);
	}

        //suc0: right move
        //test for validity
        if((swaploc1 % GRID_SIZE) == 0) {
                //failure marker
                sucVals[2][0] = -1;
        } else {
        	//swap for suc
        	swap(&sucVals[2][swaploc1], &sucVals[2][swaploc1 - 1]);
	}

        //suc0: left move
        //test for validity
        if((swaploc1 % GRID_SIZE) == (GRID_SIZE - 1)) {
                //failure marker
                sucVals[3][0] = -1;
        } else {
        	//swap for suc
        	swap(&sucVals[3][swaploc1], &sucVals[3][swaploc1 + 1]);
	}

	/*for(int j = 0; j < 4; j++) {
   		for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++) {
			printf("%d ", sucVals[j][i]);
		}
		printf("\n");
	}*/
}

int goalTest(int grid[GRID_SIZE * GRID_SIZE]) {
        for(int i = 0; i < (GRID_SIZE * GRID_SIZE); i++) {
                if(grid[i] != i) {
                        return 0;
                }
        }
        return 1;
}

//bfs
int BFS(node start) {
	int visited[10000][GRID_SIZE*GRID_SIZE];
	int parent[10000];

	parent[0] = -1;
	for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++) {
		visited[0][i] = start.grid[i];
	}
	int   visitCount = 1;

	int suc[4][GRID_SIZE*GRID_SIZE];	
	int repeatFound;
	int out;
	int stepSum = 0;


	node u;

	std::priority_queue< node > pq;

	//start queue
	pq.push(start);

	//printf("done initilizing BFS\n");
	while(!pq.empty()) {
		//printf("looping BFS queue\n");
		u = pq.top();
		pq.pop();
		//printf("pop top\n");
		//for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++) {
		//	printf("%d ", u.grid[i]);
		//}
		//printf("\n");
		//done?
		if(visitCount == 1000) {
			printf("No solution found in 1000 steps!\n");
			return -1;
		}
		if(goalTest(u.grid)) {
			printf("0 1 2 3 4 5 6 7 8\n");
			out = parent[visitCount - 1];
			while(out != -1) {
				stepSum++;
				for(int i = 0; i < (GRID_SIZE*GRID_SIZE); i++) {
					printf("%d ", visited[out][i]);
				}
				printf("\n");
				out = parent[out];
			}
			return stepSum;
		}
		//printf("done goal test\n");

		//find successors
		sucFinder(suc, u.grid);
		//printf("found sucs\n");
		
		//check for new locations and add to queue
		for(int i = 0; i < 4; i++) {
			if(suc[i][0] != -1) {
				repeatFound = 0;
				for(int j = 0; j < visitCount; j++) {
					if(comp(visited[j], suc[i]) == 1) {
						repeatFound = 1;
						break;
					}
				}
				if(repeatFound == 1) {
					//printf("repeat found!\n");
					continue;
				}

				//add to visited, and queue
				node newN;
				for(int j = 0; j < (GRID_SIZE*GRID_SIZE); j++) {
					visited[visitCount][j] = suc[i][j];
					newN.grid[j] = suc[i][j];
					//printf("%d ", newN.grid[j]);
				}
				parent[visitCount] = u.loc;
				newN.loc = visitCount;
				//printf("\n");
				visitCount++;
				pq.push(newN);
			}
		}

	}
}

void randomizeArray(int *arr, int len)
{
        int j;
        int k;
        if(len > 1) {
                for(int i = 0; i < len - 1; i++) {
                        j = i + (rand() / (RAND_MAX / (len - i) + 1));
                        k = arr[j];
                        arr[j] = arr[i];
                        arr[i] = k;
                }
        }
}


int main() {
        int grid[GRID_SIZE * GRID_SIZE];
        srand(time(NULL));

	int stepSum = 0;
	int steptmp;
	int stepCount = 0;

        //5 test iterations
        for(int i = 0; i < 5; i++) {
        	node start;
		start.loc = 0;
                //initilize
                //non-random start
                for(int j = 0; j < (GRID_SIZE * GRID_SIZE); j++) {
                        start.grid[j] = j;
                }
                //randomize
                randomizeArray(start.grid, (GRID_SIZE * GRID_SIZE));

		printf("Solution Path number %d:\n", i + 1);
		steptmp = BFS(start);
		if(steptmp != -1) {
			stepSum += steptmp;
			stepCount++;
		}

        }
	printf("Average number of steps: %d\n", stepSum / 5);
	return 1;
}
