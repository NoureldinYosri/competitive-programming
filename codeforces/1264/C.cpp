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

const int mod = 998244353,MAX = 200*1000 + 10;
int P[MAX];
int fail[MAX],weightedFail[MAX];
int prefProd[MAX],prefFail[MAX],prefWeightedFail[MAX];
int invPrefProd[MAX];
int n;

int E[MAX];
pi* ST[1 << 20];

int mul(int a,int b){
	return (a*(ll)b)%mod;
}
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int powmod(int a,int p){
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1;p >>= 1){
		if(p&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

pi* merge(pi *a,pi *b){
	if(a&&b){
		pi *res = new pi();
		res->first = add(a->first,mul(a->second,b->first));
		res->second = mul(a->second,b->second);
		return res;
	}
	else if(a) return a;
	else return b;
}

void update(int cur,int s,int e,int p,pi *v){
	if(s == e) {
		//cout << "set " << s << " to ";
		//if(v) cout << *v << endl;
		//else cout << "NULL" << endl;
		ST[cur] = v;
		return;
	}
	int m = (s+e)>>1,left = 2*cur+1,right = left+1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[cur] = merge(ST[left],ST[right]);
}





void build(){
	int i100 = powmod(100,mod-2);
	
	int prod = 1;
	prefProd[0] = 1;
	for(int i = 1;i <= n;i++){
		int np = mul(100 - P[i],i100);
		int p = mul(P[i],i100);
		
		fail[i] = mul(prod, np);
		weightedFail[i] = mul(fail[i],i);
		
		prefFail[i] = add(fail[i], prefFail[i-1]);
		prefWeightedFail[i] = add(weightedFail[i], prefWeightedFail[i-1]);
		
		prefProd[i] = prod = mul(prod,p);
	}
	for(int i = 0;i <= n;i++)
		invPrefProd[i] = powmod(prefProd[i],mod-2);
}

void getInfo(int l,int r,int &p, int &f, int &wf){
	wf = add(prefWeightedFail[r], - prefWeightedFail[l-1]);
	f = add(prefFail[r], - prefFail[l-1]);
	p = prefProd[r];
	
	int q = invPrefProd[l-1];
	
	wf = mul(wf,q);
	f = mul(f,q);
	p = mul(p,q);
}

pi getAnswer(int l,int r){
	int p,f,wf;
	getInfo(l,r,p,f,wf);
	int k = r-l+1;
	int ans = mul(k,p);
	ans = add(ans,wf);
	ans = add(ans,-mul((l-1),f));
	
	int s = add(1, -f);
	s = powmod(s,mod-2);
	
	ans = mul(ans,s);
	s = mul(p,s);
	return pi(ans,s);	
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%d",P + i);
	build();
	/*prArr(prefProd,n+1,int);
	prArr(prefFail,n+1,int);
	prArr(prefWeightedFail,n+1,int);
	*/
	
	update(0,1,n,1,new pi(getAnswer(1,n)));
	set<int> checkpoints({1,n+1});
	
	while(m--){
		int p; scanf("%d",&p);
		auto ptr = checkpoints.lower_bound(p);
		assert(ptr != checkpoints.begin());
		assert(ptr != checkpoints.end());
		ptr--;
		int l = *ptr;
		ptr++;
		if(*ptr == p)
			ptr++;
		assert(ptr != checkpoints.end());
		int r = *ptr - 1;
		if(checkpoints.count(p)){
			update(0,1,n,p,0);
			update(0,1,n,l,0);
			update(0,1,n,l,new pi(getAnswer(l,r)));
			checkpoints.erase(p);
		}
		else {
			update(0,1,n,p,new pi(getAnswer(p,r)));
			update(0,1,n,l,new pi(getAnswer(l,p-1)));
			checkpoints.insert(p);
		}
		assert(ST[0]);
		printf("%d\n",ST[0]->first);
	}
	
	return 0;
}
