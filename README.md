# Transformações 3D com OpenGL - Octaedro Interativo

Este projeto demonstra transformações geométricas aplicadas a um objeto tridimensional usando a biblioteca OpenGL com GLUT.

## Funcionalidades

- Objeto 3D: Octaedro
- Transformações interativas:
  - Translação
  - Rotação
  - Escala
- Visualização com projeção em perspectiva.
- Transformações informadas por teclado.

---

## Requisitos

Instale as dependências necessárias com:

```bash
sudo apt install freeglut3-dev
```

Para compilar:
```bash
g++ transformacoes_opengl.cpp -o transformacoes -lGL -lGLU -lglut
```

Para executar: 
```bash
./transformacoes
```
