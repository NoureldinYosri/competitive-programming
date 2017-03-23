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

int G[200][200],deg[200];
string name[200],message[200];
char buffer[200];
int n,m;
int done[200],assign[200];
map<string,int> M;

void read(){
	scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer);
		name[i] = string(buffer);
		M[name[i]] = i;
	}
	scanf("%d\n",&m);	
	loop(i,m){
		char *p = buffer;
		for(*p = getchar();*p != '\n';){
			p++;
			*p = getchar();
		}
		*p = 0;
		message[i] = string(buffer);
	}
}

void process(){
	char del[] = ".,!? :";
	bool first = 1;
	loop(i,m){
		strcpy(buffer,message[i].c_str());
		char *token = strtok(buffer,del);
		if(buffer[0] != '?'){
			string tmp = string(buffer);
			assert(M.find(tmp) != M.end());
			deg[i] = 1;
			G[i][M[tmp]] = 1;  
		}
		else{
			deg[i] = n;
			fill(G[i],G[i] + n,1);
			vector<string> V;
			for(;token;token = strtok(0,del)){
				string tmp = string(token);
				if(M.find(tmp) != M.end()){
					V.pb(tmp);				
				}
			}
			sort(all(V));
			V.resize(unique(all(V)) - V.begin());
			for(auto tmp : V){
				deg[i]--;
				G[i][M[tmp]] = 0;	
			}
		}
	}
}

bool solve(){
	memset(done,0,sizeof done);
	set<pi> S;
	loop(i,m) S.insert(mp(deg[i],i));
	while(!S.empty()){
		int u = S.begin()->yy; S.erase(S.begin());
		int k = -1;
		loop(i,n) if(G[u][i]) {
			k = i;
			break;
		}
		if(k == -1) return 0;
		assign[u] = k;
		done[u] = 1;
		if(u && !done[u-1]){
			if(G[u - 1][k]){
				if(deg[u-1] == 1) return 0;
				S.erase(mp(deg[u-1],u-1));
				deg[u - 1]--;
				G[u - 1][k] = 0;
				S.insert(mp(deg[u-1],u-1));
			}
		}
		if(u != m-1 && !done[u+1]){
			if(G[u + 1][k]){
				if(deg[u+1] == 1) return 0;
				S.erase(mp(deg[u+1],u+1));
				deg[u + 1]--;
				G[u + 1][k] = 0;
				S.insert(mp(deg[u+1],u+1));
			}
		}
	}
	loop(i,m){
		if(message[i][0] != '?') printf("%s\n",message[i].c_str());
		else{
			printf("%s%s\n",name[assign[i]].c_str(),message[i].c_str() + 1);
		}
	}
	return 1;
}

int main(){
	int T; 
	scanf("%d",&T);
	while(T--){
		memset(G,0,sizeof G);
		memset(deg,0,sizeof deg);
		M.clear();
		read();
		process();
		if(!solve()) puts("Impossible");
	}
	
	
	return 0;
}

