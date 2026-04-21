#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include <string.h>

const int VAR_SZ = 9;
/**
 * renvoie X_{id}_{jour}_{créneau}_{type}
 * id correspond au numéro de groupe (0 ou 1)
 * jour correspond à: 0 = lundi, ..., 4 = vendredi
 * créneau correspond à l'heure du créneau: 0=[9h,12h], 1=[12h,15h], 2=[15h,18h]
 * type correspond à la matière: 0=maths, 1=physique, 2=info
 */
char *variable(int id, int jour, int creneau, int type)
{
    char *s = malloc(sizeof(char) * (VAR_SZ + 1));
    sprintf(s, "X_%d_%d_%d_%d", id, jour, creneau, type);
    return s;
}

/**
 * Contrainte 1:
 * au plus un cours par créneau
 */
char *_contrainte_un_cours_par_creneau_par_groupe_par_jour(int id, int jour, int creneau)
{
    char *maths = variable(id, jour, creneau, 0);
    char *physique = variable(id, jour, creneau, 1);
    char *info = variable(id, jour, creneau, 2);
    char *ensemble[3] = {maths, physique, info};
    return au_plus_une(ensemble, 3);
}

char *_contrainte_un_cours_par_creneau_tous_les_jours(int id)
{
    char **creneaux = malloc(sizeof(char *) * 15); // 15=3 creneaux * 5 jours
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            char *pour_le_creneau_j = _contrainte_un_cours_par_creneau_par_groupe_par_jour(id, i, j);
            // int sz = strlen(pour_le_creneau_j);
            creneaux[3 * i + j] = pour_le_creneau_j;
        }
    }
    return toutes(creneaux, 15);
}

char *contrainte1()
{
    char *grp1 = _contrainte_un_cours_par_creneau_tous_les_jours(0);
    char *grp2 = _contrainte_un_cours_par_creneau_tous_les_jours(1);
    char *ens[2] = {grp1, grp2};
    return toutes(ens, 2);
}

/**
 * Contrainte 2:
 * aucun élève ne finit 2 jours d'affilée à 18h
 */
char *_contrainte_2_par_eleve_par_cours(int id, int type)
{
    /**
     * 4 clauses
     * => 3 &
     * + 4*(2S+4)
     */
    char *res = malloc(sizeof(char) * (7 + 4 * (2 * VAR_SZ + 4) + 1));
    int idx = 0;
    for (int i = 0; i <= 3; i++)
    {
        char clause[2 * VAR_SZ + 4];
        sprintf(clause, "~(%s&%s)", variable(id, i, 2, type), variable(id, i + 1, 2, type));
        // printf("%s %ld\n", clause, strlen(clause));
        if (i != 0)
            sprintf(res, "%s&%s", res, clause);
        else
            sprintf(res, "%s", clause);
    }
    return res;
}
char *_contrainte_2_par_eleve(int id)
{
    char *maths = _contrainte_2_par_eleve_par_cours(id, 0);
    char *phys = _contrainte_2_par_eleve_par_cours(id, 1);
    char *info = _contrainte_2_par_eleve_par_cours(id, 2);
    return toutes((char *[3]){maths, info, phys}, 3);
}

char *contrainte2()
{
    char *g1 = _contrainte_2_par_eleve(0);
    char *g2 = _contrainte_2_par_eleve(1);
    return toutes((char *[2]){g1, g2}, 2);
}

/**
 * Contrainte 3:
 * au plus 1 créneau de maths par jour
 */
char *_contrainte3_par_eleve_par_jour(int id, int jour)
{
    return au_plus_une((char *[3]){variable(id, jour, 0, 0), variable(id, jour, 1, 0), variable(id, jour, 2, 0)}, 3);
}

char *_contrainte3_par_eleve(int id)
{
    char *s[5] = {
        "",
        "",
        "",
        "", ""};
    for (int i = 0; i <= 4; i++)
        s[i] = _contrainte3_par_eleve_par_jour(id, i);
    return toutes(s, 5);
}

char *contrainte3()
{
    char *g1 = _contrainte3_par_eleve(0);
    char *g2 = _contrainte3_par_eleve(1);
    return toutes((char *[2]){g1, g2}, 2);
}

int main()
{
    // char *s = _contrainte_un_cours_par_creneau_par_groupe_par_jour(0, 0, 0);
    // char *s2 = contrainte1();
    // printf("%s\n", s);
    // printf("%s\n", s2);
    // char *s = _contrainte_2_par_eleve_par_cours(0, 0);
    // char *s = contrainte3();
    // printf("%s\n", s);
    // printf("%s\n", aucun((char *[3]){"x", "y", "z"}, 3));
}