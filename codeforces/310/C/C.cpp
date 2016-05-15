#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define MAX 110000
using namespace std;

typedef vector<int> vi;

vi chains[MAX];
int END[MAX],C[MAX];

void decompose(vi & V){
	int cost = 0;
	for(int i = 0;i < V.size();){
		int j = i + 1;
		while(j < V.size() && V[j] == V[j - 1] + 1) j++;
		C[V[i]] = cost;
		END[V[i]] = V[j - 1];		
		i = j;
		if(!cost) cost++;
	}
}

int main(){
	int n,k,m;
	scanf("%d %d",&n,&k);
	loop(i,k){
		scanf("%d",&m);
		chains[i] = vi(m);
		loop(j,m) scanf("%d",&chains[i][j]);
		decompose(chains[i]);
	} 
	int s = 1; long long ans = 0;
	while(s <= n){
		ans += C[s];
		if(END[s] < n) ans += 2*(END[END[s] + 1] - END[s] - 1) + 1;
		s = END[s] + 1;
	}
	cout << ans << endl;
	return 0;
}
