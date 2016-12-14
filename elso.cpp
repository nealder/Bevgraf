#include <GL/glut.h>
#include <math.h>

GLint keyStates[256];
GLfloat delta = 0.5;
GLsizei winWidth = 800, winHeight = 600;
#define PI 3.141592653589793
GLint const Radius= 20;
GLint current = 0;

typedef struct point2d {GLdouble x, y ;} POINT2D;
typedef struct circle { GLdouble x, y, vx, vy; } CIRCLE;
CIRCLE Circles[20];

POINT2D initPoint2d(GLdouble x, GLdouble y){
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

CIRCLE initCircle(GLdouble x, GLdouble y) {
	CIRCLE P;
	P.x = x;
	P.y = y;
	P.vx = (rand() % 1000-500)*0.001;
	P.vy = (rand() % 1000-500)*0.001;
	return P;
}

POINT2D A = initPoint2d(0,300);
POINT2D B = initPoint2d(800,300);
POINT2D C = initPoint2d(400,0);
POINT2D D = initPoint2d(400,600);

void init( ) {
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
    glShadeModel( GL_FLAT );
    glPointSize( 6.0 );
    glLineWidth( 5.0 );
}

void drawDots(){
	POINT2D normal1 = initPoint2d(-1*(B.y-A.y),(B.x-A.x));
	POINT2D normal2 = initPoint2d(-1*(D.y-C.y),(D.x-C.x));
	double asd = normal1.x*A.x + normal1.y*A.y;
	double qwe = normal2.x*C.x + normal2.y*C.y;
	glBegin(GL_POINTS);
	    for(int i = 10; i < 800; i+=20){
	        for(int j = 10; j < 600; j+=20){	
		    if(((normal1.x*i + normal1.y*j)>asd) && ((normal2.x*i + normal2.y*j)>qwe)){glColor3f(1.0,0.0,0.5);}
		    if(((normal1.x*i + normal1.y*j)>asd) && ((normal2.x*i + normal2.y*j)<qwe)){glColor3f(0.0,1.0,0.5);}
		    if(((normal2.x*i + normal2.y*j)>qwe) && ((normal1.x*i + normal1.y*j)<asd)){glColor3f(0.5,0.0,1.0);}
		    if(((normal2.x*i + normal2.y*j)<qwe) && ((normal1.x*i + normal1.y*j)<asd)){glColor3f(0.9,0.5,0.0);}
		    glVertex2i(i,j);
	        }
	    }
	glEnd();
}

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void keyOperations ( ) {
    if (keyStates['a']) {				//függőleges egyenes
	if(C.x-delta < 0){}
		else {C.x-=delta; D.x+=delta;} }
    if (keyStates['d']) {
	if(C.x+delta > 800){}
		else {C.x+=delta; D.x-=delta;} }

    if (keyStates['s']) {				//vízszintes egyenes
	if(A.y-delta < 0){}
		else {A.y-=delta; B.y+=delta;} }
    if (keyStates['w']) {
	if(A.y+delta > 600){}
		else {A.y+=delta; B.y-=delta;} }

    glutPostRedisplay( );
}

void processMouse( GLint button, GLint action, GLint xMouse , GLint yMouse ){
	if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN &&  current < 20){
		yMouse = winHeight - yMouse;
		Circles[current] = initCircle(xMouse, yMouse );
		current++;
	}
	if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
	     for(GLint i = 0; i< current ; i++){
		if((xMouse-Circles[i].x )*(xMouse-Circles[i].x )+((winHeight-yMouse)-Circles[i].y)*((winHeight-yMouse)-Circles[i].y) < Radius*Radius) {			
		    Circles[i].x = Circles[current-1].x;
		    Circles[i].y = Circles[current-1].y;
		    Circles[i].vx = Circles[current-1].vx;
		    Circles[i].vx = Circles[current-1].vx;
		    current--;
		}
	    }
	}
}

void circle(CIRCLE O, GLdouble r) {

	glBegin(GL_POLYGON);
	for (GLdouble t = 0; t <= 2 * PI; t += 0.01)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

bool Distance(POINT2D A, POINT2D B,CIRCLE T){
	POINT2D normal = initPoint2d(-1*(B.y - A.y), (B.x - A.x));
	double c = normal.x*A.x + normal.y*A.y; 
	return (abs((T.x*normal.x) + (T.y*normal.y)- c)/sqrt((normal.x*normal.x)+(normal.y*normal.y))<=Radius);
}

void Proj(POINT2D& A, POINT2D& B, CIRCLE& T){
	POINT2D irv = initPoint2d((B.x - A.x), (B.y - A.y));
	GLdouble temp = ((T.vx*irv.x + T.vy*irv.y)/(irv.x*irv.x + irv.y*irv.y))*2;
	irv.x*=temp;
	irv.y*=temp;
	T.vx = (-1*T.vx + irv.x);
	T.vy = (-1*T.vy + irv.y);
}

POINT2D balF0= initPoint2d(0,0);
POINT2D balF1= initPoint2d(0,600);
POINT2D jobbF0= initPoint2d(800,600);
POINT2D jobbF1= initPoint2d(800,0);
POINT2D felF0= initPoint2d(0,600);
POINT2D felF1= initPoint2d(800,600);
POINT2D alF0= initPoint2d(0,0);
POINT2D alF1= initPoint2d(800,0);

void update (int n){
	for(int i = 0 ; i < current; i++){

		Circles[i].x+=Circles[i].vx;
		Circles[i].y+=Circles[i].vy;	
	
	    if(Distance(balF0,balF1,Circles[i])){
		Proj(balF0,balF1,Circles[i]);
	    }
	    if(Distance(jobbF0,jobbF1,Circles[i])){
		Proj(jobbF0,jobbF1,Circles[i]);
	    }
	    if(Distance(felF0,felF1,Circles[i])){
		Proj(felF0,felF1,Circles[i]);
	    }
	    if(Distance(alF0,alF1,Circles[i])){
		Proj(alF0,alF1,Circles[i]);
	    }
	    if((A.x == C.x && B.y == D.y) || (A.x == D.x && B.y == C.y)){
	  	  if(Distance(A,B,Circles[i])){
			Proj(A,B,Circles[i]);
	 	  }
	    }else{
		if(Distance(A,B,Circles[i])){
		    Proj(A,B,Circles[i]);
	  	}
	  	if(Distance(C,D,Circles[i])){
		    Proj(C,D,Circles[i]);
	 	}
	    }
	}
	glutTimerFunc( 5, update, 0 );
}


void Display (void)
{	
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1, 0.0, 0.0);
	
	drawDots();
	glColor3f (0.0, 0.0, 1);
	
	for(GLint i = 0; i < current ; i++){		
		circle(Circles[i], Radius);
		//Circles[i].x+=Circles[i].vx;
		//Circles[i].y+=Circles[i].vy;
	}	

    keyOperations();

    glColor3f (0.0, 1, 0.0);
    glBegin (GL_LINES);
        glVertex2f (A.x, A.y);
        glVertex2f (B.x, B.y);
    glEnd ( );
    glBegin (GL_LINES);
        glVertex2f (C.x, C.y);
        glVertex2f (D.x, D.y);
    glEnd ( );	

    glutSwapBuffers( );
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("elso");
    init ( );
    glutDisplayFunc (Display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc( processMouse );
    glutTimerFunc( 5, update, 0 );
    glutMainLoop ( );
    return 0;
}
