/*
** EPITECH PROJECT, 2024
** Packet.hpp
** File description:
** Packet sent for client/server communication
*/

#ifndef PACKET_HPP
#define PACKET_HPP

#include <vector>
#include <cstdint>
#include <cstring>
#include <string>

enum class PacketType : uint8_t {
    CONNECT = 0,
    SUCCESS_CONNECT = 1,
    STATE_UPDATE = 2,
    ENTITY_CREATE = 3,
    ENTITY_REMOVE = 4,
    INPUT = 5,
    DISCONNECT = 6,
    SUCCESS_DISCONNECT = 7,
    COLLISION = 8,
    WON = 9,
    DEAD = 10,
    SCORE = 11,
    LEVEL = 12,
    START_ROOM = 13,
    CLIENT_READY = 14,
    CLIENT_QUIT = 15
};


class Packet {
public:
    PacketType type;             // 1 byte
    uint32_t size;               // 4 bytes (header + payload)
    uint32_t timestamp;          // 4 bytes (timestamp)
    std::vector<uint8_t> payload;

    Packet();

    std::vector<uint8_t> serialize() const;
    static Packet deserialize(const std::vector<uint8_t>& buffer);

    static Packet createConnectPacket(const std::string& name);
    static Packet createSuccessConnectPacket(uint32_t client_id);
    static Packet createInputPacket(uint32_t entity_id, int move_x, int move_y, bool firing);
    static Packet createDisconnectPacket(uint32_t entity_id);
    static Packet createStateUpdatePacket(uint32_t entity_id, int entity_type, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing);
    static Packet createSuccessDisconnectPacket();
    static Packet createEntityCreatePacket(uint32_t entity_id, int entity_type, const std::string& text, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_controllable);
    static Packet createEntityRemovePacket(uint32_t entity_id);
    static Packet createCollisionPacket(uint32_t entity_id, uint32_t enemy_id);
    static Packet createWonPacket(uint32_t entity_id, int current_level, int score);
    static Packet createDeadPacket(uint32_t entity_id, int current_level, int score);
    static Packet createScorePacket(uint32_t entity_id, int score);
    static Packet createLevelPacket(uint32_t entity_id, int level);
    static Packet createStartRoomPacket(uint32_t entity_id);
    static Packet createClientReadyPacket(uint32_t entity_id);
    static Packet createClientQuitPacket(uint32_t entity_id);

    static uint32_t extractUInt32(const std::vector<uint8_t>& buffer, size_t offset);
    static std::string extractString(const std::vector<uint8_t>& buffer, size_t offset);
};

#endif // PACKET_HPP
