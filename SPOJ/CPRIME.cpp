#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

const int MAX = 100000000;
int A[MAX],P[MAX],e = 0;;

void sieve(){
	for(int i = 2;i < MAX;i++){
		if(!A[i]) A[i] = i,P[e++] = i;
		for(int j = 0;j < e && P[j] <= A[i] && i*P[j] < MAX;j++)
			A[i*P[j]] = P[j];
	}
}
int main(){
	sieve();
	int N;
	while (scanf("%d",&N) == 1 && N){
		int p = upper_bound(P,P + e,N) - P;
		double d = N/log(N);
		d = abs(p - d)/p * 100.0;
		printf("%.1f\n",d);
	}
	return 0;
}
