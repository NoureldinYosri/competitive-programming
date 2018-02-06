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

const int MAX = 7000;
int A[MAX],B[MAX],n;
vi S1,S2;
int tA[MAX],tB[MAX];

void readS(vi & S){
	int m; scanf("%d",&m);
	S = vi(m);
	loop(i,m) scanf("%d",&S[i]);
}

void update(int *A,int *B,vi & S,int *T) {
    for (int i = 1;i < n;i++) {
        T[i] = A[i];
        bool anyLose = 0,win = 1;
        for (int x : S) {
            int j = (i + x)%n;
            if (B[j] == -1) anyLose = 1;
            win &= B[j] == 1;
        }
        if (anyLose) T[i] = 1;
        else if (win) T[i] = -1;
    }
//    print(S,int);
//    prArr(A,n,int);
//    prArr(T,n,int);
//    cerr << endl;
}


void PRINT(int *A) {
	char out [3] [10]  = {"Lose","Win","Loop"};

	for(int i = 1;i < n;i++)
		printf("%s%c",out[A[i]]," \n"[i==n-1]);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	readS(S1);
	readS(S2);

	loop(i,n) A[i] = B[i] = -2;
	A[0] = B[0] = -1;
	while(1) {
		update(A,B,S1,tA);
		update(B,A,S2,tB);
		bool change = 0;
		loop(i,n) {
			change |= A[i] != tA[i];
			change |= B[i] != tB[i];
			A[i] = tA[i];
			B[i] = tB[i];
		}
		if(!change) break;
	}
	loop(i,n) {
		if(A[i] == 0) A[i] = 2;
		if(A[i] == -1) A[i] = 0;
		if(A[i] == -2) A[i] = 2;
	}
	loop(i,n) {
		if(B[i] == 0) B[i] = 2;
		if(B[i] == -1) B[i] = 0;
		if(B[i] == -2) B[i] = 2;
	}

	PRINT(A);
	PRINT(B);
	return 0;
}
