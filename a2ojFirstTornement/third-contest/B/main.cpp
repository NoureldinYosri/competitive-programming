#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100;
int A,B;
int C,D;
char G1[MAX][MAX],G2[MAX][MAX];
char G[MAX][MAX];
int dx[] = {0,1},dy [] = {1,0};

bool place(int x,int y){
	loop(i,A) loop(j,B) G[i][j] = G1[i][j];
	loop(i,C) loop(j,D) {
		if(G2[i][j] != '.' && G1[i+x][j+y] != '.')
			return 0;
		if(G2[i][j] != '.') G[i+x][j+y] = G2[i][j];
	}
	return 1;
}

bool inside(int i,int j,int x,int y) {
	if(i < x || i >= x + C) return 0;
	if(j < y || j >= y + D) return 0;
	return 1;
}

ll get_score(int x,int y){
	int score = 0;
//	loop(i,A) puts(G[i]);
	loop(i,A) loop(j,B) {
		loop(k,2) {
			int nx = i + dx[k],ny = j + dy[k];
			if(nx < 0 || nx >= A || ny < 0 || ny >= B) continue;
			if(G[i][j] == '.' || G[nx][ny] == '.') continue;
			if(G[i][j] != G[nx][ny]) continue;
			if(G1[i][j] == '.' && G1[nx][ny] == '.') continue;
			if(G1[i][j] != '.' && G1[nx][ny] != '.') continue;


			if(inside(i,j,x,y) || inside(nx,ny,x,y))
				score++;
		}
	}
	return score;
}

void trim(){
	string E (D,'.');
	deque<string> dq;
	loop(i,C) dq.pb(string(G2[i]));
	while(!dq.empty() && dq.front() == E) dq.pop_front();
	while(!dq.empty() && dq.back() == E) dq.pop_back();
	if(dq.empty()){
		C = D = 1;
		return;
	}
	C = sz(dq);
	loop(i,C) strcpy(G2[i],dq[i].c_str());
	dq.clear();
	loop(j,D) {
		string s ;
		loop(i,C) s.pb(G2[i][j]);
		dq.pb(s);
	}
	E = string(C,'.');
	while(!dq.empty() && dq.front() == E) dq.pop_front();
	while(!dq.empty() && dq.back() == E) dq.pop_back();
	D = sz(dq);
	loop(i,C) loop(j,D) G2[i][j] = dq[j][i];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&A,&B);
	loop(i,A) scanf("%s",G1[i]);
	scanf("%d %d",&C,&D);
	loop(i,C) scanf("%s",G2[i]);
	trim();
	ll ans = -1;
	for(int i = 0;i <= A-C;i++)
		for(int j = 0;j <= B-D;j++)
			if(place(i,j))
				ans = max(ans,get_score(i,j));
	cout << ans << endl;
	return 0;
}
