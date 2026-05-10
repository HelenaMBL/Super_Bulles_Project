# 🫧 Super Bulles – Projet Informatique 2 (ING1)

> Projet de jeu d'action de type **shoot'em up à tir vertical**, développé en **C** avec la librairie graphique **Allegro 4**.

---

## 📋 Sommaire

- [Présentation](#-présentation)
- [Objectifs](#-objectifs)
- [Organisation & Planning](#-organisation--planning)
- [Cahier des charges](#-cahier-des-charges)
    - [Menu principal](#menu-principal)
    - [Fonctionnement du jeu](#fonctionnement-du-jeu)
    - [Extensions](#extensions)
    - [Contraintes techniques](#contraintes-techniques)
    - [IHM](#ihm--interactions-utilisateur)
    - [Affichage & Graphismes](#affichage--graphismes)
- [Rendus attendus](#-rendus-attendus)
- [Modalités d'évaluation](#-modalités-dévaluation)

---

## 🎮 Présentation

Le principe du jeu consiste à éliminer toutes les bulles de chaque niveau en tirant des projectiles et en évitant de se faire toucher.

- Le joueur contrôle un personnage se déplaçant **horizontalement** en bas de l'écran
- Il peut tirer avec différentes armes pour détruire des **bulles rebondissantes**
- Lorsqu'une bulle est touchée, elle se **divise en bulles plus petites**, rendant le jeu progressivement plus difficile

> Inspiré du jeu *Pang Adventures*, mais avec des règles et défis revisités.

---

## 🎯 Objectifs

- Analyser un cahier des charges et concevoir une solution
- Implémenter un programme en **C** avec **Allegro 4**
- Travailler en équipe et respecter les délais
- Maîtriser les structures de données dynamiques
- Utiliser une librairie graphique (sprites, animations, événements)
- Respecter une **séparation stricte** entre logique métier, affichage et IHM

---

## 📅 Organisation & Planning

| Date | Étape |
|------|-------|
| 09/03/2026 | Constitution des équipes |
| 16/03/2026 | Distribution du sujet |
| 30/03/2026 | **Rendu mi-parcours** |
| 04/05/2026 | **Rendu final** |
| 11/05/2026 | Soutenances |

> Équipes de **3 ou 4 étudiants** d'un même groupe de TD.

---

## 📄 Cahier des charges

### Menu principal

Au lancement, le programme affiche un menu avec :

1. Lire les règles du jeu
2. Commencer une nouvelle partie
3. Reprendre une partie (dernier niveau sauvegardé)
4. Quitter

---

### Fonctionnement du jeu

#### Déroulement d'une partie

- Le joueur saisit un **pseudo** au démarrage
- La partie comporte **au minimum 4 niveaux** de difficulté croissante
- Pour passer au niveau suivant : éliminer toutes les bulles **dans le temps imparti** sans se faire toucher
- Le **4ème niveau** se conclut par un **Boss**
- Animation de victoire à la fin d'une partie gagnée

#### Déroulement d'un niveau

L'écran est divisé en deux zones :

- **Zone de jeu** : déplacements du personnage et des bulles
- **Zone d'informations** : pseudo, score, décompte du temps

#### Démarrage d'un niveau

- Le personnage apparaît **en bas au centre**
- Décompte de 3-4 secondes avant le début
- Les bulles peuvent être pré-positionnées ou apparaître après le décompte

#### Déplacement du personnage

- Contrôle via les **flèches du clavier**
- Bloqué sur les bords de la zone de jeu
- Touché par une bulle → **mort** (fin du niveau)

#### Armement

| Niveau | Arme disponible |
|--------|----------------|
| 1 | Tir simple vers le haut (un seul tir à la fois) |
| 2+ | Armes évoluées temporaires (tirs multiples, explosions…) récupérées au sol |

#### Comportement des bulles

- Déplacement **automatique et continu** (trajectoires verticales, horizontales, diagonales)
- **Rebondissent** sur les bords et obstacles
- Simulent des effets de **gravité et de rebonds**

**Division des bulles :**
- Touchée par un projectile → se divise en bulles plus petites
- En dessous d'une taille minimum → **détruite**
- Les bulles issues de la division adoptent des trajectoires **divergentes**

**Éclairs (niveau 3+) :**
- Certaines bulles lancent des éclairs verticaux
- Toucher le personnage → foudroiement → niveau perdu

#### Le Boss (dernier niveau)

- Nécessite **plusieurs hits** pour être vaincu
- Accélère à chaque fois qu'il est touché
- Lâche des bulles supplémentaires
- Toucher le personnage → mort

#### Fin d'un niveau

**Échec si :**
- Touché par une bulle, un éclair ou le boss
- Temps écoulé sans avoir éliminé toutes les bulles

**Victoire si :**
- Toutes les bulles éliminées dans le temps imparti

**À chaque fin de niveau, le joueur peut :**
- Quitter le programme
- Sauvegarder la partie
- Continuer (recommencer ou niveau suivant)
- Revenir au menu

#### Sauvegarde

- Sauvegarde du pseudo et du dernier niveau atteint dans un **fichier texte**
- Plusieurs parties sauvegardées dans le même fichier
- Reprise possible depuis le menu via le pseudo

---

### Extensions

> ⚠️ Les extensions ne doivent pas apparaître dans les 4 premiers niveaux.

Choisir **au moins une** extension parmi :

#### 🏆 Système de scores
- Points selon le temps, la rapidité d'élimination, les bonus…
- Classement et sauvegarde des meilleurs scores

#### 🗺️ Niveaux supplémentaires
- Obstacles avec déplacement 2D
- Bulles aux comportements variés (lourdes, rapides, indestructibles temporairement…)
- Bonus/Malus (invincibilité, ralentissement des bulles…)

#### 👥 Mode 2 joueurs
- **Mode collaboratif** : les deux joueurs s'entraident
- **Mode duel** : score individuel, le meilleur score ou dernier survivant gagne

---

### Contraintes techniques

- **Langage** : C
- **Librairie graphique** : Allegro 4
- **Programmation modulaire** : modules séparés par responsabilité (logique, affichage, IHM, entités…)
- **Programmation structurée avancée** : structures de données adaptées, gestion dynamique de la mémoire (`malloc`/`free`)
- **Séparation stricte** logique métier / affichage / IHM
    - La logique métier ne doit contenir **aucune dépendance à Allegro**
    - Il doit être possible de changer de librairie graphique sans toucher aux règles du jeu
- **Affichage adaptatif** : positions et tailles calculées depuis `SCREEN_W` et `SCREEN_H`, pas de valeurs fixes

---

### IHM – Interactions utilisateur

- Navigation dans les menus au **clavier et/ou à la souris**
- Saisie du pseudo
- Contrôle du personnage (déplacements + tirs)
- Gestion des entrées **centralisée** dans des modules dédiés et **découplée** de la logique métier

---

### Affichage & Graphismes

- Affichage **100% graphique** avec Allegro 4
- Chaque niveau a un **décor de fond**
- Les entités sont représentées par des **sprites**

**Animations obligatoires :**
- Déplacements du personnage
- Tirs et explosions
- Écrans de victoire / défaite

Les animations doivent être **synchronisées avec le temps** et respecter une **cadence d'affichage stable**.

---

## 📦 Rendus attendus

### Rapport de mi-parcours *(semaine du 30/03/2026)*

1. Analyse et conception générale (logigrammes, ACD)
2. Maquettes de l'interface graphique et story-board
3. Analyse détaillée (prototypes, algorithmes, graphe d'appels)
4. Plan de tests
5. Planning prévisionnel et répartition des tâches

### Rapport final *(semaine du 04/05/2026)*

- Planning réel et répartition des tâches
- Modifications par rapport au mi-parcours
- Contenu des fichiers `.h`
- Graphe d'appels final
- Tests réalisés avec captures d'écran commentées
- Bilans individuels et collectifs
- Sources et part d'aide utilisée (humaine ou IA)

### Programme

Dossier complet contenant :
- Fichiers sources (`.c`) et headers (`.h`)
- Toutes les ressources nécessaires (images…)

---

## 📊 Modalités d'évaluation

### Travail collectif
- Qualité des rendus et présentations
- Rigueur de la démarche de conception
- Qualité du code (commentaires, indentation, modularité, mémoire)
- Respect du cahier des charges
- Créativité des extensions
- Ergonomie, jouabilité, fluidité et qualité des animations

### Travail individuel
- Implication et importance des tâches réalisées
- Qualité des réponses lors des soutenances

---

> 📌 *Projet encadré par Julienne Palasi, Jean-Pierre Segado, Baligh Mnassri et l'équipe enseignante – 2025/2026 Semestre 2*