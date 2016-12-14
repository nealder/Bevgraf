#include <GL/glut.h>
#include <math.h>
GLsizei winWidth = 800, winHeight = 600;
typedef struct point3d { GLdouble x, y, z; } POINT3D;
typedef struct point3dh { GLdouble x, y, z, h; } POINT3DH;
typedef struct vect { GLdouble x, y, z; } VECT;
GLdouble K[4][4];
GLdouble nagyit[4][4];
GLdouble eltol[4][4];
GLdouble VM[4][4];
GLdouble temp1[4][4];
GLdouble temp2[4][4];
POINT3DH Q[8];
	
void init( ) {
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
    glShadeModel( GL_FLAT );
    glPointSize( 6.0 );
    glLineWidth( 5.0 );
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

POINT3D initPoint3d(GLdouble x, GLdouble y, GLdouble z){
	POINT3D P;
	P.x = x;
	P.y = y;
	P.z = z;
	return P;
}

POINT3DH initPoint3dh(GLdouble x, GLdouble y, GLdouble z){
	POINT3DH P;
	P.x = x;
	P.y = y;
	P.z = z;
	return P;
}

VECT iniVect(GLdouble x, GLdouble y, GLdouble z){
	VECT P;
	P.x = x;
	P.y = y;
	P.z = z;
	return P;
}

GLdouble hossz(POINT3D A){
	return sqrt((A.x)*(A.x) + (A.y)*(A.y) + (A.z)*(A.z));
}

POINT3D vektmul(POINT3D A, POINT3D B){
	POINT3D P;
	P.x = A.y*B.z - A.z*B.y;
	P.y = A.z*B.x - A.x*B.z;
	P.z = A.x*B.y - A.y*B.x;
	return P;
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

void createKMatrix(){
	for(int i = 0; i<4 ; i++){
		for(int j = 0; j<4 ; j++){
			K[i][j]=0;
		}
	}
	K[0][0]=U.x;
	K[0][1]=U.y;
	K[0][2]=U.z;
	K[0][3]=-(C.x*W.x + C.y*W.y + C.z*W.z);;
	K[1][0]=V.x;
	K[1][1]=V.y;
	K[1][2]=V.z;
	K[1][3]=-(C.x*U.x + C.y*U.y + C.z*U.z);
	K[2][0]=W.x;
	K[2][1]=W.y;
	K[2][2]=W.z;
	K[2][3]=-(C.x*V.x + C.y*V.y + C.z*V.z);
	K[3][3]=1;
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

POINT3DH transzform(double matrix[][4], POINT3DH Q){
	POINT3DH P;
		P.x=matrix[0][0]*Q.x + matrix[0][1]*Q.y + matrix[0][2]*Q.z + matrix[0][3]*Q.h;
		P.y=matrix[1][0]*Q.x + matrix[1][1]*Q.y + matrix[1][2]*Q.z + matrix[1][3]*Q.h;
		P.z=matrix[2][0]*Q.x + matrix[2][1]*Q.y + matrix[2][2]*Q.z + matrix[2][3]*Q.h;
		P.h=matrix[3][0]*Q.x + matrix[3][1]*Q.y + matrix[3][2]*Q.z + matrix[3][3]*Q.h;
	return P;
}

void Display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POINTS);
		for(GLint i = 0; i < 8 ; i ++){
			glVertex2d(Q[i].x/Q[i].h, Q[i].y/Q[i].h);
		}
	glEnd();

	glutSwapBuffers();
}

int main (int argc, char** argv) {

	createKMatrix();
	createTMatrix();
	createNMatrix();
	createVMMatrix();

	mul_matrices(VM, nagyit, temp2);
	//mul_matrices(VM, temp1, temp2);
	mul_matrices( eltol, temp2, temp1);

	Q[0] = initPoint3dh(0.5,0.5,-0.5);
	Q[1] = initPoint3dh(-0.5,0.5,-0.5);
	Q[2] = initPoint3dh(-0.5,-0.5,-0.5);
	Q[3] = initPoint3dh(0.5,-0.5,-0.5);
	Q[4] = initPoint3dh(0.5,0.5,0.5);
	Q[5] = initPoint3dh(-0.5,0.5,0.5);
	Q[6] = initPoint3dh(-0.5,-0.5,0.5);
	Q[7] = initPoint3dh(0.5,-0.5,0.5);

	Q[0] = transzform(temp1, Q[0]);
	Q[1] = transzform(temp1, Q[1]);
	Q[2] = transzform(temp1, Q[2]);
	Q[3] = transzform(temp1, Q[3]);
	Q[4] = transzform(temp1, Q[4]);
	Q[5] = transzform(temp1, Q[5]);
	Q[6] = transzform(temp1, Q[6]);
	Q[7] = transzform(temp1, Q[7]);

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("asd");
    init ( );
    glutDisplayFunc (Display);
    glutMainLoop ( );
    return 0;
}