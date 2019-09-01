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

int n;
int A[50];

int parse(string s) {
	static map<string,int> M = {{"A",1},{"10",10},{"J",11},{"Q",12}};
	if(M.count(s)) return M[s] - 1;
	assert('2' <= s[0] && s[0] <= '9');
	return s[0] - '0' - 1;
}

const int MAX = 2 << 10;
map<vi,int> v2i;
vi i2v[MAX];

int tot = 0;
void bt(int cur,vi & ctr,int low) {
	if(cur == -1) {
		assert(tot < MAX);
		vi V{all(ctr)};
		while(!V.empty() && V.back() == 0) V.pop_back();
		v2i[V] = tot;
		i2v[tot] = V;
		tot++;
		return;
	}
	if(low > 4) return;
	ctr[cur] = low;
	bt(cur-1,ctr,low);
	bt(cur,ctr,low+1);
}

void init(){
	int N = 11;
	vi ctr(N,0);
	bt(N-1,ctr,0);
}

vi play(int & p) {
	static int ctr[12];
	loop(i,12) ctr[i] = 4;
	p = 0;
	loop(i,n){
		int c = A[i];
		ctr[p]--;
		p = c;
	}
	return vi{ctr,ctr + 12};
}

int encode(const vi & ctr,int j = -1,int k = -1) {
	static vi V;
	V.clear();
	loop(i,sz(ctr)) {
		if(i == j || i == k || !ctr[i]) continue;
		V.push_back(ctr[i]);
	}
	sort(all(V));
	reverse(all(V));
	assert(v2i.count(V));
	return v2i[V];
}


struct fraction{
	int a,b;
	fraction(){
		a = 0;
		b = 1;
	}
	fraction(int x,int y) {
		int g = __gcd(x,y);
		a = x/g;
		b = y/g;
	}
	fraction operator + (const fraction & o) const {
		int d = b*(o.b/__gcd(b,o.b));
		return fraction(a*(d/b) + o.a*(d/o.b),d);
	}
	fraction operator - (const fraction & o) const {
		int d = b*(o.b/__gcd(b,o.b));
		return fraction(a*(d/b) - o.a*(d/o.b),d);
	}
	fraction operator * (const fraction & o) const {
		return fraction(a*o.a,b*o.b);
	}
	fraction operator * (const int & c){
		return fraction(a*c,b);
	}
	string toString(){
		if(a == 0 && b == 1) return "0";
		if(a == 1 && b == 1) return "1";
		return to_string(a) + "/" + to_string(b);
	}
};


fraction dp[MAX][5][5];
int vis[MAX][5][5];

fraction solve(int pos,int ci,int c0){
	if(c0 == -1) return fraction(1,1);
	if(!ci) return fraction();
	fraction & ret = dp[pos][ci][c0];
	if(vis[pos][ci][c0]) return ret;
	vis[pos][ci][c0] = 1;

	vi V = i2v[pos];
	int m = ci + c0 + 1;
	for(int c : V) m += c;
	ret = solve(pos,ci-1,c0)*fraction(ci,m)
			+ solve(pos,ci,c0-1)*fraction(c0+1,m);

	for(int i = 0;i < sz(V);) {
		int & c = V[i];
		c--;
		int npos = encode(V);
		fraction tmp = solve(npos,ci,c0);
		c++;
		int j = i,s = 0;
		while(j < sz(V) && V[i] == V[j]) s += V[j++];
		ret = ret + tmp*fraction(s,m);
		i = j;
	}
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	tc(){
		scanf("%d",&n);
		loop(i,n) {
			string s; cin >> s;
			A[i] = parse(s);
		}
		int p;
		vi ctr = play(p);
		ctr[p]--;
		if(ctr[p] == -1) {
			ctr[p]++;
			loop(i,12) printf("%d%c",ctr[i]==0," \n"[i==11]);
		}
		else {
			printf("1");
			for(int i = 1;i < 12;i++) {
				int pos = encode(ctr,i,0);
				fraction ans = fraction(1,1) - solve(pos,ctr[i],ctr[0]);
				printf(" %s",ans.toString().c_str());
			}
			puts("");
		}
	}
	return 0;
}
#endif
