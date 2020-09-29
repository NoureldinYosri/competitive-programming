#pragma GCC optimize ("O3")
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

const int mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

vi txt, id, End, Start, len;
int n;

void read(){
	static char buffer[1 << 20];
	scanf("%s", buffer);
	int i = sz(Start);
	Start.pb(sz(txt));
	for(char *ptr = buffer; *ptr; ptr++){
		txt.pb(*ptr);
		id.pb(i);
	}
	txt.pb(-n + i);
	id.pb(i);
	End.pb(sz(txt));
	len.pb(0);
	if(i){
		int a = Start[i-1], b = Start[i];
		while(a < End[i-1] && b < End[i] && txt[a] == txt[b]){
			len.back()++;
			a++;
			b++;
		}
	} 
}


int solve(){
	int m = sz(txt);
	vi dp(m + 1, 0), suff(m + 1, 0);
	for(int j = End.back() - 1; j >= Start.back(); j--){
		dp[j] = 1;
		suff[j] = add(dp[j], suff[j + 1]);
	}
	for(int i = n-2; i >= 0; i--) {
		for(int j = End[i] - 1; j >= Start[i]; j--){
			int k = j - Start[i], l = len[i+1];
			if(k > len[i+1]){
				if(txt[Start[i] + l] > txt[Start[i + 1] + l]){
					dp[i] = 0;
				} else {
					assert(txt[Start[i] + l] < txt[Start[i + 1] + l]);
					dp[i] = add(suff[Start[i+1]], suff[End[i+1]]);
				}				
			} else if(k < len[i+1]){
				
			} else {
				// k == len[i + 1]
				if(k + Start[i] == End[i] - 1){
					//i is prefix of i+1
					dp[i] = add(suff[Start[i+1]], suff[End[i+1]]);					
				} else if(k + Start[i+1] == End[i+1]-1) {
					//i+1 is prefix of i
					dp[i] = 0;
				} else {
					int a = txt[j + 1];
					
				}
			}
			suff[j] = add(dp[j], suff[j + 1]);
		}
	}
	print(dp, int);
	print(suff, int);
	return add(suff[0], - suff[End[0]]);
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) read();
	cout << solve() << endl;
	return 0;
}
