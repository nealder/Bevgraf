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
	glLineStipple(1, 0xFF00);
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
    		Q[i].x = 0;
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

	

	for(GLint i = 0 ; i < 8 ; i++){
		Q[i] = transzform(kocka,Q[i]);
		W[i] = transzform(kocka,W[i]);
		E[i] = transzform(kocka,E[i]);
		A[i] = transzform(kocka,A[i]);
		S[i] = transzform(kocka,S[i]);
		D[i] = transzform(kocka,D[i]);
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(Q[0].x/Q[0].h,Q[0].y/Q[0].h);
		glVertex2d(Q[1].x/Q[1].h,Q[1].y/Q[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[0].x/Q[0].h,Q[0].y/Q[0].h);
		glVertex2d(Q[4].x/Q[4].h,Q[4].y/Q[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[0].x/Q[0].h,Q[0].y/Q[0].h);
		glVertex2d(Q[3].x/Q[3].h,Q[3].y/Q[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[1].x/Q[1].h,Q[1].y/Q[1].h);
		glVertex2d(Q[2].x/Q[2].h,Q[2].y/Q[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(Q[1].x/Q[1].h,Q[1].y/Q[1].h);
		glVertex2d(Q[5].x/Q[5].h,Q[5].y/Q[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[2].x/Q[2].h,Q[2].y/Q[2].h);
		glVertex2d(Q[3].x/Q[3].h,Q[3].y/Q[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[2].x/Q[2].h,Q[2].y/Q[2].h);
		glVertex2d(Q[6].x/Q[6].h,Q[6].y/Q[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[3].x/Q[3].h,Q[3].y/Q[3].h);
		glVertex2d(Q[7].x/Q[7].h,Q[7].y/Q[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[6].x/Q[6].h,Q[6].y/Q[6].h);
		glVertex2d(Q[7].x/Q[7].h,Q[7].y/Q[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[4].x/Q[4].h,Q[4].y/Q[4].h);
		glVertex2d(Q[7].x/Q[7].h,Q[7].y/Q[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[4].x/Q[4].h,Q[4].y/Q[4].h);
		glVertex2d(Q[5].x/Q[5].h,Q[5].y/Q[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(Q[6].x/Q[6].h,Q[6].y/Q[6].h);
		glVertex2d(Q[5].x/Q[5].h,Q[5].y/Q[5].h);
		glEnd();

		//MÁSODIK 

		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(W[0].x/W[0].h,W[0].y/W[0].h);
		glVertex2d(W[1].x/W[1].h,W[1].y/W[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[0].x/W[0].h,W[0].y/W[0].h);
		glVertex2d(W[4].x/W[4].h,W[4].y/W[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[0].x/W[0].h,W[0].y/W[0].h);
		glVertex2d(W[3].x/W[3].h,W[3].y/W[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[1].x/W[1].h,W[1].y/W[1].h);
		glVertex2d(W[2].x/W[2].h,W[2].y/W[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(W[1].x/W[1].h,W[1].y/W[1].h);
		glVertex2d(W[5].x/W[5].h,W[5].y/W[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[2].x/W[2].h,W[2].y/W[2].h);
		glVertex2d(W[3].x/W[3].h,W[3].y/W[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[2].x/W[2].h,W[2].y/W[2].h);
		glVertex2d(W[6].x/W[6].h,W[6].y/W[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[3].x/W[3].h,W[3].y/W[3].h);
		glVertex2d(W[7].x/W[7].h,W[7].y/W[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[6].x/W[6].h,W[6].y/W[6].h);
		glVertex2d(W[7].x/W[7].h,W[7].y/W[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[4].x/W[4].h,W[4].y/W[4].h);
		glVertex2d(W[7].x/W[7].h,W[7].y/W[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[4].x/W[4].h,W[4].y/W[4].h);
		glVertex2d(W[5].x/W[5].h,W[5].y/W[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(W[6].x/W[6].h,W[6].y/W[6].h);
		glVertex2d(W[5].x/W[5].h,W[5].y/W[5].h);
		glEnd();

		//HARMADIK

		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(E[0].x/E[0].h,E[0].y/E[0].h);
		glVertex2d(E[1].x/E[1].h,E[1].y/E[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[0].x/E[0].h,E[0].y/E[0].h);
		glVertex2d(E[4].x/E[4].h,E[4].y/E[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[0].x/E[0].h,E[0].y/E[0].h);
		glVertex2d(E[3].x/E[3].h,E[3].y/E[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[1].x/E[1].h,E[1].y/E[1].h);
		glVertex2d(E[2].x/E[2].h,E[2].y/E[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(E[1].x/E[1].h,E[1].y/E[1].h);
		glVertex2d(E[5].x/E[5].h,E[5].y/E[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[2].x/E[2].h,E[2].y/E[2].h);
		glVertex2d(E[3].x/E[3].h,E[3].y/E[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[2].x/E[2].h,E[2].y/E[2].h);
		glVertex2d(E[6].x/E[6].h,E[6].y/E[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[3].x/E[3].h,E[3].y/E[3].h);
		glVertex2d(E[7].x/E[7].h,E[7].y/E[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[6].x/E[6].h,E[6].y/E[6].h);
		glVertex2d(E[7].x/E[7].h,E[7].y/E[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[4].x/E[4].h,E[4].y/E[4].h);
		glVertex2d(E[7].x/E[7].h,E[7].y/E[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[4].x/E[4].h,E[4].y/E[4].h);
		glVertex2d(E[5].x/E[5].h,E[5].y/E[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(E[6].x/E[6].h,E[6].y/E[6].h);
		glVertex2d(E[5].x/E[5].h,E[5].y/E[5].h);
		glEnd();

		//MÁSIK_ELSŐ
/*
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(A[0].x/A[0].h,A[0].y/A[0].h);
		glVertex2d(A[1].x/A[1].h,A[1].y/A[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[0].x/A[0].h,A[0].y/A[0].h);
		glVertex2d(A[4].x/A[4].h,A[4].y/A[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[0].x/A[0].h,A[0].y/A[0].h);
		glVertex2d(A[3].x/A[3].h,A[3].y/A[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[1].x/A[1].h,A[1].y/A[1].h);
		glVertex2d(A[2].x/A[2].h,A[2].y/A[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(A[1].x/A[1].h,A[1].y/A[1].h);
		glVertex2d(A[5].x/A[5].h,A[5].y/A[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[2].x/A[2].h,A[2].y/A[2].h);
		glVertex2d(A[3].x/A[3].h,A[3].y/A[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[2].x/A[2].h,A[2].y/A[2].h);
		glVertex2d(A[6].x/A[6].h,A[6].y/A[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[3].x/A[3].h,A[3].y/A[3].h);
		glVertex2d(A[7].x/A[7].h,A[7].y/A[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[6].x/A[6].h,A[6].y/A[6].h);
		glVertex2d(A[7].x/A[7].h,A[7].y/A[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[4].x/A[4].h,A[4].y/A[4].h);
		glVertex2d(A[7].x/A[7].h,A[7].y/A[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[4].x/A[4].h,A[4].y/A[4].h);
		glVertex2d(A[5].x/A[5].h,A[5].y/A[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(A[6].x/A[6].h,A[6].y/A[6].h);
		glVertex2d(A[5].x/A[5].h,A[5].y/A[5].h);
		glEnd();

		//MÁSIK_MÁSODIK

		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(S[0].x/S[0].h,S[0].y/S[0].h);
		glVertex2d(S[1].x/S[1].h,S[1].y/S[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[0].x/S[0].h,S[0].y/S[0].h);
		glVertex2d(S[4].x/S[4].h,S[4].y/S[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[0].x/S[0].h,S[0].y/S[0].h);
		glVertex2d(S[3].x/S[3].h,S[3].y/S[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[1].x/S[1].h,S[1].y/S[1].h);
		glVertex2d(S[2].x/S[2].h,S[2].y/S[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(S[1].x/S[1].h,S[1].y/S[1].h);
		glVertex2d(S[5].x/S[5].h,S[5].y/S[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[2].x/S[2].h,S[2].y/S[2].h);
		glVertex2d(S[3].x/S[3].h,S[3].y/S[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[2].x/S[2].h,S[2].y/S[2].h);
		glVertex2d(S[6].x/S[6].h,S[6].y/S[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[3].x/S[3].h,S[3].y/S[3].h);
		glVertex2d(S[7].x/S[7].h,S[7].y/S[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[6].x/S[6].h,S[6].y/S[6].h);
		glVertex2d(S[7].x/S[7].h,S[7].y/S[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[4].x/S[4].h,S[4].y/S[4].h);
		glVertex2d(S[7].x/S[7].h,S[7].y/S[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[4].x/S[4].h,S[4].y/S[4].h);
		glVertex2d(S[5].x/S[5].h,S[5].y/S[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(S[6].x/S[6].h,S[6].y/S[6].h);
		glVertex2d(S[5].x/S[5].h,S[5].y/S[5].h);
		glEnd();

		//második_harmadik

		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(D[0].x/D[0].h,D[0].y/D[0].h);
		glVertex2d(D[1].x/D[1].h,D[1].y/D[1].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[0].x/D[0].h,D[0].y/D[0].h);
		glVertex2d(D[4].x/D[4].h,D[4].y/D[4].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[0].x/D[0].h,D[0].y/D[0].h);
		glVertex2d(D[3].x/D[3].h,D[3].y/D[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[1].x/D[1].h,D[1].y/D[1].h);
		glVertex2d(D[2].x/D[2].h,D[2].y/D[2].h);
		glEnd();
	
		glBegin(GL_LINES);
		glVertex2d(D[1].x/D[1].h,D[1].y/D[1].h);
		glVertex2d(D[5].x/D[5].h,D[5].y/D[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[2].x/D[2].h,D[2].y/D[2].h);
		glVertex2d(D[3].x/D[3].h,D[3].y/D[3].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[2].x/D[2].h,D[2].y/D[2].h);
		glVertex2d(D[6].x/D[6].h,D[6].y/D[6].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[3].x/D[3].h,D[3].y/D[3].h);
		glVertex2d(D[7].x/D[7].h,D[7].y/D[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[6].x/D[6].h,D[6].y/D[6].h);
		glVertex2d(D[7].x/D[7].h,D[7].y/D[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[4].x/D[4].h,D[4].y/D[4].h);
		glVertex2d(D[7].x/D[7].h,D[7].y/D[7].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[4].x/D[4].h,D[4].y/D[4].h);
		glVertex2d(D[5].x/D[5].h,D[5].y/D[5].h);
		glEnd();

		glBegin(GL_LINES);
		glVertex2d(D[6].x/D[6].h,D[6].y/D[6].h);
		glVertex2d(D[5].x/D[5].h,D[5].y/D[5].h);
		glEnd();
*/
	glutSwapBuffers();
}

void update (int n){
	
	glutTimerFunc( 5, update, 0 );
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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (500, 100);
	glutInitWindowSize (800, 600);
	glutCreateWindow ("otodik");
	init ( );
	glutDisplayFunc (Display);
	glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc( 5, update, 0 );
	glutMainLoop ( );
	return 0;
}