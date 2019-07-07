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
//const int MAXN = 1000*1000-1;
//int prime[MAXN+1];
//
//vector<ll> PP;
//
//int main(int argc,char **argv){
//	sieve(MAXN,prime);
//	for(int p = 2;p <= MAXN;p++)
//		if(prime[p] == p)
//			PP.push_back(p*1LL*p);
//
//	int ctr = 0;
//	for(int m = 1;m <= 10000;m++)
//		for(int n = 1;n*m+1 <= 100*100;n++){
//			int tot = n*m+1;
//			if(binary_search(all(PP),tot))
//				ctr++;
//		}
//	cout << ctr << endl;
//	return 0;
//}
