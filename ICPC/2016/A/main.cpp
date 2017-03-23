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

const int MAX = 100*1000 + 10;
int f[MAX],s[MAX],m,k,n;
ll sf = 0;

ll upperInc(int i){
	return ((s[i] + 2)*sf + f[i] - 1)/f[i] - 1;
}

ll upper(int i){
	return ((s[i] + 1)*sf + f[i] - 1)/f[i] - 1;
}

ll lower(int i){
	return s[i]*sf/f[i]-1;
}

int main(){
	scanf("%d %d",&m,&k); n = k;
	loop(i,m) scanf("%d",f + i),sf += f[i];
	loop(i,k) {
		int x; scanf("%d",&x); x--;
		s[x]++;
	}
	set<pl> eatable,not_eatable;
	multiset<ll> MS;
	loop(i,m){
		if(s[i]*sf < f[i]*1LL*(n + 1) ) {
			eatable.insert(mp(upperInc(i),i));
		}
		else {
			not_eatable.insert(mp(lower(i),i));
		}
		MS.insert(upper(i));
	}
	while(!eatable.empty() && n%sf){
		int u = eatable.begin()->yy; 
		MS.erase(MS.find(upper(u)));
		if(n + 1 > *MS.begin()) break;
		s[u]++; n++;
		MS.insert(upper(u));
		//cerr << "after " << f[u]*n - sf  << " " << s[u]*sf << " " << f[u]*n + sf << endl;
		assert(s[u]*sf < f[u]*1LL*n + sf);
		assert(f[u]*1LL*n - sf < s[u]*sf);
		eatable.erase(eatable.begin());
		if(lower(u) < n) eatable.insert(mp(upperInc(u),u));
		else not_eatable.insert(mp(lower(u),u));
		while(!eatable.empty() && eatable.begin()->xx <= n) {
			u = eatable.begin()->yy;			
			not_eatable.insert(mp(lower(u),u));		
			eatable.erase(eatable.begin());
		}
		while(!not_eatable.empty() && n > not_eatable.begin()->xx){			
			u = not_eatable.begin()->yy;
			not_eatable.erase(not_eatable.begin());
			if(upperInc(u) > n) eatable.insert(mp(upperInc(u),u));
		}
	}

	if(n%sf == 0) puts("forever");
	else printf("%d\n",n - k);
	return 0;
}
