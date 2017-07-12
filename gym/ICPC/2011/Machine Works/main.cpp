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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 100*1000 + 10;
struct machine{
	int day,buying_price,selling_price,revenue,idx;
	ll a,b;
public:
	bool operator < (const machine & o){
		return this->day < o.day;
	}
	void to_line(ll dp){
		this->a = this->revenue;
		this->b = dp + this->selling_price - (1 + this->day)*1LL*this->revenue;
	}
	friend ostream& operator << (ostream & st,const machine & m){
		st << "(" << m.a << " ," << m.b <<  ")" ;
		return st;
	}
};

int N,C,D;
machine M[MAX];
ll dp[MAX];
int ST[MAX << 2];
int inv[MAX];
int prv[MAX];

void build(int node,int s,int e){
	ST[node] = 0;
	if(s == e) return ;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}

void update(int node,int s,int e,int p,int v){
	ST[node] += v;
	if(s == e) return ;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
}

int get(int node,int s,int e,int k){
	if(s == e) return inv[s];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(ST[left] < k) return get(right,m+1,e,k - ST[left]);
	else return get(left,s,m,k);
}

int get_count(int node,int s,int e,int p){
	if(s == e) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return get_count(left,s,m,p);
	else return ST[left] + get_count(right,m+1,e,p);
}

ll f(int idx,ll day){
	return M[idx].a * day + M[idx].b;
}

void rename(){
	sort(M,M + N + 1,[](const machine & a,const machine & b){
		return a.revenue < b.revenue;
	});
	for(int i = 0;i <= N;i++) M[i].idx = i;
	sort(M,M + N + 1);
	for(int i = 0;i <= N;i++) inv[M[i].idx] = i;
}

double g(machine & m1,machine & m2){
	double a1 = m1.a,b1 = m1.b;
	double a2 = m2.a,b2 = m2.b;
	// a1*x + b1 < a2 *x + b2
	// b1 - b2 < (a2 - a1)/x
	// (b1 - b2)/(a2 - a1) < x
	assert(m1.a <= m2.a);
	if(m1.a == m2.a){
		if(m1.b < m2.b) return -(1LL << 62);
		else return (1LL << 62);
	}
	else return (b1 - b2)/(a2 - a1);
}

bool delete_line(int pp,int p,int i){
	//cerr << "comparing " << M[pp] << " " << M[p] << " " << M[i] << " : ";
	//cerr << g(M[pp],M[p]) << " " << g(M[p],M[i]) << endl;
	return g(M[pp],M[p]) >= g(M[p],M[i]);
}

ll solve(){
	//dp[j] = max dp[i] + (D[j] - D[i])*rev[i] + selling[i];
	// dp[i] + D[j]*rev[i] + selling[i] - D[i]*rev[i];
	// a = rev[i] .. b = dp[i] + selling[i] - D[i]*rev[i];
	build(1,0,N);
	rename();
	update(1,0,N,M[0].idx,1);
	int siz = 1;
	M[0].to_line(dp[0] = C);
	//cerr << "insert line " << M[0] << " " << M[0].idx << endl;
	for(int i = 1;i <= N;){
		int j = i;
		while(i <= N && M[i].day == M[j].day){
			int s = 1,e = siz;
			while(e - s > 1){
				int m1 = s + (e - s + 1)/3,m2 = m1 + (e - s + 1)/3;
				if(f(get(1,0,N,m1),M[i].day) < f(get(1,0,N,m2),M[i].day)) s = m1 + 1;
				else e = m2 - 1;
			}
			ll a = f(get(1,0,N,s),M[i].day), b = f(get(1,0,N,e),M[i].day) ;
			if(a > b) prv[i] = get(1,0,N,s);
			else prv[i] = get(1,0,N,e);
			dp[i] = max(a,b) - M[i].buying_price;
			if(dp[i] < 0) dp[i] = -(1LL << 60);
			i ++;
		}
		swap(i,j);
		for(;i < j;i++){
			M[i].to_line(dp[i]);
		//	cerr << "inserting line " << M[i] << " " << dp[i] << " " << M[i].day << endl;
			int cur = get_count(1,0,N,M[i].idx);
			++siz;
			update(1,0,N,M[i].idx,1);
			while(cur > 1){
				int pp = get(1,0,N,cur - 1);
				int p = get(1,0,N,cur);
				if(delete_line(pp,p,i)) {
		//			cerr << "erase line p:" << M[p] << endl;
					update(1,0,N,M[p].idx,-1);
					--cur;
					--siz;
				}
				else break;
			}
			if(cur && siz - cur > 1 && delete_line(get(1,0,N,cur),i,get(1,0,N,cur+2))){
				siz--;
		//		cerr << "erase line " << M[i] << endl;
				update(1,0,N,M[i].idx,-1);
				continue;
			}
			cur++;
			while(siz - cur > 1){
				int n = get(1,0,N,cur + 1);
				int nn = get(1,0,N,cur + 2);
				if(delete_line(i,n,nn)){
		//			cerr << "erase line n:" << M[n] << endl;
					update(1,0,N,M[n].idx,-1);
					--siz;
				}
				else break;
			}
		}
	}
	/*
	int cur = N;
	vi idx;
	prv[0] = -1;
	while(cur != -1){
		idx.pb(cur);
		cur = prv[cur];
	}
	reverse(all(idx));
	for(int x : idx) {
		cerr << M[x] << " dp = " << dp[x] << " ";
		cerr << "day = " << M[x].day << " ,selling price = " << M[x].selling_price
				<< " buying price = " << M[x].buying_price << " revenue = " << M[x].revenue << endl;
	}
*/
	return dp[N];
}

int main(){
	#ifndef ONLINE_JUDGE
//		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d %d %d",&N,&C,&D) == 3 && !(N == 0 && C == 0 && D == 0);t++){
		M[0] = machine({0,0,0,0,0});
		range(i,1,N) {
			int D,P,R,G;
			scanf("%d %d %d %d",&D,&P,&R,&G);
			M[i] = machine({D,P,R,G,0});
		}

		M[++N] = machine({D+1,0,0,0,0});
		printf("Case %d: %lld\n",t,solve());
	}
	return 0;
}
