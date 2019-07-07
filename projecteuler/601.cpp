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
//const int MAXN = 100000;
//int streak(int n) {
//	int k = 0;
//	for(k = 0;(n+k)%(k+1) == 0;k++);
//	return k;
//}
//
//int order(int N) {
//	int mx = 0;
//	for(int n = 2;n <= N;n++){
//		int s = streak(n);
//		mx = max(mx,s);
//	}
//	return mx;
//}
//
//int P(int s,int n){
//	int ret = 0;
//	for(int i = 2;i <= n;i++)
//		ret += streak(i) == s;
//	return ret;
//}
//
//int Q(int i) {
//	return P(i,1 << (2*i));
//}
//
//vi V[32];
//vector<ll> p4;
//
//int main(int argc,char **argv){
//	for(ll p = 1,e = 0;e <= 31;e++,p *= 4)
//		p4.pb(p);
//
//	for(int i = 2;i <= p4[5];i++){
//		int s = streak(i);
//		if(s >= 32) continue;
//		V[s].pb(i);
//	}
//	for(int s = 1;s < 32;s++){
//		cerr << s << ":";
//		for(int x : V[s])
//			cerr << " " << x;
//		cerr << endl;
//	}
//	return 0;
//}
