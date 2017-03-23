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

const int MAX = 200'010;
int S[MAX],n;
int mn[MAX];

int main(){
	freopen("positive.in","r",stdin);
	freopen("positive.out","w",stdout);
	scanf("%d",&n);
	range(i,1,n){
		scanf("%d",S + i);
		S[i] += S[i - 1];
	}
	mn[n + 1] = 1 << 29;
	for(int i = n;i ;i--)
		mn[i] = min(S[i],mn[i + 1]);
	int mn = 1 << 29,ans = 0;
	range(j,1,n){
		ans += ::mn[j] - S[j - 1] > 0 && mn + S[n] - S[j - 1] > 0;
		mn = min(mn,S[j]);
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
