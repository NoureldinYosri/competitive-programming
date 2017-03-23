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

const int MAX = 2e5 + 1e2;

int A[MAX],n;
ll S[MAX];
deque<pl> CH;

ll f(int idx,int x){
	return CH[idx].xx * x + CH[idx].yy;
}

bool cond(pl a,pl b,pl c){
	b.xx -= a.xx,b.yy -= a.yy;
	c.xx -= a.xx,c.yy -= a.yy;
	assert(b.xx > 0 && c.xx > 0);
	//return c.yy/(0.0-c.xx) <= b.yy/(0.0 - b.xx);
	return c.yy * b.xx >= b.yy * c.xx;
}

void add(ll a,ll b,int type){
	pl line = mp(a,b);
	if(type){
		int siz = CH.size();
		while(siz > 1 && cond(CH[siz - 2],CH[siz - 1],line)) CH.pop_back(),siz--;
		CH.pb(line);
	}
	else{
		while(sz(CH) > 1 && cond(line,CH[0],CH[1])) CH.pop_front();
		CH.push_front(line);	
	}
}

ll get(int x){
	int s = 0,e = CH.size() - 1;
	while(e - s > 1){
		int m1 = s + (e - s + 1)/3,m2 = m1 + (e - s + 1)/3;
		if(f(m1,x) < f(m2,x)) s = m1 + 1;
		else e = m2 - 1;
	}
	return max(f(s,x),f(e,x));
}

int main(){
	ll tot = 0;
	scanf("%d",&n);
	range(i,1,n){
		scanf("%d",A + i);
		tot += A[i] * (i + 0LL);
		S[i] = A[i] + S[i - 1];
	}

	ll ans = tot;
	range(r,1,n){
		if(r != 1){
			ll g = get(A[r]) + tot - A[r] *1LL* r + S[r - 1];
			ans = max(ans,g) ;
		}
		add(r,-S[r - 1],1);		
	}
	CH.clear();
	for(int l = n;l;l--){
		if(l != n){
			ll g = get(A[l]) + tot - l*1LL*A[l] + S[l];
			ans = max(ans,g );
		}
		add(l,-S[l],0);
	}
	cout << ans << endl;
	return 0;
}
