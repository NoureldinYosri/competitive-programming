/*#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
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
const double PI = acos(-1);
using namespace std;

int n,b,W;
int L[3],aux[3];
int len[10],weight[10],p[10];

int solve(){
	int ret = 0;
	for(int msk = 0;msk < (1 << (2*b));msk++){
		int tmp = 0,tot = 0;
		memset(aux,0,sizeof aux);
		for(int i = 0;i < b;i++){
			int j = 2*i,k = j + 1;
			j = (msk & (1 << j)) != 0;
			k = (msk & (1 << k)) != 0;
			int which = (j << 1) | k;
			if(which == 3) continue;
			aux[which] += len[i];
			tot += weight[i];
			tmp += p[i];
		}
		if(tot > W) continue;
		bool valid = 1;
		loop(i,3) valid &= aux[i] <= L[i];
		if(!valid) continue;
		ret = max(ret,tmp);
	}
	return ret;
}

int main(){
	freopen("airport.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&b,&W);
		memset(L,0,sizeof L);
		loop(i,n) scanf("%d",L + i);
		loop(i,b) scanf("%d %d %d",len + i,weight + i,p + i);
		printf("%d\n",solve());
	}
	return 0;
}
*/
