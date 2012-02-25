/*
 * will gnerate tiles of size 20*20 
 */





extern double poly_d;

#define INCPOLY poly_d += 1

#include <math.h>
#include "draw.h"
#include "conv.cpp"

#ifndef PI
#define PI 3.14159265358979323846f
#endif



float Humcolor[] = { 0.7f, 0.5f, 0.5f, 1.0f };
float Dinocolor[] = { 0.09f, 0.04f, 0.05f, 1.0f };
float offcolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float railcolor[] = { 0.25f, 0.2f, 0.2f, 1.0f };
float barcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float roadcolor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float grasscolor[] = { 0.1f, 0.3f, 0.1f, 1.0f };
float blackchaircolor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float bluechaircolor[] = { 0.0f, 0.0f, 0.1f, 1.0f };
float Treecolor[] =  { 0.1f, 0.3f, 0.1f, 1.0f };
float wallcolor[] =  { 0.3f, 0.35f, 0.3f, 1.0f };
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



void bar(double sy){

double sx  =0.1;
double sz = 0.1;
	
	GLfloat verts_t[24] = {-0.5*sx,0*sy,-0.5*sz,
				0.5*sx,0*sy,-0.5*sz,
				0.5*sx,0*sy,0.5*sz,
				-0.5*sx,0*sy,0.5*sz,
				-0.5*sx,0.5*sy,-0.5*sz,
				0.5*sx,0.5*sy,-0.5*sz,
				0.5*sx,0.5*sy,0.5*sz,
				-0.5*sx,0.5*sy,0.5*sz};
			 	
	GLfloat norms[24] = {	1,1,1,
				1,0,1,
				1,1,0,
				1,0,1,
				0,0,1,
				1,0,0,
				1,1,1,
				1,1,1};
	
	glVertexPointer(3,GL_FLOAT,0,verts_t);
	glNormalPointer(GL_FLOAT,0,norms);
		
		 	 
	GLubyte indices_t[24]  = {0,1,5,4
				,1,2,6,5
				,2,3,7,6
				,7,3,0,4
				,1,0,3,2
				,4,5,6,7}; 	

	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indices_t);

		
}

 void tile_gen(double x, double z,float rail){


	rail = rail/2;
	
	glPushMatrix();
	
	glTranslatef(x,0,z);
		
	
	
	glBegin(GL_QUADS);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);
	glNormal3f(0, 1, 0);								//making the area inside cage
	glVertex3f(-8,0,-8);
	glVertex3f(-8,0,8);
	glVertex3f(8,0,8);
	glVertex3f(8,0,-8);
		
											//makinh the border of the cage	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roadcolor);
	glVertex3f(-10,0,-10);	
	glVertex3f(-10,0,10);		
	glVertex3f(-8,0,10);
	glVertex3f(-8,0,-10);

	glVertex3f(8,0,-10);	
	glVertex3f(8,0,10);
	glVertex3f(10,0,10);
	glVertex3f(10,0,-10);

	glVertex3f(-8,0,-10);
	glVertex3f(-8,0,-8);
	glVertex3f(8,0,-8);
	glVertex3f(8,0,-10);
	
	glVertex3f(-8,0,8);
	glVertex3f(-8,0,10);
	glVertex3f(8,0,10);
	glVertex3f(8,0,8);
	
	glEnd();

	
	if(rail){	
		
	//glColor3fv(railcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, railcolor);
	int i,j;
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	
	glPushMatrix();
	glTranslatef(-8,0,-8);
	for(i = 0;i<67;i++){
	
		glPushMatrix();
		glTranslatef(0,0,i/4);
		bar(6);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(i/4,0,0);
		bar(6);
		glPopMatrix();	
				
	}
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(8,0,8);
	for(i = 0;i<67;i++){	
		glPushMatrix();
		glTranslatef(0,0,-i/4);
		bar(6);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-i/4,0,0);
		bar(6);
		glPopMatrix();	
	}
	
	//making the structurer above the rails
		
	glBegin(GL_QUADS);
	
	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
		
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);
		
	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);

	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
	
		
	glTranslatef(-16,0,0);	
	glBegin(GL_QUADS);
		
	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);
	
	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
		
	glRotatef(-90,0,1,0);		
	glBegin(GL_QUADS);

	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);

	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
	
	glTranslatef(-16,0,0);	
	glBegin(GL_QUADS);

	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);
	
	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
		
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
	glPopMatrix();	
	}
glPopMatrix();
}

 void tile_gen_free(double x, double z,Mesh* m){

	glPushMatrix();
	glTranslatef(x,0,z);
	tile_gen(0,0,0);//not


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackchaircolor);
	mesh_gen(Chairblack,0.3,-5,0,-6,0 );
	mesh_gen(Chairblack,0.3,0,0,-6,0 );	
	mesh_gen(Chairblack,0.3,5,0,-6,0 );	
	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bluechaircolor);
	mesh_gen(Chairblue,.7,-6,0,-5,-90 );
	mesh_gen(Chairblue,.7,-6,0,0,-90 );	
	mesh_gen(Chairblue,.7,-6,0,5,-90 );
	
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,Treecolor);
	glColor3fv(Treecolor);
	mesh_gen(m,0.05,0,0,0,0 );
	
	glPopMatrix();
	
}

 void make_wall(){
	
	glPushMatrix();
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wallcolor);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(-1, 0, 0);
	glVertex3f(14,0,13);
	glVertex3f(14,3,13);
	glVertex3f(14,3,-74);
	glVertex3f(14,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(1, 0, 0);
	glVertex3f(14.5,0,13);
	glVertex3f(14.5,3,13);
	glVertex3f(14.5,3,-74);
	glVertex3f(14.5,0,-74);
	glEnd();
	
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(1, 0, 0);
	glVertex3f(-92,0,13);
	glVertex3f(-92,3,13);
	glVertex3f(-92,3,-74);
	glVertex3f(-92,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(-1, 0, 0);
	glVertex3f(-92.5,0,13);
	glVertex3f(-92.5,3,13);
	glVertex3f(-92.5,3,-74);
	glVertex3f(-92.5,0,-74);
	glEnd();
	
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, -1);
	glVertex3f(14.5,0,13);
	glVertex3f(14.5,3,13);
	glVertex3f(-92.5,3,13);
	glVertex3f(-92.5,0,13);
	glEnd();
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, 1);
	glVertex3f(13.5,0,13.5);
	glVertex3f(13.5,3,13.5);
	glVertex3f(-92.5,3,13.5);
	glVertex3f(-92.5,0,13.5);
	glEnd();
	
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, 1);
	glVertex3f(14.5,0,-74);
	glVertex3f(14.5,3,-74);
	glVertex3f(-92.5,3,-74);
	glVertex3f(-92.5,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, -1);
	glVertex3f(14.5,0,-74.5);
	glVertex3f(14.5,3,-74.5);
	glVertex3f(-92.5,3,-74.5);
	glVertex3f(-92.5,0,-74.5);
	glEnd();
	
	
	glPopMatrix();
	}

 void Display(){	
			
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);

	
	int i,j;
	glBegin(GL_POLYGON);	//generating the ground and sky
	INCPOLY;
	glNormal3f(0, 1, 0);
	glVertex3f(-5000,-0.1,-5000);
	glVertex3f(-5000, -0.1,5000);
	glVertex3f(5000, -0.1,5000);
	glVertex3f(5000, -0.1,-5000);
	glEnd();
	
	make_wall();
	
	tile_gen_free(-10,-10,Tree);
	
	
	tile_gen(-30,-10,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	//mesh_gen(A[1],0.1,-30+Ax[1],0,-10+Az[1],Atheta[1]*Atmode[1] );		//dino
	
	tile_gen(-50,-10,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	//mesh_gen(A[0],0.1,-50+Ax[2],0,-10+Az[2],Atheta[2]*Atmode[2] );
	
	
	tile_gen_free(-70,-10,Tree)	;
	
	
	tile_gen(-10,-30,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	//mesh_gen(A[2],0.05,-10+Ax[0],0,-30+Az[0],Atheta[0]*Atmode[0] );	
	
	tile_gen(-30,-30,0); //not
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, offcolor);
	//mesh_gen(Office,0.035,-31,0,-30,0 );									//office
	
	
	tile_gen_free(-50,-30,Tree);//not

		
	tile_gen(-70,-30,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, A0color);
	//mesh_gen(A[3],0.1,-70+Ax[3],0,-30+Az[3],Atheta[3]*Atmode[3] );	
	
	
	
	tile_gen_free(-10,-50,Tree);//not
	
	
	tile_gen(-30,-50,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	//mesh_gen(A[4],0.1,-30+Ax[1],0,-50+Az[1],Atheta[1]*Atmode[1] );	
	
	tile_gen(-50,-50,5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Dinocolor);
	//mesh_gen(A[5],0.1,-50+Ax[2],0,-50+Az[2],Atheta[2]*Atmode[2] );
		
	tile_gen_free(-70,-50,Tree);//not
	glColor3f(0.8,.8,0.8);
	//mesh_gen(A[0],0.4,-70+Ax[3],0,-50+Az[3],Atheta[3]*Atmode[3] );	
	
//	
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,Humcolor);
//	/*for(i=0;i<10;i++)
//		switch(Hmode[i]){
//			
//		case -1 : //mesh_gen(H[i],.5,Hx[i],0,Hz[i],-180);break;
//		case -2 : //mesh_gen(H[i],.5,Hx[i],0,Hz[i], 180);break;
//		case 1 : //mesh_gen(H[i],.5,Hx[i],0,Hz[i],-90);break;
//		case 2 : //mesh_gen(H[i],.5,Hx[i],0,Hz[i],90);break;

//	
//		}
//	
//	for(i=0;i<3;i++){
//		
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,B0color);
//		//mesh_gen(B[i],.1,ellip_a[i]*cos(ellip_t[i])-40,20,ellip_a[i]*sin(ellip_t[i])-30,0);
//	}	
//	*/
	
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
