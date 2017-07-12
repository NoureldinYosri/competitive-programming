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
#define popcnt(x) __builtin_popcount(x)
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

struct mat{
	vector<vector<vi> > E;
public:
	mat(){}
	mat(int a,int b,int c,vi vals){
		E = vector<vector<vi> >(a,vector<vi>(b,vi(c,0)));
		loop(i,a) loop(j,b) loop(k,c) E[i][j][k] = vals[(i*b*c + j*c + k)%sz(vals)];
	}
};

char buffer[100];
map<string,mat> mem;


bool isOperator(string tok){
	return tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "iota" || tok == "rho" || tok == "drop";
}

vector<mat> parse(){
	vector<string> V;
	for(char *token = strtok(buffer," ");token;token = strtok(0," ")){
		string tok = string(token);
		V.pb(tok);
	}
	vector<mat> ST;
	for(int i = 0,L = sz(V);i < L;i++){
		
	}
	assert(ST.size() == 1);
	return ST[0];
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif

	return 0;
}
