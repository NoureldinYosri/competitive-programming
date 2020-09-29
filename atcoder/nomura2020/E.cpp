#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

char txt[1 << 20];
int n;
int ctr[2];

ll greedy1(int ones){
	memset(ctr, 0, sizeof ctr);
	ll ans = 0;
	for(int i = n-1; i >= 0; i--){
		swap(ctr[0], ctr[1]);
		ctr[1] += txt[i] == '1';
		if(txt[i] == '0') ans += ctr[1] + (ones - ctr[0] - ctr[1] + 1)/2;
	}
	return ans;
}

ll greedy2(int ones){
	memset(ctr, 0, sizeof ctr);
	ll ans = 0;
	loop(i, n){
		ctr[(i+1)&1] += txt[i] == '1';
		if(txt[i] == '0') {
			int seen = ctr[0] + ctr[1];
			ans += ctr[1] + (ones - seen + i%2)/2;
		}
	}
	return ans;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> txt;
	n = strlen(txt);
	int ones = 0;
	ll ans = 0;
	loop(i, n) if(txt[i] == '1'){
		ones++;
		ans += (ones + 1) >> 1;
	}
	
	ans += max(greedy1(ones), greedy2(ones));
	
	cout << ans << endl;
	return 0;
}
