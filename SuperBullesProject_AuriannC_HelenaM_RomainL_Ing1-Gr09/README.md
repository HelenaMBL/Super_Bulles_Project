2025-2026 – semestre 2
Julienne Palasi 1
PROJET INFORMATIQUE 2
ING1
« SUPER BULLES »
I. Présentation. ..................................... 2
II. Objectifs. ....................................... 2
III. Organisation et planning. ........................ 4
IV. Cahier des charges détaillé. ..................... 4
1. Fonctionnement du jeu de base. ................... 5
2. Extensions. ...................................... 9
3. Contraintes techniques. ......................... 11
4. IHM – interactions utilisateur .................. 12
5. Affichage - Graphismes .......................... 13
V. Travail à réaliser, rendus et modalités d’évaluation
................................................. 14
2025-2026 – semestre 2
Julienne Palasi 2
I. Présentation.
Le projet d’Informatique de ce deuxième semestre a pour
objectif de concevoir un jeu d’action de type « shoot'em
up » (« abattez-les tous ») à tir vertical.
Vous trouverez de nombreuses vidéos sur internet pour
comprendre le fonctionnement de ce type de jeu, voir par
exemple : Pang Adventures - Around the world
Le principe du jeu consiste à éliminer toutes les bulles
de chaque niveau en tirant des projectiles et en évitant
de se faire toucher : Le joueur contrôle un personnage se
déplaçant horizontalement au bas de l’écran et pouvant
tirer avec différentes armes afin de détruire des bulles
rebondissantes. Lorsqu’une bulle est touchée, elle se
divise en plusieurs bulles plus petites, rendant le jeu
progressivement de plus en plus difficile.
Tout en s’inspirant du jeu original, votre jeu devra faire
preuve d’originalité avec des règles et des défis
revisités.
Le jeu sera intégralement développé en langage C et en
mode graphique, avec la librairie graphique Allegro 4.
II. Objectifs.
A travers la mise en pratique des démarches et des
différentes notions vues durant le cours d’« Algorithmique
et Programmation structurée » du premier semestre et le
cours de « Programmation structurée avancée » de ce
deuxième semestre, ce projet vise l’acquisition de
plusieurs compétences :
2025-2026 – semestre 2
Julienne Palasi 3
• Comprendre et mener à bien les différentes étapes de
conception et développement d’un programme
informatique :
o Analyse d’un cahier des charges
o Modélisation et conception de la solution
o Réalisation : implémentation dans un langage
informatique (langage C) en utilisant une librairie
graphique (Allegro 4).
o Tests et validation
o Livraison
• Travailler en équipe.
• Planifier un projet et respecter les délais impartis.
• Renforcer la maitrise de la programmation structurée
notamment à travers l’utilisation de structures de
données dynamiques.
• Apprendre à utiliser une librairie graphique :
o Création et manipulation d’éléments graphiques
(formes, images, sprites)
o Animations
o Gestion de l’affichage et du rendu graphique
o Gestion des événements et des entrées utilisateur
(clavier, souris, manette)
o Gestion des ressources graphiques et de la mémoire
• Concevoir un programme modulaire assurant une
séparation stricte entre la logique métier (règles et
mécaniques du jeu), la gestion graphique (rendu,
animations) et l'Interface Homme-Machine (IHM) (gestion
des entrées clavier/souris).
2025-2026 – semestre 2
Julienne Palasi 4
III. Organisation et planning.
• Le projet se conduit en équipe de trois ou quatre
étudiants d’un même groupe de TD.
• Les étudiants doivent s’inscrire sur la plateforme
projet la semaine du 09/03/2026.
• Le projet démarre la semaine du 16/03/2026
(distribution du sujet) et se termine le 09/05/2026
(rendu final déposé par chaque équipe).
• Un premier rendu devra être déposé la semaine du
30/03/2026. Il présentera l’état d’avancement du projet
à mi-parcours.
• Un rapport final sera à rendre au plus tard le
10/05/2026.
• Des soutenances auront lieu la semaine du 11/05/2026.
IV. Cahier des charges détaillé.
A son lancement, le programme doit afficher une fenêtre
graphique avec un menu proposant au moins les
fonctionnalités suivantes :
1. Lire les règles du jeu
2. Commencer une nouvelle partie (à partir du 1er niveau)
3. Reprendre une partie (au dernier niveau enregistré)
4. Quitter
09/03/2026 16/03/2026 30/03/2026 04/05/2026 11/05/2026
Constitution
des équipes
Distribution
du sujet
Rendu mi-
parcours
Rendu
final
Soutenances
2025-2026 – semestre 2
Julienne Palasi 5
1. Fonctionnement du jeu de base.
A. Déroulement d’une partie
• Au lancement d’une partie, le programme demande à
l’utilisateur de saisir un pseudo.
• Une partie se compose d’au minimum 4 niveaux de difficulté
croissante.
• Pour gagner un niveau et passer au niveau suivant, il faut
éliminer toutes les bulles du niveau en un temps limité sans
se faire toucher.
• A la fin du 4ème niveau, il faut affronter un Boss.
• Pour gagner la partie, il faut atteindre le dernier niveau
et vaincre le Boss.
• Le joueur gagne la partie s’il a remporté tous les niveaux et
vaincu le Boss du dernier niveau.
• A la fin d’une partie gagnée, le programme propose une belle
animation de victoire et réaffiche le menu.
B. Déroulement d’un niveau
Chaque niveau se présente sous la forme d’un écran de jeu 2D
divisé en deux parties :
• La zone de jeu. C’est dans cette zone que se déplacera le
personnage et que se déplaceront les bulles à éliminer.
• La zone d’informations. On y retrouve au minimum :
o Le pseudo du joueur
o Le score (voir plus loin pour la description du système
de points)
o Le décompte du temps
2025-2026 – semestre 2
Julienne Palasi 6
1. Démarrage d’un niveau
Au démarrage d’un niveau :
• Le personnage apparait en bas au centre de la zone
de jeu.
• Un décompte de 3 ou 4 secondes laisse le temps au
joueur de se mettre en condition.
• Dans certains niveaux, les bulles sont prépositionnées dans
la zone de jeu ; dans d’autres, elles n’apparaissent qu’à la
fin du décompte initial.
2. Déplacement du personnage
• Le déplacement du personnage est contrôlé à l’aide des
flèches du clavier.
• Le personnage est bloqué sur les bords de la zone de jeu.
• Si le personnage est touché par une bulle, il meurt (fin du
niveau).
3. Armement du personnage
• Au démarrage d’un niveau, le personnage
dispose d’une arme de base à tir simple :
elle permet d’effectuer un seul tir à la
fois. C’est un tir direct vers le haut,
avec une vitesse constante du projectile.
• A partir du deuxième niveau, le
personnage peut acquérir temporairement
des armes plus évoluées. Ces armes
peuvent tomber au sol lors de la
division ou l’élimination de certaines bulles. Le personnage
doit passer dessus pour les récupérer. Il ne peut les
utiliser que pendant un temps limité. Elles permettent par
exemple d’enchainer plus rapidement les tirs, de faire
Arme présente dans une
bulle. Certaines armes
peuvent être cachées et
n’apparaitre que quand la
bulle est détruite.
2025-2026 – semestre 2
Julienne Palasi 7
plusieurs tirs simultanément (tirs
multiples) ou de provoquer des
explosions.
4. Comportement des bulles
a. Mouvements des bulles
• Les bulles se déplacent
automatiquement de manière continue
et fluide à l’écran selon différentes
trajectoires combinant déplacements
verticaux, horizontaux et diagonaux.
• Elles rebondissent sur les bords de
la zone de jeu ou sur des obstacles insérés dans le décor.
• Le déplacement des bulles doit donner une impression de
dynamisme et de légèreté simulant les effets de mouvements
physiques (effets de gravité et de rebonds impliquant des
changements de vitesse et de direction).
b. Division et élimination des bulles
• Lorsqu’une bulle est touchée par un
projectile, elle se divise en bulles
de taille inférieure dans la limite
d’une taille minimum à laquelle la
bulle est détruite et disparait.
• Les bulles issues de la division
adoptent des trajectoires
divergentes avec changement
immédiat de direction et de
vitesse.
c. Lancement d’éclairs
A partir du troisième niveau, certaines bulles lancent des
éclairs. Ces éclairs tombent verticalement. Si elles
Quand elles sont touchées, les
bulles se divisent en bulles
plus petites
Arme évoluée (tirs
multiples) qui tombent
après l’élimination d’une
bulle.
2025-2026 – semestre 2
Julienne Palasi 8
touchent le personnage, il est foudroyé et le niveau est
perdu.
5. Le Boss du dernier niveau
Pour gagner le dernier niveau,
il faut affronter un boss.
Vous pouvez laisser libre
cours à votre imagination pour
personnaliser le comportement
du boss mais vous devez
respecter les contraintes
suivantes :
• Pour vaincre le Boss, il faut le toucher un certain nombre
de fois (à définir pour garantir la jouabilité du jeu).
• Plus il est touché, plus il se déplace rapidement.
• Le Boss laisse aussi échapper des bulles qu’il faut éliminer
et éviter.
• Si le personnage est touché par le Boss, il meurt.
6. Difficultés des niveaux
Les niveaux sont de difficultés croissantes. La difficulté
augmente par le nombre et le comportement des bulles
(vitesses, trajectoires, nombre de divisions, lancement
d’éclairs au troisième niveau …)
7. Fin d’un niveau
Echec : le joueur perd le niveau si :
• Il est touché par une bulle ou par un éclair ou par le boss
• Il n’a pas éliminé toutes les bulles dans le temps imparti
Victoire : si le joueur a éliminé toutes les bulles dans avoir
été touché, il peut passer au niveau suivant.
2025-2026 – semestre 2
Julienne Palasi 9
A chaque fois qu’un niveau se termine, qu’il soit gagné ou
perdu, le joueur peut :
• Quitter le programme
• Sauvegarder la partie (son pseudo et le numéro du dernier
niveau gagné sera sauvegardé).
• Continuer à jouer (recommencer le niveau s’il a été perdu
ou passer au niveau suivant).
• Revenir au menu.
C. Sauvegarde et chargement
Le programme permet à un joueur de sauvegarder son dernier
niveau atteint.
Plusieurs parties peuvent être sauvegardées dans un même
fichier texte.
Au lancement du programme, le menu propose de reprendre une
partie sauvegardée en demandant au joueur de saisir son
pseudo.
2. Extensions.
En plus du jeu de base, vous devez proposer au moins une
extension au choix parmi celles décrites ci-dessous. Vous
ne pouvez mettre en place ces extensions que si le jeu de
base avec les contraintes décrites précédemment est
fonctionnel.
• Système de scores
Un système de scores permet d’évaluer la performance des
joueurs, d’encourager à rejouer et de proposer un défi
secondaire complémentaire à la réussite du niveau.
Les points peuvent être obtenus en fonction du temps de
réalisation des niveaux, de la rapidité d’élimination des
bulles après leur apparition, grâce à des objets bonus qui
apparaissent à certains moments …
2025-2026 – semestre 2
Julienne Palasi 10
Si vous mettez en place un système de scores, il
faudrait aussi prévoir une classification et une
sauvegarde des meilleurs scores.
• Niveaux supplémentaires proposant une évolution
significative des mécaniques de jeu par rapport
aux 4 niveaux du jeu de base, par exemples :
o Des obstacles avec déplacement 2D du personnage.
o Des bulles aux comportements variés : balles plus
lourdes avec rebonds plus bas, bulles plus rapides,
bulles indestructibles pendant un temps ou nécessitant
d’être touchées plusieurs fois …
o Des Bonus et/ou des Malus : invincibilité temporaire du
personnage, ralentissement global voir immobilisation
totale des bulles pendant un certain temps,
ralentissement de la vitesse de déplacement du
personnage …
• Mode 2 joueurs.
Deux joueurs jouent en même
temps sur la même zone de jeu.
Il y a deux approches
possibles :
o Mode collaboratif : les
deux joueurs s’entraident
pour éliminer toutes les bulles.
o Mode duel : Chaque joueur a un score individuel
calculé en fonction du nombre de bulles qu’il a
détruit. Un joueur peut gêner l’autre. Le dernier
survivant ou celui qui le plus haut score gagne.
Le mode duel est sans doute plus complexe à concevoir que
le mode coopératif.
Mode deux joueurs
2025-2026 – semestre 2
Julienne Palasi 11
! Ces extensions ne doivent pas apparaitre au 4 premiers
niveaux qui doivent respecter strictement le cahier des
charges du jeu de base !
Vous pouvez ensuite laisser libre cours à votre
imagination pour proposer des niveaux supplémentaires avec
d’autres extensions originales et stimulantes.
3. Contraintes techniques.
• Langage : C.
• Librairie graphique Allegro 4.
• Programmation modulaire
Le programme devra être découpé en plusieurs modules
clairement identifiés, organisés par responsabilités
fonctionnelles (par exemple : logique du jeu, gestion des
entités (joueurs, bulles, …, affichage, entrées
utilisateur, ressources).
Chaque module devra :
o Jouer un rôle clairement défini
o Exposer une interface via des fichiers .h
o Limiter ses dépendances avec les autres modules
• Programmation structurée avancée :
Le projet devra mettre en œuvre :
o Des structures de données adaptées
o Une gestion dynamique de la mémoire pour les éléments de
taille variable (bulles, projectiles, bonus …)
• Séparation stricte entre la logique métier,
la gestion graphique et l’IHM.
Une séparation stricte devra être respectée entre :
o La logique métier (règles, mécaniques de jeu, états)
o La gestion graphique (affichage, animations, rendu)
o L’IHM (gestion des entrées clavier/souris)
2025-2026 – semestre 2
Julienne Palasi 12
La logique métier ne devrait contenir aucune dépendance
directe à la librairie graphique.
Il devrait être possible, en théorie, de changer de librairie
graphique sans modifier les règles du jeu.
• Adaptabilité de l’affichage
L’interface graphique devra être conçue de manière
adaptable (responsive) : le positionnement et la taille
des éléments (zone d’affichage, zone d’interactions,
entités) devront être calculés à partir des dimensions de
l’écran (SCREEN_W et SCREEN_H) et non à l’aide de valeurs
fixes.
Cette contrainte vise à améliorer la maintenabilité et
l’évolutivité du programme.
4. IHM – interactions utilisateur
L’Interface Homme-Machine devra permettre une interaction
fluide et intuitive avec le jeu.
Elle comprendra au minimum :
• La navigation dans les menus et la validation des
choix.
Les menus devront proposer une interaction par clavier
et/ou par clics de souris, impliquant la gestion de
zones interactives à l’écran.
• La saisie du pseudo du joueur
• Le contrôle du personnage :
o Déplacements
o Tirs
• Les interactions spécifiques aux extensions (mode 2
joueurs, bonus, etc…)
2025-2026 – semestre 2
Julienne Palasi 13
La gestion des entrées utilisateur devra :
• Être centralisée dans un ou plusieurs modules dédiés
• Être découplée de la logique métier
• Permettre une évolution facile (par exemple pour
l’ajout d’un second joueur)
Une attention particulière sera portée à l’ergonomie du
jeu :
• Réactivité des contrôles
• Correspondance claire entre les actions de
l’utilisateur et leurs effets à l’écran
• Lisibilité suffisante des informations et des
interactions possibles.
5. Affichage - Graphismes
L’affichage se fera intégralement en mode graphique avec
la librairie Allegro 4.
A. Choix et gestion des images
Les images pourront être récupérées sur internet (attention
aux copyright), générées par IA, ou créées par vos soins.
Ne passez pas trop de temps sur la récupération ou la
création des images, ce n’est pas l’objectif du projet et
la qualité des images présentées ne rentre pas en compte
dans les critères d’évaluation.
Chaque niveau a un décor de fond. Les entités
(personnage(s), bulles, projectiles, boss, bonus …) devront
être représentées par des sprites.
B. Animations
Le jeu devra proposer des animations fluides au minimum
pour :
• Les déplacements du personnage
• Les tirs et explosions
• Les écrans de victoire ou de défaite
2025-2026 – semestre 2
Julienne Palasi 14
Les animations devront :
• Être synchronisées avec le temps
• Donner une impression de dynamisme
• Respecter une cadence d’affichage stable
V. Travail à réaliser, rendus et
modalités d’évaluation
Vous devez appliquer la démarche de conception et de
développement expliquée et vue en cours. Après avoir lu
attentivement et étudié le cahier des charges (n’hésitez
pas à poser des questions sur le CDC et à demander des
précisions sur certains aspects), vous devez réfléchir
pour concevoir une solution avant de passer aux phases de
codage et de tests.
Le guide pas à pas ci-dessous constitue une recommandation
méthodologique. Les équipes sont libres d’adapter leur
démarche tant que les contraintes du cahier des charges
sont respectées.
A. Guide pas à pas
1. Conception – logique métier
• Identifier et représenter les données.
o Identifier les données principales
o Modéliser les entités (personnage, bulles …)
o Définir les structures de données
• Décrire le fonctionnement du programme
o Logigramme général
o Logigramme d’une partie
o Logigramme d’un niveau
• Identifier les principaux traitements
• Mettre en place le découpage modulaire
2025-2026 – semestre 2
Julienne Palasi 15
2. Conception – Interface graphique
• Faire des maquettes de l’interface graphique
• Etablir un story-board.
Dans un premier temps, les entités seront représentées par
des formes géométriques simples : cercles pour les bulles,
rectangles pour le personnage, segments pour les
projectiles. Cette approche permettra de mettre en place,
tester, déboguer, et valider les principaux mécanismes de
jeu (déplacements, collisions …) indépendamment du rendu
graphique final.
3. Implémentation et tests
Commencez par implémenter les fonctionnalités de base et
testez-les au fur et à mesure dans une boucle de jeu avec
gestion du temps :
A. Gestion du temps et des déplacements
• Déplacement du personnage dans la zone de jeu
• Tirs
• Déplacement automatique des bulles
B. Détection et gestion des collisions
• Collisions bulle / mur
• Collisions projectile / bulle
• Collisions bulle / personnage
Pour la détection des collisions, des approches simples
basées sur des formes géométriques régulières (cercles,
rectangles) ou des boîtes englobantes (bounding boxes)
avec tests de coordonnées sont suffisantes et
recommandées.
2025-2026 – semestre 2
Julienne Palasi 16
L’utilisation de bitmaps de collision peut être envisagée
comme une approche avancée, mais n’est pas exigée.
L’avantage serait de permettre un rendu graphique plus
précis et plus réaliste en particulier pour les formes
complexes, mais l’inconvénient est une forte dépendance
aux graphismes, et une séparation moins nette entre
logique métier et affichage.
C. Mise en place d’une première version du programme
À ce stade, le jeu de base doit être fonctionnel, même
avec des graphismes rudimentaires.
D. Enrichissement graphique et animations
Les formes simples peuvent maintenant être remplacées par
des sprites. Vous pouvez mettre en place les décors, les
animations et des effets visuels.
Idéalement, cette étape doit se faire sans modifier la
logique métier, uniquement la couche graphique.
E. Extensions et améliorations
Une fois le jeu de base finalisé, vous pourrez vous
atteler à :
• L’ajout des extensions choisies
• L’amélioration de l’ergonomie
• L’équilibrage de la difficulté
2025-2026 – semestre 2
Julienne Palasi 17
B. Les rendus attendus
Le rapport de mi-parcours
Dans le premier rendu à mi-parcours (semaine du
30/03/2026) vous présenterez votre démarche de conception
et la solution proposée pour le jeu de base :
1. Analyse et conception générale (couche métier)
• Analyse chronologique descendante (ACD), de préférence
sous forme de logigramme, montrant le fonctionnement
global du programme.
• Logigrammes détaillant le fonctionnement d’une partie et
d’un niveau.
• Identification des données, modélisation des entités et
choix des structures de données.
• Découpage modulaire
2. Maquettes de l’interface graphique et story-board.
Faire des schémas légendés pour représenter les
aspects successifs de la fenêtre graphiques avec ses
différentes zones et composants.
3. Analyse et conception détaillée
• Découpage en sous-programmes et répartition des sous-
programmes dans les différents modules.
• Pour chaque sous-programme, préciser ses données en
entrée, ses résultats en sortie, et indiquer son
prototype commenté.
• Détailler les algorithmes les plus complexes sous-forme
de logigrammes.
• Graphe d’appels montrant comment l’enchainement des
appels de sous-programmes permettra de réaliser les
fonctionnalités du jeu.
• Gestion des déplacements et des collisions : Expliquer
vos solutions à l’aide de schémas.
2025-2026 – semestre 2
Julienne Palasi 18
4. Plan de tests
Présentation du plan de tests (sous forme de tableau)
prévu pour valider le bon fonctionnement du programme
et de ses principales fonctionnalités.
5. Planning prévisionnel et répartition des tâches au
sein de l’équipe.
Le rapport final
Dans le rapport final (à rendre la semaine du 04/05/2026)
vous devrez :
• Donner le planning réellement suivi et la répartition
réelle des tâches réalisées par chacun.
• Indiquer et expliquer les éventuelles modifications
apportées à la solution proposée dans le rapport de mi-
parcours.
• Montrer le contenu de vos fichiers header.
• Faire le graphe d’appels final du programme.
• Montrer les tests réalisés et les résultats obtenus à
l’aide de captures d’écran commentées.
• Rédiger des bilans individuels et collectifs sur le
déroulement du projet et le travail réalisé.
• Préciser vos sources et la part d’aide (humaine ou
artificielle) dont vous avez bénéficiée.
2025-2026 – semestre 2
Julienne Palasi 19
Le programme
Vous devez rendre le dossier complet contenant les
fichiers headers, les fichiers sources, et tous les
fichiers contenant les ressources (images …) nécessaires à
l’exécution du programme.
C. Modalités d’évaluation
• Rapports
• Soutenances (semaines du 11/05/2026 et 18/05/2026)
L’évaluation du projet tiendra compte de votre travail
collectif et individuel.
Travail collectif :
• Qualité des rendus et présentations.
• Pertinence et rigueur de la démarche de conception.
• Qualité du code (sur la forme : commentaires et
indentations ; sur le fond : découpage modulaire,
séparation couche métier, affichage graphique et IHM,
choix des structures de données, gestion dynamique de
la mémoire).
• Respect du cahier des charges
• Créativité et originalité de vos extensions dans la
limite des libertés offertes par le cahier des
charges.
• Ergonomie et jouabilité du jeu final.
• Fluidité de l’affichage graphique
• Qualité des animations
2025-2026 – semestre 2
Julienne Palasi 20
Travail individuel :
• Implication dans le projet, importances et
difficultés des tâches réalisées.
• Qualité des réponses individuelles fournies au jury
lors des soutenances.
Bon projet !
Julienne Palasi, Jean-Pierre Segado, Baligh Mnassri et
toute l’équipe enseignante.
