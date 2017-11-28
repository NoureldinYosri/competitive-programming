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

const int MAX = 1000*1000 + 10,MAXLG = 24,CNT = 3;
int n,k,K;
pi P[CNT*MAX];
int to[CNT*MAX];
int ST[CNT*MAX][MAXLG],lg[CNT*MAX];

int argmax(int a,int b) {
	return (mp(to[a],-a) > mp(to[b],-b)) ? a : b;
}
void preprocess(){
	loop(i,K){
		int a = P[i].xx, b = P[i].yy;
		to[a] = max(to[a],b);
	}
//	prArr(to+1,2*n,int);
	lg[0] = -1;
	for(int i = 1;i < CNT*MAX;i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
	range(i,1,CNT*n) ST[i][0] = to[i] ? i : 0;
	loop(q,MAXLG-1)
		range(i,1,CNT*n) {
			int j = i + (1 << q);
			if(j > 2*n) j = i;
			ST[i][q + 1] = argmax(ST[i][q],ST[j][q]);
		}
}


int RMQ(int s,int e){
	if(s > e) return 0;
	int l = lg[e - s + 1];
	return argmax(ST[s][l],ST[e - (1 << l) + 1][l]);
}


inline int getNext(int cur) {
	int nxt = RMQ(cur,to[cur]);
	if(to[to[cur]+1] && to[to[cur] + 1] >= to[nxt]) nxt = to[cur]+1;
	if(nxt == cur) cur = nxt = 0;
	return nxt;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	K = k;

	loop(i,k) {
		scanf("%d %d",&P[i].xx,&P[i].yy);
		if(P[i].xx > P[i].yy){
			P[i].yy += n ;
			P[K++] = mp(P[i].xx + n,P[i].yy + n);
		}
		else{
			P[K++] = mp(P[i].xx + n,P[i].yy+n);
//			P[K++] = mp(P[i].xx + 2*n,P[i].yy+2*n);
		}
	}
	preprocess();

	int ans = INT_MAX;
	vi aux;
	deque<int> dq;
	for(int i = 1;i <= CNT*n;i++) if(to[i]){

		if(!dq.empty()){
			int cur = i;
			aux.pb(i);
			while(cur && to[cur]+1 < dq.front()){
				int nxt = getNext(cur);
				cur = nxt;
				if(!nxt) break;
				aux.pb(nxt);
				cur = nxt;
			}
			if(!cur) {
				aux.clear();
				continue;
			}
			while(!dq.empty() && getNext(aux.back()) && getNext(aux.back()) != dq.front() && to[getNext(aux.back())] < n+i-1){
				int a = dq.front(),b = getNext(aux.back()) ;
//				cerr << "replacing " << a << " with " << b << endl;
//				cerr << "reach was " << to[a] << " became " << to[b] << endl;
				dq.pop_front();
				aux.pb(b);
			}
//			cerr << i << endl;
//			print(aux,int);
//			print(dq,int);
			while(!aux.empty()) {
				if(dq.empty() || aux.back() != dq.front())
					dq.push_front(aux.back());
				aux.pop_back();
			}
		}
		else {
			dq.pb(i);
		}


//		cerr << "==========================" << endl;
//		print(dq,int);
		int cur = dq.back();
		while(to[cur] < i+n-1) {
			int nxt = RMQ(cur,to[cur]);
//			cerr << cur << " " << nxt << " " << to[nxt]  << " " << to[cur +1 ] << endl;
			if(to[to[cur]+1] && to[to[cur] + 1] > to[nxt]) nxt = to[cur]+1;
			if(nxt == cur) break;
			dq.pb(nxt);
			cur = nxt;
		}

		if(to[dq.back()] >= i + n-1)
			ans = min(ans,sz(dq));
//		print(dq,int);
		assert(dq.front() == i);
		dq.pop_front();
	}

	if(ans == INT_MAX) puts("impossible");
	else cout << ans << endl;
	return 0;
}
