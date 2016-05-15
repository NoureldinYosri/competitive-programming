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

void sort(int k,int *SA,int *Rank,int L){
	int tmpSA[L + 1],ctr[max(256,L) + 10];
	fill(ctr,ctr + max(L,256) + 1,0);
	loop(i,L) ctr[((i + k < L) ? Rank[i + k] : 0) + 1]++;
	loop(i,max(L,256)) ctr[i + 1] += ctr[i];
	loop(i,L) {
		int u = ((SA[i] + k) < L) ? Rank[SA[i] + k] : 0;
		tmpSA[ctr[u]++] = SA[i];
	}
	loop(i,L) SA[i] = tmpSA[i];	
}


void BuildSA(const char *P,int L,int *SA,int *Rank,int *Pos){
	// initialize	
	loop(i,L) SA[i] = i,Rank[i] = P[i];
	SA[L] = L; Rank[L] = '$'; L++;
	sort(0,SA,Rank,L);	
		
	// helper	
	int tmpRank[L + 2];
	
	// main loop
	for(int k = 1,cnt; (k << 1) < L;k <<= 1){
		sort(k,SA,Rank,L);
		sort(0,SA,Rank,L);
		tmpRank[SA[0]] = cnt = 0;
		loop(i,L){
			if(!i) continue;
			cnt += !(Rank[SA[i]] == Rank[SA[i-1]] && Rank[SA[i]+k] == Rank[SA[i-1]+k]);	
			tmpRank[SA[i]] = cnt;		
		}
		loop(i,L) Rank[i] = tmpRank[i];
		break;
	}
	loop(i,L) Pos[SA[i]] = i;
//	loop(i,L) cerr << (char*)(P + SA[i]) << endl;
}

void BuildLCP(const char *P,int *SA,int *Pos,int n,int *LCP){
	int L = 0;
	loop(i,n) {
		if(Pos[i]) {
			int j = SA[Pos[i]-1];
			while(P[i + L] == P[j + L]) L++; 
		}
		LCP[Pos[i]] = L;
		if(L) L--;
	}
}

int lower_bound(int s,int e,char *P,int *SA,const char *T){
	while(s < e){
		int m = (s + e) >> 1;
		if(strcmp(T + SA[m],P) >= 0) e = m;
		else s = m + 1;
	}	
	return s;
}

pi EqualRange(const char *T,char *P,int *SA,int L){
	//loop(i,L + 1) cerr << i << " " << SA[i] << " " << (char*)(T + SA[i]) << endl;
	pi ret;
	ret.xx = lower_bound(0,L,P,SA,T);
	P[strlen(P) - 1]++;
	ret.yy = lower_bound(ret.xx,L,P,SA,T);
	return ret;
}

const int MAX = 300000;
char U[MAX],V[MAX];
int SA[MAX],Rank[MAX],Pos[MAX];

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",U);
		int L = strlen(U);
		loop(i,L) U[i] = tolower(U[i]);
		BuildSA(U,L,SA,Rank,Pos);
		int m;
		scanf("%d",&m);
		while(m--){
			scanf("%s",V);
			int l = strlen(V);
			loop(i,l) V[i] = tolower(V[i]);
			auto p = EqualRange(U,V,SA,L);
			if(p.yy - p.xx) puts("y");
			else puts("n");
		}
	}
	return 0;
}
