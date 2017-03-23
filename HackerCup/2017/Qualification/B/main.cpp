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

deque<int> dq;
int n;

int main(){
	int T; scanf("%d",&T);
	loop(t,T){
		scanf("%d",&n); dq = deque<int>(n);
		loop(i,n) scanf("%d",&dq[i]);
		sort(all(dq));
		int ans = 0;
		while(!dq.empty()){
			int s = dq.back(); dq.pop_back();
			int k = max(0,(50 + s - 1)/s - 1);
			if(sz(dq) < k) break;
			while(k--) dq.pop_front();
			ans++;
		}
		printf("Case #%d: %d\n",t+1,ans);
	}
	
	
	return 0;
}
