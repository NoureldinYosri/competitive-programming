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


vector<string> I[100];
int n;
char buffer[100];
vector<string> digits[13];
int state[7][21],state2[7][21];
char out[] = "?01W.";
vector<string> G[24*60];

void init(){
	digits[0] = vector<string>{".XX.","X..X","X..X","....","X..X","X..X",".XX."};
	digits[1] = vector<string>{"....","...X","...X","....","...X","...X","...."};
	digits[2] = vector<string>{".XX.","...X","...X",".XX.","X...","X...",".XX."};
	digits[3] = vector<string>{".XX.","...X","...X",".XX.","...X","...X",".XX."};
	digits[4] = vector<string>{"....","X..X","X..X",".XX.","...X","...X","...."};
	digits[5] = vector<string>{".XX.","X...","X...",".XX.","...X","...X",".XX."};
	digits[6] = vector<string>{".XX.","X...","X...",".XX.","X..X","X..X",".XX."};
	digits[7] = vector<string>{".XX.","...X","...X","....","...X","...X","...."};
	digits[8] = vector<string>{".XX.","X..X","X..X",".XX.","X..X","X..X",".XX."};
	digits[9] = vector<string>{".XX.","X..X","X..X",".XX.","...X","...X",".XX."};
	digits[10] = vector<string>(7,".");
	digits[11] = digits[10]; digits[11][2] = digits[11][4] = 'X';
	digits[12] = vector<string>(7,"....");
}

void append(int d,vector<string> & ret){
	loop(i,7)
		ret[i] += digits[d][i];
}

vector<string> t2s(int t){
	t %= 1440;
	if(!G[t].empty()) return G[t];
	int h = t / 60,m = t%60;
	vector<string> ret(7);
	if(h/10) append(h/10,ret);
	else append(12,ret);
	append(10,ret);
	append(h%10,ret);
	append(10,ret);
	append(11,ret);
	append(10,ret);
	append(m/10,ret);
	append(10,ret);
	append(m%10,ret);
	G[t] = ret;
	return ret;
}

bool check(int t,int i){
	auto g = t2s(t);
	loop(row,7) loop(col,21){
		if(I[i][row][col] == g[row][col]) continue;
		int b = g[row][col] == 'X';
		if(state[row][col] & (1 << b)) 	return 0;
	}
	return 1;
}

bool non(int r,int c){
	if(r == 1 && c == 0) return 0;
	if(r == 2 && c == 0) return 0;
	bool con = 1;	
	loop(t,24*60){
		auto g = t2s(t);
		con &= g[r][c] == '.';
	}
	return con;
}

int main(){
	init();
	scanf("%d",&n);
	loop(i,n) {
		I[i] = vector<string>(7);	
		loop(j,7) {
			scanf("%s",buffer);
			I[i][j] = string(buffer);
		}
	}

	loop(i,n) {
		loop(row,7) 
			loop(col,21){
				int b = I[i][row][col] == 'X';
				state[row][col] |= 1 << b;
			}
	}
	
	vi cand;
	loop(t,24*60){
		bool valid = 1;
		loop(i,n)
			valid &= check(t + i,i);
		if(valid) cand.pb(t);
	}	
	if(cand.empty()) puts("impossible");
	else{
		loop(row,7) {
			loop(col,21){
				if(non(row,col)) state2[row][col] = 4;
				else if(state[row][col] == 3) state2[row][col] = 3;
				else{
					state2[row][col] = state[row][col];
					for(int t : cand){
						int cnt[3] = {0};
						loop(i,n){
							auto g = t2s(t + i);
							int b = g[row][col] == 'X';
							cnt[1 << b]++;						
						}
						int siz = (cnt[1] != 0) + (cnt[2] != 0);
						int x = cnt[1] ? 1 : 2;
						if(siz == 1 && x == state[row][col]) {
							state2[row][col] = 0;
						}
					}
				}
			}
		}
		loop(row,7) {
			loop(col,21){
				//cerr << out[state2[row][col]];
				putchar(out[state2[row][col]]);
			}
			puts("");
			//cerr << endl;
		}
	}
	return 0;
}
