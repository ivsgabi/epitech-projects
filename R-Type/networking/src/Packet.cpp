/*
** EPITECH PROJECT, 2024
** Packet.cpp
** File description:
** Packet sent for client/server communication
*/

#include "Packet.hpp"
#include <chrono>
#include <stdexcept>
#include <arpa/inet.h>

Packet::Packet() : type(PacketType::CONNECT), size(0), timestamp(0) {}

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> buffer;

    // type
    buffer.push_back(static_cast<uint8_t>(type));

    // size
    uint32_t net_size = htonl(size);
    buffer.insert(buffer.end(),
                  reinterpret_cast<const uint8_t*>(&net_size),
                  reinterpret_cast<const uint8_t*>(&net_size) + sizeof(net_size));

    // timestamp
    uint32_t net_timestamp = htonl(timestamp);
    buffer.insert(buffer.end(),
                  reinterpret_cast<const uint8_t*>(&net_timestamp),
                  reinterpret_cast<const uint8_t*>(&net_timestamp) + sizeof(net_timestamp));

    // payload
    buffer.insert(buffer.end(), payload.begin(), payload.end());

    return buffer;
}

Packet Packet::deserialize(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 9) {
        throw std::runtime_error("Buffer too small to deserialize Packet");
    }

    Packet packet;
    packet.type = static_cast<PacketType>(buffer[0]);

    uint32_t net_size;
    std::memcpy(&net_size, &buffer[1], sizeof(net_size));
    packet.size = ntohl(net_size);

    uint32_t net_timestamp;
    std::memcpy(&net_timestamp, &buffer[5], sizeof(net_timestamp));
    packet.timestamp = ntohl(net_timestamp);

    if (buffer.size() > 9) {
        packet.payload = std::vector<uint8_t>(buffer.begin() + 9, buffer.end());
    }

    return packet;
}

Packet Packet::createConnectPacket(const std::string& name) {
    Packet packet;
    packet.type = PacketType::CONNECT;

    // Serialize name
    packet.payload.insert(packet.payload.end(), name.begin(), name.end());

    packet.size = static_cast<uint32_t>(packet.payload.size());
    packet.timestamp = static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count());

    return packet;
}

Packet Packet::createSuccessConnectPacket(uint32_t client_id) {
    Packet packet;
    packet.type = PacketType::SUCCESS_CONNECT;

    uint32_t net_client_id = htonl(client_id);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_client_id),
                          reinterpret_cast<const uint8_t*>(&net_client_id) + sizeof(net_client_id));

    packet.size = 9 + packet.payload.size();
    packet.timestamp = static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count());

    return packet;
}

Packet Packet::createInputPacket(uint32_t entity_id, int move_x, int move_y, bool firing) {
    Packet packet;
    packet.type = PacketType::INPUT;

    // Serialize entity_id
    uint32_t net_entity_id = htonl(entity_id);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    // Serialize move_x
    int32_t net_move_x = htonl(move_x);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_move_x),
                          reinterpret_cast<const uint8_t*>(&net_move_x) + sizeof(net_move_x));

    // Serialize move_y
    int32_t net_move_y = htonl(move_y);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_move_y),
                          reinterpret_cast<const uint8_t*>(&net_move_y) + sizeof(net_move_y));

    // Serialize firing
    packet.payload.push_back(static_cast<uint8_t>(firing));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createDisconnectPacket(uint32_t entity_id) {
    Packet packet;
    packet.type = PacketType::DISCONNECT;

    // Serialize entity_id
    uint32_t net_entity_id = htonl(entity_id);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createStateUpdatePacket(uint32_t entity_id, int entity_type, int pos_x, int pos_y, 
                                       int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing) {
    Packet packet;
    packet.type = PacketType::STATE_UPDATE;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_entity_type = htonl(entity_type);
    int32_t net_pos_x = htonl(pos_x);
    int32_t net_pos_y = htonl(pos_y);
    int32_t net_vel_x = htonl(vel_x);
    int32_t net_vel_y = htonl(vel_y);
    int32_t net_scale_x = htonl(scale_x);
    int32_t net_scale_y = htonl(scale_y);
    uint8_t net_is_firing = static_cast<uint8_t>(is_firing);

    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_type),
                          reinterpret_cast<const uint8_t*>(&net_entity_type) + sizeof(net_entity_type));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_pos_x),
                          reinterpret_cast<const uint8_t*>(&net_pos_x) + sizeof(net_pos_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_pos_y),
                          reinterpret_cast<const uint8_t*>(&net_pos_y) + sizeof(net_pos_y));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_vel_x),
                          reinterpret_cast<const uint8_t*>(&net_vel_x) + sizeof(net_vel_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_vel_y),
                          reinterpret_cast<const uint8_t*>(&net_vel_y) + sizeof(net_vel_y));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_scale_x),
                          reinterpret_cast<const uint8_t*>(&net_scale_x) + sizeof(net_scale_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_scale_y),
                          reinterpret_cast<const uint8_t*>(&net_scale_y) + sizeof(net_scale_y));
    packet.payload.push_back(net_is_firing);

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createSuccessDisconnectPacket() {
    Packet packet;
    packet.type = PacketType::SUCCESS_DISCONNECT;
    packet.size = 0; // No payload
    return packet;
}

Packet Packet::createEntityCreatePacket(uint32_t entity_id, int entity_type, const std::string& text,
                                        int pos_x, int pos_y, int vel_x, int vel_y,
                                        int scale_x, int scale_y, bool is_controllable) {
    Packet packet;
    packet.type = PacketType::ENTITY_CREATE;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_entity_type = htonl(entity_type);

    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_type),
                          reinterpret_cast<const uint8_t*>(&net_entity_type) + sizeof(net_entity_type));

    std::string padded_text = text.substr(0, 255);
    padded_text.resize(255, '\0');

    packet.payload.insert(packet.payload.end(), padded_text.begin(), padded_text.end());

    int32_t net_pos_x = htonl(pos_x);
    int32_t net_pos_y = htonl(pos_y);
    int32_t net_vel_x = htonl(vel_x);
    int32_t net_vel_y = htonl(vel_y);
    int32_t net_scale_x = htonl(scale_x);
    int32_t net_scale_y = htonl(scale_y);

    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_pos_x),
                          reinterpret_cast<const uint8_t*>(&net_pos_x) + sizeof(net_pos_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_pos_y),
                          reinterpret_cast<const uint8_t*>(&net_pos_y) + sizeof(net_pos_y));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_vel_x),
                          reinterpret_cast<const uint8_t*>(&net_vel_x) + sizeof(net_vel_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_vel_y),
                          reinterpret_cast<const uint8_t*>(&net_vel_y) + sizeof(net_vel_y));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_scale_x),
                          reinterpret_cast<const uint8_t*>(&net_scale_x) + sizeof(net_scale_x));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_scale_y),
                          reinterpret_cast<const uint8_t*>(&net_scale_y) + sizeof(net_scale_y));

    uint8_t net_is_controllable = static_cast<uint8_t>(is_controllable);
    packet.payload.push_back(net_is_controllable);

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createEntityRemovePacket(uint32_t entity_id) {
    Packet packet;
    packet.type = PacketType::ENTITY_REMOVE;

    // Serialize entity_id
    uint32_t net_entity_id = htonl(entity_id);
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createCollisionPacket(uint32_t entity_id, uint32_t enemy_id) {
    Packet packet;
    packet.type = PacketType::COLLISION;

    uint32_t net_entity_id = htonl(entity_id);
    uint32_t net_enemy_id = htonl(enemy_id);

    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_entity_id),
                          reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(),
                          reinterpret_cast<const uint8_t*>(&net_enemy_id),
                          reinterpret_cast<const uint8_t*>(&net_enemy_id) + sizeof(net_enemy_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createWonPacket(uint32_t entity_id, int current_level, int score) {
    Packet packet;
    packet.type = PacketType::WON;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_current_level = htonl(current_level);
    int32_t net_score = htonl(score);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_current_level), reinterpret_cast<const uint8_t*>(&net_current_level) + sizeof(net_current_level));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_score), reinterpret_cast<const uint8_t*>(&net_score) + sizeof(net_score));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createDeadPacket(uint32_t entity_id, int current_level, int score) {
    Packet packet;
    packet.type = PacketType::DEAD;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_current_level = htonl(current_level);
    int32_t net_score = htonl(score);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_current_level), reinterpret_cast<const uint8_t*>(&net_current_level) + sizeof(net_current_level));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_score), reinterpret_cast<const uint8_t*>(&net_score) + sizeof(net_score));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createScorePacket(uint32_t entity_id, int score) {
    Packet packet;
    packet.type = PacketType::SCORE;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_score = htonl(score);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_score), reinterpret_cast<const uint8_t*>(&net_score) + sizeof(net_score));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createLevelPacket(uint32_t entity_id, int level) {
    Packet packet;
    packet.type = PacketType::LEVEL;

    uint32_t net_entity_id = htonl(entity_id);
    int32_t net_level = htonl(level);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));
    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_level), reinterpret_cast<const uint8_t*>(&net_level) + sizeof(net_level));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createStartRoomPacket(uint32_t entity_id) {
    Packet packet;
    packet.type = PacketType::START_ROOM;

    uint32_t net_entity_id = htonl(entity_id);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createClientReadyPacket(uint32_t entity_id) {
    Packet packet;
    packet.type = PacketType::CLIENT_READY;

    uint32_t net_entity_id = htonl(entity_id);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}

Packet Packet::createClientQuitPacket(uint32_t entity_id) {
    Packet packet;
    packet.type = PacketType::CLIENT_QUIT;

    uint32_t net_entity_id = htonl(entity_id);

    packet.payload.insert(packet.payload.end(), reinterpret_cast<const uint8_t*>(&net_entity_id), reinterpret_cast<const uint8_t*>(&net_entity_id) + sizeof(net_entity_id));

    packet.size = static_cast<uint32_t>(packet.payload.size());
    return packet;
}


uint32_t Packet::extractUInt32(const std::vector<uint8_t>& buffer, size_t offset) {
    uint32_t value;
    std::memcpy(&value, &buffer[offset], sizeof(value));
    return ntohl(value);
}

std::string Packet::extractString(const std::vector<uint8_t>& buffer, size_t offset) {
    return std::string(buffer.begin() + offset, buffer.end());
}
