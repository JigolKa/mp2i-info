# Projet éditeur de musique

Transforme un fichier de format tel que décrit dans le DM et renvoie une mélodie

## Fonctionnalité supplémentaire

J'ai choisi d'implémenter la fonctionnalité pour renverser un son. <br>
J'ai d'abord du implementer une fonction pour le contenu binaire d'un fichier .wav et le transformer en `sound_t*`, et ensuite créer une fonction pour renverser ses samples

## Contenu:
- src/wav.h: fonctions pour l'écriture dans les fichiers
- src/waveform.h: fonctions permettant de générer différents types de sons
- src/sound.h, src/melody.h: structures et fonctions auxiliaires
- extra/read_wav.h: fonctions dédiées à la fonctionnalité supplémentaire

## Compilation

```bash
> gcc src/*.c extra/*.c -lm -o wav_writer
```

## Utilisation

```bash
> ./wav_writer <mode> <fichier_entrée> <fichier_sortie>
```

Pour utiliser le programme normalement, il faut l'utiliser avec mode=1
Pour utiliser la fonctionnalité supplémentaire, on doit l'utiliser avec mode=1, et le fichier d'entrée doit être au format .wav
