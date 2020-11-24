#include "grader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOR(i,n) for (int i=0;i<n;i++)

static char foo[1024][1024];
static int sx, sy;


static int best;
static int dist[1024][1024];
static int bfs(int x, int y, int xx, int yy) {
 memset(dist, 1, sizeof(dist));
 int q[40000], nq=0, hq=0;
 q[nq++] = x; q[nq++] = y;
 //q.push(x); q.push(y);
 dist[x][y]=0;
 while (nq>hq) {
  //x=q.front(); q.pop();
  x = q[hq++];
  //y=q.front(); q.pop();
  y = q[hq++];
  if (dist[x][y] > best) best = dist[x][y];
#define X(i,j) if (i>=0&&j>=0&&i<sx&&j<sy&&dist[i][j]>dist[x][y]+1&&foo[i][j]=='.') \
                dist[i][j]=dist[x][y]+1, q[nq++]=i, q[nq++]=j; else
  X(x-1,y);
  X(x+1,y);
  X(x,y-1);
  X(x,y+1);
 }
 return best;
}
static int whichmaze;
void rox() {
 FOR(i,sizeof(mazes)/sizeof(*mazes)) {
  if (mazes[i].sx == sx && mazes[i].sy == sy) {
   FOR(x,sx) FOR(y,sy)
    if ((mazes[i].maze[x][y] == 'X') != (foo[x][y] == 'X'))
     goto miss;
   //printf("field.%X\n", i+1);
   whichmaze = 1+i;
   return;
  }
  miss:;
 }
 exit(91);
}

int main() {
 while (gets(foo[sx++]));
 sx--;
 sy = strlen(foo[0]);
 //vector<int> exit;
 int xit[40000], nx=0;
 rox();
 FOR(i,sx) FOR(j,sy) if (foo[i][j] == '.' && (!i||!j||i==sx-1||j==sy-1))
  //exit.push_back(i), exit.push_back(j);
  xit[nx++]=i, xit[nx++]=j;
 if (nx < 2) exit(91);
 if (nx > 2) exit(91);
 int ans = bfs(xit[0],xit[1],0,0);
 if (ans > 100000) exit(91);
 printf("OK %d %i\n",whichmaze, ans+1);
 return 0;
}
