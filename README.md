# Introduction

## Objectifs
Ce module sert à embarquer un Raspberry Pi dans un modèle réduit, et pourvoir à:

* L'alimenter correctement: 5V, 2A
* Prévenir des coupures de courant intempestives. Le module peut utiliser un accumulateur secondaire si jamais le principal se décharge.
* Offrir des prises standard pour:
  * Entrée principale de courant.
  * Connexion d'un accumulateur secondaire.
  * Connexion I2C.
 
## Vue d'ensemble

# Contraintes fonctionnelles
Voici la liste des contraintes fonctionnelles répertoriées jusqu'à présent.

## Alimenter le Raspberry 2 model B à partir de l'alimentation principale

## Charger l'accumulateur secondaire à partir de l'alimentation principale.
Le module UPS surveille les niveaux de tension de sortie de l'accumulateur secondaire, et le met à la charge 

## Alimenter le Raspberry à partir de l'accumulateur secondaire.
Le module UPS offre une alimentation inintérrompue; si l'alimentation principale défaille, le module sollicite l'accumulateur secondaire.

## Détecter que le raspberry s'est éteint
Le cas échéant, le module UPS peut isoler le Rasperry de l'alimentation principale et de l'accumulateur secondaire.

## Le raspberry peut interroger le module UPS à propos des niveaux de charge
Pour que le raspberry ait une chance de s'éteindre proprement avant de manquer de courant, il peut interroger le module UPS pour récupérer:

* Le niveau de l'alimentation principale.
* Le niveau de l'accumulateur secondaire.

# Contraintes techniques

## Alimentation principale LiPo 2s
L'alimentation principale est fournie par un accumulateur de type LiPo 2S. Le module UPS:

* Supporte le niveau de charge maximum de ce type d'accumulateur.
* Ne consomme pas d'alimentation si le niveau de charge tombe en dessous du minimum.

## Pas de transfert entre l'UPS et l'alimentation
Le module UPS ne doit jamais transférer du courant vers l'alimentation principale. Celle ci étant fournie par un accumulateur de type LiPo, suivant les conditions elle pourrait réagir de façon catastrophique.

## Accumulateur secondaire Li-Ion Sony US18650VTC5A
Par exemple: http://www.conrad.ch/ce/fr/product/1499575
Le module UPS protège l'accumulateur contre:

* La surchage.
* Le courtcircuit.
* La décharge excessive.
* Dans la mesure du possible, une surabondance de cycles de charge.

## Le Raspberry PI peut se visser sur le module UPS
Le module UPS offre des fixations pour permettre de visser le Raspberry dessus.

## Les différentes prises, voyants et actionneurs sont accessibles
Le Raspberry se vissant au dessus du module, ceci implique probablement que les différents éléments de connexion se trouvent proches d'un des bords du module.

## Le Raspberry communique avec le module UPS en I2C
Parce que Raspberry supporte facilement ce protocole, et parce qu'il est prévu de l'utiliser également pour communiquer avec le module de puissance.
