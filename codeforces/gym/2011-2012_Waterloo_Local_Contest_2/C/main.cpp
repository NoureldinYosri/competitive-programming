#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

ll V[1 << 20];
int n;

inline pl normalize(ll a,ll b){
	ll d = __gcd(a,b);
	a /= d;
	b /= d;
	if(b < 0) a = -a;
	return mp(a,b);
}

bool cmp(const ll &a,const ll &b){
	return abs(a) < abs(b);
}

pl get_positive(){
	sort(V,V + n,&cmp);
	pl r = normalize(V[1],V[0]);
	prp(r); cerr << endl;
	range(i,1,n - 2){
		pl tmp = normalize(V[i + 1],V[i]);
		prp(tmp); cerr << endl;
		if(tmp != r) return mp(0,1);
	}
	return r;
}

pl get_negative(){
	sort(V,V + n,&cmp);
	loop(i,n - 1){
		int s1 = (V[i] > 0) - (V[i] < 0);
		int s2 = (V[i + 1] > 0) - (V[i + 1] < 0);
		if(s1 == s2) return mp(0,1);		
	}
	pl r = normalize(V[1],V[0]);
	range(i,1,n - 2){
		pl tmp = normalize(V[i + 1],V[i]);
		if(tmp != r) return mp(0,1);
	}
	return r;
}

int main(){
	int pos = 0,neg = 0,zero = 0;	
	cin >> n;
	loop(i,n) {
		cin >> V[i];
		if(V[i] > 0) pos++;
		else if(V[i] < 0) neg++;
		else zero++;
	}
	if(zero) cout << (zero == n) << endl;
	else{
		pl ans;
		if(pos == n || neg == n) ans = get_positive() ;
		else ans = get_negative();
		printf("%.10lf\n",ans.xx*1.0/ans.yy);
	}
	return 0;
}
