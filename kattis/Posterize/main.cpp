#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

const ll oo = 1LL << 60;
int val[300],cnt[300];
int d,K;
vi G[300];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	cin >> d >> K;
	loop(i,d) cin >> val[i] >> cnt[i];
	ll ans = oo;
	for(int t = 0;t < 1000;t++){
		vi centers(K),new_centers(K);
		loop(i,K) centers[i] = rand()%256;
		sort(all(centers));
		for(int it = 0;it < 1000;it++){
			loop(i,K) G[i].clear();
			loop(i,d){
				int c = 0; int best = 1 << 28;
				loop(j,K){
					int dist = (centers[j] - val[i])*(centers[j] - val[i]);
					if(dist < best){
						best = dist;
						c = j;
					}
				}
				G[c].pb(i);
			}
			loop(i,K) {
				ll tot = 0,sum = 0;
				for(int idx : G[i]){
					ll r = val[idx],ctr = cnt[idx];
					sum += r*ctr;
					tot += ctr;
				}
				if(!tot) new_centers[i] = rand()%256;
				else new_centers[i] = sum/tot + (sum%tot > tot/2);
			}
			sort(all(new_centers));
			if(centers == new_centers) break;
			centers.swap(new_centers);
		}
		ll tmp = 0;
		loop(i,d){
			int best = 1 << 28;
			loop(j,K){
				int dist = (centers[j] - val[i])*(centers[j] - val[i]);
				best = min(best,dist);
			}
			tmp += best*1LL*cnt[i];
		}
		ans = min(ans,tmp);
	}
	cout << ans << endl;
	return 0;
}
