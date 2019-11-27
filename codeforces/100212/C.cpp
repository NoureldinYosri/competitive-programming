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

const ll oo = 1LL << 60;
const int MAX = 2 << 10;
int n;
int freq[MAX];
ll pref[MAX];

ll dp[MAX][MAX];
int C[MAX][MAX];


void recon(int s,int e,string & str){
	assert(s <= e);
	if(s == e){
		puts(str.c_str());
		return;
	}
	int c = C[s][e];
	str.push_back('0');
	recon(s,c,str);
	str.pop_back();
	str.push_back('1');
	recon(c+1,e,str);
	str.pop_back();	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",freq + i);
		pref[i] = freq[i];
		pref[i] += i ? pref[i-1] : 0;
	}
	loop(i,n) dp[i][i] = 0,C[i][i] = i;
	for(int k = 1;k < n;k++){
		for(int s = n-1-k;s >= 0;s--){
			int e = s + k;
			dp[s][e] = oo;
			int l = s,r = e-1;
			if(s < e) l = C[s][e-1],r = C[s+1][e];
			ll sum = pref[e] - (s ? pref[s-1] : 0);
			for(int c = l;c <= r && c < e;c++){
				ll tmp = dp[s][c] + dp[c+1][e] + sum;
				if(tmp < dp[s][e]){
					dp[s][e] = tmp;
					C[s][e] = c;
				}
			}
//			cout << s << " " << e << " -> " << l << " " << r << ": " << dp[s][e] << " " << C[s][e] << endl;
		}		
	}
//	cerr << dp[0][n-1] << endl;
	string s;
	recon(0,n-1,s);
	return 0;
}
