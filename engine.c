#include "draw.c"

void make_scenary_list(sceneinfo scene){

int i;

glPopMatrix();
for(i = 0;i<scene.ncages;i++)
	scene.cages[i]->draw(scene.cages[i]);
	
for(i = 0;i<scene.nwlakways;i++)
	scene.walkways[i]->draw(scene.walkways[i]);
	
glPushMatrix();
	
}
