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


// 0 1 2 3 4 5
vi I {0,1,2,3,4,5};
// 1 4 3 5
// 4 3 5 1
vi Rx {0,4,2,5,3,1};
// 0 5 2 4
// 5 2 4 0
vi Ry {5,1,4,3,0,2};
// 0 1 2 3
vi Rz {1,2,3,0,4,5};
vector<vi> R {Rx,Ry,Rz};
ll fix_sum;
int G;
vi demand;
ll dp[1024][1 << 6];
int cnt[1024],n;

bool share_side(int a,int b) {
    if(a > b) swap(a,b);
    if(a >= 4) return 0;
    if(a <= 3 && b >= 4) return 1;
    assert(b < 4);
    if(b == a + 1) return 1;
    if(a == 0 && b == 3) return 1;
    return 0;
}

bool valid(int msk) {
    int A[6],m = 0;
    for(int i = 0;i < 6;i++)
        if(msk & (1 << i))
            A[m++] = i;
    for(int i = 0;i < m;i++)
        for(int j = 0;j < i;j++)
            if(share_side(A[i],A[j]))
                return 0;
//    cerr << msk << " is valid" << endl;
    return 1;
}

ll solve(int cur,int msk) {
    if(msk == (1 << sz(demand)) - 1) return 1;
    if(cur == n) return 0;
    ll & ret = dp[cur][msk];
    if(ret != -1) return ret;
    ret = 0;
    int rem[6],m = 0;
    for(int i = 0;i < sz(demand);i++) {
        if(msk & (1 << i)) continue;
        rem[m++] = i;
    }
    
    for(int tmsk = 0;tmsk < (1 << m);tmsk++) {
        int omsk = 0,content = 0;
        for(int i = 0;i < m;i++)
            if(tmsk & (1 << i)) {
                omsk |= 1 << rem[i];
                content |= demand[rem[i]];
            }
        if(valid(content) && popcnt(content) <= cnt[cur]) ret += solve(cur + 1,msk | omsk);
    }
    
    return ret;
}

ll get_fix_sum(vi P) {
    demand.clear();
    vi vis(6,0);

    for(int i = 0;i < 6;i++) if(!vis[i]) {
        int j = i,msk = 0;
        while(!vis[j]) {
            msk |= 1 << j;
            vis[j] = 1;
            j = P[j];
        }
        demand.push_back(msk);
    }
    memset(dp,-1,sizeof dp);
    return solve(0,0);
}

vi apply(vi P,vi X) {
    vi Y(6);
    for(int i = 0;i < 6;i++)
        Y[i] = P[X[i]];
    return Y;
}

void work(){
	set<vi> vis;
    queue<vi> q;
    q.push(I);
    vis.insert(I);
    while(!q.empty()) {
        vi P = q.front(); q.pop();
        G++;
        fix_sum += get_fix_sum(P);
        for(vi r : R) {
            vi Q = apply(r,P);
            if(!vis.count(Q)) {
				q.push(Q);
				vis.insert(Q);
			}
			
        }
    }
}


int main() {
    scanf("%d",&n);
    for(int i = 0;i < n;i++) scanf("%d",cnt + i);
    work();
//    cerr << fix_sum << " " << G << " " << fix_sum/G << endl;
    assert(fix_sum%G == 0);
    cout << fix_sum/G << endl;
    return 0;
}
