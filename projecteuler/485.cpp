//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//#include "my_math.h"
//
//const int MAXN = 100*1000*1000,MAXK = 100*1000;
//int prime[MAXN+3],sig0[MAXN+3];
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	sieve(MAXN,prime);
//	sig0[1] = 1;
//	for(int i = 2;i <= MAXN;i++) {
//		int p = prime[i],e = 1,m = i;
//		while(m%p == 0) {
//			e++;
//			m /= p;
//		}
//		sig0[i] = sig0[m]*e;
//	}
//	int k = MAXK;
//	deque<int> dq;
//	for(int i = 1;i <= k;i++) {
//		while(!dq.empty() && sig0[dq.back()] <= sig0[i]) dq.pop_back();
//		dq.push_back(i);
//	}
//	ll ans = 0;
//	for(int i = 1;i <= MAXN-k+1;i++) {
//		ans += sig0[dq.front()];
//		if(dq.front() == i) dq.pop_front();
//		int j = i+k;
//		while(!dq.empty() && sig0[dq.back()] < sig0[j]) dq.pop_back();
//		dq.push_back(j);
//	}
//	cout << ans << endl;
//	return 0;
//}
