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


string ham, alphabet = "BSC";
int have[3], price[3], need[3];
ll money;

bool can(ll k){
	ll haveToPay = 0;
	loop(i, 3){
		haveToPay += max(need[i] * k - have[i], 0LL) * price[i];
	}
	
	return haveToPay <= money;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> ham;
	loop(i, 3) cin >> have[i];
	loop(i, 3) cin >> price[i];
	cin >> money;
	
	for(char c : ham) need[find(all(alphabet), c) - alphabet.begin()]++;
	
	ll s = 0, e = 1e14;
	while(s < e){
		ll m = s + (e-s+1)/2;
		if(can(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
	
	return 0;
}
