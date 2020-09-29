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


vector<pair<pi, vi>> belief;
char buffer[1 << 20];
int n;
char txt[1 << 20];
vector<string> key;
string res[1 << 20];
int R[1 << 20];

void bt(string & s){
	if(sz(key) == n) return;
	if(sz(s) == 3) {
		key.emplace_back(s);
		return;
	}
	for(char c = 'a'; c <= 'z'; c++){
		s.push_back(c);
		bt(s);
		s.pop_back();
	}
}


void ask(){
	buffer[n] = 0;
	printf("? %s\n", buffer);
	fflush(stdout);
	scanf("%s", buffer);
	loop(i, n) res[i].pb(buffer[i]); 
}


int main(){

	scanf("%s", txt);
	n = strlen(txt);
	string aux; bt(aux);
	loop(q, 3){
		loop(i, n) buffer[i] = key[i][q];	
		ask();
	}
	map<string, int> M;
	loop(i, n) M[key[i]] = i;
	loop(i, n) {
		string s = res[i];
		assert(M.count(s));
		R[i] = M[s];
	}
	loop(i, n) buffer[R[i]] = txt[i];
	cout << "! " << buffer << endl;
	return 0;
}
