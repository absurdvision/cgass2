
typedef struct Image{
	
	int width;
	int height;
	char depth;
	
	GLubyte *data;

}image;



image* text2img(const char* fname,int hp,int wp){

	int i;
	if(!fname){printf("\nError in text2img :  no file name specified");return NULL;};

	for(i=0;(i<strlen(fname))&&(fname[i]!='/');i++);
	i++;
	for(;(i<strlen(fname))&&(fname[i]!='/');i++);
	i++;
	
	for(;(i<strlen(fname))&&(fname[i]!='.');i++);
	if(i==strlen(fname)){printf("Error in text2img :  Invalid filename");return NULL;}
	for( ;(i>0)&&(fname[i]!='_');i--);
	if(i==0){printf("\nError in text2img :  Invalid filename");return NULL;}
	
		
	FILE *fil = fopen(fname,"r");
	if(!fil){printf("\nError in text2img :  File not found");return NULL;}
	
	for(;(i<strlen(fname))&&(fname[i]!='x');i++);
	
	int w,h,k;
	i--;
	
	for(k=1,w=0;fname[i]!='_';i--,k*=10)w = w+k*(fname[i]-'0');
	
	for(;(i<strlen(fname))&&(fname[i]!='.');i++);
	i--;
	
	for(k=1,h=0;fname[i]!='x';i--,k*=10)h = h+k*(fname[i]-'0');
	
	//printf("\n %d \t %d",h,w);
	
	image *img = (image*)malloc(sizeof(image));
	img->width = h;
	img->height = w;
	img->depth = 4;
	
	img->data = (GLubyte*)malloc(sizeof(GLubyte)*img->width*img->height*img->depth);
	
	int r;
	
	for(int i=0;fscanf(fil,"%d",&r)!=EOF;i++)img->data[i] = (GLubyte)r;
	
	
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
        //printf("wewaraweraw");
        //fflush(stdout);
        
	return img;
}


