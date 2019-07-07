#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

char G[5 << 10];
int n;

bool solve(){
	if(n == 1) return 1;
	int b = 0;
	loop(i,n) b += G[i] == 'B';
	if(b >= n-1) return 0;
	if(2*b + 1 >= n) return 1;
	return b > 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("data.txt","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++){
		scanf("%s",G);
		n = strlen(G);
		printf("Case #%d: %c\n",t,"NY"[solve()]);
	}
	return 0;
}
