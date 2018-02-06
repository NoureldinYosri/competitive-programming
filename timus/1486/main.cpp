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

const int MAX = 600;

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
static inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

struct HASH{
	vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
	vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};

	int base[2];
	int mod[2];
	int base_power[2][MAX];



	HASH(){}

	HASH(int mx){
		random_shuffle(all(cand_base));
		random_shuffle(all(cand_mod));
		loop(i,2) base[i] = mx + cand_base[i];
		loop(i,2) {
			mod[i] = cand_mod[i];
			base[i] %= mod[i];
		}
		loop(i,2) base_power[i][0] = 1;
		for(int i= 0;i < 2;i++)
			for(int j = 0;j < MAX-1;j++)
				base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
	}

};


ostream& operator << (ostream & st,const pi & a){
	st << "(" << a.xx << " ," << a.yy << ")";
	return st;
}


char  G[500][500 + 10];
int m,n;
vp P;
pi row[500][500];
pi rowCol[500][500];
map<pi,pi> HM;

void firstPass(const HASH & H,int K){
	for(int r = 0;r < m;r++) {
		int h [2] = {0};
		for(int c = 0;c < n;c++) {
			int v = G[r][c];
			for(int q  = 0;q < 2;q++) {
				h[q] = mul(h[q],H.base[q],H.mod[q]);
				h[q] = add(h[q],v,H.mod[q]);
			}

			if(c >= K-1) {
				row[r][c - K + 1] = mp(h[0],h[1]);
				for(int q = 0;q < 2;q++) {
					v = G[r][c - K + 1];
					v = mul(v,H.base_power[q][K-1],H.mod[q]);
					h[q] = add(h[q],-v,H.mod[q]);
				}
			}
		}
	}
//	cerr << H.base[0] << " " << H.base[1] << endl;
//	cerr << H.mod[0] << " " << H.mod[1] << endl;
//	loop(i,m) loop(j,n-K+1) cerr << row[i][j] << " \n"[j==n-K];
//	cerr << endl;
}

int upd(int x,int v,int b,int m) {
	x = mul(x,b,m);
	x = add(x,v,m);
	return x;
}
int upd2(int x,int v,int bP,int m) {
	v = mul(v,bP,m);
	x = add(x,-v,m);
	return x;
}

void secondPass(const HASH & H,int K){
	for(int c = 0;c <= n-K;c++){
		pi h(0,0);
//		cerr << "reset" << endl;
		for(int r = 0;r < m;r++) {
			h.xx = upd(h.xx,row[r][c].xx,H.base[0],H.mod[0]);
			h.yy = upd(h.yy,row[r][c].yy,H.base[1],H.mod[1]);
//			cerr << "inc " << h << endl;
			if(r >= K-1) {
				rowCol[r-K+1][c] = h;
//				cerr << h << " to ";
				h.xx = upd2(h.xx,row[r-K+1][c].xx,H.base_power[0][K-1],H.mod[0]);
				h.yy = upd2(h.yy,row[r-K+1][c].yy,H.base_power[1][K-1],H.mod[1]);
//				cerr << "to " << h << endl;
			}
		}
	}
//	loop(i,m-K+1) loop(j,n-K+1) cerr << rowCol[i][j] << " \n"[j==n-K];
}


bool valid(int K) {
	P.clear();
	HM.clear();
	if(!K) return 1;

	HASH H1(126),H2(1e9);

	firstPass(H1,K);
	secondPass(H2,K);
	loop(i,m-K+1) loop(j,n-K+1) {
		pi p = rowCol[i][j];
//		cerr << i+1 << " " << j+1 << " " << p << endl;
		if(HM.find(p) != HM.end()){
			P.pb(HM[p]);
			P.pb(mp(i,j));
			return 1;
		}
		HM[p] = mp(i,j);
	}
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	srand(time(0));
//	srand(0);

	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);

	int s = 0,e = min(m,n);
	while(s < e) {
		int m = s + (e - s + 1)/2;
		if(valid(m)) s = m;
		else e = m-1;
	}
	valid(s);
	assert(sz(P) == 0 || sz(P) == 2);
	printf("%d\n",s);
	for(auto p : P) printf("%d %d\n",p.xx+1,p.yy+1);

	return 0;
}


