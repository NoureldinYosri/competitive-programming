#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

map<int,int> Front,OnlyFront,Back,OnlyBack;
int n,m,a,b,ans = INT_MAX;

int main(){
	scanf("%d",&n); m = (n >> 1) + (n & 1);
	loop(i,n){
		scanf("%d %d",&a,&b);
		Front[a]++;
		Back[b]++;
		if(a != b) OnlyFront[a]++,OnlyBack[b]++;
	}
	for(auto c : Front){
		int q = max(m - c.yy,0);
		if(q == 0) ans = 0;
		if(OnlyBack.find(c.xx) != OnlyBack.end()) {
			if(q <= OnlyBack[c.xx]) {
			//	cerr << "1 -> " << c.xx << " " << q << endl;			
				ans = min(ans,q);
			}
		}
	}
	for(auto c : Back){
		if(c.yy >= m) ans = min(ans,m);
		if(OnlyFront.find(c.xx) != OnlyFront.end()) {
			if(OnlyFront[c.xx] + c.yy >= m) {
				ans = min(ans,max(m - OnlyFront[c.xx],0));
			}
		}
	}
	ans = (ans == INT_MAX) ? -1 : ans;
	cout << ans << endl;
	return 0;
}
