#include <GL/glut.h>

#define ARVORE 15

GLUquadricObj *obj;

float arvEsquerda, arvDireita;
float angX = 45;
float angY = 0;
float raioCorpo = 0.7, raioMembros=0.2, raioBastao=0.1;
float trx = 0;
float try = 20;
int arvores = 10; //Quantidade de`árvores na cena
int v[ARVORE][4]; //Vetor de posições das árvores ***Linha = quantidade de árvores, Coluna = X e Y

int i = 0, cont, distancia = 70, tam = ARVORE, pontuacao = 0;
float ystep = 3, resolucao = 40, x1 = 40, y1 = 40, a;
float pos[ARVORE];

//Pontuação
GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

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

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glOrtho(-resolucao,resolucao,-resolucao,resolucao,-resolucao,resolucao);
    glPushMatrix();
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj,GLU_SMOOTH);

    //lighting();
}
//Detecta colisão
int colisao(float personagemX, float personagemY, float obstaculoX, float obstaculoY, float obstaculoX_2, float obstaculoY_2,
            float obstaculoRaio, float ajustaRaio)
{

    obstaculoRaio *= ajustaRaio; //Ajusta o raio de colisão
    float meioObstaculoRaio = obstaculoRaio/2;
    float quintoObstaculoRaio = obstaculoRaio/5;

    if(personagemY >= obstaculoY-obstaculoRaio && personagemY <= obstaculoY+obstaculoRaio &&
            personagemX >= obstaculoX-meioObstaculoRaio && personagemX <= obstaculoX+meioObstaculoRaio ||
            personagemY >= obstaculoY_2-obstaculoRaio && personagemY <= obstaculoY_2+obstaculoRaio &&
            personagemX >= obstaculoX_2-meioObstaculoRaio && personagemX <= obstaculoX_2+meioObstaculoRaio)
    {

        //printf("X\tY\n%.2f\t%.2f\n%.2f\t%.2f\n\n", personagemX, personagemY, obstaculoX, obstaculoY);

        if(personagemX >= obstaculoX-meioObstaculoRaio && personagemX <= obstaculoX+meioObstaculoRaio)
        {
            //printf("\nÁrvore Esquerda\n");
            trx -= 5; /// Caso haja colisão com a árvore esquerda, desloca o personagem 5 u.c. pra esquerda, se não ele passa dentro da árvore
            try += 3;
            vira(1);
        }
        else
        {
            if(personagemX >= obstaculoX_2-meioObstaculoRaio && personagemX <= obstaculoX_2+meioObstaculoRaio)
            {
                //printf("Árvore Direita\n");
                trx += 5; /// Caso haja colisão com a árvore direita, desloca o personagem 5 u.c. pra direita, se não ele passa dentro da árvore
                try += 3;
                vira(1);
            }
        }
    }
    else  ///Se não tiver colisão, checa se teve pontuação
    {
        if((personagemX > obstaculoX && personagemX < obstaculoX_2) && (personagemY <= obstaculoY && personagemY >= obstaculoY-2))
        {
            pontuacao++;
            //printf("\nPontuação: %d\n", pontuacao);
        }
    }
}

void arvore()
{
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

void coloca_arvores(int n_arvores)
{
    srand(5);

    while(i < n_arvores)
    {
        a = (rand() % 60 ) - 35;
        pos[i] = a;
        //printf("pos[%d]: %.1f\n", i, pos[i]);
        i++;
    }

    for(cont = 0; cont < n_arvores; cont++)
    {
        glPushMatrix();
        glTranslatef(pos[cont], y1 - (cont)*distancia, 0);
        arvore();
        v[cont][0] = pos[cont];
        v[cont][1] = y1 - (cont)*distancia;
        glPopMatrix();
        glPushMatrix();
        glTranslatef(pos[cont] + 15, y1 - (cont)*distancia, 0);
        arvore();
        v[cont][2] = pos[cont] + 15;
        v[cont][3] = y1 - (cont)*distancia;
        glPopMatrix();

        if(cont == (n_arvores-1)){
            glPushMatrix();
            glTranslatef(0,y1 - (cont+1) * distancia,-1);
            glLineWidth(3);
            glColor3f(1,0,0);
            glBegin(GL_LINES);
            glVertex2f(-40,0);
            glVertex2f(40,0);
            glEnd();
            glPopMatrix();
        }

        if(try < y1 - (ARVORE+0.2)* distancia){
            ystep-=0.5;
        }
    }

    glutPostRedisplay();
}

/*void lighting() {
    float light1_pos[] = {2.0f, 0.0f, 2.0f, 1.0f}; //fonte local

    float white[] = {1.0f,1.0f,1.0f,1.0f};
    float black[] = {0.0f,0.0f,0.0f,1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light1_pos); //dene posição da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, black); //contribuição ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white); //contribuição difusa
    glLightfv(GL_LIGHT0, GL_SPECULAR, white); //contribuição especular

    //Atenuacao
    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f); //a0
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f); //a1
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f); //a2

    //Fonte de Luz Direcional - Holofote
    //float position1[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    //glLightfv(GL_LIGHT1, GL_POSITION, position1);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    //float direction[] = {1.0f, 0.0f, 0.0f};
    //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction); //vetor direção
    //glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f); //espalhamento angular
    //glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f); //atenuação angular

    //Parâmetros definidos globalmente
    //Nível de brilho ambiente
    //float global_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //Reflexao especular - vetor de visão
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    //Cálculo da iluminação para faces traseiras e frontais
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}*/

void scoredisplay (int sx, int sy, int sz, int space_char, int pont)
{
        glColor3f(1,0,0);
        int j=0,p,k;

        p = pont;
        j = 0;
        k = 0;
        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((sx-(j*space_char)),sy, sz);
            glutBitmapCharacter(font_style1,48+k);
            j++;
            p /= 10;
        }
            glRasterPos3f ((sx-(j*space_char)), sy, sz);
            glutBitmapCharacter(font_style1,48+p);

}

void output(int x, int y, char *string)
{
    glColor3f(1,0,0);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font_style1, string[i]);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    output(resolucao-20, resolucao-5, "Score: ");
    scoredisplay(resolucao-5, resolucao-5, resolucao, 2, pontuacao);

    /// Posiciona as árvores na cena
    coloca_arvores(tam);

    /// Laço para verificar se está perto de alguma árvore
    for(int i = 0; i < tam; i++)
    {
        //printf("%d\n", i);
        colisao(trx, try, v[i][0], v[i][1], v[i][2], v[i][3], 10, 0.8);
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
    glutSolidSphere(0.22,100,100); /// ///bumbum tam tam
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

void scenarioTimerFunc(int value)
{
    y1 += ystep;

    glutPostRedisplay();
    if(ystep > 0)
        glutTimerFunc(1, scenarioTimerFunc, 1);
    else
        angY = 45;
}

void charAndarTimerFunc(){
    trx += vel;
    if(trx <= -resolucao+3 || trx >= resolucao-3)
        vel = 0;
    glutTimerFunc(1, charAndarTimerFunc, 1);

    if(try > 20)
        try-=0.5;
    if(trx > 38)
        trx-=0.5;
    else if (trx < -38)
        trx+=0.5;
}

void agaixar(int value)
{
    int i, aux = 0;

    if(aux == 0)
    {
        corpo+=0.25;
        perna-=4;
        joelho+=5;
        esqui-=2;
    }
    if(perna == 30)
    {
        aux = 1;
    }

    /// Redesenha a cena com as novas coordenadas
    glutPostRedisplay();

    if(aux == 0)
        glutTimerFunc(10, agaixar, 1);
}

void charTimerFunc(int value)
{
    if(flag == 0)
    {
        ombro+=12;
        antebraco+=10;
    }
    else if (flag == 1)
    {
        ombro-=12;
        antebraco-=10;
    }

    if (ombro == 48)
    {
        flag = 1;
        flag2++;
    }

    else if(ombro == -48)
    {
        flag = 0;
    }

    // Redesenha a cena com as novas coordenadas
    glutPostRedisplay();

    if(flag2 == 3)
        glutTimerFunc(10,agaixar,1);
    else
        glutTimerFunc(10,charTimerFunc, 1);
}
/*
void transformacoes(int key, int x, int y)
{
    switch (key)
    {
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
*/
void vira(int direcao){ ///1 frente, 2 esquerda, 3 direita
    switch(direcao){
    case 1:
        angY = 0;
        vel = 0;
        break;
    case 2:
        angY = -22.5;
        if(vel >= 0)
        {
            vel = velEsq;
        }
        break;
    case 3:
        angY = 22.5;
        if(vel <= 0)
        {
            vel = velDir;
        }
        break;
    }
}

void movimentos(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a' :
    case 'A' :
        //Vira para esquerda
        vira(2);
        break;
    case 'D' :
    case 'd' :
        //Vira para direita
        vira(3);
        break ;
    case 'S' :
    case 's' :
        //Vira para frente
        vira(1);
    default:
        break ;
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
    //glutSpecialFunc(transformacoes);
    glutKeyboardFunc(movimentos);
    glutTimerFunc(1, scenarioTimerFunc, 1);
    glutTimerFunc(10, charTimerFunc, 1);
    glutTimerFunc(1, charAndarTimerFunc, 1);
    init();
    glutMainLoop();
}
