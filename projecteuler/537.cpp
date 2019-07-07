//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#include "my_math.h"
//#include "fft.h"
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
//const int mod = 1004535809;
//const int MAX = 1000000,target = 20*1000;
//int prime[MAX + 1];
//int freq[target + 1];
//
//
//
//vi add(vi A,vi B) {
//	int a = sz(A),b = sz(B);
//	int c = max(a,b);
//	A.resize(c,0);
//	B.resize(c,0);
//	vi C(c,0);
//	loop(i,c) C[i] = add(A[i],B[i],mod);
//	return C;
//}
//vi mul(vi A,vi B) {
//	int a = sz(A),b = sz(B);
//	int c = min(a+b,target + 1);
//	vi C(c,0);
//	for(int i = 0;i < a;i++)
//		for(int j = 0;j < b && i+j < c;j++)
//			C[i + j] = add(C[i+j],mul(A[i],B[j],mod),mod);
//	return C;
//}
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	cerr << "sieving" << endl;
//	sieve(MAX,prime);
//	for(int p = 1,ctr = 0;p <= MAX;p++) {
//		ctr += prime[p] == p;
//		if(ctr <= target) freq[ctr]++;
//		else break;
//	}
//	vi f{freq,freq + target + 1};
//	int n = 20000,k = 20000;
//	vi A(1,1);
//	for(;n > 1;n >>= 1) {
//		if(n & 1) A = mul(A,f);
//		f = mul(f,f);
//	}
//	f = mul(A,f);
//	cout << f[k] << endl;
//
//	return 0;
//}
