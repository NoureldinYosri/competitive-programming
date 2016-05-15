#include <bits/stdc++.h>
using namespace std;




int A[100001],N,K;
int BIT[2][1000001];
void update(int p,int v,int *T){
	while(p <= N){
		T[p] += v;
		p += p & (-p);
	}
}

int get(int p,int *T){
	int ans = 0;
	while(p){
		ans += T[p];
		p -= p & (-p);
	}
	return ans;
}

void init(int & i1 ,int & i2,long long & ctr1,long long & ctr2){
	int i;
	for(i = 1;i <= K;){
		int j = i + 1; i1 = i;
		while(j <= K){
			if(A[j - 1] <= A[j]) {
				ctr1 += j - i;
				update(i,1,BIT[0]),update(j,-1,BIT[0]);
			}
			else break;
			j += 1;
		}
		i = j;
	} 
	for(i = 1;i <= K;){
		int j = i + 1; i2 = i;
		while(j <= K){
			if(A[j - 1] >= A[j]) {
				ctr2 += j - i;			
				update(i,1,BIT[1]),update(j,-1,BIT[1]);
			}
			else break;
			j += 1;
		}
		i = j;
	}
}

int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i <= N;i++) scanf("%d",A + i);
	long long ctr1 = 0,ctr2 = 0; int i1,i2;
	init(i1,i2,ctr1,ctr2);
	printf("%lld\n",ctr1 - ctr2);
	for(int i = K + 1;i <= N;i++){
		if(i - K == i1) i1++;
		if(i - K == i2) i2++;
		ctr1 -= get(i - K,BIT[0]);
		ctr2 -= get(i - K,BIT[1]);	
		if(A[i - 1] < A[i]){
			i2 = i;
			update(i1,1,BIT[0]);
			update(i,-1,BIT[0]);
			ctr1 += i - i1;		
		}
		else if(A[i - 1] > A[i]){
			i1 = i;
			update(i2,1,BIT[1]);
			update(i,-1,BIT[1]);
			ctr2 += i - i2;
		}
		else{
			update(i1,1,BIT[0]);
			update(i,-1,BIT[0]);
			ctr1 += i - i1;		
			update(i2,1,BIT[1]);
			update(i,-1,BIT[1]);
			ctr2 += i - i2;
		}
		printf("%lld\n",ctr1 - ctr2);
	}
}

