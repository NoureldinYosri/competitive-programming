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

int B,S;
vector<string> prog;
char buffer[50];
ll C[13][13];
int mx = 0;

int getVal(string s){
	int ret;
	sscanf(s.c_str()+1,"%d",&ret);
	return ret;
}

ll getBase(){
	vector<string> ST;
	ll cnt = 1,ret = 0;
	for(string s : prog) {
		if(s == "E"){
			assert(!ST.empty());
			assert(cnt%getVal(ST.back()) == 0);
			cnt /= getVal(ST.back());
			ST.pop_back();
		}
		else if(s[0] == 'V') {
			ret += cnt;
		}
		else {
			assert(s[0] == 'R');
			cnt *= getVal(s);
			ST.pb(s);
		}
	}
	return ret;
}

vector<string> removeSpecial(int msk) {
	vector<string> ret;
	for(string s : prog) {
		if(s == "E"){
			assert(!ret.empty());
			if(ret.back()[0] == 'R') ret.pop_back();
			else ret.pb(s);
		}
		else if(s[0] == 'V') {
			int x = getVal(s) - 1;
			if(!((msk >> x) & 1))
				ret.pb(s);
		}
		else {
			assert(s[0] == 'R');
			ret.pb(s);
		}
	}
//	print(ret,string);
	return ret;
}

struct state{
	vector<vl> C;
	int l, r;
public:
	state(){
		l = r = 0;
		C = vector<vl>(mx,vl(mx,0));
	}
	friend ostream& operator << (ostream & st,const state & s) {
		st << "(" << s.l+1 << " ," << s.r+1 <<  ")" << endl;
		loop(i,sz(s.C)) {
			loop(j,sz(s.C)) st << s.C[i][j] << " ";
			st << endl;
		}
		return st;
	}
	state operator + (const state & o) {
		state ret;
		ret.l = this->l;
		ret.r = o.r;
		loop(i,mx) loop(j,mx) ret.C[i][j] = this->C[i][j] + o.C[i][j];
		if(this->r != o.l) ret.C[this->r][o.l]++;
		return ret;
	}
};

int nxt[2000];
vi ST;
void preprocess(vector<string> & V) {
	int n = sz(V);
	loop(i,n){
		if(V[i] == "E") {
			assert(!ST.empty());
			nxt[ST.back()] = i;
			ST.pop_back();
		}
		else if(V[i][0] == 'R') {
			ST.pb(i);
		}
	}
	assert(ST.empty());
}

state buildTransitionMatrix(vector<string> & V,int s,int e) {
	assert(s <= e);
	state ret;
	if(s == e || V[s][0] == 'V') {
		assert(V[s][0] == 'V');
		int x = getVal(V[s])-1;
		ret.l = ret.r = x;
		if(s < e) ret = ret + buildTransitionMatrix(V,s+1,e);
		return ret;
	}
	assert(V[s][0] == 'R');

	state aux = buildTransitionMatrix(V,s+1,nxt[s]-1);
	int val = getVal(V[s]);
	ret = aux;
	loop(i,mx) loop(j,mx) ret.C[i][j] *= val;
	if(ret.l != ret.r) ret.C[ret.r][ret.l] += val-1;

	if(nxt[s] != e) ret = ret + buildTransitionMatrix(V,nxt[s]+1,e);
	return ret;
}

const ll oo = 1LL << 60;
ll dp[2][14][1 << 13],f[1 << 13];
int lg[1 << 13];

ll brute_force(int submsk) {
	loop(i,mx) assert(C[i][i] == 0);

	ll ret = 0;
	loop(i,mx) if(submsk & (1 << i)) loop(j,mx) if(!(submsk & (1 << j))) {
		ret += C[i][j];
	}
	return ret;
}

void buildF(int msk){
	loop(i,13) lg[1 << i] = i;
	vi V;
	loop(i,mx) if(!(msk & (1 << i))) V.pb(i);
	loop(submsk,1 << sz(V)) if(popcnt(msk) <= S){
		int new_msk = 0;
		loop(i,sz(V))
			if(submsk & (1 << i))
				new_msk |= 1 << V[i];
		f[new_msk] = brute_force(new_msk);
	}
}

vi cand[1 << 13];

ll solve(int TOT){
	static vi V;
	V.clear();
	loop(i,mx) if(TOT & (1 << i)) V.pb(i);
	for(int msk = 1;msk <= TOT;msk++)
		range(s,1,S)
			dp[0][s][msk] = oo;
	int one = 1,other = 0;
	for(int k = 1;k < B;k++) {
		for(int msk = 1;msk <= TOT;msk++)
			dp[one][0][msk] = oo;
		for(int tmsk = 1;tmsk < (1 << sz(V));tmsk++){
			int msk = 0;
			loop(i,sz(V)) if(tmsk & (1 << i)) msk |= 1 << V[i];
			for(int s = 1;s <= S;s++){
				dp[one][s][msk] = dp[one][s-1][msk];

				for(int blk : cand[msk])
					dp[one][s][msk] = min(dp[one][s][msk], f[blk] +  dp[other][s][msk ^ blk]);
			}
		}
		swap(one,other);
	}
	return dp[other][S][TOT];
}

void preprocess(){
	vi V;
	loop(msk,1 << 13){
		V.clear();
		loop(i,13) if(msk & (1 << i)) V.pb(i);
		loop(submsk,1 << sz(V)) if(submsk && popcnt(submsk) <= S){
			int new_msk = 0;
			loop(i,sz(V))
				if(submsk & (1 << i))
					new_msk |= 1 << V[i];
			assert((new_msk & msk) == new_msk);
			cand[msk].pb(new_msk);
		}
	}
}

bool trysolve(){
	mx = 0;
	if(scanf("%d %d",&B,&S) != 2) return 0;
	while(scanf("%s",buffer) == 1) prog.pb(string(buffer));
	for(string s : prog)
		if(s[0] == 'V')
			mx = max(mx,getVal(s));
	assert(mx <= 13);
	S = min(S,mx);
	ll ans = LLONG_MAX,base = getBase();


	vi zero;
	loop(msk,1 << mx) if(popcnt(msk) == S) zero.pb(msk);
	loop(q,sz(zero)) {
		int msk = zero[q];

		vector<string> aux = removeSpecial(msk);
		preprocess(aux);
		memset(C,0,sizeof C);
		state TM ;
		if(!aux.empty()) TM = buildTransitionMatrix(aux,0,sz(aux)-1);

		loop(i,mx) loop(j,mx) C[i][j] = TM.C[i][j];

		ll tmp = base;
		int tot = (1 << mx) - 1;
		buildF(msk);
		tmp += !aux.empty() + solve(tot ^ msk);
		ans = min(ans,tmp);
	}
	printf("%lld\n",ans);
	return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	preprocess();
	while(trysolve());
	return 0;
}
