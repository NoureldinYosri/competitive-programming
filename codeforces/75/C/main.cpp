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


vi factor(int x){
	vi ret ;
	for(int i = 1;i*i <= x;i++)
		if(x%i == 0){
			ret.pb(i);
			if(i*i != x) ret.pb(x/i);
		} 
	sort(all(ret));
	return ret;
}

int main(){
	int a,b; scanf("%d %d",&a,&b);
	int d = __gcd(a,b);
	vi DIV = factor(d);	
	int n; scanf("%d",&n);
	loop(i,n){
		int l,r; scanf("%d %d",&l,&r);
		auto p = upper_bound(all(DIV),r);
		if(p == DIV.begin()) puts("-1");
		else{
			p--;
			if(*p < l) puts("-1");
			else printf("%d\n",*p);
		} 
	}	
	
	return 0;
}
