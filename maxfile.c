#include <stdio.h>

int trovaMassimo(int vettore[], int lunghezza) {
    int massimo = vettore[0]; // Assume il primo elemento come massimo iniziale

    // Itera attraverso gli elementi del vettore per trovare il massimo
    for (int i = 1; i < lunghezza; i++) {
        if (vettore[i] > massimo) {
            massimo = vettore[i];
        }
    }

    return massimo;
}

int main() {
    int vettore[] = {10, 5, 20, 8, 15};
    int lunghezza = sizeof(vettore) / sizeof(vettore[0]);

    int massimo = trovaMassimo(vettore, lunghezza);
    printf("lunghezza: %d\n", lunghezza);
    printf("Il massimo elemento nel vettore è: %d\n", massimo);

    return 0;
}