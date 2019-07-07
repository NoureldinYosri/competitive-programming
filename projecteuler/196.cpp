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
//vector<int64> getRow(int n) {
//	vector<int64> R(n);
//	int64 f = (n*(n - 1))/2 + 1;
//	loop(i,n) R[i] = f + i;
////	print(R,int64);
//	return R;
//}
//
//int S(int n) {
//	vector<vector<int64> > R;
//	vector<vector<bool> > isPrime;
//	vector<vector<bool> > isPart;
//	cout << "building" << endl;
//	for(int i = -2;i <= 2;i++) {
//		R.push_back(getRow(n+i));
//		isPrime.push_back(vector<bool>());
//		isPart.push_back(vector<bool>());
//		for(int64 x : R.back()) {
//			isPrime.back().push_back(isProbablePrime(x,5));
//			isPart.back().push_back(0);
//		}
//	}
//	cout << "done" << endl;
//	for(int r = 0;r < sz(R);r++)
//		for(int c = 0;c < sz(R[r]);c++) if(isPrime[r][c]){
//			int ctr = 0;
//			for(int dx = -1;dx <= 1;dx++)
//				for(int dy = -1;dy <= 1;dy++) {
//					int x = r + dx,y = c + dy;
//					if(x < 0 || y < 0 || x >= sz(R) || y >= sz(R[x]) || !isPrime[x][y]) continue;
//					ctr++;
//				}
//			for(int dx = -1;dx <= 1 && ctr >= 3;dx++)
//				for(int dy = -1;dy <= 1;dy++) {
//					int x = r + dx,y = c + dy;
//					if(x < 0 || y < 0 || x >= sz(R) || y >= sz(R[x]) || !isPrime[x][y]) continue;
//					isPart[x][y] = 1;
//				}
//		}
//	int64 ret = 0;
//	for(int i = 0;i < n;i++)
//		ret += R[2][i] * isPart[2][i];
//	return ret;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
////	cout << S(8) << endl;
////	cout << S(9) << endl;
////	cout << S(10000) << endl;
//	int64 a,b ;
//	cout << (a = S(5678027)) << endl;
//	cout << (b = S(7208785)) << endl;
//	cout << a + b << endl;
//	return 0;
//}
