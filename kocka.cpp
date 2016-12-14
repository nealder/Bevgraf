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
GLint s = 3;
POINT3DH Q[8];

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

POINT3DH transzform(double matrix[][4], POINT3DH Q){
	POINT3DH P;
		P.x=matrix[0][0]*Q.x + matrix[0][1]*Q.y + matrix[0][2]*Q.z + matrix[0][3]*Q.h;
		P.y=matrix[1][0]*Q.x + matrix[1][1]*Q.y + matrix[1][2]*Q.z + matrix[1][3]*Q.h;
		//P.z=0;
		P.h=matrix[3][0]*Q.x + matrix[3][1]*Q.y + matrix[3][2]*Q.z + matrix[3][3]*Q.h;
	return P;
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

	glutSwapBuffers();
}

int main (int argc, char** argv) {

	createVMMatrix();
	createVCMatrix();
	createTMatrix();
	createNMatrix();
	createFXMatrix();
	createFYMatrix();

	Q[0] = initPoint3dh(0.5,0.5,-0.5);
	Q[1] = initPoint3dh(-0.5,0.5,-0.5);
	Q[2] = initPoint3dh(-0.5,-0.5,-0.5);
	Q[3] = initPoint3dh(0.5,-0.5,-0.5);
	Q[4] = initPoint3dh(0.5,0.5,0.5);
	Q[5] = initPoint3dh(-0.5,0.5,0.5);
	Q[6] = initPoint3dh(-0.5,-0.5,0.5);
	Q[7] = initPoint3dh(0.5,-0.5,0.5);

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
	glutMainLoop ( );
	return 0;
}