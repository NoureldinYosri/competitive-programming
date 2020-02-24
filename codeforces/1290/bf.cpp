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


string s;

void gen(){
	set<char> S;
	do{
		s.clear();
		int n = rand()%7 + 1;
		loop(i, n) s.pb((char)(rand()%4 + 'a'));
		S = set<char>(all(s));
	}while(sz(S) == 1);
}

vector<string> out;

bool valid(vi & V){
	string T;
	for( int i : V) T.pb(s[i]);
	if(s == T) return 0;
	int j = 0;
	out.clear();
	string t;
	int ctr[26] = {0};
	
	for(int i : V){
		ctr[s[j++] - 'a'] ++;
		char c = s[i];
		ctr[c - 'a']--;
		t.pb(c);
		bool done = 1;
		loop(k, 26) done &= ctr[k] ==0;
		if(done) {
			out.emplace_back(t);
			t.clear();
		}
	}
	if(!t.empty()) out.pb(t);
	return sz(out) == 1;
}

bool get(){
	vi V;
	loop(i, sz(s)) V.pb(i);
	do{
		if(valid(V)) {
//			cerr << "for " << s << " found " << endl;
//			print(out, string);
			return 0;
		}
	}while(next_permutation(all(V)));	
//	cout << "none found for " << s << endl;
//	exit(0);
	return 1;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	srand(time(0));
	int T = 0;
	while(){
		gen();
		if(get()){
			cout << ++T << ". " << s << endl;
			assert((set<char>(all(s))).size() <= 2);
			if((set<char>(all(s))).size() == 2){
				map<char, int> f;
				for(char c : s) f[c]++;
				
			//	cout << sz(s) << " " << f.begin()->second << " " << f.rbegin()->second << endl;
			}
		}
		else if((set<char>(all(s))).size() == 2){
			map<char, int> f;
			for(char c : s) f[c]++;
			int a = f.begin()->second, b = f.rbegin()->second;
			if(a > b) swap(a, b);
			cout << "fail " << s << " " << sz(s) << " " << a << " " << b << endl;
			assert(b-a <= (a+b+1)/2);
		}
	}
	return 0;
}
