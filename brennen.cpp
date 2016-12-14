#include <GL/glut.h>
#include <math.h>

GLfloat size=5;
void glPointSize(GLfloat size);



void init( ) {
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 400.0, 0.0, 300.0);

	
}

void display(){
	GLint i;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.5, 0.0);
	glBegin (GL_LINES);
	for ( i = 0; i < 300; i=i+10 ){
		glVertex2i ( 400 , i );
		glVertex2i ( 0 , i );
		
	}
	for ( i = 0; i < 400; i=i+10 ){
		glVertex2i ( i , 0 );
		glVertex2i ( i , 300 );
		
	}
	glEnd( );
	
	glFlush( );
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (400, 300);
    glutCreateWindow ("brennen");
    init ( );
    glutDisplayFunc (display);
    glutMainLoop ( );
    return 0;
}
