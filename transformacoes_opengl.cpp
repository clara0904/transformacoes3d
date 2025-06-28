#include <GL/glut.h>

// Variáveis de Transformação
float translacaoX = 0, translacaoY = 0, translacaoZ = 0;
float rotacaoX = 0, rotacaoY = 0, rotacaoZ = 0;
float escalaX = 1, escalaY = 1, escalaZ = 1;

void desenharTexto(float x, float y, const char* texto) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void desenharOctaedro() {
    GLfloat vertices[6][3] = {
        {  1,  0,  0 },  // V0
        { -1,  0,  0 },  // V1
        {  0,  1,  0 },  // V2
        {  0, -1,  0 },  // V3
        {  0,  0,  1 },  // V4 (frente)
        {  0,  0, -1 }   // V5 (atrás)
    };

    // Faces 
    glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_TRIANGLES);
    glVertex3fv(vertices[0]); glVertex3fv(vertices[2]); glVertex3fv(vertices[4]);
    glVertex3fv(vertices[2]); glVertex3fv(vertices[1]); glVertex3fv(vertices[4]);
    glVertex3fv(vertices[1]); glVertex3fv(vertices[3]); glVertex3fv(vertices[4]);
    glVertex3fv(vertices[3]); glVertex3fv(vertices[0]); glVertex3fv(vertices[4]);

    glVertex3fv(vertices[2]); glVertex3fv(vertices[0]); glVertex3fv(vertices[5]);
    glVertex3fv(vertices[1]); glVertex3fv(vertices[2]); glVertex3fv(vertices[5]);
    glVertex3fv(vertices[3]); glVertex3fv(vertices[1]); glVertex3fv(vertices[5]);
    glVertex3fv(vertices[0]); glVertex3fv(vertices[3]); glVertex3fv(vertices[5]);
    glEnd();

    // Arestas 
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    int arestas[][2] = {
        {0,2}, {2,1}, {1,3}, {3,0},
        {0,4}, {1,4}, {2,4}, {3,4},
        {0,5}, {1,5}, {2,5}, {3,5}
    };
    for (auto& aresta : arestas) {
        glVertex3fv(vertices[aresta[0]]);
        glVertex3fv(vertices[aresta[1]]);
    }
    glEnd();
}

void desenharCena() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3, 3, 5, 0, 0, 0, 0, 1, 0);

    glTranslatef(translacaoX, translacaoY, translacaoZ);
    glRotatef(rotacaoX, 1, 0, 0);
    glRotatef(rotacaoY, 0, 1, 0);
    glRotatef(rotacaoZ, 0, 0, 1);
    glScalef(escalaX, escalaY, escalaZ);

    desenharOctaedro();

    desenharTexto(10, 580, "W/S: sobe/desce | A/D: esquerda/direita | Q/E: profundidade");
    desenharTexto(10, 565, "I/K: rotacao X | J/L: rotacao Y | U/O: rotacao Z");
    desenharTexto(10, 550, "+/-: aumentar/reduzir escala | ESC: sair");

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': translacaoY += 0.1; break;
        case 's': translacaoY -= 0.1; break;
        case 'a': translacaoX -= 0.1; break;
        case 'd': translacaoX += 0.1; break;
        case 'q': translacaoZ += 0.1; break;
        case 'e': translacaoZ -= 0.1; break;
        case 'i': rotacaoX += 5; break;
        case 'k': rotacaoX -= 5; break;
        case 'j': rotacaoY += 5; break;
        case 'l': rotacaoY -= 5; break;
        case 'u': rotacaoZ += 5; break;
        case 'o': rotacaoZ -= 5; break;
        case '+': escalaX += 0.1; escalaY += 0.1; escalaZ += 0.1; break;
        case '-': escalaX -= 0.1; escalaY -= 0.1; escalaZ -= 0.1; break;
        case 27: exit(0); // ESC
    }
    glutPostRedisplay();
}

void redimensionar(int largura, int altura) {
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)largura / altura, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Transformações 3D - Octaedro");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(desenharCena);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}
