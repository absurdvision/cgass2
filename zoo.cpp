/*
 * will gnerate tiles of size 20*20 
 */





extern double poly_d;

#define INCPOLY poly_d += 1

#include <math.h>
#include "stdlib.h"
#include "draw.h"
#include "conv.cpp"
#include "models.cpp"
#include "textureutils.cpp"

#ifndef PI
#define PI 3.14159265358979323846f
#endif

GLfloat msh[16];
GLfloat colshad[4];



float Humcolor[] = { 0.7f, 0.5f, 0.5f, 1.0f };
float Dinocolor[] = { 0.5f, 0.5f, 0.1f, 1.0f };
float offcolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float A0color[] =  { 0.7f, 0.5f, 0.3f, 1.0f };
float B0color[] =  { 1.0f, 1.0f, 1.0f, 1.0f };

int bind;

double lx_bind;
double ly_bind;
double lz_bind;
double lt_bind;

Mesh* A[7];
Mesh* H[10];
Mesh* B[3];

Mesh* Office;
Mesh* Chairblack;
Mesh* Chairblue;
Mesh* Chairbrown;
Mesh* Tree;

int Hmode[10];
int Bmode[3];
int Axmode[6];
int Azmode[6];
int Atmode[6];

double height_hum[10];

double Atheta[6];
double Htheta[10];

double Hx[10];
double Hz[10];

double Ax[4];
double Az[4];

double Az_bound_min;
double Az_bound_max;

double Ax_bound_min;
double Ax_bound_max;


double Xbound_min;
double Xbound_max;
double Zbound_min;
double Zbound_max;

double theta;

double rpool[10];

double ellip_t[3];
double ellip_a[3];
double ellip_b[3];

unsigned long int switch_theta = 0;

GLuint m_texname[1];

image *road_tex;



void Display(GLfloat *c,int n){	

if(n){
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texname[0]);
	
        glBindTexture(GL_TEXTURE_2D, m_texname[0]);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,road_tex->height,road_tex->width, 0, GL_RGBA,
	GL_UNSIGNED_BYTE,road_tex->data);
	glDisable(GL_TEXTURE_2D);
}	
	
			
	
	create_background(Tree,Chairblack,Chairblue,c,n);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[1],0.1,-30+Ax[1],0,-10+Az[1],Atheta[1]*Atmode[1],c,n );		//dino
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	mesh_gen(A[0],0.1,-50+Ax[2],0,-10+Az[2],Atheta[2]*Atmode[2],c,n );
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[2],0.05,-10+Ax[0],0,-30+Az[0],Atheta[0]*Atmode[0],c,n );	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offcolor);
	mesh_gen(Office,0.035,-31,0,-30,0,c,n );									//office
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	mesh_gen(A[3],0.1,-70+Ax[3],0,-30+Az[3],Atheta[3]*Atmode[3],c,n );	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[4],0.1,-30+Ax[1],0,-50+Az[1],Atheta[1]*Atmode[1],c,n );	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[5],0.1,-50+Ax[2],0,-50+Az[2],Atheta[2]*Atmode[2],c,n );
		
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	mesh_gen(A[0],0.4,-70+Ax[3],0,-50+Az[3],Atheta[3]*Atmode[3],c,n );	
	
	
	
	for(int i=0;i<10;i++){
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,Humcolor);
		mesh_gen(H[i],.5,Hx[i],0,Hz[i],0,c,n);
	 }
	
	for(int i=0;i<3;i++){
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,B0color);
		mesh_gen(B[i],.1,ellip_a[i]*cos(ellip_t[i])-40,20,ellip_a[i]*sin(ellip_t[i])-30,0,c,n);
	}		
} 

void load_files(){
	
	A[0]= ReadOffFile("../animals/m86.off");
	A[1]= ReadOffFile("../dino.off");
	A[2]= ReadOffFile("../animals/m276.off");
	A[3]= ReadOffFile("../animals/m105.off");
	A[4]= ReadOffFile("../animals/m268.off");
	A[5]= ReadOffFile("../animals/m271.off");
	A[6]= ReadOffFile("../animals/m276.off");
			
	
	H[0]= ReadOffFile("../human/m118.off");
	H[1]= ReadOffFile("../human/m119.off");
	H[2]= ReadOffFile("../human/m120.off");
	H[3]= ReadOffFile("../human/m121.off");
	H[4]= ReadOffFile("../human/m122.off");
	H[5]= ReadOffFile("../human/m124.off");
	H[6]= ReadOffFile("../human/m126.off");
	H[7]= ReadOffFile("../human/m129.off");
	H[8]= ReadOffFile("../human/m130.off");
	H[9]= ReadOffFile("../human/m133.off");
	
	
	
	Office = ReadOffFile("../office.off");
	
	Chairblack = ReadOffFile("../chairblack.off");
	Chairblue = ReadOffFile("../chairblue.off");
	Chairbrown = ReadOffFile("../chairbrown.off");
	
	
	Tree = ReadOffFile("../tree.off");
	
	
	B[0]=ReadOffFile("../birds/m43.off");
	B[1]=ReadOffFile("../birds/m37.off");
	B[2]=ReadOffFile("../birds/m39.off");
	
	
	
	road_tex = text2img("../texture/concrete_bricks_170756_341x256.txt",64,64);
	

		
	}
	
	
void disp()
{

glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  
glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

glLightfv(GL_LIGHT2, GL_POSITION, light2pos);


 
glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, spotangle);
  
glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 1.f);

//glEnable(GL_LIGHT0);
//glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
   /*turn lighting on */
glEnable(GL_LIGHTING) ;
 
 
//************************************************************************************8//

GLfloat t[] = {10};

Display(t,1);

//// creating shadow for point source
//msh[7] = -1/light0pos[1];
//glTranslatef(light0pos[0],light0pos[1],light0pos[2]);
//glMultMatrixf(msh);
//glTranslatef(-light0pos[0],-light0pos[1],-light0pos[2]);
//Display(t,0);

//// creating shadow for spot source
//glMatrixMode(GL_PROJECTION);
//glPushMatrix();
//glLoadIdentity();
///* view scene in perspective */
//gluPerspective(5,1, 0.1, 500);
///* prepare to work with model again */
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//		
//msh[7] = -1/light0pos[1];
//glTranslatef(light1pos[0],light1pos[1],light1pos[2]);
//glMultMatrixf(msh);
//glTranslatef(-light1pos[0],-light1pos[1],-light1pos[2]);
//Display(t,0);
//glMatrixMode(GL_PROJECTION);
//glPopMatrix();
//glMatrixMode(GL_MODELVIEW);


//creating shadow for directional source
	
	glPushMatrix();
	
	//msh[15] = -1/light2pos[1];
	msh[7] = -1;
	msh[5]=0;
	//msh[15] = 1;
	//glTranslatef(light2pos[0],light2pos[1],light2pos[2]);
	glMultMatrixf(msh);
	//glTranslatef(-light2pos[0],-light2pos[1],-light2pos[2]);
	Display(t,0);
	
	glPopMatrix();
	//msh[15] = 0;
	msh[5] = 1;


glDisable(GL_LIGHT0);
glDisable(GL_LIGHT1);
glDisable(GL_LIGHT2);

   /*turn lighting on */
glDisable(GL_LIGHTING) ;

}


void init_ai(){
	
	
	
	Hx[0] = 0;
	Hx[1] = 0;
	Hx[2] = -30;
	Hx[3] = -20;
	Hx[4] = -20;
	Hx[5] = -40;
	Hx[6] = -50;
	Hx[7] = -50;
	Hx[8] = -10;
	Hx[9] = -60;
	
	Hz[0] = -5;
	Hz[1] = -10;
	Hz[2] = -20;
	Hz[3] = -40;
	Hz[4] = -20;
	Hz[5] = -20;
	Hz[6] = -40;
	Hz[7] = -40;
	Hz[8] = -20;
	Hz[9] = -40;
	
	Hmode[0] = -1;
	Hmode[1] = -2;
	Hmode[2] = 1;
	Hmode[3] = -1;
	Hmode[4] = 1;
	Hmode[5] = -1;
	Hmode[6] = -2;
	Hmode[7] = 1;
	Hmode[8] = -1;
	Hmode[9] = 1;
	
	Htheta[0]=0;
	Htheta[1]=0;
	Htheta[2]=0;
	Htheta[3]=0;
	Htheta[4]=0;
	Htheta[5]=0;
	Htheta[6]=0;
	Htheta[7]=0;
	Htheta[8]=0;
	Htheta[9]=0;
	
	Xbound_max = 0;
	Zbound_max = 0;
	
	Xbound_min = -70;
	Zbound_min = -50;
	
	int i;
	for(i=0;i<4;i++){
		Ax[i]=0;Az[i]=0;}
		
	Axmode[0] = -1;
	Azmode[0] = +1;
	Atmode[0] = +1;
	
	Axmode[1] = +1;
	Azmode[1] = -1;
	Atmode[1] = -1;
	
	Axmode[2] = +1;
	Azmode[2] = -1;
	Atmode[2] = +1;
	
	Axmode[3] = -1;
	Azmode[3] = +1;
	Atmode[3] = -1;
	
	Axmode[4] = +1;
	Azmode[4] = +1;
	Atmode[4] = -1;
	
	Atheta[0] = 0;
	Atheta[1] = 90;
	Atheta[2] = 45;
	Atheta[3] = 67;
	
	
	
	Az_bound_min=-4;
    Az_bound_max=4;

    Ax_bound_min=-4;
    Ax_bound_max=4;	
    
    for(i=0;i<10;i++)height_hum[i]=//mesh_gen(H[i],.50,0,0,0,0);
    
  ellip_t[0] =-34;
  ellip_t[1] = -27;
  ellip_t[2] = -6;
  
  ellip_a[0] = -70;
  ellip_a[1] = -30;
  ellip_a[2] = -60;
  
  ellip_b[0] = -60;
  ellip_b[1] = -50;
  ellip_b[2] = -30;
  
  int_shadow();
  

	
}

void idle_tasks(){

if(switch_theta == 1000) Atmode[0] *= -1;
if(switch_theta == 10000)Atmode[1] *= -1;
if(switch_theta == 100)Atmode[2] *= -1;
if(switch_theta == 40000)Atmode[3] *= -1;

}

 void ai_move(){
	
	//we are going to move the humans so that they donot collide and go out of the region
	
	int i,j,flag;
	
	for(i=0;i<10;i++){rpool[i] = -1*((float)(random()%100))/1000;}
	
	//now going to check if we are in any junction so that we can change our paths
	for(i=0;i<10;i++)switch(Hmode[i]){
		
		case 1:if((fabs(Hx[i]/20 - (int)(Hx[i]/20))<=.01))
					{Hmode[i] *= (-1);Hx[i] = ((int)(Hx[i]/20))*20;Hx[i]-=1;Htheta[i]=180;}
				break;
		
		case 2:if((fabs(Hx[i]/20 - (int)(Hx[i]/20))<=.01))
					{Hmode[i] *= (-1);Hx[i] = ((int)(Hx[i]/20))*20;Hx[i]+=1;Htheta[i]=0;}
				break;
				
		case -1:if((fabs(Hz[i]/20 - (int)(Hz[i]/20))<=.01))
					{Hmode[i] *= (-1);Hz[i] = ((int)(Hz[i]/20))*20;Hz[i]-=1;Htheta[i]=90;}
				break;
		case -2:if((fabs(Hz[i]/20 - (int)(Hz[i]/20))<=.01))
					{Hmode[i] *= (-1);Hz[i] = ((int)(Hz[i]/20))*20;Hz[i]+=1;Htheta[i]=-90;}
				break;
	}
	
	//going to check for border crosses.if found will reverse the directions
	for(i=0;i<10;i++)switch(Hmode[i]){
		
		case 1  : if(Hx[i]+rpool[i] < Xbound_min)Hmode[i] = 2;Htheta[i]=90;break; 
		case 2  : if(Hx[i]-rpool[i] > Xbound_max)Hmode[i] = 1;Htheta[i]=-90;break;
		case -1 : if(Hz[i]+rpool[i] < Xbound_min)Hmode[i] = -2;Htheta[i]=0;break;
		case -2 : if(Hz[i]-rpool[i] > Xbound_max)Hmode[i] = -1;Htheta[i]=180;break;
	}
	
	//checking for any collisions bt humans.if found they move in opposite of incoming directions
	for(i=0;i<10;i++)switch(Hmode[i]){
		
		case 1:
			flag = 1;
			for(j=0;j<5;j++) if((Hx[i]+rpool[i] < Hx[j])&&(Hx[i]>Hx[j])&&(i!=j)&&(Hz[i]==Hz[j]))
			{flag =0;Hmode[i] = 2; Htheta[i]=90;}
			
			if(flag)Hx[i] = Hx[i]+rpool[i];		
			break;
		
		case 2 :
			flag =1;
			for(j=0;j<5;j++) if(((Hx[i]-rpool[i])>Hx[j])&&(Hx[i]<Hx[j])&&(i!=j)&&(Hz[i]==Hz[j]))
				{flag = 0;Hmode[i] = 1;Htheta[i]=-90;}	
						
			if(flag)Hx[i] = Hx[i]-rpool[i];
			break;
			
		
		case -1:
			flag = 1;
				for(j=0;j<5;j++) if((Hz[i]+rpool[i] < Hz[j])&&(Hz[i]>Hz[j])&&(i!=j)&&(Hx[i]==Hx[j]))
					{flag =0;Hmode[i] = -2; Htheta[i]=0;}
				
				if(flag) Hz[i] = Hz[i]+rpool[i];		
				break;
		
		case -2:
			flag =1;
			for(j=0;j<5;j++) if(((Hz[i]-rpool[i])>Hz[j])&&(Hz[i]<Hz[j])&&(i!=j)&&(Hx[i]==Hx[j]))
				{flag = 0;Hmode[i] = -1;Htheta[i]=180;}
				
			if(flag)Hz[i] = Hz[i]-rpool[i];
			break;
		}
	
	//going to animate animals
	
	for(i=0;i<5;i++)switch(Axmode[i]){
	
		case 1: if(Ax[i]+rpool[i] < Ax_bound_min)Axmode[i] *= (-1);
				else Ax[i]+=rpool[i];
				break;
				
		case -1:if(Ax[i]+rpool[i] > Ax_bound_max)Axmode[i] *= (-1);
				else Ax[i]-=rpool[i];
				break;
	}	
	
	for(i=0;i<5;i++)switch(Azmode[i]){
	
		case 1: if(Az[i]+rpool[i] < Az_bound_min)Azmode[i] *= (-1);
				else Az[i]+=rpool[i];
				break;
				
		case -1:if(Az[i]+rpool[i] > Az_bound_max)Azmode[i] *= (-1);
				else Az[i]-=rpool[i];
				break;
	}			
	
	//switch(Hmode[i])
	for(i=0;i<10;i++)Htheta[i] += (rpool[i]-0.5)/10;
	
	Atheta[0] += rpool[0]*10;
	Atheta[1] += rpool[1]*5;
	Atheta[2] += rpool[2]*10;
	Atheta[3] += rpool[3]*7;
	
	
	if(bind>=0){lx_bind = Hx[bind];ly_bind = height_hum[bind];lz_bind = Hz[bind];lt_bind = Htheta[bind];}
	
	for(i=0;i<3;i++)ellip_t[i]+=rpool[i]/10;
	
	//gonna animate birds;
	
	
	
	
}
	
void Animate(){
	
	ai_move();
	switch_theta++;
}
