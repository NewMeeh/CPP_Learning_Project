# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
Comment faire pour quitter le programme ?
A quoi sert la touche 'F' ?

Pour ajouter on appuie sur `C`
Pour quitter faut appuyer sur `X` et `Q`
Pour le 11 septembre faut appuyer sur `F`

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
Quelles informations s'affichent dans la console ?

On voit l'avion atterrir ensuite il fait l'entretient puis il repart. en boucle.
On a l'information quand il atterrit quand il commence l'entretient, quand il a terminé, puis quand il décolle.

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

chacun des avions fait son chemin.

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

 - `aircraft` : Représente un avion
 - `aircraft_types` : Sert pour différencier les 3 différents types d'avions
 - `airport` : Représente l'aéroport
 - `airport_types` : Sert à différencier les différents types d'aéroports
 - `Point2D` : Point 2 dimensions
 - `Point3D` : Point 3 dimensions
 - `runway` : Représente la position de la piste d'atterrissage par rapport à l'aéroport
 - `terminal` : Représente le terminal pour l'entretient de l'avion
 - `tower` : Représente la tour de control de l'aéroport
 - `tower_sim` : Fait l'interface pour que l'utilisateur puisse controller la tour de contrôle
 - `waypoint` : Représente les points de passage
 - `WaypointType` : Les différents types de `waypoint` il peuvent etre sur le sol, dans un terminal ou dans les airs.

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

 - `Tower` : 
   - `get_instructions` : Sert à récupérer les instructions de la tour de controle.
   - `arrived_at_terminal` : Indique à la tour que l'avion est arrivé au terminal et commence l'entretient.
   
 - `Aircraft` : 
   - `get_flight_num` : Renvoie le numéro de vol de l'avion
   - `distance_to` : Renvoie la distance de l'avion à un point donné.
   - `display` : Affiche l'avion
   - `move` : Déplace l'avion

 - `Airport` : 
   - `get_tower` : Renvoie la tour de controle
   - `display` : Affiche l'aéroport.
   - `move` : Fait avancer l'entretient de chaque terminal

 - `Terminal` : 
   - `in_use` : Renvoie un booléen indiquant si le terminal est actuellement utilisé
   - `is_servicing` : Renvoie un booléen indiquant si le terminal est en train de faire l'entretient d'un avion
   - `assign_craft` : Assigne un avion au terminal
   - `start_service` : Commence l'entretient de l'avion
   - `finish_service` : Termine l'entretient de l'avion
   - `move` : Fait avancer l'entretient de l'avion


Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

La classe `Waypoint` la fonction `Tower::get_circle()` la fonction `Aircraft::move()`

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

Dans aircraft_types j'ai doublé la vitesse max par rapport aux autres.

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
