#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


string out;
char buffer[50];

void write(int x) {
	sprintf(buffer,"%d",x);
	out += string(buffer);
}

string form(int c,int p) {
	string ret;
	if(c != 1) ret += to_string(c);
	if(p) ret.push_back('x');
	if(p > 1) ret += to_string(p);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	string s; cin >> s;
	int sgn = (s[0] == '-') ? -1 : 1;
	for(int i = s[0]=='-';i < sz(s);i++) {
		int j = i;
		while(j < sz(s) && (s[j] != '-' && s[j] != '+')) j++;
		string term = s.substr(i,j-i);
//		cout << sgn << " " << term << endl;
		int c = 1;
		if(term[0] != 'x') sscanf(term.c_str(),"%d",&c);
		int p = 0;
		auto ptr = find(all(term),'x');
		if(ptr != term.end()) {
			p = 1;
			ptr++;
			if(ptr != term.end()){
				p = 0;
				while(ptr != term.end()){
					p = p*10 + *ptr - '0';
					ptr++;
				}
			}
		}
		c *= sgn*p;
		p--;

		if(c) {
			if(c < 0) out.push_back('-'),c *= -1;
			else if(!out.empty()) out.push_back('+');
			string aux = form(c,p);
			if(aux.empty()) aux = "1";
			out += aux;
		}

		if(j < sz(s)) sgn = (s[j] == '+' ) ? 1 : -1;
		i = j;
	}
	if(out.empty()) out = "0";
	cout << out << endl;
	return 0;
}
#endif
