//There are two possible reasons for using Manhattan distance in the homework
//First, the time cost of calculating Manhattan distance is slightly cheaper then Euclidean distance
//Second, and more likely, Euclidean distance calculations will almost always output a number that cannot be accuratly expressed in decimal. This could lead to rounding errors leading to differing solutions making grading difficult.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct coord {
	long long x, y;
};

int compx(const void *x, const void *y){
	coord *cx = (coord*)x;
	coord *cy = (coord*)y;
	return(cx->x - cy->x);
}
int compy(const void *x, const void *y){
	coord *cx = (coord*)x;
	coord *cy = (coord*)y;
	return(cx->y - cy->y);
}

long long distance(coord x, coord y){
	long long dist = (long long)abs(x.x - y.x) + (long long)abs(x.y - y.y);
	return dist;
}

long brute(coord *x, long lengthx){
	long long close = 9999999999999;
	for(long i = 0; i < lengthx; i++)
		for(long j = i + 1; j < lengthx; j++){
			if(distance(x[i], x[j]) < close){
				close = distance(x[i], x[j]);
				//if(close == 220545451)
				//	printf("here: %lld, %lld, %lld, %lld, %ld, %ld, %ld\n", x[i].x, x[i].y, x[j].x, x[j].y, i, j, lengthx);
			}
		}
	return close;
}

long lineclose(coord *c, long length, long long dist){
	long close = dist;

	for(long i = 0; i < length; i++){
		for(long j = i + 1; j < length && (c[j].y - c[i].y) < close; j++){
			if(distance(c[i], c[j]) < close){
				close = distance(c[i], c[j]);
			}
		}
	}
	return close;
}

long closepair(coord xdata[], coord ydata[], long lengthx, long k){
	long close, closel, closer;
	
	//works
	if(lengthx <= 3)
		return brute(xdata, lengthx);

	long midloc = lengthx / 2 + (lengthx % 2 != 0);
	coord midcoord;
	midcoord.x = xdata[midloc].x;
	midcoord.y = xdata[midloc].y;
	//printf("midc: %ld\n",midcoord.x);

	coord yleft[lengthx];
	coord yright[lengthx];

	long llength = 0;
	long rlength = 0;

	//works
	for(long i = 0; i < lengthx; i++){
		if(ydata[i].x < midcoord.x){
			yleft[llength].x = ydata[i].x;
			yleft[llength].y = ydata[i].y;
			//if(ydata[i].y == 0)
			//	printf("left: %ld, %ld\n", i, llength);
			llength++;
		} 
		if(ydata[i].x >= midcoord.x){
			yright[rlength].x = ydata[i].x;
			yright[rlength].y = ydata[i].y;
			//if(ydata[i].y == 0)
			//	printf("right: %ld, %ld\n", i, rlength);
			rlength++;
		}
	}
	//if(k == 117){
	//	printf("left\n");
	//}
	closel = closepair(xdata, yleft, midloc, k);
	//if(k == 117){
	//	printf("right\n");
	//}
	closer = closepair(xdata + midloc, yright, lengthx - midloc, k);

	if(closel < closer)
		close = closel;
	else
		close = closer;
	coord middata[lengthx];
	long lengthm = 0;
	for(long i = 0; i < lengthx; i++) {
		if(abs(ydata[i].x - midcoord.x) < close){
			middata[lengthm].x = ydata[i].x;
			middata[lengthm].y = ydata[i].y;
			//if(middata[lengthm].y == 0)
			//	printf("allocate: %lld, %ld, %ld, %ld\n", ydata[i].y, lengthm, i, lengthx);
			lengthm++;
		}
	}

	close = lineclose(middata, lengthm, close);
	return close;
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
	long testlength;
	coord *xdata = (coord*)malloc(sizeof(coord) * 100000000);
	coord *ydata = (coord*)malloc(sizeof(coord) * 100000000);


	fscanf(fp, "%ld", &testcount);

	for(long k = 0; k < testcount; k++){
		fscanf(fp, "%ld", &testlength);
		for(int j = 0; j < testlength; j++){
			fscanf(fp, "%lld", &xdata[j].x);
			fscanf(fp, "%lld", &xdata[j].y);
			ydata[j].x = xdata[j].x;
			ydata[j].y = xdata[j].y;
		}


		qsort(xdata, testlength, sizeof(coord), compx);
		qsort(ydata, testlength, sizeof(coord), compy);

		//test alg
		close = closepair(xdata, ydata, testlength, k+1);
		printf("Case %ld: %ld\n", k+1, close);
	}
	return(0);
}
