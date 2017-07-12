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

const int MAX = 100*1000 + 1000;
char type[MAX][20];
int num[MAX],n; ll price[MAX];
ll ST[MAX << 2][2];
int toOmit[MAX << 2];
vi ord;
int rev[MAX],m;

void push(int node,int s,int e){
	if(!toOmit[node]) return;
	int left = node << 1,right = left | 1;
	ST[left][0] = ST[right][0] = 0;
	ST[left][1] = ST[right][1] = 0;
	toOmit[left] = toOmit[right] = 1;
	toOmit[node] = 0;
}

void update(int node,int s,int e,int p){
	if(s == e){
		p = ord[p];
		ST[node][0] = num[p];
		ST[node][1] = price[p] * num[p];
		return;
	}
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p);
	else update(right,m+1,e,p);
	loop(i,2) ST[node][i] = ST[left][i] + ST[right][i];
}

ll query(int node,int s,int e,int cnt){
	if(cnt <= 0 || ST[node][0] == 0) return 0;
	if(ST[node][0] <= cnt) return ST[node][1];
	if(s == e) {
		ll d = min(cnt + 0LL,ST[node][0]);
		return d*price[ord[s]];
	}
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	ll ret = query(left,s,m,cnt);
	if(ST[left][0] < cnt) ret += query(right,m+1,e,cnt - ST[left][0]);
	loop(i,2) ST[node][i] = ST[left][i] + ST[right][i];
	return ret;
}


void omit(int node,int s,int e,int cnt){
	if(cnt <= 0 || ST[node][0] == 0) return;
	if(s == e) {
		int d = min(ST[node][0],0LL + cnt);
		ST[node][0] -= d;
		ST[node][1] = ST[node][0] * price[ord[s]];
		return;
	}
	if(ST[node][0] <= cnt){
//		cerr << "omit all in of ";
//		range(i,s,e) prp(mp(num[i],price[i]));
//		cerr << endl;
		ST[node][0] = 0;
		ST[node][1] = 0;
		toOmit[node] = 1;
		return;
	}
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	omit(right,m+1,e,cnt - ST[left][0]);
	omit(left,s,m,cnt);
	loop(i,2) ST[node][i] = ST[left][i] + ST[right][i];
}

void preprocess(){
	ord.reserve(n);
	loop(i,n) if(type[i][0] == 'A') ord.pb(i);
	sort(all(ord),[](const int & a,const int & b){
		return price[a] < price[b];
	});
	m = sz(ord);
	loop(i,m) rev[ord[i]] = i;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	while(scanf("%s",type[n]) == 1){
		scanf("%d %lld",num + n,price + n);
		n++;
	}
	preprocess();
	loop(i,n){
		if(type[i][0] == 'A') update(1,0,m-1,rev[i]);
		else if(!m || ST[1][0] < num[i]) puts("UNHAPPY");
		else{
			ll tot = query(1,0,m-1,num[i]);
			if(tot > price[i]) puts("UNHAPPY");
			else{
				puts("HAPPY");
				omit(1,0,m-1,num[i]);
			}
//			printf("%lld\n",tot);
		}
	}
	return 0;
}
