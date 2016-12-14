#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <time.h>
#include <vector>
#include <list>

GLsizei winWidth = 800, winHeight = 600;
typedef struct point2d {GLdouble x, y ;} POINT2D;
typedef struct point2dh {GLdouble x, y, z ;} POINT2DH;
std::vector<POINT2DH> body, leftEye,rightEye,chunk,mouth,leftTooth,rightTooth;


POINT2D initPoint2d(GLdouble x, GLdouble y){
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

POINT2DH initPoint2dh(GLdouble x, GLdouble y){
	POINT2DH P;
	P.x = x;
	P.y = y;
	P.z = 1;
	return P;
}

void init( ) {
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
    glShadeModel( GL_FLAT );
    glPointSize( 6.0 );
    glLineWidth( 5.0 );
    glLineStipple(1, 0xFF00);
}

class Pumpkin{
public:
	Pumpkin(){
	A = initPoint2dh(0, 0.512); body.push_back(A); chunk.push_back(A);
	B = initPoint2dh(0.454, 0.565); body.push_back(B);
	C = initPoint2dh(0.815, 0.33); body.push_back(C);
	C_1 = initPoint2dh(-0.182, 0.681); chunk.push_back(C_1);
	D = initPoint2dh(0.907, -0.313); body.push_back(D);
	D_1 = initPoint2dh(-0.063, 0.717);chunk.push_back(D_1);
	E = initPoint2dh(0.411, -0.7); body.push_back(E);
	E_1 = initPoint2dh(-0.202, -0.514); leftTooth.push_back(E_1);
	F = initPoint2dh(0, -0.7); body.push_back(F);
	F_1 = initPoint2dh(-0.069, -0.518); leftTooth.push_back(F_1);
	G = initPoint2dh(-0.411, -0.7); body.push_back(G);
	G_1 = initPoint2dh(-0.069, -0.395); leftTooth.push_back(G_1);
	H = initPoint2dh(-0.907, -0.313); body.push_back(H);
	H_1 = initPoint2dh(-0.2, -0.4); leftTooth.push_back(H_1);
	I = initPoint2dh(-0.815, 0.33); body.push_back(I);
	J = initPoint2dh(-0.454, 0.565); body.push_back(J);
	K = initPoint2dh(-0.473, 0.045); leftEye.push_back(K);
	L = initPoint2dh(-0.155, 0.028); leftEye.push_back(L);
	M = initPoint2dh(-0.208, 0.32); leftEye.push_back(M);
	N = initPoint2dh(0.196, 0.038); rightEye.push_back(N);
	O = initPoint2dh(0.52, 0.055); rightEye.push_back(O);
	P = initPoint2dh(0.312, 0.356); rightEye.push_back(P);
	Q = initPoint2dh(-0.519, -0.226); mouth.push_back(Q);
	R = initPoint2dh(0.59, -0.13); mouth.push_back(R);
	S = initPoint2dh(0.474, -0.505); mouth.push_back(S);
	T = initPoint2dh(-0.324, -0.524); mouth.push_back(T);
	U = initPoint2dh(0.358, -0.151); rightTooth.push_back(U);
	V = initPoint2dh(0.196, -0.165); rightTooth.push_back(V);
	W = initPoint2dh(0.216, -0.286); rightTooth.push_back(W);
	Z = initPoint2dh(0.374, -0.269); rightTooth.push_back(Z);
	
	nagyitas = rand() % 90 + 10;
	szog = rand() % 359 + 1;
	szog = szog * 0.0174532925;

	eltolasx = rand() % (int)(winWidth - (2 * nagyitas)) + nagyitas;
	eltolasy = rand() % (int)(winHeight - (2 * nagyitas)) + nagyitas;

	createMMatrix();
	createTMatrix();
	createNMatrix();
	createFMatrix();
	createEMatrix();
	
	mul_matrices(nagyit, forgat, transzform);
	mul_matrices(tukroz, transzform, temp);
	mul_matrices(eltol, temp, transzform);	
	
	}	
	
	POINT2DH transzf(GLfloat m[][3], POINT2DH P){
	    POINT2DH q;
	    q.x=m[0][0]*P.x + m[0][1]*P.y + m[0][2]*P.z;
	    q.y=m[1][0]*P.x + m[1][1]*P.y + m[1][2]*P.z;
	    q.z=m[2][0]*P.x + m[2][1]*P.y + m[2][2]*P.z;
	    return q;
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
	
	void createNMatrix(){
		for(int i = 0; i<3 ; i++){
			for(int j = 0; j<3 ; j++){
				nagyit[i][j]=0;
			}
		}
		nagyit[0][0]=nagyitas;
		nagyit[1][1]=nagyitas;
		nagyit[2][2]=1;
	}

	void createFMatrix(){
		for(int i = 0; i<3 ; i++){
			for(int j = 0; j<3 ; j++){
				forgat[i][j]=0;
			}
		}
		forgat[0][0]= cos(szog);
		forgat[0][1]= -sin(szog);
		forgat[1][0]= sin(szog);
		forgat[1][1]= cos(szog);
		forgat[2][2]= 1;
	}

	void createTMatrix(){
		for(int i = 0; i<3 ; i++){
			for(int j = 0; j<3 ; j++){
				eltol[i][j]=0;
			}
		}
		eltol[0][0]=1;
		eltol[0][2]=eltolasx;
		eltol[1][1]=1;
		eltol[1][2]=eltolasy;
		eltol[2][2]=1;
	}

	void createMMatrix(){
		for(int i = 0; i<3 ; i++){
			for(int j = 0; j<3 ; j++){
				transzform[i][j]=0;
			}
		}
	}
	
	void createEMatrix(){
		int a = rand() % 3;
		switch(a){
			case(0):{for(int i = 0; i<3 ; i++){
					for(int j = 0; j<3 ; j++){
						tukroz[i][j]=0;
					}
				}
				tukroz[0][0]=1;
				tukroz[1][1]=1;
				tukroz[2][2]=1;
			}break;
			case(1):{for(int i = 0; i<3 ; i++){
					for(int j = 0; j<3 ; j++){
						tukroz[i][j]=0;
					}
				}
				tukroz[0][0]=-1;
				tukroz[1][1]=1;
				tukroz[2][2]=1;
			}break;	
			case(2):{for(int i = 0; i<3 ; i++){
					for(int j = 0; j<3 ; j++){
						tukroz[i][j]=0;
					}
				}
				tukroz[0][0]=1;
				tukroz[1][1]=-1;
				tukroz[2][2]=1;
			}
			break;
		}
	}

	void draw(){
		glColor3f(1.0,0.5,0.0);
		glBegin(GL_POLYGON);
			for(auto it = body.begin(); it != body.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}		
		glEnd();

		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POLYGON);
			for(auto it = leftEye.begin(); it != leftEye.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}		
		glEnd();

		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POLYGON);
			for(auto it = rightEye.begin(); it != rightEye.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}		
		glEnd();
	
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POLYGON);
			for(auto it = mouth.begin(); it != mouth.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}
		glEnd();

		glColor3f(1.0,0.5,0.0);
		glBegin(GL_POLYGON);
			for(auto it = leftTooth.begin(); it != leftTooth.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}		
		glEnd();

		glColor3f(1.0,0.5,0.0);
		glBegin(GL_POLYGON);
			for(auto it = rightTooth.begin(); it != rightTooth.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}
		glEnd();
		
		glColor3f(1.0,0.5,0.0);
		glBegin(GL_POLYGON);
			for(auto it = chunk.begin(); it != chunk.end(); it++){
				glVertex2d(getPoint2D((transzf(transzform, (*it)))).x,getPoint2D((transzf(transzform, (*it)))).y);
			}
		glEnd();
		
	}

	POINT2D getPoint2D(POINT2DH a){
		POINT2D b = initPoint2d((a.x/a.z),(a.y/a.z));
		return b;
	}
	
private:
	
	POINT2DH A, B, C, C_1, D, D_1, E, E_1, F, F_1, G, G_1, H, H_1, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, Z;
	GLfloat nagyit[3][3], forgat[3][3], eltol[3][3], tukroz[3][3], transzform[3][3], temp[3][3];
	GLfloat nagyitas, szog, eltolasx, eltolasy;
	std::vector<POINT2DH> body, mouth, leftEye, rightEye, leftTooth, rightTooth, chunk;
	
	
};
	std::list<Pumpkin> Pumpkins;

void update(int n){
	Pumpkin current;
	Pumpkins.push_back(current);

	glutPostRedisplay();
	glutTimerFunc(1000, update, 0);
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(auto it = Pumpkins.begin(); it != Pumpkins.end() ; it ++){
		(*it).draw();
	}

	glutSwapBuffers();
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("harmadik");
    init ( );
        glutDisplayFunc (Display);
    glutTimerFunc(1000, update, 0);

    glutMainLoop ( );
    return 0;
}
