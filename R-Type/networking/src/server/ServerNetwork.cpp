/*
** EPITECH PROJECT, 2024
** ServerNetwork.cpp
** File description:
** Network communication from the server side
*/

#include "server/ServerNetwork.hpp"
#include "Logger.hpp"

ServerNetwork::ServerNetwork(int port)
    : ANetwork() {
    udp_socket_->bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
    Logger::getInstance()->info("Server initialized on UDP port {}", port);
}

void ServerNetwork::receiveAndDispatchUDP() {
    receivePacketUDP([this](const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
        Logger::getInstance()->info("Received UDP packet from {}:{}", client_endpoint.address().to_string(), client_endpoint.port());
        
        dispatchPacket(packet, client_endpoint);

        receiveAndDispatchUDP();
    });
}

void ServerNetwork::sendPacketToClient(const Packet& packet, uint32_t client_id) {
    if (clients_.find(client_id) == clients_.end()) {
        Logger::getInstance()->error("Invalid client ID: {}", client_id);
        return;
    }

    sendPacketUDP(packet, clients_[client_id]);
    Logger::getInstance()->info("Sent packet to client_id={} at {}:{}", client_id,
                                clients_[client_id].address().to_string(), clients_[client_id].port());
}

void ServerNetwork::broadcastPacket(const Packet& packet) {
    for (const auto& [client_id, endpoint] : clients_) {
        sendPacketToClient(packet, client_id);
    }
        Logger::getInstance()->info("Broadcasted packet to {} clients.", clients_.size());
}

void ServerNetwork::dispatchPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    switch (packet.type) {
        case PacketType::CONNECT:
            handleConnectPacket(packet, client_endpoint);
            break;
        case PacketType::INPUT:
            handleInputPacket(packet, client_endpoint);
            break;
        case PacketType::DISCONNECT:
            handleDisconnectPacket(packet, client_endpoint);
            break;
        case PacketType::COLLISION:
            handleCollisionPacket(packet, client_endpoint);
            break;
        case PacketType::CLIENT_READY:
            handleClientReadyPacket(packet, client_endpoint);
            break;
        case PacketType::CLIENT_QUIT:
            handleClientQuitPacket(packet, client_endpoint);
            break;
        default:
            Logger::getInstance()->warn("Unknown packet type received from {}:{}", client_endpoint.address().to_string(), client_endpoint.port());
    }
}

void ServerNetwork::handleInputPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    // Deserialize fields
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int move_x = Packet::extractUInt32(packet.payload, 4);
    int move_y = Packet::extractUInt32(packet.payload, 8);
    bool firing = packet.payload[12];

    Logger::getInstance()->info("Received INPUT packet from {}: entity_id={}, move_x={}, move_y={}, firing={}",
                                client_endpoint.address().to_string(), entity_id, move_x, move_y, firing);

    // Process input in the game logic
    if (inputHandler_) {
        inputHandler_(entity_id, move_x, move_y, firing);

    }
}

void ServerNetwork::handleDisconnectPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);

    if (endpoints_.find(client_endpoint) != endpoints_.end()) {
        uint32_t client_id = endpoints_[client_endpoint];

        clients_.erase(client_id);
        endpoints_.erase(client_endpoint);

        Logger::getInstance()->info("Client disconnected: client_id={}, entity_id={}", client_id, entity_id);

        // Respond with SUCCESS_DISCONNECT (remembder to do it)
        Packet response = Packet::createSuccessDisconnectPacket();
        sendPacketToClient(response, client_id);
    } else {
        Logger::getInstance()->warn("Received DISCONNECT from unknown client.");
    }
}

void ServerNetwork::handleConnectPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    std::string name(packet.payload.begin(), packet.payload.end());

    // Check if the client is already registered
    if (endpoints_.find(client_endpoint) == endpoints_.end()) {
        // Assign a new client ID
        uint32_t client_id = next_client_id_++;
        clients_[client_id] = client_endpoint;
        endpoints_[client_endpoint] = client_id;

        Logger::getInstance()->info("New client connected: client_id={}, name={}, endpoint={}:{}",
                                    client_id, name, client_endpoint.address().to_string(), client_endpoint.port());

        sendSuccessConnectPacket(client_id, client_id);
        // check if a handler is present, if not do nothing or call the function with payload
        if (successConnectHandler_) {
            successConnectHandler_(client_id);
        }
    }
}

void ServerNetwork::handleCollisionPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    uint32_t enemy_id = Packet::extractUInt32(packet.payload, 4);

    Logger::getInstance()->info("Collision detected: entity_id={}, enemy_id={} from client {}:{}",
                                entity_id, enemy_id,
                                client_endpoint.address().to_string(), client_endpoint.port());

    // check if a handler is present, if not do nothing or call the function with payload
    if (collisionHandler_) {
        collisionHandler_(enemy_id);
    }
}

void ServerNetwork::handleClientReadyPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);

    Logger::getInstance()->info("Received CLIENT_READY packet from {}:{}: entity_id={}",
                                client_endpoint.address().to_string(), client_endpoint.port(), entity_id);
    if (clientReadyHandler_) {
        clientReadyHandler_(entity_id);
    }
}

void ServerNetwork::handleClientQuitPacket(const Packet& packet, const asio::ip::udp::endpoint& client_endpoint) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);

    Logger::getInstance()->info("Received CLIENT_QUIT packet from {}:{}: entity_id={}",
                                client_endpoint.address().to_string(), client_endpoint.port(), entity_id);
    if (clientQuitHandler_) { // calls game function handle client quitting room in game logic ???
        clientQuitHandler_(entity_id);
    }
}


void ServerNetwork::sendSuccessConnectPacket(uint32_t entity_id, uint32_t client_id) {
    Packet packet = Packet::createSuccessConnectPacket(entity_id);
    Logger::getInstance()->info("HEYUABDUENBAHDK");
    if (client_id == 0) { // 0 indicates broadcast
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendWonPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id) {
    Packet packet = Packet::createWonPacket(entity_id, current_level, score);
    if (client_id == 0) {
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendDeadPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id) {
    Packet packet = Packet::createDeadPacket(entity_id, current_level, score);
    if (client_id == 0) {
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendScorePacket(uint32_t entity_id, int score, uint32_t client_id) {
    Packet packet = Packet::createScorePacket(entity_id, score);
    if (client_id == 0) {
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendLevelPacket(uint32_t entity_id, int level, uint32_t client_id) {
    Packet packet = Packet::createLevelPacket(entity_id, level);
    if (client_id == 0) {
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendStartRoomPacket(uint32_t entity_id, uint32_t client_id) {
    Packet packet = Packet::createStartRoomPacket(entity_id);
    if (client_id == 0) {
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendStateUpdatePacket(uint32_t entity_id, int entity_type, int pos_x, int pos_y, 
                                          int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing, uint32_t client_id) {
    Packet packet = Packet::createStateUpdatePacket(entity_id, entity_type, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_firing);

    if (client_id == 0) { // 0 indicates broadcast
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendSuccessDisconnectPacket(uint32_t client_id) {
    Packet packet = Packet::createSuccessDisconnectPacket();

    if (client_id == 0) { // 0 indicates broadcast
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendEntityCreatePacket(uint32_t entity_id, int entity_type, const std::string& text,
                                           int pos_x, int pos_y, int vel_x, int vel_y,
                                           int scale_x, int scale_y, bool is_controllable, uint32_t client_id) {
    Packet packet = Packet::createEntityCreatePacket(entity_id, entity_type, text, pos_x, pos_y, 
                                                     vel_x, vel_y, scale_x, scale_y, is_controllable);

    if (client_id == 0) { // 0 indicates broadcast
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::sendEntityRemovePacket(uint32_t entity_id, uint32_t client_id) {
    Packet packet = Packet::createEntityRemovePacket(entity_id);

    if (client_id == 0) { // 0 indicates broadcast
        broadcastPacket(packet);
    } else {
        sendPacketToClient(packet, client_id);
    }
}

void ServerNetwork::registerSuccessConnectHandler(SuccessConnectHandler handler) {
    successConnectHandler_ = std::move(handler);
}

void ServerNetwork::registerCollisionHandler(CollisionHandler handler) {
    collisionHandler_ = std::move(handler);
}

void ServerNetwork::registerInputHandler(InputHandler handler) {
    inputHandler_ = std::move(handler);
}

void ServerNetwork::registerClientReadyHandler(ClientReadyHandler handler) {
    clientReadyHandler_ = std::move(handler);
}

void ServerNetwork::registerClientQuitHandler(ClientQuitHandler handler) {
    clientQuitHandler_ = std::move(handler);
}