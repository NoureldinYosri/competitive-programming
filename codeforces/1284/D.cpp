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

vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};
const int MAX = 200*1000 + 10;
int base[2],mod[2];
int base_power[2][MAX];

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}



void init(){
	srand((unsigned ll) new char());
	random_shuffle(all(cand_base));
	random_shuffle(all(cand_mod));
	loop(i,2) base[i] = cand_base[i];
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAX-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}

struct node{
	pi h;
	int siz;
};

const int MAXST = 1 << 19;
node ST[2][MAXST];

node merge(node l,node r){
	node ret;
	ret.siz = l.siz + r.siz;
	ret.h.first = add(l.h.first, mul(base_power[0][l.siz],r.h.first, mod[0]),mod[0]);	
	ret.h.second = add(l.h.second, mul(base_power[1][l.siz],r.h.second, mod[1]),mod[1]);	
	return ret;
}

void insert(int cur,int s,int e,int p,node *ST){
	ST[cur].siz++;
	if(s == e){
		ST[cur].h = pi(p,p);
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1,right = left + 1;
	if(p <= m) insert(left,s,m,p,ST);
	else insert(right,m + 1,e, p, ST);
	ST[cur] = merge(ST[left], ST[right]);
}
void remove(int cur,int s,int e,int p,node *ST){
	ST[cur].siz--;
	if(s == e){
		ST[cur].h = pi(0,0);
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1,right = left + 1;
	if(p <= m) remove(left,s,m,p,ST);
	else remove(right,m + 1,e, p, ST);
	ST[cur] = merge(ST[left], ST[right]);
}



pi S[MAX],T[MAX];
int n;

vector<pair<pi,pi> > events;
vector<pi> A,B;

void solve(pi *S, vector<pi> & A,node *ST){
	events.clear();
	for(int i = 1;i <= n;i++){
		events.emplace_back(pi(S[i].first, -1),pi(i,0));
		events.emplace_back(pi(S[i].second, 1),pi(i,0));
	}
	sort(all(events));
	for(int i = 0;i < sz(events);){
		int j = i;
		int t = events[j].first.second;
		while(j < sz(events) && t == events[j].first.second){
			auto e = events[j++];
//			int which = e.second.second;
			int id = e.second.first;
			int type = e.first.second;
			if(type == -1) {
//				cout << "+ " << id << " " << which << endl;
				insert(0,1,n,id,ST);
			}
			else {
//				cout << "- " << id << " " << which << endl;
				remove(0,1,n,id,ST);			
			}
		}
//		cout << "check " << endl;
		if(ST[0].siz > 1) A.push_back(ST[0].h);
		i = j;
	}
	sort(all(A));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d %d",&S[i].first,&S[i].second);
		scanf("%d %d",&T[i].first,&T[i].second);
	}
	solve(S, A, ST[0]);
	solve(T, B, ST[1]);
	puts((A==B)? "YES" : "NO");
	return 0;
}
