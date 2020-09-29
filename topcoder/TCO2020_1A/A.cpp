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

class AveragePrice{
public:
	double nonDuplicatedAverage(vector <int> prices){
		sort(prices.begin(), prices.end());
		prices.resize(unique(prices.begin(), prices.end()) - prices.begin());
		int n = prices.size();
		double ans = 0;
		for(int x : prices) ans += x;
		return ans/n;
	}
};


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	
	return 0;
}
