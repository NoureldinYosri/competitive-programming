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

const int MAX = 200*1000 + 10;
char U[MAX],V[MAX];
int m,n;
int match[MAX];
bool pal[MAX];
int base[2],mod[2];
int base_power[2][MAX];
int H[2][MAX];

vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}


ostream& operator << (ostream & st,const pi & a){
	st << "(" << a.xx << " ," << a.yy << ")";
	return st;
}

void init(){
	srand(0);
	srand(time(0));
	random_shuffle(all(cand_base));
	random_shuffle(all(cand_mod));
	loop(i,2) base[i] = cand_base[i];
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAX-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}


void doHASH(char *txt,int N,int n,int H[2][MAX]) {
	static int HASH[2][MAX];

	int h [2] = {0};
	loop(i,N) {
		char c = txt[i] - 'a' + 1;
		loop(j,2) {
			h[j] = mul(h[j],base[j],mod[j]);
			h[j] = add(h[j],c,mod[j]);
		}
		loop(j,2) HASH[j][i] = h[j];
//		cerr << i << ". " << mp(HASH[0][i],HASH[1][i]) << endl;
		if(i >= n-1) {
			int offset [2] = {0};
			if(i >= n) {
				int k = i-n;
				loop(j,2) offset[j] = HASH[j][k];
			}
			loop(j,2) offset[j] = mul(offset[j],base_power[j][n],mod[j]);
			loop(j,2) H[j][i-n+1] = add(h[j],-offset[j],mod[j]);
		}
	}
}


void step1(){
	static map<pi,int> mem;
	static char txt[MAX];
	init();

	strcpy(txt,V);
	strcpy(txt+n,V);
	reverse(txt,txt + 2*n);
	doHASH(txt,2*n,n,H);
	loop(i,n) {
		int a = H[0][i],b = H[1][i];
		pi t = mp(a,b);
		mem[t] = (n - i)%n + 1;
//		cerr << i << ". " << t << endl;
	}

	strcpy(txt,U);
	strcpy(txt+m,U);
//	memset(H,0,sizeof H);
	doHASH(txt,2*m,n,H);
	loop(i,m) {
		int a = H[0][i],b = H[1][i];
		pi t = mp(a,b);
		if(mem.find(t) != mem.end()) {
			match[i] = mem[t];
//			cerr << i << " -> " << match[i] << endl;
		}
//		else cerr << i << " -> no match" << endl;
//		cerr << i << ". " << t << endl;
	}


}


void manacher (char *S,int N,int *P) {
	for (int i = 0,r = -1,c = -1;i < N;i++) {
		int l = 0;
		if (i <= r)
			l = min(P[2*c - i],r - i);
		while (i-l-1 >= 0 && i+l+1 < N && S[i-l-1] == S[i+l+1])
			l++;
		P[i] = l;
		if(i + l > r) {
			r = i + l;
			c = i;
		}
	}
}


void addDel(char *I,int n,char *O) {
	loop(i,n) O[2*i + 1] = I[i];
	int N = 2*n + 1;
	for(int i = 0;i < N;i += 2)
		O[i] = '#';
	O[N] = 0;
}

void step2(){
	static char itxt[MAX],txt[MAX];
	static int P[4*MAX];
	if(m == n) {
		fill(pal,pal + m,1);
		return;
	}
	strcpy(itxt,U);
	strcpy(itxt+m,U);
	addDel(itxt,2*m,txt);
	int N = 4*m + 1;
	manacher(txt,N,P);
//	prArr(txt,N,char);
//	cerr << "##";
//	prArr(P,N,int);


	set<int> pivot;
	set<pi> reach;
	int len = m - n,offset = len - 1;
	for(int i = N-1;i > 0;i--) {
		reach.insert(mp(i - P[i],i));
		pivot.insert(i);
//		cerr << "insert " << mp(i-P[i],i) << endl;
		while(!reach.empty() && reach.rbegin()->xx > i) {
			int p = reach.rbegin()->yy;
			pivot.erase(p);
//			cerr << "erase " << *reach.rbegin() << endl;
			reach.erase(*reach.rbegin());
		}
		if(i & 1) {
//			cerr << i << " ... ";
//			print(pivot,int);
			int tp = i + offset;
			if(pivot.count(tp)) pal[i >> 1] = 1;
		}
	}

}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s %s",U,V);
	m = strlen(U);
	n = strlen(V);


	step1();
	step2();
	loop(i,m) if(match[i] && pal[i + n]) {
		puts("Yes");
		int a = i+1,b = match[i];

		printf("%d %d\n",a,b);
		return 0;
	}

	puts("No");
	return 0;
}
