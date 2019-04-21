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
        playerId = std::stoi( std::string( r1["result"]["vk_user_id"] ) );
        std::cout << "Authorization successful, " << playerId << std::endl;
    } else {
        std::cout << "Incorrect login or password.\n";
    }
    return isAuthorized;
}

bool NetworkManager::isAuthorized1() const {
    return isAuthorized;
}

NetworkManager::~NetworkManager() = default;
