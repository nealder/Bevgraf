#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
GLint keyStates[256];
#define PI 3.141592653589793
GLint winWidth = 800;
GLint winHeight = 600;

typedef struct point3dh { GLdouble x, y, z, h; } POINT3DH;
typedef struct point2d { GLdouble x, y; } POINT2D;
typedef struct point3d { GLdouble x, y, z; } POINT3D;

class Side{
public:

	POINT3DH tomb[4];

	Side(POINT3DH a,POINT3DH b,POINT3DH c,POINT3DH d){
		
		this->tomb[0]=a;
		this->tomb[1]=b;
		this->tomb[2]=c;
		this->tomb[3]=d;


	}
	~Side(){

	}
};

GLdouble eltol1[3]={0,0,0};
GLdouble eltol2[3]={-2,0,0};
GLdouble eltol3[3]={2,0,0};
GLdouble eltol4[3]={0,-2,0};
GLdouble eltol5[3]={0,2,0};
GLdouble eltol6[3]={0,0,-2};
GLdouble eltol7[3]={0,0,2};
GLdouble temp1[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
GLdouble temp2[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
GLdouble VC[4][4];
GLdouble WtV[4][4];
GLdouble s = 3;
GLdouble deltaf = 0.15;
GLdouble deltav = 2 * 0.0174532925;
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

POINT3D centrum = initPoint3d(0, 0, s);

POINT3D C = initPoint3d (5,0,0);
POINT3D P = initPoint3d (0,0,0);
POINT3D up = initPoint3d (0, 0.0, 1.0);
POINT3D PCinit = initPoint3d(-(P.x-C.x),-(P.y-C.y),-(P.z-C.z));

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

POINT2D winMin = initPoint2d(-1, -1);
POINT2D winMax = initPoint2d(1, 1);
POINT2D viewMin = initPoint2d(200,100);
POINT2D viewMax = initPoint2d(600, 500);

void init( ) {
	glClearColor( 1.0, 1.0, 1.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
	glShadeModel( GL_FLAT );
	glPointSize( 10.0 );
	glLineWidth( 10.0 );
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

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations ( ) {
	if(keyStates['w']){
		if(C.z+deltaf<=10 ){
			C.z+=deltaf;
		}		
	}
	if(keyStates['s']){
		if(C.z-deltaf>=-10){
			C.z-=deltaf;
		}		
	}
	if(keyStates['d']){
		C.x=hossz(PCinit)*cos(deltav);
		C.y=hossz(PCinit)*sin(deltav);
		deltav+=0.01;	
	}
	if(keyStates['a']){
		C.x=hossz(PCinit)*cos(deltav);
		C.y=hossz(PCinit)*sin(deltav);
		deltav-=0.01; 	
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

void createKMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			K[i][j]=0;
		}
	}
	POINT3D PC = initPoint3d(-(P.x-C.x),-(P.y-C.y),-(P.z-C.z));
	POINT3D W = initPoint3d (PC.x / hossz(PC),
		PC.y / hossz(PC),
		PC.z / hossz(PC));

	POINT3D U = initPoint3d ((vektmul(up,W).x/hossz(vektmul(up,W))),
		(vektmul(up,W).y/hossz(vektmul(up,W))),
		(vektmul(up,W).z/hossz(vektmul(up,W))));

	POINT3D V = initPoint3d ((vektmul(W,U).x) / hossz(vektmul(W,U)), 
		(vektmul(W,U).y) / hossz(vektmul(W,U)), 
		(vektmul(W,U).z) / hossz(vektmul(W,U)));

	K[0][0]=U.x;
	K[0][1]=U.y;
	K[0][2]=U.z;
	K[0][3]=-(C.x*U.x + C.y*U.y + C.z*U.z);
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

void createTmp1(){
	for(int i =0; i<4 ; i++){
		for(int j =0; j<4 ; j++){
			temp1[i][j]=0;
		}
	}
}
void createTmp2(){
	for(int i =0; i<4 ; i++){
		for(int j =0; j<4 ; j++){
			temp2[i][j]=0;
		}
	}
}

POINT3D Sidemidp(Side G){
	POINT3D A;
	for(GLint i=0;i<4;i++){
		A.x+=G.tomb[i].x;
		A.y+=G.tomb[i].y;
		A.z+=G.tomb[i].z;
	}
	A.x=A.x/4;
	A.y=A.y/4;
	A.z=A.z/4;
	return A;
}

bool which_further(Side qwe, Side asd){
	POINT3D Q=initPoint3d(0-Sidemidp(qwe).x,0-Sidemidp(qwe).y,0-Sidemidp(qwe).z);
	POINT3D A=initPoint3d(0-Sidemidp(asd).x,0-Sidemidp(asd).y,0-Sidemidp(asd).z);
	
	return (sqrt(Q.x*Q.x + Q.y*Q.y + Q.z*Q.z) > sqrt(A.x*A.x + A.y*A.y + A.z*A.z));
}

bool YesorNo(Side Q){
	double tmp;
	POINT3D W=initPoint3d((centrum.x - Sidemidp(Q).x),(centrum.y - Sidemidp(Q).y),(centrum.z - Sidemidp(Q).z));
	POINT3D AS=initPoint3d((Q.tomb[1].x-Q.tomb[0].x),(Q.tomb[1].y-Q.tomb[0].y),(Q.tomb[1].z-Q.tomb[0].z));
	POINT3D AD=initPoint3d((Q.tomb[2].x-Q.tomb[0].x),(Q.tomb[2].y-Q.tomb[0].y),(Q.tomb[2].z-Q.tomb[0].z));
	POINT3D ASxAD=vektmul(AS,AD);
	tmp=ASxAD.x*W.x + ASxAD.y*W.y + ASxAD.z*W.z;

	return (tmp < 0);
}

void Display(){

	std::vector<Side> allSide;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	keyOperations();

	createVCMatrix();
	createWtVMatrix(viewMin,viewMax,winMin,winMax, WtV);
	createKMatrix();
	createTmp1();
	createTmp2();

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

	Side side1_1(displayable_kocka1[0],displayable_kocka1[3],displayable_kocka1[2],displayable_kocka1[1]);
	Side side1_2(displayable_kocka1[0],displayable_kocka1[3],displayable_kocka1[7],displayable_kocka1[4]);
	Side side1_3(displayable_kocka1[4],displayable_kocka1[7],displayable_kocka1[6],displayable_kocka1[5]);
	Side side1_4(displayable_kocka1[1],displayable_kocka1[2],displayable_kocka1[6],displayable_kocka1[5]);
	Side side1_5(displayable_kocka1[0],displayable_kocka1[1],displayable_kocka1[5],displayable_kocka1[4]);
	Side side1_6(displayable_kocka1[3],displayable_kocka1[2],displayable_kocka1[6],displayable_kocka1[7]);

	Side side2_1(displayable_kocka2[0],displayable_kocka2[3],displayable_kocka2[2],displayable_kocka2[1]);
	Side side2_2(displayable_kocka2[0],displayable_kocka2[3],displayable_kocka2[7],displayable_kocka2[4]);
	Side side2_3(displayable_kocka2[4],displayable_kocka2[7],displayable_kocka2[6],displayable_kocka2[5]);
	Side side2_4(displayable_kocka2[1],displayable_kocka2[2],displayable_kocka2[6],displayable_kocka2[5]);
	Side side2_5(displayable_kocka2[0],displayable_kocka2[1],displayable_kocka2[5],displayable_kocka2[4]);
	Side side2_6(displayable_kocka2[3],displayable_kocka2[2],displayable_kocka2[6],displayable_kocka2[7]);

	Side side3_1(displayable_kocka3[0],displayable_kocka3[3],displayable_kocka3[2],displayable_kocka3[1]);
	Side side3_2(displayable_kocka3[0],displayable_kocka3[3],displayable_kocka3[7],displayable_kocka3[4]);
	Side side3_3(displayable_kocka3[4],displayable_kocka3[7],displayable_kocka3[6],displayable_kocka3[5]);
	Side side3_4(displayable_kocka3[1],displayable_kocka3[2],displayable_kocka3[6],displayable_kocka3[5]);
	Side side3_5(displayable_kocka3[0],displayable_kocka3[1],displayable_kocka3[5],displayable_kocka3[4]);
	Side side3_6(displayable_kocka3[3],displayable_kocka3[2],displayable_kocka3[6],displayable_kocka3[7]);

	Side side4_1(displayable_kocka4[0],displayable_kocka4[3],displayable_kocka4[2],displayable_kocka4[1]);
	Side side4_2(displayable_kocka4[0],displayable_kocka4[3],displayable_kocka4[7],displayable_kocka4[4]);
	Side side4_3(displayable_kocka4[4],displayable_kocka4[7],displayable_kocka4[6],displayable_kocka4[5]);
	Side side4_4(displayable_kocka4[1],displayable_kocka4[2],displayable_kocka4[6],displayable_kocka4[5]);
	Side side4_5(displayable_kocka4[0],displayable_kocka4[1],displayable_kocka4[5],displayable_kocka4[4]);
	Side side4_6(displayable_kocka4[3],displayable_kocka4[2],displayable_kocka4[6],displayable_kocka4[7]);

	Side side5_1(displayable_kocka5[0],displayable_kocka5[3],displayable_kocka5[2],displayable_kocka5[1]);
	Side side5_2(displayable_kocka5[0],displayable_kocka5[3],displayable_kocka5[7],displayable_kocka5[4]);
	Side side5_3(displayable_kocka5[4],displayable_kocka5[7],displayable_kocka5[6],displayable_kocka5[5]);
	Side side5_4(displayable_kocka5[1],displayable_kocka5[2],displayable_kocka5[6],displayable_kocka5[5]);
	Side side5_5(displayable_kocka5[0],displayable_kocka5[1],displayable_kocka5[5],displayable_kocka5[4]);
	Side side5_6(displayable_kocka5[3],displayable_kocka5[2],displayable_kocka5[6],displayable_kocka5[7]);

	Side side6_1(displayable_kocka6[0],displayable_kocka6[3],displayable_kocka6[2],displayable_kocka6[1]);
	Side side6_2(displayable_kocka6[0],displayable_kocka6[3],displayable_kocka6[7],displayable_kocka6[4]);
	Side side6_3(displayable_kocka6[4],displayable_kocka6[7],displayable_kocka6[6],displayable_kocka6[5]);
	Side side6_4(displayable_kocka6[1],displayable_kocka6[2],displayable_kocka6[6],displayable_kocka6[5]);
	Side side6_5(displayable_kocka6[0],displayable_kocka6[1],displayable_kocka6[5],displayable_kocka6[4]);
	Side side6_6(displayable_kocka6[3],displayable_kocka6[2],displayable_kocka6[6],displayable_kocka6[7]);

	Side side7_1(displayable_kocka7[0],displayable_kocka7[3],displayable_kocka7[2],displayable_kocka7[1]);
	Side side7_2(displayable_kocka7[0],displayable_kocka7[3],displayable_kocka7[7],displayable_kocka7[4]);
	Side side7_3(displayable_kocka7[4],displayable_kocka7[7],displayable_kocka7[6],displayable_kocka7[5]);
	Side side7_4(displayable_kocka7[1],displayable_kocka7[2],displayable_kocka7[6],displayable_kocka7[5]);
	Side side7_5(displayable_kocka7[0],displayable_kocka7[1],displayable_kocka7[5],displayable_kocka7[4]);
	Side side7_6(displayable_kocka7[3],displayable_kocka7[2],displayable_kocka7[6],displayable_kocka7[7]);
	//elso 
	allSide.push_back(side1_1);
	allSide.push_back(side1_2);
	allSide.push_back(side1_3);
	allSide.push_back(side1_4);
	allSide.push_back(side1_5);
	allSide.push_back(side1_6);
	//masodik
	allSide.push_back(side2_1);
	allSide.push_back(side2_2);
	allSide.push_back(side2_3);
	allSide.push_back(side2_4);
	allSide.push_back(side2_5);
	allSide.push_back(side2_6);
//harmadik
	allSide.push_back(side3_1);
	allSide.push_back(side3_2);
	allSide.push_back(side3_3);
	allSide.push_back(side3_4);
	allSide.push_back(side3_5);
	allSide.push_back(side3_6);
//negyedik
	allSide.push_back(side4_1);
	allSide.push_back(side4_2);
	allSide.push_back(side4_3);
	allSide.push_back(side4_4);
	allSide.push_back(side4_5);
	allSide.push_back(side4_6);
//otodik
	allSide.push_back(side5_1);
	allSide.push_back(side5_2);
	allSide.push_back(side5_3);
	allSide.push_back(side5_4);
	allSide.push_back(side5_5);
	allSide.push_back(side5_6);
//hatodik
	allSide.push_back(side6_1);
	allSide.push_back(side6_2);
	allSide.push_back(side6_3);
	allSide.push_back(side6_4);
	allSide.push_back(side6_5);
	allSide.push_back(side6_6);
//hetedik
	allSide.push_back(side7_1);
	allSide.push_back(side7_2);
	allSide.push_back(side7_3);
	allSide.push_back(side7_4);
	allSide.push_back(side7_5);
	allSide.push_back(side7_6);


	for(auto it = allSide.begin();it != allSide.end();  ){
		if(YesorNo(*it)){
			it = allSide.erase(it);
		}
		else{
			it++;
		}
	}//
	//std::qsort...
	std::sort( allSide.begin(), allSide.end(), which_further);  

	glColor3f(0.6,0.0,0.0);

	for( auto it =allSide.begin() ; it != allSide.end(); it++){
		
			glBegin(GL_POLYGON);
			for(GLint i=0;i<4;i++){
				glVertex2d((*it).tomb[i].x/(*it).tomb[i].h,(*it).tomb[i].y/(*it).tomb[i].h);
			}
			glEnd();
	}

	//elso kocka elso oldal
	/*glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_1.tomb[i].x/side1_1.tomb[i].h,side1_1.tomb[i].y/side1_1.tomb[i].h);
	}
	glEnd();

	//elso kocka masodik oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_2.tomb[i].x/side1_2.tomb[i].h,side1_2.tomb[i].y/side1_2.tomb[i].h);
	}
	glEnd();

	//elso kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_3.tomb[i].x/side1_3.tomb[i].h,side1_3.tomb[i].y/side1_3.tomb[i].h);
	}
	glEnd();

	//elso kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_4.tomb[i].x/side1_4.tomb[i].h,side1_4.tomb[i].y/side1_4.tomb[i].h);
	}
	glEnd();

	//elso kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_5.tomb[i].x/side1_5.tomb[i].h,side1_5.tomb[i].y/side1_5.tomb[i].h);
	}
	glEnd();

	//elso kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_6.tomb[i].x/side1_6.tomb[i].h,side1_6.tomb[i].y/side1_6.tomb[i].h);
	}
	glEnd();


	glColor3f(0.0,0.6,0.0);
	//2 kocka elso oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_1.tomb[i].x/side2_1.tomb[i].h,side2_1.tomb[i].y/side2_1.tomb[i].h);
	}
	glEnd();

	//2 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_2.tomb[i].x/side2_2.tomb[i].h,side2_2.tomb[i].y/side2_2.tomb[i].h);
	}
	glEnd();

	//2 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_3.tomb[i].x/side2_3.tomb[i].h,side2_3.tomb[i].y/side2_3.tomb[i].h);
	}
	glEnd();

	//2 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_4.tomb[i].x/side2_4.tomb[i].h,side2_4.tomb[i].y/side2_4.tomb[i].h);
	}
	glEnd();

	//2 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_5.tomb[i].x/side2_5.tomb[i].h,side2_5.tomb[i].y/side2_5.tomb[i].h);
	}
	glEnd();

	//2 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_6.tomb[i].x/side2_6.tomb[i].h,side2_6.tomb[i].y/side2_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,0.0,0.6);
	//3 kocka 1 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_1.tomb[i].x/side3_1.tomb[i].h,side3_1.tomb[i].y/side3_1.tomb[i].h);
	}
	glEnd();

	//3 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_2.tomb[i].x/side3_2.tomb[i].h,side3_2.tomb[i].y/side3_2.tomb[i].h);
	}
	glEnd();

	//3 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_3.tomb[i].x/side3_3.tomb[i].h,side3_3.tomb[i].y/side3_3.tomb[i].h);
	}
	glEnd();

	//3 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_4.tomb[i].x/side3_4.tomb[i].h,side3_4.tomb[i].y/side3_4.tomb[i].h);
	}
	glEnd();

	//3 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_5.tomb[i].x/side3_5.tomb[i].h,side3_5.tomb[i].y/side3_5.tomb[i].h);
	}
	glEnd();

	//3 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_6.tomb[i].x/side3_6.tomb[i].h,side3_6.tomb[i].y/side3_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	//4 kocka elso oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_1.tomb[i].x/side4_1.tomb[i].h,side4_1.tomb[i].y/side4_1.tomb[i].h);
	}
	glEnd();

	//4 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_2.tomb[i].x/side4_2.tomb[i].h,side4_2.tomb[i].y/side4_2.tomb[i].h);
	}
	glEnd();

	//4 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_3.tomb[i].x/side4_3.tomb[i].h,side4_3.tomb[i].y/side4_3.tomb[i].h);
	}
	glEnd();

	//4 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_4.tomb[i].x/side4_4.tomb[i].h,side4_4.tomb[i].y/side4_4.tomb[i].h);
	}
	glEnd();

	//4 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_5.tomb[i].x/side4_5.tomb[i].h,side4_5.tomb[i].y/side4_5.tomb[i].h);
	}
	glEnd();

	//4 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_6.tomb[i].x/side4_6.tomb[i].h,side4_6.tomb[i].y/side4_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.6,0.0,0.6);
	//5 kocka 1 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_1.tomb[i].x/side5_1.tomb[i].h,side5_1.tomb[i].y/side5_1.tomb[i].h);
	}
	glEnd();

	//5 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_2.tomb[i].x/side5_2.tomb[i].h,side5_2.tomb[i].y/side5_2.tomb[i].h);
	}
	glEnd();

	//5 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_3.tomb[i].x/side5_3.tomb[i].h,side5_3.tomb[i].y/side5_3.tomb[i].h);
	}
	glEnd();

	//5 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_4.tomb[i].x/side5_4.tomb[i].h,side5_4.tomb[i].y/side5_4.tomb[i].h);
	}
	glEnd();

	//5 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_5.tomb[i].x/side5_5.tomb[i].h,side5_5.tomb[i].y/side5_5.tomb[i].h);
	}
	glEnd();

	//5 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_6.tomb[i].x/side5_6.tomb[i].h,side5_6.tomb[i].y/side5_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.6,0.6,0.0);
	//6 kocka 1 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_1.tomb[i].x/side6_1.tomb[i].h,side6_1.tomb[i].y/side6_1.tomb[i].h);
	}
	glEnd();

	//6 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_2.tomb[i].x/side6_2.tomb[i].h,side6_2.tomb[i].y/side6_2.tomb[i].h);
	}
	glEnd();

	//6 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_3.tomb[i].x/side6_3.tomb[i].h,side6_3.tomb[i].y/side6_3.tomb[i].h);
	}
	glEnd();

	//6 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_4.tomb[i].x/side6_4.tomb[i].h,side6_4.tomb[i].y/side6_4.tomb[i].h);
	}
	glEnd();

	//6 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_5.tomb[i].x/side6_5.tomb[i].h,side6_5.tomb[i].y/side6_5.tomb[i].h);
	}
	glEnd();

	//6 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_6.tomb[i].x/side6_6.tomb[i].h,side6_6.tomb[i].y/side6_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,0.6,0.6);
	//7 kocka 1 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_1.tomb[i].x/side7_1.tomb[i].h,side7_1.tomb[i].y/side7_1.tomb[i].h);
	}
	glEnd();

	//7 kocka 2 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_2.tomb[i].x/side7_2.tomb[i].h,side7_2.tomb[i].y/side7_2.tomb[i].h);
	}
	glEnd();

	//7 kocka 3 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_3.tomb[i].x/side7_3.tomb[i].h,side7_3.tomb[i].y/side7_3.tomb[i].h);
	}
	glEnd();

	//7 kocka 4 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_4.tomb[i].x/side7_4.tomb[i].h,side7_4.tomb[i].y/side7_4.tomb[i].h);
	}
	glEnd();

	//7 kocka 5 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_5.tomb[i].x/side7_5.tomb[i].h,side7_5.tomb[i].y/side7_5.tomb[i].h);
	}
	glEnd();

	//7 kocka 6 oldal
	glBegin(GL_POLYGON);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_6.tomb[i].x/side7_6.tomb[i].h,side7_6.tomb[i].y/side7_6.tomb[i].h);
	}
	glEnd();

	glColor3f(1.0,0.0,0.0);

	//elso kocka elso oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_1.tomb[i].x/side1_1.tomb[i].h,side1_1.tomb[i].y/side1_1.tomb[i].h);
	}
	glEnd();

	//elso kocka masodik oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_2.tomb[i].x/side1_2.tomb[i].h,side1_2.tomb[i].y/side1_2.tomb[i].h);
	}
	glEnd();

	//elso kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_3.tomb[i].x/side1_3.tomb[i].h,side1_3.tomb[i].y/side1_3.tomb[i].h);
	}
	glEnd();

	//elso kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_4.tomb[i].x/side1_4.tomb[i].h,side1_4.tomb[i].y/side1_4.tomb[i].h);
	}
	glEnd();

	//elso kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_5.tomb[i].x/side1_5.tomb[i].h,side1_5.tomb[i].y/side1_5.tomb[i].h);
	}
	glEnd();

	//elso kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side1_6.tomb[i].x/side1_6.tomb[i].h,side1_6.tomb[i].y/side1_6.tomb[i].h);
	}
	glEnd();


	glColor3f(0.0,1.0,0.0);
	//2 kocka elso oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_1.tomb[i].x/side2_1.tomb[i].h,side2_1.tomb[i].y/side2_1.tomb[i].h);
	}
	glEnd();

	//2 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_2.tomb[i].x/side2_2.tomb[i].h,side2_2.tomb[i].y/side2_2.tomb[i].h);
	}
	glEnd();

	//2 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_3.tomb[i].x/side2_3.tomb[i].h,side2_3.tomb[i].y/side2_3.tomb[i].h);
	}
	glEnd();

	//2 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_4.tomb[i].x/side2_4.tomb[i].h,side2_4.tomb[i].y/side2_4.tomb[i].h);
	}
	glEnd();

	//2 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_5.tomb[i].x/side2_5.tomb[i].h,side2_5.tomb[i].y/side2_5.tomb[i].h);
	}
	glEnd();

	//2 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side2_6.tomb[i].x/side2_6.tomb[i].h,side2_6.tomb[i].y/side2_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,0.0,1.0);
	//3 kocka 1 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_1.tomb[i].x/side3_1.tomb[i].h,side3_1.tomb[i].y/side3_1.tomb[i].h);
	}
	glEnd();

	//3 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_2.tomb[i].x/side3_2.tomb[i].h,side3_2.tomb[i].y/side3_2.tomb[i].h);
	}
	glEnd();

	//3 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_3.tomb[i].x/side3_3.tomb[i].h,side3_3.tomb[i].y/side3_3.tomb[i].h);
	}
	glEnd();

	//3 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_4.tomb[i].x/side3_4.tomb[i].h,side3_4.tomb[i].y/side3_4.tomb[i].h);
	}
	glEnd();

	//3 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_5.tomb[i].x/side3_5.tomb[i].h,side3_5.tomb[i].y/side3_5.tomb[i].h);
	}
	glEnd();

	//3 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side3_6.tomb[i].x/side3_6.tomb[i].h,side3_6.tomb[i].y/side3_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	//4 kocka elso oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_1.tomb[i].x/side4_1.tomb[i].h,side4_1.tomb[i].y/side4_1.tomb[i].h);
	}
	glEnd();

	//4 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_2.tomb[i].x/side4_2.tomb[i].h,side4_2.tomb[i].y/side4_2.tomb[i].h);
	}
	glEnd();

	//4 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_3.tomb[i].x/side4_3.tomb[i].h,side4_3.tomb[i].y/side4_3.tomb[i].h);
	}
	glEnd();

	//4 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_4.tomb[i].x/side4_4.tomb[i].h,side4_4.tomb[i].y/side4_4.tomb[i].h);
	}
	glEnd();

	//4 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_5.tomb[i].x/side4_5.tomb[i].h,side4_5.tomb[i].y/side4_5.tomb[i].h);
	}
	glEnd();

	//4 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side4_6.tomb[i].x/side4_6.tomb[i].h,side4_6.tomb[i].y/side4_6.tomb[i].h);
	}
	glEnd();
	glColor3f(1.0,0.0,1.0);
	//5 kocka 1 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_1.tomb[i].x/side5_1.tomb[i].h,side5_1.tomb[i].y/side5_1.tomb[i].h);
	}
	glEnd();

	//5 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_2.tomb[i].x/side5_2.tomb[i].h,side5_2.tomb[i].y/side5_2.tomb[i].h);
	}
	glEnd();

	//5 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_3.tomb[i].x/side5_3.tomb[i].h,side5_3.tomb[i].y/side5_3.tomb[i].h);
	}
	glEnd();

	//5 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_4.tomb[i].x/side5_4.tomb[i].h,side5_4.tomb[i].y/side5_4.tomb[i].h);
	}
	glEnd();

	//5 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_5.tomb[i].x/side5_5.tomb[i].h,side5_5.tomb[i].y/side5_5.tomb[i].h);
	}
	glEnd();

	//5 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side5_6.tomb[i].x/side5_6.tomb[i].h,side5_6.tomb[i].y/side5_6.tomb[i].h);
	}
	glEnd();
	glColor3f(1.0,1.0,0.0);
	//6 kocka 1 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_1.tomb[i].x/side6_1.tomb[i].h,side6_1.tomb[i].y/side6_1.tomb[i].h);
	}
	glEnd();

	//6 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_2.tomb[i].x/side6_2.tomb[i].h,side6_2.tomb[i].y/side6_2.tomb[i].h);
	}
	glEnd();

	//6 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_3.tomb[i].x/side6_3.tomb[i].h,side6_3.tomb[i].y/side6_3.tomb[i].h);
	}
	glEnd();

	//6 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_4.tomb[i].x/side6_4.tomb[i].h,side6_4.tomb[i].y/side6_4.tomb[i].h);
	}
	glEnd();

	//6 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_5.tomb[i].x/side6_5.tomb[i].h,side6_5.tomb[i].y/side6_5.tomb[i].h);
	}
	glEnd();

	//6 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side6_6.tomb[i].x/side6_6.tomb[i].h,side6_6.tomb[i].y/side6_6.tomb[i].h);
	}
	glEnd();
	glColor3f(0.0,1.0,1.0);
	//7 kocka 1 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_1.tomb[i].x/side7_1.tomb[i].h,side7_1.tomb[i].y/side7_1.tomb[i].h);
	}
	glEnd();

	//7 kocka 2 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_2.tomb[i].x/side7_2.tomb[i].h,side7_2.tomb[i].y/side7_2.tomb[i].h);
	}
	glEnd();

	//7 kocka 3 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_3.tomb[i].x/side7_3.tomb[i].h,side7_3.tomb[i].y/side7_3.tomb[i].h);
	}
	glEnd();

	//7 kocka 4 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_4.tomb[i].x/side7_4.tomb[i].h,side7_4.tomb[i].y/side7_4.tomb[i].h);
	}
	glEnd();

	//7 kocka 5 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_5.tomb[i].x/side7_5.tomb[i].h,side7_5.tomb[i].y/side7_5.tomb[i].h);
	}
	glEnd();

	//7 kocka 6 oldal
	glBegin(GL_LINE_LOOP);
	for(GLint i=0;i<4;i++){
		glVertex2d(side7_6.tomb[i].x/side7_6.tomb[i].h,side7_6.tomb[i].y/side7_6.tomb[i].h);
	}
	glEnd();*/

	for( auto it =allSide.begin() ; it != allSide.end(); it++){
		
			glBegin(GL_LINE_LOOP);
			for(GLint i=0;i<4;i++){
				glVertex2d((*it).tomb[i].x/(*it).tomb[i].h,(*it).tomb[i].y/(*it).tomb[i].h);
			}
			glEnd();
			
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

int main (int argc, char** argv) {

	createVCMatrix();
	createWtVMatrix(viewMin,viewMax,winMin,winMax, WtV);
	createKMatrix();
	createTmp1();
	createTmp2();

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

	std::cout << "| " << kocka2[0].x << std::endl;

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (500, 100);
	glutInitWindowSize (800, 600);
	glutCreateWindow ("hatodik");
	init ( );
	glutDisplayFunc (Display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop ( );
	return 0;
}