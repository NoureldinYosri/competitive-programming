#ifdef ACTIVE
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

map<vi,double> dp[101];

double solve(int d,vi cnt) {
	int tot = 0;
	for(int i = 6;i < 12;i++)
		tot += cnt[i];
	if(tot == 0) return 1;
	if(d == 0) return 0;
	tot = 0;
	for(int x : cnt) tot += x;

	if(dp[d].count(cnt)) return dp[d][cnt];
	double ret = 0;

	for(int i = 0;i < 12;i++) if(cnt[i]){
		cnt[i]--;
		int j = -1;
		if(i != 0 && i != 6) j = i - 1;
		if(j != -1) cnt[j]++;

		ret += (cnt[i] + 1)*solve(d-1,cnt)/tot;

		cnt[i]++;
		if(j != -1) cnt[j]--;
	}
	dp[d][cnt] = ret;
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int n,m,d; cin >> n >> m >> d;
	vi cnt(12);
	loop(i,n) {
		int x; cin >> x;
		cnt[x-1]++;
	}
	loop(i,m) {
		int x; cin >> x; x--;
		cnt[x+6]++;
	}
	printf("%.12f\n",solve(d,cnt));
	return 0;
}
#endif
