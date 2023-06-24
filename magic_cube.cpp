#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

struct point {
    GLfloat x, y, z;
};

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
}

// Global variables
int stacks = 100, slices = 100;
struct point points[101][101];

GLfloat eyex = 4, eyey = 4, eyez = 4;
GLfloat centerx = 0, centery = 0, centerz = 0;
GLfloat upx = 0, upy = 1, upz = 0;
bool isAxes = true, isCube = false, isPyramid = false;

/* Draw axes: X in Red, Y in Green and Z in Blue */
void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);   // Red
        // X axis
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);

        glColor3f(0,1,0);   // Green
        // Y axis
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);

        glColor3f(0,0,1);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    glEnd();
}

/* Draw a cube centered at the origin */
void drawCube() {
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f( 1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f,  1.0f);
        glVertex3f( 1.0f, 1.0f,  1.0f);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( 1.0f,  1.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glVertex3f(1.0f,  1.0f, -1.0f);
        glVertex3f(1.0f,  1.0f,  1.0f);
        glVertex3f(1.0f, -1.0f,  1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}

/* Draw a pyramid centered at the origin */
void drawPyramid() {
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
        // Front
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Right
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(1.0f, -1.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Back
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(1.0f, -1.0f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-1.0f, -1.0f, -1.0f);

        // Left
        glColor3f(1.0f,0.0f,0.0f);       // Red
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f,0.0f,1.0f);       // Blue
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glColor3f(0.0f,1.0f,0.0f);       // Green
        glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
}

// Function name getVertices that returns a 2d array of point structure
// that contains the vertices of the sphere


void setCoordinates(double radius){
    GLdouble n1[3];        // normal of longitudinal plane rotating along Y-axis
    GLdouble n2[3];        // normal of latitudinal plane rotating along Z-axis
    GLdouble v[3];         // direction vector intersecting 2 planes, n1 x n2
    GLdouble a1;           // longitudinal angle along Y-axis
    GLdouble a2;           // latitudinal angle along Z-axis

    // compute the number of vertices per row, 2^n + 1
    int pointsPerRow = 9;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
    for(unsigned int i = 0; i < stacks; i++)
    {
        // normal for latitudinal plane
        // if latitude angle is 0, then normal vector of latitude plane is n2=(0,1,0)
        // therefore, it is rotating (0,1,0) vector by latitude angle a2
        a2 = (45.0f - 90.0f * i / (stacks - 1))*M_PI/180.0f;
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        // rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
        for(unsigned int j = 0; j < stacks; ++j)
        {
            // normal for longitudinal plane
            // if longitude angle is 0, then normal vector of longitude is n1=(0,0,-1)
            // therefore, it is rotating (0,0,-1) vector by longitude angle a1
            a1 = (-45.0f + 90.0f * j / (stacks - 1))*M_PI/180.0f;
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            // find direction vector of intersected line, n1 x n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            float scale = (radius) / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            // add a vertex into array
            points[j][i].x = v[0];
            points[j][i].y = v[1];
            points[j][i].z = v[2];
        }
    }
}

void drawSphere(double radius) {
    setCoordinates(radius);

    glBegin(GL_QUADS);
        for (int j = 0; j < stacks; j++) {
            for (int i = 0; i < slices; i++) {
                // GLfloat c = (2+cos((i+j) * 2.0 * M_PI / slices)) / 3;
                // glColor3f(c,c,c);
                glVertex3f(points[j][i].x, points[j][i].y, points[j][i].z);
                glVertex3f(points[j][i+1].x, points[j][i+1].y, points[j][i+1].z);

                glVertex3f(points[j+1][i+1].x, points[j+1][i+1].y, points[j+1][i+1].z);
                glVertex3f(points[j+1][i].x, points[j+1][i].y, points[j+1][i].z);
            }
        }
    glEnd();
}
float scalefactor = 1.0f;

void drawOneSphere(){
    glTranslatef(scalefactor,0,0);  //1.0-(1/sqrt(3))+
    glScalef(1.0-scalefactor,1.0-scalefactor,1.0-scalefactor);
    drawSphere((1/sqrt(3)));
}

void drawAllSpheres(){

    glPushMatrix();
        glRotated(0, 0, 0, 0);
        glColor3d(0, 1, 0);
        drawOneSphere();
    glPopMatrix();

    glPushMatrix();
        glRotated(90, 0, 1, 0);
        glColor3d(1, 0, 0);
        drawOneSphere();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 0, 1, 0);
        glColor3d(0, 1, 0);
        drawOneSphere();
    glPopMatrix();

    glPushMatrix();
        glRotated(270, 0, 1, 0);
        glColor3d(1, 0, 0);
        drawOneSphere();
    glPopMatrix();

    glPushMatrix();
        glRotated(90, 0, 0, 1);
        glColor3d(0, 0, 1);
        drawOneSphere();
    glPopMatrix();

    glPushMatrix();
        glRotated(-90, 0, 0, 1);
        glColor3d(0, 0, 1);
        drawOneSphere();
    glPopMatrix();
}

void drawRawCylinder() {

    double currx, curry;
    double radius = (1.0-scalefactor)*(1/sqrt(3));
    double height =  (1.0-scalefactor)*sqrt(2);
    glBegin(GL_QUADS);
        for (int i = 1; i <= 100; i++) {
            double theta = i * 70.53 * M_PI / (180 * 100);
            currx = radius * cos(theta);
            curry = radius * sin(theta);

            GLfloat c = (2+cos(theta))/3;
            glColor3f(c,c,c);
            glVertex3f(currx, curry, height/2);
            glVertex3f(currx, curry, -height/2);

            glVertex3f(radius, 0, -height/2);
            glVertex3f(radius, 0, height/2);
        }
    glEnd();
}

void drawCylinder(){
    glPushMatrix();
        glRotated(-45, 0, 1, 0);
        glTranslatef(((1/sqrt(2))-((1/sqrt(3))/sin(((109.47)/2)*M_PI/180.0))),0,0);
        glRotated(-70.53/2, 0, 0, 1);
        //glRotated(-35, 0, 0, 1);
        //glScalef(1.0-scalefactor,1.0-scalefactor,1.0-scalefactor);
        //glTranslatef(scalefactor,0,0);
        drawRawCylinder();
    glPopMatrix();
}

void drawTriangle(){
    glScalef(scalefactor,scalefactor,scalefactor);
    glTranslatef(1.0-scalefactor,1.0-scalefactor,1.0-scalefactor);
    glBegin(GL_TRIANGLES);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(0, 0, 1);
    glEnd();
}

void drawTriangles(){
    glPushMatrix();
        glRotated(0, 0, 0, 0);
        glColor3d(1, 0, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(90, 0, 1, 0);
        glColor3d(0, 1, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 0, 1, 0);
        glColor3d(1, 0, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(270, 0, 1, 0);
        glColor3d(0, 1, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 1, 0, 1);
        glRotated(90, 0, 1, 0);
        glColor3d(1, 0, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 1, 0, 1);
        glRotated(180, 0, 1, 0);
        glColor3d(0, 1, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 1, 0, 1);
        glRotated(270, 0, 1, 0);
        glColor3d(1, 0, 0);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(180, 1, 0, 1);
        glRotated(0, 0, 1, 0);
        glColor3d(0, 1, 0);
        drawTriangle();
    glPopMatrix();
}


/*  Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
void display() {
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix

    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    gluLookAt(eyex,eyey,eyez,
              centerx,centery,centerz,
              upx,upy,upz);
    // draw
    if (isAxes) drawAxes();
    if (isCube) drawCube();
    //if (isPyramid) 
   // drawPyramid();
    //drawCylinder(1, 0.5, 100);
    drawAllSpheres();
    drawTriangles();
    drawCylinder();
    
    glutSwapBuffers();  // Render now
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeListener(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y) {
    float v = 0.1;
    switch (key) {
        //sphere scaling factor
    case 'z':
        scalefactor += 0.1;
        break;
    case 'x':
        scalefactor -= 0.1;
        break;
    // Control eye (location of the eye)
    // control eyex
    case '1':
        eyex += v;
        break;
    case '2':
        eyex -= v;
        break;
    // control eyey
    case '3':
        eyey += v;
        break;
    case '4':
        eyey -= v;
        break;
    // control eyez
    case '5':
        eyez += v;
        break;
    case '6':
        eyez -= v;
        break;

    // Control center (location where the eye is looking at)
    // control centerx
    case 'q':
        centerx += v;
        break;
    case 'w':
        centerx -= v;
        break;
    // control centery
    case 'e':
        centery += v;
        break;
    case 'r':
        centery -= v;
        break;
    // control centerz
    case 't':
        centerz += v;
        break;
    case 'y':
        centerz -= v;
        break;

    // Control what is shown
    case 'a':
        isAxes = !isAxes;   // show/hide Axes if 'a' is pressed
        break;
    case 'c':
        isCube = !isCube;   // show/hide Cube if 'c' is pressed
        break;
    case 'p':
        isPyramid = !isPyramid; // show/hide Pyramid if 'p' is pressed
        break;

    // Control exit
    case 27:    // ESC key
        exit(0);    // Exit window
        break;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y) {
    double v = 0.25;
    double lx = centerx - eyex;
    double lz = centerz - eyez;
    double s;
    switch (key) {
    case GLUT_KEY_LEFT:
        eyex += v * (upy*lz);
        eyez += v * (-lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_RIGHT:
        eyex += v * (-upy*lz);
        eyez += v * (lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_UP:
        eyey += v;
        break;
    case GLUT_KEY_DOWN:
        eyey -= v;
        break;
    
    default:
        return;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(640, 640);               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("OpenGL 3D Drawing");      // Create a window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}
