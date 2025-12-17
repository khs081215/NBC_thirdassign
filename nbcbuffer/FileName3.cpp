#include<iostream>

using namespace std;


const int TILE_EMPTY = 0;   // 빈칸
const int TILE_PLAYER = 1;   // 플레이어
const int TILE_MON1 = 2;   // 몬스터 A
const int TILE_MON2 = 3;   // 몬스터 B
const int TILE_MON3 = 4;   // 몬스터 C
const int TILE_BOSS = 5;   // 보스

const char DISP_EMPTY = '-';
const char DISP_PLAYER = 'P';
const char DISP_MON1 = 'a';
const char DISP_MON2 = 'b';
const char DISP_MON3 = 'c';
const char DISP_BOSS = 'B';

// 시야 밖(#) 은 별도로 사용
const char DISP_OUTSIDE = '#';

const int WIDTH = 20;
const int HEIGHT = 10;

int map[WIDTH * HEIGHT] =
{
    // 0행
    0,0,0,0,0,  2,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,
    // 1행
    0,0,3,0,0,  0,0,0,0,0,  0,0,0,0,4,  0,0,0,0,0,
    // 2행
    0,0,0,0,0,  0,0,2,0,0,  0,0,0,0,0,  0,0,0,0,0,
    // 3행
    0,0,0,0,0,  0,0,0,0,3,  0,0,0,0,0,  0,0,0,0,0,
    // 4행
    0,0,0,0,0,  0,0,0,1,0,  0,0,0,0,0,  0,0,2,0,0,
    // 5행
    0,0,0,0,0,  4,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,
    // 6행
    0,3,0,0,0,  0,0,0,0,0,  0,0,0,2,0,  0,0,0,0,0,
    // 7행
    0,0,0,0,0,  0,0,4,0,0,  0,0,0,0,0,  0,3,0,0,0,
    // 8행
    0,0,0,0,0,  0,0,0,0,0,  0,2,0,0,0,  0,0,0,0,0,
    // 9행
    0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0,  0,0,0,5,0,
};

void main()
{
    int nowx=0, nowy=0;
    int bminx, bmaxx, bminy, bmaxy;
    bool flag = false;
    int buffer,ibuffer;
    int i, j;
    bool fail = false;
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (map[WIDTH * i + j] == TILE_PLAYER)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
    nowx = i;
    nowy = j;
    while (true)
    {
        //시야가 보이는 범위
        bminx = nowx - 2;
        bmaxx = nowx + 2;
        bminy = nowy - 2;
        bmaxy = nowy + 2;
        if (bminx < 0)
        {
            bminx = 0;
            bmaxx = 4;
        }
        if (bminy < 0)
        {
            bminy = 0;
            bmaxy = 4;
        }
        if (bmaxx > HEIGHT - 1)
        {
            bmaxx = HEIGHT - 1;
            bminx = HEIGHT - 5;
        }
        if (bmaxy > WIDTH - 1)
        {
            bmaxy = WIDTH - 1;
            bminy = WIDTH - 5;
        }
        //전체 맵 출력
        for (i = 0; i < HEIGHT; i++)
        {
            for (j = 0; j < WIDTH; j++)
            {
                if (bminx > i || bmaxx<i || bminy>j || bmaxy < j)
                {
                    cout << DISP_OUTSIDE<<" ";
                }
                else
                {
                    buffer = map[i*WIDTH+j];
                    switch (buffer)
                    {
                    case TILE_EMPTY:
                        cout << DISP_EMPTY << " ";
                        break;
                    case TILE_PLAYER:
                        cout << DISP_PLAYER << " ";
                        break;
                    case TILE_MON1:
                        cout << DISP_MON1 << " ";
                        break;
                    case TILE_MON2:
                        cout << DISP_MON2 << " ";
                        break;
                    case TILE_MON3:
                        cout << DISP_MON3 << " ";
                        break;
                    case TILE_BOSS:
                        cout << DISP_BOSS << " ";
                        break;
                    }
                    
                }
            }
            cout << endl;
        }

        while (true)
        {

            cout << "1)상 2)하 3)좌 4)우" << endl;
            cin >> ibuffer;
            switch (ibuffer)
            {
            case 1:
                if (nowx == 0)
                {
                    fail = true;
                    break;
                }
                if (map[(nowx - 1) * WIDTH + nowy] != TILE_EMPTY)
                {
                    fail = true;
                    break;
                }
                map[(nowx)*WIDTH + nowy] = TILE_EMPTY;
                nowx -= 1;
                map[(nowx)*WIDTH + nowy] = TILE_PLAYER;
                break;
            case 2:
                if (nowx == HEIGHT - 1)
                {
                    fail = true;
                    break;
                }
                if (map[(nowx + 1) * WIDTH + nowy] != TILE_EMPTY)
                {
                    fail = true;
                    break;
                }
                map[(nowx)*WIDTH + nowy] = TILE_EMPTY;
                nowx += 1;
                map[(nowx)*WIDTH + nowy] = TILE_PLAYER;
                break;
            case 3:
                if (nowy == 0)
                {
                    fail = true;
                    break;
                }
                if (map[(nowx) * WIDTH + (nowy-1)] != TILE_EMPTY)
                {
                    fail = true;
                    break;
                }
                map[(nowx)*WIDTH + nowy] = TILE_EMPTY;
                nowy -= 1;
                map[(nowx)*WIDTH + nowy] = TILE_PLAYER;
                break;
            case 4:
                if (nowy == WIDTH - 1)
                {
                    fail = true;
                    break;
                }
                if (map[(nowx)*WIDTH + (nowy + 1)] != TILE_EMPTY)
                {
                    fail = true;
                    break;
                }
                map[(nowx)*WIDTH + nowy] = TILE_EMPTY;
                nowy += 1;
                map[(nowx)*WIDTH + nowy] = TILE_PLAYER;
                break;
            }

            if (fail)
            {
                cout << "벽이나 몬스터에 가로막혀 갈 수 없다." << endl;
                fail = false;
            }
            else
            {
                system("cls");
                break;
            }

        }
    }




}
