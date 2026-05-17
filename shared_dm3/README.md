# Utilisation des fichiers

## Compilation du satsolver

`ocamlc ./satsolver.ml -o satsolver`

**Tests :** <br/>
`./satsolver test`

## Génération de la formule des n-dames

`gcc ./problemes/n_dames.c ./problemes/utils.c -o n_dames`

**Utilisation :** (pour la formule des 4-dames) <br/>
`./n_dames 4`

## Recherche d'une solution

`./satsolver 4_dames.txt`

## Emploi du temps

**Génération de la formule :** <br/>

`gcc ./problemes/emploi_du_temps.c ./problemes/utils.c -o emploi_du_temps`

**Utilisation :** <br/>
`./emploi_du_temps formule.txt`

**Recherche d'une solution :**<br/>
`./satsolver formule.txt`