#include <iostream>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include <Windows.h>
#include <MMSystem.h>
using namespace std;

///**************************************************USER MANUAL**********************************************///

/// For Day View -> Press d Of Keyboard
/// For Night View -> Press n Of Keyboard
/// For Starting Rain -> Press r Of Keyboard
/// For Stopping Rain -> Press e Of Keyboard
/// For Star->Press s of Keyboard
/// For No Star->Press c of Keyboard
/// For Starting Car -> Press Right Arrow Of Keyboard
/// For Stopping Car -> Press Left Arrow Of Keyboard
/// For Comet -> Press Left Button Of Mouse
/// For Thunder -> Press Right Button Of Mouse


int day=1;///1 for day,0 for night
int rainy=0;///1 for rain,0 for no rain
int cometenable=0;///1 for comet,0 for no comet
int thunderenable=0;///1 for thunder,0 for no thunder
int starenable=0;///1 for star,0 for no star
float cloud1 = 0.0f;
float cloudspeed=0.01;
float rainspeed=0;
float cometspeed=0;
float carspeed=0;
float tirespeed=0;
float bigcarspeed=0;
float smallcarspeed=0;
float savecloudspeed=0;
float angle=0;
float red=1;              ///
float green=1;           /// red,green,blue used for cloud colour
float blue=1;           ///
float red1=0.980392;             ///
float green1=0.980392;          ///
float blue1=0.823529;          ///
float red2=0.52734375;        /// red1,green1,blue1,red2,green2,blue2,red3,green3,blue3 used for sky colour
float green2=0.8046878;      ///
float blue2=0.99765625;     ///
float red3=0.498039;       ///
float green3= 1;          ///
float blue3= 0.831373;
float red4=1.0;            ///
float green4= 0.95;       /// red4,green4,blue4 used for sun colour
float blue4= 0.0;        ///
float red5=1.0;             ///
float green5= 1.0;         /// red5,green5,blue5 used for moon colour
float blue5= 0.70;        ///
float red6=0.20;             ///
float green6=0.20;          /// red6,green6,blue6 used for star colour
float blue6=0.26;          ///

bool showthunder=false;

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^UPDATE FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void update(int value)
{
    rainspeed-=.5;
    if(rainspeed -.8 < -1.0)
    {
        rainspeed = 1;
    }

    cometspeed-=.03;

    cloud1 += cloudspeed;
    if(cloud1 -1.3 > 1.0)
    {
        cloud1 = -1;
    }

    bigcarspeed += carspeed;
    if(bigcarspeed -1.3 > 1.0)
    {
        bigcarspeed = -1;
    }

    smallcarspeed+=carspeed;
    if(smallcarspeed -1 > 1.0)
    {
        smallcarspeed = -1;
    }

    angle-=tirespeed;

	glutPostRedisplay(); ///Notify GLUT that the display has changed

	glutTimerFunc(50, update, 0); ///Notify GLUT to call update again in 50 milliseconds
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SPECIAL KEY FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            carspeed+=0.01f;
            tirespeed+=2;
            break;

        case GLUT_KEY_LEFT:
            carspeed=0;
            tirespeed=0;
            break;
    }
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^KEYBOARD FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
        case 'd':
            day=1;
            break;

        case 'n':
            day=0;
            break;

        case 'r':
            rainy=1;
            savecloudspeed=cloudspeed;
            cloudspeed=0;
            //glColor3f(1,0,0);
            red=0.498;
            green=0.498;
            blue=0.498;
            red4=0.64;
            green4=0.64;
            blue4=0.64;
            red5=0.20;
            green5=0.20;
            blue5=0.26;
            break;

        case 'e':
            rainy=0;
            cloudspeed=savecloudspeed;
            red=1;
            green=1;
            blue=1;
            red4=1.0;
            green4= 0.95;
            blue4= 0.0;
            red5=1.0;
            green5= 1.0;
            blue5= 0.70;
            break;

        case 's':
            starenable=1;
            red6=1;
            green6=1;
            blue6=1;
            break;

        case 'c':
            starenable=0;
            red6=0.20;
            green6=0.20;
            blue6=0.26;
            break;
   }
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^MOUSE FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cometenable=1;
        cometspeed=.03;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        showthunder=!showthunder;
        if(showthunder)
        {
            thunderenable=1;
        }
        else if(!showthunder)
        {
            thunderenable=0;
        }
    }
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^CIRCLE FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void circle(float x, float y, double r )
{
    float x1,y1;
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/25;
		float x1 = x+((r-.07) * cos(A) );
		float y1 = y+((r) * sin(A) );
		glVertex2f(x1,y1);
	}
	glEnd();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SUN FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void sun()
{
    glColor3f(red4,green4,blue4);
	circle(0.50,0.85,0.15);
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^MOON FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void moon()
{
    glColor3f(red5,green5,blue5);
	circle(0.15,0.90,0.15);
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^THUNDER FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void thunder()
{
    glPushMatrix();
    glLineWidth(3);
    glColor3f(1,1,0);

    glBegin(GL_LINES);
        glVertex2f(-0.15,0.8);
        glVertex2f(-0.18,0.7);

    glBegin(GL_LINES);
        glVertex2f(-0.18,0.7);
        glVertex2f(-0.14,0.6);

    glBegin(GL_LINES);
        glVertex2f(-0.14,0.6);
        glVertex2f(-0.18,0.5);

    glBegin(GL_LINES);
        glVertex2f(-0.17,0.67);
        glVertex2f(-0.25,0.5);

    glBegin(GL_LINES);
        glVertex2f(-0.26,0.65);
        glVertex2f(-0.32,0.5);

    glBegin(GL_LINES);
        glVertex2f(-0.25,0.5);
        glVertex2f(-0.26,0.65);

    glBegin(GL_LINES);
        glVertex2f(0.04,0.9);
        glVertex2f(0.07,0.8);

    glBegin(GL_LINES);
        glVertex2f(0.07,0.8);
        glVertex2f(0.15,0.75);

    glBegin(GL_LINES);
        glVertex2f(0.15,0.75);
        glVertex2f(0.12,0.7);

    glBegin(GL_LINES);
        glVertex2f(0.09,0.78);
        glVertex2f(0.07,0.7);

    glBegin(GL_LINES);
        glVertex2f(0.07,0.7);
        glVertex2f(0.09,0.65);

    glBegin(GL_LINES);
        glVertex2f(0.09,0.65);
        glVertex2f(0.07,0.6);

        glEnd();
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^BIG CAR TIRE1 FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void bigcartire1()
{
///tire1 ring
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3);
    glPointSize(25);
    glTranslatef(-0.88, -0.78, 0.0);
    glRotatef(angle,0,0,1);
    glTranslatef(0.88, 0.78, 0.0);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.88, -.78);
        glVertex2f(-.88, -0.71);
        glVertex2f(-.94, -0.74);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.88, -.78);
        glVertex2f(-.93, -0.83);
        glVertex2f(-.88, -0.86);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.88, -.78);
        glVertex2f(-.82, -0.82);
        glVertex2f(-.81, -0.75);
    glEnd();
    glPopMatrix();

///tire1 barrel
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-0.88, -0.78, 0.0);
    glutSolidSphere(.007,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^BIG CAR TIRE2 FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void bigcartire2()
{
///tire2 ring
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3);
    glPointSize(25);
    glTranslatef(-0.60, -0.78, 0.0);
    glRotatef(angle,0,0,1);
    glTranslatef(0.60, 0.78, 0.0);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.60, -.78);
        glVertex2f(-.60, -0.71);
        glVertex2f(-.66, -0.74);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.60, -.78);
        glVertex2f(-.65, -0.83);
        glVertex2f(-.60, -0.86);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(-.60, -.78);
        glVertex2f(-.54, -0.82);
        glVertex2f(-.53, -0.75);
    glEnd();
    glPopMatrix();

///tire2 barrel
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-0.60, -0.78, 0.0);
    glutSolidSphere(.007,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^BIG CAR FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void bigcar()
{
///body
    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0, -0.75);
        glVertex2f(-.45, -0.75);
        glVertex2f(-.45, -0.5);
        glVertex2f(-1.0, -0.5);
	glEnd();
    glPopMatrix();

///upper part
///black part
    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-.90, -0.5);
        glVertex2f(-.85, -0.3);
        glVertex2f(-.65, -0.3);
        glVertex2f(-.60, -0.5);
	glEnd();
    glPopMatrix();

///white part
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-.89, -0.5);
        glVertex2f(-.84, -0.32);
        glVertex2f(-.66, -0.32);
        glVertex2f(-.61, -0.5);
	glEnd();
    glPopMatrix();

///white middle border
    glPushMatrix();
    glLineWidth(3);
    glPointSize(25);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-.75, -0.5);
        glVertex2f(-.75, -0.3);
    glEnd();
    glPopMatrix();

///curve
    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-.90, -0.5);
        glVertex2f(-.88, -0.42);
        glVertex2f(-.92, -0.5);
	glEnd();
    glPopMatrix();

    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-.60, -0.5);
        glVertex2f(-.62, -0.42);
        glVertex2f(-.59, -0.5);
	glEnd();
    glPopMatrix();

///door lock
    glPushMatrix();
    glLineWidth(3);
    glPointSize(25);
    glColor3f(1,1,1);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-.85, -0.6);
        glVertex2f(-.82, -0.6);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLineWidth(3);
    glPointSize(25);
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-.70, -0.6);
        glVertex2f(-.67, -0.6);
    glEnd();
    glPopMatrix();
///head light
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-.44, -0.53);
        glVertex2f(-.44, -0.59);
        glVertex2f(-.48, -0.56);
	glEnd();
    glPopMatrix();

///tire
    glPushMatrix();
    glColor3f(0.4,0.4,0.4);
    glTranslatef(-0.88, -0.78, 0.0);
    glutSolidSphere(.070,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.4,0.4,0.4);
    glTranslatef(-0.60, -0.78, 0.0);
    glutSolidSphere(.070,50,50);
    glPopMatrix();

///big car tire1
    glPushMatrix();
    bigcartire1();
    glPopMatrix();

///big car tire2
    glPushMatrix();
    bigcartire2();
    glPopMatrix();

}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SMALL CAR TIRE1 FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void smallcartire1()
{
///tire1 ring
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3);
    glPointSize(25);
    glTranslatef(0.03, -0.55, 0.0);
    glRotatef(angle,0,0,1);
    glTranslatef(-0.03, 0.55, 0.0);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.03, -0.55);
        glVertex2f(0.03, -0.51);
        glVertex2f(0.01, -0.52);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.03, -0.55);
        glVertex2f(0.00, -0.57);
        glVertex2f(0.01, -0.59);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.03, -0.55);
        glVertex2f(0.07, -0.55);
        glVertex2f(0.06, -0.57);
    glEnd();
    glPopMatrix();

///tire1 barrel
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.03, -0.55, 0.0);
    glutSolidSphere(.004,50,50);
    glPopMatrix();

}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SMALL CAR TIRE2 FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void smallcartire2()
{
///tire2 ring
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3);
    glPointSize(25);
    glTranslatef(0.24, -0.55, 0.0);
    glRotatef(angle,0,0,1);
    glTranslatef(-0.24, 0.55, 0.0);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.24, -0.55);
        glVertex2f(0.24, -0.51);
        glVertex2f(0.22, -0.52);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.24, -0.55);
        glVertex2f(0.21, -0.57);
        glVertex2f(0.22, -0.59);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex2f(0.24, -0.55);
        glVertex2f(0.28, -0.55);
        glVertex2f(0.27, -0.57);
    glEnd();
    glPopMatrix();

///tire2 barrel
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.24, -0.55, 0.0);
    glutSolidSphere(.004,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SMALL CAR FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void smallcar()
{
///body
    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-.05, -0.54);
        glVertex2f(-.05, -0.37);
        glVertex2f(0.33, -0.37);
        glVertex2f(0.33, -0.54);
	glEnd();
    glPopMatrix();

///upper part
///black part
    glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.01, -0.37);
        glVertex2f(0.25, -0.37);
        glVertex2f(0.20, -0.24);
        glVertex2f(0.05, -0.24);
	glEnd();
    glPopMatrix();

///white part
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.02, -0.37);
        glVertex2f(0.24, -0.37);
        glVertex2f(0.19, -0.25);
        glVertex2f(0.06, -0.25);
	glEnd();
    glPopMatrix();

///white middle border
    glPushMatrix();
    glLineWidth(3);
    glPointSize(25);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.13, -0.25);
        glVertex2f(0.13, -0.37);
    glEnd();
    glPopMatrix();

///door lock
    glPushMatrix();
    glLineWidth(2);
    glPointSize(25);
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.06, -0.44);
        glVertex2f(0.08, -0.44);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLineWidth(2);
    glPointSize(25);
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
       glVertex2f(0.17, -0.44);
        glVertex2f(0.19, -0.44);
    glEnd();
    glPopMatrix();

///tire
    glPushMatrix();
    glColor3f(0.4,0.4,0.4);
    glTranslatef(0.03, -0.55, 0.0);
    glutSolidSphere(.038,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.4,0.4,0.4);
    glTranslatef(0.24, -0.55, 0.0);
    glutSolidSphere(.038,50,50);
    glPopMatrix();

///small car tire1
    glPushMatrix();
    smallcartire1();
    glPopMatrix();

///small car tire2
    glPushMatrix();
    smallcartire2();
    glPopMatrix();

///head light
    glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.34, -0.39);
        glVertex2f(0.34, -0.41);
        glVertex2f(0.31, -0.40);
	glEnd();
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^CLOUD LEFT FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void cloudleft()
{
    glTranslatef(cloud1,0,0);

    glPushMatrix();
        glColor3f(red,green,blue);
        glTranslatef(-0.8,0.8,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-0.75,0.85,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-0.7,0.85,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-0.65,0.8,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.73,0.77,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^CLOUD MIDDLE FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void cloudmiddle()
{
    glTranslatef(cloud1,0,0);

    glPushMatrix();
        glColor3f(red,green,blue);
        glTranslatef(-0.5,0.65,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.45,0.7,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.4,0.7,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.35,0.65,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.43,0.62,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^CLOUD RIGHT FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void cloudright()
{
    glTranslatef(cloud1,0,0);

    glPushMatrix();
        glColor3f(red,green,blue);
        glTranslatef(0.7,0.8,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.6,0.85,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.65,0.85,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.55,0.8,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.63,0.77,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^COMET FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void comet()
{
    glTranslatef(-cometspeed,cometspeed,0);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-.60, 0.71, 0.0);
    glutSolidSphere(.010,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-.60,.72);
        glVertex2f(-.60,.70);
        glVertex2f(-.68,.78);
    glEnd();glColor3f(red2,green2,blue2);
    glPopMatrix();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^RAIN FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void rain()
{
    glTranslatef(0,rainspeed,0);
    glColor3f(1,1,1);
    glLineWidth(2);

    glTranslatef(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(-0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(2,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

    glTranslatef(0.1,0,0);
    glBegin(GL_LINES);
        glVertex2f(1,1);
        glVertex2f(0.985,.95);
        glVertex2f(0.97,.9);
        glVertex2f(0.955,.85);
        glVertex2f(0.94,.8);
        glVertex2f(0.925,.75);
        glVertex2f(0.91,.7);
        glVertex2f(0.895,.65);
        glVertex2f(0.88,.6);
        glVertex2f(0.865,.55);
        glVertex2f(0.85,.5);
        glVertex2f(0.835,.45);
        glVertex2f(0.82,.4);
        glVertex2f(0.805,.35);
        glVertex2f(0.79,0.3);
        glVertex2f(0.775,0.25);
        glVertex2f(0.76,0.2);
        glVertex2f(0.745,0.15);
        glVertex2f(0.73,0.1);
        glVertex2f(0.715,0.05);
        glVertex2f(0.7,0);
        glVertex2f(0.685,-.05);
        glVertex2f(0.67,-.1);
        glVertex2f(0.655,-.15);
        glVertex2f(0.64,-.2);
        glVertex2f(0.625,-.25);
        glVertex2f(0.61,-.3);
        glVertex2f(0.595,-.35);
        glVertex2f(0.58,-.4);
        glVertex2f(0.565,-.45);
        glVertex2f(0.55,-.5);
        glVertex2f(0.535,-.55);
        glVertex2f(0.52,-.6);
        glVertex2f(0.505,-.65);
        glVertex2f(0.49,-.7);
        glVertex2f(0.475,-.75);
        glVertex2f(0.46,-.8);
        glVertex2f(0.445,-.85);
        glVertex2f(0.43,-.9);
        glVertex2f(0.415,-.95);
    glEnd();

}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^STAR FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///
void star()
{
    glColor3f(red6,green6,blue6);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex2f(-0.1,.7);
        glVertex2f(-0.2,.9);
        glVertex2f(-0.3,.65);
        glVertex2f(-0.25,.4);
        glVertex2f(-0.45,.8);
        glVertex2f(-0.5,.45);
        glVertex2f(-0.7,.3);
        glVertex2f(-0.65,.65);
        glVertex2f(-0.8,.93);
        glVertex2f(-0.85,.5);
        glVertex2f(-0.95,.75);

        glVertex2f(0.2,.4);
        glVertex2f(0.3,.7);
        glVertex2f(0.4,.9);
        glVertex2f(0.5,.65);
        glVertex2f(0.45,.4);
        glVertex2f(0.65,.8);
        glVertex2f(0.8,.75);
        glVertex2f(0.9,.3);
        glVertex2f(0.95,.65);
        glVertex2f(0.8,.93);
        glVertex2f(0.75,.5);
        glVertex2f(0.95,.95);
    glEnd();
}

///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DISPLAY FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^///

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

///**************************************************SKY**************************************************///
    if(day==0)
    {
        glPushMatrix();
        glColor3f(0.0, 0.02, 0.07);
		glBegin(GL_POLYGON);
            glVertex2f(-1, 0);
            glColor3f(0.0, 0.02, 0.20);
            glVertex2f(-1, 1);
            glColor3f(0.35, 0.35, 0.35);
            glVertex2f(1, 1);
            glColor3f(0, 0, 0);
            glVertex2f(1,0);
		glEnd();
        glPopMatrix();

///*********************************************MOON********************************************************///
        glPushMatrix();
        moon();
        glPopMatrix();

///*********************************************COMET*******************************************************///
        if(rainy==0)
        {
            if(cometenable==1)
            {
                glPushMatrix();
                comet();
                glPopMatrix();
            }
        }
    }
    else
    {
        glPushMatrix();
            glColor3f(red2,green2,blue2);
            glBegin(GL_POLYGON);
            glVertex2f(-1, 0);
            glVertex2f(-1, 1);
            glColor3f(red1,green1,blue1);
            glVertex2f(1, 1);
            glColor3f(red3,green3,blue3);
            glVertex2f(1,0);
            glEnd();
        glPopMatrix();

///*************************************************SUN**************************************************///
        glPushMatrix();
        sun();
        glPopMatrix();
    }

///**********************************************MOUNTAIN***********************************************///
    glPushMatrix();
///left small mountain
    glBegin(GL_POLYGON);
        glColor3f(0.74,0.17,0);
        glVertex2f(-0.7, -0.2);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(-0.4, 0.3);
        glColor3f(0.0,0.42,0.0);
        glVertex2f(-0.1, -0.2);
    glEnd();

///right small mountain
    glBegin(GL_POLYGON);
        glColor3f(0.74,0.0,0.0);
        glVertex2f(0.7, -0.1);
        glColor3f(0.35,0.20,0);
        glVertex2f(0.4, 0.4);
        glColor3f(0.0,0.65,0);
        glVertex2f(0.1, 0);
    glEnd();

///left mountain
    glBegin(GL_POLYGON);
        glColor3f(0.0,0.38,0);
        glVertex2f(-1, -0.7);
        glColor3f(0.0,0.50,0);
        glVertex2f(-1, 0);
        glColor3f(0.77,0.38,0);
        glVertex2f(-0.8, 0.35);
        glColor3f(0.0,0.38,0);
        glVertex2f(-0.4,- 0.2);
        glColor3f(0.77,0.38,0);
        glVertex2f(-0.7, -0.7);
    glEnd();

///right mountain
    glBegin(GL_POLYGON);
        glColor3f(0.0,0.65,0.0);
        glVertex2f(1, -0.7);
        glColor3f(0.0,0.38,0.0);
        glVertex2f(1, 0);
        glColor3f(0.77,0.38,0);
        glVertex2f(0.7, 0.5);
        glColor3f(0.0,0.0,0.0);
        glVertex2f(0.34, 0);
        glColor3f(0.0,0.0,0);
        glVertex2f(-0.1, -0.7);
    glEnd();

///middle mountain
    glBegin(GL_POLYGON);
        glColor3f(0.0,0.65,0);
        glVertex2f(-0.7, -0.7);
        glColor3f(0.77,0.38,0.0);
        glVertex2f(0, 0.6);
        glColor3f(0.0,0.15,0);
        glVertex2f(0.7, -0.7);
    glEnd();
    glPopMatrix();

///**********************************************ROAD*************************************************///
    glPushMatrix();
     glBegin(GL_POLYGON);
        glColor3f(0.2,0.2,0.2);
        glVertex2f(-1, -1);
        glVertex2f(-1, -0.5);
        glVertex2f(1, -0.5);
        glVertex2f(1, -1);
     glEnd();
     glPopMatrix();

///*****************************************ROAD DIVIDER**********************************************///

///part 1
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(-1, -.75);
        glVertex2f(-.8, -0.75);
    glEnd();
    glPopMatrix();

///part 2
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(-.6, -.75);
        glVertex2f(-.4, -0.75);
    glEnd();
    glPopMatrix();

///part 3
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(-.2, -.75);
        glVertex2f(0, -0.75);
    glEnd();
    glPopMatrix();

///part 4
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(.2, -.75);
        glVertex2f(.4, -0.75);
    glEnd();
    glPopMatrix();

///part 5
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(.6, -.75);
        glVertex2f(.8, -0.75);
    glEnd();
    glPopMatrix();

///part 6
    glPushMatrix();
    glLineWidth(10);
    glPointSize(25);
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2f(.95, -.75);
        glVertex2f(1, -0.75);
    glEnd();
    glPopMatrix();

///******************************************************TREES***********************************///
///tree left
///trunk
    glPushMatrix();
    glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
        glVertex2f(-0.9, -0.5);
        glVertex2f(-0.9, -0.3);
        glVertex2f(-0.87, -0.3);
        glVertex2f(-0.87, -0.5);
	glEnd();
	glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
	glBegin(GL_TRIANGLES);
        glVertex2f(-0.99, -0.3);
        glVertex2f(-0.88,- 0.1);
        glVertex2f(-0.77, -0.3);
	glEnd();
    glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.97, -0.2);
        glVertex2f(-0.88,0);
        glVertex2f(-0.79, -0.2);
	glEnd();
	glPopMatrix();

///tree round leafs left
///trunk
    glPushMatrix();
    glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
        glVertex2f(-0.4, -0.5);
        glVertex2f(-0.4, -0.3);
        glVertex2f(-0.37, -0.3);
        glVertex2f(-0.37, -0.5);
	glEnd();
	glPopMatrix();

///leafs
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.4,-0.30,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.35,-0.30,0);
        glutSolidSphere(.045,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.33,-0.25,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.43,-0.30,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.40,-0.33,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.45,-0.25,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.43,-0.20,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.40,-0.25,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.45,-0.20,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.38,-0.20,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.35,-0.23,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.33,-0.20,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

     glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.35,-0.15,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.38,-0.12,0);
        glutSolidSphere(.06,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.37,-0.15,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.43,-0.15,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

///tree middle
///trunk
    glPushMatrix();
    glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
        glVertex2f(-0.23, -0.5);
        glVertex2f(-0.23, -0.3);
        glVertex2f(-0.20, -0.3);
        glVertex2f(-0.20, -0.5);
	glEnd();
	glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
	glBegin(GL_TRIANGLES);
        glVertex2f(-0.14, -0.3);
        glVertex2f(-0.21,- 0.1);
        glVertex2f(-0.28, -0.3);
	glEnd();
    glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.14, -0.2);
        glVertex2f(-0.21,0);
        glVertex2f(-0.28, -0.2);
	glEnd();
	glPopMatrix();

///tree round leafs middle
///trunk
    glPushMatrix();
    glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
        glVertex2f(0.1, -0.5);
        glVertex2f(0.1, -0.3);
        glVertex2f(0.07, -0.3);
        glVertex2f(0.07, -0.5);
	glEnd();
	glPopMatrix();

///leafs
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.1,-0.30,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.05,-0.30,0);
        glutSolidSphere(.045,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.03,-0.25,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.13,-0.30,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.10,-0.33,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.15,-0.25,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.13,-0.20,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.10,-0.25,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.15,-0.20,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.08,-0.20,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.05,-0.23,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.03,-0.20,0);
        glutSolidSphere(.035,50,50);
    glPopMatrix();

     glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.05,-0.15,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.08,-0.12,0);
        glutSolidSphere(.06,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.07,-0.15,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.13,-0.15,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

///tree right
///trunk
    glPushMatrix();
    glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
        glVertex2f(0.65, -0.5);
        glVertex2f(0.65, -0.3);
        glVertex2f(0.62, -0.3);
        glVertex2f(0.62, -0.5);
	glEnd();
	glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
	glBegin(GL_TRIANGLES);
        glVertex2f(0.72, -0.3);
        glVertex2f(0.62,- 0.1);
        glVertex2f(0.54, -0.3);
	glEnd();
    glPopMatrix();

///leafs
    glPushMatrix();
	glColor3f(0.0, 0.58, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.72, -0.2);
        glVertex2f(0.62,0);
        glVertex2f(0.54, -0.2);
	glEnd();
	glPopMatrix();

///bush left back
    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(-0.7,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(-0.65,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(-0.67,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

///bush middle back
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.45,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.5,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.48,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.53,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.58,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.55,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.51,-0.41,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

///bush right back
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.75,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.8,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.7,0.0);
        glTranslatef(0.78,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.83,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.88,-0.47,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.85,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.81,-0.41,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

///bush left front
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-1.0,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.8,0.0);
        glTranslatef(-0.9,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.7,0.0);
        glTranslatef(-0.8,-1.0,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.95,-.95,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.85,-1.0,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.85,-0.95,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(-0.78,-1.0,0);
        glutSolidSphere(.040,50,50);
    glPopMatrix();

///bush left front leafs
    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.99, -0.96);
        glVertex2f(-0.97, -0.96);
        glVertex2f(-1.0, -0.85);
	glEnd();
    glPopMatrix();

    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.96, -0.96);
        glVertex2f(-0.92, -0.96);
        glVertex2f(-0.97, -0.88);
	glEnd();
    glPopMatrix();

    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.82, -0.98);
        glVertex2f(-0.83, -0.98);
        glVertex2f(-0.81, -0.88);
	glEnd();
    glPopMatrix();

///bush middle front
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.20,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.25,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.23,-0.96,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.28,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.33,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.30,-0.98,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.5,0.0);
        glTranslatef(0.26,-0.94,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

///bush right front
    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(1.0,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.8,0.0);
        glTranslatef(0.9,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.7,0.0);
        glTranslatef(0.8,-1.0,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.95,-.95,0);
        glutSolidSphere(.05,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.85,-1.0,0);
        glutSolidSphere(.04,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.85,-0.42,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.6,0.0);
        glTranslatef(0.81,-0.41,0);
        glutSolidSphere(.03,50,50);
    glPopMatrix();

///bush right front leafs
    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.99, -0.96);
        glVertex2f(0.97, -0.96);
        glVertex2f(1.0, -0.85);
	glEnd();
    glPopMatrix();

    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.96, -0.96);
        glVertex2f(0.92, -0.96);
        glVertex2f(0.97, -0.88);
	glEnd();
    glPopMatrix();

    glPushMatrix();
	glColor3f(0.0, 0.60, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.82, -0.98);
        glVertex2f(0.83, -0.98);
        glVertex2f(0.81, -0.88);
	glEnd();
    glPopMatrix();

///***************************************************CLOUD****************************************///
///big cloud
    glPushMatrix();
        glColor3f(red,green,blue);
        glTranslatef(-0.3,1,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.2,0.9,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.1,0.9,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.1,1,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.15,1,0);
        glutSolidSphere(.1,50,50);
    glPopMatrix();

///**************************************************RAIN*******************************************///
    if(rainy==1)
    {
        red2=red1=red3=.64;
        green2=green1=green3=.64;
        blue2=blue1=blue3=.64;
        glPushMatrix();
        rain();
        glPopMatrix();

        if(thunderenable==1)
        {
            glPushMatrix();
            thunder();
            glPopMatrix();
        }
    }

    if(rainy==0)
    {
        PlaySound(TEXT("Rain_Thunder.wav"), NULL, SND_ASYNC);
        red1=0.980392;
        green1=0.980392;
        blue1=0.823529;
        red2=0.52734375;
        green2=0.8046878;
        blue2=0.99765625;
        red3=0.498039;
        green3= 1;
        blue3= 0.831373;
    }

///**********************************************CLOUD**********************************************///
///cloud left
    glPushMatrix();
    cloudleft();
    glPopMatrix();

///cloud middle
    glPushMatrix();
    cloudmiddle();
    glPopMatrix();

/// cloud right
    glPushMatrix();
    cloudright();
    glPopMatrix();

///***************************************************CAR*******************************************///
///small car
    glPushMatrix();
    glTranslatef(smallcarspeed, 0.0f, 0.0f);
    smallcar();
    glPopMatrix();

///big car
    glPushMatrix();
    glTranslatef(bigcarspeed, 0.0f, 0.0f);
    bigcar();
    glPopMatrix();

///**************************************************STAR*******************************************///
    if(starenable==1 && day==0 && rainy==0)
    {
        glPushMatrix();
        star();
        glPopMatrix();
    }

///*************************************************************************************************///
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1450, 700);
	glutCreateWindow("Hill View");
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutTimerFunc(20, update, 0); ///Add a timer

	glutMainLoop();
	return 0;
}
