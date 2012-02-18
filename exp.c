
varray bar = newbar( 

GlFloat vertices[8][3] = {-0.5,0,-0.5},{0.5,0,-0.5},{0.5,0,0.5},{-0.5,0,0.5},
			 {-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5};

void newbar(GlFloat sx,GlFloat sy,GlFloat sz,GlFloat tx,GlFloat ty,GlFloat tz,Glfloat **verts ,GlUbyte **indices)
{
	GlFloat vertices[8][3] = {-0.5*sx-tx,0*sy-ty,-0.5*sz-tz},{0.5*sx-tx,0*sy-ty,-0.5*sz-tz},
				 {0.5*sx-tx,0*sy-ty,0.5*sz-tz},{-0.5*sx-tx,0*sy-ty,0.5*sz-tz},
			 	 {-0.5*sx-tx,0.5*sy-ty,-0.5*sz-tz},{0.5*sx-tx,0.5*sy-ty,-0.5*sz-tz}
			 	 ,{0.5*sx-tx,0.5*sy-ty,0.5*sz-tz},{-0.5*sx-tx,0.5*sy-ty,0.5*sz-tz};
			 	 
	GlUbyte indices[24]   = {0,1,5,4
				,1,2,6,5
				,2,3,7,6
				,7,3,0,4
				,1,0,3,2
				,4,5,6,7}; 
			 	 
	
}

void newcage(GlFloat sx,GlFloat sy,GlFloat sz,GlFloat ***verts ,GlUbyte ***indices)
{
	GlFloat vertices[4][3] = {-0.5*sx,0,-0.5*sz},{0.5*sx,0,-0.5*sz},
				 {0.5*sx,0,0.5*sz},{-0.5*sx,0*sy,0.5*sz};
	
	GlUbyte indices[4] = {1 2 3 4};
	
	GLFloat	barvrtx[4*10][3];
	GLFloat barindx[4];		 
				 
	for(i=0;i<10;i++)
	{
		bar[i] = newbar(0.25,0.25,0.25,-0.5*sx,0*sy,-0.5*sz+i*sz/10,&barvrtx[0][0],&barindx[0]);
		
		bar[i*2+10] = newbar(0.25,0.25,0.25,-0.5*sx+i*sx/10,0*sy,-0.5*sz,&barvrtx[0][0],&barindx[0]);
		
		bar[i*2+20] = newbar(0.25,0.25,0.25,-0.5*sx+sx,0*sy,-0.5*sz+i*sz/10,&barvrtx[0][0],&barindx[0]);
		
		bar[i*2+30] = newbar(0.25,0.25,0.25,-0.5*sx+i*sx/10,0*sy,-0.5*sz+sz,&barvrtx[0][0],&barindx[0]);
	}
}
