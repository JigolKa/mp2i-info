#pragma once

#define min(a, b) a > b ? b : a
#define max(a, b) a + b - min(a, b)

/**
 * renvoie la disjonction
 */
char *au_moins_une(char **l, int n);

/**
 * utilise le nouvel opérateur %
 */
char *exactement_une(char **l, int n);

/**
 * renvoie la conjonction
 */
char *toutes(char **l, int n);

/**
 * renvoie ~toutes(l,n)
 */
char *aucun(char **l, int n);

/**
 * pour l = x1, ..., xn,
 * renvoie (~x1|~x2)&(~x1|~x3)&...&(~x(n-1)|~xn)
 */
char *au_plus_une(char **l, int n);