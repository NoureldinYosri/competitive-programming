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

const int MAX = 3e5 + 1e2;
int L[MAX],R[MAX],n,K;
int ord1[MAX],ord2[MAX];
int dont[MAX];
int yes[MAX];

int can(int q){
	memset(dont,0,sizeof dont);
	memset(yes,0,sizeof yes);
	ll l = L[ord1[0]],i = 0,j = 0,k = 0,ctr = 0;
	for(k = 0;k < n;k++){
		l = L[ord1[k]];
		while(i < n && L[ord1[i]] <= l) {
			if(!dont[ord1[i]]) {
				yes[ord1[i]] = 1;
				ctr++;
			}
			i++;
		}
		while(j < n && R[ord2[j]] < l + q - 1){
			if(yes[ord2[j]])	{
			//	cerr << "erase " << ord2[j] << endl;			
				yes[ord2[j]] = 0;
				ctr--;
			}
			else dont[ord2[j]] = 1;
			j++;
		}
//		cerr << sz(alive) << " " << K << endl;
		if(ctr >= K) return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&K);
	loop(i,n) scanf("%d %d",L + i,R + i),ord1[i] = ord2[i] = i;
	sort(ord1,ord1 + n,[](const int & a,const int & b){
		return L[a] < L[b];
	});
	sort(ord2,ord2 + n,[](const int & a,const int & b){
		return R[a] < R[b];
	});
	
	
	int s = 1,e = 2e9 + 10;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(can(m)) s = m;
		else e = m - 1;
	}	
	if(s == 1 && !can(1)){
		puts("0");
		loop(i,K) printf("%d%c",i+1," \n"[i==K-1]);
		return 0;
	}	
	printf("%d\n",s);
	can(s);
	vi ans;
	loop(i,n) if(yes[i]) ans.pb(i);
	auto it = ans.begin();
	assert(ans.size() >= K);
	loop(i,K) {
		printf("%d%c",*it + 1," \n"[i == K-1]);
		it++;
	}
	return 0;
}
