/*
** EPITECH PROJECT, 2024
** ClientNetwork.hpp
** File description:
** Network communication from the client side
*/

#ifndef CLIENTNETWORK_HPP
#define CLIENTNETWORK_HPP

#include <memory>
#include <string>
#include "../network/ANetwork.hpp"
#include "Packet.hpp"

class ClientNetwork : public ANetwork {
public:
    ClientNetwork(const std::string& host, int port);

    using SuccessConnectHandler = std::function<void(uint32_t)>;
    using StateUpdateHandler = std::function<void(uint32_t, int, int, int, int, int, int, int, bool)>;
    using EntityCreateHandler = std::function<void(uint32_t, int, const std::string&, int, int, int, int, int, int, bool)>;
    using EntityRemoveHandler = std::function<void(uint32_t)>;
    using SuccessDisconnectHandler = std::function<void()>;
    using WonHandler = std::function<void(uint32_t, int, int)>;
    using DeadHandler = std::function<void(uint32_t, int, int)>;
    using ScoreHandler = std::function<void(uint32_t, int)>;
    using LevelHandler = std::function<void(uint32_t, int)>;
    using StartRoomHandler = std::function<void(uint32_t)>;
    
    void registerSuccessConnectHandler(SuccessConnectHandler handler);
    void registerStateUpdateHandler(StateUpdateHandler handler);
    void registerEntityCreateHandler(EntityCreateHandler handler);
    void registerEntityRemoveHandler(EntityRemoveHandler handler);
    void registerSuccessDisconnectHandler(SuccessDisconnectHandler handler);
    void registerWonHandler(WonHandler handler);
    void registerDeadHandler(DeadHandler handler);
    void registerScoreHandler(ScoreHandler handler);
    void registerLevelHandler(LevelHandler handler);
    void registerStartRoomHandler(StartRoomHandler handler);

    void receiveAndDispatchUDP();
    void disconnect();

    void sendConnectPacket(const std::string& name);
    void sendInputPacket(uint32_t entity_id, int move_x, int move_y, bool firing);
    void sendDisconnectPacket(uint32_t entity_id);
    void sendCollisionPacket(uint32_t entity_id, uint32_t enemy_id);
    void sendClientReadyPacket(uint32_t entity_id);
    void sendClientQuitPacket(uint32_t entity_id);

    void handleSucessConnect(const Packet& packet);
    void handleStateUpdatePacket(const Packet& packet);
    void handleSuccessDisconnectPacket(const Packet& packet);
    void handleEntityCreatePacket(const Packet& packet);
    void handleEntityRemovePacket(const Packet& packet);
    void handleWonPacket(const Packet& packet);
    void handleDeadPacket(const Packet& packet);
    void handleScorePacket(const Packet& packet);
    void handleLevelPacket(const Packet& packet);
    void handleStartRoomPacket(const Packet& packet);

    void poll() {
        io_context_.poll();
    }

    void poll_one() {
        io_context_.poll_one();
    }


private:
    void dispatchPacket(const Packet& packet);
    asio::ip::udp::endpoint server_endpoint_;

    SuccessConnectHandler successConnectHandler_;
    StateUpdateHandler stateUpdateHandler_;
    EntityCreateHandler entityCreateHandler_;
    EntityRemoveHandler entityRemoveHandler_;
    SuccessDisconnectHandler successDisconnectHandler_;
    WonHandler wonHandler_;
    DeadHandler deadHandler_;
    ScoreHandler scoreHandler_;
    LevelHandler levelHandler_;
    StartRoomHandler startRoomHandler_;
};

#endif // CLIENTNETWORK_HPP
