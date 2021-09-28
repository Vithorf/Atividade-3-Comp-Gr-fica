#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#define XW 1000
#define YW 1000

//estrutura para definir as cores que podem ser alteradas ao decorrer da execução
typedef struct{
	float r;
	float g;
	float b;
	int newColor;
}COLOR;

//cores do objeto, janela e labirinto 
COLOR objectColor,windowColor,mazeColor;

/*
0 - Vermelho
1 - Verde
2 - Azul
3 - Amarelo
4 - Rosa
5 - Azul Bebe
*/

//Banco de cores
float R[] = {1,0,0,1,1,0.67};
float G[] = {0,1,0,0.79,0.79,0.84};
float B[] = {0,0,1,0,0.85,0.9};

//Globais: Xr e Yr: Deslocamento do player; Velocidade: deslocamento por ação; Chance: Vidas; Life: vetor com 3 valores binários para cada vida. 1 * as coordenadas do triangulo, o exibe, 0, o oculta.
float xr = 0, yr = 0;
int velocidade = 10,chance = 3;
int life[]={1,1,1};
 
 //Função que define o contato, retorna 1 para caso haja contato, 0 para caso não haja.
int contact(float x, float y){
	if(x < 10 && y>100 && y<210 ||
	x>60 &&  y>100 && y<210 ||
	x>-440 && y>240 && y<350 ||
	x<260 && y>380 && y<490 ||
	x>310 && y>380 && y<490 ||
	x<460 && y>520 && y<630 ||
	x<-190 && y>660 && y<770 ||
	x>-140 && y>660 && y<770 ||
	x<-290 && y>800 && y<910 ||
	x>-240 && y>800 && y<910
	)
		return 1;
	else
		return 0;
	
}

void mouseEscape( int button, int state, int x, int y ){
//função que altera as cores a partir do clique do botão esquerdo do mouse.
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    if(objectColor.newColor<5)
    	objectColor.newColor++;
	else
		objectColor.newColor = 0;
		
	//procedimento para garantir que nenhuma cor irá se repetir
	windowColor.newColor = objectColor.newColor == 5 ? 0 : objectColor.newColor + 1; 
	mazeColor.newColor = windowColor.newColor == 5 ? 0 : windowColor.newColor + 1;
	
	//aplicação das cores na estrutura do objeto
   	objectColor.r = R[objectColor.newColor];
    objectColor.g = G[objectColor.newColor];
    objectColor.b = B[objectColor.newColor];
    
    //aplicação das cores na estrutura da janela
    windowColor.r = R[windowColor.newColor];
    windowColor.g = G[windowColor.newColor];
    windowColor.b = B[windowColor.newColor];
    
    //aplicação das cores na estrutura do labirinto
    mazeColor.r = R[mazeColor.newColor];
    mazeColor.g = G[mazeColor.newColor];
    mazeColor.b = B[mazeColor.newColor];
    
    glutPostRedisplay();
	}
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Labirinto
    glColor3f(mazeColor.r,mazeColor.g,mazeColor.b); //aplicação da cor da estrutura 
    glBegin(GL_QUADS);
		glVertex2f(0,210);
		glVertex2f(0,220);
		glVertex2f(500,220);
		glVertex2f(500,210);
    glEnd();
    
    glBegin(GL_QUADS);
		glVertex2f(1100,210);
		glVertex2f(1100,220);
		glVertex2f(650,220);
		glVertex2f(650,210);
    glEnd();
    
    glBegin(GL_QUADS);
		glVertex2f(1100,350);
		glVertex2f(1100,360);
		glVertex2f(150,360);
		glVertex2f(150,350);
    glEnd();
    
    glBegin(GL_QUADS);
		glVertex2f(0,490);
		glVertex2f(0,500);
		glVertex2f(750,500);
		glVertex2f(750,490);
    glEnd();
    
     glBegin(GL_QUADS);
		glVertex2f(1100,490);
		glVertex2f(1100,500);
		glVertex2f(900,500);
		glVertex2f(900,490);
    glEnd();
    
     glBegin(GL_QUADS);
		glVertex2f(0,630);
		glVertex2f(0,640);
		glVertex2f(950,640);
		glVertex2f(950,630);
    glEnd();
    
    glBegin(GL_QUADS);
		glVertex2f(0,770);
		glVertex2f(0,780);
		glVertex2f(300,780);
		glVertex2f(300,770);
    glEnd();
    
    glBegin(GL_QUADS);
		glVertex2f(1100,770);
		glVertex2f(1100,780);
		glVertex2f(450,780);
		glVertex2f(450,770);
    glEnd();
    
     glBegin(GL_QUADS);
		glVertex2f(1100,910);
		glVertex2f(1100,920);
		glVertex2f(350,920);
		glVertex2f(350,910);
    glEnd();
    
     glBegin(GL_QUADS);
		glVertex2f(0,910);
		glVertex2f(0,920);
		glVertex2f(200,920);
		glVertex2f(200,910);
    glEnd();
    
    glClearColor(windowColor.r,windowColor.g,windowColor.b,1);//aplicação da cor da estrutura
    
    //Player
    glColor3f(objectColor.r,objectColor.g,objectColor.b);//aplicação da cor da estrutura

    glBegin(GL_QUADS);
    
    glVertex2f(490+xr,10+yr);
    glVertex2f(490+xr,110+yr);
    glVertex2f(590+xr,110+yr);
    glVertex2f(590+xr,10+yr);
    glEnd();
    
    //Pontos de Vida 
    glBegin(GL_TRIANGLES);
    glVertex2f(20*life[0],1095*life[0]); 
    glVertex2f(5*life[0],1075*life[0]);
    glVertex2f(35*life[0],1075*life[0]);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2f(50*life[1],1095*life[1]);
    glVertex2f(35*life[1],1075*life[1]);
    glVertex2f(65*life[1],1075*life[1]);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2f(80*life[2],1095*life[2]);
    glVertex2f(65*life[2],1075*life[2]);
    glVertex2f(95*life[2],1075*life[2]);
    glEnd();
    
    //chegada
    glBegin(GL_QUADS);
    	glVertex2f(180,920);
		glVertex2f(180,960);
		glVertex2f(370,960);
		glVertex2f(370,920);
    glEnd();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
 
}

void specialkey(int key, int x, int y){
	
    
        switch(key){
        case GLUT_KEY_UP:
        yr+= velocidade;
        break;

        case GLUT_KEY_DOWN:
        yr-= velocidade;
        break;

        case GLUT_KEY_LEFT:
        xr-= velocidade;
        break;

        case GLUT_KEY_RIGHT:
        xr += velocidade;
        break;
        }
        
    //Limites da tela    
    if (xr+490<0){
    	xr = -490;
	}
	if (xr+490>XW){
    	xr = XW-490;
	}
	if(yr-10<0){
		yr = 0;
	}
	 
	if(yr>YW-10){
		yr = YW;
	}
	
	//Contato e criterio de parada ou perda de vida
	if(contact(xr,yr)){
    	xr = yr = 0; //redefinição da posição do jogador
    	chance--; //perda de vida
    	life[chance] = 0; // atribuição do valor 0 na respectiva vida
    	if (!chance){
		
    		if(MessageBox(NULL, "Você não conseguiu! Tentar novamente?", "Poxa!!!", MB_YESNO | MB_ICONASTERISK )==6){ //caixa de mensagem para tentar novamente ou sair
				life[0]=life[1]=life[2]=1; //redefinição das vidas (visualmente)
				xr = yr = 0; //redefinição da posição incial
				chance = 3;} // redefinição das vidas
			else
				exit(0); //saida caso "Não" seja escolhido
	}
	}
	else if (yr==810){ //caso o jogador chege à linha de chegada
		if(MessageBox(NULL, "Você conseguiu!!! Tentar novamente?", "Parabéns!!!", MB_YESNO | MB_ICONASTERISK )==6){
		life[0]=life[1]=life[2]=1;
		xr = yr = 0;
		chance = 3;}
		else
		exit(0);
	}
	
	glutPostRedisplay();
	
	

}

int main(int argc, char** argv){
	
	//atribuições inicias às cores iniciais 
	objectColor.r = R[0];
	objectColor.g = G[0];
	objectColor.b = B[0];
	
	windowColor.r = R[1];
	windowColor.g = G[1];
	windowColor.b = B[1];
	
	mazeColor.r = R[2];
	mazeColor.g = G[2];
	mazeColor.b = B[2];
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(XW,YW);
    glutInitWindowPosition(500,20);
    glutCreateWindow("MAZE GAME - Computação Gráfica");

    glutDisplayFunc(display);
    glutMouseFunc(mouseEscape);

    glClearColor(1,1,1,1);
    gluOrtho2D(0.0,100+XW,0.0,100+YW);
    glutSpecialFunc(specialkey);

    glutMainLoop();
    return 0;
}

