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
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

typedef pair<pi,pi> seg;
seg P[1 << 20];
int n,bucket_size;
vector<pair<int,pi> > H,V;
vector<pi> bucket;

void compress(vector<pair<int,pi> > & H){
	int e = 0;
	loop(i,sz(H)){
		int j = i,endpoint = H[i].yy.yy;
		while(j < sz(H) && H[i].xx == H[j].xx && H[j].yy.xx <= endpoint){
			endpoint = max(endpoint,H[j].yy.yy);
			j++;
		}
		H[e++] = mp(H[i].xx,mp(H[i].yy.xx,endpoint));
	}
	H.resize(e);
}

ostream & operator << (ostream & stream, const pair<int,pi>  sege){
	stream << "(" << sege.xx << " ,(" << sege.yy.xx <<"," << sege.yy.yy << "))";
	return stream;
}	

bool cmp(const pair<int,pi> & p,const int x){
	return p.xx < x;
}

int f(int s,int e,int x){
	if(e < s) return 0;
	int ans = 0;
	loop(i,e - s + 1) ans += V[i].yy.xx <= x && x <= V[i].yy.yy;
	return ans; 
}

int main(){
	ll ans = 0;  
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %d %d %d",&P[i].first.xx,&P[i].first.yy,&P[i].second.xx,&P[i].second.yy);
		if(P[i].first.xx == P[i].second.xx) {
			int a = P[i].first.yy,b = P[i].second.yy;
			if(b < a) swap(a,b);
			H.pb(mp(P[i].first.xx,mp(a,b)));
		}
		else {
			int a = P[i].first.xx,b = P[i].second.xx;
			if(b < a) swap(a,b);
			V.pb(mp(P[i].first.yy,mp(a,b)));
		}
	}
	sort(all(H));
	sort(all(V));
	compress(H);
	compress(V);
	loop(i,sz(V)) ans += V[i].yy.yy - V[i].yy.xx + 1;
	loop(i,sz(H)) ans += H[i].yy.yy - H[i].yy.xx + 1;
	priority_queue<int,vi,greater<int> > pq;
	int j = 0;	
	loop(i,sz(V)){
		int x = V[i].xx;
		while(j < sz(H) && H[j].yy.xx <= x) pq.push(H[j++].yy.yy);
		while(!pq.empty() && pq.top() < x) pq.pop();
		ans -= pq.size();
	}
	cout << ans << endl;
	return 0;
}
