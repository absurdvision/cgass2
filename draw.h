#ifndef _GLFRAMEWORK_H_
#define _GLFRAMEWORK_H_
/********************************************************************
  This is the basic framework for GLUT based 
  visualization of objects. Objects are modeled
  and rendered in draw.c

  Author: Vijay Natarajan
*/

/* includes glu and gl correctly */
#ifndef __APPLE_CC__
#  include "GL/glut.h"
#else
#  include <GLUT/glut.h>
#endif

#include<stdbool.h>

/*variables to store rotation/scaling/translation parameters */
bool myMovingOn;
GLfloat rotAngle;

/*keyboard controls */
bool  myLightsOn, mySmoothShadingOn, myBackFaceCullingOn;


/* Display is called whenever the contents of the window need 
   to be redrawn. The contents of the window may need to be redrawn 
   when the window is initially opened, when the window is popped and
   window damage is exposed, and when glutPostRedisplay() is 
   explicitly called. */
void Display ();

/* Animate will be executed if no other events are pending. This is 
   for example a good spot to calculate the frame rate . */
void Animate ();

/*DrawButterflyDL draws a butterfly!! */
void DrawButterfly();

#endif
