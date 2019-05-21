//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#ifndef TANCHIKI_NETWORKMANAGER_HPP
#define TANCHIKI_NETWORKMANAGER_HPP


#include <string>
#include <SFML/Network.hpp>
#include "json/json.hpp"
#include "Match.hpp"

#define SERVER_IP "95.163.180.31"
#define SERVER_PORT 54000

using json = nlohmann::json;

class NetworkManager {
private:
    sf::IpAddress serverIpAddress;
    sf::UdpSocket udpSocket;
    unsigned short serverPort;
    std::string playerId;
    int myPlayerId = -1;
    bool ready = false;
public:
    bool isReady() const;

public:
    void setMyPlayerId(int myPlayerId);

private:
    bool isAuthorized;
    std::string token = "Hello world";
    Match* match;
public:
    void setMatch(Match *match);


public:
    bool isAuthorized1() const;
    explicit NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort);
    ~NetworkManager();



    json    jsonRPC(std::string method, json::array_t params);

    bool authorize(const std::pair<std::string, std::string>& login_password);

    json getGamesList();
    json getPlayersInGame(int gameId);

    bool connectToGame (int gameId);
    bool setReady(bool value);
    bool areAllReady(int gameId);
    unsigned short establishConnection(int game_id);
    void processPakcetsFromServer();
    void sendMessageToServer(const std::string& message);

    void sendXYs(std::vector<Tank *>& tanks);
    void waitForOthers();
    std::string getNick(std::string vk_id);
};


#endif //TANCHIKI_NETWORKMANAGER_HPP
