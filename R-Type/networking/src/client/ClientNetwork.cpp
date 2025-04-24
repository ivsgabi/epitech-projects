/*
** EPITECH PROJECT, 2024
** ClientNetwork.cpp
** File description:
** Network communication from the client side
*/

#include "client/ClientNetwork.hpp"
#include "Logger.hpp"

ClientNetwork::ClientNetwork(const std::string& host, int port)
    : ANetwork(), server_endpoint_(asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {
    asio::ip::udp::resolver resolver(io_context_);
    server_endpoint_ = *resolver.resolve(host, std::to_string(port)).begin();
    Logger::getInstance()->info("ClientNetwork initialized for UDP. Server endpoint: {}:{}", host, port);
}

void ClientNetwork::sendConnectPacket(const std::string& name) {
    Packet packet = Packet::createConnectPacket(name);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent CONNECT packet to server.");
}

void ClientNetwork::sendInputPacket(uint32_t entity_id, int move_x, int move_y, bool firing) {
    Packet packet = Packet::createInputPacket(entity_id, move_x, move_y, firing);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent INPUT packet to server.");
}

void ClientNetwork::sendDisconnectPacket(uint32_t entity_id) {
    Packet packet = Packet::createDisconnectPacket(entity_id);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent DISCONNECT packet to server.");
}

void ClientNetwork::sendCollisionPacket(uint32_t entity_id, uint32_t enemy_id) {
    Packet packet = Packet::createCollisionPacket(entity_id, enemy_id);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent COLLISION packet: entity_id={}, enemy_id={}", entity_id, enemy_id);
}

void ClientNetwork::receiveAndDispatchUDP() {
    receivePacketUDP([this](const Packet& packet, const asio::ip::udp::endpoint& endpoint) {
        Logger::getInstance()->info("Received UDP packet from server.");
        dispatchPacket(packet);
    });
}

void ClientNetwork::sendClientReadyPacket(uint32_t entity_id) {
    Packet packet = Packet::createClientReadyPacket(entity_id);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent CLIENT_READY packet: entity_id={}", entity_id);
}

void ClientNetwork::sendClientQuitPacket(uint32_t entity_id) {
    Packet packet = Packet::createClientQuitPacket(entity_id);
    sendPacketUDP(packet, server_endpoint_);
    Logger::getInstance()->info("Sent CLIENT_QUIT packet: entity_id={}", entity_id);
}

void ClientNetwork::dispatchPacket(const Packet& packet) {
    switch (packet.type) {
        case PacketType::SUCCESS_CONNECT:
            handleSucessConnect(packet);
            break;
        case PacketType::STATE_UPDATE:
            handleStateUpdatePacket(packet);
            break;
        case PacketType::SUCCESS_DISCONNECT:
            handleSuccessDisconnectPacket(packet);
            break;
        case PacketType::ENTITY_CREATE:
            handleEntityCreatePacket(packet);
            break;
        case PacketType::ENTITY_REMOVE:
            handleEntityRemovePacket(packet);
            break;
        case PacketType::WON:
            handleWonPacket(packet);
            break;
        case PacketType::DEAD:
            handleDeadPacket(packet);
            break;
        case PacketType::SCORE:
            handleScorePacket(packet);
            break;
        case PacketType::LEVEL:
            handleLevelPacket(packet);
            break;
        case PacketType::START_ROOM:
            handleStartRoomPacket(packet);
        default:
            Logger::getInstance()->warn("Unknown packet type received.");
    }
}

void ClientNetwork::handleSucessConnect(const Packet& packet) {
    uint32_t client_id = Packet::extractUInt32(packet.payload, 0);
    Logger::getInstance()->info("Received SUCCESS_CONNECT: client_id={}", client_id);
    if (successConnectHandler_) {
        successConnectHandler_(client_id);
    }
}

void ClientNetwork::handleStateUpdatePacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int entity_type = Packet::extractUInt32(packet.payload, 4);
    int pos_x = Packet::extractUInt32(packet.payload, 8);
    int pos_y = Packet::extractUInt32(packet.payload, 12);
    int vel_x = Packet::extractUInt32(packet.payload, 16);
    int vel_y = Packet::extractUInt32(packet.payload, 20);
    int scale_x = Packet::extractUInt32(packet.payload, 24);
    int scale_y = Packet::extractUInt32(packet.payload, 28);
    bool is_firing = packet.payload[32] != 0;

    Logger::getInstance()->info(
        "Received STATE_UPDATE: entity_id={}, entity_type={}, pos_x={}, pos_y={}, vel_x={}, vel_y={}, scale_x={}, scale_y={}, is_firing={}",
        entity_id, entity_type, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_firing
    );

    if (stateUpdateHandler_) {
        stateUpdateHandler_(entity_id, entity_type, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_firing);
    }
}

void ClientNetwork::handleSuccessDisconnectPacket(const Packet& packet) {
    Logger::getInstance()->info("Received SUCCESS_DISCONNECT from server.");
    if (successDisconnectHandler_) {
        successDisconnectHandler_();
    }
}

void ClientNetwork::handleEntityCreatePacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int entity_type = Packet::extractUInt32(packet.payload, 4);

    std::string text(packet.payload.begin() + 8, packet.payload.begin() + 8 + 255);

    int pos_x = Packet::extractUInt32(packet.payload, 8 + 255);
    int pos_y = Packet::extractUInt32(packet.payload, 12 + 255);
    int vel_x = Packet::extractUInt32(packet.payload, 16 + 255);
    int vel_y = Packet::extractUInt32(packet.payload, 20 + 255);
    int scale_x = Packet::extractUInt32(packet.payload, 24 + 255);
    int scale_y = Packet::extractUInt32(packet.payload, 28 + 255);
    bool is_controllable = packet.payload[32 + 255] != 0;

    Logger::getInstance()->info(
        "Received ENTITY_CREATE: entity_id={}, entity_type={}, text={}, pos_x={}, pos_y={}, vel_x={}, vel_y={}, scale_x={}, scale_y={}, is_controllable={}",
        entity_id, entity_type, text, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_controllable
    );

    if (entityCreateHandler_) {
        entityCreateHandler_(entity_id, entity_type, text, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_controllable);
    }
}

void ClientNetwork::handleEntityRemovePacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);

    Logger::getInstance()->info("Received ENTITY_REMOVE: entity_id={}", entity_id);
    if (entityRemoveHandler_) {
        entityRemoveHandler_(entity_id);
    }
}

void ClientNetwork::handleWonPacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int current_level = Packet::extractUInt32(packet.payload, 4);
    int score = Packet::extractUInt32(packet.payload, 8);

    Logger::getInstance()->info("Received WON packet: entity_id={}, current_level={}, score={}", entity_id, current_level, score);
    if (wonHandler_) {
        wonHandler_(entity_id, current_level, score);
    }
}

void ClientNetwork::handleDeadPacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int current_level = Packet::extractUInt32(packet.payload, 4);
    int score = Packet::extractUInt32(packet.payload, 8);

    Logger::getInstance()->info("Received DEAD packet: entity_id={}, current_level={}, score={}", entity_id, current_level, score);
    if (deadHandler_) {
        deadHandler_(entity_id, current_level, score);
    }
}

void ClientNetwork::handleScorePacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int score = Packet::extractUInt32(packet.payload, 4);

    Logger::getInstance()->info("Received SCORE packet: entity_id={}, score={}", entity_id, score);
    if (scoreHandler_) {
        scoreHandler_(entity_id, score);
    }
}

void ClientNetwork::handleLevelPacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);
    int level = Packet::extractUInt32(packet.payload, 4);

    Logger::getInstance()->info("Received LEVEL packet: entity_id={}, level={}", entity_id, level);
    if (levelHandler_) {
        levelHandler_(entity_id, level);
    }
}

void ClientNetwork::handleStartRoomPacket(const Packet& packet) {
    uint32_t entity_id = Packet::extractUInt32(packet.payload, 0);

    Logger::getInstance()->info("Received START_ROOM packet: entity_id={}", entity_id);
    if (startRoomHandler_) {
        startRoomHandler_(entity_id);
    }
}

void ClientNetwork::disconnect() {
    udp_socket_->close();
    Logger::getInstance()->info("Client disconnected.");
}







void ClientNetwork::registerSuccessConnectHandler(SuccessConnectHandler handler) {
    successConnectHandler_ = std::move(handler);
}

void ClientNetwork::registerStateUpdateHandler(StateUpdateHandler handler) {
    stateUpdateHandler_ = std::move(handler);
}

void ClientNetwork::registerEntityCreateHandler(EntityCreateHandler handler) {
    entityCreateHandler_ = std::move(handler);
}

void ClientNetwork::registerEntityRemoveHandler(EntityRemoveHandler handler) {
    entityRemoveHandler_ = std::move(handler);
}

void ClientNetwork::registerSuccessDisconnectHandler(SuccessDisconnectHandler handler) {
    successDisconnectHandler_ = std::move(handler);
}

void ClientNetwork::registerWonHandler(WonHandler handler) {
    wonHandler_ = std::move(handler);
}

void ClientNetwork::registerDeadHandler(DeadHandler handler) {
    deadHandler_ = std::move(handler);
}

void ClientNetwork::registerScoreHandler(ScoreHandler handler) {
    scoreHandler_ = std::move(handler);
}

void ClientNetwork::registerLevelHandler(LevelHandler handler) {
    levelHandler_ = std::move(handler);
}

void ClientNetwork::registerStartRoomHandler(StartRoomHandler handler) {
    startRoomHandler_ = std::move(handler);
}
