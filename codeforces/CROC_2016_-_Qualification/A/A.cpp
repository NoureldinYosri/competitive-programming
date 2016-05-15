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

int G[100][100],x,a,b;

bool can_even(int i,int j){
	if(i && G[i - 1][j]%2 == 0) return 0;
	if(j && G[i][j - 1]%2 == 0) return 0;
	return 1;	
}

bool can_odd(int i,int j){
	if(i && G[i - 1][j]%2 == 1) return 0;
	if(j && G[i][j - 1]%2 == 1) return 0;
	return 1;	
}


bool f(){
	int i = 0,j = 0;
	deque<int> even,odd;
	for(int i = 1;i <= x;i++){
		if(i & 1) odd.pb(i);
		else even.pb(i);
	}
	loop(i,a){
		loop(j,b){
			if(can_even(i,j) && !even.empty()) {
				G[i][j] = even.front();
				even.pop_front();
			}
			else if(can_odd(i,j) && !odd.empty()){
				G[i][j] = odd.front();
				odd.pop_front();
			}
		}
	}		
	return even.empty() && odd.empty();
}

bool g(){
	fill(&G[0][0],&G[a][0],0);
	int i = 0,j = 0,n = 1;
	while (j < b && n <= x){
		i = 0;
		while(i < a && n <= x){
			if(j && G[i][j - 1]%2 == n%2 && G[i][j - 1]){
				i++;
				continue;
			}
			if(i && G[i - 1][j] && G[i - 1][j]%2 == n%2){
				i++;
				continue;
			}
			G[i][j] = n++;
			i++;
		}
		j++;
	}
	return n == x + 1;
}

int main(){
	cin >> x >> a >> b;
	if(f()){
		loop(i,a) loop(j,b) printf("%d%s",G[i][j],(j == b - 1) ? "\n" : " ");
	}	
	else if(g()){
		loop(i,a) loop(j,b) printf("%d%s",G[i][j],(j == b - 1) ? "\n" : " ");
	}
	else puts("-1");
	return 0;
}
