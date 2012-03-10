/********************************************************************
  This is the basic framework for GLUT based 
  visualization of objects. Objects are modeled
  and rendered in draw.c

  Author: Vijay Natarajan dsnnnn
*/

/* includes glu and gl correctly*/
float fps= 1;
double  poly_d;
float curr_quat[4],net_quat[4],rot[4][4],rotm[16];
float c_x,c_y,drag=0,f_x,f_y;

float p2lt[3]={0,10,-5000},p2lf[3]={0,10,0},walktru=1;
int lig0=0,lig1=0,lig2=0;

float pos_1[3] = {0,0,0};

#ifndef __APPLE_CC__
#  include "GL/glut.h"         
#else
#  include <GLUT/glut.h>
#endif

#include <stdio.h>
#include <string.h>


#include "trackball.cpp"

GLfloat curr_pos[] = {0,-4,0};

#include "zoo.cpp"

/********************************************************************/
/* Globals */

/*   Variables */

char *      theProgramTitle;
int         theWindowWidth = 700, theWindowHeight = 700;
int         theWindowPositionX = 40, theWindowPositionY = 40;
bool        isAnimating = false;
bool        isFullScreen = false;
int	    wireframe = 0;
int 	    ortho=0;


double lx,ly,lz;	//the  location where we are looking from;
double hx,hy,hz;
double sx,sy,sz;

double vtheta;
double htheta;


extern int bind;

extern double lx_bind;
extern double ly_bind;
extern double lz_bind;

GLfloat lightpos[] =  {1};
GLfloat light0pos[] = { 30, 60, -30, 1 }; //point source
GLfloat light1pos[] = { -50, 100, -30, 1 };   //spot 
GLfloat light2pos[] = { 30, 100, 50, 0 };
GLfloat light1dir[] = { 0, -1, 0, 0 };


GLfloat spotangle = 5;

int n=1;


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
	      
	//fps =   frameCount * 1000.0 / (currentTime - lastFrameTime);
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
		gluPerspective(view_angle,(GLfloat)(viewport[2])/(GLfloat)(viewport[3]), 0.1, 500);
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

	if(!walktru){
	if(bind>=0){
		gluLookAt(  lx_bind, 1.2, lz_bind, /* from position */
					lx_bind-1*(lx_bind+50)*sin(lt_bind), 1, lz_bind-1*(lz_bind+50)*cos(lt_bind),/* to position */
					0, 1, 0); /* up direction */							
							
	}			
	else{ 
		
//		sz = sz+lz*cos(htheta*PI/180)+lx*sin(htheta*PI/180);
//		sx = sx-lz*sin(htheta*PI/180)+lx*cos(htheta*PI/180);
//		
//		
//		double hx = 50*sin(htheta*PI/180)*cos(vtheta*PI/180);
//		double hz = -50*cos(htheta*PI/180)*cos(vtheta*PI/180);
//		double hy = 50*sin(vtheta*PI/180);
		
//		gluLookAt( sx, ly, sz,        /* from position */
//				   sx+hx, ly+hy, sz+hz,        /* to position */
//					0, 1, 0);       /* up direction */
//	

		gluLookAt(0,1,0,0,1,-50,0,1,0);	
	lx=lz=0;
	}}
	else
	{      
		
		gluLookAt(p2lf[0],p2lf[1],p2lf[2],p2lt[0],p2lt[1],p2lt[2],0,1,0);	
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
  printf("A            Toggle animation\n");
  printf("S            Step animation\n");
  printf("B            Toggle back face culling\n");
  printf("F            Toggle smooth shading\n");
  printf("W            Toggle wireframe\n");
  printf("O            Toggle ortho mode\n");
  printf("M            Toggle walkthrough\n");
  
  
  printf("0            Toggle light 0\n");
  printf("1            Toggle light 1\n");
  printf("2            Toggle light 2\n");
  
  
  
  printf("\n");
  printf("P            Print this legend\n");
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
  
  
  //glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  
  //glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
  
  //glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, spotangle);
  
  //glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 1.f);
  			//spot light
  /* turn light 0  and 1 on */
 
 
 

  GLfloat diffuse[] = { 0.9f, 0.9f, 0.9f,1.0f }; 
  GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };
  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); 
  glLightfv(GL_LIGHT0, GL_AMBIENT,ambient ); 
  glLightfv(GL_LIGHT0, GL_SPECULAR,specular); 
  
  glLightfv(GL_LIGHT1, GL_AMBIENT,ambient ); 
  glLightfv(GL_LIGHT1, GL_SPECULAR,specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse); 
  
  glLightfv(GL_LIGHT2, GL_AMBIENT,ambient ); 
  glLightfv(GL_LIGHT2, GL_SPECULAR,specular);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse); 
  
  
  
 //glEnable(GL_LIGHT0);
 //glEnable(GL_LIGHT1);
   /*turn lighting on */
 // glEnable(GL_LIGHTING) ;
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

int i,j;
for(i=0;i<4;i++){
curr_quat[i]=net_quat[i]=0;
}
curr_quat[3] = 1;
net_quat[3] = 1;

for(i=0;i<4;i++)
for(j=0;j<4;j++){
rot[i][j]=0;
rot[i][i] = 1;
}

for(i=0;i<4;i++)
for(j=0;j<4;j++){
rotm[i*4+j] = rot[i][j];
}
	
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
  glMatrixMode(GL_MODELVIEW);
  
  glPushMatrix();
  setCamera();
  
  
  if(!walktru){ 
  glRotatef(htheta,0,1,0);
  glRotatef(vtheta,1,0,0);
  glTranslatef(curr_pos[0],curr_pos[1],curr_pos[2]);
  
  glMultMatrixf(rotm);
  glTranslatef(50,0,30);
  }
  else{
  	//walkt();
  }
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);  
  glLightfv(GL_LIGHT2, GL_POSITION, light2pos);

  glLightfv(GL_LIGHT1, GL_POSITION, light1pos); 	
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, spotangle);
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 1.f);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, light1dir);

  if(lig0 )glEnable(GL_LIGHT0);
  if(lig1 )glEnable(GL_LIGHT1);
  if(lig2 )glEnable(GL_LIGHT2);
  if(lig0||lig1||lig2) glEnable(GL_LIGHTING);
  
  disp();
  //call_disp_list();
  
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHTING);
  glPopMatrix();
  
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
  }

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
  
        
     idle_tasks();
   
}

void onMouseMotion (int x, int y)
/* pre:  mouse is dragged (i.e., moved while button is pressed) within glut window
   post: scene is updated and re-rendered  */
{
  drag = 1;
  
  if(drag ==1){
    	//drag = 0;
    	f_x = x;
    	f_y = y;
    	
    	
    	
    	GLint viewport[4];
  	glGetIntegerv(GL_VIEWPORT, viewport);
  	f_x = (viewport[2]-2*f_x)/viewport[2];
  	f_y = (viewport[3]-2*f_y)/viewport[3];
  	c_x = (viewport[2]-2*c_x)/viewport[2];
  	c_y = (viewport[3]-2*c_y)/viewport[3];
  	
//  	printf("%f\t%f\t%f\t%f\n",f_x,f_y,c_x,c_y);
//    	fflush(stdout);
  
    	///****///going to process quaternions
	int i,j;
	    
    	trackball(curr_quat, c_x,c_y,f_x,f_y);
    	add_quats(net_quat,curr_quat,net_quat);
    	
   	//for(i=0;i<4;i++)printf("q%f\t",curr_quat[i]);
   	//printf("###############\n");
   	//for(i=0;i<4;i++)printf("q%f\t",net_quat[i]);
	//printf("**********\n");
    	
    	build_rotmatrix(rot, net_quat);
   
    	for(i=0;i<4;i++){printf("\n");
    	for(j=0;j<4;j++)
    	{
    	//printf("m%f\t",rot[j][i]);
    	rotm[i*4+j] = rot[j][i];}
    	}
    	c_x = x;
    	c_y = y;
    	
    	
    	}
  glutPostRedisplay();
}

void onMouseButtonPress (int button, int state, int x, int y)
/* pre:  mouse button has been pressed while within glut window
   post: scene is updated and re-rendered */
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    myMovingOn = true;
    c_x = x;
    c_y = y;
    drag = 1;
    //printf("$$$");
    //fflush(stdout);
  }
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    myMovingOn = false;
    drag=0;
    //printf("***");
    //fflush(stdout);
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
	
	case 'w':curr_pos[2]+=1;  break;	
	case 's':curr_pos[2]-=1;break;
				
	case 'd' : curr_pos[0]-=1;break;
	case 'a' :curr_pos[0]+=1;break;
	
	case 'e':curr_pos[1]-=1;break;
	case 'q':curr_pos[1]+=1;break;
	
	
	case 'i':vtheta += 10;break;
	case 'k':vtheta -= 10;break;
	
	case 'j':htheta  = htheta - 1;break;
	case 'l':htheta  = htheta + 1;break;
	
	case 'h' :bind=(bind+1)%10;break;
	
	case 't' :bind=-1;break;
	
	case '0':lig0 = !lig0;break;
	case '1':lig1 = !lig1;break;
	case '2':lig2 = !lig2;break;
	
	case 'M':walktru = !walktru;w_state=0;break;
	
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
  PrintAlphaNumericKeysLegend();
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
