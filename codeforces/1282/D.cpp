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

int N = 300;

int ask(string s){
	cout << s << endl;
	fflush(stdout);
	int r; cin >> r;
	if(r <= 0) exit(0);
	return r;
}


int main(){
	int ca = N - ask(string(N,'a')); 
	int cb = N - ask(string(N,'b')); 
	int n = ca + cb;
	
	if(!ca) ask(string(n,'b'));
	else if(!cb) ask(string(n,'a'));
	
	string S(n,'b');
	int f = ca;
	for(int i = 0;i < n;i++){
		S[i] = 'a';
		int g = ask(S);
		if(g < f){
			f = g;
		}
		else S[i] = 'b';
	}
	ask(S);
	return 0;
}
