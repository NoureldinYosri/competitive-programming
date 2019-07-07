#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 1 << 20;
int n;
int P[MAX];
vp ans;
int D[MAX],loc[MAX];


bool cond(int i,int j,int & rej) {
	if(2*abs(i-j) < n) return 0;
	if(rej) {
		rej--;
		return 0;
	}
	return 1;
}
int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",P + i),P[i]--;
	loop(i,n) loc[P[i]] = i;
	set<pi> pq;
	loop(i,n) {
		D[i] = abs(loc[i] - i);
		if(i == loc[i]) continue;
		pq.insert(mp(D[i],i));
	}

	while(!pq.empty() && pq.rbegin()->xx > 0) {
		pi p = *pq.rbegin();
		assert(p.yy == P[loc[p.yy]]);
		if(2*p.xx >= n) {
			cerr << "1" << endl;
			int i = p.yy;
			int j = loc[i];
			ans.push_back(mp(i,j));
			int t = P[i];
			pq.erase(p);
			pq.erase(mp(D[t],t));

			swap(P[i],P[j]);
			loc[i] = i;
			loc[t] = j;
			D[i] = 0;
			D[t] = abs(loc[t] - t);
			pq.insert(mp(D[t],t));
		}
		else {
			int i = loc[p.yy];
			int j = (rand()*(ll)rand())%n;
			int rej = 3;
			while(!cond(i,j,rej)) j = (rand()*(ll)rand())%n;

			ans.push_back(mp(i,j));
			int a = P[i],b = P[j];
			pq.erase(mp(D[a],a));
			pq.erase(mp(D[b],b));
			swap(P[i],P[j]);
			loc[a] = j;
			loc[b] = i;
			D[a] = abs(loc[a] - a);
			D[b] = abs(loc[b] - b);
			pq.insert(mp(D[a],a));
			pq.insert(mp(D[b],b));
		}
		while(!pq.empty() && pq.begin()->xx == 0) pq.erase(pq.begin());
		prArr(P,n,int);
		assert(sz(ans) <= 5*n);
	}
	printf("%d\n",sz(ans));
	for(auto p : ans)
		printf("%d %d\n",p.xx+1,p.yy+1);
	return 0;
}
#endif
