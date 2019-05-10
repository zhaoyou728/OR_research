#define _CRT_SECURE_NO_WARNINGS
/* �ŒZ�H���ɑ΂���_�C�N�X�g���@�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>

#include "ibaraki_dijkstra.h"

void dijkstra(struct edge *E, struct edge *T, float *dstar, int n, int m)
/*  �ߓ_��n, �}��m, �}�W��E�����O���t�̎n�_s=0����̍ŒZ�H�؂����߂�
    �_�C�N�X�g���̃A���S���Y��; ���ʂ�T�i�ŒZ�H�؁j��dstar�i�ŒZ�H���j
    �ɓ���� */
{
    int i, j, k, u, v1, v2, vadj, nh;
    int P[N];            /* u��P�̗v�f�Ȃ�P[u]==1�A�����Ȃ����0 */
    int loc[N];          /* �ߓ_u�̓q�[�v��loc[u]�Ԗڂ̃Z���Ɋi�[ */
    int edge[N];         /* edge[v]�͍ŒZ�H�؂ɂ�����v�ւ̎}�̌�� */
    float du;
    struct cell *adjlist[N];      /* �O���t�̗אڃ��X�g */
    struct cell *r, *q, *p;  
    struct value vh, vmin; 
    struct value heap[N-1];       /* (dstar[u], u)�̃q�[�v */

    P[0]=1;                       /* P�̏����� */
    for(j=1; j<n; j++) P[j]=0;
    for(j=0; j<n; j++) {adjlist[j]=NULL; loc[j]=-1;}  /* �אڃ��X�g�̍\�� */
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
    u=0;                          /* �ߓ_0����J�n */
    du=0.0; dstar[u]=0.0;
    for(k=0; k<n-1; k++)          /* �_�C�N�X�g���@�̔��� */
    {
	p=adjlist[u];  /* u�ɐڑ�����}�ɂ��q�[�v�̍X�V�i�X�e�b�v1(i)) */
	while(p!=NULL)
	{
	    vadj=p->adj;            /* vadj��u�ɗאڂ���ߓ_ */
	    if(P[vadj]==0) 
	    {
		if(loc[vadj] == -1)  /* vadj���q�[�v�ɓ���� */
		{
		    vh.d=du+E[p->edge].d; vh.node=vadj;
		    edge[vadj]=p->edge;
		    insert(vh, heap, loc, nh);
		    nh=nh+1;
		}
		else                 /* ���łɃq�[�v�ɂ���vadj�̍X�V */
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
	vmin=deletemin(heap, loc, nh); /* �X�e�b�v1(ii): vmin�̑I�� */
	nh=nh-1;                   /* u=vmin.node��P�ֈړ� */
	u=vmin.node;
	du=vmin.d;
	P[u]=1; dstar[u]=du;
	T[k]=E[edge[u]];           /* edge[u]���ŒZ�H�؂֓���� */
    }
    return;
}

void insert(struct value vh, struct value *A, int *loc, int n)
/* �q�[�vA[0],...,A[n-1]�֐V�����v�fx�̑}��; n=n+1 */
{
    A[n].d=vh.d;
    A[n].node=vh.node;
    loc[A[n].node]=n;
    upmin(n, A, loc, n+1);
}

struct value deletemin(struct value *A, int *loc, int n)
/* �q�[�vA[0],...,A[n-1]����ŏ��v�fA[0]�̏o�͂Ə���; n=n-1 */
{
    struct value min;

    min.d=A[0].d; A[0].d=A[n-1].d;
    min.node=A[0].node; A[0].node=A[n-1].node;
    loc[A[0].node]=0;
    if(n>1) downmin(0, A, loc, n-1);
    return(min);
}

void upmin(int i, struct value *A, int *loc, int n)
/* A[i]�������ցA�q�[�v�����񕜂̂���swap�����K�p */
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
/* A[i]���牺���ցA�q�[�v�����񕜂̂��߂�swap�����K�p */
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
/* �q�[�vA�ɂ�����\����A[i]��A[j]�̌��� */
{
    struct value temp;

    temp=A[i]; A[i]=A[j]; A[j]=temp;
    loc[A[i].node]=i; loc[A[j].node]=j;           /* loc�̍X�V */
    return;
}

int main(int argc, char** argv)
/* �ŒZ�H���̃A���S���Y���̃e�X�g�v���O���� */
{
    struct edge E[M], T[N-1];     /* �}�W��E, �ŒZ�H��T */
    float dstar[N];               /* �ߓ_�ւ̍ŒZ�H�� */
    int i, k, n, m;
    FILE *file;
    int target;
    int start = atoi(argv[1]);

    //file=fopen("spathdata", "r");              /* �f�[�^�̓Ǎ��� */
    file=fopen("GraphData.txt", "r");              /* �f�[�^�̓Ǎ��� */
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
    dijkstra(E, T, dstar, n, m);              /* �ŒZ�H�̌v�Z */
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
