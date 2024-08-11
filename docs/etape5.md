### Plan pour l'étape 5 : Gestion des Voxels

#### 1. **Structure de données pour les voxels**
- Créer une classe `Voxel` pour représenter un voxel individuel.
- Créer une classe `Chunk` pour représenter une section du monde contenant un tableau 3D de voxels.
- Créer une classe `World` pour gérer plusieurs chunks.

#### 2. **Rendu des voxels**
- Écrire une fonction pour générer les sommets et les indices d'un cube.
- Écrire une fonction pour rendre un chunk de voxels.
- Écrire une fonction pour rendre le monde entier.

### Code

#### Classe `Voxel`
```cpp
class Voxel {
public:
    bool isActive; // Indique si le voxel est actif (visible)
    // Ajouter d'autres propriétés si nécessaire (ex. type, couleur)

    Voxel() : isActive(false) {}
};
```

#### Classe `Chunk`
```cpp
#include <vector>

class Chunk {
public:
    static const int CHUNK_SIZE = 16; // Taille du chunk (16x16x16)
    Voxel voxels[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    Chunk() {
        // Initialiser tous les voxels comme inactifs
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            for (int y = 0; y < CHUNK_SIZE; ++y) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    voxels[x][y][z] = Voxel();
                }
            }
        }
    }

    // Fonction pour activer un voxel
    void activateVoxel(int x, int y, int z) {
        if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE) {
            voxels[x][y][z].isActive = true;
        }
    }
};
```

#### Classe `World`
```cpp
#include <map>
#include <tuple>

class World {
public:
    std::map<std::tuple<int, int, int>, Chunk> chunks;

    // Fonction pour obtenir un chunk à une position donnée
    Chunk& getChunk(int x, int y, int z) {
        std::tuple<int, int, int> pos = std::make_tuple(x, y, z);
        if (chunks.find(pos) == chunks.end()) {
            chunks[pos] = Chunk();
        }
        return chunks[pos];
    }

    // Fonction pour activer un voxel dans le monde
    void activateVoxel(int chunkX, int chunkY, int chunkZ, int voxelX, int voxelY, int voxelZ) {
        Chunk& chunk = getChunk(chunkX, chunkY, chunkZ);
        chunk.activateVoxel(voxelX, voxelY, voxelZ);
    }
};
```

#### Fonction pour générer les sommets et les indices d'un cube
```cpp
#include <vector>
#include <GL/glew.h>

void generateCubeMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float x, float y, float z) {
    // Sommets d'un cube
    GLfloat cubeVertices[] = {
        // Positions          // Normales
        x, y, z,              0.0f, 0.0f, -1.0f,
        x + 1, y, z,          0.0f, 0.0f, -1.0f,
        x + 1, y + 1, z,      0.0f, 0.0f, -1.0f,
        x, y + 1, z,          0.0f, 0.0f, -1.0f,
        // Autres faces...
    };

    // Indices d'un cube
    GLuint cubeIndices[] = {
        0, 1, 2, 2, 3, 0,
        // Autres faces...
    };

    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
    indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));
}
```

#### Fonction pour rendre un chunk de voxels
```cpp
void renderChunk(const Chunk& chunk) {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                if (chunk.voxels[x][y][z].isActive) {
                    generateCubeMesh(vertices, indices, x, y, z);
                }
            }
        }
    }

    // Charger les sommets et les indices dans des buffers OpenGL et dessiner
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Définir les attributs de sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Dessiner les cubes
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Nettoyer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}
```

#### Fonction pour rendre le monde entier
```cpp
void renderWorld(const World& world) {
    for (const auto& [pos, chunk] : world.chunks) {
        renderChunk(chunk);
    }
}
```