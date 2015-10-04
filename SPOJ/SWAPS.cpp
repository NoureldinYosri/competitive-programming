#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int BIT[600][50001],m = 0,u,N;
int A[500 * 600];

inline int get(int p,int k){
	int ans = 0;
	while(p){
		ans += BIT[k][p];
		p -= p & (-p);
	}
	return ans;
}

inline void update(int p,int v,int k){
	while(p <= 50000){
		BIT[k][p] += v;
		p += p & (-p);
	}
}


#define gc getchar_unlocked
inline void scan(int & x){
	x = 0;
	char c;
	while((c = gc()) && !('0' <= c && c <= '9'));
	x = c - '0';
	while((c = gc()) && ('0' <= c && c <= '9')) x = (x << 1) + (x << 3) + c - '0'; 
}

int main(){
	int M,a,b;
	scan(N);
	assert(N > 0);
	u = sqrt(N) + 2;
	while(u*u > N) u--;
	loop(i,N){
		scan(A[i]);
		m = i/u + 1;
	}
	ll ans = 0;
	for(int i = 0;i < N;i++){	
		ans += i - get(A[i],509);
		update(A[i],1,509);
		update(A[i],1,i/u);		
	}
	//cerr << "origianl " << ans << endl;
	scanf("%d",&M);
	while(M--){
		scan(a); a--;
		scan(b);
		int buc = a/u; ll tmp = 0;
		for(int k = 0;k < buc;k++) tmp += get(A[a],k) - get(b,k);
		//cerr << tmp << endl;
		for(int k = buc + 1;k < m;k++) tmp += get(b - 1,k) - get(A[a] - 1,k);
		//cerr << tmp << endl;
		for(int i = buc*u,L = min(N,buc*u + u);i < L;i++){
			if(i < a) tmp += (A[i] > b) - (A[i] > A[a]);
			if(i > a) tmp += (A[i] < b) - (A[i] < A[a]);
		}
		//cerr << tmp << endl;
		ans += tmp;
		update(A[a],-1,buc);
		update(b,1,buc);
		A[a] = b;
		printf("%lld\n",ans);
	}
	return 0;
}
