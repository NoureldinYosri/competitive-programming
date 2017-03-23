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

const int mod = 1e9 + 7;

int cnt[1 << 20];
int p2[1 << 20 | 1];
int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;	
	return x;
}

int main(){
	int n,a; scanf("%d",&n);
	loop(i,n){
		scanf("%d",&a);
		cnt[a]++;
	}
	loop(b,20){
		loop(i,1<<20){
			if(i & (1 << b)) 
				cnt[i ^ (1 << b)] = add(cnt[i ^ (1<<b)],cnt[i]);
		}
	}
	int ans = 0;
	p2[0] = 1;
	loop(i,(1 << 20)) p2[i + 1] = add(p2[i],p2[i]);
	loop(i,1<<20){
		ans = add(ans,(1 - 2*(popcnt(i)&1))*(p2[cnt[i]]-1));
	}
	cout << ans << endl;
	return 0;
}
