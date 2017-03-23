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

const int MAX = 1111;
int n,m;
map<string,int> F;
string S[MAX];
pi pos[MAX];
char buffer[MAX];
char s1[MAX],s2[MAX],s3[MAX];
double dist[MAX][MAX];
vector<string> Q[MAX];
int id[MAX],rid[MAX];

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d",&n,&m);

		F.clear();
		loop(i,n){
			scanf("%s %d %d",buffer,&pos[i].xx,&pos[i].yy);
			S[i] = string(buffer);
			F[S[i]] = i;
		}

		set<string> S;
		loop(i,m){
			scanf("%s heard %s firing before %s",s1,s2,s3);
			Q[i].clear();
			Q[i].pb(string(s1));	
			Q[i].pb(string(s2));	
			Q[i].pb(string(s3));	
			S.insert(Q[i][1]);
			S.insert(Q[i][2]);
		}
		int ctr = 0;
		for(auto s : S){
			id[F[s]] = ctr;
			rid[ctr] = F[s];
			++ctr;
		}	
		double oo = 1e8 ;
		n = ctr;
		loop(i,n) loop(j,n) dist[i][j] = (i != j)*oo;
		loop(i,m){
			int x = F[Q[i][0]],y = F[Q[i][1]],z = F[Q[i][2]];
			double d1 = hypot(pos[x].xx - pos[y].xx,pos[x].yy - pos[y].yy);
			double d2 = hypot(pos[x].xx - pos[z].xx,pos[x].yy - pos[z].yy);
			dist[id[y]][id[z]] = min(dist[id[y]][id[z]],d2 - d1);
			// - d1;
//			dist[id[y]][id[z]] = d1 - d2;
//			cerr << x << " " << y << " " << z << endl;
//			prp(pos[x]); prp(pos[y]) prp(pos[z]); cerr << endl;
//			cerr << id[y] << " " << id[z] << " " << d1 << " " << d2 << endl;
		}
		loop(k,n) loop(i,n) loop(j,n) dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
		bool done = 0;	
		loop(i,n) if(dist[i][i] < 0){
			puts("IMPOSSIBLE");
			done = 1;
			break;
		}
		if(done) continue;
		//loop(i,n) {prArr(dist[i],n,double);};
		vi aux;
		loop(i,n) {
			bool c = 1;
			loop(j,n) if(i != j) c &= dist[i][j] < 0;
			if(c) aux.pb(i);
		}
		loop(i,n) loop(j,i) if(dist[i][j] > 0 && dist[j][i] > 0) aux.clear();
		loop(i,n) loop(j,i) if(dist[i][j] < 0 && dist[j][i] < 0) aux.clear();
		if(sz(aux) != 1) puts("UNKNOWN");
		else{
			vector<double> T(n);
			int s = aux[0];
			T[s] = 0;
			loop(i,n) T[i] = T[s] - dist[s][i];
			vi ord(n);
			loop(i,n) ord[i] = i;
			sort(all(ord),[T](const int & a,const int & b){
				return T[a] < T[b];
			});
			loop(i,n) printf("%s%c",::S[rid[ord[i]]].c_str()," \n"[i == n-1]);
		}
	}	
	return 0;
}
