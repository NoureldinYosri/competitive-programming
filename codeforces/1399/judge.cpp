//HEADER FILES AND NAMESPACES

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  
#include <ext/pb_ds/tree_policy.hpp>   
using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>; 

// DEFINE STATEMENTS
const long long infty = 1e18;
#define num1 1000000007
#define num2 998244353
#define REP(i,a,n) for(ll i=a;i<n;i++)
#define REPd(i,a,n) for(ll i=a; i>=n; i--)
#define pb push_back
#define pob pop_back
#define f first
#define s second
#define fix(f,n) std::fixed<<std::setprecision(n)<<f
#define all(x) x.begin(), x.end()
#define M_PI 3.14159265358979323846
#define epsilon (double)(0.000000001)

typedef long long ll;
typedef vector<long long> vll;
typedef pair<long long, long long> pll;
typedef vector<pair<long long, long long>> vpll;
typedef vector<int> vii;

// DEBUG FUNCTIONS 
#ifndef ONLINE_JUDGE

template<typename T>
void __p(T a) {
    cout<<a;
}
template<typename T, typename F>
void __p(pair<T, F> a) {
    cout<<"{";
    __p(a.first);
    cout<<",";
    __p(a.second);
    cout<<"}";
}
template<typename T>
void __p(std::vector<T> a) {
    cout<<"{";
    for(auto it=a.begin(); it<a.end(); it++)
        __p(*it),cout<<",}"[it+1==a.end()];
}
template<typename T>
void __p(std::set<T> a) {
    cout<<"{";
    for(auto it=a.begin(); it!=a.end();){
        __p(*it); 
        cout<<",}"[++it==a.end()];
    }

}
template<typename T>
void __p(std::multiset<T> a) {
    cout<<"{";
    for(auto it=a.begin(); it!=a.end();){
        __p(*it); 
        cout<<",}"[++it==a.end()];
    }
}
template<typename T, typename F>
void __p(std::map<T,F> a) {
    cout<<"{\n";
    for(auto it=a.begin(); it!=a.end();++it)
    {
        __p(it->first);
        cout << ": ";
        __p(it->second);
        cout<<"\n";
    }
    cout << "}\n";
}

template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
    __p(a1);
    __p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
    cout<<name<<" : ";
    __p(arg1);
    cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
    int bracket=0,i=0;
    for(;; i++)
        if(names[i]==','&&bracket==0)
            break;
        else if(names[i]=='(')
            bracket++;
        else if(names[i]==')')
            bracket--;
    const char *comma=names+i;
    cout.write(names,comma-names)<<" : ";
    __p(arg1);
    cout<<" | ";
    __f(comma+1,args...);
}
#define trace(...) cout<<"Line:"<<__LINE__<<" ", __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...)
#define error(...)
#endif

// DEBUG FUNCTIONS END 

// CUSTOM HASH TO SPEED UP UNORDERED MAP AND TO AVOID FORCED CLASHES
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());  // FOR RANDOM NUMBER GENERATION

ll mod_exp(ll a, ll b, ll c)
{
    ll res=1;   a=a%c;
    while(b>0)
    {
        if(b%2==1)
            res=(res*a)%c;
        b/=2;
        a=(a*a)%c;
    }
    return res;
}
ll mymod(ll a,ll b)
{
        return ((a%b)+b)%b;
}
ll gcdExtended(ll,ll,ll *,ll *);
ll modInverse(ll a, ll m) 
{ 
        ll x, y; 
        ll g = gcdExtended(a, m, &x, &y); 
        g++;   //this line was added just to remove compiler warning
        ll res = (x%m + m) % m;
        return res;
} 
ll gcdExtended(ll a, ll b, ll *x, ll *y) 
{ 
        if (a == 0) 
        { 
                *x = 0, *y = 1; 
                return b; 
        } 
        ll x1, y1; 
        ll gcd = gcdExtended(b%a, a, &x1, &y1);
        *x = y1 - (b/a) * x1; 
        *y = x1; 
        return gcd; 
}
struct node
{
    vector<pair<ll,pll>> adj;
    ll par;
    ll cost;
    ll weight;
    ll leaves;
};
void dfs(node N[], ll x, ll par=-1)
{
    N[x].par = par;
    N[x].leaves = 0;
    bool isleaf = true;
    for(auto &p: N[x].adj)
    {
        if(p.f!=par)
        {
            N[p.f].cost = p.s.s;
            N[p.f].weight = p.s.f;
            dfs(N, p.f, x);
            isleaf = false;
            N[x].leaves += N[p.f].leaves;
        }
    }
    if(isleaf) N[x].leaves++;
}
set<pll> s[2];
ll sum = 0, n, S, cost = 0;
void operate(ll x, node N[])
{
    pll p = *(s[x].rbegin());
    s[x].erase(p);
    // trace("erasing", p);
    sum -= p.f;
    N[p.s].weight/=2;
    p.f = N[p.s].leaves * ((N[p.s].weight+1)/2);
    s[x].insert(p);
    // trace("inserting", p);

    // p.f/=2;
    // s[x].insert(p);
    cost += x+1;
}
void doit(node N[])
{
    if(s[0].empty()) operate(1, N);
    else if(s[1].empty()) operate(0, N);
    else
    {
        pll x1 = *(s[0].rbegin());
        pll x2 = *(s[1].rbegin());
        ll n1 = x1.f;
        ll w = N[x1.s].weight;
        // trace(n1, ((w+1)/2)*N[x1.s].leaves, x1, x2);
        assert(n1 == ((w+1)/2)*N[x1.s].leaves);
        if(n1 >= sum - S)
        {
            operate(0, N);
            return;
        }
        // trace(n1);
        if(s[0].size()==1)
        {
            n1 += N[x1.s].leaves * (w/2 - w/4); 
        }
        else
        {
            n1 += max(N[x1.s].leaves*(w/2-w/4), (*(++(s[0].rbegin()))).f);
        }
        ll n2 = x2.f;
        // trace(n1, n2);
        // cout << n1 << " " << n2 << "\n";
        if(n1>=n2)
        {
            // cout << n1 << "\n";
            operate(0, N);
        }
        else
        {
            // cout << n2 << "\n";
            operate(1, N);
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    REP(i,0,t)
    {
        s[0].clear();
        s[1].clear();
        sum=0; cost=0;
        cin>>n>>S;
        node N[n+1];
        REP(i,0,n-1)
        {
            ll a,b,c,d;
            cin>>a>>b>>c>>d;
            N[a].adj.pb({b,{c,d}});
            N[b].adj.pb({a,{c,d}});
        }
        dfs(N,1);
        REP(i,2,n+1)
        {
            //  trace(i, N[i].leaves, N[i].weight);
            s[N[i].cost-1].insert({N[i].leaves * ((N[i].weight+1)/2), i});
            sum += N[i].leaves * N[i].weight;
        }
        while(S < sum)
        {
            // trace(sum, S, cost);
            doit(N);
        }
        cout << cost << "\n";
    }
    return 0;
}

/*
4
10 120
3 1 8 1
5 2 10 1
8 1 5 1
2 1 6 1
7 2 8 1
10 7 7 1
6 4 10 1
4 3 10 2
9 7 9 1
10 22
6 5 1 1
3 2 5 1
10 8 4 1
8 7 6 2
7 6 6 1
9 8 9 1
5 3 3 1
2 1 7 1
4 3 9 2
10 54
4 1 7 1
9 2 7 1
5 1 8 2
2 1 2 1
3 1 1 2
8 1 7 1
6 2 4 2
7 2 10 2
10 3 1 2
10 109
3 1 1 2
7 2 10 1
8 1 4 2
5 1 5 1
6 2 9 1
4 1 8 1
9 4 1 2
10 2 2 2
2 1 10 1
*/