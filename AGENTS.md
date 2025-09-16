# AGENTS.md

Guide pour les agents de codage IA travaillant sur ce projet Minecraft Clone.

## 📋 Vue d'ensemble du projet

Clone de Minecraft développé en C++ avec une architecture modulaire séparant la logique de jeu (Game) du rendu (Renderer).

**Technologies principales :**
- C++17 avec CMake
- OpenGL + GLEW + GLFW pour le rendu
- ImGui pour l'interface utilisateur
- STB pour le chargement d'images
- vcpkg pour la gestion des dépendances

## 🚀 Commandes de configuration

### Installation et build
```bash
# Prérequis : vcpkg installé et configuré
# Variable d'environnement CMAKE_TOOLCHAIN_FILE doit pointer vers vcpkg.cmake

# Build debug
cmake -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debug

# Build release
cmake -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release

# Exécution
./cmake-build-debug/mc.exe  # ou cmake-build-release/mc.exe
```

### Tests et validation
```bash
# Compilation test
cmake --build cmake-build-debug --config Debug

# Nettoyage
cmake --build cmake-build-debug --target clean

# Rebuild complet
cmake --build cmake-build-debug --target rebuild_cache
```

## 📁 Architecture et structure

### Principe de séparation STRICT
- **Game/** : Logique métier, état du monde, AUCUN appel OpenGL
- **Renderer/** : Rendu graphique uniquement, AUCUNE logique de jeu
- **Communication unidirectionnelle** : Game → RenderData → Renderer

### Structure des dossiers sources
```
src/
├── main.cpp                           # Point d'entrée
├── Game/                              # Logique de jeu PURE
│   ├── Game.cpp/.h                    # Boucle principale
│   ├── SharedPropertiesGame.h         # Propriétés partagées
│   ├── World/                         # État du monde
│   │   ├── World.cpp/.h
│   │   ├── PhysicsEngine.h (abstract)
│   │   ├── ChunkManager/              # Gestion des chunks
│   │   │   ├── ChunkManager.cpp/.h
│   │   │   └── Chunk/                 # Blocs et chunks
│   │   │       ├── Block.h (abstract)
│   │   │       ├── Block.cpp
│   │   │       ├── Blocks.cpp/.h
│   │   │       └── Textures.cpp/.h
│   │   └── EntityManager/             # Gestion des entités
│   │       ├── EntityManager.cpp/.h
│   │       └── Entity/                # Classes d'entités
│   │           ├── Entity.h (abstract)
│   │           ├── Player.h
│   │           ├── Mob.h
│   │           └── ItemEntity.h
│   └── GameSystems/                   # Systèmes transversaux
│       ├── InputSystem.h (abstract)
│       ├── UpdateSystem.h (abstract)
│       ├── SaveSystem.h (abstract)
│       └── CameraController.cpp/.h
└── Renderer/                          # Moteur de rendu PURE
    ├── SharedPropertiesEngine.h       # Propriétés partagées
    ├── Window/                        # Gestion fenêtre
    │   ├── Window.cpp/.h
    │   └── InputHandler.h (abstract)
    ├── Renderer3D/                    # Pipeline 3D
    │   ├── Renderer.cpp/.h
    │   ├── Camera/Camera.cpp/.h
    │   ├── SceneGraph/                # Graphe de scène
    │   │   ├── Mesh.cpp/.h
    │   │   └── RenderNode/            # Nœuds de rendu
    │   │       ├── RenderNode.h (abstract)
    │   │       ├── MeshNode.h
    │   │       └── LightNode.h
    │   └── RenderPipeline/            # Pipeline de rendu
    │       ├── Shader.cpp/.h
    │       ├── Texture.cpp/.h
    │       ├── ShaderManager.h (abstract)
    │       ├── TextureManager.h (abstract)
    │       ├── Material.h (abstract)
    │       └── BufferManager/         # Gestion des buffers
    │           ├── BufferManager.h (abstract)
    │           └── Buffer/            # Types de buffers
    │               ├── Buffer.h (abstract)
    │               ├── VertexBuffer.h
    │               ├── IndexBuffer.h
    │               ├── UniformBuffer.h
    │               └── Framebuffer.h
    └── Renderer2D/                    # Interface utilisateur
        ├── FontRenderer.h (abstract)
        └── UIElement/                 # Éléments UI
            ├── UIElement.h (abstract)
            ├── UIButton.h
            ├── UILabel.h
            └── UISlider.h
```

## 📝 Gestion de version et commits

### Commits Git obligatoires
**Toutes les modifications doivent être commitées sur Git.**

### Format des messages de commit
Utiliser les **Conventional Commits** selon le standard de [conventionalcommits.org](https://conventionalcommits.org)

#### Format requis :
```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

#### Types principaux :
- `feat`: nouvelle fonctionnalité
- `fix`: correction de bug
- `docs`: modifications de documentation
- `style`: formatage, espaces, etc. (pas de changement de code)
- `refactor`: refactorisation sans ajout de fonctionnalité ni correction
- `test`: ajout ou modification de tests
- `chore`: tâches de maintenance (build, dépendances, etc.)
- `perf`: amélioration de performance
- `ci`: modifications de CI/CD

#### Exemples :
```bash
feat(renderer): add texture loading system
fix(game): resolve chunk loading memory leak
docs(readme): update build instructions
refactor(world): extract chunk generation logic
chore(deps): update vcpkg dependencies
```

#### Règles importantes :
- Utiliser l'impératif ("add" pas "added")
- Pas de point final dans la description
- Description en anglais de préférence
- Corps du commit pour expliquer le "pourquoi" si nécessaire
```

## 💻 Style de code et conventions

### Standards C++
- **C++17** strict, pas d'extensions
- **RAII** pour la gestion des ressources
- **Smart pointers** (std::unique_ptr, std::shared_ptr)
- **Const-correctness** systématique
- **#pragma once** pour les headers

### Conventions de nommage
```cpp
// Classes : PascalCase
class ChunkManager {};

// Méthodes et variables : camelCase
void updateChunks();
float deltaTime;

// Constantes : UPPER_SNAKE_CASE
const int MAX_CHUNKS = 100;

// Classes abstraites : commentaire (abstract)
class Entity {  // (abstract)
    virtual void update() = 0;
};
```

### Commentaires et documentation
- **Pas de commentaires inutiles** : Ne pas ajouter de commentaires explicatifs en fin de ligne lors des corrections
- **Exemple à éviter** : `#include "Game/World.h"  // ✅ Include absolu corrigé`
- **Préférer** : `#include "Game/World.h"`
- **Commentaires utiles** : Seulement pour expliquer la logique complexe ou les algorithmes
- **Documentation** : Utiliser des commentaires de documentation pour les interfaces publiques

### Organisation des includes
```cpp
// 1. Header correspondant (si .cpp)
#include "MyClass.h"

// 2. Headers standard C++
#include <vector>
#include <memory>

// 3. Headers externes (OpenGL, GLFW, etc.)
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 4. Headers du projet
#include "Game/World/World.h"
```

## 🔧 Instructions de développement

### Ajout de nouveaux fichiers
- **AUCUNE modification** du CMakeLists.txt nécessaire
- Le système `file(GLOB_RECURSE)` collecte automatiquement tous les `.cpp` et `.h`
- Placez les fichiers dans la structure appropriée (Game/ ou Renderer/)

### Création de nouvelles classes
1. **Abstraites** : Héritez des classes de base existantes (Entity, Block, etc.)
2. **Concrètes** : Implémentez toutes les méthodes abstraites
3. **Managers** : Suivez le pattern des classes existantes (ChunkManager, EntityManager)

### Communication Game ↔ Renderer (RÈGLE ABSOLUE)
```cpp
// ❌ INTERDIT dans Game/
#include <GL/glew.h>        // Aucun header OpenGL
glDrawElements(...);        // Aucun appel OpenGL
glGenBuffers(...);          // Aucune fonction OpenGL

// ✅ CORRECT : données pures uniquement
struct RenderData {
    std::vector<MeshInstance> meshes;
    CameraData camera;
    std::vector<LightData> lights;
    UIData userInterface;
};

// ❌ INTERDIT dans Renderer/
if (player.health < 10) {} // Aucune logique de jeu
player.takeDamage(5);       // Aucune modification d'état de jeu

// ✅ CORRECT : rendu pur uniquement
void renderMesh(const MeshData& mesh, const Matrix4& transform);
```

### Tests et validation
- **Compilation** : Testez TOUJOURS les deux configurations (Debug/Release)
- **Erreurs** : Vérifiez les logs de compilation et corrigez immédiatement
- **Architecture** : Respectez STRICTEMENT la séparation Game/Renderer
- **Performance** : Préférez les optimisations dans le Renderer

## 🎯 Instructions spécifiques par domaine

### Côté Game (Logique pure)
- **AUCUN include** de headers OpenGL (GL/glew.h, GLFW/glfw3.h, etc.)
- **Logique métier uniquement** : calculs, état du monde, règles de jeu
- **Données de sortie** : structures simples pour le Renderer
- **Performance** : optimisations algorithmiques, structures de données
- **Physique** : collisions, gravité, mouvements
- **IA** : comportement des mobs, pathfinding

### Côté Renderer (Affichage pur)
- **AUCUNE logique métier** : pas de règles de jeu, pas d'état de jeu
- **OpenGL exclusivement** : draw calls, shaders, textures, buffers
- **Optimisations graphiques** : batching, culling, LOD, instancing
- **Abstraction** : classes pour Shader, Texture, Buffer, Material
- **Pipeline** : forward/deferred rendering, post-processing
- **UI** : rendu des interfaces utilisateur

### Système de build
- **CMake automatique** : les nouveaux fichiers sont détectés automatiquement
- **Dépendances** : ajoutez dans vcpkg.json si besoin
- **Resources** : placez dans Resources/ (copiées automatiquement au build)

## 🐛 Débogage et résolution de problèmes

### Erreurs de compilation courantes
```bash
# Erreur de linking OpenGL
# → Vérifiez que vcpkg est configuré correctement
# → CMAKE_TOOLCHAIN_FILE doit pointer vers vcpkg.cmake

# Headers non trouvés
# → Vérifiez les includes relatifs depuis src/
# → Utilisez des chemins depuis la racine src/

# Symboles non définis
# → Implémentez toutes les méthodes abstraites
# → Vérifiez que tous les .cpp sont dans src/

# Erreurs de séparation Game/Renderer
# → Game ne doit jamais inclure de headers OpenGL
# → Renderer ne doit jamais accéder aux objets de jeu
```

### Patterns de débogage
```cpp
// Debug conditionnel
#if DEBUG_LEVEL > 0
    std::cout << "Debug: " << variable << std::endl;
#endif

// Assertions pour la validation
#include <cassert>
assert(pointer != nullptr);
assert(chunkIndex < MAX_CHUNKS);
```

## 📦 Ressources et dépendances

### Dépendances actuelles (vcpkg.json)
```json
{
  "dependencies": [
    "opengl",
    "glew",
    "glfw3",
    "imgui[opengl3-binding,glfw-binding]",
    "stb"
  ]
}
```

### Ajout de nouvelles dépendances
1. Ajoutez dans `vcpkg.json`
2. Mettez à jour `CMakeLists.txt` si nécessaire (find_package, target_link_libraries)
3. Regenerez le cache : `cmake --build cmake-build-debug --target rebuild_cache`
4. Testez la compilation

### Gestion des resources
- **Shaders** : `Resources/Shaders/` (GLSL)
- **Textures** : `Resources/Textures/` (PNG, JPG)
- **Models** : `Resources/Models/` (OBJ, GLTF)
- **Chargement automatique** : copiées dans le dossier de build

## 🔄 Workflow de développement

### Avant de committer
1. **Compilation Debug** : `cmake --build cmake-build-debug`
2. **Compilation Release** : `cmake --build cmake-build-release`
3. **Test d'exécution** : `./cmake-build-debug/mc.exe`
4. **Vérification architecture** : respect STRICT de la séparation Game/Renderer
5. **Code style** : conventions de nommage respectées

### Ajout de fonctionnalités
1. **Planification** : déterminez si c'est Game ou Renderer (JAMAIS les deux)
2. **Interfaces** : créez d'abord les classes abstraites si nécessaire
3. **Implémentation** : respectez les conventions existantes
4. **Tests** : compilation et exécution des deux configurations
5. **Documentation** : mise à jour AGENTS.md si nouveaux patterns

### Structure des commits
```
[Game] Add new entity type: Creeper
[Renderer] Implement shadow mapping
[Build] Update vcpkg dependencies
[Docs] Update architecture documentation
```

## 🚨 Règles ABSOLUES à respecter

### Séparation Game/Renderer
```cpp
// ❌ JAMAIS dans Game/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
glGenBuffers(1, &vbo);
glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

// ❌ JAMAIS dans Renderer/
if (player.isDead()) return;
mob.updateAI(deltaTime);
world.generateChunk(x, z);
```

### Performance
- **Game** : Optimisations algorithmiques (O(n) vs O(n²))
- **Renderer** : Optimisations GPU (batching, culling, LOD)

### Mémoire
- **Game** : Smart pointers, RAII
- **Renderer** : Gestion explicite des ressources GPU

---

*Architecture modulaire STRICTE - La séparation Game/Renderer est NON-NÉGOCIABLE*
