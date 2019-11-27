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

int n;
int A[1 << 20];

vi B,C;

ll  match(){
	C.clear();
	set<pi> S;
	loop(i,sz(B)) S.emplace(B[i],i);
	int ret = INT_MAX;
	loop(i,sz(B)){
		pi p(B[i],i);
		if(!S.count(p)) continue;
		S.erase(p);
		if(S.empty()){
			ret = min(ret,p.first);
			break;
		}
		C.push_back(B[i]);
		ret = min(ret,S.rbegin()->first);
		S.erase(*S.rbegin());
	}
	B.swap(C);
	int j = min_element(B.begin()+1,B.end()) - B.begin();
	if(j < sz(B) && B[j] < ret){
		swap(ret,B[j]);
	}
	return ret;
}

ll solve(int m){
	if(B.empty()) return 0;
	//cout << m << " " << sz(B) << endl;
	//print(B,int);
	if(m == 1){
		ll v = match();
		return v + solve(1);
	}
	else {
		if(m&1) {
			B.push_back(0);
			m--;
		}
		match();
		return solve(m/2);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	int p = find(A,A + n,-1) - A;
	B = vi{A+p+1,A+n};
	reverse(all(B));
	cout << solve(p+1) << endl;
	return 0;
}
