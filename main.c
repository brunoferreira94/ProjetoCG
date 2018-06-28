#include <GL/glut.h>

GLUquadricObj *obj;

float angX = 45;
float angY = 0;
float raioCorpo = 0.7, raioMembros=0.2, raioBastao=0.1;
float trx = 0;
float try = 0;
int arvores = 30; //Quantidade de`árvores na cena
int v[30][2]; //Vetor de posições das árvores ***Linha = quantidade de árvores, Coluna = X e Y

int i = 0, cont, distancia = 70, tam = 30;
float ystep = 2, resolucao = 40, x1 = 40, y1 = 40, a;
float pos[15];

//Variáveis de animação
float ombro = 0;
float antebraco = -90;
float perna = 90;
float joelho = 0;
float esqui = 90;
float corpo = 0;
int flag = 0;
int flag2 = 0;
float vel = 0, velEsq = -2.5, velDir = 2.5;

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
    int metadeRaio = obstaculoRaio/2;

    if(personagemY >= obstaculoY-obstaculoRaio && personagemY <= obstaculoY+obstaculoRaio &&
        personagemX >= obstaculoX-metadeRaio && personagemX <= obstaculoX+metadeRaio){
        printf("X\tY\n%.2f\t%.2f\n%.2f\t%.2f\n\n", personagemX, personagemY, obstaculoX, obstaculoY);
    }
}

void arvore(){
    glPushMatrix();

    	///A função 'glutSolidCone' desenha o cone deitado. Como este é pretendido a pé usamos o rotate
    	glRotatef(-45, 1, 0, 0);
    	glColor3f(0.7, 0.3, 0); /// cor do tronco: marrom
    	glutSolidCone(1, 10, 100, 100); /// desenha o cone

    	glTranslatef(0, 0, 2.5);
        glColor3f(0.0, 0.6, 0.2);
    	glutSolidCone(2.5, 7.5, 100, 100);

    glPopMatrix();

}

void coloca_arvores(int n_arvores){
    srand(5);

    while(i < (n_arvores/2)){
        a = (rand() % 60 ) - 35;
        pos[i] = a;
        printf("pos[%d]: %.1f\n", i, pos[i]);
        i++;
    }

    for(cont = 0; cont < (n_arvores/2); cont++){
            glPushMatrix();
                glTranslatef(pos[cont], y1 - (cont)*distancia, 0);
                arvore();
                v[cont][0] = pos[cont];
                v[cont][1] = y1 - (cont)*distancia;
            glPopMatrix();
            glPushMatrix();
                glTranslatef(pos[cont] + 15, y1 - (cont)*distancia, 0);
                arvore();
                v[cont+15][0] = pos[cont] + 15;
                v[cont+15][1] = y1 - (cont)*distancia;
            glPopMatrix();

    }

    /*int x,y;
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
    }*/
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    /// Posiciona as árvores na cena
    coloca_arvores(tam);

    /// Laço para verificar se está perto de alguma árvore
    for(int i = 0; i < tam; i++){
        //printf("%d\n", i);
        colisao(trx,try,v[i][0],v[i][1], 10, 0.3);
    }

    glColor3f(1.0, 0.85, 0.75);

    glPopMatrix();

    glPushMatrix();
    	glTranslatef(trx,try,0);

        glRotatef(corpo,1,0,0);
        //glRotatef(corpo/2,0,1,0);
        //glRotatef(corpo/2,1,0,0);

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

                    glPushMatrix();
                        glRotatef(joelho,1,0,0);
                        gluDisk(obj,0,raioMembros,100,100);
                        gluCylinder(obj, raioMembros, raioMembros, 1.4, 100, 100);

                        glPushMatrix();
                            glTranslatef(0,0,1.4);
                            glColor3f(0,0,1);
                            glutSolidSphere(0.3,100,100); // pe

                            glColor3f(0.5,0.5,0.5);
                            glPushMatrix();
                                glRotatef(esqui,1,0,0);
                                glTranslatef(0,0.25,0);
                                glScalef(1,0.2,10);
                                glutSolidSphere(0.35,100,100); // esqui
                            glPopMatrix();
                         glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glColor3f(1,1,1);
            glTranslatef(-0.4,-1.9,0);
            glutSolidSphere(0.22,100,100); //bumbum tam tam
            glPushMatrix(); //perna esquerda
                glColor3f(1.0, 0.85, 0.75);
                glRotatef(perna,1,0,0);
                gluDisk(obj,0,raioMembros,100,100);
                gluCylinder(obj, raioMembros, raioMembros, 1.5, 100, 100);

                glPushMatrix();
                    glTranslatef(0,0,1.5);
                    glutSolidSphere(0.22,100,100); ///joelho

                    glPushMatrix();
                        glRotatef(joelho,1,0,0);
                        gluDisk(obj,0,raioMembros,100,100); ///panturrilha
                        gluCylinder(obj, raioMembros, raioMembros, 1.4, 100, 100);

                        glPushMatrix();
                            glTranslatef(0,0,1.4);
                            glColor3f(0,0,1);
                            glutSolidSphere(0.3,100,100); /// pe

                            glColor3f(0.5,0.5,0.5);
                            glPushMatrix();
                                glRotatef(esqui,1,0,0);
                                glTranslatef(0,0.25,0);
                                glScalef(1,0.2,10);
                                glutSolidSphere(0.35,100,100); /// esqui
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void scenarioTimerFunc(int value){
    y1 += ystep;

    glutPostRedisplay();
    glutTimerFunc(10, scenarioTimerFunc, 1);
}

void agaixar(int value){
	int i, aux = 0;

	if(aux == 0){
        corpo+=0.25;
    	perna-=4;
        joelho+=5;
        esqui-=2;
    }
	if(perna == 30){
		aux = 1;
    }

	/// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();

	if(aux == 0)
		glutTimerFunc(10, agaixar, 1);
}

void charTimerFunc(int value)
{
    if(flag == 0){
        ombro+=12;
        antebraco+=10;
    }
    else if (flag == 1){
        ombro-=12;
        antebraco-=10;
    }

    if (ombro == 48){
        flag = 1;
        flag2++;
    }

    else if(ombro == -48){
        flag = 0;
    }
	// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();

    if(flag2 == 3)
        glutTimerFunc(10,agaixar,1);
    else
	    glutTimerFunc(10,charTimerFunc, 1);
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
            try+=1.5;
			break;
		case 'a' :
		case 'A' :
            //Vira para esquerda
            angY = -22.5;
            if(vel > 0){
                vel = velEsq;
            }
			break;
		case 'D' :
		case 'd' :
            //Vira para direita
            angY = 22.5;
            if(vel < 0){
                vel = velDir;
            }
			break ;
		case 'S' :
		case 's' :
            //Vira para frente
            angY = 0;
            vel = 0;
			break ;
        case 'x' :
        case 'X' :
            glutTimerFunc(10, charTimerFunc, 1);
 		default:
           	break;
	}

	glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50, 100);
     glutInitWindowSize(600, 600);
     glutCreateWindow("Esqui nos Alpes");
     glutDisplayFunc(display);
     glutSpecialFunc(transformacoes);
	 glutKeyboardFunc(movimentos);
	 glutTimerFunc(10, scenarioTimerFunc, 1);
	 glutTimerFunc(10, charTimerFunc, 1);
     init();
     glutMainLoop();
}
