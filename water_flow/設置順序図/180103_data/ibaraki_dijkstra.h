#ifndef _IBARAKI_DIJKSTRA_H_
#define _IBARAKI_DIJKSTRA_H_

#define N 34000         /* 節点数の上限 */
#define M 125000         /* 枝数の上限 */ 
//#define N 20000         /* 節点数の上限 */
//#define M 50000         /* 枝数の上限 */ 
//#define N 1000         /* 節点数の上限 */
//#define M 5000         /* 枝数の上限 */ 
#define ZERO 0.0001   /* 丸め誤差の許容値 */
struct edge           /* 構造体edgeの定義 */
{
    float d;
    int end1, end2;
};
struct value          /* 構造体valueの定義 */
{
    float d;
    int node;
};
struct cell           /* 構造体cellの定義 */
{
    int adj;
    int edge;
    struct cell *next;
};

/* 関数の宣言 */
void dijkstra(struct edge *E, struct edge *T, float *d, int n, int m);
struct value deletemin(struct value *A, int *loc, int n);
void downmin(int i, struct value *A, int *loc, int n);
void insert(struct value dj, struct value *A, int *loc, int n); 
void upmin(int i, struct value *A, int *loc, int n);
void swap(int i, int j, struct value *A, int *loc);

#endif //_IBARAKI_DIJKSTRA_H_

///// End of file /////
