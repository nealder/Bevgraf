#include <GL/glut.h>
#include <math.h>
#include <iostream>
GLint keyStates[256];
GLfloat delta = 0.5;
#define PI 3.141592653589793
GLint winWidth = 800;
GLint winHeight = 600;
GLdouble szog = 24 * 0.0174532925;

typedef struct point3dh { GLdouble x, y, z, h; } POINT3DH;
GLdouble eltol[4][4];
GLdouble forgaty[4][4];
GLdouble forgatx[4][4];
GLdouble nagyit[4][4];
GLdouble kocka[4][4];
GLdouble temp[4][4];
GLdouble temp2[4][4];
GLdouble VC[4][4];
GLdouble VM[4][4];
GLdouble forgat[4][4];
GLint s = 3;
POINT3DH Q[8];
POINT3DH W[8];
POINT3DH E[8];
POINT3DH A[8];
POINT3DH S[8];
POINT3DH D[8];
POINT3DH Qd[8];
POINT3DH Wd[8];
POINT3DH Ed[8];
POINT3DH Ad[8];
POINT3DH Sd[8];
POINT3DH Dd[8];

POINT3DH initPoint3dh(GLdouble x , GLdouble y , GLdouble z){
	POINT3DH P;
	P.x = x;
	P.y = y;
	P.z = z;
	P.h = 1;
	return P;
}

void init( ) {
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
	glShadeModel( GL_FLAT );
	glPointSize( 10.0 );
	glLineWidth( 5.0 );
}

POINT3DH transzform(double matrix[][4], POINT3DH Q){
	POINT3DH P;
	P.x=matrix[0][0]*Q.x + matrix[0][1]*Q.y + matrix[0][2]*Q.z + matrix[0][3]*Q.h;
	P.y=matrix[1][0]*Q.x + matrix[1][1]*Q.y + matrix[1][2]*Q.z + matrix[1][3]*Q.h;
	P.z=matrix[2][0]*Q.x + matrix[2][1]*Q.y + matrix[2][2]*Q.z + matrix[2][3]*Q.h;
	P.h=matrix[3][0]*Q.x + matrix[3][1]*Q.y + matrix[3][2]*Q.z + matrix[3][3]*Q.h;
	return P;
}

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations ( ) {
	if(keyStates['q']){
		for(GLint i = 0; i < 8; i++){
			//Q[i] = transzform(forgat,Q[i]);
		}
	}

	glutPostRedisplay( );
}

void mul_matrices( double A[ ][ 4 ], double B[ ][ 4 ], double C[ ][ 4 ] ){
	int i, j, k;
	float sum;
	for( i = 0; i < 4; i++ ){
		for( j = 0; j < 4; j++ ){
			sum = 0;
			for( k = 0; k < 4; k++ ){
				sum = sum + A[ i ][ k ] * B[ k ][ j ];
			}
			C[ i ][ j ] = sum;
		}
	}
}

void createFMatrix(){
	for(int i = 0; i<3 ; i++){
		for(int j = 0; j<3 ; j++){
			forgat[i][j]=0;
		}
	}
	forgat[0][0]= cos(szog);
	forgat[0][2]= sin(szog);
	forgat[1][1]= 1;
	forgat[2][0]= -sin(szog);
	forgat[2][2]= cos(szog);
	forgat[3][3]= 1;
}

void createFYMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			forgaty[i][j]=0;
		}
	}
	forgaty[0][0]= cos(szog);
	forgaty[0][2]= sin(szog);
	forgaty[1][1]= 1;
	forgaty[2][0]= -sin(szog);
	forgaty[2][2]= cos(szog);
	forgaty[3][3]= 1;
}

void createFXMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			forgatx[i][j]=0;
		}
	}
	forgatx[0][0]= 1;
	forgatx[1][1]= cos(szog);
	forgatx[1][2]= -sin(szog);
	forgatx[2][1]= sin(szog);
	forgatx[2][2]= cos(szog);
	forgatx[3][3]= 1;
}

void createNMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			nagyit[i][j]=0;
		}
	}
	nagyit[0][0]=150;
	nagyit[1][1]=150;
	nagyit[2][2]=150;
	nagyit[3][3]=1;
}

void createTMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			eltol[i][j]=0;
		}
	}
	eltol[0][0]=1;
	eltol[1][1]=1;
	eltol[2][2]=1;
	eltol[3][3]=1;
	eltol[0][3]=400;
	eltol[1][3]=300;
}

void createVCMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			VC[i][j]=0;
		}
	}
	VC[0][0]=1;
	VC[1][1]=1;
	VC[3][2]=-1/s;
	VC[3][3]=1;
}

void createVMMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			VM[i][j]=0;
		}
	}
	VM[0][0]=1;
	VM[1][1]=1;
	VM[3][3]=1;
}



void Display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	keyOperations();

	for(GLint i = 0 ; i < 8 ; i++){
		Qd[i] = transzform(kocka,Q[i]);
		Wd[i] = transzform(kocka,W[i]);
		Ed[i] = transzform(kocka,E[i]);
		//Ad[i] = transzform(kocka,A[i]);
		//Sd[i] = transzform(kocka,S[i]);
		//Dd[i] = transzform(kocka,D[i]);
	}
	
	glBegin(GL_LINES);
	glVertex2d(Qd[0].x/Qd[0].h,Qd[0].y/Qd[0].h);
	glVertex2d(Qd[1].x/Qd[1].h,Qd[1].y/Qd[1].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[0].x/Qd[0].h,Qd[0].y/Qd[0].h);
	glVertex2d(Qd[4].x/Qd[4].h,Qd[4].y/Qd[4].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[0].x/Qd[0].h,Qd[0].y/Qd[0].h);
	glVertex2d(Qd[3].x/Qd[3].h,Qd[3].y/Qd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[1].x/Qd[1].h,Qd[1].y/Qd[1].h);
	glVertex2d(Qd[2].x/Qd[2].h,Qd[2].y/Qd[2].h);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2d(Qd[1].x/Qd[1].h,Qd[1].y/Qd[1].h);
	glVertex2d(Qd[5].x/Qd[5].h,Qd[5].y/Qd[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[2].x/Qd[2].h,Qd[2].y/Qd[2].h);
	glVertex2d(Qd[3].x/Qd[3].h,Qd[3].y/Qd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[2].x/Qd[2].h,Qd[2].y/Qd[2].h);
	glVertex2d(Qd[6].x/Qd[6].h,Qd[6].y/Qd[6].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[3].x/Qd[3].h,Qd[3].y/Qd[3].h);
	glVertex2d(Qd[7].x/Qd[7].h,Qd[7].y/Qd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[6].x/Qd[6].h,Qd[6].y/Qd[6].h);
	glVertex2d(Qd[7].x/Qd[7].h,Qd[7].y/Qd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[4].x/Qd[4].h,Qd[4].y/Qd[4].h);
	glVertex2d(Qd[7].x/Qd[7].h,Qd[7].y/Qd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[4].x/Qd[4].h,Qd[4].y/Qd[4].h);
	glVertex2d(Qd[5].x/Qd[5].h,Qd[5].y/Qd[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Qd[6].x/Qd[6].h,Qd[6].y/Qd[6].h);
	glVertex2d(Qd[5].x/Qd[5].h,Qd[5].y/Qd[5].h);
	glEnd();

		//MÁSODIK 

	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(Wd[0].x/Wd[0].h,Wd[0].y/Wd[0].h);
	glVertex2d(Wd[1].x/Wd[1].h,Wd[1].y/Wd[1].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[0].x/Wd[0].h,Wd[0].y/Wd[0].h);
	glVertex2d(Wd[4].x/Wd[4].h,Wd[4].y/Wd[4].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[0].x/Wd[0].h,Wd[0].y/Wd[0].h);
	glVertex2d(Wd[3].x/Wd[3].h,Wd[3].y/Wd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[1].x/Wd[1].h,Wd[1].y/Wd[1].h);
	glVertex2d(Wd[2].x/Wd[2].h,Wd[2].y/Wd[2].h);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2d(Wd[1].x/Wd[1].h,Wd[1].y/Wd[1].h);
	glVertex2d(Wd[5].x/Wd[5].h,Wd[5].y/Wd[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[2].x/Wd[2].h,Wd[2].y/Wd[2].h);
	glVertex2d(Wd[3].x/Wd[3].h,Wd[3].y/Wd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[2].x/Wd[2].h,Wd[2].y/Wd[2].h);
	glVertex2d(Wd[6].x/Wd[6].h,Wd[6].y/Wd[6].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[3].x/Wd[3].h,Wd[3].y/Wd[3].h);
	glVertex2d(Wd[7].x/Wd[7].h,Wd[7].y/Wd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[6].x/Wd[6].h,Wd[6].y/Wd[6].h);
	glVertex2d(Wd[7].x/Wd[7].h,Wd[7].y/Wd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[4].x/Wd[4].h,Wd[4].y/Wd[4].h);
	glVertex2d(Wd[7].x/Wd[7].h,Wd[7].y/Wd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[4].x/Wd[4].h,Wd[4].y/Wd[4].h);
	glVertex2d(Wd[5].x/Wd[5].h,Wd[5].y/Wd[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Wd[6].x/Wd[6].h,Wd[6].y/Wd[6].h);
	glVertex2d(Wd[5].x/Wd[5].h,Wd[5].y/Wd[5].h);
	glEnd();

		//HARMADIK

	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex2d(Ed[0].x/Ed[0].h,Ed[0].y/Ed[0].h);
	glVertex2d(Ed[1].x/Ed[1].h,Ed[1].y/Ed[1].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[0].x/Ed[0].h,Ed[0].y/Ed[0].h);
	glVertex2d(Ed[4].x/Ed[4].h,Ed[4].y/Ed[4].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[0].x/Ed[0].h,Ed[0].y/Ed[0].h);
	glVertex2d(Ed[3].x/Ed[3].h,Ed[3].y/Ed[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[1].x/Ed[1].h,Ed[1].y/Ed[1].h);
	glVertex2d(Ed[2].x/Ed[2].h,Ed[2].y/Ed[2].h);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2d(Ed[1].x/Ed[1].h,Ed[1].y/Ed[1].h);
	glVertex2d(Ed[5].x/Ed[5].h,Ed[5].y/Ed[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[2].x/Ed[2].h,Ed[2].y/Ed[2].h);
	glVertex2d(Ed[3].x/Ed[3].h,Ed[3].y/Ed[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[2].x/Ed[2].h,Ed[2].y/Ed[2].h);
	glVertex2d(Ed[6].x/Ed[6].h,Ed[6].y/Ed[6].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[3].x/Ed[3].h,Ed[3].y/Ed[3].h);
	glVertex2d(Ed[7].x/Ed[7].h,Ed[7].y/Ed[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[6].x/Ed[6].h,Ed[6].y/Ed[6].h);
	glVertex2d(Ed[7].x/Ed[7].h,Ed[7].y/Ed[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[4].x/Ed[4].h,Ed[4].y/Ed[4].h);
	glVertex2d(Ed[7].x/Ed[7].h,Ed[7].y/Ed[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[4].x/Ed[4].h,Ed[4].y/Ed[4].h);
	glVertex2d(Ed[5].x/Ed[5].h,Ed[5].y/Ed[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ed[6].x/Ed[6].h,Ed[6].y/Ed[6].h);
	glVertex2d(Ed[5].x/Ed[5].h,Ed[5].y/Ed[5].h);
	glEnd();

		//MÁSIK_ELSŐ
/*
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(Add[0].x/Add[0].h,Add[0].y/Add[0].h);
		glVertex2d(Add[1].x/Add[1].h,Add[1].y/Add[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Add[0].x/Ad[0].h,Ad[0].y/Ad[0].h);
		glVertex2d(Add[4].x/Ad[4].h,Ad[4].y/Ad[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[0].x/Ad[0].h,Ad[0].y/Ad[0].h);
		glVertex2d(Ad[3].x/Ad[3].h,Ad[3].y/Ad[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[1].x/Ad[1].h,Ad[1].y/Ad[1].h);
		glVertex2d(Ad[2].x/Ad[2].h,Ad[2].y/Ad[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(Ad[1].x/Ad[1].h,Ad[1].y/Ad[1].h);
		glVertex2d(Ad[5].x/Ad[5].h,Ad[5].y/Ad[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[2].x/Ad[2].h,Ad[2].y/Ad[2].h);
		glVertex2d(Ad[3].x/Ad[3].h,Ad[3].y/Ad[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[2].x/Ad[2].h,Ad[2].y/Ad[2].h);
		glVertex2d(Ad[6].x/Ad[6].h,Ad[6].y/Ad[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[3].x/Ad[3].h,Ad[3].y/Ad[3].h);
		glVertex2d(Ad[7].x/Ad[7].h,Ad[7].y/Ad[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[6].x/Ad[6].h,Ad[6].y/Ad[6].h);
		glVertex2d(Ad[7].x/Ad[7].h,Ad[7].y/Ad[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[4].x/Ad[4].h,Ad[4].y/Ad[4].h);
		glVertex2d(Ad[7].x/Ad[7].h,Ad[7].y/Ad[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[4].x/Ad[4].h,Ad[4].y/Ad[4].h);
		glVertex2d(Ad[5].x/Ad[5].h,Ad[5].y/Ad[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Ad[6].x/Ad[6].h,Ad[6].y/Ad[6].h);
		glVertex2d(Ad[5].x/Ad[5].h,Ad[5].y/Ad[5].h);
		glEnd();

		//MÁSIK_MÁSODIK

		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINESd);
		glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
		glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
		glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
		glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
		glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
		glEnd();
	
		glBegin(GL_LINESd);
		glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
		glVertex2d(Sd[5].x/Sd[5].h,Sd[5].y/Sd[5].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
		glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
		glVertex2d(Sd[6].x/Sd[6].h,Sd[6].y/Sd[6].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
		glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[6].x/Sd[6].h,Sd[6].y/Sd[6].h);
		glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
		glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
		glVertex2d(Sd[5].x/Sd[5].h,Sd[5].y/Sd[5].h);
		glEnd();

		glBegin(GL_LINESd);
		glVertex2d(Sd[6].x/Sd[6].h,Sd[6].y/Sd[6].h);
		glVertex2d(Sd[5].x/Sd[5].h,Sd[5].y/Sd[5].h);
		glEnd();

		//második_harmadik

		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(Dd[0].x/Dd[0].h,Dd[0].y/Dd[0].h);
		glVertex2d(Dd[1].x/Dd[1].h,Dd[1].y/Dd[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[0].x/Dd[0].h,Dd[0].y/Dd[0].h);
		glVertex2d(Dd[4].x/Dd[4].h,Dd[4].y/Dd[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[0].x/Dd[0].h,Dd[0].y/Dd[0].h);
		glVertex2d(Dd[3].x/Dd[3].h,Dd[3].y/Dd[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[1].x/Dd[1].h,Dd[1].y/Dd[1].h);
		glVertex2d(Dd[2].x/Dd[2].h,Dd[2].y/Dd[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(Dd[1].x/Dd[1].h,Dd[1].y/Dd[1].h);
		glVertex2d(Dd[5].x/Dd[5].h,Dd[5].y/Dd[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[2].x/Dd[2].h,Dd[2].y/Dd[2].h);
		glVertex2d(Dd[3].x/Dd[3].h,Dd[3].y/Dd[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[2].x/Dd[2].h,Dd[2].y/Dd[2].h);
		glVertex2d(Dd[6].x/Dd[6].h,Dd[6].y/Dd[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[3].x/Dd[3].h,Dd[3].y/Dd[3].h);
		glVertex2d(Dd[7].x/Dd[7].h,Dd[7].y/Dd[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[6].x/Dd[6].h,Dd[6].y/Dd[6].h);
		glVertex2d(Dd[7].x/Dd[7].h,Dd[7].y/Dd[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[4].x/Dd[4].h,Dd[4].y/Dd[4].h);
		glVertex2d(Dd[7].x/Dd[7].h,Dd[7].y/Dd[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[4].x/Dd[4].h,Dd[4].y/Dd[4].h);
		glVertex2d(Dd[5].x/Dd[5].h,Dd[5].y/Dd[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Dd[6].x/Dd[6].h,Dd[6].y/Dd[6].h);
		glVertex2d(Dd[5].x/Dd[5].h,Dd[5].y/Dd[5].h);
		glEnd();
*/

	glutPostRedisplay();
	glutSwapBuffers();
}

void update (int n){
	
	glutTimerFunc( 1000, update, 0 );
}

int main (int argc, char** argv) {

	createVMMatrix();
	createVCMatrix();
	createTMatrix();
	createNMatrix();
	createFXMatrix();
	createFYMatrix();

	Q[0] = initPoint3dh(0.5,-0.1666,-0.5);
	Q[1] = initPoint3dh(-0.5,-0.1666,-0.5);
	Q[2] = initPoint3dh(-0.5,-0.5,-0.5);
	Q[3] = initPoint3dh(0.5,-0.5,-0.5);
	Q[4] = initPoint3dh(0.5,-0.1666,0.5);
	Q[5] = initPoint3dh(-0.5,-0.1666,0.5);
	Q[6] = initPoint3dh(-0.5,-0.5,0.5);
	Q[7] = initPoint3dh(0.5,-0.5,0.5);

	W[0] = initPoint3dh(0.5,0.1666,-0.5);
	W[1] = initPoint3dh(-0.5,0.1666,-0.5);
	W[2] = initPoint3dh(-0.5,-0.1666,-0.5);
	W[3] = initPoint3dh(0.5,-0.1666,-0.5);
	W[4] = initPoint3dh(0.5,0.1666,0.5);
	W[5] = initPoint3dh(-0.5,0.1666,0.5);
	W[6] = initPoint3dh(-0.5,-0.1666,0.5);
	W[7] = initPoint3dh(0.5,-0.1666,0.5);

	E[0] = initPoint3dh(0.5,0.5,-0.5);
	E[1] = initPoint3dh(-0.5,0.5,-0.5);
	E[2] = initPoint3dh(-0.5,0.1666,-0.5);
	E[3] = initPoint3dh(0.5,0.1666,-0.5);
	E[4] = initPoint3dh(0.5,0.5,0.5);
	E[5] = initPoint3dh(-0.5,0.5,0.5);
	E[6] = initPoint3dh(-0.5,0.1666,0.5);
	E[7] = initPoint3dh(0.5,0.1666,0.5);

	A[0] = initPoint3dh(0.5,0.0,-0.5);
	A[1] = initPoint3dh(-0.5,0.0,-0.5);
	A[2] = initPoint3dh(-0.5,-0.5,-0.5);
	A[3] = initPoint3dh(0.5,-0.5,-0.5);
	A[4] = initPoint3dh(0.5,0.5,0.5);
	A[5] = initPoint3dh(-0.5,0.5,0.5);
	A[6] = initPoint3dh(-0.5,-0.0,0.5);
	A[7] = initPoint3dh(0.5,-0.0,0.5);

	S[0] = initPoint3dh(0.5,0.0,-0.5);
	S[1] = initPoint3dh(-0.5,0.0,-0.5);
	S[2] = initPoint3dh(-0.5,-0.5,-0.5);
	S[3] = initPoint3dh(0.5,-0.5,-0.5);
	S[4] = initPoint3dh(0.5,0.5,0.5);
	S[5] = initPoint3dh(-0.5,0.5,0.5);
	S[6] = initPoint3dh(-0.5,-0.0,0.5);
	S[7] = initPoint3dh(0.5,-0.0,0.5);

	D[0] = initPoint3dh(0.5,0.0,-0.5);
	D[1] = initPoint3dh(-0.5,0.0,-0.5);
	D[2] = initPoint3dh(-0.5,-0.5,-0.5);
	D[3] = initPoint3dh(0.5,-0.5,-0.5);
	D[4] = initPoint3dh(0.5,0.5,0.5);
	D[5] = initPoint3dh(-0.5,0.5,0.5);
	D[6] = initPoint3dh(-0.5,-0.0,0.5);
	D[7] = initPoint3dh(0.5,-0.0,0.5);

	mul_matrices(forgaty,nagyit,kocka);
	mul_matrices(forgatx,kocka,temp);
	mul_matrices(eltol,temp,temp2);
	mul_matrices(VM,temp2,kocka);	

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (500, 100);
	glutInitWindowSize (800, 600);
	glutCreateWindow ("otodik");
	init ( );
	glutDisplayFunc (Display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc( 1000, update, 0 );
	glutMainLoop ( );
	return 0;
}