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

const double PI = acos(-1);
const int MAX = 100;
pl P[MAX];
vi G[MAX];
int cnt[MAX*MAX],N;
ll X[MAX],Y[MAX];
ll R;
vi aux;
int xxx[MAX];

void preprocess(){
	memset(cnt,0,sizeof cnt);
	memset(xxx,0,sizeof xxx);

	loop(i,N) G[i].clear();
	loop(i,N) X[i] = P[i].xx,Y[i] = P[i].yy;
	int m,n,l = 0;
	sort(X,X + N); m = unique(X,X + N) - X;
	sort(Y,Y + N); n = unique(Y,Y + N) - Y;

	loop(i,m) loop(j,n) {
		int x = X[i],y = Y[j];
		loop(k,N) 
			if(P[k].xx >= x && P[k].yy >= y && P[k].xx - x <= R && P[k].yy - y <= R){
				cnt[l]++;
				G[k].pb(l);
			}
		xxx[cnt[l]]++;
		l++;
	}
}

int work(vi & aux){
	sort(all(aux),[](const int & a,const int & b){
		return P[a].yy < P[b].yy;
	});
	vi X;
	for(int k : aux) X.pb(P[k].xx);
	sort(all(X)); X.resize(unique(all(X)) - X.begin());
	int ret = 0;	
	for(int x : X){
		vi tmp; deque<int> dq;
		for(int k : aux) if(P[k].xx >= x && P[k].xx - x <= R) tmp.pb(P[k].yy);
		for(int y : tmp){
			while(!dq.empty() && y - dq.front() > R) dq.pop_front();
			dq.pb(y);
			ret = max(ret,sz(dq));
		}
	}
	return ret;
}

void work(int & ans){

	for(int k : aux){
		for(int p : G[k]) {
			xxx[cnt[p]]--;
			cnt[p]--;
			xxx[cnt[p]]++;
		}
	}
	
	int x = N,y = work(aux);
	for(;x && !xxx[x];x--);
	ans = max(ans,x + y);
	for(int k : aux){
		for(int p : G[k]) {
			xxx[cnt[p]]--;
			cnt[p]++;
			xxx[cnt[p]]++;
		}
	}
}
int solve(){
	int ans = 0;
	preprocess();
	loop(i,N) loop(j,i) {
		aux.clear();
		ll dist = (P[i].xx-P[j].xx)*(P[i].xx-P[j].xx) + (P[i].yy-P[j].yy)*(P[i].yy-P[j].yy);
		if(P[i] == P[j] || dist > 2*R) aux.pb(i);
		else{
			double ox = (P[i].xx + P[j].xx)/2.0;
			double oy = (P[i].yy + P[j].yy)/2.0;
			complex<double> I(ox,oy); 
			complex<double> r(P[i].xx - P[j].xx,P[i].yy - P[j].yy); 
			r /= abs(r);
			r *= polar(1.0,PI/2.0);
			double d = abs(I - complex<double>(P[i].xx,P[i].yy)); sqrt(R*R - d*d);
			r *= d;
			complex<double> O = I + r;
			loop(k,N){
				complex<double> pos(P[k].xx,P[k].yy); pos -= O;
				if(abs(pos) < R || abs(abs(pos) - R) < 1e-9) aux.pb(k);
			}
			assert(sz(aux));		
			work(ans);
			aux.clear();
			r *= polar(1.0,PI);
			O = I + r;
			loop(k,N){
				complex<double> pos(P[k].xx,P[k].yy); pos -= O;
				if(abs(pos) < R || abs(abs(pos) - R) < 1e-9) aux.pb(k);
			}								
			assert(sz(aux));		
		}
		work(ans);
	}
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %lld",&N,&R);
		loop(i,N) scanf("%lld %lld",&P[i].xx,&P[i].yy);
		int ans = solve();
		printf("Case #%d: %d\n",t,ans);
//		break;
	}
	
	
	return 0;
}
