#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
 
int l = 1;
 
void ddaline(int x1, int y1, int x2, int y2)       //DDA Line Algorithm continues
{
 
    int s, dx, dy, m;
    float xi, yi, x, y;
 
    dx = x2 - x1;
    dy = y2 - y1;
 
    if (abs(dx) > abs(dy))
	s = abs(dx);
    else
	s = abs(dy);
 
    xi = dx / (float) s;
    yi = dy / (float) s;
 
    x = x1;
    y = y1;
 
    putpixel(x1 + 0.5, y1 + 0.5, 15);
 
    for (m = 0; m < s; m++) {
	x += xi;
	y += yi;
	putpixel(x + 0.5, y + 0.5, 15);
    }
}
 
 
void plotpoints1(int x, int y, int vx, int vy)
{
    putpixel(vx + x, vy + y, 15);                //putpixel plots a point in the color defined by color at (x,y)
    putpixel(vx - x, vy - y, 15);
    putpixel(vx - y, vy + x, 15);
    putpixel(vx + y, vy - x, 15);
    if (l % 20 == 0) {
	ddaline(vx - x, vy - y, vx + x, vy + y);
	ddaline(vx - y, vy + x, vx + y, vy - x);
    }
    l++;
}
 
void plotpoints2(int x, int y, int vx, int vy)
{
 
    putpixel(vx - x, vy + y, 15);
    putpixel(vx + x, vy - y, 15);
    putpixel(vx + y, vy + x, 15);
    putpixel(vx - y, vy - x, 15);
    if (l % 20 == 0) {
	ddaline(vx + x, vy - y, vx - x, vy + y);
	ddaline(vx - y, vy - x, vx + y, vy + x);
    }
    l++;
}
 
 
void mcircle(int vx, int vy, int r)                  //Mid point circle Algorithm calling
{
    int x = 0, y, p;
 
    y = r;
    p = 1 - r;
 
 
    while (x < y) {
	plotpoints1(x, y, vx, vy);
	x++;
	if (p < 0)
	    p += 2 * x + 1;
	else {
	    y--;
	    p += 2 * (x - y) + 1;
	}
    }
 
 
 
    x = y + 1;
    while (abs(x) > 0) {
	plotpoints2(x, y, vx, vy);
	x--;
	if (p >= 0)
	    p = p - 2 * x - 1;
	else {
	    y++;
	    p = p - 2 * (x - y) - 1;
	}
    }
}
 
void main()
{
    int gd = DETECT, gm = DETECT;
    int i = 0;
    initgraph(&gd, &gm, "");
 
    while (!kbhit()) {
	if (i > 640)
	    i = -200;
	cleardevice();
	mcircle(100 + (i++), 200, 100);
	delay(90);                                   // delay 
	i++;
    }
    getch();
}
