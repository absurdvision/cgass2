#  include "GL/glut.h"   
#include <stdio.h>
#include <string.h>
#include "draw.cpp"



char *	theProgramTitle;
int	theWindowWidth = 700, theWindowHeight = 700;
int	theWindowPositionX = 40, theWindowPositionY = 40;
bool	isAnimating = false;
bool	isFullScreen = false;
int 	wireframe = 0;
int 	ortho=0;


int bind;
double poly_d;


/* Constants */
const int   ANIMATION_DELAY = 1;    /* milliseconds between rendering */


void computeFPS ()
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
		gluPerspective(45, (GLfloat)(viewport[2]) / (GLfloat)(viewport[3]), 0.1, 500);
		/* prepare to work with model again */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else{
		/* set camera to view viewport area */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		/*	 view scene in perspective */
		glOrtho((-10-(45)/2)*(GLfloat)(viewport[2]) / (GLfloat)(viewport[3]),
		(0.1+45/2)*(GLfloat)(viewport[2]) / (GLfloat)(viewport[3]),
		0.1-45/2,10+45/2,
		-0.1,-5000);
		/* prepare to work with model again */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
  
}

void setCamera ()
{
	gluLookAt( 0, 1, 0, 0,0,0,0, 1, 0);						
}



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
  bind=-1;					//bind = -1 unsets all bindings
  

  
  glEnable(GL_NORMALIZE);
  
 // glEnable(GL_COLOR_MATERIAL);		//enabling color 
  //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); //enableing the material prop fro v=color tracking

}

void onDisplay ()
{
  /* clears requested bits (color and depth) in glut window */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
   setCamera();
   Display(1,1,1);
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

	
	
void onIdle ()
{
  static int oldTime = 0;
	
  if (isAnimating)
    {
		
      int currentTime = glutGet((GLenum)(GLUT_ELAPSED_TIME));
      /* Ensures fairly constant framerate */
      if (currentTime - oldTime > ANIMATION_DELAY)
        {
	  /* animate the scene */
	  //Animate();
	  oldTime = currentTime;
	  /* compute the frame rate */
	  computeFPS();
	  /* notify window it has to be repainted */
	  glutPostRedisplay();
        }
        
     //idle_tasks();
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
      //Animate();
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
			   setPerspective(GL_RENDER,0,0);
			   break;
	
	case 'z': break;
	case 'x': break;
	
	case 'w':break;	
	case 's':break;
				
	case 'd' :break;
	case 'a' :break;
	
	case 'e':break;
	case 'q':break;
	
	
	case 'i':break;
	case 'k':break;
	
	case 'j':break;
	case 'l':break;
	
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
