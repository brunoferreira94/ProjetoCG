#include <GL/glut.h>

GLUquadricObj *obj;

float angX = 0;
float angY = 0;
float raioCorpo = 0.7, raioMembros=0.2, raioBastao=0.1,
resolucao = 30, tam = 3;
int angBracoPersonagem = 90, levantaBraco = 1;

void init(){
     glClearColor(1.0,1.0,1.0,1.0);
     glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0.0, -1.0, 0.0,   //posição da câmera (P_0)
              1.0, 1.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
     glOrtho(-resolucao,resolucao,-resolucao,resolucao,-resolucao,resolucao);
     glPushMatrix();
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_SMOOTH);
}

void arvore(float tam){
    int x;
    glPushMatrix();
    //A função 'glutSolidCone' desenha o cone deitado. Como este é pretendido a pé usamos o rotate
    glRotatef(-90, 1, 0, 0);

    glColor3f(0.7, 0.3, 0);
    glutSolidCone(0.1*tam, tam, 20, 10);

    glTranslatef(0, 0, 0.25*tam);

    x=rand()%2;
    switch (x) {
        case 0:
            glColor3f(0, 0.5, 0);
            break;

        case 1:
            glColor3f(0.0, 0.6, 0.2);
            break;

        default:
            break;
    }

    glutSolidCone(0.25*tam, 0.75*tam, 20, 10);

    glPopMatrix();

}

void coloca_arvores(int n_arvores){
    int x,y;
    srand(4); //Inicia a sequência aleatória para ser sempre a mesma a sequência a ser gerada
    while (n_arvores>0) {
        x=rand()%10;
        y=rand()%10;

        //Fazemos um Push para preservar o ponto de origem
        glPushMatrix();
            glTranslatef(x, y, 0); //Translate para a posição pretendida
            arvore(tam);
        glPopMatrix();
        n_arvores--;
    }
}

void timerFunc(int value)
{
	if(levantaBraco){
        angBracoPersonagem--;
        if (angBracoPersonagem <= 1)
            levantaBraco = 0;
	}

    else{
        angBracoPersonagem++;
        if(angBracoPersonagem >= 90)
            levantaBraco = 1;
    }

	// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();
	glutTimerFunc(value,timerFunc, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    coloca_arvores(2);

    glColor3f(1.0, 0.85, 0.75);

    glPopMatrix();
    glPushMatrix();
        glRotatef(angX,1,0,0);
        glRotatef(angY,0,1,0);
        glPushMatrix(); // rosto
            glTranslatef(0,4.1,0);
            glutSolidSphere(1.2,100,100);
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
            glutSolidSphere(0.2,100,100);
        glPopMatrix();
        glPushMatrix(); // braço direito

            glColor3f(1.0, 0.85, 0.75);
            glRotatef(angBracoPersonagem,1,0,0);
            glRotatef(angBracoPersonagem,1,0,0);
            glTranslatef(0.75,0,-2.4);
            gluDisk(obj,0,raioMembros,100,100);
            gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

            glPushMatrix(); //antebraço direito
                glTranslatef(0,0,1.6);
                glRotatef(-90,1,0,0);
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

        glPushMatrix(); // ombro esquerdo
            glColor3f(1,0,0);
            glTranslatef(-.78,2.5,0);
            glutSolidSphere(0.2,100,100);
        glPopMatrix();
        glPushMatrix(); // braço esquerdo

            glColor3f(1.0, 0.85, 0.75);
            glRotatef(90,1,0,0);
            glTranslatef(-0.75,0,-2.4);
            gluDisk(obj,0,raioMembros,100,100);
            gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

            glPushMatrix(); //antebraço esquerdo
                glTranslatef(0,0,1.6);
                glRotatef(-90,1,0,0);
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

        glPushMatrix(); //perna direita
            glColor3f(1.0, 0.85, 0.75);
            glRotatef(90,1,0,0);
            glTranslatef(0.4,0,1.9);
            gluDisk(obj,0,raioMembros,100,100);
            gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

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

        glPushMatrix(); //perna esquerda
            glColor3f(1.0, 0.85, 0.75);
            glRotatef(90,1,0,0);
            glTranslatef(-0.4,0,1.9);
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

    glFlush();
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
           break;
     }
     glutPostRedisplay() ;
     printf("\nAngX: %.2f\tAngY: %.2f\nAngBracoPersonagem: %d\tLevantaBraco: %d",
      angX, angY, angBracoPersonagem, levantaBraco);
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
     glutTimerFunc(10, timerFunc, 1);
     init();
     glutMainLoop();
}
