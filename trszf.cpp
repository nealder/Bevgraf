#include <GL/glut.h>
#include <iostream>
#include <cmath>

typedef struct point2dh { GLfloat x1, x2, x3; } POINT2Dh;

typedef struct point2d { GLfloat x1, x2; } POINT2D;


POINT2Dh initPOINT2Dh(GLfloat x1, GLfloat x2){

	POINT2Dh e;
	e.x1 = x1;
	e.x2 = x2;
	e.x3 = 1;
	return e;
}

POINT2D initPOINT2D(GLfloat x1, GLfloat x2){

	POINT2D e;
	e.x1 = x1;
	e.x2 = x2;
	return e;
}

POINT2Dh trszf ( GLfloat Th[][3], POINT2Dh Ph){
	POINT2Dh P_;
	P_.x1 = Th[0][0]*Ph.x1 + Th[0][1]*Ph.x2 + Th[0][2]*Ph.x3;
	P_.x2 = Th[1][0]*Ph.x1 + Th[1][1]*Ph.x2 + Th[1][2]*Ph.x3;
	P_.x3 = Th[2][0]*Ph.x1 + Th[2][1]*Ph.x2 + Th[2][2]*Ph.x3;
	return P_;
}



void init( ) {
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 400.0, 0.0, 300.0);
    glPointSize( 10.0 );
}

void drawPoint2Dh ( POINT2Dh P ){
	POINT2D Q = initPOINT2D ( (P.x1/P.x3), (P.x2/P.x3));
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin (GL_POINTS);
		glVertex2f( Q.x1, Q.x2);
	glEnd( );
}

void mul_matrices( float A[ ][ 3 ], float B[ ][ 3 ], float C[ ][ 3 ] ){
	int i, j, k;

	float sum;

	for( i = 0; i < 3; i++ ){
		for( j = 0; j < 3; j++ ) {
        		sum = 0;
        		for( k = 0; k < 3; k++ ){
            			sum = sum + A[ i ][ k ] * B[ k ][ j ];
			}
        		C[ i ][ j ] = sum;
    		}
	}
}


POINT2Dh A = initPOINT2Dh(100,50);
GLfloat E[3][3] = {{1,0,200},{0,1,100},{0,0,1}};
GLfloat F[3][3] = {{ cos(M_PI/10), -sin(M_PI/10), 0 }, { sin(M_PI/10), cos(M_PI/10), 0 }, { 0, 0, 1 }};
GLfloat M[3][3];
GLfloat E2[3][3] = {{1,0,50},{0,1,50},{0,0,1}};
GLfloat temp[3][3];

void display( ) {
    int i;
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);

	/*drawPoint2Dh(A);
	A = trszf ( F , A);
	drawPoint2Dh(A);
	A = trszf ( E , A);
	drawPoint2Dh(A);
	A = trszf ( E2 , A);
	drawPoint2Dh(A);*/
	mul_matrices( E , F , temp );
	mul_matrices( temp , E2 , M);
	A = trszf( M , A);
	drawPoint2Dh(A);
	
    glFlush( );
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("trszf");
    init ( );
    glutDisplayFunc (display);
    glutMainLoop ( );
    return 0;
}
