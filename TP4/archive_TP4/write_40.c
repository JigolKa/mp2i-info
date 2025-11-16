#include <stdio.h>

int main(){
    // ouvrir le fichier en mode write
    FILE* f = fopen("quarante.pas_txt", "w");
    // écrire 40 sur 4 bits
    int x = 40;
    fwrite(&x, 4, 1, f); // depuis l'adresse de x, lire
                         // 1 case mémoire de 4 octets
                         // et stocker dans f

    // fermer le fichier
    fclose(f);

    return 0;
}
