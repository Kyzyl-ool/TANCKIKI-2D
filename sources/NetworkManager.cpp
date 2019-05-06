//
// Created by Кежик Кызыл-оол on 2019-04-21.
//

#include "NetworkManager.hpp"
#include <thread>
#include <iostream>
#include "json/json.hpp"

using json = nlohmann::json;

NetworkManager::NetworkManager(sf::IpAddress serverIp, unsigned short defaultPort)
        : serverIpAddress(serverIp), serverPort(defaultPort), isAuthorized(false) {
//    std::cout << login_password.first << login_password.second << std::endl;

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

json NetworkManager::jsonRPC(std::string method, json::array_t params) {
    sf::Http http("http://meowbook.ru");
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
    } else {
        std::cout << "Incorrect login or password.\n";
    }
    return isAuthorized;
}

bool NetworkManager::isAuthorized1() const {
    return isAuthorized;
}

json NetworkManager::getGamesList() {
    return jsonRPC("get_games_list", {token})["result"];
}

bool NetworkManager::connectToGame(int gameId) {
    std::cout << token << std::endl;
    std::cout << playerId << std::endl;
    std::cout << gameId << std::endl;
    json j = jsonRPC("connect_to_game", {token, playerId, gameId});
    std::cout << j << std::endl;
    return true;
}

NetworkManager::~NetworkManager() = default;
