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

void modify(char a,char & b,char c){
	if(a != b && b != c) return ;	
	if(a > c) swap(a,c);
	if(a > 'a') b = 'a';
	else if(c > 'b') b = 'b';
	else b = 'c';
}
char s[1 << 20];

int main(){
	scanf("%s",s);
	int L = strlen(s);
	range(i,1,L - 2) {
		if(s[i - 1] == s[i] && s[i] == s[i + 1]) modify(s[i - 1],s[i],s[i + 1]);
	}
	range(i,1,L - 2) {
		modify(s[i - 1],s[i],s[i + 1]);
	}
	if(L == 2) {
		if(s[0] == s[1]){
			if(s[0] == 'a') s[1] = 'b';
			else s[0] = 'a';
		}
	}
	cerr << s << endl;
	return 0;
}
