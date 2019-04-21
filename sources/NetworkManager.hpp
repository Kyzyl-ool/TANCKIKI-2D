//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#ifndef TANCHIKI_NETWORKMANAGER_HPP
#define TANCHIKI_NETWORKMANAGER_HPP


#include <string>
#include <SFML/Network.hpp>

class NetworkManager {
private:
    sf::IpAddress serverIpAddress;
    sf::UdpSocket udpSocket;
    unsigned short serverPort;
    int playerId;

public:
    explicit NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort,
                            const std::pair<std::string, std::string>& login_password);
    ~NetworkManager();

    sf::Socket::Status sendPacketToServer(sf::Packet packet);
    sf::Packet receivePacketsFromServer();

    sf::Socket::Status sendStringToServer(std::string string);
};


#endif //TANCHIKI_NETWORKMANAGER_HPP
