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

const int MAX = 4 << 10,MAXT = 24*3600;
int n,K;
int T[MAX],D[MAX];

int dpEnd[5][MAXT];
int dpStart[5][MAXT];


int getEarliestStart(int,int);

int getEarliestEnd(int i,int k) {
	if(i < 0) return 0;
	if(i == 0) return k ? 0 : (T[0] + D[0]);
	int & ret = dpEnd[i%5][k];
	if(ret != -1) return ret;
	ret = getEarliestStart(i,k) + D[i];
	if(k) ret = min(ret,getEarliestEnd(i-1,k-1));
	return ret;
}
int getEarliestStart(int i,int k) {
	if(i == 0) return T[i];
	int & ret = dpStart[i%5][k];
	if(ret != -1) return ret;
	ret = getEarliestEnd(i-1,k);
	ret = max(ret,T[i]);
	return ret;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&K);
	if(n <= K) {
		printf("%d\n",MAXT);
		return 0;
	}
	loop(i,n){
		int t,d; scanf("%d %d",&t,&d);
		t--;
		T[i] = t;
		D[i] = d;
	}
//	prArr(T,n,int);
//	prArr(D,n,int);
	int ans = 0;
	for(int k = 0;k < n && k <= K;k++) ans = max(ans,T[k]);

	memset(dpStart,-1,sizeof dpStart);
	memset(dpEnd,-1,sizeof dpEnd);
	vp stopping;
	for(int i = 0;i < n;i++) {
		for(int r = 0;r < 1;r++) {
			int j = (i + r)%5;
			fill(dpStart[j],dpStart[j] + MAXT,-1);
			fill(dpEnd[j],dpEnd[j] + MAXT,-1);
		}
		stopping.clear();
		for(int k = 0;k <= K;k++) {
			int t = getEarliestStart(i,k) + D[i];
//			cerr << t << " ";
			if(stopping.empty() || stopping.back().first > t)
				stopping.push_back(mp(t,k));
		}
//		cerr << endl;
		for(auto p : stopping) {
			int t = p.first,k = p.second;
			if(n-i-1+k <= K) {
				ans = max(ans,MAXT - t);
				continue;
			}
			int j = K + i + 1 - k;
			if(j >= n) continue;
			int s = max(t,T[j]);
			ans = max(ans,s - t);
		}
	}
	cout << ans << endl;

	return 0;
}
