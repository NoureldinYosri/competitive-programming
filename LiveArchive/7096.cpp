#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

struct ratio{
	ll a,b;
public:
	ratio(){}
	ratio(ll a,ll b):a(a),b(b){}
	bool operator < (const ratio & r){
		return a*r.b < r.a * b;
	}
	bool operator > (const ratio & r){
		return a*r.b > r.a * b;
	}
	bool operator != (ratio & r){
		ratio t = *this;
		return (t < r) || (r < t);
	}
	bool operator == (ratio & r){
		return !(*this != r);
	}
	ratio right(){
		return ratio(a + b,b);
	}
	ratio left(){
		return ratio(a,a + b);
	}
	friend ostream& operator<<(ostream &stream, const ratio & r){
		stream << r.a << "/" << r.b;
		return stream;
	}
};


ratio one = ratio(1,1);

ratio solve(ratio r){
	if(r.b == 1) return ratio(1,r.a + 1);
	else if(r < one) return ratio(r.b,r.b - r.a);
	ll l = r.a/r.b;
	return ratio(r.b,(2*l + 1)*r.b - r.a);
}

int main(){
	int i;
	int T,K; char c[100];
	scanf("%d",&T);
	ll a,b;	
	while(T--){
		scanf("%d %lld/%lld",&K,&a,&b);
		cout << K << " " << solve(ratio(a,b)) << endl;
	}
	return 0;
}
