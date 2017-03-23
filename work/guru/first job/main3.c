#include <stdio.h>
#define MAXM 20
#define MAXN 20

char G[MAXM][MAXN + 1];
int dist_to_nearst_white[MAXM][MAXN + 1];
int dist_to_nearst_black[MAXM][MAXN + 1];
int queue[MAXM*MAXN + 1];
int m,n;
int dx[] = {-1,0,1,0},dy[] = {0,-1,0,1};

void bfs(char ch,int dist[MAXM][MAXN + 1]){
	int i,j;
	int start = 0,end = 0;
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
		{
			if(G[i][j] == ch) queue[end++] = i*n + j,dist[i][j] = 1;
		}
	while(start < end){
		int u = queue[start++];
		int x = u/n,y = u%n;
		for(i = 0;i < 4;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if(dist[nx][ny]) continue;
			if(G[nx][ny] != '.') continue;
			dist[nx][ny] = 1;
			queue[end++] = nx*n + ny;
		}
	}
}

int main(){
	scanf("%d %d",&m,&n);	
	int i,j;
	for(i = 0;i < m;i++)
		scanf("%s",G[i]);
	bfs('W',dist_to_nearst_white);
	bfs('B',dist_to_nearst_black);
	int white = 0,black = 0;
	for(i = 0;i < m;i++)
		for(j = 0;j < n;j++){
			if(G[i][j] != '.') continue;
			if(dist_to_nearst_white[i][j] && !dist_to_nearst_black[i][j]) white++;
			if(!dist_to_nearst_white[i][j] && dist_to_nearst_black[i][j]) black++;	
		}
	printf("%d %d\n",white,black);
}
