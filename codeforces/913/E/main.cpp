#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

#define white 0
#define grey 1
#define black 2

string f[1 << 8],g[1 << 8];
int vis[1 << 8];

string bin(int msk) {
	string s(8,'0');
	loop(i,8) if(msk & (1 << i)) s[i] = '1';
	return s;
}

string dfs(int);

string argmin(string a,string b) {
	if(a.empty()) return b;
	if(b.empty()) return a;
	if(sz(a) < sz(b)) return a;
	if(sz(a) > sz(b)) return b;
	return min(a,b);
}


bool freeAnd(string s) {
	int ctr = 0;
	for(char c : s) {
		if(c == '(') ++ctr;
		else if(c == ')') --ctr;
		else if(c == '&' && ctr == 0) return 1;
	}
	return 0;
}
bool freeOr(string s) {
	int ctr = 0;
	for(char c : s) {
		if(c == '(') ++ctr;
		else if(c == ')') --ctr;
		else if(c == '|' && ctr == 0) return 1;
	}
	return 0;
}

string doAnd(int msk) {
	vi V;
	loop(i,8) if(!(msk & (1 << i))) V.pb(i);
	string ret = "";
	int tot = 1;
	loop(i,sz(V)) tot *= 3;

	for(int tmsk = 0;tmsk < tot;tmsk++) {
		int cur = tmsk ;
		int L = msk,R = msk;
		for(int j : V) {
			L |= (1 << j);
			R |= (1 << j);
		}
		loop(i,sz(V)) {
			int r = cur%3,j = V[i];
			cur /= 3;
			if(r == 0 || r == 2) L &= ~(1 << j);
			if(r == 1 || r == 2) R &= ~(1 << j);
		}
		string a = dfs(L),b = dfs(R);
		if(!a.empty() && !b.empty()) {
			if(freeOr(a) && sz(a) > 2) a = "(" + a + ")";
			if(freeOr(b) && sz(b) > 2) b = "(" + b + ")";
			string tmp = a + "&" + b;
			ret = argmin(ret,tmp);
		}
	}

	return ret;
}

string doOr(int msk) {
	vi V;
	loop(i,8) if(msk & (1 << i)) V.pb(i);
	string ret = "";
	int tot = 1;
	loop(i,sz(V)) tot *= 3;
	vp S;
	for(int tmsk = 0;tmsk < tot;tmsk++) {
		int cur = tmsk;
		int L = msk,R = msk;
		for(int j : V) {
			L &= ~(1 << j);
			R &= ~(1 << j);
		}
		loop(i,sz(V)) {
			int r = cur%3,j = V[i];
			cur /= 3;
			if(r == 0 || r == 2) L |= (1 << j);
			if(r == 1 || r == 2) R |= (1 << j);
		}
//		cerr << bin(msk) << " = " << bin(L) << " | " << bin(R) << " ... " << tmsk << endl;
		S.pb(mp(L,R));
	}
//	exit(0);
	for(auto p : S) {
		int L = p.xx,R = p.yy;
		string a = dfs(L),b = dfs(R);
		if(!a.empty() && !b.empty()) {
//			if(freeAnd(a) && sz(a) > 2) a = "(" + a + ")";
//			if(freeAnd(b) && sz(b) > 2) b = "(" + b + ")";
			string tmp = a + "|" + b;
			ret = argmin(ret,tmp);
		}
	}
	return ret;
}

bool terminal(int msk,string & ret) {
	string s = bin(msk);
	if(s == "00001111") return ret = "x",1;
	if(s == "11110000") return ret = "!x",1;
	if(s == "00110011") return ret = "y",1;
	if(s == "11001100") return ret = "!y",1;
	if(s == "01010101") return ret = "z",1;
	if(s == "10101010") return ret = "!z",1;

	return 0;
}

string doNot(int msk) {
	string res = dfs(~msk & 0xFF);
	if(res == "") return "";
	if(sz(res) > 1) res = "(" + res + ")";
	res = "!" + res;
	return res;
}


string dfs(int msk) {
	string x;
	if(terminal(msk,x)) return vis[msk] = black,g[msk] = x;
	if(vis[msk] == black) return g[msk];
	if(vis[msk] == grey) return "";
	vis[msk] = grey;
	string res = "";
	string a = doOr(msk);
	string b = doAnd(msk);
	string c = doNot(msk);
	if(!a.empty()) res = argmin(res,a);
	if(!b.empty()) res = argmin(res,b);
	if(!c.empty()) res = argmin(res,c);
	vis[msk] = black;
//	cerr << "'" << a << "' '" << b << "' '" << c << "' = '" << res << "'" << endl;
	return g[msk] = res;
}

int b2d(string s) {
//	reverse(all(s));
	int msk = 0;
	loop(i,8) msk |= (s[i] - '0') << i;
	return msk;
}

vector<string> S = {"00000000" ,"10000000" ,"01000000" ,"11000000" ,"00100000" ,"10100000" ,"01100000" ,"11100000" ,"00010000" ,"10010000" ,"01010000" ,"11010000" ,"00110000" ,"10110000" ,"01110000" ,"11110000" ,"00001000" ,"10001000" ,"01001000" ,"11001000" ,"00101000" ,"10101000" ,"01101000" ,"11101000" ,"00011000" ,"10011000" ,"01011000" ,"11011000" ,"00111000" ,"10111000" ,"01111000" ,"11111000" ,"00000100" ,"10000100" ,"01000100" ,"11000100" ,"00100100" ,"10100100" ,"01100100" ,"11100100" ,"00010100" ,"10010100" ,"01010100" ,"11010100" ,"00110100" ,"10110100" ,"01110100" ,"11110100" ,"00001100" ,"10001100" ,"01001100" ,"11001100" ,"00101100" ,"10101100" ,"01101100" ,"11101100" ,"00011100" ,"10011100" ,"01011100" ,"11011100" ,"00111100" ,"10111100" ,"01111100" ,"11111100" ,"00000010" ,"10000010" ,"01000010" ,"11000010" ,"00100010" ,"10100010" ,"01100010" ,"11100010" ,"00010010" ,"10010010" ,"01010010" ,"11010010" ,"00110010" ,"10110010" ,"01110010" ,"11110010" ,"00001010" ,"10001010" ,"01001010" ,"11001010" ,"00101010" ,"10101010" ,"01101010" ,"11101010" ,"00011010" ,"10011010" ,"01011010" ,"11011010" ,"00111010" ,"10111010" ,"01111010" ,"11111010" ,"00000110" ,"10000110" ,"01000110" ,"11000110" ,"00100110" ,"10100110" ,"01100110" ,"11100110" ,"00010110" ,"10010110" ,"01010110" ,"11010110" ,"00110110" ,"10110110" ,"01110110" ,"11110110" ,"00001110" ,"10001110" ,"01001110" ,"11001110" ,"00101110" ,"10101110" ,"01101110" ,"11101110" ,"00011110" ,"10011110" ,"01011110" ,"11011110" ,"00111110" ,"10111110" ,"01111110" ,"11111110" ,"00000001" ,"10000001" ,"01000001" ,"11000001" ,"00100001" ,"10100001" ,"01100001" ,"11100001" ,"00010001" ,"10010001" ,"01010001" ,"11010001" ,"00110001" ,"10110001" ,"01110001" ,"11110001" ,"00001001" ,"10001001" ,"01001001" ,"11001001" ,"00101001" ,"10101001" ,"01101001" ,"11101001" ,"00011001" ,"10011001" ,"01011001" ,"11011001" ,"00111001" ,"10111001" ,"01111001" ,"11111001" ,"00000101" ,"10000101" ,"01000101" ,"11000101" ,"00100101" ,"10100101" ,"01100101" ,"11100101" ,"00010101" ,"10010101" ,"01010101" ,"11010101" ,"00110101" ,"10110101" ,"01110101" ,"11110101" ,"00001101" ,"10001101" ,"01001101" ,"11001101" ,"00101101" ,"10101101" ,"01101101" ,"11101101" ,"00011101" ,"10011101" ,"01011101" ,"11011101" ,"00111101" ,"10111101" ,"01111101" ,"11111101" ,"00000011" ,"10000011" ,"01000011" ,"11000011" ,"00100011" ,"10100011" ,"01100011" ,"11100011" ,"00010011" ,"10010011" ,"01010011" ,"11010011" ,"00110011" ,"10110011" ,"01110011" ,"11110011" ,"00001011" ,"10001011" ,"01001011" ,"11001011" ,"00101011" ,"10101011" ,"01101011" ,"11101011" ,"00011011" ,"10011011" ,"01011011" ,"11011011" ,"00111011" ,"10111011" ,"01111011" ,"11111011" ,"00000111" ,"10000111" ,"01000111" ,"11000111" ,"00100111" ,"10100111" ,"01100111" ,"11100111" ,"00010111" ,"10010111" ,"01010111" ,"11010111" ,"00110111" ,"10110111" ,"01110111" ,"11110111" ,"00001111" ,"10001111" ,"01001111" ,"11001111" ,"00101111" ,"10101111" ,"01101111" ,"11101111" ,"00011111" ,"10011111" ,"01011111" ,"11011111" ,"00111111" ,"10111111" ,"01111111" ,"11111111" };
vector<string> F = {"!x&x" ,"!(x|y|z)" ,"!x&!y&z" ,"!x&!y" ,"!x&!z&y" ,"!x&!z" ,"!x&!y&z|!x&!z&y" ,"!(x|y&z)" ,"!x&y&z" ,"!x&!y&!z|!x&y&z" ,"!x&z" ,"!(!z&y|x)" ,"!x&y" ,"!(!y&z|x)" ,"!x&(y|z)" ,"!x" ,"!y&!z&x" ,"!y&!z" ,"!(x&z|y)&(x|z)" ,"!(x&z|y)" ,"!x&!z&y|!y&!z&x" ,"!z&(!x|!y)" ,"!x&(!y&z|!z&y|x)|!y&!z&x" ,"!(x&z|y)|!x&!z" ,"!x&y&z|!y&!z&x" ,"!x&y&z|!y&!z" ,"!x&z|!y&!z&x" ,"!x&z|!y&!z" ,"!x&y|!y&!z&x" ,"!x&y|!y&!z" ,"(!x|!y)&(!x|!z)&(x|y|z)" ,"!x|!y&!z" ,"!y&x&z" ,"!x&!y&!z|!y&x&z" ,"!y&z" ,"!y&(!x|z)" ,"!x&!z&y|!y&x&z" ,"!x&!z|!y&x&z" ,"!x&!z&y|!y&z" ,"!x&!z|!y&z" ,"!x&y&z|!y&x&z" ,"!(!y&z|!z&y|x)|!y&x&z" ,"!x&z|!y&z" ,"!x&(!y|z)|!y&z" ,"!x&y|!y&x&z" ,"!x&(!z|y)|!y&x&z" ,"!x&y|!y&z" ,"!x|!y&z" ,"!y&x" ,"!y&(!z|x)" ,"!y&(x|z)" ,"!y" ,"!x&!z&y|!y&x" ,"!x&!z|!y&x" ,"!x&(!y&z|!z&y|x)|!y&x" ,"!x&!z|!y" ,"!x&y&z|!y&x" ,"!x&y&z|!y&(!z|x)" ,"!x&z|!y&x" ,"!x&z|!y" ,"!x&y|!y&x" ,"!x&(!z|y)|!y&x" ,"(!x|!y)&(x|y|z)" ,"!x|!y" ,"!z&x&y" ,"!x&!y&!z|!z&x&y" ,"!x&!y&z|!z&x&y" ,"!x&!y|!z&x&y" ,"!z&y" ,"!z&(!x|y)" ,"!x&!y&z|!z&y" ,"!x&!y|!z&y" ,"!x&y&z|!z&x&y" ,"!(!y&z|!z&y|x)|!z&x&y" ,"!x&z|!z&x&y" ,"!x&(!y|z)|!z&x&y" ,"!x&y|!z&y" ,"!x&(!z|y)|!z&y" ,"!x&z|!z&y" ,"!x|!z&y" ,"!z&x" ,"!(!x&y|z)" ,"!x&!y&z|!z&x" ,"!x&!y|!z&x" ,"!z&(x|y)" ,"!z" ,"!x&(!y&z|!z&y|x)|!z&x" ,"!x&!y|!z" ,"!x&y&z|!z&x" ,"!x&y&z|!z&(!y|x)" ,"!x&z|!z&x" ,"!x&(!y|z)|!z&x" ,"!x&y|!z&x" ,"!x&y|!z" ,"(!x|!z)&(x|y|z)" ,"!x|!z" ,"!y&x&z|!z&x&y" ,"!y&(!x|z)&(!z|x)|!z&x&y" ,"!y&z|!z&x&y" ,"!y&(!x|z)|!z&x&y" ,"!y&x&z|!z&y" ,"!y&x&z|!z&(!x|y)" ,"!y&z|!z&y" ,"!y&(!x|z)|!z&y" ,"!z&x&y|(!x|!y)&z&(x&z|y)" ,"!z&(!x|y)&(!y|x)|(!x|!y)&z&(x&z|y)" ,"!z&x&y|(!x|!y)&z" ,"!z&(!x|y)&(!y|x)|(!x|!y)&z" ,"!y&x&z|(!x|!z)&y" ,"!z&(!x|y)|(!x|!y)&(x&z|y)" ,"!y&z|(!x|!z)&y" ,"!((!y|z)&x)|!y&z" ,"!(!x|y&z)" ,"!y&(!z|x)|!z&x" ,"!y&z|!z&x" ,"!y|!z&x" ,"!y&x|!z&y" ,"!y&x|!z" ,"(!y|!z)&(x|y|z)" ,"!y|!z" ,"!x&y&z|(!y|!z)&x" ,"!(!y&z|!z&y|x)|(!y|!z)&x" ,"!x&z|(!y|!z)&x" ,"!((!x|z)&(!z|x)&y)" ,"!x&y|(!y|!z)&x" ,"!((!x|y)&(!y|x)&z)" ,"!y&x|(!x|!z)&(y|z)" ,"!(x&y&z)" ,"x&y&z" ,"!x&!y&!z|x&y&z" ,"!x&!y&z|x&y&z" ,"!x&!y|x&y&z" ,"!x&!z&y|x&y&z" ,"!x&!z|x&y&z" ,"!x&(!y&z|!z&y|x)|x&y&z" ,"!x&(!y|!z)|x&y&z" ,"y&z" ,"!x&!y&!z|y&z" ,"!x&z|y&z" ,"!x&!y|y&z" ,"!x&y|y&z" ,"!x&!z|y&z" ,"!x&y|(!x|y)&z" ,"!x|y&z" ,"!y&!z&x|x&y&z" ,"!y&!z|x&y&z" ,"!x&!y&z|(!y|z)&(!z|y)&x" ,"!(x&z|y)|x&y&z" ,"!x&!z&y|(!y|z)&(!z|y)&x" ,"!z&(!x|!y)|x&y&z" ,"!x&(!y&z|!z&y|x)|(!y|z)&(!z|y)&x" ,"!(x&z|y)|(!x|y&z)&(!z|x)" ,"!y&!z&x|y&z" ,"!y&!z|y&z" ,"!y&!z&x|(!x|y)&z" ,"!(x&z|y)|y&z" ,"!x&y|y&z|!y&!z&x" ,"!x&y|y&z|!y&!z" ,"!x&y|(!x|y)&z|!y&!z&x" ,"!x|y&z|!y&!z" ,"x&z" ,"!x&!y&!z|x&z" ,"!y&z|x&z" ,"!x&!y|x&z" ,"!x&!z&y|x&z" ,"!x&!z|x&z" ,"!x&!z&y|(!y|x)&z" ,"!x&!z|(!y|x)&z" ,"(x|y)&z" ,"!(!y&z|!z&y|x)|x&z" ,"z" ,"!x&!y|z" ,"!x&y|x&z" ,"!x&(!z|y)|x&z" ,"!x&y|z" ,"!x|z" ,"!y&x|x&z" ,"!y&!z|x&z" ,"!y&x|(!y|x)&z" ,"!y|x&z" ,"!x&!z&y|(!y|z)&x" ,"!x&!z|(!y|z)&x" ,"!x&(!y&z|!z&y|x)|(!y|z)&x" ,"!y|(!x|z)&(!z|x)" ,"!y&x|y&z" ,"!y&(!z|x)|y&z" ,"!y&x|z" ,"!y|z" ,"!x&y|(!y|z)&x" ,"!x&(!z|y)|(!y|z)&x" ,"!x&y|z|!y&x" ,"!x|!y|z" ,"x&y" ,"!x&!y&!z|x&y" ,"!x&!y&z|x&y" ,"!x&!y|x&y" ,"!z&y|x&y" ,"!x&!z|x&y" ,"!x&!y&z|(!z|x)&y" ,"!x&!y|(!z|x)&y" ,"(x|z)&y" ,"!(!y&z|!z&y|x)|x&y" ,"!x&z|x&y" ,"!x&(!y|z)|x&y" ,"y" ,"!x&!z|y" ,"!x&z|y" ,"!x|y" ,"!z&x|x&y" ,"!y&!z|x&y" ,"!x&!y&z|(!z|y)&x" ,"!(x&z|y)|x&y" ,"!z&x|(!z|x)&y" ,"!z|x&y" ,"(!x|!z|y)&(!y&z|!z&y|x)" ,"!z|(!x|y)&(!y|x)" ,"!z&x|y&z" ,"!z&(!y|x)|y&z" ,"!x&z|(!z|y)&x" ,"!x&(!y|z)|(!z|y)&x" ,"!z&x|y" ,"!z|y" ,"(!x|!z|y)&(x|y|z)" ,"!x|!z|y" ,"(y|z)&x" ,"!x&!y&!z|(y|z)&x" ,"!y&z|x&y" ,"!x&!y|(y|z)&x" ,"!z&y|x&z" ,"!x&!z|(y|z)&x" ,"!y&z|!z&y|x&z" ,"!x&!y|!z&y|x&z" ,"(y|z)&x|y&z" ,"!(!y&z|!z&y|x)|(y|z)&x" ,"x&y|z" ,"(!x|y)&(!y|x)|z" ,"x&z|y" ,"!x&!z|x&z|y" ,"y|z" ,"!x|y|z" ,"x" ,"!y&!z|x" ,"!y&z|x" ,"!y|x" ,"!z&y|x" ,"!z|x" ,"!y&z|!z&y|x" ,"!y|!z|x" ,"x|y&z" ,"!y&!z|x|y&z" ,"x|z" ,"!y|x|z" ,"x|y" ,"!z|x|y" ,"x|y|z" ,"!x|x" };



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("out.out","w",stdout);
	#endif
//	loop(msk,1 << 8) {
//		memset(vis,0,sizeof vis);
//		f[msk] = dfs(msk);
//	}
//	cout << "{";
//	loop(msk,1 << 8)
//		if(!f[msk].empty()) cout << "\"" << bin(msk) << "\" ,";
//	cout << "}" << endl;
//	cout << "{";
//	loop(msk,1 << 8)
//		if(!f[msk].empty()) cout << "\"" << f[msk] << "\" ,";
//	cout << "}" << endl;
//
	map<string,string> mem;
	loop(i,sz(S)) mem[S[i]] = F[i];
	PRESTDIO();
	int n; cin >> n;
	loop(i,n) {
		string s; cin >> s;
		cout << mem[s] << endl;
	}

	return 0;
}
