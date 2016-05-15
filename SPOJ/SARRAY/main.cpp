#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

void sort(int k,int *SA,int L,int *Rank){
	int m = max(L,256) + 2; 
	int CTR[m],tmpSA[L];
	fill(CTR,CTR + m,0);
	loop(i,L) {
		int v = SA[i] + k; v = min(v,L - 1);
		CTR[Rank[v] + 1]++;
	}
	loop(i,m - 1) CTR[i + 1] += CTR[i];
	loop(i,L){
		int v = SA[i] + k; v = min(v,L - 1);
		tmpSA[CTR[Rank[v]]++] = SA[i];
	}
	copy(tmpSA,tmpSA + L,SA);
}

void reRank(int k,int *SA,int L,int *Rank){
	int helper[L];
	helper[SA[0]] = 0;
	loop(i,L){
		if(!i) continue;
		helper[SA[i]] = helper[SA[i - 1]];
		if(Rank[SA[i]] == Rank[SA[i - 1]]){
			int v = SA[i] + k;     v = min(v,L - 1);
			int u = SA[i - 1] + k; u = min(u,L - 1);
			helper[SA[i]] += Rank[u] != Rank[v]; 
		}
		else helper[SA[i]]++;
	}
	copy(helper,helper + L,Rank);
}

void printSA(char *T,int *SA,int L){
	loop(i,L) cerr << T + SA[i] << endl;
}

void buildSA(char *T,int *SA,int *Rank){
	int L = strlen(T); T[L++] = '$'; T[L] = '\0';
	loop(i,L) SA[i] = i,Rank[i] = T[i];
	sort(0,SA,L,Rank);
	//prArr(SA,L,int);
	for(int k = 1;k < L;k <<= 1){
		sort(k,SA,L,Rank);
		sort(0,SA,L,Rank);
		reRank(k,SA,L,Rank);
	//	prArr(SA,L,int);
	}	
}

const int MAX = 1 << 20;
char line[MAX],U[MAX],V[MAX];
int SA[MAX],Rank[MAX];

int BS(char *P){
	//cerr << line << " " << P << " " << strcmp(line,P) << endl;
	int s = 0,e = strlen(line) + 1;
	while(e - s){
		int m = (s + e) >> 1;
		if(strcmp(line + SA[m],P) >= 0) e = m;
		else s = m + 1;
	}
	//cerr << s << endl;
	return s;
}

int main(){
	scanf("%s %s %s",line,U,V); 
	int L = strlen(line);
	buildSA(line,SA,Rank);
	//printSA(line,SA,L + 1);
	
	line[L] = 0; 
	int sx = BS(U); U[strlen(U) - 1]++; int ex = BS(U);
	int sy = BS(V); V[strlen(V) - 1]++; int ey = BS(V);
	V[strlen(V) - 1]--;
	
	int m = strlen(V),n = strlen(U);
	vi VV;
	for(int i = sy;i < ey;i++) VV.pb(SA[i] + m);
	sort(all(VV));
	
	set<string> out;
	for(;sx < ex;sx++) {
		int p = SA[sx]; string s = "";
		for(auto v : VV){
			if(p > v) continue;
			while(p < v) s += line[p++];
			if(p - SA[sx] < max(n,m)) continue;
			out.insert(s);
		//	cerr << SA[sx] << " " << v << " " << s << endl;
		//	cerr << s << endl;
		}	
	}
	//print(out,string);
	printf("%lu\n",out.size());
	return 0;
}
