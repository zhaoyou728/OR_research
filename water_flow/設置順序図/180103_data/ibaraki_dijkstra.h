#ifndef _IBARAKI_DIJKSTRA_H_
#define _IBARAKI_DIJKSTRA_H_

#define N 34000         /* �ߓ_���̏�� */
#define M 125000         /* �}���̏�� */ 
//#define N 20000         /* �ߓ_���̏�� */
//#define M 50000         /* �}���̏�� */ 
//#define N 1000         /* �ߓ_���̏�� */
//#define M 5000         /* �}���̏�� */ 
#define ZERO 0.0001   /* �ۂߌ덷�̋��e�l */
struct edge           /* �\����edge�̒�` */
{
    float d;
    int end1, end2;
};
struct value          /* �\����value�̒�` */
{
    float d;
    int node;
};
struct cell           /* �\����cell�̒�` */
{
    int adj;
    int edge;
    struct cell *next;
};

/* �֐��̐錾 */
void dijkstra(struct edge *E, struct edge *T, float *d, int n, int m);
struct value deletemin(struct value *A, int *loc, int n);
void downmin(int i, struct value *A, int *loc, int n);
void insert(struct value dj, struct value *A, int *loc, int n); 
void upmin(int i, struct value *A, int *loc, int n);
void swap(int i, int j, struct value *A, int *loc);

#endif //_IBARAKI_DIJKSTRA_H_

///// End of file /////
