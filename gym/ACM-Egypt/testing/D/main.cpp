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

int cnt[128];
int prime_cnt[41][41];

int main(){
	loop(i,40){
		loop(j,41) prime_cnt[i + 1][j] = prime_cnt[i][j];
		int num = i + 1;
		range(j,2,40) while(num%j == 0) prime_cnt[i + 1][j]++,num /= j;
	}
	string s; cin >> s;
	assert(1 <= sz(s) && sz(s) <= 40);
	unsigned ll ans = 0;	
	for(int i = 0;i < sz(s);i++){
		memset(cnt,0,sizeof cnt);
		string ch; int odd = 0;
		for(int j = i;j < sz(s);j++){
			if(!cnt[s[j]]) ch.pb(s[j]);
			if(cnt[s[j]] & 1) odd--;
			else odd++;
			cnt[s[j]]++;
			
			int len = j - i + 1;
			if(len & 1){
				if(odd != 1) continue;				
			}
			else{
				if(odd) continue;
			}
			int ctr[41] ; 
			loop(k,41) ctr[k] = prime_cnt[len/2][k];
			for(char c : ch) loop(k,41) ctr[k] -= prime_cnt[cnt[c]/2][k];
			unsigned ll tmp = 1;
			range(k,2,40){
				loop(q,ctr[k]) tmp *= k;
			}
			ans += tmp;
		}
	}
	cout << ans << endl;
	cerr << ans << endl;
	
	return 0;
}
