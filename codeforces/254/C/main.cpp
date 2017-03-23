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

multiset<char> avail;
int ctr[128],ctr2[128];
char S[1 << 20],T[1 << 20];
int pos[1 << 20];

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin >> S >> T;
	for(char *p = T; *p ;p++) avail.insert(*p),ctr[*p]--;;
	int ans = 0;	
	for(char *p = S; *p ;p++) {
		ctr[*p]++;
		if(avail.find(*p) != avail.end()) avail.erase(avail.find(*p));
	}
	loop(i,128) ans += max(ctr[i],0);
	for(int i = strlen(S) - 1;i >= 0;i--)
		pos[i] = ++ctr2[S[i]];
	for(int i = 0,L = strlen(S);i < L;i++){
		char *p = S + i;
		if(ctr[*p] > 0 && *avail.begin() < *p){
			ctr[*p]--;
			*p = *avail.begin();
			avail.erase(avail.begin());
		}
		else if(ctr[*p] > 0 && pos[i] == ctr[*p]){
			ctr[*p]--;
			*p = *avail.begin();
			avail.erase(avail.begin());
		}
	}
	
	for(int i = strlen(S) - 1;i >= 0;i--){
		char *p = S + i;		
		if(ctr[*p] > 0){
			ctr[*p]--;
			*p = *avail.rbegin();
			avail.erase(avail.find(*p));
		}
	}
	cout << ans << endl;
	cout << S << endl;	
	cerr << S << endl;			
	return 0;
}
