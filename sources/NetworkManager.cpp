//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#include "NetworkManager.hpp"
#include <thread>
#include <iostream>
#include "json/json.hpp"
#include "utils/dateTime.cpp"

using json = nlohmann::json;

NetworkManager::NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort)
        : serverIpAddress(serverIp), serverPort(defaultPort), isAuthorized(false), match(match) {
//    std::cout << login_password.first << login_password.second << std::endl;
    assert(udpSocket.bind(54001) == sf::Socket::Done);
}

//sf::Packet NetworkManager::receivePacketsFromServer() {
//    sf::Packet p;
//    udpSocket.receive(p, serverIpAddress, serverPort);
//    return p;
//}
//
//sf::Socket::Status NetworkManager::sendPacketToServer(sf::Packet packet) {
//    return udpSocket.send(packet, serverIpAddress, serverPort);
//}
//
//sf::Socket::Status NetworkManager::sendStringToServer(std::string string) {
//    sf::Packet p;
//    p << string;
//    return udpSocket.send(p, serverIpAddress, serverPort);
//}

json NetworkManager::jsonRPC(std::string method, json::array_t params) {
    sf::Http http("http://www.meowbook.ru");
    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Post);
    request.setUri("/tanchiki");
    request.setField("Content-Type", "application/json");

    json j;
    j["jsonrpc"] = "2.0";
    j["id"] = 0;
    j["method"] = method;
    j["params"] = params;

    request.setBody(j.dump());



    sf::Http::Response response = http.sendRequest(request);

//    std::cout << "status: " << response.getStatus() << std::endl;
//    std::cout << "HTTP version: " << response.getMajorHttpVersion() << "." << response.getMinorHttpVersion() << std::endl;
//    std::cout << "Content-Type header:" << response.getField("Content-Type") << std::endl;
//    std::cout << "Body: " << response.getBody() << std::endl;

    try {
        return json::parse(response.getBody());
    }
    catch (json::parse_error ) {
        std::cout << "Sorry, probably server is down.\n";
        return json();
    }

}

bool NetworkManager::authorize(const std::pair<std::string, std::string> &login_password) {
    json response = jsonRPC("check_password_by_nickname", {login_password.first, login_password.second});
    if (response.empty())
        return false;
//    std::cout << response.dump();
    isAuthorized = response["result"]["count"] == 1;
    if (isAuthorized) {
        json r1 = jsonRPC("get_vk_id", {login_password.first});
//        std::cout << r1["result"];
        playerId = std::string( r1["result"]["vk_user_id"] );

        json r2 = jsonRPC("get_user_data_by_vk_id", {playerId});
        std::cout << "Welcome, " << r2["result"]["first_name"].get<std::string>() << " " << r2["result"]["last_name"].get<std::string>() << std::endl;
        myName = login_password.first;
        setReady(false);
    } else {
        std::cout << "Incorrect login or password.\n";
    }
    return isAuthorized;
}

void NetworkManager::sendMessageToServer(const std::string& message) {
    if (message.empty())
        return;
    sf::Packet packet;
    packet << message;
    udpSocket.send(packet, SERVER_IP, SERVER_PORT);
}

unsigned short NetworkManager::establishConnection(int game_id) {
    sf::Packet packet;
    std::string response;
    std::cout << "Connecting to server...\n";
    udpSocket.unbind();
    assert(udpSocket.bind(54001) == sf::Socket::Done);
    udpSocket.setBlocking(true);
    packet << "CONN";
    packet << game_id;
    udpSocket.send(packet, SERVER_IP, SERVER_PORT);
    udpSocket.send(packet, SERVER_IP, SERVER_PORT);
    udpSocket.send(packet, SERVER_IP, SERVER_PORT);
    udpSocket.receive(packet, serverIpAddress, serverPort);
    packet >> response;
    json j;
    j = json::parse(response);
    std::cout << j << std::endl;
    if (j["status"] == "OK") {
        std::cout << "OK.\n";
        udpSocket.setBlocking(false);
        match->setMyPlayerId(j["playerId"].get <unsigned short>());
        std::cout << "Your player Id: " << match->getMyPlayerId() << std::endl;
        return match->getMyPlayerId();
    } else {
        assert(!"Not OK");
    }
}

void NetworkManager::processPakcetsFromServer() {
    sf::Packet p;
    udpSocket.receive(p, serverIpAddress, serverPort);
    std::string content;
    p >> content;
    if (!content.empty()) {
//        std::cout << "Received from server: " << content << std::endl;
        if (content == "REQUEST") {
            std::string requestContent;
            p >> requestContent;
            if (requestContent == "PLAYERS_INFO") {
                sf::Packet packet;
                auto tankID = match->playerId_tankId[match->getMyPlayerId()];
                auto tanks = match->getObjectManager()->getTanks();
                packet << "RESPONSE" << "PLAYERS_INFO" << match->getMyPlayerId() << tanks[tankID]->getX() << tanks[tankID]->getY();
                udpSocket.send(packet, SERVER_IP, SERVER_PORT);
            }
//            json j = json::parse(requestContent);
//            std::cout << requestContent << std::endl;
        } else {

            match->processMessage(content, myPlayerId);
        }
    }
}

void NetworkManager::setMatch(Match *match) {
    NetworkManager::match = match;
}

void NetworkManager::sendXYs(std::vector<Tank *> &tanks) {
    for (int i = 0; i < tanks.size(); ++i) {
        sf::Packet packet;
        packet << "CHECK_XY";
        packet << i;
        packet << tanks[i]->getX();
        packet << tanks[i]->getY();
        udpSocket.send(packet, SERVER_IP, SERVER_PORT);
    }
}

json NetworkManager::getGamesList() {
    return jsonRPC("get_games_list", {token})["result"];
}

bool NetworkManager::connectToGame(int gameId) {
//    std::cout << token << std::endl;
//    std::cout << playerId << std::endl;
//    std::cout << gameId << std::endl;
    json j = jsonRPC("connect_to_game", {token, playerId, gameId});
//    std::cout << j << std::endl;
    return true;
}

json NetworkManager::getPlayersInGame(int gameId) {
    return jsonRPC("get_players_in_game", {token, gameId});;
}

bool NetworkManager::setReady(bool value) {
    ready = value;
    json j = jsonRPC("set_ready", {token, playerId, value});
//    std::cout << j << std::endl;
    return true;
}

bool NetworkManager::areAllReady(int gameId) {
    json j = jsonRPC("are_all_ready", {token, gameId});
    return j["result"]["count"] == 0;
}

void NetworkManager::waitForOthers() {
    auto tmp = udpSocket.isBlocking();

    udpSocket.setBlocking(true);
    udpSocket.setBlocking(tmp);
}

void NetworkManager::setMyPlayerId(int myPlayerId) {
    NetworkManager::myPlayerId = myPlayerId;
}

std::string NetworkManager::getNick(std::string vk_id) {
    json j = jsonRPC("get_nick", {vk_id});
    return j["result"]["nickname"].get <std::string> ();

}

bool NetworkManager::isReady() const {
    return ready;
}

int NetworkManager::createNewGame(std::string name, int map_id) {
    json j = jsonRPC("create_game", {token, name, playerId, currentDateTime(), map_id});
    std::cout << j << std::endl;
    return j["result"]["game_id"].get <int> ();
}

const std::string &NetworkManager::getMyName() const {
    return myName;
}

NetworkManager::~NetworkManager() = default;
