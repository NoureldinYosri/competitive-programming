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

int A[1 << 20],n,m,a,b;
ll offset[1 << 20];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);	
	while(m--){
		scanf("%d %d",&a,&b);
		a--,b--;
		offset[a]++;
		offset[b + 1]--;
	}
	loop(i,n) offset[i + 1] += offset[i];
	sort(offset,offset + n);
	ll ans = 0;
	loop(i,n) ans += offset[i] * A[i];
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
