#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

class BipartiteMatching {
private:
 vector<vector<int> > adjmat;
 vector<int> matched;
 vector<int> visited;

 int N;
 int M;

 bool augment(int node, int side) {
   visited[side*N+node] = 1;
   if (!side) {
     // left side
     for (int i = 0; i < M; i++) {
       if (adjmat[node][i] == 1 && !visited[i+N]) {
         // check for right-side unmatched node
         if (matched[i+N] == -1) {
           adjmat[node][i] = 2;
           matched[i+N] = matched[node] = i;
           return true;
         }
         // otherwise dfs more
         bool f = augment(i, 1-side);
         if (f) {
           // augmenting path found
           adjmat[node][i] = 2;
           matched[i+N] = matched[node] = i;
           return true;
         }
       }
     }
     return false;
   } else {
     // right side
     for (int i = 0; i < N; i++) {
       if (adjmat[i][node] == 2 && !visited[i]) {
         bool f = augment(i, 1-side);
         if (f) {
           // augmenting path found
           adjmat[i][node] = 1;
           return true;
         }
       }
     }
     return false;
   }
   return false;
 }

public:
 BipartiteMatching(int _N, int _M) : N(_N), M(_M) {
   // initialise the data structures
   adjmat = vector<vector<int> >(N, vector<int>(M, 0));
   visited = vector<int>(N+M,0);
   matched = vector<int>(N+M,0);
 }

 void Reset() {
   for (int i = 0; i < adjmat.size(); i++) {
     fill(adjmat[i].begin(),adjmat[i].end(),0);
   }
 }

 void AddEdge(int i, int j) {
   adjmat[i][j] = 1;
 }

 int maxMatching() {
   int res = 0;
   bool valid = true;
   // all vertices are unmatched at the start
   for (int i = 0; i < N + M; i++) matched[i] = -1;
   // while there is at least 1 valid augmenting path keep
   // iterating
   while (valid) {
     valid = false;
     for (int i = 0; i < N; i++) {
       if (matched[i] == -1) {
         fill(visited.begin(),visited.end(),0);
         bool f = augment(i,0);
         if (f) valid = true;
       }
     }
   }
   // count the number of matches
   for (int i = 0; i < N; i++) {
     if (matched[i] != -1) { res++; }
   }
   return res;
 }
};

class point {
public:
 int x;
 int y;
 point() { }
 point(int _x, int _y) : x(_x), y(_y) { }
};

bool operator<(const point& lhs, const point& rhs) {
 if (lhs.x != rhs.x) return lhs.x < rhs.x;
 if (lhs.y != rhs.y) return lhs.y < rhs.y;
 return false;
}

int main(int argc, char** argv) {
 ios_base::sync_with_stdio(false);
 int numTest = 0;
 cin >> numTest;
 int p, t, s, c;
 BipartiteMatching* bpm = new BipartiteMatching(406,206);
 while (numTest-- && cin >> p >> t >> s >> c) {
   vector<point> people;
   vector<point> taxi;
   // people
   int x, y;
   while (p-- && cin >> x >> y) {
     people.push_back(point(x,y));
   }
   while (t-- && cin >> x >> y) {
     taxi.push_back(point(x,y));
   }
   // make graph
   bpm->Reset();
   for (int i = 0; i < people.size(); i++) {
     for (int j = 0; j < taxi.size(); j++) {
       long long dist = abs(people[i].x-taxi[j].x)+
         abs(people[i].y-taxi[j].y);
       if (dist*200 <= c*s) {
         // can reach
         bpm->AddEdge(i,j);
       }
     }
   }
   // calculate maximum bipartite matching
   cout << bpm->maxMatching() << "\n";
 }
 return 0;
}

