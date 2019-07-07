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

const int MAX = 500*1000 + 10;
char S[MAX];
int A[MAX],B[MAX],pos[MAX],m,n;

int ST[1 << 20][4];

void push_up(int cur) {
	int left = 2*cur + 1,right = left + 1;

	ST[cur][0] = min(ST[left][0],ST[left][1] + ST[right][0]);
	ST[cur][2] = min(ST[left][2] + ST[right][3],ST[right][2]);

	ST[cur][1] = ST[left][1] + ST[right][1];
	ST[cur][3] = ST[left][3] + ST[right][3];
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur][0] = ST[cur][1] = (S[s] == ')') ? -1 : 1;
		ST[cur][2] = ST[cur][3] = (S[s] == '(') ? -1 : 1;
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);

	push_up(cur);
}

void update(int cur,int s,int e,int p,char c) {
//	cerr << cur << " " << s << " " << e << endl;
	if(s == e) {
//		cerr << "set " << s << " to " << c << endl;

		ST[cur][0] = ST[cur][1] = (c == ')') ? -1 : 1;
		ST[cur][2] = ST[cur][3] = (c == '(') ? -1 : 1;
//		prArr(ST[cur],4,int);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) update(left,s,m,p,c);
	else update(right,m+1,e,p,c);

	push_up(cur);
//	cerr << s << " " << e << ": ";
//	prArr(ST[cur],4,int);
//	cerr << "left is " ;
//	prArr(ST[left],4,int);
}

pi query(int cur,int s,int e,int l,int r){
	if(l <= s && e <= r) return mp(S[0],S[2]);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	pi a = query(left,s,m,l,m);
	pi b = query(right,m+1,e,m+1,r);
	a.first = min(a.first,b.first);
	a.second = min(a.second,b.second);
	return a;
}

void add(int p,int v,int *BIT) {
	for(++p;p < MAX;p += LSOne(p))
		BIT[p] += v;
}
int get(int p,int *BIT){
	int ret = 0;
	for(++p;p; p ^= LSOne(p)) ret += BIT[p];
	return ret;
}

bool canOpenf(int i) {
	update(0,0,n-1,i,'(');
//	cerr << i << ": " << ST[0][0] << " " << ST[0][2] << endl;
	bool f = ST[0][0] >= 0 && ST[0][2] >= 0;
	update(0,0,n-1,i,'?');
	return f;
}
bool canClosef(int i) {
	update(0,0,n-1,i,')');
	bool f = ST[0][0] >= 0 && ST[0][2] >= 0;
	update(0,0,n-1,i,'?');
	return f;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%s",S);
	n = strlen(S);
	if(n&1) {
		cout << -1 << endl;
		return 0;
	}
	loop(i,n) {
		if(S[i] != '?') continue;
		pos[m] = i;
		m++;
	}
	loop(i,m) scanf("%d %d",A + pos[i],B + pos[i]);
	ll ans = 0;
	vi V;
	loop(i,n){
		if(S[i] == '?') {
			int d = min(A[i],B[i]);
			ans += d;
			A[i] -= d;
			B[i] -= d;
			V.push_back(i);
		}
	}
	build(0,0,n-1);
	sort(all(V),[](const int & a,const int & b) {
		int fa = -max(A[a],B[a]);
		int fb = -max(A[b],B[b]);
		return tie(fa,a) < tie(fb,b);
	});
	int rem [] = {n/2,n/2};
	loop(i,n) {
		if(S[i] == '(') rem[0]--;
		else if(S[i] == ')') rem[1]--;
	}
	for(auto i : V) {

		bool canOpen = rem[0] && canOpenf(i);
		bool canClose = rem[1] && canClosef(i);

//		prArr(rem,2,int);
//		cerr << i  << " -";
//		if(canOpen) cerr << "(";
//		if(canClose) cerr << ")";
//		cerr << "-: " << string(S) << endl;

		if(!canOpen && !canClose){
			cout << -1 << endl;
			return 0;
		}

		int c = 0;
		if(!A[i]) {
			if(canOpen) c = 0;
			else c = 1;
		}
		else {
			if(canClose) c = 1;
			else c = 0;
		}


		rem[c]--;
		ans += c ? B[i] : A[i];
		S[i] = "()"[c];
		update(0,0,n-1,i,S[i]);
	}
	if(ST[0][0] == 0) {
		cout << ans << endl;
		cout << string(S) << endl;
	}
	else cout << -1 << endl;
	return 0;
}
