// line, circle, setcolor,initgraph
#include <graphics.h>
// sin, cos, M_PI
#include <math.h>
// getch
#include <conio.h>
// delay
#include <dos.h>
// time, localtime
#include <time.h>
// NULL
#include <stdio.h>
// system
#include <stdlib.h>

// color time bars
#define SEC_COLOR            BLUE
#define MIN_COLOR            GREEN
#define HOUR_COLOR           RED
#define HOUR_POINTS_COLOR    RED
#define SEC_MIN_POINTS_COLOR YELLOW
// center point
#define CENTER_POINT_COLOR   MAGENTA
#define CENTER_POINT_SIZE    8
// dont change this
#define SHOW 1
#define HIDE 0

void draw_clock(float cx, float cy, float angle,
    float radius, float delay_t,int state){

    // get time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // x,y position for circles and lines
    float x, y;

    // highlight point, for counter
    int h_point, i, hour;

    // convert hour 24h to 12h
    hour = tm.tm_hour;
    hour += (tm.tm_hour>=12)?-12:0;

    if(state){
    // sec color
    setcolor(SEC_COLOR);
    outtextxy(10, 10, "second color");
    // min color
    setcolor(MIN_COLOR);
    outtextxy(10, 30, "minute color");
    // hour color
    setcolor(HOUR_COLOR);
    outtextxy(10, 50, "hour color");
    }

    // draw clock
    for(i=-90; i < 270 ;i+=6){
    x = cx + cos(i* M_PI / 180) * angle;
    y = cy + sin(i* M_PI / 180) * angle;

    // draw clock with time
    if(state){
        // dont hightlight this point
        h_point = 0;

        // center point
        setcolor(CENTER_POINT_COLOR);
        circle(cx, cy, radius+4);

        // default bar color
        setcolor(BLACK);

        // time lines
        // hour line; slice circle to 360/30 = 12
        if(hour == (i + 90) / 30.0){
        setcolor(HOUR_COLOR);
        h_point = 1;
        }
        // min line; slice circle to 360/6 = 60
        if(tm.tm_min == (i + 90) / 6){
        setcolor(MIN_COLOR);
        h_point = 1;
        }
        // sec line; slice circle to 360/6 = 60
        if(tm.tm_sec == (i + 90) / 6){
        setcolor(SEC_COLOR);
        h_point = 1;
        }

        // draw lines
        line(cx, cy, x, y);

        // circles; if 360 % 30 == 0 its a hour point
        if((i+90)%30==0){
        if(!h_point) // highlight this point if a bar in this section
            setcolor(HOUR_POINTS_COLOR);
        circle(x, y, radius+5);
        }
        else {
        if(!h_point) // highlight this point if a bar in this section
            setcolor(SEC_MIN_POINTS_COLOR);
        circle(x, y, radius+1);
        }

    } else {
        // animations section
        // lines
        setcolor(RED);
        line(cx, cy, x, y);
        // circles
        setcolor(CYAN);
        circle(x, y, radius);
    }
    // its like sleep function
    delay(delay_t);
    }
}


void main(){
    float x, y, cx, cy, angle, radius;
    int  graphdriver = DETECT, graphmode;

    initgraph(&graphdriver, &graphmode, "..\\BGI");
    // center screen
    cx = getmaxx() / 2.0;
    cy = getmaxy() / 2.0;

    angle = 200;

    radius = 1;

    // clock style animation
    draw_clock(cx, cy, angle, radius, 20, HIDE);

    // draw clock
    draw_clock(cx, cy, angle, radius, 10, SHOW);
    // update clock ; if you press any key program stoped.
    while(!kbhit())
    draw_clock(cx, cy, angle, radius, 0, SHOW);

    // wait for a key and exit
    getch();
    closegraph();
}
