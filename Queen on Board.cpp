#include <cstdio>
#include <cstring>
#define MOD 1000000007
int n, m;
char g[50][5];
int good[50][1 << 5];
int szg[50];
int block[50];
int memo[50][1 << 15];
int memo2[1 << 15];
int spread(int mask){
  if (memo2[mask] != -1) return memo2[mask];
  int nmask = 0;
  for (int i = 0; i < m; i++) {
    if (mask & 1 << 3 * i && i > 0) {
      nmask |= 1 << 3 * i - 3;
    }
    if (mask & 1 << 3 * i + 1) {
      nmask |= 1 << 3 * i + 1;
    }
    if (mask & 1 << 3 * i + 2 && i + 1 < m) {
      nmask |= 1 << 3 * i + 5;
    }
  }
  return memo2[mask] = nmask;
}
int solve (int x, int mask)
{
  if (x == n) return 1;
  mask &= ~block[x];
  if (memo[x][mask] != -1) return memo[x][mask];
  int ret = 0;
  for (int i = 0; i < szg[x]; i++) {
    if (!(good[x][i] & mask)) {
      ret += solve(x + 1, spread(good[x][i] | mask));
      if(ret >= MOD) ret -= MOD;
    }
  }
  return memo[x][mask] = ret;
}
int solve()
{
  for (int i = 0; i < n; i++) {
    block[i] = 0;
    int cmask = 0;
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        cmask |= 1 << j;
        block[i] |= 7 << 3 * j;
      }
    }
    szg[i] = 0;
    for (int j = 0; j < 1 << m; j++) {
      if ((j & cmask) == 0) {
        bool valid = true;
        for (int k = 0; k < m; k++) {
          if (j & 1 << k) {
            for (int kk = k + 1; kk < m && g[i][kk] != '#'; kk++) {
              if (j & 1 << kk) {
                valid = false;
              }
            }
          }
        }
        if (!valid) continue;
        int sp = 0;
        for (int k = 0; k < m; k++) {
          if (j & 1 << k) {
            sp |= 7 << 3 * k;
          }
        }
        good[i][szg[i]] = sp;
        szg[i]++;
      }
    }
  }
  memset(memo,255,sizeof memo);
  memset(memo2,255,sizeof memo2);
  return solve(0,0);
}
int main()
{
  int runs;
  scanf("%d",&runs);
  while (runs--) {
    scanf("%d%d",&n,&m);
    for (int i = 0;i < n;i++) scanf("%s",g[i]);
    int ret = solve();
    ret = (ret - 1 + MOD) % MOD;
    printf("%d\n",ret);
  }
  return 0;
}
