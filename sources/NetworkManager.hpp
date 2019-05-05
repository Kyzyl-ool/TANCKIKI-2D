//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#ifndef TANCHIKI_NETWORKMANAGER_HPP
#define TANCHIKI_NETWORKMANAGER_HPP


#include <string>
#include <SFML/Network.hpp>
#include "json/json.hpp"

using json = nlohmann::json;

class NetworkManager {
private:
    sf::IpAddress serverIpAddress;
    sf::UdpSocket udpSocket;
    unsigned short serverPort;
    std::string playerId;
    bool isAuthorized;
    std::string token = "Hello world";

public:
    bool isAuthorized1() const;
    explicit NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort);
    ~NetworkManager();

    sf::Socket::Status sendPacketToServer(sf::Packet packet);
    sf::Packet receivePacketsFromServer();

    sf::Socket::Status sendStringToServer(std::string string);

    json    jsonRPC(std::string method, json::array_t params);

    bool authorize(const std::pair<std::string, std::string>& login_password);

    json getGamesList();

    bool connectToGame (int gameId);

    bool disconnectFromGame(int gameId);

    bool createGame(std::string name, int creator);

    bool deleteGame(int gameId);
};


#endif //TANCHIKI_NETWORKMANAGER_HPP
