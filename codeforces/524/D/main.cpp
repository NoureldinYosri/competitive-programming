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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 20'010;
int id[MAX],n,M,T;
int S[MAX];
vi G[86400];

int main(){
	scanf("%d %d %d",&n,&M,&T);
	vector<pair<pi,int> > I;
	loop(i,n){
		int h,m,s; scanf("%d:%d:%d",&h,&m,&s);
		S[i] = h*3600 + m*60 + s;
		I.pb(mp(mp(S[i],1),i));
		I.pb(mp(mp(S[i] + T,-1),i));
	}

	map<int,int> vals;
	set<pi> death_time;
	sort(all(I));
	int cnt = 0,found = 0;
	for(auto i : I){
		int t = i.xx.xx,type = i.xx.yy, idx = i.yy;
		if(type == -1){
			int x = id[idx];
			vals[x]--;
			if(!vals[x]) vals.erase(x);			
			continue;
		}
		if(sz(vals) < M) {
			id[idx] = ++cnt;
			death_time.insert(mp(S[idx] + T,id[idx]));
		}
		else {
			assert(!death_time.empty());		
			int x = death_time.rbegin()->yy;
			id[idx] = x;
			int e = death_time.rbegin()->xx;
			if(S[idx] + T  > e) {
				death_time.erase(mp(e,x));
				e = S[idx] + T;
				death_time.insert(mp(e,x));
			}
		}
		vals[id[idx]]++;
		found |= sz(vals) == M;
	}
	if(!found) puts("No solution");
	else {
		printf("%d\n",cnt);
		loop(i,n) printf("%d\n",id[i]);	
	}	return 0;
}
