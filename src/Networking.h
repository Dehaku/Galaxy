#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace network
{
    extern int mainPort;
    extern bool packetDeletion;
}

int displayPort();



class Identity
{
    public: // You could say this is redundent, But I don't care for Enums, And this prevents idiotic programming errors.
    std::string wrongVersion;
    std::string connection;
    std::string connectionSuccessful;
    std::string textMessage;
    std::string drawStuffs;
    std::string grid;
    std::string peers;
    std::string clientMouse;

    Identity();
};
extern Identity ident;



class BoolPacket
{
    public:
    sf::Packet packet;
    bool toDelete;
    BoolPacket();
};

extern std::vector<BoolPacket> packetContainer;

class ServerController
{
    public:
    bool waiting;
    int conID;
    std::vector<std::string> chatHistory;


    ServerController();
};
extern ServerController servCon;

class ClientController
{
    public:
    std::string mode;
    bool waiting;
    bool connected;
    bool chatting;
    sf::IpAddress server;
    std::string name;
    int ID;
    std::string chatString;
    std::vector<std::string> chatHistory;
    std::vector<sf::Packet> packets;

    ClientController();
};
extern ClientController cliCon;

class Peer
{
    public:
    std::string name;
    int ID;
    sf::IpAddress IP;
    sf::Vector2f pos;
    sf::Vector2f mousePos;
    sf::Vector2f mom;
    sf::Sprite img;
    unsigned short port;
    Peer();
};

class Peers
{
    public:
    std::vector<Peer> connected;
};
extern Peers peers;

class NestClass
{
    public:
    std::vector<BoolPacket>::iterator nestIter;
};

void DealPackets();

void runTcpServer(unsigned short port);

void runTcpClient(unsigned short port);

#endif // NETWORKING_H_INCLUDED
