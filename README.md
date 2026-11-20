# 🐣 S1 | Prog: Workshop

Template de projet pour le workshop de prog des Imac1. Vous trouverez le sujet ici: https://dsmte.github.io/Learn--cpp_programming/Workshop

# Rapport de workshop

## Exercice 1 : Ne garder que le vert

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![vert](images_rapport/keep_green_only.png)     |         

## Exercice 2 : Echanger les canaux

J'ai d'abord voulu échanger les couleurs bleu et rouge en écrivant `color.r=color.b` et `color.b=color.r`, ce qui m'a donné :

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/channels_swap_rate.png)     |    

J'ai ensuite trouvé que je devais utilisé `std::swap()`pour échanger les canaux correctement :

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/channels_swap.png)     |

## Exercice 3 : Noir et blanc

J’ai compris qu’il fallait faire la moyenne des couleurs bleu, rouge et vert puis assigner cette moyenne à chacune des trois couleurs : 
```cpp
float moyenne {(color.r + color.b + color.g)/3.f} ;
        color.r = moyenne ;
        color.b = moyenne ;
        color.g = moyenne ;
```

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/black_white.png)     |    

## Exercice 4 : Négatif

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/negative.png)     |

## Exercice 5 : Dégradé

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/degrade.png)     |

## Exercice 6 : Miroir

J’ai commencé par écrire : `x=image.width()-(x+1)` au lieu d’inverser les couleurs des pixels.
Ensuite j’ai parcouru tous les pixels de l’image sur la largeur au lieu de parcourir seulement la moitié.
Voici le résultat après avoir corrigé ces erreurs :

| Avant      |    Après     |
| ------------- | :-----------: | 
| ![og](images/logo.png)| ![channels](images_rapport/mirror.png)     |