#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

char line[1 << 20];
int n,l,r;

bool pos(int d,bool c = 0){
	ll s = 0;
	loop(i,n){
		int j = i;
		s = 0;
		while(j < n && s < l&& j - i + 1 <= d){
			s = s * 10 + line[j] - '0';
			j++;
		}
		while(j < n && s < r){
			s = s * 10 + line[j] - '0';
			j++;
		}
		if(s > r) return 0;
		if(s < l) return 0;
		if(c){
			while(i < j) putchar(line[i++]);
			if(j != n) putchar(',');
		}		
		i = j - 1;
	}
	return 1;
}

int main(){
	scanf("%d %d %s",&l,&r,line);  
	n = strlen(line);
	int d = 1;
	while(d <= 5){
		if(pos(d)) break;
		d ++;
	}
	if(pos(d)) pos(d,1);	
	else putchar('-'),putchar('1');
	puts("");
	return 0;
}
