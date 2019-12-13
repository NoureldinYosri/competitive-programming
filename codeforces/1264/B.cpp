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


void answer(string s){
	char prv = 0;
	for(char c : s){
		if(prv && abs(c - prv) != 1) {
			puts("NO");
			exit(0);
		}
		prv = c;
	}
	puts("YES");
	for(char c : s){
		putchar(c);
		putchar(' ');
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int a,b,c,d; cin >> a >> b >> c >> d;


	string pref,suff;
	if(b < a-1){
		puts("NO");
		return 0;
	}
	if(c < d-1){
		puts("NO");
		return 0;
	}
	for(int i = 0;i < a;i++){
		pref.push_back('0');
		pref.push_back('1');
	}
	if(!pref.empty()) pref.pop_back();
	b -= max(0,a-1);
	a = 0;
	
	for(int i = 0;i < d;i++){
		suff.push_back('3');
		suff.push_back('2');
	}
	if(!suff.empty()) suff.pop_back();
	c -= max(d - 1,0);
	d = 0;

	//cout << pref << endl;
	//cout << suff << endl;
	//cout << b << " " << c << " " << pref.size() << " " << suff.size() << endl;
	// pref 00
	// suff 33
//	exit(0);
	string res;
	if(!pref.empty() && !suff.empty()){
		string mid ;
		int len = min(b,c);
		if(!len){
			puts("NO");
			return 0;
		}
		loop(i,len) {
			mid.push_back('1');
			mid.push_back('2');
		}
		b -= len;
		c -= len;
		if(b) pref = "1" + pref,b--;
		if(c) suff = suff + "2",c--;
		if(b || c){
			puts("NO");
			return 0;
		}
		answer(pref + mid + suff);
	}
	
	else if(!pref.empty()){
		if(b > c + 2 || b < c){
			puts("NO");
			return 0;
		}
		string res = pref;
		loop(i,c){
			res.push_back('1');
			res.push_back('2');
			b--;
		}
		if(b) res.push_back('1'),b--;
		if(b) res = "1" + res,b--;
		assert(b == 0);
		answer(res);
	}
	else if(!suff.empty()){
		if(c < b || c > b + 2) {
			puts("NO");
			return 0;
		}
		string res = suff;
		loop(i,b){
			res.push_back('2');
			res.push_back('1');
			c--;
		}
		if(c) res.push_back('2'),c--;
		if(c) res = "2" + res,c--;
		assert(c==0);
		answer(res);
	}
	else {
		if(abs(b-c) > 1) {
			puts("NO");
			return 0;
		}
		int len = min(b,c);
		string res ;
		loop(i,len) {
			res.push_back('1');
			res.push_back('2');
			b--,c--;
		}
		if(b) res += "1",b --;
		else if(c) res = "2" + res,c--;
		assert(b==0 && c==0);
		answer(res);
	}
	return 0;
}
