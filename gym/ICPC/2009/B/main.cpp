/*#include <bits/stdc++.h>
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
#define popcnt(x) __builtin_popcount(x)
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


const int MAX = 3*20;

char error_message[4][20] = {"","output stuck at 0","output stuck at 1","output inverted"};

vi to[MAX];
char type[MAX];
int I1[MAX],I2[MAX];
int N,G,U,B;
int input[MAX][MAX],observation[MAX][MAX];
int fault[MAX],val[MAX],vis[MAX];

bool eval(int obs_idx){
	memset(vis,0,sizeof vis);
	queue<int> q;
	loop(i,N) {
		val[i] = input[obs_idx][i];
		q.push(i);
		vis[i] = 1;
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u >= N) {
			if(fault[u] == 1 || fault[u] == 2){
				if(fault[u] == 1) val[u] = 0;
				else val[u] = 1;
			}
			else{
				if(type[u] == 'u') val[u] = val[I1[u]];
				else if(type[u] == 'n' ) val[u] = !val[I1[u]];
				else{
					int x = val[I1[u]],y = val[I2[u]];
					if(type[u] == 'a') val[u] = x & y;
					else if(type[u] == 'o') val[u] = x | y;
					else if(type[u] == 'x') val[u] = x ^ y;
		//			else cerr << "fuck shit " << " " << u << " is " << type[u]  << endl;
				}
				if(fault[u] == 3) val[u] ^= 1;
			}
/*			cerr << "set " ;
			if(u < N + G) cerr << "gate #" << u  << " to " << val[u] << endl;
			else cerr << "output #" << u - N - G + 1 << " to " << val[u] << endl;
		}
		for(int v : to[u]){
			vis[v]++;
			if(vis[v] == 2) q.push(v);
			else if(vis[v] == 1 && (type[v] == 'n' || type[v] == 'u')) q.push(v);
	//		if(vis[v] > 2) cerr << "shit" << endl;
		}
	}
//	loop(i,U) if(!vis[i + N + G]) cerr << "fuck" << endl;
	loop(i,U)
		if(observation[obs_idx][i] != val[i + N + G])
			return 0;
	return 1;
}

bool check(){
	loop(i,B) if(!eval(i)) return 0;
	return 1;
}

int main(){
//	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d %d %d",&N,&G,&U) == 3 && !(N == 0 && G == 0 && U == 0);t++){
		loop(i,MAX) to[i].clear();
		loop(i,G){
			string i1,i2; cin >> type[i + N] >> i1;
			I1[i + N] = i1[1] - '1';
			if(i1[0] == 'g')  I1[i + N] += N;
			to[I1[i + N]].pb(i + N);
			if(type[i + N] != 'n'){
				cin >> i2;
				I2[i + N] = i2[1] - '1';
				if(i2[0] == 'g')  I2[i + N] += N;
				to[I2[i + N]].pb(i + N);
			}
		}
		loop(i,U) {
			int x; scanf("%d",&x);
			to[x + N - 1].pb(i + N + G);
			I1[i + N + G] = x + N - 1;
			type[i + N + G] = 'u';
		}
		scanf("%d",&B);
		loop(i,B){
			loop(j,N) scanf("%d",&input[i][j]);
			loop(j,U) scanf("%d",&observation[i][j]);
		}
		if(t != 1) puts("");
		printf("Case %d: ",t);
		vp cand;
		loop(i,G) {
			range(j,1,3) {
				fault[i + N] = j;
				if(check()) cand.pb(mp(i,j));
				fault[i + N] = 0;
			}
		}
		if(cand.empty() || check()) printf("No faults detected");
		else if(cand.size() != 1) printf("Unable to totally classify the failure");
		else {
			printf("Gate %d is failing; ",cand[0].xx + 1);
			printf(error_message[cand[0].yy]);
		}
	}
	return 0;
}
*/

