import matplotlib.pyplot as plt
import numpy as np


def lire_labyrinthe(fn):
    """
    Renvoie une grille de booléen correspondant au labyrinthe stocké dans le fichier fn
    """
    with open(fn) as f:
        lines = f.readlines()
        g = [[c == "X" for c in l[:-1]] for l in lines[1:]]
    n = len(g)
    m = len(g[0])
    for i in range(n):
        print(i, len(g[i]))
    return g


def lire_chemin(fn):
    """
    Renvoie le chemin stocké dans le fichier fn
    """
    with open(fn) as f:
        l = f.readlines()
    l = [map(int, s.strip().split(" ")) for s in l]
    l = [(x, y) for x, y in l]
    return l


def verifier_chemin(lab, c):
    """
    Vérifie que le chemin c est valide dans lab.
    """
    n = len(lab)
    m = len(lab[0])
    # Vérifier que le chemin est valide
    if c[0] != (0, 0) or c[-1] != (n - 1, m - 1):
        print("Mauvais départ ou mauvaise fin du chemin")
        exit(1)
    for i, j in c:
        print(i, j)
        if lab[i][j]:
            print("Le chemin passe par un mur")
            exit(1)
    for k in range(len(c) - 1):
        i1, j1 = c[k]
        i2, j2 = c[k + 1]
        if abs(i2 - i1) + abs(j2 - j1) != 1:
            print("Le chemin n'est pas bien formé")
            exit(1)


def generer_image(lab, c, fn):
    """
    Génère une image du labyrinthe lab, puis une image de lab
    avec le chemin c en rouge. fn est le nom du fichier texte
    du labyrinthe.
    Si fn = bla.txt, alors les deux fichiers image générés sont
    bla.png et bla_solution.png
    """
    # taille pixels
    if len(lab) + len(lab[0]) > 500:
        B = 1
    elif len(lab) + len(lab[0]) > 100:
        B = 4
    else:
        B = 8

    # image du labyrinthe sans chemin
    n = len(lab)
    m = len(lab[0])
    img = [
        [[0, 0, 0] if lab[i // B][j // B] else [255, 255, 255] for j in range(B * m)]
        for i in range(B * n)
    ]

    fn_img = fn.split(".")[0] + ".png"
    plt.imsave(fn_img, np.uint8(img))
    print(f"Fichier {fn_img} créé")

    # chemin en rouge
    for i, j in c:
        for k in range(B):
            for l in range(B):
                img[B * i + k][B * j + l] = [255, 0, 0]

    fn_img = fn.split(".")[0] + "_solution.png"
    plt.imsave(fn_img, np.uint8(img))
    print(f"Fichier {fn_img} créé")


##
import sys

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Préciser le fichier labyrinthe et le fichier chemin")
        exit(1)
    fn_lab = sys.argv[1]
    fn_che = sys.argv[2]
    try:
        lab = lire_labyrinthe(fn_lab)
        c = lire_chemin(fn_che)
    except Exception as e:
        print(f"Erreur de lecture des fichiers: {e}")
        exit(1)

    verifier_chemin(lab, c)
    generer_image(lab, c, fn_lab)
