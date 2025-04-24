/*
** EPITECH PROJECT, 2024
** ServerNetwork.hpp
** File description:
** Network communication from the server side
*/

#ifndef SERVERNETWORK_HPP
#define SERVERNETWORK_HPP

#include "../network/ANetwork.hpp"
#include "Packet.hpp"
#include <unordered_map>
#define SERVER_PORT 4242

struct UdpEndpointHash {
    std::size_t operator()(const asio::ip::udp::endpoint& endpoint) const {
        return std::hash<std::string>()(endpoint.address().to_string()) ^ std::hash<uint16_t>()(endpoint.port());
    }
};

struct UdpEndpointEqual {
    bool operator()(const asio::ip::udp::endpoint& lhs, const asio::ip::udp::endpoint& rhs) const {
        return lhs.address() == rhs.address() && lhs.port() == rhs.port();
    }
};

class ServerNetwork : public ANetwork {
public:
    explicit ServerNetwork(int port);

    using SuccessConnectHandler = std::function<void(uint32_t)>;
    // using StateUpdateHandler = std::function<void(uint32_t, int, int, int, int)>;
    // using EntityCreateHandler = std::function<void(uint32_t, int, int, int)>;
    using InputHandler = std::function<void(uint32_t, int, int, bool)>;
    using CollisionHandler = std::function<void(uint32_t)>;
    using ClientReadyHandler = std::function<void(uint32_t)>;
    using ClientQuitHandler = std::function<void(uint32_t)>;
    void registerSuccessConnectHandler(SuccessConnectHandler handler);
    void registerCollisionHandler(CollisionHandler handler);
    void registerInputHandler(InputHandler handler);
    void registerClientReadyHandler(ClientReadyHandler handler);
    void registerClientQuitHandler(ClientQuitHandler handler);
    // void registerStateUpdateHandler(StateUpdateHandler handler);
    // void registerEntityCreateHandler(EntityCreateHandler handler);
    // void registerEntityRemoveHandler(EntityRemoveHandler handler);
    // void registerSuccessDisconnectHandler(SuccessDisconnectHandler handler);
    

    void receiveAndDispatchUDP();
    void sendPacketToClient(const Packet& packet, uint32_t client_id);
    void broadcastPacket(const Packet& packet);

    void sendSuccessConnectPacket(uint32_t entity_id, uint32_t client_id = 0);
    void sendStateUpdatePacket(uint32_t entity_id, int entity_type, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing, uint32_t client_id = 0);
    void sendEntityCreatePacket(uint32_t entity_id, int entity_type, const std::string& text, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_controllable, uint32_t client_id);
    void sendEntityRemovePacket(uint32_t entity_id, uint32_t client_id = 0);
    void sendSuccessDisconnectPacket(uint32_t client_id);
    void sendStartRoomPacket(uint32_t entity_id, uint32_t client_id = 0);
    void sendLevelPacket(uint32_t entity_id, int level, uint32_t client_id = 0);
    void sendScorePacket(uint32_t entity_id, int score, uint32_t client_id = 0);
    void sendDeadPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id = 0);
    void sendWonPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id = 0);


private:
    void dispatchPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleConnectPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleInputPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleDisconnectPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleCollisionPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleClientReadyPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);
    void handleClientQuitPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint);

    std::unordered_map<uint32_t, asio::ip::udp::endpoint> clients_; // Maps client IDs to udp endpoints
    std::unordered_map<asio::ip::udp::endpoint, uint32_t, UdpEndpointHash, UdpEndpointEqual> endpoints_;
    uint32_t next_client_id_ = 1;
    SuccessConnectHandler successConnectHandler_;
    CollisionHandler collisionHandler_;
    InputHandler inputHandler_;
    ClientReadyHandler clientReadyHandler_;
    ClientQuitHandler clientQuitHandler_;
    // using InputHandler = std::function<void(uint32_t, int, int, bool)>;
};

#endif // SERVERNETWORK_HPP
