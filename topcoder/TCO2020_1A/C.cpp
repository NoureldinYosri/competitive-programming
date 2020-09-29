#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int K = 500;
struct BlindBoxSets{
	vector<vector<long double>> C;
	vector<vector<long double>> f;
	
public:
	void init(int N, int m){
		int T = N*m + K;
		C = vector<vector<long double>> (T+1, vector<long double>(T+1, 0.0));
		for(int n = 0; n <= T; n++){
			C[n][0] = C[n][n] = 1;
			for(int k = 1; k < n; k++)
				C[n][k] = C[n-1][k] + C[n-1][k-1];
		}
		f = vector<vector<long double>> (T + 1, vector<long double>(N+1, 0.0));
		for(int t = 0; t <= T; t++){
			for(int n = 0; n <= N; n++){
				if(t < n*m) f[t][n] = 0;
				else if(n == 0) f[t][n] = t == 0;
				else {
					for(int k = m; k <= t; k++)
						f[t][n] += f[t-k][n-1] * C[t][k];
				}
			}
		}
	}
	long double expectedPurchases(int numSets, int numItems){
		init(numItems, numSets);
		long double ans = 0;
		int m = numSets;
		long double p0 = pow(1.0/numItems, numItems * numSets);
		for(int t = numItems*numSets, k = 0; k < K; k++, t ++){
			long double p = numItems * f[t - m][numItems-1] * p0 * C[t-1][m-1];
			//if(p < 1e-18) break;
		//	cerr << t << " " << p << " " << f[t-m][numItems-1] << " " << C[t-1][m-1] << endl;
			ans += t*p;
			p0 /= numItems;
		}
		return ans;
	}
};

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int m = 1; m <= 4; m++, cerr << endl)
		for(int n = 1; n <= 20; n++)
			cerr << BlindBoxSets().expectedPurchases(m, n) << " ";
	cerr << BlindBoxSets().expectedPurchases(4, 50) << endl;
	return 0;
}
