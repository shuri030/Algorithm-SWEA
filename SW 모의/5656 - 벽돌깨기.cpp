#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

int N, W, H;
int board[17][14];
int temp[17][14];
int wb[17][14];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int ans = INT_MAX / 2;
int brick_cnt;
int per[4];

bool isin(int x, int y)
{
    if(x < 0 || y < 0 || x >= H || y >= W)
        return false;
    return true;

}
void shoot(int num)
{
    queue<pair<int, int> > q;

    for(int i = 0; i < H; i++) {
        if(temp[i][num] != 0) {
            //해당 벽돌이 1이면 본인만 터지고 함수 종료
            if(temp[i][num] == 1) {
                temp[i][num] = 0;
                return;
            }
            //1이 아니면 큐에 넣는다
            else {
                wb[i][num] = 1;
                q.push({i, num});
                break;
            }

        }
    }

    int x, y, xx, yy, val;

    //BFS로 터지기
    while(!q.empty()) {
        x = q.front().first; y = q.front().second;
        q.pop();
        val = temp[x][y];

        for(int k = 0; k < 4; k++) {
            for(int l = val - 1; l >= 1; l--) {
                xx = x + (dx[k] * l); yy = y + (dy[k] * l);
                if(isin(xx, yy) && temp[xx][yy] > 0 && wb[xx][yy] == 0) {
                    wb[xx][yy] = 1;
                    if(temp[xx][yy] > 1) {
                        q.push({xx, yy});
                    }
                }
            }
        }
    }

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(wb[i][j] == 1) {
                temp[i][j] = 0;
                wb[i][j] = 0;
            }
        }
    }

}
void count_brick()
{
    int cnt = 0;

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(temp[i][j] != 0) {
                cnt++;
            }
        }
    }

    if(cnt < ans) {
        ans = cnt;
    }
}
void down()
{
    for(int i = 0; i < W; i++) {
        for(int j = H - 1; j >= 0; j--) {
            if(temp[j][i] == 0) {
                int t = j - 1;
                int flag = 0;

                while(t >= 0) {
                    if(temp[t][i] != 0) {
                        flag = 1;
                        temp[j][i] = temp[t][i];
                        temp[t][i] = 0;
                        break;
                    }
                    t--;
                }
                if(flag == 0) { //위에 붕 뜬게 없으니 나가
                    break;
                }

            }
        }
    }


}
void DFS(int n)
{
    if(n >= N) {
        //copy
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                temp[i][j] = board[i][j];
            }
        }

        for(int i = 0; i < N; i++) {
            shoot(per[i]); //터지기
            down(); //밑으로 당겨
        }

        count_brick(); //벽돌 세
        memset(wb, 0, sizeof(wb));

        //답 0일때
        if(ans == 0) {
            return;
        }

        return;
    }

    //순열 만들기
    for(int i = 0; i < W; i++) {
        per[n] = i;
        DFS(n + 1);
        if(ans == 0) { return; } //벽돌 없으면 리턴
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    for(int tc = 0; tc < t; tc++) {

        scanf("%d %d %d", &N, &W, &H);

        //input
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                scanf("%d", &board[i][j]);
            }
        }

        DFS(0);

        printf("#%d %d\n", tc + 1, ans);
        memset(board, 0, sizeof(board));
        memset(temp, 0, sizeof(temp));

        ans = INT_MAX / 2;
    }

    return 0;
}
