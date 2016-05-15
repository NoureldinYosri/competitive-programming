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
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

#define milk yy.yy
#define tt xx
#define person yy.xx
#define ignore 1
#define possible 0

pair<int,pi> events[1000];
vi drinks [110];
int status[110];
vi drank[110];

int main(){
	if(!freopen("badmilk.in","r",stdin)){
		cerr << "couldn't open input" << endl;
		exit(1);
	}
	if(!freopen("badmilk.out","w",stdout)){
		cout << "couldn't open output" << endl;
		exit(1);
	}
	int N,M,D,S;
	cin >> N >> M >> D >> S;
	vi pos;
	loop(i,D) cin >> events[i].person >> events[i].milk >> events[i].tt;
	loop(i,S) cin >> events[D + i].person >> events[D + i].tt,events[D + i].milk = -1;
	sort(events,events + D + S);
	loop(i,D + S){
		int j = i;
		while(j < D + S && events[i].tt == events[j].tt){
			if(events[j].milk == -1){
				loop(k,M){
					if(status[k + 1] == possible)
						status[k + 1] = !binary_search(all(drinks[events[j].person]),k+1);
				}
			}
			j++;
		}
		while(i < j){
			if(events[i].milk != -1){
				int m = events[i].milk,p = events[i].person;
				drinks[p].pb(m);
				sort(all(drinks[p]));
				drank[m].pb(p);
			}
			i++;
		}
		i--;
	}
	int ans = 0;
	loop(i,M){
		if(status[i + 1] == possible){
			vi & V = drank[i + 1];
			sort(all(V));
			V.resize(unique(all(V)) - V.begin());
			ans = max(ans,(int)sz(V));
		}
	}
	assert(ans > 0);
	cout << ans << endl;
	return 0;
}
