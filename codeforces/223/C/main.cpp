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

const int mod = 1e9 + 7,MAX = 2 << 10,MAXK = MAX << 1;
int A[MAX],inv[MAXK];
int n,K;


int mul(int a,int b){
	return (a * 1LL * b)%mod;
}
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int powmod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int C(int n,int k){
	if(k > n) return 0;
	if(k < 0) return 0;
	k = min(k,n - k);
	int ret = 1;
	for(int i = 0;i < k;i++){
		ret = mul(ret,n - i);
		ret = mul(ret,inv[i+1]);
	}
	return ret;
}

int f(int n,int k){
	return C(n + k - 1,n-1);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	loop(i,MAXK) inv[i] = powmod(i,mod - 2);
	scanf("%d %d",&n,&K);
	deque<int> dq;
	loop(i,n) {
		scanf("%d",A + i);
		dq.push_front(f(K,i));
		dq.back() = 1;
		int s = 0;
		for(int j = 0;j <= i;j++)
			s = add(s,mul(A[j],dq[j]));
		printf("%d%c",s," \n"[i==n-1]);
	}
//	print(dq,int);
	return 0;
}
