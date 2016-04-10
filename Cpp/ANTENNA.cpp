#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include<iostream.h>
#include<process.h>

int index=0;
int clockwise[]={0x08,0x04,0x02,0x01};
int anticlock[]={0x01,0x02,0x04,0x08};
float pos=0.0;

void clockwise1step()
{
	delay(350);
	outportb(0x378,clockwise[index]);
	if(index==3)
		index=0;
	else
		index++;
}

void anticlockwise1step()
{
	delay(350);
	outportb(0x378,anticlock[index]);
	if(index==3)
		index=0;
	else
		index++;
}

void main()
{
	clrscr();
	int ch,direction=0,i;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	settextstyle(7,0,3);
	char buf[100]={0};
	setcolor(RED);
	outtextxy(40,20,"WELCOME TO ANTENNA SYSTEM");
	outtextxy(40,60,"PRESS ANY KEY TO EXIT.....");
	setcolor(WHITE);
	outtextxy(10,300,"PRESS ANY KET TO START THE SYSTEM.....");
	getch();
	settextstyle(7,0,1);
	setcolor(GREEN);
	while(1)
	{
		for(i=0;i<40;i++)
		{
			if(kbhit())
			{
				getch();
				exit(0);
			}
			ch=(int)inportb(0x379);
			if(ch==127)
			{
				if(direction==0)
				{
					clockwise1step();
					pos=pos+9;
					gotoxy(1,10);
					cleardevice();
					sprintf(buf,"position: %f",pos);
					outtextxy(10,50,buf);
					line(320,240,320+90*cos((pos-90)*3.1415/180),240+90*sin((pos-90)*3.1415/180));
					circle(320,240,100);
					if(pos>=360)
						pos=0;
				}
				else
				{
					if(pos==0)
						pos=360;
					anticlockwise1step();
					pos=pos-9;
					gotoxy(1,10);
					cleardevice();
					sprintf(buf,"position: %f",pos);
					outtextxy(10,50,buf);
					line(320,240,320+90*cos((pos-90)*3.1415/180),240+90*sin((pos-90)*3.1415/180));
					circle(320,240,100);
				}
			}
			else
			{
				gotoxy(1,10);
				//cleardevice();
				//delay(500);
				sprintf(buf,"position: %f",pos);
				outtextxy(10,50,buf);
				line(320,240,320+90*cos((pos-90)*3.1415/180),240+90*sin((pos-90)*3.1415/180));
				circle(320,240,100);
				i--;
			}
		}
		direction=!direction;
	}
}
