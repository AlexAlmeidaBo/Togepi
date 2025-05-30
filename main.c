/*
Aluno: Alexsandro Almeida Bomfim
matricula: 202310347
Docente: Vânia (mãe)
Pokemon - Togepi
*/

#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

float posX = 0.0f, posY = 0.0f;
float escala = 1.0f;
float anguloBraco = 0.0f;
float anguloAntebraco = 0.0f;
float anguloMao = 0.0f;
float anguloBracoDir = 0.0f;
float anguloAntebracoDir = 0.0f;
float anguloMaoDir = 0.0f;


void display(void);
void togepi();
void corpo();
void cabeca();
void rosto();
void triangulosCabeca();
void padraoTriangulo();
void pes();
void bracos();
void padraoColoridoCorpo();
void drawCircle(float centroX, float centroY, float raio, int numLados);
void drawEllipse(float centroX, float centroY, float raioX, float raioY, int numLados);
void semiCirculo(float centroX, float centroY, float raioX, float raioY, int numLados);
void tecladoEspecial(int tecla, int x, int y);
void cenarioPokemonStyle();

int main(int argc, char **argv)
{
  glutInit(&argc, argv);                       // Estabelece contato com sistema de janelas
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Cores dos pixels serão expressos em RGB
  glutInitWindowSize(600, 600);                // Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition(50, 50);              // Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow(argv[0]);                   // Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.85f, 0.92f, 1.0f, 1.0f); // selecionar cor de fundo (Branco)
  glOrtho(-1, 1, -1, 1, -1, 1);           // define as coordenadas do volume de recorte (clipping volume),
  glutDisplayFunc(display);               // Função callback chamada para fazer o desenho
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();                         // Depois de registradas as callbacks, o controle é entregue ao sistema de janela
  
  return 0;
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Desenha o cenário fixo
  cenarioPokemonStyle();

  // Aplica transformações apenas ao Togepi
  glPushMatrix();
  glTranslatef(posX, posY, 0.0f);
  glScalef(escala, escala, 1.0f);
  togepi();
  glPopMatrix();

  glFlush();
}

void drawCircle(float centroX, float centroY, float raio, int numLados)
{
  float angulo, passo = 2.0f * PI / numLados;

  // Salva cor atual
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  glBegin(GL_POLYGON);
  for (int i = 0; i <= numLados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raio;
    float y = centroY + sinf(angulo) * raio;
    glVertex2f(x, y);
  }
  glEnd();

  // Desenha contorno
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= numLados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raio;
    float y = centroY + sinf(angulo) * raio;
    glVertex2f(x, y);
  }
  glEnd();

  // Restaura cor
  glColor4fv(corAtual);
}

void drawEllipse(float centroX, float centroY, float raioX, float raioY, int numLados)
{
  float angulo, passo = 2.0f * PI / numLados;
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  glBegin(GL_POLYGON);
  for (int i = 0; i <= numLados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raioX;
    float y = centroY + sinf(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();

  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= numLados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raioX;
    float y = centroY + sinf(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();

  glColor4fv(corAtual);
}

void semiCirculo(float centroX, float centroY, float raioX, float raioY, int numLados)
{
  float angulo, passo = PI / (numLados - 1);
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  // Preenchimento
  glBegin(GL_POLYGON);
  for (int i = 0; i < numLados; i++) {
    angulo = passo * i;
    float x = centroX + cos(angulo) * raioX;
    float y = centroY + sin(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();


  glColor4fv(corAtual);
}

void drawCurvedLine(float inicioX, float inicioY, float fimX, float fimY, float alturaMax, int segmentos)
{
  float t, x, y;
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= segmentos; i++) {
    t = (float)i / segmentos;
    x = (1 - t) * inicioX + t * fimX;
    y = (1 - t) * inicioY + t * fimY + alturaMax * 4 * t * (1 - t);
    glVertex2f(x, y);
  }
  glEnd();
}


void togepi(){
  triangulosCabeca();
  pes();
  corpo();
  cabeca();              
  padraoColoridoCorpo(); 
  rosto();
  padraoTriangulo();
  bracos();
}


// Espinhos no topo da cabeça
void triangulosCabeca()
{
  glColor3f(1.0, 1.0, 0.6);
  glBegin(GL_TRIANGLES);

  // Triângulo esquerdo
  glVertex2f(-0.32f, 0.14f);
  glVertex2f(-0.40f, 0.38f);
  glVertex2f(-0.1f, 0.28f);

  // Triângulo central
  glVertex2f(-0.27f, 0.18f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(0.27f, 0.18f);

  // Triângulo direito
  glVertex2f(0.1f, 0.28f);
  glVertex2f(0.40f, 0.38f);
  glVertex2f(0.32f, 0.14f);
  glEnd();

  //contornos
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(-0.32f, 0.14f);
  glVertex2f(-0.40f, 0.38f);
  glVertex2f(-0.1f, 0.28f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex2f(-0.27f, 0.18f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(0.27f, 0.18f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex2f(0.1f, 0.28f);
  glVertex2f(0.40f, 0.38f);
  glVertex2f(0.32f, 0.14f);

  glEnd();
}


void cabeca()
{
  glColor3f(1.0, 1.0, 0.6);
  semiCirculo(0.0, -0.1, 0.38, 0.45, 100); // preenchimento da cabeça

  // Contorno lateral direito adicional
  glColor3f(0.0, 0.0, 0.0);
  drawCurvedLine(0.30f, 0.18f, 0.38f, -0.1f, 0.055f, 100);
  drawCurvedLine(-0.30f, 0.18f, -0.38f, -0.1f, 0.055f, 100);
}

//corpo ou 'casca' do topegi
void corpo()
{
  glColor3f(1.0, 1.0, 1.0);
  int i;
  float angulo;
  float x, y;

  // estou criando uma elipse sem usar a DrawElipse pois precisava de uma modificação especifica.
  glBegin(GL_POLYGON);
  for (i = 0; i < 360; i++)
  {
    angulo = i * PI / 180.0;
    x = 0.4 * cos(angulo);
    y = 0.35 * sin(angulo) - 0.15;
    glVertex2f(x, y);
  }
  glEnd();

  // Contorno da casca
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (i = 0; i < 360; i++)
  {
    angulo = i * PI / 180.0;
    x = 0.4 * cos(angulo);
    y = 0.35 * sin(angulo) - 0.15;
    glVertex2f(x, y);
  }
  glEnd();

}


// padrao triangular a cima da casca do togepi
void padraoTriangulo()
{
  // Cor branca para o preenchimento
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(-0.4f, -0.15f);
  glVertex2f(-0.35f, -0.05f);
  glVertex2f(-0.30f, -0.12f);
  glVertex2f(-0.25f, -0.02f);
  glVertex2f(-0.20f, -0.10f);
  glVertex2f(-0.10f, 0.02f);
  glVertex2f(0.0f, -0.1f);
  glVertex2f(0.10f, 0.02f);
  glVertex2f(0.20f, -0.10f);
  glVertex2f(0.25f, -0.02f);
  glVertex2f(0.30f, -0.12f);
  glVertex2f(0.35f, -0.05f);
  glVertex2f(0.4f, -0.15f);
  glEnd();

 
};


void rosto()
{

  // Olhos
  glColor3f(0.0, 0.0, 0.0);
  drawEllipse(-0.1f, 0.2f, 0.02f, 0.05f, 20); // olho esquerdo
  drawEllipse(0.1f, 0.2f, 0.02f, 0.05f, 20);  // olho direito

  // Brilho dos olhos
  glColor3f(1.0, 1.0, 1.0);
  drawEllipse(-0.095f, 0.225f, 0.007f, 0.015f, 10); // brilho esquerdo
  drawEllipse(0.105f, 0.225f, 0.007f, 0.015f, 10);  // brilho direito

  // boca
  glColor3f(0.0, 0.0, 0.0);
  semiCirculo(0.0, 0.170, 0.03, -0.1, 100);

  // Língua
  glColor3f(0.8, 0.4, 0.6);
  drawEllipse(0.0, 0.100, 0.02, 0.027, 100);
}


void bracos()
{
  glColor3f(1.0, 1.0, 0.6);

  
  glPushMatrix();
  glTranslatef(-0.38f, -0.1f, 0.0f);
  glRotatef(anguloBraco, 0.0f, 0.0f, 1.0f);

  drawEllipse(0.0f, 0.0f, 0.065f, 0.10f, 50); // braço

  glTranslatef(0.0f, -0.1f, 0.0f);
  glRotatef(anguloAntebraco, 0.0f, 0.0f, 1.0f);
  drawEllipse(0.0f, -0.05f, 0.04f, 0.07f, 50); // antebraço

  glTranslatef(0.0f, -0.1f, 0.0f);
  glRotatef(anguloMao, 0.0f, 0.0f, 1.0f);
  drawEllipse(0.0f, -0.03f, 0.03f, 0.04f, 50); // mão
  glPopMatrix();

 
  glPushMatrix();
  glTranslatef(0.38f, -0.1f, 0.0f);
  glRotatef(-anguloBracoDir, 0.0f, 0.0f, 1.0f);

  drawEllipse(0.0f, 0.0f, 0.065f, 0.10f, 50); // braço

  glTranslatef(0.0f, -0.1f, 0.0f);
  glRotatef(-anguloAntebracoDir, 0.0f, 0.0f, 1.0f);
  drawEllipse(0.0f, -0.05f, 0.04f, 0.07f, 50); // antebraço

  glTranslatef(0.0f, -0.1f, 0.0f);
  glRotatef(-anguloMaoDir, 0.0f, 0.0f, 1.0f);
  drawEllipse(0.0f, -0.03f, 0.03f, 0.04f, 50); // mão
  glPopMatrix();
}


void pes()
{
  glColor3f(1.0, 1.0, 0.6);

  // Pé esquerdo
  glPushMatrix();
  glTranslatef(-0.2f, -0.45f, 0.0f);
  glRotatef(35.0f, 0.0f, 0.0f, 1.0f); // Rotaciona o pé
  drawEllipse(0.0f, 0.0f, 0.08f, 0.04f, 50);
  glPopMatrix();

  // Pé direito
  glPushMatrix();
  glTranslatef(0.2f, -0.45f, 0.0f);
  glRotatef(-35.0f, 0.0f, 0.0f, 1.0f); // Rotaciona o pé
  drawEllipse(0.0f, 0.0f, 0.08f, 0.04f, 50);
  glPopMatrix();
}


void padraoColoridoCorpo()
{
  // Triângulo vermelho (cheio)
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(-0.30f, -0.23f);
  glVertex2f(-0.23f, -0.15f);
  glVertex2f(-0.20f, -0.25f);
  glEnd();

  //triangulo azul
  glColor3f(0.0, 0.5, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f( 0.0f, -0.30f);
  glVertex2f(-0.05f, -0.20f);
  glVertex2f( 0.05f, -0.20f);
  glEnd();

  // Triângulo vermelho
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(0.30f, -0.25f);
  glVertex2f(0.25f, -0.15f);
  glVertex2f(0.20f, -0.25f);
  glEnd();
  // Branco sobreposto
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(0.275f, -0.23f);
  glVertex2f(0.25f, -0.18f);
  glVertex2f(0.225f, -0.23f);
  glEnd();
}

void tecladoEspecial(int tecla, int x, int y)
{
  switch (tecla)
  {
  // Translação
  case GLUT_KEY_UP: posY += 0.05f; break;
  case GLUT_KEY_DOWN: posY -= 0.05f; break;
  case GLUT_KEY_LEFT: posX -= 0.05f; break;
  case GLUT_KEY_RIGHT: posX += 0.05f; break;

  // Escala
  case GLUT_KEY_PAGE_UP: escala += 0.05f; break;
  case GLUT_KEY_PAGE_DOWN: escala = (escala > 0.1f) ? escala - 0.05f : escala; break;

  // Braço esquerdo
  case GLUT_KEY_F1:
    if (anguloBraco < 90.0f) anguloBraco += 5.0f;
    break;
  case GLUT_KEY_F2:
    if (anguloAntebraco < 150.0f) anguloAntebraco += 5.0f;
    break;
  case GLUT_KEY_F3:
    if (anguloMao < 45.0f) anguloMao += 5.0f;
    break;

  // Braço direito
  case GLUT_KEY_F4:
    if (anguloBracoDir < 90.0f) anguloBracoDir += 5.0f;
    break;
  case GLUT_KEY_F5:
    if (anguloAntebracoDir < 150.0f) anguloAntebracoDir += 5.0f;
    break;
  case GLUT_KEY_F6:
    if (anguloMaoDir < 45.0f) anguloMaoDir += 5.0f;
    break;

      // Inverter rotação (braço esquerdo)
  case GLUT_KEY_F7:
    if (anguloBraco > -90.0f) anguloBraco -= 5.0f;
    break;
  case GLUT_KEY_F8:
    if (anguloAntebraco > 0.0f) anguloAntebraco -= 5.0f;
    break;
  case GLUT_KEY_F9:
    if (anguloMao > -45.0f) anguloMao -= 5.0f;
    break;

  // Inverter rotação (braço direito)
  case GLUT_KEY_F10:
    if (anguloBracoDir > -90.0f) anguloBracoDir -= 5.0f;
    break;
  case GLUT_KEY_F11:
    if (anguloAntebracoDir > 0.0f) anguloAntebracoDir -= 5.0f;
    break;
  case GLUT_KEY_F12:
    if (anguloMaoDir > -45.0f) anguloMaoDir -= 5.0f;
    break;
}
  glutPostRedisplay();
}

void cenarioPokemonStyle() {
    // Céu
    glColor3f(0.53f, 0.81f, 0.98f); // Azul do céu
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();

    // Mata/grama
    glColor3f(0.0f, 0.6f, 0.0f); // Verde da grama
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.4f);
        glVertex2f(-1.0f, -0.4f);
    glEnd();

    // Nuvens
    glColor3f(1.0f, 1.0f, 1.0f);
    drawEllipse(-0.7f, 0.7f, 0.15f, 0.07f, 50);
    drawEllipse(-0.6f, 0.75f, 0.10f, 0.05f, 50);
    drawEllipse(0.0f, 0.8f, 0.12f, 0.06f, 50);
    drawEllipse(0.1f, 0.75f, 0.08f, 0.04f, 50);
    drawEllipse(0.6f, 0.6f, 0.13f, 0.06f, 50);
    drawEllipse(0.7f, 0.65f, 0.09f, 0.04f, 50);

    // Árvores
    // Tronco
    glColor3f(0.29f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.4f);
        glVertex2f(-0.8f, -0.1f);
        glVertex2f(-0.75f, -0.1f);
        glVertex2f(-0.75f, -0.4f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.7f, -0.4f);
        glVertex2f(0.7f, -0.05f);
        glVertex2f(0.75f, -0.05f);
        glVertex2f(0.75f, -0.4f);
    glEnd();
    // Folhas
    glColor3f(0.13f, 0.55f, 0.13f);
    drawEllipse(-0.775f, -0.05f, 0.07f, 0.10f, 50);
    drawEllipse(0.725f, 0.0f, 0.08f, 0.11f, 50);
}
