#include <bits/stdc++.h>
using namespace std;

int n;
int D[10][10];

int read(int i,int j){
	scanf("%d",&D[i][j]);
	return (j == n - 1) ? ((i == n - 1) ? 0 : read(i + 1,0)) : read(i,j + 1);
}

int f(int k,int i,int j){
	D[i][j] = min(D[i][j],D[i][k] + D[k][j]);
	return (j == n - 1) ? ((i == n - 1) ? ((k == n - 1) ? 0 : f(k + 1,0,0)) : f(k,i + 1,0)) : f(k,i,j + 1);
}

int get(int i,int j){
	return (j == n - 1) ? max(D[i][j],(i == n - 1) ? 0 : get(i + 1,0)) : max(D[i][j],get(i,j + 1));
}

int main(){
	scanf("%d",&n);
	read(0,0);
	f(0,0,0);
	printf("%d\n",get(0,0));
	return 0;
}