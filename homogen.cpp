#include <GL/glut.h>
#include <iostream>

typedef struct point2dh { GLfloat x, y;GLfloat homo; } POINT2Dh;

typedef struct point2d { GLfloat x, y; } POINT2D;

POINT2Dh initPOINT2Dh(GLfloat x, GLfloat y){

	POINT2Dh e;
	e.x = x;
	e.y = y;
	e.homo = 1;
	return e;
}

POINT2D initPOINT2D(GLfloat x, GLfloat y){

	POINT2D e;
	e.x = x;
	e.y = y;
	return e;
}

POINT2Dh metszilleszt(POINT2Dh X, POINT2Dh Y){
	POINT2Dh e;
	
	e.x = X.y * Y.homo - X.homo * Y.y; 
	e.y = -1 * ( X.x * Y.homo - X.homo * Y.x );
	e.homo = X.x * Y.y - Y.x * X.y;

	return e;
}

POINT2Dh A = initPOINT2Dh(100,100);
POINT2Dh B = initPOINT2Dh(300,150);
POINT2Dh C = initPOINT2Dh(200,175);
POINT2Dh D = initPOINT2Dh(350,50);

void init( ) {
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 400.0, 0.0, 300.0);
    glPointSize( 10.0 );
}

void drawPoint2Dh ( POINT2Dh P ){
	POINT2D Q = initPOINT2D ( (P.x/P.homo), (P.y/P.homo));
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin (GL_POINTS);
		glVertex2f( Q.x, Q.y);
	glEnd( );

}

void display( ) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);

    glBegin (GL_LINES);
	glVertex2f ( A.x, A.y );
	glVertex2f ( B.x, B.y );
	glVertex2f ( C.x, C.y );
	glVertex2f ( D.x, D.y );	
    glEnd( );
	drawPoint2Dh( metszilleszt ( metszilleszt ( A, B ),metszilleszt ( C, D )));
    
    glFlush( );
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("homogen");
    init ( );
    glutDisplayFunc (display);
    glutMainLoop ( );
    return 0;
}
