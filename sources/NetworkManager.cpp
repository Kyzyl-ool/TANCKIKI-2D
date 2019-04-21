//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#include "NetworkManager.hpp"
#include <thread>
#include <iostream>


NetworkManager::NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort,
                               const std::pair<std::string, std::string>& login_password)
        : serverIpAddress(serverIp), serverPort(defaultPort) {
//    assert(udpSocket.bind(defaultPort) == sf::Socket::Done);
//    sf::Packet testPacket;
//    testPacket << "{\"player_id\":-1}";
//    assert(udpSocket.send(testPacket, serverIpAddress, serverPort) == sf::Socket::Done);
//    sf::Packet responsePacket;
//    assert(udpSocket.receive(responsePacket, serverIpAddress, serverPort) == sf::Socket::Done);
//    std::string responseString;
//    responsePacket >> responseString;
//    assert(responseString == "OK");
//    std::cout << login_password.first << login_password.second << std::endl;
//    sf::Http http;

}

sf::Packet NetworkManager::receivePacketsFromServer() {
    sf::Packet p;
    udpSocket.receive(p, serverIpAddress, serverPort);
    return p;
}

sf::Socket::Status NetworkManager::sendPacketToServer(sf::Packet packet) {
    return udpSocket.send(packet, serverIpAddress, serverPort);
}

sf::Socket::Status NetworkManager::sendStringToServer(std::string string) {
    sf::Packet p;
    p << string;
    return udpSocket.send(p, serverIpAddress, serverPort);
}

NetworkManager::~NetworkManager() = default;
