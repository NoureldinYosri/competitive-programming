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

const int MAX = 50;
int X[MAX],Y[MAX],n;
int S[MAX],I[MAX],m;
vi nxt[MAX][MAX][2];
bool used[MAX];

int ccw(int i,int j,int k){
	int x1 = X[j] - X[i],y1 = Y[j] - Y[i];
	int x2 = X[k] - X[i],y2 = Y[k] - Y[i];
	return x1*y2 - x2*y1;
} 

bool intersect(int a,int b,int c,int d,int f = 1){
	int x = ccw(a,b,c),y = ccw(a,b,d);
	x = (x > 0) ? 1 : -1;
	y = (y > 0) ? 1 : -1;
	if(x == y) return 0;
	return f ? intersect(c,d,a,b,0) : 1;
}

bool bt(){
    if(m == n) return 1;
    int i = S[m - 2],j = S[m - 1];
    for(int x : nxt[i][j][I[m - 2]])
        if(!used[x]){
			bool cond = 1;
			for(int i = 0;i < m - 2 && cond;i ++)
				cond = !intersect(S[i],S[i + 1],S[m - 1],x);
			if(!cond) continue;
            S[m++] = x;
            used[x] = 1;
            if(bt()) return 1;
            m--;
            used[x] = 0;
        }
    return 0;
}


int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	string s; cin >> s;
	for(int i = 0;i < n - 2;i++)
		I[i] = s[i] == 'L';
	
	for (int i = 0;i < n;i++)
		for(int j = 0;j < n;j++) 
		    for (int k = 0; k < n; k++)
		        if (i != j && j != k && i != k) 
		            nxt[i][j][ccw(j , k, i) > 0].pb(k);
	
	bool found = 0;
    for(int i = 0;i < n && !found;i++)
        for(int j = 0;j < n && !found;j++) if(i != j){
            S[0] = i;
            S[1] = j;
            used[i] = used[j] = 1;
            m = 2;
            found = bt();
            used[i] = used[j] = 0;
        }
    if (!found) cout << -1 << endl;
    else{
        for(int i = 0;i < n;i++) printf("%d%c",S[i] + 1," \n"[i==n-1]);
		for(int i = 0;i < n - 2;i++) cerr << I[i] << " " << ccw(S[i + 1],S[i + 2],S[i]) << endl;
    }

	
	
	
	return 0;
}
