#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

GLUquadricObj *obj;

float angX = 45;
float angY = 45;
float raioCorpo = 0.7, raioMembros=0.2, raioBastao=0.1;
float trx = 0;
float try = 0;
float ombro = 0;
float antebraco = -90;
float perna = 90;
int flag = 0;

void init(){
     glClearColor(0.0,0.0,0.0,0.0);
     glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7,7,-7,7,-7,7);
     glPushMatrix();
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_SMOOTH);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glColor3f(1.0, 0.85, 0.75);

    glPopMatrix();
    glPushMatrix();
    	glTranslatef(trx,try,0);
        glRotatef(angX,1,0,0);
        glRotatef(angY,0,1,0);
        glPushMatrix(); // rosto
            glTranslatef(0,4.1,0);
            glutSolidSphere(1.2,100,100);
			glPushMatrix(); //olhos
				glColor3f(0,0,1);
				glTranslatef(0.4,0.4,0.8);
				glutSolidSphere(0.3,50,50);
				glTranslatef(-0.8,0,0);
				glutSolidSphere(0.3,50,50);
			glPopMatrix();
        glPopMatrix();
        glPushMatrix(); // corpo
            glColor3f(1.0, 0, 0);
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-3);
            gluDisk(obj,0,raioCorpo,100,100);
            gluCylinder(obj, raioCorpo,raioCorpo, 5, 100, 100);
        glPopMatrix();

        glPushMatrix(); // ombro direito
            glTranslatef(.78,2.5,0);
            glRotatef(ombro,1,0,0);
            glutSolidSphere(0.2,100,100);

            glPushMatrix(); // braço direito

                glColor3f(1.0, 0.85, 0.75);
                glRotatef(90,2,0,0);

                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

                glPushMatrix(); //antebraço direito
                    glTranslatef(0,0,1.6);
                    glRotatef(antebraco,1,0,0);
                    glutSolidSphere(0.2,100,100); ///cotovelo
                    gluDisk(obj,0,raioMembros,100,100);
                    gluCylinder(obj, raioMembros, raioMembros, 1, 100, 100);

                    glPushMatrix(); // mao direita
                        glColor3f(0,0,1);
                        glTranslatef(0,0,1);
                        glutSolidSphere(0.3,100,100);

                        glColor3f(0.5,0.5,0.5);
                        glRotatef(90,1,0,0);
                        glTranslatef(0,0,-2.5);
                        gluDisk(obj,0,raioBastao,100,100);
                        gluCylinder(obj, raioBastao, raioBastao, 8, 100, 100);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix(); // ombro esquerdo
            glColor3f(1,0,0);
            glTranslatef(-.78,2.5,0);
            glRotatef(ombro,1,0,0);
            glutSolidSphere(0.2,100,100);

            glPushMatrix(); // braço esquerdo

                glColor3f(1.0, 0.85, 0.75);
                glRotatef(90,1,0,0);
                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

                glPushMatrix(); //antebraço esquerdo
                    glTranslatef(0,0,1.6);
                    glRotatef(antebraco,1,0,0);
                    glutSolidSphere(0.2,100,100); ///cotovelo
                    gluDisk(obj,0,raioMembros,100,100);
                    gluCylinder(obj, raioMembros, raioMembros, 1, 100, 100);

                    glPushMatrix(); // mao esquerda
                        glColor3f(0,0,1);
                        glTranslatef(0,0,1);
                        glutSolidSphere(0.3,100,100);

                        glColor3f(0.5,0.5,0.5);
                        glRotatef(90,1,0,0);
                        glTranslatef(0,0,-2.5);
                        gluDisk(obj,0,raioBastao,100,100);
                        gluCylinder(obj, raioBastao, raioBastao, 8, 100, 100);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(0.4,-1.9,0);
            glutSolidSphere(0.22,100,100); ///bumbum tam
            glPushMatrix(); //perna direita
                glColor3f(1.0, 0.85, 0.75);
                glRotatef(perna,1,0,0);
                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

                glPushMatrix();
                    glTranslatef(0,0,1.5);
                    glutSolidSphere(0.22,100,100); ///joelho

                    gluDisk(obj,0,raioMembros,100,100);
                    gluCylinder(obj, raioMembros, raioMembros, 1.4, 100, 100);

                    glPushMatrix();
                        glTranslatef(0,0,1.4);
                        glColor3f(0,0,1);
                        glutSolidSphere(0.3,100,100); // pe

                        glColor3f(0.5,0.5,0.5);

                        glRotatef(90,1,0,0);
                        glTranslatef(0,0.25,0);
                        glScalef(1,0.2,10);
                        glutSolidSphere(0.35,100,100); // esqui
                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(-0.4,-1.9,0);
            glutSolidSphere(0.22,100,100); /// ///bumbum tam tam
            glPushMatrix(); //perna esquerda
                glColor3f(1.0, 0.85, 0.75);
                glRotatef(90,1,0,0);
                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

                glTranslatef(0,0,1.5);
                glutSolidSphere(0.22,100,100); ///joelho

                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.4, 100, 100);

                glPushMatrix();
                    glTranslatef(0,0,1.4);
                    glColor3f(0,0,1);
                    glutSolidSphere(0.3,100,100); /// pe

                    glColor3f(0.5,0.5,0.5);

                    glRotatef(90,1,0,0);
                    glTranslatef(0,0.25,0);
                    glScalef(1,0.2,10);
                    glutSolidSphere(0.35,100,100); /// esqui
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=15;
           break ;
        default:
           	break ;
     }
     glutPostRedisplay() ;
}


void agaixar(int value)
{
	int i, aux = 0;
	if(aux == 0)
    	perna-=2;
	if(perna == 60)
		aux = 1;

	// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();

	if(aux == 0)
		glutTimerFunc(10,agaixar, 1);
}

void movimentos(unsigned char key, int x, int y){
	switch (key){
		case 'a' :
		case 'A' :
			trx-=1;
			try-=1;
			break;
		case 'D' :
		case 'd' :
			trx+=1;
			try+=1;
			break ;
        case 's' :
        case 'S' :
            glutTimerFunc(10,agaixar,1);
 		default:
           	break ;
	}
	glutPostRedisplay() ;
}

void timerFunc(int value)
{

    if(flag == 0){
        ombro+=3;
        antebraco+=2.5;
    }
    else if (flag == 1){
        ombro-=3;
        antebraco-=2.5;
    }

    if (ombro == 45)
        flag = 1;
    else if(ombro == -45)

        flag = 0;

	// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();
	glutTimerFunc(10,timerFunc, 1);
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Primeiro esboço - Personagem Esqui nos Alpes");
     glutDisplayFunc(display);
     glutSpecialFunc(transformacoes);
	 glutKeyboardFunc(movimentos);
     glutTimerFunc(10,timerFunc,1);
     init();
     glutMainLoop();
}

