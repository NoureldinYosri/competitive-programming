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

const int MAX = 25010;
int orig[128],lst[128],n,T,ord[MAX];
char q[MAX];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %s",&n,q);
		loop(i,n) lst[q[i]] = i;
		memset(orig,0,sizeof orig);
		int ans = 0;		
		loop(i,n) orig[q[i]] += lst[q[i]] - i,ans += lst[q[i]] - i;
		loop(i,n) ord[i] = i;
		sort(ord,ord + n,[](const int & a,const int &b){
			return tie(lst[q[a]],a) < tie(lst[q[b]],b);
		});
	//	cerr << ans << endl;
		loop(i,n){
			int j = ord[i];
			lst[q[j]] = i;
		//	cerr << q[j];
		}
//		cerr << endl;
		loop(i,n){
			int j = ord[i];
			ans -= lst[q[j]] - i;
		}
		ans *= 5;
		cerr << ans << endl;
		printf("%d\n",ans);
	}
	
	
	return 0;
}
