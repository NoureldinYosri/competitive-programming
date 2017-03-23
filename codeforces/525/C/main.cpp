#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
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

int cnt[1 << 20],n;

int main(){
	scanf("%d",&n);
	loop(i,n) {
		int x; scanf("%d",&x);
		cnt[x]++;
	}
	vi L;
	ll ans = 0;
	int l = 0;
	for(int i = 1000*1000;i > 1;i--){
		if(l==i+1 && cnt[i]){
			L.pb(i);
			cnt[i]--;
		}		
		l = 0;
		while(cnt[i] >= 2){
			L.pb(i);
			cnt[i] -= 2;
		}
		if(cnt[i]) l = i;
	}
	for(int i = 0;i < sz(L) - 1;i += 2) ans += L[i]*1LL*L[i + 1];
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
