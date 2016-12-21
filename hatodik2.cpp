#include <GL/glut.h>
#include <math.h>
#include <iostream>
GLint keyStates[256];
#define PI 3.141592653589793
GLint winWidth = 800;
GLint winHeight = 600;

typedef struct point3dh { GLdouble x, y, z, h; } POINT3DH;
typedef struct point2d { GLdouble x, y; } POINT2D;
GLdouble eltol1[4][4];
GLdouble eltol2[4][4];
GLdouble forgaty1[4][4];
GLdouble forgaty2[4][4];
GLdouble forgaty3[4][4];
GLdouble forgatx[4][4];
GLdouble nagyit[4][4];
GLdouble kocka1t[4][4];
GLdouble kocka2t[4][4];
GLdouble kocka3t[4][4];
GLdouble kocka4t[4][4];
GLdouble kocka5t[4][4];
GLdouble kocka6t[4][4];
GLdouble kocka7t[4][4];
GLdouble temp1_1[4][4];
GLdouble temp1_2[4][4];
GLdouble temp2_1[4][4];
GLdouble temp2_2[4][4];
GLdouble temp3_1[4][4];
GLdouble temp3_2[4][4];
GLdouble temp4_1[4][4];
GLdouble temp4_2[4][4];
GLdouble temp5_1[4][4];
GLdouble temp5_2[4][4];
GLdouble temp6_1[4][4];
GLdouble temp6_2[4][4];
GLdouble temp7_1[4][4];
GLdouble temp7_2[4][4];
GLdouble VC[4][4];
GLdouble VM[4][4];
GLdouble WtV1[4][4];
GLdouble WtV2[4][4];
GLdouble s = 3;
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
POINT3DH Fd[8];
GLdouble szogx = 24 * 0.0174532925;
GLdouble szogy1 = 24 * 0.0174532925;
GLdouble szogy2 = 24 * 0.0174532925;
GLdouble szogy3 = 24 * 0.0174532925;
GLdouble delta = 5 * 0.0174532925; 
POINT3DH kocka1[8];
POINT3DH kocka2[8];
POINT3DH kocka3[8];
POINT3DH kocka4[8];
POINT3DH kocka5[8];
POINT3DH kocka6[8];
POINT3DH kocka7[8];

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
POINT2D viewMin1 = initPoint2d(200, 100);
POINT2D viewMax1 = initPoint2d(600, 500);

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
		szogy3+=delta;
	}
	if(keyStates['w']){
		szogy3-=delta;
	}
	if(keyStates['a']){
		szogy2+=delta;
	}
	if(keyStates['s']){
		szogy2-=delta;
	}
	if(keyStates['y']){
		szogy1+=delta;
	}
	if(keyStates['x']){
		szogy1-=delta;
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

void createFY1Matrix(GLdouble szog){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			forgaty1[i][j]=0;
		}
	}
	forgaty1[0][0]= cos(szog);
	forgaty1[0][2]= sin(szog);
	forgaty1[1][1]= 1;
	forgaty1[2][0]= -sin(szog);
	forgaty1[2][2]= cos(szog);
	forgaty1[3][3]= 1;
}

void createFY2Matrix(GLdouble szog){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			forgaty2[i][j]=0;
		}
	}
	forgaty2[0][0]= cos(szog);
	forgaty2[0][2]= sin(szog);
	forgaty2[1][1]= 1;
	forgaty2[2][0]= -sin(szog);
	forgaty2[2][2]= cos(szog);
	forgaty2[3][3]= 1;
}

void createFY3Matrix(GLdouble szog){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			forgaty3[i][j]=0;
		}
	}
	forgaty3[0][0]= cos(szog);
	forgaty3[0][2]= sin(szog);
	forgaty3[1][1]= 1;
	forgaty3[2][0]= -sin(szog);
	forgaty3[2][2]= cos(szog);
	forgaty3[3][3]= 1;
}

void createFXMatrix(GLdouble szog){
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
/*
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
}*/

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

	createFY1Matrix(szogy1);
	createFY2Matrix(szogy2);
	createFY3Matrix(szogy3);

	createWtVMatrix(viewMin1,viewMax1,winMin,winMax, WtV1);

	mul_matrices(VM,temp1_1,temp1_2);
	mul_matrices(WtV1,temp1_2,kocka1t);


	mul_matrices(VM,temp2_1,temp2_2);
	mul_matrices(WtV1,temp2_2,kocka2t);


	mul_matrices(VM,temp3_1,temp3_2);
	mul_matrices(WtV1,temp3_2,kocka3t);


	mul_matrices(VC,temp4_1,temp4_2);
	mul_matrices(WtV1,temp4_2,kocka4t);


	mul_matrices(VC,temp5_1,temp5_2);
	mul_matrices(WtV1,temp5_2,kocka5t);


	mul_matrices(VC,temp6_1,temp6_2);
	mul_matrices(WtV1,temp6_2,kocka6t);


	mul_matrices(VC,temp7_1,temp7_2);
	mul_matrices(WtV1,temp7_2,kocka7t);

	for(GLint i = 0 ; i < 8 ; i++){
		Qd[i] = transzform(kocka1t,kocka1[i]);
		Wd[i] = transzform(kocka2t,kocka2[i]);
		Ed[i] = transzform(kocka3t,kocka3[i]);
		Ad[i] = transzform(kocka4t,kocka4[i]);
		Sd[i] = transzform(kocka5t,kocka5[i]);
		Dd[i] = transzform(kocka6t,kocka6[i]);
		Fd[i] = transzform(kocka7t,kocka7[i]);
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

	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(Ad[0].x/Ad[0].h,Ad[0].y/Ad[0].h);
	glVertex2d(Ad[1].x/Ad[1].h,Ad[1].y/Ad[1].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Ad[0].x/Ad[0].h,Ad[0].y/Ad[0].h);
	glVertex2d(Ad[4].x/Ad[4].h,Ad[4].y/Ad[4].h);
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
	glBegin(GL_LINES);
	glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
	glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
	glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[0].x/Sd[0].h,Sd[0].y/Sd[0].h);
	glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
	glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[1].x/Sd[1].h,Sd[1].y/Sd[1].h);
	glVertex2d(Sd[5].x/Sd[5].h,Sd[5].y/Sd[5].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
	glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[2].x/Sd[2].h,Sd[2].y/Sd[2].h);
	glVertex2d(Sd[6].x/Sd[6].h,Sd[6].y/Sd[6].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[3].x/Sd[3].h,Sd[3].y/Sd[3].h);
	glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[6].x/Sd[6].h,Sd[6].y/Sd[6].h);
	glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
	glVertex2d(Sd[7].x/Sd[7].h,Sd[7].y/Sd[7].h);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(Sd[4].x/Sd[4].h,Sd[4].y/Sd[4].h);
	glVertex2d(Sd[5].x/Sd[5].h,Sd[5].y/Sd[5].h);
	glEnd();

	glBegin(GL_LINES);
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

	glutPostRedisplay();
	glutSwapBuffers();
}

int main (int argc, char** argv) {

	createVCMatrix();
	createFXMatrix(szogx);

	kocka1[0] = initPoint3dh(0.5,0.5,-0.5);
	kocka1[1] = initPoint3dh(-0.5,0.5,-0.5);
	kocka1[2] = initPoint3dh(-0.5,-0.5,-0.5);
	kocka1[3] = initPoint3dh(0.5,-0.5,-0.5);
	kocka1[4] = initPoint3dh(0.5,0.5,0.5);
	kocka1[5] = initPoint3dh(-0.5,0.5,0.5);
	kocka1[6] = initPoint3dh(-0.5,-0.5,0.5);
	kocka1[7] = initPoint3dh(0.5,-0.5,0.5);

	kocka2[0] = initPoint3dh(0.5,0.5+2,-0.5);
	kocka2[1] = initPoint3dh(-0.5,0.5+2,-0.5);
	kocka2[2] = initPoint3dh(-0.5,-0.5+2,-0.5);
	kocka2[3] = initPoint3dh(0.5,-0.5+2,-0.5);
	kocka2[4] = initPoint3dh(0.5,0.5+2,0.5);
	kocka2[5] = initPoint3dh(-0.5,0.5+2,0.5);
	kocka2[6] = initPoint3dh(-0.5,-0.5+2,0.5);
	kocka2[7] = initPoint3dh(0.5,-0.5+2,0.5);

	kocka3[0] = initPoint3dh(0.5,0.5-2,-0.5);
	kocka3[1] = initPoint3dh(-0.5,0.5-2,-0.5);
	kocka3[2] = initPoint3dh(-0.5,-0.5-2,-0.5);
	kocka3[3] = initPoint3dh(0.5,-0.5-2,-0.5);
	kocka3[4] = initPoint3dh(0.5,0.5-2,0.5);
	kocka3[5] = initPoint3dh(-0.5,0.5-2,0.5);
	kocka3[6] = initPoint3dh(-0.5,-0.5-2,0.5);
	kocka3[7] = initPoint3dh(0.5,-0.5-2,0.5);

	kocka4[0] = initPoint3dh(0.5-2,0.5,-0.5);
	kocka4[1] = initPoint3dh(-0.5-2,0.5,-0.5);
	kocka4[2] = initPoint3dh(-0.5-2,-0.5,-0.5);
	kocka4[3] = initPoint3dh(0.5-2,-0.5,-0.5);
	kocka4[4] = initPoint3dh(0.5-2,0.5,0.5);
	kocka4[5] = initPoint3dh(-0.5-2,0.5,0.5);
	kocka4[6] = initPoint3dh(-0.5-2,-0.5,0.5);
	kocka4[7] = initPoint3dh(0.5-2,-0.5,0.5);

	kocka5[0] = initPoint3dh(0.5+2,0.5,-0.5);
	kocka5[1] = initPoint3dh(-0.5+2,0.5,-0.5);
	kocka5[2] = initPoint3dh(-0.5+2,-0.5,-0.5);
	kocka5[3] = initPoint3dh(0.5+2,-0.5,-0.5);
	kocka5[4] = initPoint3dh(0.5+2,0.5,0.5);
	kocka5[5] = initPoint3dh(-0.5+2,0.5,0.5);
	kocka5[6] = initPoint3dh(-0.5+2,-0.5,0.5);
	kocka5[7] = initPoint3dh(0.5+2,-0.5,0.5);

	kocka6[0] = initPoint3dh(0.5,0.5,-0.5-2);
	kocka6[1] = initPoint3dh(-0.5,0.5,-0.5-2);
	kocka6[2] = initPoint3dh(-0.5,-0.5,-0.5-2);
	kocka6[3] = initPoint3dh(0.5,-0.5,-0.5-2);
	kocka6[4] = initPoint3dh(0.5,0.5,0.5-2);
	kocka6[5] = initPoint3dh(-0.5,0.5,0.5-2);
	kocka6[6] = initPoint3dh(-0.5,-0.5,0.5-2);
	kocka6[7] = initPoint3dh(0.5,-0.5,0.5-2);

	kocka7[0] = initPoint3dh(0.5,0.5,-0.5+2);
	kocka7[1] = initPoint3dh(-0.5,0.5,-0.5+2);
	kocka7[2] = initPoint3dh(-0.5,-0.5,-0.5+2);
	kocka7[3] = initPoint3dh(0.5,-0.5,-0.5+2);
	kocka7[4] = initPoint3dh(0.5,0.5,0.5+2);
	kocka7[5] = initPoint3dh(-0.5,0.5,0.5+2);
	kocka7[6] = initPoint3dh(-0.5,-0.5,0.5+2);
	kocka7[7] = initPoint3dh(0.5,-0.5,0.5+2);	

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