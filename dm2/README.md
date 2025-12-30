# Projet éditeur de musique

Transforme un fichier de format tel que décrit dans le DM et renvoie une mélodie

## Contenu:
- wav.h: fonctions pour l'écriture dans les fichiers
- waveform.h: fonctions permettant de générer différents types de sons
- sound.h/melody.h: structures et fonctions auxiliaires

## Compilation

```bash
> cd src
> gcc *.c -lm -o
```

## Utilisation

```bash
> gcc *.c -lm -o wav_writer
> ./wav_writer fichier_entrée fichier_sortie
```

## Réponses questions

- Q1. La valeur est égale à:  $U(i*t_ech)=Asin(\dfrac{2\pi*f*i}{f_ech})$
- Q3: <br/>
52 49 46 46 2e 00 00 00 57 41 56 45 66 6d 74 20 <br/>
10 00 00 00 01 00 01 00 22 56 00 00 44 ac 00 00 <br/>
02 00 10 00 64 61 74 61 0a 00 00 00 d2 03 5e 06 <br/>
ff ff 92 d2 ff 7f

- Q18: $O(n\max(l_n))$