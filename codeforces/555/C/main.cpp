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

const int MAX = 2e5 + 1e2;
int n,m;
int X[MAX],Y[MAX],F[MAX],G[MAX],k1,k2;
char type[MAX];
int ST[2][MAX << 2];
set<int> S;

void compress(int *X,int *F,int & k){
	sort(F,F + m + 1);
	k = unique(F,F + m + 1) - F;
	loop(i,m) X[i] = lower_bound(F,F + k,X[i]) - F;
}

void update(int node,int s,int e,int l,int r,int v,int *T){
	if(l <= s && e <= r){
		T[node] = max(T[node],v);
		return;	
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,v,T);
	else if(m < l) update(right,m+1,e,l,r,v,T);
	else update(left,s,m,l,m,v,T),update(right,m+1,e,m+1,r,v,T);
}

int query(int node,int s,int e,int p,int *T){
	if(s == e) return T[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return max(T[node],query(left,s,m,p,T));
	else return max(T[node],query(right,m+1,e,p,T));	
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		scanf("%d %d %c",X + i,Y + i,&type[i]);
		swap(X[i],Y[i]);
		F[i] = X[i];
		G[i] = Y[i];
	}
	compress(X,F,k1);
	compress(Y,G,k2);	
	loop(i,m){
		if(S.find(X[i]) != S.end()){
			puts("0");
			continue;
		}
		//cerr << X[i] << " " << Y[i] << endl;
		if(type[i] == 'U'){
			int r = query(1,0,k2 - 1,Y[i],ST[0]);
		//	cerr << "U " << F[X[i]] << " -> " << G[Y[i]] << " -> " << F[r] << endl;
			printf("%d\n",F[X[i]] - F[r]);
			update(1,0,k1 - 1,r,X[i],Y[i],ST[1]);
		}
		else{
			int c = query(1,0,k1-1,X[i],ST[1]);
		//	cerr << "L " << F[X[i]] << " -> " << G[c] << endl;
			printf("%d\n",G[Y[i]] - G[c]);
			update(1,0,k2 - 1,c,Y[i],X[i],ST[0]);			
		}
		S.insert(X[i]);
	}	
	return 0;
}
