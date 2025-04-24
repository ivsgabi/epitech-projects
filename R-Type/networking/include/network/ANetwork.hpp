/*
** EPITECH PROJECT, 2024
** ANetwork.hpp
** File description:
** General low level Network Abstract
*/

#ifndef ANETWORK_HPP
#define ANETWORK_HPP

#include "Packet.hpp"
#include <asio.hpp>
#include <functional>
#include <thread>
#include <memory>
#include "Logger.hpp"

class ANetwork {
public:
    ANetwork();
    virtual ~ANetwork();

    void sendPacketUDP(const Packet& packet, const asio::ip::udp::endpoint& endpoint);
    void receivePacketUDP(std::function<void(const Packet&, const asio::ip::udp::endpoint&)> callback);
    asio::io_context& getIoContext() {
        return io_context_;
    }

    void run();
    void stop();

protected:
    asio::io_context io_context_;
    std::shared_ptr<asio::ip::udp::socket> udp_socket_;
    std::thread io_thread_;
};

#endif // ANETWORK_HPP
