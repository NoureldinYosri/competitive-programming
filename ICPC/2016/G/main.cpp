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

const int MAX = 4000;
int X[MAX],Y[MAX],len[MAX],aux[MAX],n,m;

ll ccw(int o,int a,int b){
	ll x1 = X[a] - X[o],y1 = Y[a] - Y[o];
	ll x2 = X[b] - X[o],y2 = Y[b] - Y[o];
	if(Y[a] < Y[o]) x1 = -x1,y1 = -y1;
	if(Y[b] < Y[o]) x2 = -x2,y2 = -y2;
	return x1*y2 - x2*y1;
}

int main(){
	scanf("%d",&n);
	ll ans = 0;
	loop(i,n) {
		scanf("%d %d %d",&X[2*i],&X[2*i + 1],&Y[2*i]);
		Y[2*i + 1] = Y[2*i];
		if(X[2*i] > X[2*i + 1]) swap(X[2*i],X[2*i + 1]);
		len[2*i] = len[2*i + 1] = X[2*i + 1] - X[2*i];
		ans = max(ans,len[2*i] + 0LL);
	}
	loop(i,2*n){
		m = 0;
		loop(j,2*n) if(Y[j] != Y[i]) aux[m++] = j;
		sort(aux,aux + m,[i](const int & a,const int & b){	
			ll v = ccw(i,a,b);
			if(v) return v < 0;
			int x = !((Y[a] < Y[i]) ^ (a & 1));
			int y = !((Y[b] < Y[i]) ^ (b & 1));
			return x > y;	
		});

		
		ll sum = X[i | 1] - X[i & ~1];
		
		loop(j,m){
			int t = aux[j];
			int x = !((Y[t] < Y[i]) ^ (t & 1));
			if(x) {
				sum += len[t];
				ans = max(ans,sum);
			}
			if(!x) sum -= X[t | 1] - X[t & ~1];
		}

	}
	cout << ans << endl;
	cerr << ans << endl;
	
	return 0;
}
