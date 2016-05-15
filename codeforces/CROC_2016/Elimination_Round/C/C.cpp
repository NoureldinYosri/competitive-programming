#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n,k;
deque<int> dq;
char room[1 << 20];

int g(int j){
	return max(dq.back() - dq[j],dq[j] - dq.front());
}

int f(){
	int s = 0,e = sz(dq) - 1;
	while(e - s > 1){
		int m1 = s + (e - s + 1)/3,m2 = m1 + (e - s + 1)/3;
		if(g(m1) < g(m2)) e = m2 - 1;
		else s = m1 + 1;
	}
	return min(g(s),g(e));
}


int main(){
	scanf("%d %d %s",&n,&k,room); 
	int i = 0;
	while(i < n && sz(dq) < k + 1){
		if(room[i] == '0') dq.pb(i);
		i++;
	}
	int j = 0;
	int ans = f();
	while(i < n){
		if(room[i] == '0'){
			dq.pop_front();
			dq.pb(i);
			ans = min(ans,f());
		}
		i++;
	}
	cout << ans << endl;
	return 0;
}
