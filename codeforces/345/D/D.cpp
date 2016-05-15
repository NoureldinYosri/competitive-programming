#include <bits/stdc++.h>
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

int n,a,b,T;
char line[1 << 20];
ll cost[1 << 21];

ll f(ll left,ll right){
	//cerr << left << " " << right << " " ;
	ll tmp = left*a + right*a + left*a*(right > 0);
	right += n;
	left = n - left;
	ll ret = cost[right] - cost[left - 1] + right - left + 1 + tmp;
	//cerr << cost[right] - cost[left - 1] << " " << right - left + 1 << " " << tmp << " " << ret << endl;
	return ret;
}

ll g(ll left,ll right){
	ll tmp = left*a + right*a + right*a*(left > 0);
	right += n;
	left = n - left;
	ll ret = cost[right] - cost[left - 1] + right - left + 1 + tmp;
	return ret;
}

int main(){
	scanf("%d %d %d %d",&n,&a,&b,&T);
	scanf("%s",line);
	loop(i,n) cost[i] = (line[i] == 'w')*b;
	copy(cost,cost + n,cost + n);
	loop(i,2*n - 1) cost[i + 1] += cost[i];
	int ans = 0;
	loop(left,n){
		int s = 0,e = n - 1;
		while(s < e){
			int m = s + (e - s + 1)/2;
			if(f(left,m) <= T) s = m;
			else e = m - 1;
		}
		if(f(left,s) <= T) ans = max(ans,min(n,s + left + 1));
	}
	loop(right,n){
		int s = 0,e = n - 1;
		while(s < e){
			int m = s + (e - s + 1)/2;
			if(g(m,right) <= T) s = m;
			else e = m - 1;
		}
		if(g(s,right) <= T) ans = max(ans,min(n,s + right + 1));
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
