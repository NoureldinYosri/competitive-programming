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
#define popcnt(x) __builtin_popcount(x)
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
int n,k;
int X1[MAX],Y1[MAX],X2[MAX],Y2[MAX];
int CX[MAX],CY[MAX];
int ord1[MAX],ord2[MAX],ord3[MAX],ord4[MAX];
int vis[MAX];

auto cmp1 = [](const int & a,const int & b){
	return CX[a] < CX[b];
};
auto cmp2 = [](const int & a,const int & b){
	return CX[a] > CX[b];
};
auto cmp3 = [](const int & a,const int & b){
	return CY[a] < CY[b];
};
auto cmp4 = [](const int & a,const int & b){
	return CY[a] > CY[b];
};

vi done;

ll solve(int left,int right,int down,int top){
	bool change = 1;
	while(change){
		change = 0;
		for(int i = 0;i < n && left;i++){
			int x = ord1[i];
			if(vis[x]) continue;
			vis[x] = 1;
			done.pb(x);
			left--;
			change = 1;
		}

		for(int i = 0;i < n && right;i++){
			int x = ord2[i];
			if(vis[x]) continue;
			vis[x] = 1;
			done.pb(x);
			right--;
			change = 1;
		}
		for(int i = 0;i < n && down;i++){
			int x = ord3[i];
			if(vis[x]) continue;
			vis[x] = 1;
			done.pb(x);
			down--;
			change = 1;
		}
		for(int i = 0;i < n && top;i++){
			int x = ord4[i];
			if(vis[x]) continue;
			vis[x] = 1;
			done.pb(x);
			top--;
			change = 1;
		}

	}
	assert(sz(done) <= k);
	int x = 1,y = 1,lx = 0,ly = 0,rx = 1,ry = 1;
	for(int i = 0;i < n;i++){
		int cur = ord1[i];
		if(!vis[cur]){
			lx = CX[cur];
			break;
		}
	}
	for(int i = 0;i < n;i++){
		int cur = ord2[i];
		if(!vis[cur]){
			rx = CX[cur];
			break;
		}
	}
	for(int i = 0;i < n;i++){
		int cur = ord3[i];
		if(!vis[cur]){
			ly = CY[cur];
			break;
		}
	}
	for(int i = 0;i < n;i++){
		int cur = ord4[i];
		if(!vis[cur]){
			ry = CY[cur];
			break;
		}
	}
	x = max(rx - lx,1);
	y = max(ry - ly,1);
	/*cerr << lx << " " << rx << " -> " << x << endl;
	cerr << ly << " " << ry << " -> " << y << endl;
	*/x = (x + 1)/2;
	y = (y + 1)/2;
	/*print(done,int);
	cerr << "lead to " << x << " " << y << " -> " << x*y << endl;
	cerr << endl;
	*/for(int u : done) vis[u] = 0;
	done.clear();
	return x*1LL*y;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	loop(i,n) {
		scanf("%d %d %d %d",X1 + i,Y1 + i,X2 + i,Y2 + i);
		ord1[i] = ord2[i] = ord3[i] = ord4[i] = i;
		CX[i] = X1[i] + X2[i];
		CY[i] = Y1[i] + Y2[i];
	}
	sort(ord1,ord1 + n,cmp1);
	sort(ord2,ord2 + n,cmp2);
	sort(ord3,ord3 + n,cmp3);
	sort(ord4,ord4 + n,cmp4);
	ll ans = LLONG_MAX;
	for(int left = 0;left <= k;left++)
		for(int right = 0;left + right <= k;right++)
			for(int top = 0;top + left + right <= k;top++)
				for(int down = 0;down + top + left + right <= k;down++)
					ans = min(ans,solve(left,right,down,top));
	cout << ans << endl;
	return 0;
}
