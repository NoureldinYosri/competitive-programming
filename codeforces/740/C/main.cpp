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
int LEFT[MAX],RIGHT[MAX],ord[MAX],n,m,mex = INT_MAX;
int A[MAX];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		scanf("%d %d",LEFT + i,RIGHT + i);
		ord[i] = i;
		mex = min(mex,RIGHT[i] - LEFT[i] + 1);
		LEFT[i]--,RIGHT[i]--;	
	}
	printf("%d\n",mex);
	if(mex == 1){
		loop(i,n) printf("0%c"," \n"[i==n-1]);
		return 0;
	}
	sort(ord,ord + m,[](const int & a,const int & b){
		return LEFT[a] < LEFT[b];
	});
	int e = 0,v = 0;
	loop(j,m){
		int i = ord[j];
		if(LEFT[i] >= e) {
			v = 0;
			for(e = LEFT[i];e <= RIGHT[i];e++){
				A[e] = v;
				v++;
				v %= mex;
			}
		}
		else{
			for(;e <= RIGHT[i];e++){
				A[e] = v;
				v++;
				v %= mex;
			}
			e = max(e,RIGHT[i]);
		}
	//	cerr << LEFT[i] << " " << RIGHT[i] << endl;
	//	prArr(A,n,int);
	}
	loop(i,n) printf("%d%c",A[i]," \n"[i==n-1]);
	return 0;
}
