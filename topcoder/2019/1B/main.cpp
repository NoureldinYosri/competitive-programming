#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

#define DEBUG
#include "A.cpp"
#include "B.cpp"
#include "C.cpp"


int main(int argc,char **argv){
//	vi H{50, 77, 24, 86, 98, 84, 42, 70, 88, 78, 73, 17, 76, 68, 64, 65, 40, 77, 33, 87, 11, 23, 78, 20, 8, 74, 44, 95, 94, 78, 27, 88, 71, 40, 11, 98, 82, 85, 79, 89, 31, 67, 41, 61, 71, 62, 74, 77, 86, 36};//{3, 4, 11, 6, 2, 2, 2, 5, 7, 7, 10, 8, 5, 8, 1, 4};
//	cout << EllysSki().getMax(H) << endl;

//	cout << EllysTeleport().getMax(11,9,17,9,7,13,23) << endl;
	vi P {5, 6, 2, 4, 7, 2, 2, 3, 3, 6, 1, 3, 6, 3, 7, 5, 1, 2, 3, 4, 6, 5, 6, 3, 2, 5, 3, 3, 5, 6};
	cout << EllysPearls().getMin(30,7,P) << endl;
	return 0;
}
