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


set<int> S;
set<pi> R;
int n,k;
map<int,int> F;

vi form(){
	vi Q;
	auto ptr = S.begin();
	loop(i,k){
		Q.push_back(*ptr);
		ptr++;
	}
	return Q;
}

int ctr;
int ans = 0;

pi ask(vi Q){
	sort(all(Q));
	static map<vi,pi> mem;
	if(mem.count(Q)) return mem[Q];
	ctr--;
	cout << "?";
	for(int q : Q) cout << " " << q;
	cout << endl;
	fflush(stdout);
	int pos,val;
	cin >> pos >> val;
	F[pos] = val;
	
	int m = 0;
	int t = 0;
	for(auto p : Q){
		if(F.count(p))
			m += F[p] <= val,t += F[p] > val;
	}
	ans = max(ans,m);
	ans = max(ans,k - t);

	return mem[Q] = pi(val, pos);
}

int main(){
	cin >> n >> k;
	loop(i,n) S.insert(i+1);
	ctr = n;
	for(;ctr && sz(R) < k && sz(S) >= k;){
		vi Q = form();
		pi res = ask(Q);
		R.insert(res);
		S.erase(res.second);
	}
	for(;ctr && sz(R) < k;){
		set<int> Q;
		for(auto p : R) Q.insert(p.second);
		
		auto ptr = S.begin();
		assert(sz(S) + sz(Q) >= k);
		while(sz(Q) < k){
			Q.insert(*ptr);
			ptr++;
		}
		pi res = ask(vi{all(Q)});
		R.insert(res);
		if(S.count(res.second))
			S.erase(res.second);		
		else{
			S.erase(S.begin());
		}
	}
/*	if(sz(R) == k){
		vi Q;
		for(auto p : R) Q.push_back(p.second);
		pi res = ask(Q);
		int pos = res.second;
		int m = upper_bound(all(Q), pos) - Q.begin();
		cout << "! " << m << endl;				
	}
	else {
*/		cout << "! " << ans << endl;
//	}
	return 0;
}
