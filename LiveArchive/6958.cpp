
#include <algorithm>
#include <cstdio>
using namespace std;

const int nmax = 14;

long long Dis[nmax][nmax];

long long Trip1[720], Trip2[720]; 

int tryallperms (int n, int p, int s, long long Trip[])
{	// Base case
	if (s == 0)
	{	Trip[0] = Dis[0][p];
		return 1;
	}
	int m = 0, i, k = 0;
	int Point[nmax/2];
	long long d = 0;
	// Dissect subset
	for (i = 1; i < n; i++)
		if (s & (1<<i))
			Point[k++] = i;
	do
	{	d = Dis[0][Point[0]];
		for (i = 1; i < k; i++)
			d += Dis[Point[i-1]][Point[i]];
		d += Dis[Point[k-1]][p];
		Trip[m++] = d;
	}
	while (next_permutation(Point, Point+k));
	return m;
}

int solve(){
  int n, i, j, m1, m2, p, q, s;
  long long L;
  fill(Trip1,Trip1 + 720,0);
  fill(Trip2,Trip2 + 720,0);
  if(scanf("%d %lld", &n, &L) != 2) return 1;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%lld", &Dis[i][j]);
  // 0 = start point, p = mid point
  for (p = 1; p < n; p++)
    { q = (p==1 ? 2 : 1); // Arbitrary other point
      // Try all subsets of size n/2-1 that do not involve 0, p or q
      for (s = 0; s < (1<<n); s += 2)
	if (!(s & (1<<p)) && !(s & (1<<q)) && __builtin_popcount(s) == n/2-1)
	  {	m1 = tryallperms(n, p, s, Trip1);
	    // Invert subset (ignoring 0 and p)
	    m2 = tryallperms(n, p, s ^ ((1<<n)-2) ^ (1<<p), Trip2);
	    // See if two trip lengths combined give L
	    sort(Trip1, Trip1 + m1);
	    sort(Trip2, Trip2 + m2);
	    for (i = 0, j = m2-1; i < m1 && j >= 0;)
	      {	if (Trip1[i] + Trip2[j] < L)
		  i++;
		else if (Trip1[i] + Trip2[j] > L)
		  j--;
		else
		  {	printf("possible\n");
		    return 0;
		  }
	      }
	  }
    }
    printf("impossible\n");
    return 0;
}

int main()
{	
  while(!solve());
  return 0;
}

