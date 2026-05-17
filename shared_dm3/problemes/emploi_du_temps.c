#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include <string.h>

const int VAR_SZ = 4;
/**
 * renvoie {id}{jour}{créneau}{type}
 * id correspond au numéro de groupe (0 ou 1)
 * jour correspond à: 0 = lundi, ..., 4 = vendredi
 * créneau correspond à l'heure du créneau: 0=[9h,12h], 1=[12h,15h], 2=[15h,18h]
 * type correspond à la matière: 0=maths, 1=physique, 2=info
 */
char *variable(int id, int jour, int creneau, int matiere)
{
    char *s = malloc(sizeof(char) * (VAR_SZ + 1));
    sprintf(s, "%d%d%d%d", id, jour, creneau, matiere);
    return s;
}

/**
 * Contrainte 0:
 * un prof à un seul cours à la fois
 */
char *_c0_par_jour_par_creneau_par_matiere(int jour, int creneau, int matiere)
{
    return au_plus_une((char *[]){variable(0, jour, creneau, matiere), variable(1, jour, creneau, matiere)}, 2);
}

char *contrainte0()
{
    char **s = malloc(sizeof(char *) * 15);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
        {
            s[3 * i + j] = toutes((char *[]){
                                      _c0_par_jour_par_creneau_par_matiere(i, j, 0),
                                      _c0_par_jour_par_creneau_par_matiere(i, j, 1),
                                      _c0_par_jour_par_creneau_par_matiere(i, j, 2),
                                  },
                                  3);
        }
    return toutes(s, 15);
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
            // printf("%s\n", pour_le_creneau_j);
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
char *_contrainte_2_par_eleve(int id)
{
    int sz = 4 * 3 * 3;
    char **res = malloc(sizeof(char *) * sz);
    int idx = 0;
    for (int i = 0; i <= 3; i++)
    {
        for (int m1 = 0; m1 < 3; m1++)
            for (int m2 = 0; m2 < 3; m2++)
            {
                char *clause = malloc(sizeof(char) * (2 * VAR_SZ + 4 + 1));
                sprintf(clause, "~(%s&%s)", variable(id, i, 2, m1), variable(id, i + 1, 2, m2));
                res[idx++] = clause;
            }
    }
    return toutes(res, sz);
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
    int sz = 0;
    // valeurs trouvées expérimentalement
    // désigne le nombre de combinaisons possibles
    // de 3 créneaux par matière en fonction des
    // autres contraintes
    switch (matiere)
    {
    case 0:
        sz = 80;
        break;
    case 1:
        sz = 406;
        break;
    case 2:
        sz = 91;
        break;
    }

    char **res = malloc(sizeof(char *) * sz);
    int idx = 0;
    for (int c1 = 0; c1 < 15; c1++)
        for (int c2 = c1 + 1; c2 < 15; c2++)
            for (int c3 = c2 + 1; c3 < 15; c3++)
            {
                int jour1 = c1 / 3, creneau1 = c1 % 3;
                int jour2 = c2 / 3, creneau2 = c2 % 3;
                int jour3 = c3 / 3, creneau3 = c3 % 3;

                // contrainte 2
                if (abs(jour1 - jour2) == 1 && creneau1 == creneau2 && creneau1 == 2)
                    continue;
                if (abs(jour1 - jour3) == 1 && creneau1 == creneau3 && creneau1 == 2)
                    continue;
                if (abs(jour2 - jour3) == 1 && creneau2 == creneau3 && creneau2 == 2)
                    continue;

                // contrainte 3 et 4
                if (matiere == 0 && (jour1 == jour2 || jour2 == jour3 || jour1 == jour3 || creneau1 == 2 || creneau2 == 2 || creneau3 == 2))
                    continue;

                if (matiere == 2 && (creneau1 == 0 || creneau2 == 0 || creneau3 == 0))
                    continue;

                char *s = malloc(sizeof(char) * (4 + 1 + 3 * VAR_SZ));
                sprintf(s,
                        "(%s&%s&%s)",
                        variable(id, jour1, creneau1, matiere),
                        variable(id, jour2, creneau2, matiere),
                        variable(id, jour3, creneau3, matiere));
                res[idx] = s;
                // printf("%s\n", s);
                idx++;
            }
    // printf("idx: %d\n", idx);
    return exactement_une(res, sz);
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

int main(int argc, char **argv)
{
    // test();
    // char *s = contrainte1();
    // printf("%s\n", s);
    // _contrainte_un_cours_par_creneau_tous_les_jours(0);
    if (argc != 2)
    {
        printf("Utilisation: ./emploi_du_temps fichier_de_sortie\n");
        return 0;
    }

    FILE *f = fopen(argv[1], "w");

    char *contraintes[8] = {
        contrainte0(),
        contrainte1(),
        contrainte2(),
        contrainte3(),
        contrainte4(),
        contrainte5(),
        contrainte6(),
        contrainte7(),
    };
    char *s = toutes(contraintes, 8);
    // printf("%s\n", s);
    fprintf(f, "%s\n", s);
    fclose(f);
}