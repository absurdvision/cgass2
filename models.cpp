
extern GLuint m_texname[1];

float barcolor[] = { 0.1f, 0.05f, 0.05, 1.0f };
float roadcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float grasscolor[] = { 0.1f, 0.3f, 0.1f, 1.0f };
float blackchaircolor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float bluechaircolor[] = { 0.0f, 0.0f, 0.1f, 1.0f };
float Treecolor[] =  { 0.1f, 0.3f, 0.1f, 1.0f };
float wallcolor[] =  { 0.3f, 0.35f, 0.3f, 1.0f };



GLfloat verts_t_b[24] = {-0.5*0.1,0*6,-0.5*0.1,
				0.5*0.1,0*6,-0.5*0.1,
				0.5*0.1,0*6,0.5*0.1,
				-0.5*0.1,0*6,0.5*0.1,
				-0.5*0.1,0.5*6,-0.5*0.1,
				0.5*0.1,0.5*6,-0.5*0.1,
				0.5*0.1,0.5*6,0.5*0.1,
				-0.5*0.1,0.5*6,0.5*0.1};
			 	
GLfloat norms_b[24] = {	1,1,1,
			1,0,1,
			1,1,0,
			1,0,1,
			0,0,1,
			1,0,0,
			1,1,1,
			1,1,1};
			
GLubyte indices_t_b[24]  ={0,1,5,4
			,1,2,6,5
			,2,3,7,6
			,7,3,0,4
			,1,0,3,2
			,4,5,6,7}; 

				


void make_a_tile(GLfloat x,GLfloat y,GLfloat xx,GLfloat yy,GLfloat d){
	int i,j;
	
	
	for(i=x;i<xx;i+=1)
	for(j=x;j<yy;j+=1)
	{
		glVertex3f(i,d,j);
		glVertex3f(i,d,j+1);
		glVertex3f(i+1,d,j+1);
		glVertex3f(i+1,d,j);
	}
	
	/* using vertex arrays
	*/

}


void make_a_tex_tile(GLfloat x,GLfloat y,GLfloat xx,GLfloat yy){
	
	int i,j;
	for(i=x;i<xx;i+=1)
	for(j=x;j<yy;j+=1)
	{
		glTexCoord2f(0.0, 0.0);glVertex3f(i,-0.01,j);
		glTexCoord2f(0.0, 1.0);glVertex3f(i,-0.01,j+1);
		glTexCoord2f(1.0, 1.0);glVertex3f(i+1,-0.01,j+1);
		glTexCoord2f(1.0, 0.0);glVertex3f(i+1,-0.01,j);
	}

}



void bar(double sy){

	
	
	glVertexPointer(3,GL_FLOAT,0,verts_t_b);
	glNormalPointer(GL_FLOAT,0,norms_b);

	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indices_t_b);

		
}



void tile_gen(double x, double z,float rail,int n){


	rail = rail/2;
	
	glPushMatrix();
	
	glTranslatef(x,0,z);
	
	glPushMatrix();
if(n){
	glBegin(GL_QUADS);       
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);
	
	glNormal3f(0, 1, 0);	
	make_a_tile(-8,-8,8,8,-0.01);							//making the area inside cage
//	int i,j;
//	for(i=-8;i<0;i+=1)
//	for(j=-8;j<0;j+=1)
//	{
//		glVertex3f(i,-0.01,j);
//		glVertex3f(i,-0.01,j+1);
//		glVertex3f(i+1,-0.01,j+1);
//		glVertex3f(i+1,-0.01,j);
//	}
//	glVertex3f(-8,-0.01,-8);
//	glVertex3f(-6,-0.01,-8);
//	glvertex3f(-6,-0.01,-6);
//	glvertex3f(-8,-0.01,-6);
//	
//	
//	
//	glVertex3f(-8,-0.01,8);
//	glVertex3f(8,-0.01,8);
//	glVertex3f(8,-0.01,-8);
	glEnd();
	}
	
	
	glPopMatrix();
if(n){	
	
	glEnable(GL_TEXTURE_2D);
        //glShadeModel(GL_FLAT); 
        glBindTexture(GL_TEXTURE_2D,m_texname[0]); 
		
	glBegin(GL_QUADS);										//makinh the border of the cage	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roadcolor);
	
	//make_a_tex_tile(-10,-10,-8,10);
	
	glTexCoord2f(0.0, 0.0);glVertex3f(-10,-0.01,-10);	
	glTexCoord2f(0.0, 100.0);glVertex3f(-10,-0.01,10);		
	glTexCoord2f(5.0, 100.0);glVertex3f(-8,-0.01,10);
	glTexCoord2f(5.0, 0.0);glVertex3f(-8,-0.01,-10);

	glTexCoord2f(0.0, 0.0);glVertex3f(8,-0.01,-10);	
	glTexCoord2f(0.0, 100.0);glVertex3f(8,-0.01,10);
	glTexCoord2f(5.0, 100.0);glVertex3f(10,-0.01,10);
	glTexCoord2f(5.0, 0.0);glVertex3f(10,-0.01,-10);

	glTexCoord2f(0.0, 0.0);glVertex3f(-8,-0.01,-10);
	glTexCoord2f(0.0, 5.0);glVertex3f(-8,-0.01,-8);
	glTexCoord2f(100.0, 5.0);glVertex3f(8,-0.01,-8);
	glTexCoord2f(100.0, 0.0);glVertex3f(8,-0.01,-10);
	
	glTexCoord2f(0.0, 0.0);glVertex3f(-8,-0.01,8);
	glTexCoord2f(0.0, 5.0);glVertex3f(-8,-0.01,10);
	glTexCoord2f(100.0, 5.0);glVertex3f(8,-0.01,10);
	glTexCoord2f(100.0, 0.0);glVertex3f(8,-0.01,8);
	
	glEnd();
         
        glDisable(GL_TEXTURE_2D);
        
        }
	
	if(rail){	
	if(n)glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, barcolor);
	else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colshad);
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

void tile_gen_free(double x, double z,Mesh* m,Mesh *Chairblack,Mesh *Chairblue,GLfloat *c,int n){

	glPushMatrix();
	glTranslatef(x,0,z);
	tile_gen(0,0,0,n);//not


	if(n)glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackchaircolor);
	else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,colshad);
	mesh_gen(Chairblack,0.3,-5,0,-6,0,c,n);
	mesh_gen(Chairblack,0.3,0,0,-6,0,c,n );	
	mesh_gen(Chairblack,0.3,5,0,-6,0,c,n );	
	

	if(n) glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bluechaircolor);
	else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,colshad);
	mesh_gen(Chairblue,.7,-6,0,-5,-90,c,n );
	mesh_gen(Chairblue,.7,-6,0,0,-90,c,n );	
	mesh_gen(Chairblue,.7,-6,0,5,-90,c,n );
	
	
	if(n) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,Treecolor);
	else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,colshad);
	mesh_gen(m,0.05,0,0,0,0,c,n );
	
	glPopMatrix();
	
}


void make_wall(int n){
	
	glPushMatrix();
	
	if(n)glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wallcolor);
	else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colshad);
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


void create_background(Mesh *Tree,Mesh *Chairblack,Mesh *Chairblue,GLfloat *c,int n)
{
if(n){	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);

	glBegin(GL_QUADS);	//generating the ground 
	glNormal3f(0, 1, 0);
	make_a_tile(-100,-100,20,20,-0.1);
//	glVertex3f(-5000,-0.1,-5000);
//	glVertex3f(-5000, -0.1,5000);
//	glVertex3f(5000, -0.1,5000);
//	glVertex3f(5000, -0.1,-5000);
	glEnd();
}
	make_wall(n);
	tile_gen_free(-10,-10,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-30,-10,5,n);
	tile_gen(-50,-10,5,n);
	tile_gen_free(-70,-10,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-10,-30,5,n);
	tile_gen(-30,-30,0,n);
	tile_gen_free(-50,-30,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-70,-30,5,n);
	tile_gen_free(-10,-50,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-30,-50,5,n);
	tile_gen(-50,-50,5,n);
	tile_gen_free(-70,-50,Tree,Chairblack,Chairblue,c,n);
		
}
