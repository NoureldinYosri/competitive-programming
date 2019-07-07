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

const int MAX = 100*1000 + 10,MAXLG = 20;
int A[MAX],B[MAX],H[MAX],n;
map<int,int> right_to_left;
PQ<pi> pq;
int sparse[MAX][MAXLG][2],lg[MAX];
map<int,vi> idx;

void build() {
	lg[0] = -1;
	range(i,1,n) lg[i] = lg[i-1] + (i==LSOne(i));

	loop(i,n) sparse[i][0][0] = sparse[i][0][1] = A[i];

	loop(k,MAXLG-1)
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			sparse[i][k+1][0] = min(sparse[i][k][0],sparse[j][k][0]);
			sparse[i][k+1][1] = max(sparse[i][k][1],sparse[j][k][1]);
	}
}
int get_min(int s,int e) {
	int l = lg[e-s+1];
	return min(sparse[s][l][0],sparse[e-(1<<l)+1][l][0]);
}
int get_max(int s,int e) {
	int l = lg[e-s+1];
	return max(sparse[s][l][1],sparse[e-(1<<l)+1][l][1]);
}

void insert(int l,int r,int h) {
	if(l > r) return;
	H[r] = h;
	right_to_left[r] = l;
}

int get_left(int s,int e,int i) {
	e = i;
	while(s < e) {
		int m = (s + e) >> 1;
		if(get_min(m,i) >= B[i])
			e = m;
		else
			s = m+1;
	}
	vi & V = idx[B[i]];
	return *lower_bound(all(V),s);
}

int get_right(int s,int e,int i) {
	s = i;
	while(s < e) {
		int m = s + (e-s+1)/2;
		if(get_min(i,m) >= B[i]) s = m;
		else e=m-1;
	}
	vi & V = idx[B[i]];
	auto ptr = upper_bound(all(V),e);
	--ptr;
	return *ptr;
}




int get_h(int s,int e,int old) {
	return min(get_max(s,e),old);
}

bool cond(int i,int s,int e,int old,int h) {
	return min(A[i],old) != h;
}

int solve(){
	loop(i,n) if(A[i] < B[i]) return -1;
	int ans = 0;
	build();
	right_to_left.clear();

	insert(0,n-1,INT_MAX);
	loop(i,n) pq.push(mp(B[i],i));

	idx.clear();
	loop(i,n) idx[B[i]].push_back(i);

	while(!pq.empty()) {
		pi cur = pq.top(); pq.pop();
		int i = cur.yy,h = cur.xx;
		int r = right_to_left.lower_bound(i)->first,l = right_to_left[r];
		int s = get_left(l,r,i),e = get_right(l,r,i);
		int old_h = H[r];
		right_to_left.erase(r);

//		cerr << i << " " << min(A[i],old_h) << " -> " << h << " " << s << " " << e << endl;

		if(cond(i,s,e,old_h,h)){
//			cerr << s << " " << e << " " << h << endl;
			ans ++;
			insert(l,s-1,old_h);
			insert(s,i-1,h);
			insert(i+1,e,h);
			insert(e+1,r,old_h);
		}
		else {
			insert(l,i-1,old_h);
			insert(i+1,r,old_h);
		}
	}

	return ans;
}



int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		loop(i,n) scanf("%d",B + i);
		printf("%d\n",solve());
	}
	return 0;
}

