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
//bool isPan(ll x,int b) {
//	static vector<bool> vis;
//	vis.resize(b);
//	fill(all(vis),0);
//	while (x > 0) {
//		vis[x%b] = 1;
//		x /= b;
//	}
//	for (bool v : vis) if (!v) return 0;
//	return 1;
//}
//
//bool isSuper(ll x,int n) {
//	for (int b = n;b >= 2;b--)
//		if (!isPan(x,b))
//			return 0;
//	return 1;
//}
//
//void bf(int n) {
//	vi D;
//	loop(i,n) D.push_back(i);
//	swap(D[0],D[1]);
//	ll ans = 0;
//	int ctr = 0;
//	do{
//		ll x = 0;
//		for(int d : D)
//			x = x*n + d;
//		if(isSuper(x,n)) {
//			cout << x << endl;
//			ans += x;
//			ctr++;
//			if(ctr == 10) break;
//		}
//	}while(next_permutation(all(D)));
//	cout << "ans = " << ans << endl;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	bf(12);
//	return 0;
//}
