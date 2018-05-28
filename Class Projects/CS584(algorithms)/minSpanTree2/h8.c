#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <algorithm>
#include <queue>
//#include <iterator>

struct Triple{
	long val[3];
};

long min(long a, long b){
	if(a < b)
		return a;
	return b;
}

long bfs(long vertcount, long *P, std::map<std::pair<long, long>, long> capacity, std::map<std::pair<long, long>, long> residual, long sink, long source, std::map<std::pair<long, long>, long> flowm){

	long M[vertcount];
	//long (*capacity)[vertcount] = static_cast<long (*)[vertcount]>(vcapacity);
	//long (*residual)[vertcount] = static_cast<long (*)[vertcount]>(vresidual);
	//long (*flowm)[vertcount] = static_cast<long (*)[vertcount]>(vflowm);
	//printf("in function\n");	
	for(long i = 0; i < vertcount; i++){
		P[i] = -1;
	}
	P[source] = -2;
	M[source] = 9999999;

	std::queue<long> Q;

	long temp;

	//start
	Q.push(source);
	while(Q.size() > 0){
		temp = Q.front();
		Q.pop();
		//printf("temp: %ld\n", temp);
		for(long i = 0; i < vertcount; i++){
			//printf("residual test: %ld %ld %ld\n", temp, i, residual[std::make_pair(temp, i)]);
			//printf("P: %ld\n", P[i]);
			if((residual[std::make_pair(temp, i)] > 0) && (P[i] == -1) && (i != temp)){
				//printf("inner bfs: %ld %ld\n", residual[temp][i], P[i]);
				P[i] = temp;
				M[i] = min(M[temp], capacity[std::make_pair(temp, i)] - flowm[std::make_pair(temp, i)]);
				if(i != sink){
					Q.push(i);
				} else {
					return M[sink];
				}
			}
		}
	}
	return 0;
}

void mst(long test, long vertcount, long source, long sink, long edgecount, std::map<std::pair<long, long>, long> capacity){
	//long (*capacity)[vertcount] = static_cast<long (*)[vertcount]>(vcapacity);
	//printf("code start\n");

	long m;
	long u;
	long v;

	//residual is capacity
	std::map<std::pair<long, long>, long> residual;
	std::copy(capacity.begin(), capacity.end(), std::inserter(residual, residual.end()) );
	//printf("test number: %ld\n", residual[std::make_pair(2, 1)]);
	//for(long i = 0; i < vertcount; i++){
	//	for(long j = 0; j < vertcount; j++){
	//		residual[std::make_pair(i, j)] = capacity[std::make_pair(i, j)];
	//		printf("code loop\n");
	//	}
	//}

	//printf("code start\n");
	//flow and it's path
	long flow = 0;
	std::map<std::pair<long, long>, long> flowm;
	//for(long i = 0; i < vertcount; i++){
	//	for(long j = 0; j < vertcount; j++){
	//		flowm[std::make_pair(i, j)] = 0;
	//	}
	//}
	//printf("code start\n");

	//bfs output
	long P[vertcount];

	//printf("in mst\n");	
	//runtime
	//printf("code start\n");
	while(true){
		m = bfs(vertcount, P, capacity, residual, sink, source, flowm);
		//printf("after bfs m: %ld\n", m);	

		if(m == 0){
			break;
		}
		flow = flow + m;

		v = sink;
		while(v != source){
			u = P[v];
			//printf("loop in reverse2 %ld %ld %ld\n", u, v, m);	
			flowm[std::make_pair(u, v)] = flowm[std::make_pair(u, v)] + m;
			flowm[std::make_pair(v, u)] = flowm[std::make_pair(v, u)] - m;
			residual[std::make_pair(u, v)] = residual[std::make_pair(u, v)] - m;
			residual[std::make_pair(v, u)] = residual[std::make_pair(v, u)] + m;
			v = u;
		}
	}
	printf("Case %ld: %ld\n", test, flow);
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
	long source;
	long sink;
	long verticecount;
	long edgecount;
	long tempv1;
	long tempv2;
	long tempw;
	std::map<long,long> vertices;
	std::map<std::pair<long, long>, long> edges;

	//read in number of test cases
	fscanf(fp, "%ld", &testcount);

	//read in and run each case
	for(long k = 0; k < testcount; k++){
		//vertice count
		fscanf(fp, "%ld", &verticecount);

		//init edges
		//for(long i = 0; i < verticecount; i++){
		//	for(long j = 0; j < verticecount; j++){
		//		edges[i][j] = 0;
		//	}
		//}

		//source and sink (same line)
		fscanf(fp, "%ld", &source);
		fscanf(fp, "%ld", &sink);
		source--;
		sink--;
		//edge count
		fscanf(fp, "%ld", &edgecount);

		//init vert values
		for(long i = 0; i < verticecount; i++){
			vertices[i] = i;
		}

		//read edges
		for(long i = 0; i < edgecount; i++){
			//vertex1
			fscanf(fp, "%ld", &tempv1);
			//vertex2
			fscanf(fp, "%ld", &tempv2);
			//weight
			fscanf(fp, "%ld", &tempw);
			//save it
			edges[std::make_pair(tempv1 - 1, tempv2 - 1)] = tempw;
			//edges[std::make_pair(tempv2, tempv1)] = tempw;
		}
		mst(k + 1, verticecount, source, sink, edgecount, edges);
		vertices.clear();
	}
	return(0);
}
