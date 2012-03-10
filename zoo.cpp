/*
 * will gnerate tiles of size 20*20 
 */

float ground[4] = {0 ,1,0,0};
float curt =0,last=0;
int lst_cmpile =0;


extern double poly_d;

#define INCPOLY poly_d += 1

#include <math.h>
#include "stdlib.h"
#include "draw.h"
#include "conv.cpp"
#include "models.cpp"
#include "textureutils.cpp"

#define LST_ORG 1
#define LST_SH0 2
#define LST_SH1 3
#define LST_SH2 4

#ifndef PI
#define PI 3.14159265358979323846f
#endif

GLfloat msh[16];
 GLfloat colshad[] = {0,0,0,0.7};

int w_state = 0;

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
	
	create_background(Tree,Chairblack,Chairblue,c,n);

	
	
}	
void hum(GLfloat *c,int n){
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[1],0.1,-30+Ax[1],0,-10+Az[1],Atheta[1]*Atmode[1],c,n );		//dino
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	mesh_gen(A[0],0.1,-50+Ax[2],0,-10+Az[2],Atheta[2]*Atmode[2],c,n );
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	mesh_gen(A[2],0.05,-10+Ax[0],0,-30+Az[0],Atheta[0]*Atmode[0],c,n );	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offcolor);
	mesh_gen(Office,0.035,-37,0,-36,0,c,n );									//office
	
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
	

void disp_lst_make()
{
	glNewList(LST_ORG, GL_COMPILE);
	GLfloat t[] = {10};
	Display(t,1);
	glEndList();
	
	glNewList(LST_SH0, GL_COMPILE);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	config_shadow(ground,light0pos);
	glMatrixMode(GL_MODELVIEW);		
	glPushMatrix();
	glTranslatef(0,0.01,0);
	glMultMatrixf(msh);
	Display(t,0);
	glMatrixMode(GL_MODELVIEW);		
	glPopMatrix();
	glDisable (GL_BLEND);
	
	glEndList();
	
	glNewList(LST_SH1, GL_COMPILE);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	config_shadow(ground,light1pos);
	glMatrixMode(GL_MODELVIEW);		
	glPushMatrix();
	glTranslatef(0,0.01,0);
	glMultMatrixf(msh);
	Display(t,0);
	glMatrixMode(GL_MODELVIEW);		
	glPopMatrix();
	glDisable (GL_BLEND);
	glEndList();
	
	glNewList(LST_SH2, GL_COMPILE);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	config_shadow(ground,light2pos);
	glMatrixMode(GL_MODELVIEW);		
	glPushMatrix();
	glTranslatef(0,0.01,0);
	glMultMatrixf(msh);
	Display(t,0);
	glMatrixMode(GL_MODELVIEW);		
	glPopMatrix();
	glDisable (GL_BLEND);
	glEndList();	
}
void call_disp_list(){

glCallList(LST_ORG );
glCallList(LST_SH0);
glCallList(LST_SH1);
glCallList(LST_SH2);


}
void walkthrough(GLfloat p2lf[],GLfloat p2lt[])
{	


switch(w_state){

case 0:	if(p2lf[1]>1){

	p2lt[1] -=0.1;
	p2lf[1] -=0.1;
	
	}
	else w_state = 1;
	break;
	
case 1:if(p2lf[2] > -18){

	p2lf[2] -= 0.05;
	p2lt[0] -= 10;
	p2lt[2] += 10;
	
	}
	else w_state = 2;
	break;

case 2:if(p2lf[0] > -10){

	p2lf[0] -=0.05;
	
		if(p2lt[0]<0){
		p2lt[0] += 20;
		p2lt[2] -= 10;
		p2lt[1]+= 1;
		}
	}
	else w_state = 3;
	break;
	
case 3:if(p2lf[0] > -20){

	//p2lf[2] -= 0.05;
	p2lf[0] -=0.05;
	
		if(p2lt[0]<10000){
		p2lt[0] -= 20;
		p2lt[2] -= 10;
		//p2lt[1]+= 1;
		}
	}
	else w_state = 4;
	break;

case 4:if(p2lt[1] < 3000){

	p2lt[1] +=10;
	}
	else w_state = 5;
	break;


case 5:if(p2lt[1] > 1){

	p2lt[1] -=10;
	p2lt[0] -=20;
	}
	else w_state = 6;
	break;

case 6:if(p2lf[2] >-40){
	
	p2lf[2] -=0.1;
	if(p2lt[0]<=100)p2lt[0] += 100;	
	else if(p2lt[0]<=-50)p2lt[0] += 10;
		
	}
	else w_state = 7;
	break;

case 7:if(p2lf[0] >-40){
	
	p2lf[0] -=0.1;
	if(p2lt[0]>=-1000)p2lt[0] += 100;	
	else if(p2lt[0]>=-5000)p2lt[0] += 1;	
	}
	else w_state = 8;
	break;

case 8:if(p2lf[2] <0){
	
	p2lf[2] +=0.1;
	if(p2lt[2]<0)p2lt[2]*=-1;
	//if(p2lt[0]>=-1000)
	p2lt[0] -= 100;	
	//else if(p2lt[0]>=5000)p2lt[0] -= 100;	
	}
	else w_state = 9;
	break;
	
}
}

void disp()
{
//************************************************************************************8//

glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texname[0]);
	
        glBindTexture(GL_TEXTURE_2D, m_texname[0]);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,road_tex->height,road_tex->width, 0, GL_RGBA,
//	GL_UNSIGNED_BYTE,road_tex->data);
	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,road_tex->height,road_tex->width,GL_RGBA,GL_UNSIGNED_BYTE,road_tex->data);
glDisable(GL_TEXTURE_2D);

GLfloat t[] = {10};

if(!lst_cmpile){
 disp_lst_make();
 lst_cmpile =1;
 }
 
glPushMatrix(); 
call_disp_list();
glPopMatrix();

//Display(t,1);

hum(t,1);
walkthrough(p2lf,p2lt);


glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//creating shadow for directional source
if(lig0){
config_shadow(ground,light0pos);
glMatrixMode(GL_MODELVIEW);		
glPushMatrix();
glTranslatef(0,0.01,0);
glMultMatrixf(msh);
//Display(t,0);
hum(t,0);
glMatrixMode(GL_MODELVIEW);		
glPopMatrix();
}

if(lig1){
//creating shadow for directional source
config_shadow(ground,light1pos);

glMatrixMode(GL_MODELVIEW);		
glPushMatrix();
glTranslatef(0,0.01,0);
glMultMatrixf(msh);
//Display(t,0);
hum(t,0);
glMatrixMode(GL_MODELVIEW);		
glPopMatrix();
}

if(lig2){
//creating shadow for directional source
config_shadow(ground,light2pos);

glMatrixMode(GL_MODELVIEW);		
glPushMatrix();
glTranslatef(0,0.01,0);
glMultMatrixf(msh);
//Display(t,0);
hum(t,0);
glMatrixMode(GL_MODELVIEW);		
glPopMatrix();
}
glDisable (GL_BLEND);

//glDisable(GL_LIGHT0);
//glDisable(GL_LIGHT1);
//glDisable(GL_LIGHT2);
//glDisable(GL_LIGHTING) ;

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
  
  //int_shadow();
  //disp_lst_make();
  

	
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


void up_walk()
{
switch(w_state){
		
	case 1: pos_1[1] +=0.1;
		if(pos_1[1] > 8) w_state = 2;
		break;
		
	case 2:	pos_1[2] +=0.1;
		if(pos_1[2] > 20) w_state = 3;
		break;
	}
}

void walkt()
{
	
	switch(w_state){
	
	case 2: glTranslatef(0,0,pos_1[2]);
	case 1 : glTranslatef(0,pos_1[1],0);
	}
}
	
void Animate(){
	
	ai_move();
	switch_theta++;
	
	//	up_walk();
	
}




