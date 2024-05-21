#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Raindrop {
    float x, y; // Posição da gota de chuva
    float length; // Comprimento da gota
    float speed; // Velocidade de queda
};

std::vector<Raindrop> raindrops;
int numberOfDrops = 1000; 
bool isBlackBackground = false; 
bool isGreyBackground = false; 


void initRain() {
    srand(time(NULL)); 
    for (int i = 0; i < numberOfDrops; ++i) {
        Raindrop drop;
        drop.x = (rand() % 1000) / 500.0f - 1.0f; 
        drop.y = (rand() % 1000) / 500.0f - 1.0f; 
        drop.length = (rand() % 5) / 100.0f + 0.02f; 
        drop.speed = (rand() % 5) / 1000.0f + 0.01f; 
        raindrops.push_back(drop);
    }
}

void drawWindows() {
    // Desenha a borda das janelas (marrom)
    glColor3f(0.65f, 0.16f, 0.16f); 
    // Janela esquerda
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, -0.3f);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.35f, -0.1f);
    glEnd();
    // Janela direita
    glBegin(GL_QUADS);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(0.35f, -0.3f);
    glVertex2f(0.35f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glEnd();

    // Desenha o vidro das janelas (azul claro)
    glColor3f(0.53f, 0.81f, 0.92f); 
    // Vidro esquerdo
    glBegin(GL_QUADS);
    glVertex2f(-0.33f, -0.28f);
    glVertex2f(-0.22f, -0.28f);
    glVertex2f(-0.22f, -0.12f);
    glVertex2f(-0.33f, -0.12f);
    glEnd();
    // Vidro direito
    glBegin(GL_QUADS);
    glVertex2f(0.22f, -0.28f);
    glVertex2f(0.33f, -0.28f);
    glVertex2f(0.33f, -0.12f);
    glVertex2f(0.22f, -0.12f);
    glEnd();
}

void drawRain() {
    glColor3f(0.53f, 0.81f, 0.92f); 
    glLineWidth(2); 
    glBegin(GL_LINES);
    for (auto &drop : raindrops) {
        glVertex2f(drop.x, drop.y);
        glVertex2f(drop.x, drop.y + drop.length);
    }
    glEnd();
}

void updateRain(int value) {
    for (auto &drop : raindrops) {
        drop.y -= drop.speed; // Move a gota para baixo
        if (drop.y < -1) { // Se a gota sair da tela, reinicia na parte superior
            drop.y = 1.0f;
            drop.x = (rand() % 1000) / 500.0f - 1.0f; // Nova posição x aleatória
        }
    }
    glutPostRedisplay(); // Marca a janela atual para ser redesenhada
    glutTimerFunc(16, updateRain, 0); // Reagenda a atualização para 16 ms depois
}

// Função para atualizar a cor de fundo
void updateBackgroundColor() {
    if (isBlackBackground) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    } else if (isGreyBackground) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    } else {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

// Função de callback para eventos de teclado
void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        isBlackBackground = true; // Muda para preto com ESPAÇO
        isGreyBackground = false; // Desativa o fundo cinza
    } else {
        isBlackBackground = false; // Muda para branco com qualquer outra tecla comum
        isGreyBackground = false; // Desativa o fundo cinza
    }
    updateBackgroundColor();
    glutPostRedisplay();
}

// Função de callback para teclas especiais
void specialKeys(int key, int x, int y) {
    isGreyBackground = true; // Ativa o fundo cinza para qualquer tecla especial
    isBlackBackground = false; // Desativa o fundo preto
    updateBackgroundColor();
    glutPostRedisplay();
}


void drawDoor() {
    // Corpo da porta em marrom
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glEnd();

    // Borda da porta em preto
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glEnd();

    // Maçaneta da porta (ponto preto)
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(0.08f, -0.35f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();


    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();


    glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, 0.0f);
    glEnd();


    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, 0.0f);
    glEnd();


    glColor3f(0.5f, 0.35f, 0.05f); // Cor das telhas
    float startY = 0.01f; // Posição inicial Y das linhas dentro do telhado
    float endY = 0.49f; // Posição final Y das linhas (próximo ao topo do telhado)
    float stepY = 0.05f; // Espaçamento entre as linhas

    for (float y = startY; y < endY; y += stepY) {
        float xLeft = -0.5f + y;
        float xRight = 0.5f - y;
        
        glBegin(GL_LINES);
        glVertex2f(xLeft, y);
        glVertex2f(xRight, y);
        glEnd();
    }

    drawDoor();
    drawRain();
    drawWindows();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480); 
    glutCreateWindow("Casa com chuva");

    updateBackgroundColor();

    initRain();

    glutDisplayFunc(display); // Registra a função de callback de desenho
    glutKeyboardFunc(keyboard); // Registra a função de callback de teclado
    glutSpecialFunc(specialKeys); // Registra a função de callback para teclas especiais
    glutTimerFunc(0, updateRain, 0); // Inicia a animação da chuva

    glutMainLoop();

    return 0;
}
