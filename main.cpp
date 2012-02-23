/********************************************************************
  This is the basic framework for GLUT based 
  visualization of objects. Objects are modeled
  and rendered in draw.c

  Author: Vijay Natarajan dsnnnn
*/

/* includes glu and gl correctly*/
double  poly_d;

#ifndef __APPLE_CC__
#  include "GL/glut.h"         
#else
#  include <GLUT/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include "zoo.cpp"



/********************************************************************/
/* Globals */

/*   Variables */

char *      theProgramTitle;
int         theWindowWidth = 700, theWindowHeight = 700;
int         theWindowPositionX = 40, theWindowPositionY = 40;
bool        isAnimating = false;
bool        isFullScreen = false;
int			wireframe = 0;
int 		ortho=0;


double lx,ly,lz;	//the  location where we are looking from;
double hx,hy,hz;
double sx,sy,sz;

double vtheta;
double htheta;


extern int bind;

extern double lx_bind;
extern double ly_bind;
extern double lz_bind;



double view_angle;


/* Constants */
const int   ANIMATION_DELAY = 1;    /* milliseconds between rendering */


void computeFPS ()
/* post: compute frames per second and display in window's title bar */
{
  static int frameCount = 0;
  static int lastFrameTime = 0;
  static char * title;
  int currentTime;

  if(!title)
    title = (char*) malloc((strlen(theProgramTitle)+100) * sizeof(char));
  frameCount++;
  currentTime = glutGet((GLenum)(GLUT_ELAPSED_TIME));
  if (currentTime - lastFrameTime > 1000)
    {
      sprintf(title, "%s [ FPS: %4.2f ] [ PRS: %8.2f ]",
	      theProgramTitle,
	      frameCount * 1000.0 / (currentTime - lastFrameTime),
	      (poly_d /(currentTime - lastFrameTime))*1000);
	      
      glutSetWindowTitle(title);
      lastFrameTime = currentTime;
      frameCount = 0;
      poly_d = 0;
    }
}


void setPerspective (GLenum mode, int x, int y)
{
  /* get info about viewport (x, y, w, h) */
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  
	if(ortho ==0){
	/* set camera to view viewport area */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		/* view scene in perspective */
		gluPerspective(view_angle, (GLfloat)(viewport[2]) / (GLfloat)(viewport[3]), 0.1, 500);
		/* prepare to work with model again */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else{
		/* set camera to view viewport area */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		/*	 view scene in perspective */
		glOrtho((-10-(view_angle)/2)*(GLfloat)(viewport[2]) / (GLfloat)(viewport[3]),
		(0.1+view_angle/2)*(GLfloat)(viewport[2]) / (GLfloat)(viewport[3]),
		0.1-view_angle/2,10+view_angle/2,
		-0.1,-5000);
		/* prepare to work with model again */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
  
}

void setCamera ()
{

	
	if(bind>=0){
		gluLookAt(  lx_bind, 1.2, lz_bind, /* from position */
					lx_bind-1*(lx_bind+50)*sin(lt_bind), 1, lz_bind-1*(lz_bind+50)*cos(lt_bind),/* to position */
					0, 1, 0); /* up direction */							
							
	}			
	else{ 
		
		sz = sz+lz*cos(htheta*PI/180)+lx*sin(htheta*PI/180);
		sx = sx-lz*sin(htheta*PI/180)+lx*cos(htheta*PI/180);
		
		
		double hx = 50*sin(htheta*PI/180)*cos(vtheta*PI/180);
		double hz = -50*cos(htheta*PI/180)*cos(vtheta*PI/180);
		double hy = 50*sin(vtheta*PI/180);
		
		gluLookAt( sx, ly, sz,        /* from position */
				   sx+hx, ly+hy, sz+hz,        /* to position */
					0, 1, 0);       /* up direction */
	
	
	lx=lz=0;
	
	}	
	
	
}

/********************************************************************
 Reporting Functions
 These functions are registered with the glut window and called 
 when certain events occur.
*/

void ReportError (GLenum errorCode)
{/* Handle error */
}

void PrintAlphaNumericKeysLegend()
{
  printf("\n");
  printf("*************KEYBOARD INPUT*************\n");
  printf("a            Toggle animation\n");
  printf("b            Toggle back face culling\n");
  printf("f            Toggle smooth shading\n");
  printf("l            Toggle lights\n");
  printf("s            Toggle step animation\n");
  printf("\n");
  printf("h            Print this legend\n");
  printf("H            Print state variable values\n");
  printf("q/Q/Esc      Quit\n");
  printf("\n");
  printf("F1           Toggle full screen mode\n");
  printf("****************************************\n");
}

char* state[2] = {"Off", "On"};

void PrintStateVariableValues()
{
  printf("\n");
  printf("*************STATE VARIABLES*************\n");
  printf("back face culling        %s\n",state[myBackFaceCullingOn]);
  printf("smooth shading           %s\n",state[mySmoothShadingOn]);
  printf("lights                   %s\n",state[myLightsOn]);
  printf("*****************************************\n");
}


/********************************************************************
 Callback Functions
 These functions are registered with the glut window and called 
 when certain events occur.
*/

void onInit (int argc, char * argv[])
/* pre:  glut window has been initialized
   post: model has been initialized */
{
  /* clear colour changed to sky blue */
  glClearColor(0.3, 0.3, 0.7, 0.0);
  /* set to draw in window based on depth  */
  glEnable(GL_DEPTH_TEST); 

  /* create light 0 and give it a position */
  GLfloat light0pos[4] = { 30, 100, 25, 0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  /* turn light 0 on */
 

  GLfloat diffuse[] = { 0.7f, 0.7f, 0.7f,1.0f }; 
  GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); 
  glLightfv(GL_LIGHT0, GL_AMBIENT,ambient ); 
  glLightfv(GL_LIGHT0, GL_SPECULAR,specular); 
  
 glEnable(GL_LIGHT0);
   /*turn lighting on */
  glEnable(GL_LIGHTING) ;
  /*turn material colors on */
  //glEnable(GL_COLOR_MATERIAL);
  /*turn back face culling off */
  glDisable(GL_CULL_FACE);


  /*initial parameters */
  rotAngle = 0.0;

  myLightsOn = true;
  mySmoothShadingOn = true;
  myBackFaceCullingOn = false;
  
  
  // settiing all the initial view settings;
  
  wireframe = 0;
  view_angle = 45;
  bind=-1;					//bind = -1 unsets all bindings
  
  sx=sy=sz=0;
  htheta = vtheta =0;
  lx	=	0;
  ly	=	1;
  lz	=	-50;
  
  glEnable(GL_NORMALIZE);
  
 // glEnable(GL_COLOR_MATERIAL);		//enabling color 
  //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); //enableing the material prop fro v=color tracking

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);

}

void onDisplay ()
/* pre:  glut window needs to be refreshed
   post: model is drawn  */
{
  /* clears requested bits (color and depth) in glut window */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //if(wireframe)glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
 // else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  
  
  /* draw entire scene into cleared window */
  glPushMatrix();
   setCamera();
   Display();
  glPopMatrix();

  /* check for any errors when rendering */
  GLenum errorCode = glGetError();
  if (errorCode == GL_NO_ERROR)
    {
      /* double-buffering - swap the back and front buffers */
      glFlush();
      glutSwapBuffers();
    }
  else
    {
      ReportError(errorCode);
    }
}

void onReshape (int width, int height)
/* pre:  glut window has been resized
   post: resets cameras location and aspect to match window */
{
  glViewport(0, 0, width, height);
  if (! isFullScreen)
    {
      theWindowWidth = width;
      theWindowHeight = height;
    }

  /* set camera to view resized area */
  setPerspective(GL_RENDER,0,0);
}


void zoom_in(){
	if(!ortho){
	if(view_angle>20)view_angle-=1;
	else if(view_angle>1)view_angle-=.1;
	else return;
	}
	else{
		 if(view_angle>-8) view_angle-=1;
			
	 }
	setPerspective(GL_RENDER,0,0);
	}
	
void zoom_out(){
	if(!ortho){
	if(view_angle<150)view_angle+=1;
	else if(view_angle<170)view_angle+=.1;
	else return;
	}
	else {
		
		view_angle+=1;
	}
	setPerspective(GL_RENDER,0,0);	
	}
	
	
void onIdle ()
/* pre:  glut window is not doing anything else
   post: scene is updated and re-rendered if necessary */
{
  static int oldTime = 0;
	
  if (isAnimating)
    {
		
      int currentTime = glutGet((GLenum)(GLUT_ELAPSED_TIME));
      /* Ensures fairly constant framerate */
      if (currentTime - oldTime > ANIMATION_DELAY)
        {
	  /* animate the scene */
	  Animate();
	  oldTime = currentTime;
	  /* compute the frame rate */
	  computeFPS();
	  /* notify window it has to be repainted */
	  glutPostRedisplay();
        }
        
     idle_tasks();
    }
}

void onMouseMotion (int x, int y)
/* pre:  mouse is dragged (i.e., moved while button is pressed) within glut window
   post: scene is updated and re-rendered  */
{
  /* notify window that it has to be re-rendered */
  glutPostRedisplay();
}

void onMouseButtonPress (int button, int state, int x, int y)
/* pre:  mouse button has been pressed while within glut window
   post: scene is updated and re-rendered */
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    myMovingOn = true;
    
    
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    myMovingOn = false;
  /* notify window that it has to be re-rendered */
  glutPostRedisplay();
}

void onAlphaNumericKeyPress (unsigned char key, int x, int y) 
/* pre:  key has been pressed
   post: scene is updated and re-rendered */
{
  switch (key)
    {
      /* toggle animation running */
    case 'A':
      isAnimating = ! isAnimating;
      break;
      /* step animation to next frame */
    case 'S':
      Animate();
      break;
      /*toggle back face culling */
    case 'B':
      myBackFaceCullingOn = ! myBackFaceCullingOn;
      if(myBackFaceCullingOn)   glEnable(GL_CULL_FACE);
      else                      glDisable(GL_CULL_FACE);
      break;
      /* toggle smooth shading */
    case 'F':
      mySmoothShadingOn = ! mySmoothShadingOn;
      if (mySmoothShadingOn)  glShadeModel(GL_SMOOTH);
      else                    glShadeModel(GL_FLAT);
      break;
      /*print legend */
    case 'P':
      PrintAlphaNumericKeysLegend();
      break;
      /*print current values */
    case 'H':
      PrintStateVariableValues();
      break;
      /* toggle lights */
    case 'L':
      myLightsOn = ! myLightsOn;
      if (myLightsOn)         glEnable(GL_LIGHTING);
      else                    glDisable(GL_LIGHTING);
      break;

	case 'W' :wireframe = !wireframe;
			 if(wireframe)glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			 else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
	
	case 'O' : ortho = !ortho;
			   if(ortho)view_angle = 0;
			   else view_angle = 45;
			   setPerspective(GL_RENDER,0,0);
			   break;
	
	case 'z': zoom_in();break;
	case 'x': zoom_out();;break;
	
	case 'w':lz = lz-0.5;break;	
	case 's':lz = lz+0.5;break;
				
	case 'd' : lx = lx+0.5;break;
	case 'a' : lx = lx-0.5;break;
	
	case 'e': ly = ly + 0.5;break;
	case 'q': ly = ly - 0.5;break;
	
	
	case 'i':vtheta += 1;break;
	case 'k':vtheta -= 1;break;
	
	case 'j':htheta  = htheta - 1;break;
	case 'l':htheta  = htheta + 1;break;
	
	case 'h' :bind=(bind+1)%10;break;
	
	case 't' :bind=-1;break;
	
      /* quit! */
    case 'Q':
    
    case 27:
      exit(0);
    
    }

  /* notify window that it has to be re-rendered */
  glutPostRedisplay();
}

void onSpecialKeyPress (int key, int x, int y) 
/* pre:  arrow or function key has been pressed
   post: scene is updated and re-rendered */
{
  /* please do not change function of these keys */
  switch (key)
    {
      /* toggle full screen mode */
    case GLUT_KEY_F1:
      isFullScreen = ! isFullScreen;
      if (isFullScreen)
        {
	  theWindowPositionX = glutGet((GLenum)(GLUT_WINDOW_X));
	  theWindowPositionY = glutGet((GLenum)(GLUT_WINDOW_Y));
	  glutFullScreen();
        }
      else                
        {
	  glutReshapeWindow(theWindowWidth, theWindowHeight);
	  glutPositionWindow(theWindowPositionX, theWindowPositionY);
        }
      break;
    }

  /* notify window that it has to be re-rendered */
  glutPostRedisplay();
}

void onVisible (int state)
/* pre:  glut window has just been iconified or restored 
   post: if window is visible, animate model, otherwise don't bother */
{
  if (state == GLUT_VISIBLE)
    {
      /* tell glut to animate model again */
      glutIdleFunc(onIdle);
    }
  else
    {
      glutIdleFunc(NULL);
    }
}


/********************************************************************
 Main Function
*/

int main (int argc, char *argv[]) 
{
  theProgramTitle = argv[0];
  
  load_files();
  
   init_ai();
   
  /* initialize glut */
  glutInit(&argc, argv);      
  /* request initial window size and position on the screen */
  glutInitWindowSize(theWindowWidth, theWindowHeight);
  glutInitWindowPosition(theWindowPositionX, theWindowPositionY);
  /* request full color with double buffering and depth-based rendering */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
 //glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGBA);

  /* create window whose title is the name of the executable */
  glutCreateWindow(theProgramTitle);

  /* tell glut how to display model */
  glutDisplayFunc(onDisplay);
  /* tell glutwhat to do when it would otherwise be idle */
  glutIdleFunc(onIdle); 
  /* tell glut how to respond to changes in window size */
  glutReshapeFunc(onReshape);
  /* tell glut how to handle changes in window visibility */
  glutVisibilityFunc(onVisible);
  /* tell glut how to handle key presses */
  glutKeyboardFunc(onAlphaNumericKeyPress);
  glutSpecialFunc(onSpecialKeyPress);
  /* tell glut how to handle the mouse */
  glutMotionFunc(onMouseMotion);
  glutMouseFunc(onMouseButtonPress);

  /* initialize model */
  onInit(argc, argv);

  /* give control over to glut to handle rendering and interaction  */
  glutMainLoop();

  /* program should never get here */
  return 0;
}
