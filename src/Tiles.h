#ifndef __TILES_H_INCLUDED__
#define __TILES_H_INCLUDED__

#include <SFML/Graphics.hpp>

const int Grids = 96;

const int ChunkSize = 32;

class WorldTileType
{
public:
    enum
    {
        City,
        Spire,
        Grass,
        Road,
        River,
        Ocean
    };
};

class Tile
{
public:
    unsigned int id;
    int deathID;
    float health;
    bool walkable;
    sf::Sprite img;
    sf::Color worldColor;

    void dirt();
    void rendGrass();
    void grass();
    void stone();
    void stoneWall();
    void wall();
    void woodFloor();
    void road(bool Center = false);
    void door();
    void lava();
    void sky();
    void cake();
    Tile();
};

class XTile
{
public:
    unsigned short id;
    unsigned short deathID;
    float health;
    sf::Texture *img;
    sf::Color worldColor;

    XTile();
    void initImage();
};

class Chunk
{
public:
    Tile zTiles[ChunkSize][ChunkSize][ChunkSize];
};

class Planet
{
public:
    std::vector<Chunk> chunks;
};

class WorldTile
{
public:
    sf::Sprite img;
    int id;
    sf::Vector2f galPos;
    sf::Vector2f regPos;
    sf::Vector2f locPos;
    int infected;
    int tiles;
    std::string type;

    std::string owner;

    class Building
    {
    public:
        sf::Vector2f pos;
        int size;
    };

    std::vector<Building> builds;

    WorldTile();
};

extern Tile tiles[Grids][Grids][Grids];

extern WorldTile worldMap[100][100];

extern Tile vChunk[ChunkSize][ChunkSize][ChunkSize]; // 10223616
extern Tile tempTile[Grids][Grids][Grids];
extern XTile xChunk[ChunkSize][ChunkSize][ChunkSize];

void zGenerateChunk(std::string type, int planet, sf::Vector2i Cords,
                    sf::Vector2i Pos = sf::Vector2i(500, 500));
void generateChunk(std::string type, int planet, sf::Vector2i Cords,
                   sf::Vector2i Pos = sf::Vector2i(500, 500));
void generateWorld(int RegionSize = 100, int PlanetNum = 500);
void saveMap(int planet, int xcord, int ycord, int xpos, int ypos);
void loadMap(int planet, int xcord, int ycord, int xpos, int ypos);
void initalizeWorldTiles();
void drawWorldTiles();
void initializeTiles();
void drawTile(int xpos, int ypos, sf::Texture &Image);
void drawNewTiles();
void tilesRandom();
void tilesGoUp();
void tilesGoDown();
void tilesGoLeft();
void tilesGoRight();
void buildLocalfromWorld(sf::Vector2i WorldPos);

#endif // TILES_H_INCLUDED
