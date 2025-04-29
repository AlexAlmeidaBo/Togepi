#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
int R = 0, G=0, B = 0;


void display(void);
void togepi();
void corpo();
void cabeça();
void rosto();
void drawCircle(float centroX, float centroY, float raio, int numLados);
void drawEllipse(float centroX, float centroY, float raioX, float raioY, int numLados);
void metadeCirculo(float centroX, float centroY, float raioX, float raioY, int numLados);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);


int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (600, 600); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (50, 50); //Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow (argv[0]); //Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.85f, 0.92f, 1.0f, 1.0f); //selecionar cor de fundo (Branco)
  glOrtho (-1, 1,-1, 1, -1 ,1); //define as coordenadas do volume de recorte (clipping volume),
  glutDisplayFunc(display); //Função callback chamada para fazer o desenho
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutSpecialFunc(Special_keyboard); // Registra a função para tratamento das teclas NÂO ASCII
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  printf("\nTestando... \n");
  return 0;
}


void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  togepi();
  glColor3ub (R, G, B);
  glFlush(); 
}


void drawCircle(float centroX, float centroY, float raio, int numLados) {
  float angulo;

  glBegin(GL_POLYGON);
  for (int i = 0; i <= numLados; i++) {
      angulo = 2.0f * PI * i / numLados;
      float x = centroX + cosf(angulo) * raio;
      float y = centroY + sinf(angulo) * raio;
      glVertex2f(x, y);
  }
  glEnd();
}


void drawEllipse(float centroX, float centroY, float raioX, float raioY, int numLados) {
  float angulo;

  glBegin(GL_POLYGON);
  for (int i = 0; i <= numLados; i++) {
      angulo = 2.0f * PI * i / numLados;
      float x = centroX + cosf(angulo) * raioX;
      float y = centroY + sinf(angulo) * raioY;
      glVertex2f(x, y);
  }
  glEnd();
}


void metadeCirculo(float centroX, float centroY, float raioX, float raioY, int numLados){
  float angulo;

  glBegin(GL_POLYGON);
  for (int i = 0; i < numLados; i++) {
      float angulo = PI * i / (numLados - 1); 
      float x = centroX + cos(angulo) * raioX;
      float y = centroY + sin(angulo) * raioY;
      glVertex2f(x, y);
}
  glEnd();
}


void togepi(){
  cabeça();
  rosto();
  corpo();
    
}


void cabeça(){
  glColor3f(1.0, 1.0, 0.6);
  metadeCirculo(0.0,0.0,0.35,0.40, 100);
}


void corpo() {

    glColor3f(1.0, 1.0, 1.0); 
    metadeCirculo(0.0,0.0,0.35,-0.45, 100);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(-0.35, 0.0);
    glVertex2f(-0.34, 0.08);
    glVertex2f(-0.30, 0.00);

    glVertex2f(-0.25, 0.08);
    glVertex2f(-0.18, 0.00);
    glVertex2f(-0.14, 0.08);
    

    glEnd();
}

void rosto() {

  // Olhos (pretos)
  glColor3f(0.0, 0.0, 0.0);
  drawEllipse(-0.1f, 0.3f, 0.02f, 0.05f, 20); // olho esquerdo
  drawEllipse(0.1f, 0.3f, 0.02f, 0.05f, 20);  // olho direito

  // Brilho dos olhos
  glColor3f(1.0, 1.0, 1.0);
  drawEllipse(-0.095f, 0.325f, 0.007f, 0.015f, 10); //brilho esquerdo
  drawEllipse(0.105f, 0.325f, 0.007f, 0.015f, 10); //brilho direito

  //boca
  glColor3f(0.0, 0.0, 0.0);
  metadeCirculo(0.0,0.270, 0.03, -0.1, 100);

  // Língua 
  glColor3f(0.8, 0.4, 0.6);
  drawEllipse(0.0, 0.200, 0.02, 0.027, 100);

}





void keyboard(unsigned char key, int x, int y){
  printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",key);
  switch (key) {
    case 27: exit(0); // ESC
    case 32: R = 0; G += 50; B = 0; glutPostRedisplay(); break;
  }
}

void Special_keyboard(GLint tecla, int x, int y) {
  switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
    case GLUT_KEY_F12: R = 0; G = 200; B = 200; glutPostRedisplay(); break;
    case GLUT_KEY_F10: R = 0; G = 100; B = 200; glutPostRedisplay(); break;
  }
}
