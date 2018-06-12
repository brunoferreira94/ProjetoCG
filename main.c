#include <GL/glut.h>

GLUquadricObj *obj;

float angX = 45;
float angY = 0;
float raioCorpo = 0.7, raioMembros=0.2, raioBastao=0.1, resolucao = 25, tam = 10;
float trx = 0;
float try = 0;
int arvores = 10; //Quantidade de`árvores na cena
int v[10][2]; //Vetor de posições das árvores ***Linha = quantidade de árvores, Coluna = X e Y

void init(){
     glClearColor(1.0,1.0,1.0,1.0);
     glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-resolucao,resolucao,-resolucao,resolucao,-resolucao,resolucao);
     glPushMatrix();
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_SMOOTH);
}
//Detecta colisão
int colisao(float personagemX, float personagemY, float obstaculoX, float obstaculoY, float obstaculoRaio, float ajustaRaio){
    obstaculoRaio *= ajustaRaio; //Ajusta o raio de colisão
    if(personagemX >= obstaculoX-obstaculoRaio/2 && personagemX <= obstaculoX+obstaculoRaio/2 &&
        personagemY >= obstaculoY-obstaculoRaio && personagemY <= obstaculoY+obstaculoRaio){
        printf("X\tY\n%.2f\t%.2f\n%.2f\t%.2f\n", personagemX, personagemY, obstaculoX, obstaculoY);
    }
}

void arvore(float tam){
    int x;
    glPushMatrix();

    	//A função 'glutSolidCone' desenha o cone deitado. Como este é pretendido a pé usamos o rotate
    	glRotatef(-45, 1, 0, 0);
		glRotatef(0,1,0,0);

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
        x= 20 - rand()%40;
        y= 20 - rand()%40;

        v[n_arvores-1][0] = x;
        v[n_arvores-1][1] = y;

        //Fazemos um Push para preservar o ponto de origem
        glPushMatrix();
            glTranslatef(x, y, 0); //Translate para a posição pretendida
            arvore(tam);
        glPopMatrix();
        n_arvores--;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    //Posiciona as árvores na cena
    coloca_arvores(arvores);

    //Laço para verificar se está perto de alguma árvore
    for(int i = 0; i < arvores; i++){
        printf("%d\n", i);
        colisao(trx,try,v[i][0],v[i][1],tam, 0.3);
    }

    glColor3f(1.0, 0.85, 0.75);

    glPopMatrix();
    glPushMatrix();
		glTranslatef(trx,try,0);
        glRotatef(angX,1,0,0);
        glRotatef(angY,0,1,0);
        glPushMatrix(); // rosto
            glTranslatef(0,4.1,0);
            glutSolidSphere(1.2,100,100);
			glPushMatrix();
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
            glutSolidSphere(0.2,100,100);
        glPopMatrix();
        glPushMatrix(); // braço direito

            glColor3f(1.0, 0.85, 0.75);
            glRotatef(90,1,0,0);
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
     //printf("AngX: %.2f\tAngY: %.2f", angX, angY);
}

void movimentos(unsigned char key, int x, int y){
	switch (key){
        case 'w' :
		case 'W' :
            try++;
			break;
		case 'a' :
		case 'A' :
            //Vira para esquerda
            angY = 315;
            trx--;
			break;
		case 'D' :
		case 'd' :
            //Vira para direita
            angY = 45;
            trx++;
			break ;
		case 'S' :
		case 's' :
            //Vira para frente
            angY = 0;
            try--;
			break ;
 		default:
           	break ;
	}
	glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Esqui nos Alpes");
     glutDisplayFunc(display);
     glutSpecialFunc(transformacoes);
	 glutKeyboardFunc(movimentos);
     init();
     glutMainLoop();
}
