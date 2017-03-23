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

bool vis[1 << 18];
pi dp[1 << 18];
int choice[1 << 18];
int aux[1 << 18];

string i2b(int msk){
	char buffer[19] = {0};
	loop(i,18) 
		if(msk & (1 << i)) buffer[i] = '1'; 
		else buffer[i] = '0';
	reverse(buffer,buffer + 18);
	return string(buffer);
}

vector<vi> TRI {{1,2,3},{4,5,6},{3,5,7},{7,8,9},{10,11,12},{6,11,13},{13,14,15},{9,14,16},{16,17,18}};
int get(int msk,int x){
	int ret = 0;	
	for(vi & tri:TRI)
		if(binary_search(all(tri),x)){
			int t = 0;
			for(int a : tri) if(a != x) t |= 1 << a;
			assert(popcnt(t) == 2);
			ret += (t & msk) == t;
		} 
	return ret;
}

pi solve(int msk){
	if(msk == (1 << 18) - 1) return mp(0,0);
	if(vis[msk]) return dp[msk];
	vis[msk] = 1;
	dp[msk] = {-1,0};
	int omsk = ((1 << 18) - 1) ^ msk;
	for(int i = 0;i < 18;i++) if(omsk & (1 << i)) {
		pi tmp = solve(msk | (1 << i));
		int k = get(msk,i);
		if(k) tmp.xx += k;
		else swap(tmp.xx,tmp.yy); 
		if(tmp.xx > dp[msk].xx || (tmp.xx == dp[msk].xx && tmp.yy < dp[msk].yy)) {
			dp[msk] = tmp;
			choice[msk] = i;
			aux[msk] = k;
		}
	}
 	//cerr << i2b(msk) << " ";prp(dp[msk]); cerr << endl;
	return dp[msk];
}

int main(){
	for(auto & X : TRI) for(auto & y : X) y--;
	int n; 
	while(scanf("%d",&n) == 1 && n){
		int msk = 0;
		loop(i,n){
			int x; scanf("%d",&x); x --;
			msk |= 1 << x;
		}
		memset(vis,0,sizeof vis);
		auto ans = solve(msk);
		if(ans.xx == ans.yy) puts("Draw");
		else if(ans.xx > ans.yy) puts("Andy wins");
		else puts("Ralph wins");	
	}	
	
	
	return 0;
}
