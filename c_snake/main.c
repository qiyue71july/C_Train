//Gluttonous Snake
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<time.h>

#define U 1
#define D 2
#define L 3
#define R 4

void showPos(int x,int y);
void createMap();
void createSnake();
void updateSnake();
void createFood();
int eatSelf();
void crossWall();
void gamecircle();
int status;

typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE* next;
    int speed;
}snake;

snake* head;
snake* it;
snake* food;

void showPos(int x,int y)//设置光标位置
{
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void createMap()
{
    int i;
    for(i=0;i<58;i+=2)//打印上下边框
    {
        showPos(i,0);
        printf("*");
        showPos(i,26);
        printf("*");
    }
    for(i=0;i<26;i++)//打印左右边框
    {
        showPos(0,i);
        printf("*");
        showPos(56,i);
        printf("*");
    }
}

void createSnake()
{
    snake* tail = (snake*)malloc(sizeof(snake));
    tail->x = 20;
    tail->y = 20;
    int i;
    for(i = 1;i < 4;i++)
    {
        head = (snake*)malloc(sizeof(snake));
        head->next = tail;
        head->x = 20 + 2*i;
        head->y = 20;
        tail = head;
    }
    while(tail!=NULL)
    {
        showPos(tail->x,tail->y);
        printf("@");
        tail=tail->next;
    }
}

int eatSelf()
{
    snake *self;
    self=head->next;
    while(self!=NULL)
    {
        if(self->x==head->x && self->y==head->y)
        {
            return 1;
        }
        self=self->next;
    }
    return 0;
}

void crossWall()
{
    if(head->x == 56 || head->x == 0 || head->y == 0 || head->y == 26)
    {
        status = 0;
    }
}

void updateSnake()
{
    snake * nexthead;
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        nexthead->next=head;
        head=nexthead;
        it=head;
        if(nexthead->x==food->x && nexthead->y==food->y)
        {
            while(it!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            createFood();
        }
        else
        {
            while(it->next->next!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            showPos(it->next->x,it->next->y);
            printf(" ");
            free(it->next);
            it->next=NULL;
        }
    }
    if(status==D)
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
        nexthead->next=head;
        head=nexthead;
        it=head;
        if(nexthead->x==food->x && nexthead->y==food->y)
        {
            while(it!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            createFood();
        }
        else
        {
            while(it->next->next!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            showPos(it->next->x,it->next->y);
            printf("  ");
            free(it->next);
            it->next=NULL;
        }
    }
    if(status==L)
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        it=head;
        if(nexthead->x==food->x && nexthead->y==food->y)
        {

            while(it!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            createFood();
        }
        else
        {
            while(it->next->next!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            showPos(it->next->x,it->next->y);
            printf("  ");
            free(it->next);
            it->next=NULL;
        }
    }
    if(status==R)
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        it=head;
        if(nexthead->x==food->x && nexthead->y==food->y)
        {
            while(it!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            createFood();
        }
        else
        {
            while(it->next->next!=NULL)
            {
                showPos(it->x,it->y);
                printf("@");
                it=it->next;
            }
            showPos(it->next->x,it->next->y);
            printf("  ");
            free(it->next);
            it->next=NULL;
        }
    }
    crossWall();
    if(eatSelf()==1)
    {
        status = 0;
    }
}

void createFood()
{
    snake *food_1;
    food_1=(snake*)malloc(sizeof(snake));
    srand((unsigned)time(NULL));

    int x = 0;
    int y = 0;
    while(!(x%2 == 0 && x > 10 && x < 56 && y > 10 && y < 26))
    {
        x = rand();
        y = rand();
    }
    food_1->x = x;
    food_1->y = y;

    it=head;
    while(it->next != NULL)
    {
        if(it->x==food_1->x && it->y==food_1->y) //判断蛇身是否与食物重合
        {
            free(food_1);
            createFood();
        }
        it=it->next;
    }

    showPos(food_1->x,food_1->y);
    printf("#");
    food=food_1;
}

void gamecircle()
{
    status=R;
    while(1)
    {
        if(GetAsyncKeyState(VK_UP) && status!=D)
        {
            status=U;
        }
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)
        {
            status=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
        {
            status=R;
        }

        Sleep(500);
        updateSnake();
    }
}

int main(void)
{
    createMap();
    createSnake();
    createFood();
    gamecircle();
    return 0;
}

