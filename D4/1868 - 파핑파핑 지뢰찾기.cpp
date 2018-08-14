#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
char board[301][301];
int cnt[301][301];
int visit[301][301];
int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int dy[8] = {0, 0, -1, 1, 1, -1, -1, 1};

bool isin(int x, int y)
{
    if(x >= 1 && y >= 1 && x <= N && y <= N) {
        return true;
    }
    else {
        return false;
    }
}
void check(int x, int y)
{
    int xx, yy, x1, y1;
    queue<pair<int, int> > q;
    q.push(make_pair(x, y));

    while(!q.empty()) {
        x1 = q.front().first; y1 = q.front().second;
        q.pop();

        for(int k = 0; k < 8; k++) {
            xx = x1 + dx[k]; yy = y1 + dy[k];
            if(isin(xx, yy) && cnt[xx][yy] != -1 && visit[xx][yy] == 0) {
                visit[xx][yy] = 1;
                if(cnt[xx][yy] == 0) {
                    q.push(make_pair(xx, yy));
                }

            }
        }

    }


}
void init()
{
    for(int i = 1; i <= 300; i++) {
        for(int j = 1; j <= 300; j++) {
            board[i][j] = 0;
            cnt[i][j] = 0;
            visit[i][j] = 0;
        }
    }
}
int main()
{
    int tc, ans;
    scanf("%d", &tc);

    for(int t = 1; t <= tc; t++) {
        ans = 0;
        init();

        scanf("%d", &N);

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                scanf(" %1c", &board[i][j]);
                if(board[i][j] == '*') {
                    cnt[i][j] = -1;
                }
            }
        }

        int xx, yy;
        //지뢰 갯수 처리
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(board[i][j] == '.') {
                    for(int k = 0; k < 8; k++) {
                        xx = i + dx[k]; yy = j + dy[k];
                        if(isin(xx, yy) && board[xx][yy] == '*') {
                            cnt[i][j]++;
                        }
                    }
                }
            }
        }
        //뭉치 세기
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(cnt[i][j] == 0 && visit[i][j] == 0) {
                    visit[i][j] = 1;
                    check(i, j);
                    ans++;
                }
            }
        }

        //떨어져 있는 애들 세기
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(cnt[i][j] != -1 && visit[i][j] == 0) {
                    ans++;
                }
            }
        }

        printf("#%d %d\n", t, ans);
    }

    return 0;
}
