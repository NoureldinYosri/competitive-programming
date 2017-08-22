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

const int MAX = 100*1000 + 10;
int vis[MAX],n,d;
vi aux,bank;
ll A[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--) {
		memset(vis,0,sizeof vis);
		scanf("%d %d",&n,&d);
		loop(i,n) scanf("%lld",A + i);
		ll target_val,ans = 0;
		bool cond = 1;
		loop(t,n) if(!vis[t]) {
			int j = t,len = 0; ll sum = 0,tmp = 0;
			while(j < n) {
				sum += A[j];
				aux.pb(j);
				vis[j] = 1;
				len++;
				j += d;
			}
			if(sum%len) cond = 0;
			else {
				sum /= len;
				if(!t) target_val = sum;
				else if(target_val != sum){
					cond = 0;
					continue;
				}
				loop(i,len) {
					ll cur = A[aux[i]] - sum;
					while(cur > 0 && !bank.empty() && A[aux[bank.back()]] < 0) {
						ll d = min(cur,-A[aux[bank.back()]]);
						cur -= d;
						A[aux[bank.back()]] += d;
						tmp += d*(i - bank.back());
						if(!A[aux[bank.back()]]) bank.pop_back();
					}
					while(cur < 0 && !bank.empty() && A[aux[bank.back()]] > 0) {
						ll d = min(-cur,A[aux[bank.back()]]);
						cur += d;
						A[aux[bank.back()]] -= d;
						tmp += d*(i - bank.back());
						if(!A[aux[bank.back()]]) bank.pop_back();
					}
					A[aux[i]] = cur;
					if(cur) bank.pb(i);
				}
				assert(bank.empty());
			}
			ans += tmp;
			aux.clear();
		}
		if(!cond) ans = -1;
		printf("%lld\n",ans);
	}
	return 0;
}
