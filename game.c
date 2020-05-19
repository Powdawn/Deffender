#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#define High 100
#define Width 100
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN0x50
#define ESC 27 //0x1b
#define BREAKSPACE 0x20

void keycontrol();
void setCursorPosition(int x, int y);
void setColor(int color);
void timmerb();
void timmere();
void drawimage();

int score=0, skill=3;
int life=3;
int px=600, py=600;//plane
int ex[1000];//normal enemy
int ey[1000];
int esx[1000];//fast suiside enemy
int esy[1000];
int bx[1000];//bullet
int by[1000];
int clean[1000];//reset roll
int hx[10] = {10,20,30,40,50,60,70,80,90};//hostage
int hy[10] = {95,95,95,95,95,95,95,95,95};


void timmerb()//timmer for each 0.5s
{
    for (int i=0; i<1000; i++)
    {
        unsigned char q,w,e;
        for(q=15;q>0;q--)
        for(w=202;w>0;w--)
        for(e=81;e>0;e--);
        bx[i] = px;//creat new bullet
        by[i] = py;
        for(int o=0; o<i; o++)
        {
            if(by[o]!=0)
            by[o] = by[o]-2;//bullet move up
            if(ey[o]!=0)
            ey[o] = ey[o]+2;//normal enemy move down
            if(esy[o]!=0)
            esy[o] = esy[o]+4;//special enemy move down
            if(by[o]<=0)//remove bullet out of the screen
            {
                by[o]=clean[o];
                bx[o]=clean[o];
            }
            if(ey[o]>=100)//remove enemy out of the screen
            {
                ey[o]=clean[o];
                ex[o]=clean[o];
            }
            if(esy[o]>=100)//remove special enemy out of the screen
            {
                esy[o]=clean[o];
                esx[o]=clean[o];
            }     
        }   
    }
}

void timmere()//timmer for each 1.5s
{
    for (int p=0; p<1000; p++)
    {
        int n=0, s=0;
        unsigned char q,w,e;
        for(q=15;q>0;q--)
        for(w=202;w>0;w--)
        for(e=81;e>0;e--);
        for(q=15;q>0;q--)
        for(w=202;w>0;w--)
        for(e=81;e>0;e--);
        for(q=15;q>0;q--)
        for(w=202;w>0;w--)
        for(e=81;e>0;e--);
        int r=rand()%2;//creat random enemy
        if(r==0)
        {
            n++;
            ex[n]=rand()%100;
            ey[n]=1;
        }
        else if (r==1)
        {
            s++;
            esx[s]=rand()%100;
            esy[s]=1;
        }
        for(int i=0;i<10; i++)//hostage moves up after being captured
        {
            if(hy[i]<95)
            hy[i]=hy[i]-3;
        }
    }
}

void drawimage()// draw image for each element
{
    setColor(3);
    setCursorPosition(px, py);
    puts("★");

    for (int i =0; i<1000; i++)
    {
        if (bx[i]!=0)
        {
            setColor(0XC);
            setCursorPosition(bx[i], by[i]);
            puts("◆");
        }
        if (ex[i]!=0)
        {
            setColor(6);
            setCursorPosition(ex[i], ey[i]);
            puts("■");
        }
        if (esx[i]!=0)
        {
            setColor(6);
            setCursorPosition(esx[i], esy[i]);
            puts("■");            
        }
        if (hx[i]!=0)
        {
            setColor(6);
            setCursorPosition(hx[i], hy[i]);
            puts("★");
        }
    }
}

/*void delay500ms(void)
{
    unsigned char i,j,k;
    for(i=15;i>0;i--)
    for(j=202;j>0;j--)
    for(k=81;k>0;k--);
}*/

void keyControl () // key control
{
    char input;
    while((input=getch())!=0x1b)
    {
        if((input==0x48)&&py>1)
            py--;
        if((input==0x50)&&py<95)
            py++;
        if((input==0x4b)&&px>1)
            px--;
        if((input==0x4d)&&px<100)
            px++;
        if((input==0x20)&&skill>0)
        {
            skill--;
            for(int i=0; i<1000; i++)
            {
                while(ex[i]!=0)
                {
                    score = score + 2000;
                    ex[i] = clean[i];
                    ey[i] = clean[i];
                }
                while(esx[i]!=0)
                {
                    score = score + 3000;
                    esx[i] = clean[i];
                    esy[i] = clean[i];
                }                
            }
        }    
    }
}

int main(void)
{
    for(int i=0; i<1000; i++)
    {
        for(int o=0; o<1000; o++)
        {
            if((ey[i]-by[o]<=3)&&(ex[i]==bx[o]))//bullet kill normal enemy
            {
                score = score + 2000;
                ex[i]=clean[i];
                ey[i]=clean[i];
                bx[o]=clean[o];
                by[o]=clean[o];
            }
            if((esy[i]-by[o]<=5)&&(esx[i]==bx[o]))// kill special enemy
            {
                score = score + 3000;
                esx[i]=clean[i];
                esy[i]=clean[i];
                bx[o]=clean[o];
                by[o]=clean[o];
            }
            if(((hx[o]-ex[i]<=2)||(ex[i]-hx[o]<=2))&&(ey[i]>=95))// hostage captured
            {
                score = score - 5000;
                ex[i]=clean[i];
                ey[i]=clean[i];
                hy[o] --;
            }
            if(((hx[o]-esx[i]<=2)||(esx[i]-hx[o]<=2))&&(esy[i]>=95))//special kill the hostage directly
            {
                score = score - 5000;
                esx[i]=clean[i];
                esy[i]=clean[i];
                hy[o]=clean[i];
                hx[o]=clean[i];
                life--;
            }
            if (by[i]-hy[o]<=2&&bx[i]==hx[o])//reset hostage position after meet the bullet
            {
                hy[o]= 95;
                score = score+4000;
                bx[o]=clean[o];
                by[o]=clean[o];
                break;
            }
        }
        if ((hy[i]<=3)&&(hy[i]!=0))// life-- for moveing too high
        {
            life --;
            hx[i]=clean[i];
            hy[i]=clean[i];
        }
    }

    if(life = 0)
    {
        system("pause");
    }
}

void setCursorPosition(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);}
void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color) ;
    }
