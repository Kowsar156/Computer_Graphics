/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 */
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <ctime>

using namespace std;
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */

GLdouble pendulum_center_x = 0, pendulum_center_y = -0.3;
GLdouble pendulum_bob_x, pendulum_bob_y;
GLdouble pendulum_theta = 0, pendulum_d_theta = 3;
GLdouble pendulum_l = 0.6;

GLdouble initial_hour, initial_minute, initial_second;
GLdouble hour_angle, minute_angle, second_angle;

GLdouble clock_center_x = 0, clock_center_y = 0.35;

GLdouble second_hand_x, second_hand_y;
GLdouble minute_hand_x, minute_hand_y;
GLdouble hour_hand_x, hour_hand_y;

GLdouble second_hand_l = 0.5;
GLdouble minute_hand_l = 0.4;
GLdouble hour_hand_l = 0.3;

void showTime(){
    GLdouble clock_start_l, clock_end_l = 0.55;
    GLdouble clock_start_x, clock_start_y;
    GLdouble clock_end_x, clock_end_y;
    glColor3d(1,1,1);
    glLineWidth(2);
    for (int angle = 0; angle < 360; angle += 6)
    {
        clock_start_l = 0.5;
        if (angle%5 == 0)
        {
            clock_start_l = 0.4;
        }
        clock_start_x = clock_center_x + clock_start_l*sin(angle*M_PI/180.0);
        clock_start_y = clock_center_y + clock_start_l*cos(angle*M_PI/180.0);

        clock_end_x = clock_center_x + clock_end_l*sin(angle*M_PI/180.0);
        clock_end_y = clock_center_y + clock_end_l*cos(angle*M_PI/180.0);

        glBegin(GL_LINES);
            glVertex2d(clock_start_x, clock_start_y);
            glVertex2d(clock_end_x, clock_end_y);
        glEnd();
    }
}

void showClock(){
    second_hand_x = clock_center_x + second_hand_l*sin(second_angle*M_PI/180.0);
    second_hand_y = clock_center_y + second_hand_l*cos(second_angle*M_PI/180.0);

    minute_hand_x = clock_center_x + minute_hand_l*sin(minute_angle*M_PI/180.0);
    minute_hand_y = clock_center_y + minute_hand_l*cos(minute_angle*M_PI/180.0);

    hour_hand_x = clock_center_x + hour_hand_l*sin(hour_angle*M_PI/180.0);
    hour_hand_y = clock_center_y + hour_hand_l*cos(hour_angle*M_PI/180.0);

    glColor3d(0,0,1);
    glLineWidth(2);

    glBegin(GL_LINES);
        glVertex2d(clock_center_x, clock_center_y);
        glVertex2d(second_hand_x, second_hand_y);
    glEnd();

    glColor3d(0,1,0);
    glLineWidth(3);

    glBegin(GL_LINES);
        glVertex2d(clock_center_x, clock_center_y);
        glVertex2d(minute_hand_x, minute_hand_y);
    glEnd();

    glColor3d(1,0,0);
    glLineWidth(4);

    glBegin(GL_LINES);
        glVertex2d(clock_center_x, clock_center_y);
        glVertex2d(hour_hand_x, hour_hand_y);
    glEnd();
}

void drawCircle(){
    GLdouble x,y;
    GLdouble angle;
    GLdouble radius=0.06;

    glColor3d(1,1,0);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(pendulum_bob_x, pendulum_bob_y);

        for (angle=1.0; angle<361.0; angle += 0.2)
        {
            x = pendulum_bob_x + sin(angle)*radius;
            y = pendulum_bob_y + cos(angle)*radius;
            glVertex2d(x,y);
        }
    glEnd();
}

void showPendulum(){
    glColor3d(1,0,0);

    pendulum_bob_x = pendulum_center_x + pendulum_l*sin(pendulum_theta *M_PI/180.0);
    pendulum_bob_y = pendulum_center_y - pendulum_l*cos(pendulum_theta *M_PI/180.0);

    glBegin(GL_LINES);
        glVertex2d(pendulum_center_x, pendulum_center_y);
        glVertex2d(pendulum_bob_x, pendulum_bob_y);
    glEnd();

    glBegin(GL_POINTS);
        glPointSize(5);
        glVertex2d(pendulum_center_x, pendulum_center_y);
        //glVertex2d(pendulum_bob_x, pendulum_bob_y);
    glEnd();

    // glBegin(GL_POINTS);
    //     //glVertex2d(pendulum_center_x, pendulum_center_y);
    //     glPointSize(15);
    //     glVertex2d(pendulum_bob_x, pendulum_bob_y);
    // glEnd();

    drawCircle();
}

void showClockBody(){
    GLdouble x1,y1;
    GLdouble angle;
    GLdouble radius=0.55;

    glColor3d(1,1,1);
    glPointSize(2);

    glBegin(GL_POINTS);
        for (angle=1.0; angle<361.0; angle += 0.2)
        {
            x1 = clock_center_x + sin(angle)*radius;
            y1 = clock_center_y + cos(angle)*radius;
            glVertex2d(x1,y1);
        }
    glEnd();
}

void showClockSquare(){

    glColor3d(1,1,1);

    glBegin(GL_LINES);
        glVertex2d(clock_center_x+0.6, clock_center_y+0.6);
        glVertex2d(clock_center_x-0.6, clock_center_y+0.6);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(clock_center_x-0.6, clock_center_y+0.6);
        glVertex2d(clock_center_x-0.6, clock_center_y-0.6);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(clock_center_x-0.6, clock_center_y-0.6);
        glVertex2d(clock_center_x+0.6, clock_center_y-0.6);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(clock_center_x+0.6, clock_center_y+0.6);
        glVertex2d(clock_center_x+0.6, clock_center_y-0.6);
    glEnd();
}

void showPendulumBox(){
    glColor3d(1,1,1);

    glBegin(GL_LINES);
        glVertex2d(pendulum_center_x+0.25, pendulum_center_y);
        glVertex2d(pendulum_center_x+0.25, pendulum_center_y-0.7);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(pendulum_center_x+0.25, pendulum_center_y-0.7);
        glVertex2d(pendulum_center_x-0.25, pendulum_center_y-0.7);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(pendulum_center_x-0.25, pendulum_center_y-0.7);
        glVertex2d(pendulum_center_x-0.25, pendulum_center_y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(pendulum_center_x-0.25, pendulum_center_y);
        glVertex2d(pendulum_center_x+0.25, pendulum_center_y);
    glEnd();
}

void display() {
   //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
   glPointSize(10);

   glColor3d(0,0,1);

   showClockBody();
   showClock();
   showPendulum();
   showClockSquare();
   showPendulumBox();
   showTime();
 
   glFlush();  // Render now
}

void reshape(int width, int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height){
        gluOrtho2D(-width*1.0/height, width*1.0/height, -1, 1);
    }
    else{
        gluOrtho2D( -1, 1, -height*1.0/width, height*1.0/width);
    }
}

void timerListener(int value){
    pendulum_theta += pendulum_d_theta;
    if (pendulum_theta < -15 || pendulum_theta > 15)
    {
        pendulum_d_theta = -pendulum_d_theta;
    }

    hour_angle += 0.000833;
    minute_angle += 0.01;
    second_angle += 0.6;

    glutPostRedisplay();
    glutTimerFunc(100, timerListener, 0);
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(1640, 1640);   // Set the window's initial width & height
   glutInitWindowPosition(100, 50); // Position the window's initial top-left corner


   // current date and time on the current system
   time_t now = time(0);
   // convert now to string form
   char* date_time = ctime(&now);
   string t(date_time);
   vector<string> tokens;
   string token;
   istringstream tokenStream(t);
   while (getline(tokenStream, token, ' ')) {
       tokens.push_back(token);
   }
   string present_time = tokens[3];
   vector<string> times;
   istringstream anotherTokenStream(present_time);
   while (getline(anotherTokenStream, token, ':')) {
       times.push_back(token);
   }
   string h = times[0];
   string m = times[1];
   string s = times[2];

   initial_hour = (GLdouble)(stoi(h)%12);
   initial_minute = (GLdouble)(stoi(m));
   initial_second = (GLdouble)(stoi(s));

   hour_angle = (initial_hour*3600.0 + initial_minute*60.0 + initial_second)/120.0;
   minute_angle = (initial_minute*60.0 + initial_second)/10.0;
   second_angle = initial_second/0.167;

   //cout << present_time << endl;

   glutDisplayFunc(display); // Register display callback handler for window re-paint
   //glutIdleFunc(idle);
   glutTimerFunc(0, timerListener, 0);
   //glClearColor(1,1,1,0);
   glutReshapeFunc(reshape);
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}