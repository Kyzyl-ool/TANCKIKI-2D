//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#ifndef TANCHIKI_NETWORKMANAGER_HPP
#define TANCHIKI_NETWORKMANAGER_HPP


#include <string>
#include <SFML/Network.hpp>
#include "json/json.hpp"
#include "Match.hpp"

using json = nlohmann::json;

class NetworkManager {
private:
    sf::IpAddress serverIpAddress;
    sf::UdpSocket udpSocket;
    unsigned short serverPort;
    int playerId;
    Match* match;
private:
    bool isAuthorized;

public:
    explicit NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort);
    ~NetworkManager();

    void processPakcetsFromServer();
    void sendMessageToServer(const std::string& message);

    json jsonRPC(std::string method, json::array_t params);

    bool authorize(const std::pair<std::string, std::string>& login_password);
};


#endif //TANCHIKI_NETWORKMANAGER_HPP
