#pragma GCC optimize ("O3")
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

const int MAX = 200000 + 10;
int A[MAX],n,m;
int freq[MAX];
int cnt[MAX];

int erase(int p) {
	int v = A[p];
	p = v - freq[v] + 1;
	freq[v] --;
	if(p <= 0) return 0;
	cnt[p]--;
	return cnt[p] == 0;
}

int insert(int p,int v) {
	freq[v]++;
	A[p] = v;
	p = v - freq[v] + 1;
	if(p <= 0) return 0;
	cnt[p] ++;
	return cnt[p] == 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(i,1,n) {
		scanf("%d",A + i);
		freq[A[i]]++;
	}
	range(i,1,n) if(freq[i]){
		cnt[max(1,i - freq[i] + 1)]++;
		cnt[i+1]--;
	}
	int pref = 0;
	range(i,1,n) cnt[i] = pref += cnt[i];

	int ans = 0;
	range(i,1,n) ans += cnt[i] == 0;
//	cerr << "intial answer = " << ans << endl;
	while(m--) {
		int p,v; scanf("%d %d",&p,&v);
		ans += erase(p);
		ans -= insert(p,v);
		printf("%d\n",ans);
/*

 		cerr << erase(p) << endl;
		cerr << insert(p,v) << endl;
		cerr << "===========================" << endl;
*/
	}
	return 0;
}
