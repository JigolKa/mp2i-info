#ifndef UTILS_H
#define UTILS_H

// renvoie la formule de disjonction des formules de l
char *au_moins_une(char **l, int n);

// renvoie not(s) sous forme atomique
// remarque : il faut que s soit sous forme atomique
char *not(char *s);

// renvoie la formule correspondant à au plus une des formules de l est vraie
// pour le rapport : la longueur de chaîne crée est de l'ordre de la somme totale des longueurs (longueur conjonction)
// multipliée par le nombre totale de formule atomiques + 1 à une constante près
char *au_plus_une(char **l, int n);

//  renvoie la formule de conjonction des formules de l
// le code de cette fonction est exactement le même que celui de au_moins_une
char *exactement(char **l, int n);
char *toutes(char **l, int n);

/**
 * utilise le nouvel opérateur %
 */
char *exactement_une(char **l, int n);

// ensemble des tests
void t_batterie_utils();

#endif
