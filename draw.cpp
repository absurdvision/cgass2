#include <math.h>
#include "offread.cpp"
#include "draw.h"

#ifndef PI
#define PI 3.14159265358979323846f
#endif

typedef struct Vertarray{


}varray;

typedef struct normlist{

}nlist;


typedef struct Model{
 
//structure to hold all the aspects of a off model
//the function draw should define al the glvertices , nothing else

	float pos[3];
	float col[3];
	float ang[2];
	float bbox[3];
	
	Mesh* data;
	
	void *draw(struct Model);
}model;

typedef struct Cage{
//structur to holdall aspects of a cage
//should not include any thigng other than cage,even the walkway outside
	float pos[3];
	float dim[3];
	bool isbarred;
	unsigned int ncomp;
	
	Mesh **complist;
	vlist *list;
	
	bool *isinside(float[]);
	void *draw(struct Cage);
}cage;

typedef struct Walkway{

	float pos[3];
	float dim[3];
	
	unsigned int ncomp;
	Mesh **complist;
	vlist *list; 
	
	bool *isinside(float[]);
	void *draw(struct Walkway);
}walkway;


void make_scene()
{

}

void idle_tasks();

void Display(int dx,int dy,int dz){

	printf("chaka");
	fflush(stdout);



}

