#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


const int MAX = 1 << 20;
int id[MAX],W[MAX],mn[MAX],mx[MAX];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

bool join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	id[b] = a;
	W[a] += W[b];
	mn[a] = min(mn[a],mn[b]);
	mx[a] = max(mx[a],mx[b]);
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int n,m; scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i++){
		id[i] = i;
		W[i] = 1;
		mn[i] = mx[i] = i;
	}
	loop(e,m){
		int a,b; scanf("%d %d",&a,&b);
		join(a,b);
	}
	
	vi V;
	for(int i = 1;i <= n;i++) if(find(i) == i) V.push_back(i);
	sort(all(V),[](const int & a,const int & b){
		return mx[a] < mx[b];
	});
	int ans = 0;
	while(!V.empty()){
		int i = V.back(); V.pop_back();
		if(find(i) != i) continue;
		int s = mn[i],e = mx[i];
		int t = e-1;
		while(t > s){
			ans += join(t,i);
			s = mn[find(i)];
			t--;
		}
	}
	cout << ans << endl;
	return 0;
}
