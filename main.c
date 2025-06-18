/*
* Aluno    : Alexsandro Almeida Bomfim
* matricula: 202310347
* Docente  : Vânia
* Pokemon - Togepi
*/

/*
*   Manual de Instruções:
* - Use as setas para mover o Togepi.
* - Pressione espaço para iniciar a animação.
* - Pressione pgUp para aumentar a escala.
* - Pressione pgDn para diminuir a escala.  
* - Pressione F1 para rotacionar o braço esquerdo.
* - Pressione F2 para rotacionar o braço direito.
* - Pressione F3 para inverter a rotação do braço esquerdo.
* - Pressione F4 para inverter a rotação do braço direito.
* - Pressione ESC para sair do programa.
*/


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

// Variáveis globais para controlar posição, escala e animações do Togepi
float posicaoX = 0.0f, posicaoY = -0.4f; // Posição inicial do Togepi
float escalaTogepi = 0.1f;               // Escala inicial do Togepi
float anguloBracoEsq = 0.0f;
float anguloAntebracoEsq = 0.0f;
float anguloMaoEsq = 0.0f;
float anguloBracoDir = 0.0f;
float anguloAntebracoDir = 0.0f;
float anguloMaoDir = 0.0f;

int faseAnimacao = 0; // Controla a fase da animação automática
int frames = 0;       // Contador de frames para animação
int direcaoPulo = 1;  // Direção do pulo (não utilizado)
int estaPiscando = 0; // Indica se o Togepi está piscando

float deslocamentoPulo = 0.0f; // Deslocamento vertical do pulo
float anguloBracoPulo = 0.0f;  // Animação dos braços durante o pulo
float rotacaoPeEsq = 0.0f;     // Rotação do pé esquerdo
float rotacaoPeDir = 0.0f;     // Rotação do pé direito

// Posições das nuvens no cenário
float posicaoNuvem1 = -0.7f;
float posicaoNuvem2 = 0.0f;
float posicaoNuvem3 = 0.6f;

int animacaoAtiva = 0; // Flag para ativar/desativar animação automática

// Protótipos das funções principais
void display(void); 
void togepi();      
void corpo();
void cabeca();
void rosto();
void espinhosCabeca();
void padraoTriangular();
void pes();
void bracos();
void padraoColoridoCorpo();
void desenharCirculo(float centroX, float centroY, float raio, int lados);
void desenharElipse(float centroX, float centroY, float raioX, float raioY, int lados);
void desenharSemicirculo(float centroX, float centroY, float raioX, float raioY, int lados);
void desenharLinhaCurva(float inicioX, float inicioY, float fimX, float fimY, float alturaMax, int segmentos);
void tratarTeclaEspecial(int tecla, int x, int y);
void cenario();
void animar(int valor);
void atualizarNuvens(int valor);
void tratarTeclado(unsigned char tecla, int x, int y);


int main(int argc, char **argv){
  // Inicialização da janela e contexto OpenGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(50, 50);
  glutCreateWindow(argv[0]);
  glClearColor(0.85f, 0.92f, 1.0f, 1.0f); // Cor de fundo
  glOrtho(-1, 1, -1, 1, -1, 1);           // Projeção ortográfica
  glutDisplayFunc(display);                // Função de desenho
  glutSpecialFunc(tratarTeclaEspecial);    // Teclas especiais (setas, F1-F4)
  glutKeyboardFunc(tratarTeclado);         // Teclas normais (ESC, espaço)
  glutTimerFunc(30, atualizarNuvens, 0);   // Timer para animar nuvens
  glutMainLoop();
  return 0;
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  cenario();           // Desenha o cenário fixo
  glPushMatrix();      // Aplica transformações apenas ao Togepi
  glTranslatef(posicaoX + deslocamentoPulo, posicaoY, 0.0f); // Move Togepi
  glScalef(escalaTogepi, escalaTogepi, 0.10f);               // Escala Togepi
  togepi();            // Desenha o Togepi
  glPopMatrix();
  glutSwapBuffers();   // Troca buffers para exibir desenho
}


// Função para desenhar um círculo preenchido e seu contorno
void desenharCirculo(float centroX, float centroY, float raio, int lados)
{
  float angulo, passo = 2.0f * PI / lados;
  // Salva cor atual
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  glBegin(GL_POLYGON);
  for (int i = 0; i <= lados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raio;
    float y = centroY + sinf(angulo) * raio;
    glVertex2f(x, y);
  }
  glEnd();

  // Desenha contorno
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= lados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raio;
    float y = centroY + sinf(angulo) * raio;
    glVertex2f(x, y);
  }
  glEnd();

  // Restaura cor
  glColor4fv(corAtual);
}


void desenharElipse(float centroX, float centroY, float raioX, float raioY, int lados)
{
  float angulo, passo = 2.0f * PI / lados;
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  glBegin(GL_POLYGON);
  for (int i = 0; i <= lados; i++) {
    angulo = passo * i;
    float x = centroX + cosf(angulo) * raioX;
    float y = centroY + sinf(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();

  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= lados; i++) {
    angulo = passo * i;
    float x  = centroX + cosf(angulo) * raioX;
    float y  = centroY + sinf(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();

  glColor4fv(corAtual);
}


void desenharSemicirculo(float centroX, float centroY, float raioX, float raioY, int lados)
{
  float angulo, passo = PI / (lados - 1);
  GLfloat corAtual[4];
  glGetFloatv(GL_CURRENT_COLOR, corAtual);

  // Preenchimento
  glBegin(GL_POLYGON);
  for (int i = 0; i < lados; i++) {
    angulo = passo * i;
    float x = centroX + cos(angulo) * raioX;
    float y = centroY + sin(angulo) * raioY;
    glVertex2f(x, y);
  }
  glEnd();
  glColor4fv(corAtual);
}


void desenharLinhaCurva(float inicioX, float inicioY, float fimX, float fimY, float alturaMax, int segmentos)
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
  espinhosCabeca(); // Desenha os espinhos (triângulos) da cabeça
  pes();            // Desenha os pés
  corpo();          // Desenha o corpo/casca
  cabeca();         // Desenha a cabeça
  padraoColoridoCorpo(); // Desenha os triângulos coloridos do corpo
  rosto();          // Desenha olhos, boca e língua
  padraoTriangular();    // Desenha padrão triangular acima da casca
  bracos();         // Desenha os braços
}


//Função para desenhar os triangulos acima da cabeça do togepi
void espinhosCabeca()
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
  desenharSemicirculo(0.0, -0.1, 0.38, 0.45, 100);  // preenchimento da cabeça

  // Contorno lateral direito adicional
  glColor3f(0.0, 0.0, 0.0);
  desenharLinhaCurva(0.30f, 0.18f, 0.38f, -0.1f, 0.055f, 100);
  desenharLinhaCurva(-0.30f, 0.18f, -0.38f, -0.1f, 0.055f, 100);
}


//corpo ou 'casca' do topegi
void corpo()
{
  glColor3f(1.0, 1.0, 1.0);
  int i;
  float angulo;
  float x, y;

  // estou criando uma elipse sem usar a função DesenharElipse pois precisava de uma modificação especifica.
  glBegin(GL_POLYGON);
  for (i = 0; i < 360; i++)
  {
    angulo = i * PI / 180.0;
    x      = 0.4 * cos(angulo);
    y      = 0.35 * sin(angulo) - 0.15;
    glVertex2f(x, y);
  }
  glEnd();

  // Contorno da casca
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (i = 0; i < 360; i++)
  {
    angulo = i * PI / 180.0;
    x      = 0.4 * cos(angulo);
    y      = 0.35 * sin(angulo) - 0.15;
    glVertex2f(x, y);
  }
  glEnd();

}


// padrao triangular a cima da casca do togepi
void padraoTriangular()
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

  if(!estaPiscando){
  
    // Olhos
    glColor3f(0.0, 0.0, 0.0);
    desenharElipse(-0.1f, 0.2f, 0.02f, 0.05f, 20);  // olho esquerdo
    desenharElipse(0.1f, 0.2f, 0.02f, 0.05f, 20);   // olho direito

    // Brilho dos olhos
    glColor3f(1.0, 1.0, 1.0);
    desenharElipse(-0.095f, 0.225f, 0.007f, 0.015f, 10);  // brilho esquerdo
    desenharElipse(0.105f, 0.225f, 0.007f, 0.015f, 10);   // brilho direito

  } else {

    // Olhos piscando
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.12f, 0.2f); glVertex2f(-0.08f, 0.2f);
    glVertex2f(0.08f, 0.2f); glVertex2f(0.12f, 0.2f);
    glEnd();
  }
  
  // boca
  glColor3f(0.0, 0.0, 0.0);
  desenharSemicirculo(0.0, 0.170, 0.03, -0.1, 100);

  // Língua
  glColor3f(0.8, 0.4, 0.6);
  desenharElipse(0.0, 0.100, 0.02, 0.027, 100);
}


void bracos()
{
  glColor3f(1.0, 1.0, 0.6);

  float anguloEsq = animacaoAtiva ? anguloBracoPulo : anguloBracoEsq; 
  float anguloDir = animacaoAtiva ? -anguloBracoPulo : anguloBracoDir;

  glPushMatrix();
  glTranslatef(-0.38f, -0.1f, 0.0f);
  glRotatef(anguloEsq, 0.0f, 0.0f, 1.0f);
  desenharElipse(0.0f, 0.0f, 0.065f, 0.10f, 50);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.38f, -0.1f, 0.0f);
  glRotatef(anguloDir, 0.0f, 0.0f, 1.0f);
  desenharElipse(0.0f, 0.0f, 0.065f, 0.10f, 50);
  glPopMatrix();
}


void pes()
{
  glColor3f(1.0, 1.0, 0.6);

  // Pé esquerdo
  glPushMatrix();
  glTranslatef(-0.2f, -0.45f, 0.0f);
  glRotatef(rotacaoPeEsq, 0.0f, 0.0f, 2.0f); 
  desenharElipse(0.0f, 0.0f, 0.08f, 0.04f, 50);
  glPopMatrix();

  // Pé direito
  glPushMatrix();
  glTranslatef(0.2f, -0.45f, 0.0f);
  glRotatef(rotacaoPeDir, 0.0f, 0.0f, 2.0f); 
  desenharElipse(0.0f, 0.0f, 0.08f, 0.04f, 50);
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


void tratarTeclaEspecial(int tecla, int x, int y)
{
  // Controle de movimentação, escala e rotação dos braços via teclado
  switch (tecla)
  {
    // Translação
  case GLUT_KEY_UP: posicaoY    += 0.05f; break;
  case GLUT_KEY_DOWN: posicaoY  -= 0.05f; break;
  case GLUT_KEY_LEFT: posicaoX  -= 0.05f; break;
  case GLUT_KEY_RIGHT: posicaoX += 0.05f; break;

    // Escala
  case GLUT_KEY_PAGE_UP: escalaTogepi   += 0.05f; break;
  case GLUT_KEY_PAGE_DOWN: escalaTogepi  = (escalaTogepi > 0.1f) ? escalaTogepi - 0.05f : escalaTogepi; break;

    // Braço esquerdo
  case GLUT_KEY_F1: 
    if (anguloBracoEsq < 90.0f) anguloBracoEsq += 5.0f;
    break;
    // Braço direito
  case GLUT_KEY_F2: 
    if (anguloBracoDir < 90.0f) anguloBracoDir += 5.0f;
    break;
    // Inverter rotação (braço esquerdo)
  case GLUT_KEY_F3: 
    if (anguloBracoEsq > -90.0f) anguloBracoEsq -= 5.0f;
    break;
    // Inverter rotação (braço direito)
  case GLUT_KEY_F4: 
    if (anguloBracoDir > -90.0f) anguloBracoDir -= 5.0f;
    break;
  }
  glutPostRedisplay();
}


// Função para desenhar o cenário: céu, grama, nuvens e árvores
void cenario() {
  // Céu
  glColor3f(0.53f, 0.81f, 0.98f);  
  glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
  glEnd();

  // Mata e grama
  glColor3f(0.0f, 0.6f, 0.0f);  
  glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
  glEnd();

  // Nuvens (movimentação controlada por atualizarNuvens)
  glColor3f(1.0f, 1.0f, 1.0f);
  desenharElipse(posicaoNuvem1, 0.7f, 0.15f, 0.07f, 50);
  desenharElipse(posicaoNuvem1 + 0.1f, 0.75f, 0.10f, 0.05f, 50);
  desenharElipse(posicaoNuvem2, 0.8f, 0.12f, 0.06f, 50);
  desenharElipse(posicaoNuvem2 + 0.1f, 0.75f, 0.08f, 0.04f, 50);
  desenharElipse(posicaoNuvem3, 0.6f, 0.13f, 0.06f, 50);
  desenharElipse(posicaoNuvem3 + 0.1f, 0.65f, 0.09f, 0.04f, 50);

  
  //Arvores e Troncos
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
  desenharElipse(-0.775f, -0.05f, 0.07f, 0.10f, 50);
  desenharElipse(0.725f, 0.0f, 0.08f, 0.11f, 50);
}


// Função de animação automática do Togepi
void animar(int valor) {
  if (!animacaoAtiva) return; // Só anima se ativado
  frames++;

  if (faseAnimacao == 0) { // Crescendo
    if (escalaTogepi < 1.0f) {
      escalaTogepi  += 0.015f;
      rotacaoPeEsq  = sin(frames * 0.2f) * 10.0f;  // Movimento vertical
      rotacaoPeDir  = sin(frames * 0.2f) * 10.0f;  // Movimento vertical
    } else {
      faseAnimacao  = 1;
      frames = 0;
    }
  }
  else if (faseAnimacao == 1) { // Piscar
    estaPiscando = (frames < 15); // Pisca por alguns frames
    if (frames > 30) {
      faseAnimacao  = 2;
      frames = 0;
    }
  }
  else if (faseAnimacao == 2) { // Dança
    deslocamentoPulo = sin(frames * 0.2f) * 0.05f;
    anguloBracoPulo = sin(frames * 0.2f) * 30.0f;
    rotacaoPeEsq = sin(frames * 0.2f) * 10.0f;  // Movimento vertical
    rotacaoPeDir = -rotacaoPeEsq;              // Movimento vertical
  }

  if (frames > 500) { // Limita duração da animação
    animacaoAtiva = 0;
    return;
  }

  glutPostRedisplay();
  glutTimerFunc(30, animar, 0); // Chama novamente para próximo frame
}

// Função para mover as nuvens
void atualizarNuvens(int valor) {
  posicaoNuvem1 += 0.003f;
  posicaoNuvem2 += 0.003f;
  posicaoNuvem3 += 0.003f;

  // Reaparecer pela esquerda ao sair da tela
  if (posicaoNuvem1 > 1.0f) posicaoNuvem1 = -1.0f;
  if (posicaoNuvem2 > 1.0f) posicaoNuvem2 = -1.0f;
  if (posicaoNuvem3 > 1.0f) posicaoNuvem3 = -1.0f;

  glutPostRedisplay();
  glutTimerFunc(30, atualizarNuvens, 0); // Chama novamente
}

// Função para tratatamento de teclas normais (ESC e espaço)
void tratarTeclado(unsigned char tecla, int x, int y) {
  if (tecla == 27) exit(0);  // ESC para sair

  if (tecla == 32) { // Barra de espaço inicia animação automática
    if(animacaoAtiva) return;
    faseAnimacao = 0;
    frames = 0;
    escalaTogepi = 0.1f;
    posicaoX = 0.0f;
    posicaoY = -0.4f;
    deslocamentoPulo = 0.0f;
    estaPiscando = 0;
    anguloBracoPulo = 0.0f;
    rotacaoPeEsq = 0.0f;
    rotacaoPeDir = 0.0f;
    animacaoAtiva = 1;               // Inicia a animação 
    glutTimerFunc  (30, animar, 0);  // Recomeça a animação com intervalo consistente
  }
}