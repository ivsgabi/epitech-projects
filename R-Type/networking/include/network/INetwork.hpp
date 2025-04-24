/*
** EPITECH PROJECT, 2024
** INetwork.hpp
** File description:
** General low level Network Interface
*/

#ifndef INETWORK_HPP
#define INETWORK_HPP

#include <vector>
#include <cstddef>
#include <asio.hpp>

class INetwork {
public:
    virtual ~INetwork() = default;

    virtual void sendDataUDP(const std::vector<uint8_t>& data, const asio::ip::udp::endpoint& endpoint) = 0;
    virtual void receiveDataUDP(std::function<void(const std::vector<uint8_t>&, const asio::ip::udp::endpoint&)> callback) = 0;
};

#endif // INETWORK_HPP
