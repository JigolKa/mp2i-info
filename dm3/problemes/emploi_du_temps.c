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
char *variable(int id, int jour, int creneau, int matiere)
{
    char *s = malloc(sizeof(char) * (VAR_SZ + 1));
    sprintf(s, "X_%d_%d_%d_%d", id, jour, creneau, matiere);
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
    int idx = 0;
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            char *pour_le_creneau_j = _contrainte_un_cours_par_creneau_par_groupe_par_jour(id, i, j);
            // int sz = strlen(pour_le_creneau_j);
            printf("%s\n", pour_le_creneau_j);
            creneaux[idx] = pour_le_creneau_j;
            idx++;
        }
    }
    return toutes(creneaux, 15);
}

char *contrainte1()
{
    char *grp1 = _contrainte_un_cours_par_creneau_tous_les_jours(0);
    char *grp2 = _contrainte_un_cours_par_creneau_tous_les_jours(1);
    int sz = strlen(grp1) + strlen(grp2) + 3;
    char *s = malloc(sizeof(char) * (sz + 1));
    sprintf(s, "(%s&%s)", grp1, grp2);
    return s;
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
        char clause[2 * VAR_SZ + 4 + 1];
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
char *
_contrainte3_par_eleve_par_jour(int id, int jour)
{
    return au_plus_une((char *[3]){variable(id, jour, 0, 0), variable(id, jour, 1, 0), variable(id, jour, 2, 0)}, 3);
}

char *_contrainte3_par_eleve(int id)
{
    char *s[5];
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

/**
 * Contrainte 4:
 * pas de cours de maths sur le créneau 15h-18h
 */
char *_contrainte4_par_jour(int jour)
{
    char *res = malloc(sizeof(char) * (2 * VAR_SZ + 4 + 1));
    sprintf(res, "~(%s|%s)", variable(0, jour, 2, 0), variable(1, jour, 2, 0));
    return res;
}

char *contrainte4()
{
    char *s[5];
    for (int i = 0; i <= 4; i++)
        s[i] = _contrainte4_par_jour(i);
    return toutes(s, 5);
}

/**
 * Contrainte 5:
 * pas de cours d'info sur le créneau 9h-12h (fainéant)
 */
char *_contrainte5_par_jour(int jour)
{
    char *res = malloc(sizeof(char) * (2 * VAR_SZ + 4 + 1));
    sprintf(res, "~(%s|%s)", variable(0, jour, 0, 2), variable(1, jour, 0, 2));
    return res;
}

char *contrainte5()
{
    char *s[5];
    for (int i = 0; i <= 4; i++)
        s[i] = _contrainte5_par_jour(i);
    return toutes(s, 5);
}

/**
 * Contrainte 6:
 * un créneau libre pour le proviseur
 */
char *_c6_creneau_libre_pour_les_2_groupes(int jour, int creneau)
{
    char *res = malloc(sizeof(char) * (6 * VAR_SZ + 8 + 1));
    sprintf(
        res,
        "~(%s|%s|%s|%s|%s|%s)",
        variable(0, jour, creneau, 0), variable(0, jour, creneau, 1), variable(0, jour, creneau, 2),
        variable(1, jour, creneau, 0), variable(1, jour, creneau, 1), variable(1, jour, creneau, 2));
    return res;
}

char *contrainte6()
{
    char **res = malloc(sizeof(char *) * 15); // 15 = 3 creneaux * 5 jours
    for (int i = 0; i <= 4; i++)
        for (int j = 0; j <= 2; j++)
        {
            res[3 * i + j] = _c6_creneau_libre_pour_les_2_groupes(i, j);
        }
    return au_moins_une(res, 15);
}

/**
 * Contrainte 7:
 * chaque groupe a 3 creneaux de maths, info et physique
 */
char *_c7_exactement_3_creneaux_par_groupe_par_matiere(int id, int matiere)
{
    int sz = 15 * 14 * 13;
    char **res = malloc(sizeof(char *) * sz);
    int idx = 0;
    for (int c1 = 0; c1 < 15; c1++)
        for (int c2 = c1 + 1; c2 < 15; c2++)
            for (int c3 = c2 + 1; c3 < 15; c3++)
            {
                int jour1 = c1 / 3, creneau1 = c1 % 3;
                int jour2 = c2 / 3, creneau2 = c2 % 3;
                int jour3 = c3 / 3, creneau3 = c3 % 3;
                printf("%d %d\n", jour1, creneau1);
                printf("%d %d\n", jour2, creneau2);
                printf("%d %d\n", jour3, creneau3);

                char *s = malloc(sizeof(char) * (4 + 1 + 3 * VAR_SZ));
                sprintf(s,
                        "(%s&%s&%s)",
                        variable(id, jour1, creneau1, matiere),
                        variable(id, jour2, creneau2, matiere),
                        variable(id, jour3, creneau3, matiere));
                res[idx] = s;
                printf("%s\n", s);
                idx++;
            }
    // return toutes((char *[]){au_moins_une(res, 2), au_plus_une(res, 2)}, 2);
    return au_moins_une(res, sz);
    // return "";
}

char *contrainte7()
{
    return toutes((char *[]){
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(0, 0),
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(0, 1),
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(0, 2),
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(1, 0),
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(1, 1),
                      _c7_exactement_3_creneaux_par_groupe_par_matiere(1, 2)},
                  6);
}

void test()
{
    // printf("%s\n", contrainte1());
    // printf("%s\n", contrainte2());
    // printf("%s\n", contrainte3());
    // printf("%s\n", contrainte4());
    // printf("%s\n", contrainte5());
    // printf("%s\n", contrainte6());
    printf("%s\n", contrainte7());
}

int main()
{
    // test();
    // char *s = contrainte1();
    // printf("%s\n", s);
    // _contrainte_un_cours_par_creneau_tous_les_jours(0);

    char *contraintes[7] = {
        contrainte1(),
        contrainte2(),
        contrainte3(),
        contrainte4(),
        contrainte5(),
        contrainte6(),
        contrainte7(),
    };
    // char *s = toutes(contraintes, 7);
    printf("%s\n", _c7_exactement_3_creneaux_par_groupe_par_matiere(0, 0));
    // FILE *f = fopen("emploi_du_temps_formule.txt", "w");
    // fprintf(f, "%s", toutes(contraintes, 7));
    // fclose(f);
    // char *s = _contrainte_un_cours_par_creneau_par_groupe_par_jour(0, 0, 0);
    // char *s2 = contrainte1();
    // printf("%s\n", s);
    // printf("%s\n", s2);
    // char *s = _contrainte_2_par_eleve_par_cours(0, 0);
    // char *s = contrainte3();
    // printf("%s\n", s);
    // printf("%s\n", aucun((char *[3]){"x", "y", "z"}, 3));
}