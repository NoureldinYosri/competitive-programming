#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int seed = 0,MAXM = 100,MAXA = 10000,MAXLEN = 4000;
const int POPCNT = 100,IPOPLEN = 5;
int N,M,A,X,R;
string S,T[MAXM],P[MAXA];
int C[MAXM],Q[MAXA];


int getVal(char c){
	if(islower(c)) return c - 'a' + 1;
	return c - 'A' + 27;
}

string readString(char *dist) {
	static char buffer[1 << 20];
	if(dist) {
		scanf("%s",dist);
		return "";
	}
	else {
		scanf("%s",buffer);
		return string(buffer);
	}
}

void read(){
	scanf("%d %d %d %d %d",&N,&M,&A,&X,&R);
	S = readString(0);
	loop(i,M) {
		T[i] = readString(0);
		scanf("%d",C + i);
	}
	loop(i,A) {
		P[i] = readString(0);
		scanf("%d",Q + i);
	}
}

string int2alpha(int x) {
	static char buffer[2];
	sprintf(buffer,"%c",x);
	return string(buffer);
}

struct op{
	int type;
	vi vals;
	op(){}
	op(int t,vi V) {
		type = t;
		vals = V;
	}
	string toString(){
		string ret = to_string(type);
		bool f = 1;
		for(int x : vals) {
			string y = to_string(x);
			if(type == 1 && !f) y = int2alpha(x);
			f = 0;
			ret += " " + y;
		}

		return ret;
	}
};


typedef vector<op> member;
vector<member > pop;

op create_random(bool f = 0){
	static vi aux;
	int t = rand()%(2 + f) + 1;
	aux.clear();
	if(t == 1) {
		aux.push_back(rand()%N + 1);
		aux.push_back(alphabet[rand()%sz(alphabet)]);
	}
	else {
		int l = rand()%N + 1;
		int r = rand()%N + 1;
		if(r < l) swap(l,r);
		aux.push_back(l);
		aux.push_back(r);
		if(t == 2) aux.push_back(rand()%A + 1);
	}
	return op(t,aux);
}

vector<op> createSeq(){
	static vector<op> V;
	int len = rand()%IPOPLEN + 1;
	V.clear();
	loop(j,len) V.push_back(create_random());
	return V;
}

void init(){
	loop(i,POPCNT) {
		pop.push_back(createSeq());
	}
}

inline void split(string s,int l,int r,string & pref,string & mid,string & suff) {
	loop(i,sz(s)) {
		if(i < l) pref += s[i];
		else if(i < r) mid += s[i];
		else suff += s[i];
	}
}

string apply(member & seq,ll & score) {
	string ret = S;
	int ctr = 0;
	for(op & O : seq) {
		if(sz(ret) > MAXLEN) return ret;
		if(O.type == 1) {
			int i = O.vals[0] - 1;
			score -= abs(O.vals[1] - ret[i]);
			ret[i] = O.vals[1];
		}
		else if(O.type == 2) {
			int l = O.vals[0] - 1,r = O.vals[1] - 1;
			if(r >= sz(ret)) {
				score -= 10000;
				continue;
			}
			int i = O.vals.back()-1;
			score -= Q[i];
			string pref,mid,suff;
			split(ret,l,r,pref,mid,suff);
//			string s = P[i];
			string s = "";
			ret = pref + s + suff;
		}
		else {
			int l = O.vals[0] - 1,r = O.vals[1] - 1;
			if(r >= sz(ret)) {
				score -= 10000;
				continue;
			}
			score -= R;
			ctr ++;
			string pref,mid,suff;
			split(ret,l,r,pref,mid,suff);
			string s = mid;
			s += s;
			ret += pref + s + suff;
		}
	}
	score -= abs(ctr - 3) * 1000000LL;
	return ret;
}

bool Find(string & text,string pat,int & f) {
	for(;f <= sz(text)-sz(pat);f++) {
		bool y = 1;
		for(int i = 0;i < sz(pat) && y;i++)
			y &= text[f + i] == pat[i];
		if(y) return y;
	}
	return 0;
}

ll eval(string & S) {
	ll ret = 0;
	loop(i,M) {
		int f = 0,ctr = 0;
		while(Find(S,T[i],f)) {
			ctr++;
			f++;
		}
		ret += ctr*(ll)C[i];
	}
	return ret;
}

ll measureFitness(vector<op> & seq) {
	ll score = 0;
	string res = apply(seq,score);
	ll pen = 100;
	if(sz(res) > MAXLEN) {
		score -= pen*(MAXLEN - sz(res));
		res = res.substr(0,MAXLEN);
	}
	score += eval(res);
	return score;
}


void enforceOrder(){
	static vi ord;
	static vector<ll> F;
	static vector<member> aux;
	int n = sz(pop);
	ord.resize(n);
	F.resize(n);
	aux.resize(n);

	loop(i,n) F[i] = measureFitness(pop[i]),ord[i] = i;
	sort(all(ord),[](const int & a,const int & b) {
		return -F[a] < -F[b];
	});
	loop(i,n) aux[i] = pop[ord[i]];
	pop.swap(aux);
}

vector<member> sample(int n){
	static int mu = 2;
    static random_device rd;
    static mt19937 gen(rd());
    static poisson_distribution<> D(mu);
    static vector<member> ret;
    ret.clear();
    for(int i = 0;i < 2*n && sz(ret) < n;i++)
    	ret.push_back(pop[D(gen)%sz(pop)]);
    return ret;
}

member mate(member a,member b){
	int i = 0,j = 0;
	int n = sz(a),m = sz(b);
	member ret;
	while(i < n && j < m){
		if(rand()&1) ret.pb(a[i]);
		else ret.pb(b[j]);
		i++,j++;
	}
	for(;i < n;i++) {
		if(rand()&3) ret.push_back(a[i]);
	}
	for(;j < m;j++) {
		if(rand()%3) ret.push_back(b[j]);
	}
	return ret;
}

vector<member> Mate(){
	vector<member> V = sample(max(2,sz(pop)/8));
	vector<member> ret;
	for(int i = 0;i + 1 < sz(V);i += 2) {
		int l = rand()%3 + 1;
		loop(j,l)
			ret.push_back(mate(V[i],V[i+1]));
	}
	return ret;
}


vector<op> solve(){
	for(int t = 1;t <= 100;t++) {
		enforceOrder();
		vector<member> offSpring = Mate();
		for(member & seq : offSpring)
			pop.push_back(seq);

		enforceOrder();
		pop = sample(100);
		for(int i = 0,L = rand()%6;i < L;i++)
			pop.push_back(createSeq());
	}
	enforceOrder();
	return pop[0];
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	srand(seed);
	read();
//	init();
//	vector<op> fittest = solve();
	vector<op> fittest;
	int n = rand()%50;
	int ctr = 0;
	loop(i,n) {
		if(N >= 50000) break;
		op O = create_random(ctr < 3);
		ctr += O.type == 3;
		if(O.type == 1) O.vals[0] = rand()%N + 1;
		else {
			int l = rand()%N + 1;
			int r = rand()%N + 1;
			if(r < l) swap(l,r);
			if(O.type == 2) {
				int i = rand()%A;
				N += r-l+1 + sz(P[i]);
				O.vals.back() = i+1;
			}
			else N += 2*(r-l+1);
			O.vals[0] = l;
			O.vals[1] = r;
		}
		fittest.push_back(O);
	}
	printf("%d\n",sz(fittest));
	for(op & O : fittest)
		printf("%s\n",O.toString().c_str());

	return 0;
}
