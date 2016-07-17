#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int M,N,T;
char G[1 << 10][1 << 10];
ll mod[3] = {2147483647,1000000007,982451653};
ll base[3];
ll POW[3][1 << 10];
ll HASH[1 << 10][1 << 10][3];
ll HP[1 << 10][3];
vector<pair<int,pi> > V;
	

void init(){
	loop(i,3) POW[0][i] = 1;
	loop(i,3) base[i] = 2 + rand()%5000;
	loop(i,3) loop(j,(1 << 20) - 1) POW[i][j + 1] = (POW[i][j] * base[i])%mod[i];
}

#define mul(a,b,c) ((((a%c)*(b%c))%c + c)%c)
#define add(a,b,c) ((((a%c)+(b%c))%c + c)%c)



void preprocess(){
	V.clear();	
	for(int i = 1;i*i <= M;i++){
		if(M%i) continue;
		for(int j = 1;j*j <= N;j++){
			if(N%j) continue;
			V.pb(mp(i*j,mp(i,j)));
			V.pb(mp(i*(N/j),mp(i,N/j)));
			V.pb(mp((M/i)*j,mp(M/i,j)));
			V.pb(mp((M/i)*(N/j),mp(M/i,N/j)));
		}
	}
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());

	ll h[3];
	loop(i,M){
		loop(j,3) h[j] = 0;
		loop(j,N){
			loop(k,3) h[k] = add(mul(h[k],base[k],mod[k]),G[i][j],mod[k]);
			loop(k,3) HASH[i][j][k] = h[k];
		}
	}
}


bool verify(int m,int n){
	for(int i = 0;i < M;i += m) for(int j = 0;j < N;j += n){
		loop(k,m){
			loop(q,3){
				ll tmp = HASH[i + k][j + n - 1][q];
				if(j)tmp = add(tmp,-mul(HASH[i + k][j - 1][q],POW[q][n],mod[q]),mod[q]);
				if(tmp != HP[k][q]) return 0;
			}
		}
	}
	return 1;
}

int solve(){
	for(auto p : V){
		int m = p.yy.xx,n = p.yy.yy;
		loop(i,m) loop(k,3) HP[i][k] = HASH[i][n - 1][k];
		if(verify(m,n)) return p.xx;
	}			
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d\n",&M,&N);
		loop(i,M) fgets(G[i],1 << 10,stdin);
		preprocess();
		printf("%d\n",solve());
	}
	return 0;
}
