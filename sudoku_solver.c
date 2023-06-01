#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9

int operationCount = 0;

int isSafe(int grid[N][N], int row, int col, int num);
void printGrid(int grid[N][N]);
int solveSudoku(int grid[N][N]);
int findUnassignedLocation(int grid[N][N], int *row, int *col);

// Função para verificar se é seguro atribuir um número em uma determinada posição
int isSafe(int grid[N][N], int row, int col, int num) {
    // Verifica se o número já está presente na linha
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }
    // Verifica se o número já está presente na coluna
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }
    // Verifica se o número já está presente no bloco 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }
    return 1;
}

// Função para imprimir o tabuleiro sudoku
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0) {
            printf("-------------------------\n");
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0) {
                printf("| ");
            }
            if (grid[row][col] != 0) {
                printf("%d ", grid[row][col]);
            } else {
                printf("x ");
            }
        }
        printf("|\n");
    }
    printf("-------------------------\n");
}

// Função para resolver o sudoku usando backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;
    // Verifica se todas as posições foram preenchidas, se sim, retorna 1
    if (!findUnassignedLocation(grid, &row, &col)) {
        return 1;
    }
    // Tenta atribuir valores de 1 a 9 em posições vazias
    for (int num = 1; num <= 9; num++) {
        operationCount++; // Conta a atribuição
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            // Se a atribuição for bem-sucedida, tenta resolver o restante do tabuleiro
            if (solveSudoku(grid)) {
                return 1;
            }
            // Se a atribuição não for bem-sucedida, desfaz e tenta novamente
            grid[row][col] = 0;
        }
    }
    return 0;
}

// Função para encontrar uma posição não atribuída no tabuleiro
int findUnassignedLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    clock_t start, end;
    double executionTime;
    
    start = clock(); // Inicia a contagem do tempo
    
    int grid[N][N];

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            scanf("%d", &grid[row][col]);
        }
    }

    if (solveSudoku(grid)) {
        end = clock(); // Finaliza a contagem do tempo
        executionTime = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // Tempo de execução em milissegundos
        
        printGrid(grid);
        printf("\nNúmero de operações: %d\n", operationCount);
        printf("Tempo de execução: %.2f ms\n", executionTime);
    } else {
        printf("Não é possível resolver o Sudoku.\n");
    }

    return 0;
}