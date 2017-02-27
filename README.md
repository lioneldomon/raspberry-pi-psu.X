# Objectifs
Ce module sert à embarquer un Raspberry Pi dans un modèle réduit, et pourvoir à:
1. L'alimenter correctement: 5V, 2A
2. Prévenir des coupures de courant intempestives. Le module peut utiliser un accumulateur secondaire si jamais le principal se décharge.
3. Offrir des prises standard pour:
   * Entrée principale de courant.
   * Connexion d'un accumulateur secondaire.
   * Connexion I2C.
 
# Contraintes fonctionnelles

## Fournir en courant un Raspberry 2 model B à partir d'une alimentation principale provenante d'un accumulateur de modélisme.

## Offrir une alimentation inintérrompue; si l'accumulateur principal défaille, le module sollicite un accumulateur secondaire.

## Le module charge l'accumulateur secondaire à partir de l'alimentation principale quand nécessaire.

## Le module détecte que le raspberry s'est éteint, et peut se débrancher à son tour des deux accumulateurs.

# Contraintes techniques


