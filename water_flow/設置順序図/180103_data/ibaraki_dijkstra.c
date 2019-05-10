#define _CRT_SECURE_NO_WARNINGS
/* 最短路問題に対するダイクストラ法のプログラム例 */

#include <stdio.h>
#include <stdlib.h>

#include "ibaraki_dijkstra.h"

void dijkstra(struct edge *E, struct edge *T, float *dstar, int n, int m)
/*  節点数n, 枝数m, 枝集合Eをもつグラフの始点s=0からの最短路木を求める
    ダイクストラのアルゴリズム; 結果をT（最短路木）とdstar（最短路長）
    に入れる */
{
    int i, j, k, u, v1, v2, vadj, nh;
    int P[N];            /* uがPの要素ならP[u]==1、さもなければ0 */
    int loc[N];          /* 節点uはヒープのloc[u]番目のセルに格納 */
    int edge[N];         /* edge[v]は最短路木におけるvへの枝の候補 */
    float du;
    struct cell *adjlist[N];      /* グラフの隣接リスト */
    struct cell *r, *q, *p;  
    struct value vh, vmin; 
    struct value heap[N-1];       /* (dstar[u], u)のヒープ */

    P[0]=1;                       /* Pの初期化 */
    for(j=1; j<n; j++) P[j]=0;
    for(j=0; j<n; j++) {adjlist[j]=NULL; loc[j]=-1;}  /* 隣接リストの構成 */
    for(i=0; i<m; i++)
    {
	v1=E[i].end1;
	v2=E[i].end2;    
	r=(struct cell *)malloc(sizeof(struct cell));
	r->adj=v2; r->edge=i; r->next=adjlist[v1]; adjlist[v1]=r;
	q=(struct cell *)malloc(sizeof(struct cell));
	q->adj=v1; q->edge=i; q->next=adjlist[v2]; adjlist[v2]=q;
    }
    nh=0;
    u=0;                          /* 節点0から開始 */
    du=0.0; dstar[u]=0.0;
    for(k=0; k<n-1; k++)          /* ダイクストラ法の反復 */
    {
	p=adjlist[u];  /* uに接続する枝によるヒープの更新（ステップ1(i)) */
	while(p!=NULL)
	{
	    vadj=p->adj;            /* vadjはuに隣接する節点 */
	    if(P[vadj]==0) 
	    {
		if(loc[vadj] == -1)  /* vadjをヒープに入れる */
		{
		    vh.d=du+E[p->edge].d; vh.node=vadj;
		    edge[vadj]=p->edge;
		    insert(vh, heap, loc, nh);
		    nh=nh+1;
		}
		else                 /* すでにヒープにあるvadjの更新 */
		{
		    j=loc[vadj];
		    if(heap[j].d > du+E[p->edge].d+ZERO) 
		    {
			heap[j].d=du+E[p->edge].d;
			edge[vadj]=p->edge;
			upmin(j, heap, loc, nh);
		    }
		}
	    }
	    p=p->next;
	}
	vmin=deletemin(heap, loc, nh); /* ステップ1(ii): vminの選択 */
	nh=nh-1;                   /* u=vmin.nodeをPへ移動 */
	u=vmin.node;
	du=vmin.d;
	P[u]=1; dstar[u]=du;
	T[k]=E[edge[u]];           /* edge[u]を最短路木へ入れる */
    }
    return;
}

void insert(struct value vh, struct value *A, int *loc, int n)
/* ヒープA[0],...,A[n-1]へ新しい要素xの挿入; n=n+1 */
{
    A[n].d=vh.d;
    A[n].node=vh.node;
    loc[A[n].node]=n;
    upmin(n, A, loc, n+1);
}

struct value deletemin(struct value *A, int *loc, int n)
/* ヒープA[0],...,A[n-1]から最小要素A[0]の出力と除去; n=n-1 */
{
    struct value min;

    min.d=A[0].d; A[0].d=A[n-1].d;
    min.node=A[0].node; A[0].node=A[n-1].node;
    loc[A[0].node]=0;
    if(n>1) downmin(0, A, loc, n-1);
    return(min);
}

void upmin(int i, struct value *A, int *loc, int n)
/* A[i]から上方へ、ヒープ条件回復のためswap操作を適用 */
{
    int j;
    if(i<0 || i>=n)
    { 
	printf("Illegal element i = %d for n = %d\n", i, n); 
	exit(1);
    }
    if(i==0) return;
    j=(i+1)/2-1; 
    if(A[j].d>A[i].d)
    {
	swap(i, j, A, loc); 
	upmin(j, A, loc, n);
    }
    return;
}


void downmin(int i, struct value *A, int *loc, int n)
/* A[i]から下方へ、ヒープ条件回復のためのswap操作を適用 */
{
    int j;

    if(i<0 || i>=n) 
    { 
	printf("Illegal element i = %d for n = %d\n", i, n); 
	exit(1);
    }
    j=2*i+1;
    if(j>=n) return;
    if(j+1<n && A[j].d > A[j+1].d+ZERO) j=j+1; 
    if(A[j].d < A[i].d-ZERO) 
    {
	swap(i, j, A, loc);
	downmin(j, A, loc, n);
    }
    return;
}


void swap(int i, int j, struct value *A, int *loc)
/* ヒープAにおける構造体A[i]とA[j]の交換 */
{
    struct value temp;

    temp=A[i]; A[i]=A[j]; A[j]=temp;
    loc[A[i].node]=i; loc[A[j].node]=j;           /* locの更新 */
    return;
}

int main(int argc, char** argv)
/* 最短路問題のアルゴリズムのテストプログラム */
{
    struct edge E[M], T[N-1];     /* 枝集合E, 最短路木T */
    float dstar[N];               /* 節点への最短路長 */
    int i, k, n, m;
    FILE *file;
    int target;
    int start = atoi(argv[1]);

    //file=fopen("spathdata", "r");              /* データの読込み */
    file=fopen("GraphData.txt", "r");              /* データの読込み */
    {
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &m);
    }
    for(i=0; i<m; i++)
    {
	fscanf(file, "%f", &E[i].d);
	fscanf(file, "%d", &E[i].end1);
	fscanf(file, "%d", &E[i].end2);
    }
    fclose(file);
//    printf("n = %d, m = %d\n", n, m);
//    printf("edges; d  end1  end2 \n");
//    for(i=0; i<m; i++) 
//	printf("%f, %d, %d\n", E[i].d, E[i].end1, E[i].end2);
    dijkstra(E, T, dstar, n, m);              /* 最短路の計算 */
//    printf("Shortest path tree edges\n");
//    for(k=0; k<n-1; k++) 
//	printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
//    printf("Shortest path length\n");
//    for(k=0; k<n; k++) 
//	printf("node %d: %f\n", k, dstar[k]);

    file=fopen("Target.txt", "r");
    while( (fscanf(file, "%d", &target)) != EOF ){
	if(start != target){
	    printf("[%d, %d] %f\n", start, target, dstar[target]);
	}
    }
    fclose(file);

    return(0);
}

///// End of file /////
