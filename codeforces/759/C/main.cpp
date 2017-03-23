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

const int MAX = 1e5 + 1e2;
int ord[MAX],P[MAX],T[MAX],X[MAX],n;
int ST[MAX << 2][2];
int rev[MAX];

void update(int node,int s,int e,int p){
	if(s == e){
		if(T[rev[p]]) ST[node][1]++;
		else ST[node][0]++;
	}
	else{
		int m = (s + e) >> 1,left = node << 1,right = left | 1;
		if(p <= m) update(left,s,m,p);
		else update(right,m+1,e,p);
		ST[node][0] = ST[left][0] + max(ST[right][0] - ST[left][1],0);
		ST[node][1] = ST[right][1] + max(ST[left][1] - ST[right][0],0);
	}
}

int query(int node,int s,int e,int cnt){
	if(s == e) {
		if(ST[node][1]){
			if(cnt) return -1;
			return X[rev[s]];
		}
		else return -1;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(ST[right][1] > cnt) return query(right,m+1,e,cnt);
	else return query(left,s,m,cnt - ST[right][1] + ST[right][0]);	
}

int main(){
	scanf("%d",&n);
	loop(i,n){
		scanf("%d %d",P + i,T + i);
		if(T[i] == 1) scanf("%d",X + i);
		P[i]--; rev[P[i]] = i;
		update(1,0,n-1,P[i]);
		printf("%d\n",query(1,0,n-1,0));
//		cerr << query(1,0,n-1,0) << endl;
	}
	
	return 0;
}
