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


int m,n;
vector<vi> A,B;

bool validate(vector<vi> & B) {
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++) {
			int v = B[i][j] - 1,x = v/n,y = v%n;
			if(i) {
				int u = B[i - 1][j] - 1;
				int ox = u/n,oy = u%n;
				if(ox == x && abs(y-oy) == 1) {
					cerr << i+1 << " " << j+1 << endl;
					return 0;
				}
				if(oy == y && abs(x-ox) == 1) {
					cerr << i+1 << " " << j+1 << endl;
					return 0;
				}
			}
			if(j){
				int u = B[i][j-1] - 1;
				int ox = u/n,oy = u%n;
				if(ox == x && abs(y-oy) == 1) {
					cerr << i+1 << " " << j+1 << endl;
					return 0;
				}
				if(oy == y && abs(x-ox) == 1) {
					cerr << i+1 << " " << j+1 << endl;
					return 0;
				}
			}
		}
	return 1;
}

void brute_force(){
	vi ord(m*n);
	B = vector<vi>(m,vi(n));
	loop(i,m*n) ord[i] = i + 1;
	do{
		loop(i,m) loop(j,n) B[i][j] = ord[i*n + j];
		if(validate(B)){
			puts("YES");
			loop(i,m) loop(j,n) printf("%d%c",B[i][j]," \n"[j==n-1]);
			return;
		}
	}while(next_permutation(all(ord)));
	puts("NO");
}

void plan1(vi & V) {
	vi R(sz(V));
	int z = 0;
	for(int i = 1;i < sz(V);i += 2) R[z++] = V[i];
	for(int i = 0;i < sz(V);i += 2) R[z++] = V[i];
	V.swap(R);
}


void plan2(vi & V) {
	vi R(sz(V));
	int e = 0;
	for(int i = 0;i < sz(V);i += 2) R[e++] = V[i];
	reverse(R.begin(),R.begin() + e);
	int s = e;
	for(int i = 1;i < sz(V);i += 2) R[e++] = V[i];
	reverse(R.begin() + s,R.begin() + e);
	V.swap(R);
}

void plan3(vi & V){
//	return plan2(V);
	vi R(sz(V));
	int e = 0;
	for(int i = 1;i < sz(V);i += 2) R[e++] = V[i];
	rotate(R.begin(),R.begin() + 1,R.begin() + e);
	int s = e;
	for(int i = 0;i < sz(V);i += 2) R[e++] = V[i];
	rotate(R.begin() + s,R.begin() + e - 1,R.begin() + e);
	V.swap(R);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> m >> n;
	A = vector<vi>(m,vi(n,0));
	for(int i = 0,ctr = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			A[i][j] = ++ctr;
	if(m <= 3 && n <= 3) brute_force();
	else if(m > 3){
		puts("YES");
		vi V(m);
		for(int j = 0;j < n;j++) {
			for(int i = 0;i < m;i++) V[i] = A[i][j];
			if(j%2 == 0) {
				if(m%2 == 0) plan2(V);
				else plan3(V);
			}
			else plan1(V);
			for(int i = 0;i < m;i++) A[i][j] = V[i];
		}
		loop(i,m) loop(j,n) printf("%d%c",A[i][j]," \n"[j==n-1]);
		assert(validate(A));
	}
	else {
		puts("YES");
		vi V(n);
		for(int i = 0;i < m;i++) {
			for(int j = 0;j < n;j++) V[j] = A[i][j];
			if(i%2 == 0) {
				if(n%2 == 0) plan2(V);
				else plan3(V);
			}
			else plan1(V);
			for(int j = 0;j < n;j++) A[i][j] = V[j];
		}
		loop(i,m) loop(j,n) printf("%d%c",A[i][j]," \n"[j==n-1]);
		assert(validate(A));

	}
	return 0;
}
