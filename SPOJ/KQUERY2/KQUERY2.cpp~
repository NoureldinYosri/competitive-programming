#include <cstdio>
#include <cmath>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n,A[30010],bucket_size;
int bucket[200][20001];

inline void update(int p,int v,int *T){
	for(;p <= 10000;p += LSOne(p)) T[p] += v;
}

inline int get(int p,int *T){
	int ans = 0;
	for(;p;p -= LSOne(p)) ans += T[p];
	return ans;
}

#define gc getchar_unlocked
inline void scan(int & x){
	x = 0;
	char c;
	while((c = gc()) && (c < '0' || '9' < c));
	x = c - '0';
	while((c = gc()) && ('0' <= c && c <= '9')) x = (x << 3) + (x << 1) + c - '0';
}

int main(){
	int ctr = 0,j = 0;
	scan(n);
	bucket_size = sqrt(n) + 3;
	bucket_size = (bucket_size < n) ? bucket_size : n;
	loop(i,n) {
		scan(A[i]);
		if(ctr == bucket_size) j++,ctr = 0;
		update(A[i],1,bucket[j]);
		++ctr;
	}
	int Q;
	scan(Q);
	while(Q--){
		int f,a,b,k;
		scan(f); scan(a); scan(b);
		if(f){
			scan(k); --a,--b;
			int u = a/bucket_size,v = b/bucket_size,ans = 0;
			if(u == v) {
				for(;a <= b;a++) ans += A[a] > k;
			}
			else{
				for(;a < (u + 1)*bucket_size;a++) ans += A[a] > k;
				for(;b >= v * bucket_size;b--) ans += A[b] > k;
				for(++u;u < v;u++) 
					ans += get(10000,bucket[u]) - get(k,bucket[u]);
			}
			printf("%d\n",ans);
		}
		else{
			a--;
			int u = a/bucket_size;
			update(A[a],-1,bucket[u]);
			update(b,1,bucket[u]);
			A[a] = b;
		}
	} 
	return 0;
}
