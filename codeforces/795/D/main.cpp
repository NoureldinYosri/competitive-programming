#include <stdio.h>
#include <stdlib.h>

const int MAX = 100*1000 + 10;
int A[MAX],B[MAX],n,l,r;

int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d %d",&n,&l,&r); l--;
	int i;
	for(i = 0;i < n;i++) scanf("%d",A + i);
	for(i = 0;i < n;i++) scanf("%d",B + i);
	qsort(A + l,r - l,sizeof(int),cmp);
	qsort(B + l,r - l,sizeof(int),cmp);

	int eq = 1;
	for(i = 0;i < n && eq;i++) eq = A[i] == B[i];
	puts(eq ? "TRUTH" : "LIE");
	return 0;
}
