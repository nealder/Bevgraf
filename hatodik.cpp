#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <list>
GLint keyStates[256];
#define PI 3.141592653589793
GLint winWidth = 800;
GLint winHeight = 600;

typedef struct point3dh { GLdouble x, y, z, h; } POINT3DH;
typedef struct point2d { GLdouble x, y; } POINT2D;
typedef struct point3d { GLdouble x, y, z; } POINT3D;
GLdouble eltol1[3]={0,0,0};
GLdouble eltol2[3]={-2,0,0};
GLdouble eltol3[3]={2,0,0};
GLdouble eltol4[3]={0,-2,0};
GLdouble eltol5[3]={0,2,0};
GLdouble eltol6[3]={0,0,-2};
GLdouble eltol7[3]={0,0,2};
GLdouble temp1[4][4];
GLdouble temp2[4][4];
GLdouble VC[4][4];
GLdouble WtV[4][4];
GLdouble s = 3;
GLdouble delta = 5 * 0.0174532925;
GLdouble K[4][4];
POINT3DH kocka1[8];
POINT3DH kocka2[8];
POINT3DH kocka3[8];
POINT3DH kocka4[8];
POINT3DH kocka5[8];
POINT3DH kocka6[8];
POINT3DH kocka7[8];
POINT3DH displayable_kocka1[8];
POINT3DH displayable_kocka2[8];
POINT3DH displayable_kocka3[8];
POINT3DH displayable_kocka4[8];
POINT3DH displayable_kocka5[8];
POINT3DH displayable_kocka6[8];
POINT3DH displayable_kocka7[8];

void kockaeltol(POINT3DH kocka[8], GLdouble eltol[3]){
	for(GLint i=0; i<8 ;i++){
		kocka[i].x+=eltol[0];
		kocka[i].y+=eltol[1];
		kocka[i].z+=eltol[2];
	}
}

POINT3D initPoint3d(GLdouble x, GLdouble y, GLdouble z){
	POINT3D P;
	P.x = x;
	P.y = y;
	P.z = z;
	return P;
}

POINT3DH initPoint3dh(GLdouble x , GLdouble y , GLdouble z){
	POINT3DH P;
	P.x = x;
	P.y = y;
	P.z = z;
	P.h = 1;
	return P;
}

POINT2D initPoint2d(GLdouble x , GLdouble y){
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

POINT2D winMin = initPoint2d(-4, -4);
POINT2D winMax = initPoint2d(4, 4);
POINT2D viewMin = initPoint2d(200,100);
POINT2D viewMax = initPoint2d(600, 500);

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

POINT3D vektmul(POINT3D A, POINT3D B){
	POINT3D P;
	P.x = A.y*B.z - A.z*B.y;
	P.y = A.z*B.x - A.x*B.z;
	P.z = A.x*B.y - A.y*B.x;
	return P;
}

GLdouble hossz(POINT3D A){
	return sqrt((A.x)*(A.x) + (A.y)*(A.y) + (A.z)*(A.z));
}

	POINT3D C = initPoint3d (300,500,200);
	POINT3D P = initPoint3d (0,0,0);
	POINT3D up = initPoint3d (0, 1.0, 0);

	POINT3D W = initPoint3d ((C.x-P.x) / hossz(vektmul(C, P)),
							(C.y-P.y) / hossz(vektmul(C, P)),
							(C.z-P.z) / hossz(vektmul(C, P)));

	POINT3D U = initPoint3d ((up.y*W.z-up.z*W.y) / hossz(vektmul(up,W)),
							(up.z*W.x-up.x*W.z) / hossz(vektmul(up,W)), 
							(up.x*W.y-up.y*W.x) / hossz(vektmul(up,W)));

	POINT3D V = initPoint3d ((W.y*U.z-W.z*U.y) / hossz(vektmul(W,U)), 
							(W.z*U.x-W.x*U.z) / hossz(vektmul(W,U)), 
							(W.x*U.y-W.y*U.x) / hossz(vektmul(W,U)));

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations ( ) {
	

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

void createKMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			K[i][j]=0;
		}
	}
	K[0][0]=U.x;
	K[0][1]=U.y;
	K[0][2]=U.z;
	K[0][3]=-(C.x*U.x + C.y*U.y + C.z*U.z);;
	K[1][0]=V.x;
	K[1][1]=V.y;
	K[1][2]=V.z;
	K[1][3]=-(C.x*V.x + C.y*V.y + C.z*V.z);
	K[2][0]=W.x;
	K[2][1]=W.y;
	K[2][2]=W.z;
	K[2][3]=-(C.x*W.x + C.y*W.y + C.z*W.z);
	K[3][3]=1;
}

void createWtVMatrix(POINT2D viewMin, POINT2D viewMax,POINT2D winMin,POINT2D winMax,GLdouble WtV[][4]){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			WtV[i][j]=0;
		}
	}
	WtV[0][0]=(viewMax.x-viewMin.x)/(winMax.x-winMin.x);
	WtV[0][3]=viewMin.x-winMin.x*((viewMax.x-viewMin.x)/(winMax.x-winMin.x));
	WtV[1][1]=(viewMax.y-viewMin.y)/(winMax.y-winMin.y);
	WtV[1][3]=viewMin.y-winMin.y*((viewMax.y-viewMin.y)/(winMax.y-winMin.y));
	WtV[2][2]=1;
	WtV[3][3]=1;
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

void Display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	keyOperations();

	mul_matrices(VC,K,temp1);
	mul_matrices(WtV,temp1,temp2);

	for(GLint i=0 ; i<8 ; i++){
		displayable_kocka1[i]=transzform(temp2,kocka1[i]);
		displayable_kocka2[i]=transzform(temp2,kocka2[i]);
		displayable_kocka3[i]=transzform(temp2,kocka3[i]);
		displayable_kocka4[i]=transzform(temp2,kocka4[i]);
		displayable_kocka5[i]=transzform(temp2,kocka5[i]);
		displayable_kocka6[i]=transzform(temp2,kocka6[i]);
		displayable_kocka7[i]=transzform(temp2,kocka7[i]);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

int main (int argc, char** argv) {

	createVCMatrix();
	createWtVMatrix(viewMin,viewMax,winMin,winMax, WtV);
	createKMatrix();

	kocka1[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka1[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka1[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka1[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka1[4] = initPoint3dh(0.5,0.5,0.5);
	kocka1[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka1[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka1[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka2[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka2[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka2[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka2[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka2[4] = initPoint3dh(0.5,0.5,0.5);
	kocka2[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka2[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka2[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka3[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka3[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka3[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka3[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka3[4] = initPoint3dh(0.5,0.5,0.5);
	kocka3[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka3[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka3[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka4[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka4[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka4[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka4[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka4[4] = initPoint3dh(0.5,0.5,0.5);
	kocka4[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka4[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka4[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka5[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka5[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka5[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka5[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka5[4] = initPoint3dh(0.5,0.5,0.5);
	kocka5[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka5[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka5[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka6[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka6[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka6[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka6[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka6[4] = initPoint3dh(0.5,0.5,0.5);
	kocka6[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka6[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka6[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka7[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka7[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka7[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka7[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka7[4] = initPoint3dh(0.5,0.5,0.5);
	kocka7[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka7[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka7[7] = initPoint3dh(0.5,-0.5,0.5);

	kockaeltol(kocka1,eltol1);
	kockaeltol(kocka2,eltol2);
	kockaeltol(kocka3,eltol3);
	kockaeltol(kocka4,eltol4);
	kockaeltol(kocka5,eltol5);
	kockaeltol(kocka6,eltol6);
	kockaeltol(kocka7,eltol7);

	std::cout << "| " << kocka2[0].x << std::endl;

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (500, 100);
	glutInitWindowSize (800, 600);
	glutCreateWindow ("otodik");
	init ( );
	glutDisplayFunc (Display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop ( );
	return 0;
}