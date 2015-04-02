//
//  main.cpp
//  TSP
//
//  Created by 刘彦超 on 14/10/25.
//  Copyright (c) 2014年 刘彦超. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

using namespace std;

struct point{
  int x;
  int y;
};

typedef struct point Point;

Point nodes[20];

double edges[20][20];

double cache[20][1048576];

double dynamicPlanning(int state,int pos,int cnt);

int main(int argc, const char * argv[]){
  //freopen("data.in","r",stdin);
  int T=0,N=0;
  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    for (int i=0; i<N; i++) {
      scanf("%d %d",&nodes[i].x,&nodes[i].y);
      memset(cache[i], 0, sizeof(cache[i]));
    }
    for (int i=0; i<N-1; i++) {
      for (int j=i+1; j<N; j++) {
	double distance = sqrt((nodes[i].x-nodes[j].x)*(nodes[i].x-nodes[j].x)+(nodes[i].y-nodes[j].y)*(nodes[i].y-nodes[j].y));
	edges[i][j]=distance;
	edges[j][i]=distance;
      }
    }
    int state = 1<<(N-1);
    printf("%.2lf\n",dynamicPlanning(state, N-1, N-1));
    //printf("time passed:%.2lf s\n",(double)clock()/CLOCKS_PER_SEC);
  }
  return 0;
}

double dynamicPlanning(int state,int pos,int cnt){
  //printf("time passed:%.2lf s\n",(double)clock()/CLOCKS_PER_SEC);
  if (cache[pos][state]!=0) {
    return cache[pos][state];
  }
  if (cnt<=1)
    return edges[pos][0];
  else{
    int tmp=state>>1;
    int trace=1;
    double min=99999999;
    int i=0;
    while (i<cnt-1) {
      if (!(tmp & 0x1)) {
	double cal=dynamicPlanning(state+(1<<trace), trace,cnt-1)+edges[pos][trace];
	if (cal<min) {
	  min=cal;
	}
	i++;
      }
      tmp=tmp>>1;
      trace++;
    }
    cache[pos][state]=min;
    return min;
  }
}                                 
