#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    // Para _kbhit() y _getch()
#include <windows.h>  // Para Sleep()

#define WIDTH 54   // Ancho del campo de juego
#define HEIGHT 20  // Altura del campo de juego

// Posiciones iniciales
int ballX = WIDTH / 2, ballY = HEIGHT / 2;   // Posición de la pelota
int ballDirX = 1, ballDirY = 1;              // Dirección de la pelota
int paddle1Y = HEIGHT / 2 - 2, paddle2Y = HEIGHT / 2 - 2; // Posición de las barras
int score1 = 0, score2 = 0;                  // Puntuaciones

boolean cMove = TRUE;

// Dibuja el campo de juego, la pelota y las barras
void drawField() {
    system("cls");  // Limpia la pantalla en Windows

    // Dibuja el campo
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) {
                printf("|");  // Pared lateral
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-");  // Pared superior e inferior
            } else if (x == ballX && y == ballY) {
                printf("O");  // Pelota
            } else if (x == 2 && y >= paddle1Y && y < paddle1Y + 4) {
                printf("#");  // Barra izquierda
            } else if (x == WIDTH - 3 && y >= paddle2Y && y < paddle2Y + 4) {
                printf("#");  // Barra derecha
            } else {
                printf(" ");  // Espacio vacío
            }
        }
        printf("\n");
    }
    // Mostrar puntuación
    printf("Jugador 1: %d  |  Jugador 2: %d\n", score1, score2);
}

// Controla la lógica del movimiento de la pelota
void moveBall() {
    cMove = !cMove;
    if(cMove)
    {
        // Mueve la pelota
        ballX += ballDirX;
        ballY += ballDirY;

        // Rebote superior e inferior
        if (ballY == 0 || ballY == HEIGHT - 1) {
            ballDirY = -ballDirY;
        }

        // Rebote en la barra izquierda
        if (ballX == 3 && ballY >= paddle1Y && ballY < paddle1Y + 4) {
            ballDirX = -ballDirX;
        }

        // Rebote en la barra derecha
        if (ballX == WIDTH - 4 && ballY >= paddle2Y && ballY < paddle2Y + 4) {
            ballDirX = -ballDirX;
        }

        // Puntuación de jugador 2
        if (ballX == 0) {
            score2++;
            ballX = WIDTH / 2;
            ballY = HEIGHT / 2;
            ballDirX = -ballDirX;
        }

        // Puntuación de jugador 1
        if (ballX == WIDTH - 1) {
            score1++;
            ballX = WIDTH / 2;
            ballY = HEIGHT / 2;
            ballDirX = -ballDirX;
        }
    }

}

// Mueve las barras de los jugadores
void movePaddles() {
    if (_kbhit()) {  // Si se ha presionado una tecla
        char ch = _getch();
        // Jugador 1: w (arriba), s (abajo)
        if (ch == 'w' && paddle1Y > 1) {
            paddle1Y--;
        }
        if (ch == 's' && paddle1Y < HEIGHT - 5) {
            paddle1Y++;
        }
        if (ch == 'i' && paddle2Y > 1) {
            paddle2Y--;
        }
        if (ch == 'k' && paddle2Y < HEIGHT - 5) {
            paddle2Y++;
        }

        // Jugador 2: flecha arriba, flecha abajo
        if (ch == 224) {  // Secuencia para las teclas especiales
            switch (_getch()) {
                case 72:  // Flecha arriba
                    if (paddle2Y > 1) paddle2Y--;
                    break;
                case 80:  // Flecha abajo
                    if (paddle2Y < HEIGHT - 5) paddle2Y++;
                    break;
            }
        }
    }
}

int main() {
    // Bucle principal del juego
    while (1) {
        drawField();   // Dibuja el campo
        moveBall();    // Mueve la pelota
        movePaddles(); // Mueve las barras
        Sleep(1);     // Retardo para controlar la velocidad del juego (50ms)
        //usleep(100);
    }
    return 0;
}
