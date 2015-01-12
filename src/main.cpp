//
//  main.cpp
//  Springy
//
//  Created by Uriana on 13-11-1.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
//#include <GLUI/glui.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#pragma comment(lib,"opengl32.lib")  
#pragma comment(lib,"GLU32.LIB")  
#pragma comment(lib,"GLUT32.LIB")  

#include "Vector3D.h"
#include "EulerIntegration.h"
#include "ForceAir.h"
#include "loadMusic.h"

#define WIDTH 1280
#define HEIGHT 720

#define N SIZE*SIZE
#define SIZE 30

GLfloat posx = 3.0;    //camera position
GLfloat posy = 1.0;    //camera position
bool paused = true;
bool displayMode = true;//display mode "fixed"
bool normal = false;
bool ro_all = false;
float theta = 0.0;	//rotate theta
//lighting
GLfloat light0_pos[4] = {0.0, 3.0, 3.0, 0.0};
//ambient light setting
GLfloat global_ambient[4] = {1.0,1.0,1.0,1.0};
//initiate different type of light with a defined lighting structure
typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0}
};

lightingStruct coloredLighting = {
   {0.2, 0.0, 0.0, 1.0},
   {0.0, 1.0, 0.0, 1.0},
   {0.0, 0.0, 1.0, 1.0}
};
//store current lighting parameters
lightingStruct *currentLighting;
//initiate different type of material with a defined material structure
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;
//body material
materialStruct original_body_mat = {
	{0.5,0.5,0.5,1.0},
	{0.5,0.5,0.5,1.0},
	{1.0,1.0,1.0,0.5},
	20.0
};
//store current material parameters
materialStruct * currentBodyMat;

int particle = 0;		//particle type

double frames_per_second = 30;   // display rate
int refreshTime = 0;
double size = 2;        //the size of the box
float bDrate = 0;	//beat decrease rate
float factor = 4;	//size

Integration * integ;
EulerIntegration ei(0.1);

std::vector<Particle *> s(N);
std::vector<Particle *> s_next(N);

World w;
loadMusic music("Endeavors.mp3");
//loadMusic music("friend.mp3");
//loadMusic music("piano.mp3");
float **spectrum;

using namespace std;

void PSinitialize()
{
    float mass = 0.1;

    
    //for (int n = 0; n < N; n++) {
        for (int i = 0; i < SIZE; i++)
                for (int k = 0; k < SIZE; k++) {
                    int n = i*SIZE + k;
                    Particle *p = new Particle(Point3D(factor*(float)(i-SIZE/2)/SIZE, -1.9, factor*(float)(k-SIZE/2)/SIZE), Vector3D(0,0,0), mass, Point3D(0.5,0.5,0.5));
                    //printf("%f \t",p->getPosition().x);
                    s[n] = p;
                    
                    Particle *p_init = new Particle();
                    s_next[n] = p_init;
                }
    
    w.addObstacle(new ObstaclePlane(Vector3D(0,1,0), Point3D(0,-2,0)));
    /*w.addObstacle(new ObstaclePlane(Vector3D(0,-1,0), Point3D(0,2,0)));
	w.addObstacle(new ObstaclePlane(Vector3D(1,0,0), Point3D(-2,0,0)));
	w.addObstacle(new ObstaclePlane(Vector3D(-1,0,0), Point3D(2,0,0)));
	w.addObstacle(new ObstaclePlane(Vector3D(0,0,-1), Point3D(0,0,2)));
	w.addObstacle(new ObstaclePlane(Vector3D(0,0,1), Point3D(0,0,-2)));
*/
	spectrum = new float*[SIZE+1];
	for(int i = 0; i < SIZE+1; ++i)
		spectrum[i] = new float[music.sampleSize];

	for(int i = 0; i < music.sampleSize; i++)
		spectrum[SIZE][i] = 0;
}
void onBeat()
{
	 for (int i = 0; i < SIZE; i++)
                for (int k = 0; k < SIZE; k++) {
                    int n = i*SIZE + k;
					s[n]->setPosition(Point3D(factor*(float)(i-SIZE/2)/SIZE, s[n]->getPosition().y, factor*(float)(k-SIZE/2)/SIZE));
				}
}

void Spectrum()
{
	//printf("%d\t",refreshTime%SIZE);
	spectrum[refreshTime%SIZE] = music.spec;
	float maxHeight = 4.0;
	//printf("%d\t",refreshTime%SIZE);
	//first row particles
	for (int i = SIZE/2; i < SIZE; i++){
		int n = i *SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * music.spec[(int)(((float)(i-SIZE/2)/SIZE) * music.sampleSize )], s[n]->getPosition().z));
	}

	for (int i = SIZE/2 - 1; i >= 0; i--){
		int n = i *SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * music.spec[(int)(((float)(SIZE/2-i)/SIZE) * music.sampleSize) ], s[n]->getPosition().z));
	}

	//for rest rows
	if(displayMode){
	for (int i = SIZE/2; i < SIZE; i++)
	for (int j = 1; j < SIZE; j++){
		int n = i *SIZE + j;
		int newj = refreshTime%SIZE - j;
		if (newj < 0 && refreshTime < SIZE)
			newj = SIZE;
		else if(newj < 0)
			newj += SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * spectrum[newj][(int)(((float)(i-SIZE/2)/SIZE) * music.sampleSize )], s[n]->getPosition().z));
	}

	for (int i = SIZE/2 - 1; i >= 0; i--)
		for (int j = 1; j < SIZE; j++){
		int n = i *SIZE + j;
		int newj = refreshTime%SIZE - j;
		if (newj < 0 && refreshTime < SIZE)
			newj = SIZE;
		else if(newj < 0)
			newj += SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * spectrum[newj][(int)(((float)(SIZE/2-i)/SIZE) * music.sampleSize) ], s[n]->getPosition().z));
		}
	}else{
		
	if (refreshTime%SIZE != 0){
		//for (int i = 0; i < SIZE; i++){
		//	int n = i *SIZE + 10;
		//	//printf("%f\t", spectrum[0][0]);
		//	s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * spectrum[0][(int)(((float)(i)/SIZE) * music.sampleSize )], s[n]->getPosition().z));
	
		//}
	for (int i = SIZE/2; i < SIZE; i++){
		int n = i *SIZE + refreshTime%SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * spectrum[0][(int)(((float)(i-SIZE/2)/SIZE) * music.sampleSize /2)], s[n]->getPosition().z));
	}

	for (int i = SIZE/2 - 1; i >= 0; i--){
		int n = i *SIZE + refreshTime%SIZE;
		s[n]->setPosition(Point3D(s[n]->getPosition().x, -1.99 + maxHeight * spectrum[0][(int)(((float)(SIZE/2-i)/SIZE) * music.sampleSize) /2], s[n]->getPosition().z));
	}
	}
	}
}

void Euler()
{
    //EulerIntegration ei(0.01);
    integ = &ei;
    
}



void idle() {
	//rotate
	if(ro_all){
		theta+=0.5;
		if(theta>360.0)
			theta=theta-360.0;
	}

    double start = integ->getTime();
    clock_t start_time = clock();
	music.FrequencyAnalysis();
	if(!paused){
	if(music.beat == true){
		bDrate = 0;
		factor = 5;
		onBeat();
	}else {
		if (factor != 4){
			bDrate +=0.1;
			factor = 5 - bDrate;
			onBeat();
		}
	}
		Spectrum();
	}
    for (int n = 0; n < N; n++){
        integ->update(*s[n], *s_next[n], w);
    }
    
    double tau = 1.0 / frames_per_second;
    while ((integ->getTime()) - start < tau){
		music.FrequencyAnalysis();
		if (!paused)
		{
		if(music.beat == true){
		bDrate = 0;
		factor = 5;
		onBeat();
		}else {
			if (factor != 4){
				bDrate +=0.1;
				factor = 5 - bDrate;
				onBeat();
			}
		}
		
			Spectrum();
		}
        for (int n = 0; n < N; n++){
            integ->update(*s[n], *s_next[n], w);
        }
	}
    while (((double)(clock()) - start_time) / CLOCKS_PER_SEC < tau)
        ;
    glutPostRedisplay();
	if(!paused)
		refreshTime++;
}
void output(float x, float y, char *string)
{
	int len, i; glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	float textC[4] = {1,1,1,1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, textC);
	glMaterialfv(GL_FRONT, GL_AMBIENT, textC);
	//glColor3f(1,1,1);
	if(!paused)
		output(-2.8,2.8,"now playing: MitiS - Endeavors");
	else
		output(-2.8,2.8,"Paused");
	output(-2.8,2.6,"Press P to toggle pause, N to toggle normalize, 1 and 2 to adjust FFT size");
	if(normal)

		output(-2.8,-2.8,"Disable normalization to enable Beat detection and BPM calculation");
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
 	gluLookAt(posx, posy, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//isometric view
    glRotatef(theta,0.0,1.0,0.0);//rotate the whole object
    
	switch(particle){
	case 0:
    glPointSize(3);
    glBegin(GL_POINTS);
	//printf("%f\t",s[1]->getPosition().y);
    for (int n = 0; n < N; n++) {
		GLfloat color[4] = {s[n]->getColor().x,s[n]->getColor().y,s[n]->getColor().z, 1.0};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
		glMaterialfv(GL_FRONT, GL_AMBIENT, color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, currentBodyMat->specular);
		glMaterialf(GL_FRONT, GL_SHININESS, currentBodyMat->shininess);
        //glColor3f(s[n]->getColor().x,s[n]->getColor().y,s[n]->getColor().z);
        glVertex3f(s[n]->getPosition().x, s[n]->getPosition().y, s[n]->getPosition().z);

    }
    glEnd();
	break;
	case 1://wireframe
		for (int n = 0; n < N; n++) {
				//printf("%f\n",s[n]->getPosition().x - s[m]->getPosition().x);
					GLfloat color[4] = {s[n]->getColor().x,s[n]->getColor().y,s[n]->getColor().z, 1.0};
					glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
					glMaterialfv(GL_FRONT, GL_AMBIENT, color);
					glMaterialfv(GL_FRONT, GL_SPECULAR, currentBodyMat->specular);
					glMaterialf(GL_FRONT, GL_SHININESS, currentBodyMat->shininess);
					if(n+1 < N){
					glBegin(GL_LINES);
					glVertex3f(s[n]->getPosition().x, s[n]->getPosition().y, s[n]->getPosition().z);
					glVertex3f(s[n+1]->getPosition().x, s[n+1]->getPosition().y, s[n+1]->getPosition().z);  
					glEnd();
					}
					if(n+SIZE < N){
					glBegin(GL_LINES);
					glVertex3f(s[n]->getPosition().x, s[n]->getPosition().y, s[n]->getPosition().z);
					glVertex3f(s[n+SIZE]->getPosition().x, s[n+SIZE]->getPosition().y, s[n+SIZE]->getPosition().z);  
					glEnd();
					}
		}
		break;
	case 2://Cube
		break;
	case 3://cylinder
		for (int n = 0; n < N; n++) {
				//printf("%f\n",s[n]->getPosition().x - s[m]->getPosition().x);
					GLfloat color[4] = {s[n]->getColor().x,s[n]->getColor().y,s[n]->getColor().z, 1.0};
					glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
					glMaterialfv(GL_FRONT, GL_AMBIENT, color);
					glMaterialfv(GL_FRONT, GL_SPECULAR, currentBodyMat->specular);
					glMaterialf(GL_FRONT, GL_SHININESS, currentBodyMat->shininess);
					GLUquadric* quad;
					quad  = gluNewQuadric();
					glPushMatrix();
					glTranslatef(s[n]->getPosition().x,-1.9,s[n]->getPosition().z);
					glRotatef(-90,1,0,0);
					gluCylinder(quad,0.1,0.1,s[n]->getPosition().y + 2,10,10);
					glPopMatrix();
		}
		break;
	case 4://sphere
		for (int n = 0; n < N; n++) {
				//printf("%f\n",s[n]->getPosition().x - s[m]->getPosition().x);
					GLfloat color[4] = {s[n]->getColor().x,s[n]->getColor().y,s[n]->getColor().z, 1.0};
					glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
					glMaterialfv(GL_FRONT, GL_AMBIENT, color);
					glMaterialfv(GL_FRONT, GL_SPECULAR, currentBodyMat->specular);
					glMaterialf(GL_FRONT, GL_SHININESS, currentBodyMat->shininess);
					GLUquadric* quad;
					quad  = gluNewQuadric();
					glPushMatrix();
					glTranslatef(s[n]->getPosition().x,s[n]->getPosition().y,s[n]->getPosition().z);
					gluSphere(quad,0.08,10,10);
					glPopMatrix();
		}
		break;
	}
    //printf("%f \t",s[1]->getPosition().y);
	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	 //int dis = w < h ? w : h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    GLfloat aspect = w/h;
    glLoadIdentity();
    if (w <= h) {
        // width is smaller, so stretch out the height
        glOrtho(-3, 3, -3/aspect, 3/aspect, -10.0, 10.0);
    } else {
        // height is smaller, so stretch out the width
        glOrtho(-3*aspect, 3*aspect, -3, 3, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mymouse(int btn,int state,int x,int y)
{
    
}
void keyPressed (unsigned char key, int x, int y) { 
	 switch (key) {
		 case 'P': case 'p':
			printf("P pressed\n");
			paused = !paused;
			music.OnKeyCharacter('p', 0, false, false);
			break;
		case 'n': case 'N':
			music.OnKeyCharacter('n', 0, false, false);
			normal = !normal;
			break;
		case '1':
			music.OnKeyCharacter('1', 0, false, false);
			break;
		case '2':
			music.OnKeyCharacter('2', 0, false, false);
			break;
		case 'd': case 'D':
			displayMode = !displayMode;
			refreshTime = 0;
			break;
		default:
			break;
	 }
} 
void keyboard(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT:
            posx -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            posx += 0.1;
            break;
        case GLUT_KEY_UP:
            posy += 0.1;
            break;
        case GLUT_KEY_DOWN:
            posy -= 0.1;
            break;
        default:
            break;
    }
}

void init() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
	//light properties
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
  glEnable(GL_NORMALIZE);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //enable white distant light
  currentLighting = &whiteLighting;
		
  glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	//set current material properties
	currentBodyMat = &original_body_mat;

}
void mymenu(int id)
{

	if(id==1){	
		paused = !paused;
			music.OnKeyCharacter('p', 0, false, false);
	}
	if(id==2){
		ro_all = !ro_all;
	}
	if(id==3){
		music.OnKeyCharacter('n', 0, false, false);
		normal = !normal;
	}
	if(id==4){
		displayMode = true;
			refreshTime = 0;
	}
	if(id==5){
		displayMode = false;
			refreshTime = 0;
	}
	if(id==6)particle = 1;
	if(id==7)particle = 2;
	if(id==8)particle = 3;
	if(id==9)particle = 4;
	if(id==10)particle = 0;
}
void createMenu()
{
	int menu,submenu1,submenu2;
	submenu1 = glutCreateMenu(mymenu);
	glutAddMenuEntry("flow",4);
	glutAddMenuEntry("wave",5);
	
	submenu2 = glutCreateMenu(mymenu);
	glutAddMenuEntry("wireframe",6);
	//glutAddMenuEntry("cube",7);
    glutAddMenuEntry("cylinder",8);
    glutAddMenuEntry("sphere",9);
	glutAddMenuEntry("points",10);
  
	menu = glutCreateMenu(mymenu);
	glutAddMenuEntry("pause",1);
	glutAddMenuEntry("rotate",2);
	glutAddMenuEntry("normalize",3);
	glutAddSubMenu("display mode",submenu1);
	glutAddSubMenu("objects",submenu2);
  

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// The usual main function.
int main(int argc, char** argv) {
	
	
    PSinitialize();
    Euler();
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Visualizer");
	createMenu();//create menu
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mymouse);
    glutSpecialFunc(keyboard);
	glutKeyboardFunc(keyPressed);
    glutIdleFunc(idle);
    init();
    
    glutMainLoop();
	return 0;
}

