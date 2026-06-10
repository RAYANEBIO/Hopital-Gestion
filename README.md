# 🏥 Hopital-Gestion

Une application de gestion hospitalière complète développée en C/C++ pour centraliser et optimiser les opérations essentielles d'un établissement de santé.

---

## 📋 Table des matières
- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Technologies](#technologies-utilisées)
- [Installation](#installation-et-utilisation)
- [Architecture](#architecture)
- [Utilisation](#utilisation)
- [Contribution](#contribution)
- [Licence](#licence)

---

## 📌 Description

**Hopital-Gestion** est un système d'information hospitalier (HIS) conçu pour simplifier la gestion administrative et médicale d'un hôpital. L'application offre une interface centralisée permettant de gérer efficacement :

- 👥 **Les patients** et leurs dossiers médicaux
- 👨‍⚕️ **Le personnel médical** (médecins, infirmiers, administrateurs)
- 🏢 **Les services hospitaliers** (consultations, hospitalisations, urgences)
- 📊 **Les données administratives** et statistiques

---

## 🚀 Fonctionnalités

### Gestion des Patients
- ✅ Ajout et modification des données patients
- ✅ Suivi du dossier médical complet
- ✅ Consultation historique médical
- ✅ Suppression de dossiers archivés

### Gestion du Personnel
- ✅ Enregistrement des médecins et infirmiers
- ✅ Attribution des services
- ✅ Gestion des rôles et permissions
- ✅ Accès sécurisé via authentification

### Gestion des Services
- ✅ Organisation des consultations
- ✅ Gestion des hospitalisations
- ✅ Service d'urgence intégré
- ✅ Allocation des ressources

### Persistance des Données
- ✅ Base de données SQLite (`Gestionnaire.db`)
- ✅ Export CSV des dossiers médicaux (`Dossier_Med.csv`)
- ✅ Sauvegarde automatique

---

## 🛠️ Technologies utilisées

| Technologie | Version | Utilité |
|---|---|---|
| **C** | 99.3% | Logique métier et gestion de base de données |
| **C++** | 0.7% | Interface et appels système |
| **SQLite** | 3.x | Base de données relationnelle |
| **CSV** | Standard | Format d'export des données |
| **Code::Blocks** | IDE | Environnement de développement |

---

## 📂 Installation et utilisation

### Prérequis
- GCC ou MinGW (pour compiler C/C++)
- Code::Blocks ou un IDE compatible
- SQLite 3 (inclus dans la plupart des systèmes)

### Étapes d'installation

1. **Cloner le dépôt :**
   ```bash
   git clone https://github.com/RAYANEBIO/Hopital-Gestion.git
   cd Hopital-Gestion
   ```

2. **Ouvrir le projet dans Code::Blocks :**
   ```bash
   # Ouvrir le fichier projet
   hopital\ gestion.cbp
   ```

3. **Compiler le projet :**
   - Menu : Build → Build (Ctrl+F9)
   - Ou utiliser gcc/g++ en ligne de commande :
   ```bash
   g++ -o Hopital main.cpp DatabasManager.c -lsqlite3
   ```

4. **Lancer l'application :**
   ```bash
   ./Hopital
   ```

---

## 🏗️ Architecture

```
Hopital-Gestion/
├── main.cpp                    # Point d'entrée de l'application
├── DatabasManager.c            # Gestion de la base de données
├── User.h                      # Gestion des utilisateurs
├── Ultimate_Database_Manager.h # Gestionnaire avancé de BD
├── Gestionnaire.db             # Base de données SQLite
├── Dossier_Med.csv             # Fichier d'export des dossiers
├── src/                        # Code source
├── include/                    # En-têtes (.h)
├── obj/                        # Fichiers objets compilés
├── bin/                        # Exécutables générés
└── hopital\ gestion.*          # Fichiers de configuration Code::Blocks
```

---

## 💻 Utilisation

### Authentification
L'application démarre par un écran de connexion sécurisé :
```
______Bienvenue sur la plateforme de Gestion_____
Identifiant : [________]
Mot de passe : [________]
```

Les identifiants par défaut sont disponibles dans `identifiant.txt`

### Menu Principal
Après connexion, accédez à :
- Gestion des patients
- Gestion du personnel
- Gestion des services
- Statistiques et rapports
- Paramètres utilisateur

---

## 🔧 Développement

### Ajouter une nouvelle fonctionnalité

1. Créer une nouvelle fonction dans le fichier source approprié
2. Déclarer le prototype dans le `.h` correspondant
3. Compiler et tester
4. Commiter les changements

### Format de code
- Indentation : 4 espaces
- Norme : C99/C++11
- Commentaires : Français ou Anglais (cohérent)

---

## 🤝 Contribution

Les contributions sont bienvenues ! Pour contribuer :

1. Fork le projet
2. Créer une branche (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add AmazingFeature'`)
4. Push la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

---

## 📄 Licence

Ce projet est distribué sous la licence **MIT**. Libre d'utilisation et de modification.
Consultez le fichier [LICENSE](LICENSE) pour plus de détails.

---

## 📧 Contact & Support

**Auteur :** RAYANEBIO  
**GitHub :** [@RAYANEBIO](https://github.com/RAYANEBIO)
