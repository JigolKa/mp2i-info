#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define max(a, b) a > b ? a : b
char FILL_CHARACTER = '@';
int CHARACTER_COUNT = 1;

char *open(char c)
{
    bool is_maj = 65 <= c && c <= 90, is_min = 97 <= c && c <= 122, is_space = c == 32, is_num = 48 <= c && c <= 57;
    if (!is_num && !is_maj && !is_min && !is_space) // vérifie si c est une lettre ou un espace
        return NULL;

    char *res = NULL;
    if (is_maj)
    {
        res = malloc(sizeof(char) * 15);
        sprintf(res, "lettres/%c%c.txt", c, c);
    }
    else if (is_num || is_min)
    {
        res = malloc(sizeof(char) * 14);
        sprintf(res, "lettres/%c.txt", c);
    }
    else
        res = "lettres/espace.txt";

    return res;
}

/**
 * Récupère le symbole associé à c (matrice 2D)
 */
char **get_mat(char c)
{
    char *filename = open(c);
    FILE *f = fopen(filename, "r");
    if (c != ' ')
        free(filename);
    char **mat = malloc(sizeof(char *) * 8);
    for (int i = 0; i < 8; i++)
        mat[i] = malloc(sizeof(char) * 9);
    int x;

    for (int i = 0; i < 8; i++)
    {
        fscanf(f, "%d", &x);
        // printf("i=%d,x=%d\n", i, x);
        for (int j = 0; j < 8; j++)
        {
            mat[i][7 - j] = x % 2 == 1 ? FILL_CHARACTER : ' ';
            x /= 2;
        }
        mat[i][8] = '\0';
        // printf("%s\n", mat[i]);
    }
    fclose(f);
    return mat;
}

/**
 * Fusionne les matrices
 * n: nombre de matrices (mots)
 */
char **merge_mats(char ***matrices)
{
    int n = CHARACTER_COUNT;
    char **res = malloc(sizeof(char *) * 8);
    for (int i = 0; i < 8; i++)
        res[i] = malloc(sizeof(char) * (8 * n + 1));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < n; j++) // j-ième image
        {
            for (int k = 0; k < 8; k++) // k-ième pixel de la j-ième image
                res[i][j * 8 + k] = matrices[j][i][k];
        }
        res[i][8 * n] = '\0';
        // printf("%s\n", res[i]);
    }
    return res;
}

void print_mat(char **mat)
{
    for (int i = 0; i < 8; i++)
        printf("%s\n", mat[i]);
}

/**
 * Convertit une phrase en liste de ses symboles (liste de matrices 2D)
 */
char ***convert_sentence(char *sentence)
{
    int n = CHARACTER_COUNT;
    char ***matrices = malloc(sizeof(char **) * n);
    // alloue la mémoire
    for (int i = 0; i < 8; i++)
    {
        matrices[i] = malloc(sizeof(char *) * 8);
        for (int j = 0; j < 8; j++)
            matrices[i][j] = malloc(sizeof(char) * 9);
    }

    for (int i = 0; i < n; i++)
        matrices[i] = get_mat(sentence[i]);
    return matrices;
}
/**
 * Sépare la phrase s en lignes, telle que chaque ligne a au plus CHARACTER_COUNT caractères
 * en gardant les mots en entier (pas de mot sur plusieurs lignes)
 *
 * (1) CHARACTER_COUNT >= au mot le plus long
 * n: nombre de lignes
 */
char **split_sentence(char *s, int *number_of_lines)
{
    int size = strlen(s), cur_idx = 0; // index de la ligne actuelle (0<=cur_idx<CHARACTER_COUNT)
    int pos = 0;                       // index de la phrase s (0<=pos<size)
    int res_size = 1, res_idx = 0;

    // le nombre de lignes n'est pas connu à l'avance, on augmente de 1 en 1 la taille
    char **res = malloc(sizeof(char *) * res_size);
    char *cur = malloc(sizeof(char) * CHARACTER_COUNT); // Le reste de la phrase sera remplie avec des espaces

    while (pos < size)
    {
        if (cur_idx == CHARACTER_COUNT)
        {
            res_size++;
            res = realloc(res, sizeof(char *) * res_size); // alloue une ligne de plus

            // printf("pos=%d,%c\n", pos, s[pos + 1]);

            if (s[pos] != ' ')
            {
                while (cur_idx >= 0 && cur[cur_idx] != ' ') // on retourne jusqu'à retrouver le début d'un mot
                    cur[cur_idx] = ' ', cur_idx--, pos--;
                pos++; // pour skip l'espace
            }
            // pos++;

            res[res_idx] = cur;
            printf("cur=%s,\n", cur);
            cur = malloc(sizeof(char) * CHARACTER_COUNT);

            res_idx++;
            cur_idx = 0;
        }
        if (cur_idx == 0 && s[pos] == ' ')
        {
            pos++;
            continue;
        }
        cur[cur_idx] = s[pos];
        cur_idx++, pos++;
    }
    res = realloc(res, sizeof(char *) * res_size);
    while (cur_idx < CHARACTER_COUNT)
        cur[cur_idx] = ' ', cur_idx++;
    res[res_idx] = cur;
    *number_of_lines = res_size;
    printf("cur (end)=%s, cur_idx=%d\n", cur, cur_idx);
    printf("res_idx=%d,res_size=%d\n", res_idx, res_size);
    // free(cur);
    return res;
}
const int MAXSIZE = 1024;
int main(int argc, char **argv)
{
    assert(argc == 3);
    FILL_CHARACTER = argv[1][0], CHARACTER_COUNT = atoi(argv[2]);

    char *s = "MP9 Tous des Oeufs";
    int n = strlen(s);

    /**
     * vérifie (1)
     * si (1) n'est pas vérifié, on ne peut pas afficher le mot de longueur maximale
     * car l'algorithme garde les mots en entier (il ne les sectionne pas à la fin de chaque ligne)
     *
     * ex:
     * Bonj
     * our
     */
    int cur = 0, maxi = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
            maxi = max(maxi, cur), cur = 0;
        else
            cur++;
    }
    assert(CHARACTER_COUNT >= maxi); // (1)

    int number_of_lines = 0;
    char **parts = split_sentence(s, &number_of_lines);

    // printf("number_of_lines=%d\n", number_of_lines);

    for (int i = 0; i < number_of_lines; i++)
    {
        char ***sentence_in_blocks = convert_sentence(parts[i]);
        print_mat(merge_mats(sentence_in_blocks));

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                free(sentence_in_blocks[i][j]);
            free(sentence_in_blocks[i]);
        }
        free(sentence_in_blocks);
    }

    for (int i = 0; i < number_of_lines; i++)
        free(parts[i]);
    free(parts);

    // printf("%c %d\n", FILL_CHARACTER, CHARACTER_COUNT);

    // char **
    //     matrices[] = {get_mat('a'), get_mat('b'), get_mat('c'), get_mat('d')};
    // merge_mats(matrices, 4);
    // // get_mat(c);
    // int n = 5;
    // print_mat(merge_mats(convert_sentence("abcde", n), n));
}
