#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <algorithm>

struct Triple{
	long val[3];
};

long findrank( long *subsetpar, long loc){
	if (subsetpar[loc] != loc)
		subsetpar[loc] = findrank(subsetpar, subsetpar[loc]);
 
	return subsetpar[loc];	
}

void mst(long test, long vertcount, long edgecount, std::map<long,long> component, std::map<long,Triple> edge){
	//mapping
        std::map<int,int>::iterator it;
        std::map<int,int>::reverse_iterator rit;
	long minedgeloc[vertcount];

	//size of component set
	long compcount = vertcount;
	long subsetpar[vertcount];
	long subsetrank[vertcount];

	//output
	long mstedge[edgecount];
	long mstcount = 0;

	//vars
	long left;
	long right;
	long weight;
	long compleft;
	long compright;

	for(long i = 0; i < vertcount; i++){
		mstedge[i] = 9999999;
	}

	for(long i = 0; i < compcount; i++){
		subsetpar[i]  = i;
		subsetrank[i] = 0;
		minedgeloc[i] = -1;
	}

	long mstweight = 0;

	while(compcount > 1){
		for(long i = 0; i < vertcount; i++){
			minedgeloc[i] = -1;
		}
		for(long i = 0; i < edgecount; i++){
			//left and right are vertices
			left      = edge[i].val[0];
			right     = edge[i].val[1];
			//weight of edge
			weight    = edge[i].val[2];
			//what component the verts are in
			compleft  = findrank(subsetpar, left);
			compright = findrank(subsetpar, right);
			//i is edge
			//check for useless edge
			if(compleft == compright){
				continue;
			}
			//printf("test %ld %ld %ld %ld\n", compleft, compright, left, right);
			/*if(weight == 3){
				printf("testm %ld %ld\n", edge[minedgeloc[compleft]].val[2], edge[minedgeloc[compright]].val[2]);
				printf("testm %ld \n", edge[minedgeloc[i]].val[2]);
			}*/
			//check if weight is best found for components
			if((minedgeloc[compleft] == -1) || (weight < edge[minedgeloc[compleft]].val[2])){
				//save edgeloc and it's value
				minedgeloc[compleft] = i;
			}
			if((minedgeloc[compright] == -1) || (weight < edge[minedgeloc[compright]].val[2])){
				//save edgeloc and it's value
				minedgeloc[compright] = i;
			}
		}

		for(long i = 0; i < vertcount; i++){
			//printf("test: %ld\n", compcount);
			//printf("min: %ld\n",edge[minedgeloc[i]].val[2]);
			if(edge[minedgeloc[i]].val[2] != -1){
				weight= edge[minedgeloc[i]].val[2];
				left  = edge[minedgeloc[i]].val[0];
				right = edge[minedgeloc[i]].val[1];
				compleft  = findrank(subsetpar, left);
				compright = findrank(subsetpar, right);




				//printf("test: %ld\n", compcount);
				if(compleft == compright){
					continue;
				}
				//printf("test2 %ld\n", minedgeloc[i]);

				mstweight += weight;
				mstedge[mstcount] = minedgeloc[i] + 1;
				mstcount++;
				compcount--;
				//subsetpar
				//subsetrank
				long rootleft  = findrank(subsetpar, left);
				long rootright = findrank(subsetpar, right);
				if(subsetrank[rootleft] < subsetrank[rootright]){
					subsetpar[rootleft] = rootright;
				}
				else if(subsetrank[rootleft] > subsetrank[rootright]){
					subsetpar[rootright] = rootleft;
				}
				else {
					subsetpar[rootright] = rootleft;
					subsetrank[rootleft]++;
				}
			}
		}
	}

	std::sort(mstedge, mstedge + vertcount);
	printf("Case %ld:", test);
	for(long i = 0; i < vertcount; i++){
		if(mstedge[i] != 9999999)
			printf(" %ld", mstedge[i]);
	}
	printf("\n");
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
	long verticecount;
	long edgecount;
	long tempv1;
	long tempv2;
	long tempw;
	std::map<long, Triple> edges;
	std::map<long,long> vertices;

	//read in number of test cases
	fscanf(fp, "%ld", &testcount);

	//read in and run each case
	for(long k = 0; k < testcount; k++){
		//vertice and edge count
		fscanf(fp, "%ld", &verticecount);
		fscanf(fp, "%ld", &edgecount);

		for(long i = 0; i < verticecount; i++){
			vertices[i] = i;
		}
		for(long i = 0; i < edgecount; i++){
			//vertex1
			fscanf(fp, "%ld", &tempv1);
			//vertex2
			fscanf(fp, "%ld", &tempv2);
			//weight
			fscanf(fp, "%ld", &tempw);
			//save it
			edges[i] = (Triple) { tempv1 - 1, tempv2 - 1, tempw};
		}
		mst(k + 1, verticecount, edgecount, vertices, edges);
		edges.clear();
		vertices.clear();
	}
	return(0);
}
