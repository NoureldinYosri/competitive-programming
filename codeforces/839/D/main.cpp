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
#define popcnt(x) __builtin_popcount(x)
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

const int mod = 1e9 + 7,MAX = 1 << 20;
int cnt[MAX],freq[MAX];
int p2[MAX],f[MAX];

int mul(int a,int b){
	return (a*1LL*b)%mod;
}
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	p2[0] = 1;
	loop(i,MAX + 1) p2[i + 1] = add(p2[i],p2[i]);
	int n,x; scanf("%d",&n);
	loop(i,n){
		scanf("%d",&x);
		freq[x]++;
	}
	int ans = 0;
	for(int i = MAX-1;i > 1;i--) {
		for(int j = i;j < MAX;j += i)
			cnt[i] += freq[j];
		if(!cnt[i]) continue;
		f[i] = mul(cnt[i],p2[cnt[i] - 1]);
		for(int j = i+i;j < MAX;j += i)
			f[i] = add(f[i],-f[j]);
		ans = add(ans,mul(f[i],i));
//		cerr << i << " " << cnt[i] << " " << f[i] << endl;
	}
	cout << ans << endl;
	return 0;
}
