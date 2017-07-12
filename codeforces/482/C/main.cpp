#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

char I[50][21];
int n,len;
double dp[1 << 20];
ll who[1 << 20],someone[1 << 20];
int cnt[1 << 20];
int trie[20*50 + 10][128],siz;
ll END[20*50 + 10];
vector<char> VC[20*50 + 10];


void preprocess(){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++) if(i != j){
			int msk = 0;
			for(int k = 0;k < len;k++)
				if(I[i][k] == I[j][k])
					msk |= 1 << k;
			someone[msk] |= 1LL << i;
		}
	}
	int tot = (1 << len) - 1;
	for(int msk = (1 << len)-1;msk >= 0;msk--){
		for(int tmp = tot^msk;tmp;tmp ^= LSOne(tmp))
			someone[msk] |= someone[msk | LSOne(tmp)];
		who[msk] = ((1LL << n) - 1) ^ someone[msk];
	}
}

void solve(){
	for(int msk = (1 << len)-2;msk >= 0;msk--){
		double & ret = dp[msk]; ret = 0;
		for(int tmp = ((1 << len) - 1) ^ msk;tmp;tmp ^= LSOne(tmp)){
			int nmsk = msk | LSOne(tmp);
			ret += popcnt(who[nmsk] & ~who[msk])*popcnt(nmsk)*1.0/n;
			ret += dp[nmsk];
		}
		ret /= len - popcnt(msk);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	#endif

	cin >> n;
	loop(i,n) cin >> I[i];
	len = strlen(I[0]);

	preprocess();
	solve();
	printf("%.10lf\n",dp[0]);
	return 0;
}
