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

const int MAXN = 5000000 + 10;
const int base[2] = {67, 71};
const int mod[2] = {1000000007,1000000009};

char txt[MAXN];
int pref[2][MAXN],suff[2][MAXN];
int Power[2][MAXN];
int n;

int add(int a,int b,int m) {
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}
int mul(int a,int b,int m) {
	return (a*(ll)b)%m;
}

int char2code(char c) {
	if(isdigit(c)) return c - '0';
	if(islower(c)) return c - 'a' + 10;
	return c - 'A' + 36;
}

void init(){
	loop(h,2) Power[h][0] = 1;
	loop(h,2) {
		for(int i = 1;i < MAXN;i++)
			Power[h][i] = mul(Power[h][i-1],base[h],mod[h]);
	}

	int aux[2] = {0,0};
	for(int i = 0;i < n;i++) {
		for(int h = 0;h < 2;h++){
			aux[h] = add(mul(aux[h],base[h],mod[h]),char2code(txt[i]),mod[h]);
			pref[h][i] = aux[h];
		}
	}
	aux[0] = aux[1] = 0;
	for(int i = n-1;i >= 0;i--) {
		for(int h = 0;h < 2;h++){
			aux[h] = add(mul(aux[h],base[h],mod[h]),char2code(txt[i]),mod[h]);
			suff[h][i] = aux[h];
		}
	}
}

int ord[MAXN];

void getPref(int i,int *H) {
	loop(h,2) H[h] = pref[h][i];
}

void getSuff(int s,int e,int *H){
	loop(h,2) H[h] = suff[h][s];
	int l = e-s+1;
	loop(h,2) {
		int x = suff[h][e+1];
		x = mul(x,Power[h][l],mod[h]);
		H[h] = add(H[h],-x,mod[h]);
	}
}

bool isPal(int n){
	if(n == 1) return 1;
	int len = n/2;
	int L[2],R[2];
	getPref(len-1,L);
	getSuff(n-len,n-1,R);
	loop(h,2) if(L[h] != R[h]) return 0;
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%s",txt);
	n = strlen(txt);
	init();
	for(int i = 0;i < n;i++){
		int k = 0;
		int len = (i+1)/2;
		int j = len-1;
		if(j >= 0) k = ord[j];
		ord[i] = (1+k)*isPal(i+1);
	}
	ll ans = 0;
	for_each(ord,ord + n,[&ans](const int & a) {ans += a;});
//	prArr(ord,n,int);
	cout << ans << endl;
	return 0;
}
