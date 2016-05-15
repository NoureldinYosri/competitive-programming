#include "bits/stdc++.h"
using namespace std;
inline int scan(){
	int x = 0;
	char c = getchar_unlocked();
	while(c < '0' || c > '9'){
		c = getchar_unlocked();
	}
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar_unlocked();
	}
	return x;
}
const int N = 2.5e5 + 5;
const int M = 5e4 + 5;
const int SQN = 1005;
int n;
int arr[N];
int q;
int x , y;
int start[SQN];
int finish[SQN];
int block[N];
int bit[SQN][M] = {0};
void update(int i , int idx , int val){
	while(idx < M){
		bit[i][idx] += val;
		idx += idx & -idx;
	}
}
int sum(int i , int idx){
	int res = 0;
	while(idx){
		res += bit[i][idx];
		idx -= idx & -idx;
	}
	return res;
}
long long inv = 0;
int get(int l , int r , int x){
	int res = 0;
	for(int i = block[l] ; i <= block[r] ; ++i){
		if(start[i] >= l && finish[i] <= r){
			res += sum(i , x);
		}
		else{
			for(int j = max(start[i] , l) ; j <= min(finish[i] , r) ; ++j){
				res += (arr[j] <= x);
			}
		}
	}
	return res;
}
int main(){
	n = scan();
	for(int i = 1 ; i <= n ; ++i){
		//arr[i] = rand() % 50000;
		//++arr[i];
		arr[i] = scan();
	}
	int i = 1;
	int cur = 0;
	while(i <= n){
		int j = i;
		start[++cur] = i;
		while(j <= n && j < i + SQN){
			block[j] = cur;
			update(cur , arr[j] , 1);
			++j;
		}
		finish[cur] = j - 1;
		i = j;
	}
	for(int i = n ; i >= 1 ; --i){
		inv += sum(0 , arr[i] - 1);
		update(0 , arr[i] , 1);
	}
	q = scan();
	while(q--){
		//x = rand() % n;
		//++x;
		//y = rand() % 50000;
		//++y;
		x = scan() , y = scan();
		inv -= x - 1 - get(1 , x - 1 , arr[x]);
		inv -= get(x + 1 , n , arr[x] - 1);
		update(block[x] , y , 1);
		update(block[x] , arr[x] , -1);
		arr[x] = y;
		inv += x - 1 - get(1 , x - 1 , arr[x]);
		inv += get(x + 1 , n , arr[x] - 1);
		printf("%lld\n" , inv);
	}
}	

