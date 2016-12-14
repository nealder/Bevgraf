#include <GL/glut.h>
#include <math.h>

GLint const n = 7 ;
GLfloat const r = 120;

GLfloat points[ n ][ 2 ];

void pointscalc( GLint q , GLint n){	

	points[q][0] = r * cos(2*M_PI*q/n) + 200;
	points[q][1] = r * sin(2*M_PI*q/n) + 150;
	
}

void init( ) {
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 400.0, 0.0, 300.0);
}

void display( ) {
    int i=0;
    int j=0;
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.5, 0.0);
	while(i<n){
	    pointscalc( i ,  n);
	    i++;
	}

    glBegin (GL_LINE_LOOP);
	for ( i = 0; i < n; i++ ){
	    for ( j = i+1; j < n; j++){
	         glVertex2fv ( points[ i ] );
		 glVertex2fv ( points[ j ] );
		 }
	   //break; 
	}
    glEnd( );

    glFlush( );
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("Polygon");
    init ( );
    glutDisplayFunc (display);
    glutMainLoop ( );
    return 0;
}
