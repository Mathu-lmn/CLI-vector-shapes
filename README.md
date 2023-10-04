# Projet C - Les images vectorielles

[Documentation détaillée en ligne](https://mathu-lmn.is-a.dev/documentation/index.html)

## Introduction

Ce projet a été réalisé dans le cadre du cours de C de première année à l'EFREI Paris. Il a pour but de nous faire découvrir le langage C et de nous apprendre à utiliser nos connaissances en langage C dans un objectif concret.
<br><br>
Guidés par un sujet, nous avons dû réaliser un programme permettant de créer des images vectorielles à partir de commandes entrées par l'utilisateur.

## Instructions

- Extraire le contenu de l'archive `projet.zip` dans un dossier de votre choix.
- Ouvrir le dossier dans le logiciel CLion ou tout autre logiciel qui permet de compiler du programme C.
- Compiler et exécuter le programme en entrant une des commandes suivantes : 
  - `clear` : Efface l'écran.
  - `exit` : Quitte le programme.
  - `line` `x` `y` `x2` `y2` : Créée une ligne entre les points (x, y) et (x2, y2).
  - `rectangle` `x` `y` `width` `height` : Créée un rectangle de largeur `width` et de hauteur `height` dont le coin supérieur gauche est situé au point (x, y).
  - `circle` `x` `y` `radius` : Créée un cercle de rayon `radius` dont le centre est situé au point (x, y).
  - `square` `x` `y` `side` : Créée un carré de côté `side` dont le coin supérieur gauche est situé au point (x, y).
  - `polygon` `x1` `y1` `x2` `y2` `x3` `y3` ... : Créée un polygone dont les sommets sont situés aux points (x1, y1), (x2, y2), (x3, y3), etc.
  - `plot` : Trace les figures précédemment définies.
  - `list` : Affiche la liste des figures précédemment définies sous forme de liste.
  - `delete` `id` : Supprime la figure avec l'`id` de la liste des figures précédemment définies.
  - `erase` : Supprime toutes les figures de la liste des figures précédemment définies.
  - `help` : Affiche la liste des commandes disponibles.

## Crédits

- [Mathurin Lemoine](https://github.com/Mathu-lmn)
- Chengfeng Ding