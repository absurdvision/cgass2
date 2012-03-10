
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

extern double poly_d;

extern GLfloat light0pos[];
extern GLfloat light1pos[];
extern GLfloat light2pos[];
extern GLfloat spotangle;

extern GLfloat colshad[];
extern GLfloat msh[];

typedef struct Vertex {
  float x, y, z;
} Vertex;

typedef struct Face {

  int nverts;
  Vertex **verts;
  float normal[3];
} Face;

typedef struct Mesh {

  int nverts;
  Vertex *verts;
  int nfaces;
  Face *faces;
} Mesh;



Mesh *
ReadOffFile(const char *filename)
{
  int i;


  FILE *fp;
  if (!(fp = fopen(filename, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return 0;
  }

  Mesh *mesh = new Mesh();
  if (!mesh) {
    fprintf(stderr, "Unable to allocate memory for file %s\n", filename);
    fclose(fp);
    return 0;
  }

  int nverts = 0;
  int nfaces = 0;
  int nedges = 0;
  int line_count = 0;
  char buffer[1024];
  while (fgets(buffer, 1023, fp)) {
    line_count++;

    char *bufferp = buffer;
    while (isspace(*bufferp)) bufferp++;

    if (*bufferp == '#') continue;
    if (*bufferp == '\0') continue;

    if (nverts == 0) {
      if (!strstr(bufferp, "OFF")) {
        if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
          fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }

        mesh->verts = new Vertex [nverts];
        assert(mesh->verts);
        mesh->faces = new Face [nfaces];
        assert(mesh->faces);
      }
    }
    else if (mesh->nverts < nverts) {

      Vertex& vert = mesh->verts[mesh->nverts++];
      if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
        fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }
    }
    else if (mesh->nfaces < nfaces) {

      Face& face = mesh->faces[mesh->nfaces++];

      bufferp = strtok(bufferp, " \t");
      if (bufferp) face.nverts = atoi(bufferp);
      else {
        fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }

      // Allocate memory for face vertices
      face.verts = new Vertex *[face.nverts];
      assert(face.verts);

      // Read vertex indices for face
      for (i = 0; i < face.nverts; i++) {
        bufferp = strtok(NULL, " \t");
        if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
        else {
          fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }
      }

      face.normal[0] = face.normal[1] = face.normal[2] = 0;
      Vertex *v1 = face.verts[face.nverts-1];
      for (i = 0; i < face.nverts; i++) {
        Vertex *v2 = face.verts[i];
        face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
        face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
        face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
        v1 = v2;
      }

      float squared_normal_length = 0.0;
      squared_normal_length += face.normal[0]*face.normal[0];
      squared_normal_length += face.normal[1]*face.normal[1];
      squared_normal_length += face.normal[2]*face.normal[2];
      float normal_length = sqrt(squared_normal_length);
      if (normal_length > 1.0E-6) {
        face.normal[0] /= normal_length;
        face.normal[1] /= normal_length;
        face.normal[2] /= normal_length;
      }
    }
    else {

      fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
      break;
    }
  }


  if (nfaces != mesh->nfaces) {
    fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, mesh->nfaces, filename);
  }


  fclose(fp);

  return mesh;
 
}


void config_shadow(float ground[],float light[]){
	
	
    float  dot;
    float  shadowMat[4][4];

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];
    
    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];
    
    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];
    
    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];
    
    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];
    
    int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)msh[i*4+j] = shadowMat[i][j];
	
//	colshad[1]=0;
//	colshad[2]=0;
//	colshad[3]=0;
//	colshad[4]=1;
//	
		
}



double mesh_gen(Mesh *mesh,float scale,float xtrans,float ytrans, float ztrans,double theta,float *x,int n){

  int i;
  double height=0;
  scale  *= 2;
  
  double miny=10000;
  double maxx=0,minx=100000,minz=10000,maxz=0;
  
  if(!n) glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,&colshad[0]);
  
  glPushMatrix();
  glTranslatef(xtrans,ytrans,ztrans);
  glRotatef(theta, 0, 1, 0);
  
 
	    
	    
	     
glBegin(GL_TRIANGLES);
  
  // Draw faces
 for (int i = 0; i < mesh->nfaces; i++) {
    Face& face = mesh->faces[i]; 
     poly_d +=1;
     
    glNormal3fv(face.normal);
    for (int j = 0; j < face.nverts; j++) {
     Vertex *vert = face.verts[j];
		
	//enable this for per vertex coloring	
	//float d = sqrt(vert->x/scale*vert->x/scale+vert->y/scale*vert->y/scale+vert->z/scale*vert->z/scale);
	//float vcolor[] = { vert->x/(scale*d), vert->y/(scale*d), vert->z/(scale*d), 1.0f };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vcolor);

    glVertex3f(vert->x/scale, vert->y/scale, vert->z/scale);
     
    }
 
  }
     
glEnd(); 
  
 glPopMatrix();
 return(1);
 }


