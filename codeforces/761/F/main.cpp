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


const int MAX = 300*1000 + 10;
const int MAXN = 1024;
char grid[MAXN][MAXN];
int n,m,k;
int S[MAX][4];
char c[MAX];
ll BIT[26][MAXN][MAXN];
ll cnt[MAXN][MAXN][26];
ll cost[MAXN][MAXN];

void update(int x1,int y1,ll v,ll T[MAXN][MAXN]){
	if(!x1 || !y1) return;	
	for(int x = x1;x <= n;x += LSOne(x)){
		for(int y = y1; y <= m; y += LSOne(y)){
			T[x][y] += v;
		}
	}
}

ll get(int x,int y0,ll T[MAXN][MAXN]){
	ll ret = 0;
	for(;x;x ^= LSOne(x))
		for(int y = y0;y;y ^= LSOne(y))
			ret += T[x][y];
	return ret;
}


int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n) scanf("%s",grid[i]);
	loop(i,k) {
		loop(j,4) scanf("%d",&S[i][j]);
		scanf(" %c",c + i);
		int x1 = S[i][0],y1 = S[i][1],x2 = S[i][2],y2 = S[i][3];
		update(x1,y1,1,BIT[c[i] - 'a']);
		update(x1,y2 + 1,-1,BIT[c[i] - 'a']);
		update(x2 + 1,y1,-1,BIT[c[i] - 'a']);
		update(x2 + 1,y2 + 1,1,BIT[c[i] - 'a']);
	}	
	loop(i,n) loop(j,m) {
		int sum = 0;	
		loop(ch,26) {
			cnt[i][j][ch] = get(i+1,j+1,BIT[ch]);
			sum += cnt[i][j][ch];
	//		if(cnt[i][j][ch]) fprintf(stderr,"f(%d,%d,%c) = %lld\n",i,j,ch + 'a',cnt[i][j][ch]);
		}
		cnt[i][j][grid[i][j] - 'a'] += k - sum;
		assert(sum <= k);
	//	loop(ch,26) if(cnt[i][j][ch]) fprintf(stderr,"f(%d,%d,%c) = %lld\n",i,j,ch + 'a',cnt[i][j][ch]);
	}
	ll ans = LLONG_MAX;
	ll sum = 0;
	loop(i,n) {
		loop(j,m) {
			int ch = grid[i][j] - 'a';
			ll tmp = 0;
			loop(q,26) tmp += abs(ch - q)*cnt[i][j][q];
		//	cerr << tmp << " ";
			sum += tmp;
			cost[i][j] = tmp;
			if(i) cost[i][j] += cost[i - 1][j];
			if(j) cost[i][j] += cost[i][j - 1];
			if(i && j) cost[i][j] -= cost[i - 1][j - 1];
		}
	//	cerr << endl;
	}
	/*loop(i,n) {
		prArr(cost[i],m,ll);
	}*/
	loop(i,n) loop(j,m){
		loop(ch,26) {
			if(i) cnt[i][j][ch] += cnt[i-1][j][ch];
			if(j) cnt[i][j][ch] += cnt[i][j-1][ch];
			if(i && j) cnt[i][j][ch] -= cnt[i-1][j-1][ch];
		}

	}
//	cerr << "sum = " << sum << endl; 
	loop(i,k){
		int x1 = S[i][0],y1 = S[i][1],x2 = S[i][2],y2 = S[i][3];
		int ch = c[i] - 'a';
		x1--,y1--,x2--,y2--;
		ll tmp = cost[x2][y2];
		if(x1) tmp -= cost[x1-1][y2];
		if(y1) tmp -= cost[x2][y1-1];
		if(x1 && y1) tmp += cost[x1-1][y1-1];
		tmp = sum - tmp;
		loop(j,26) {
			ll ctr = cnt[x2][y2][j];
			if(x1) ctr -= cnt[x1-1][y2][j];
			if(y1) ctr -= cnt[x2][y1-1][j];
			if(x1 && y1) ctr += cnt[x1-1][y1-1][j];
//			if(abs(j - ch)*ctr){
	//			cerr << "to " << char(j + 'a') << " " << abs(j - ch)*ctr << " ctr = " << ctr << endl;			
			tmp += abs(j - ch)*ctr; 
		//	}
		}
		//cerr << "aux = " << tmp << endl;
		ans = min(ans,tmp);
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
