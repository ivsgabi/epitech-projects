/*
** EPITECH PROJECT, 2024
** ANetwork.cpp
** File description:
** General low level Network Abstract
*/

#include "network/ANetwork.hpp"

ANetwork::ANetwork()
    : udp_socket_(std::make_shared<asio::ip::udp::socket>(io_context_)) {
    udp_socket_->open(asio::ip::udp::v4());
    Logger::getInstance()->info("ANetwork initialized with UDP socket.");
}

ANetwork::~ANetwork() {
    stop();
    Logger::getInstance()->info("ANetwork destructor called.");
}

void ANetwork::sendPacketUDP(const Packet& packet, const asio::ip::udp::endpoint& endpoint) {
    auto buffer = std::make_shared<std::vector<uint8_t>>(packet.serialize());
    udp_socket_->async_send_to(asio::buffer(*buffer), endpoint,
        [buffer](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                Logger::getInstance()->info("Sent UDP packet of {} bytes.", bytes_transferred);
            } else {
                Logger::getInstance()->error("UDP send error: {}", error.message());
            }
        });
}

void ANetwork::receivePacketUDP(std::function<void(const Packet&, const asio::ip::udp::endpoint&)> callback) {
    auto buffer = std::make_shared<std::vector<uint8_t>>(1024);
    auto remote_endpoint = std::make_shared<asio::ip::udp::endpoint>();

    udp_socket_->async_receive_from(asio::buffer(*buffer), *remote_endpoint,
        [this, buffer, remote_endpoint, callback](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                buffer->resize(bytes_transferred);
                try {
                    Packet packet = Packet::deserialize(*buffer);
                    callback(packet, *remote_endpoint);
                } catch (const std::exception& e) {
                    Logger::getInstance()->error("Failed to deserialize UDP packet: {}", e.what());
                }
            } else {
                Logger::getInstance()->error("UDP receive error: {}", error.message());
            }
            // Re-initiate the asynchronous receive to continue listening for packets
            receivePacketUDP(callback);
        });
}

void ANetwork::run() {
    try {
        Logger::getInstance()->info("Starting io_context...");
        io_thread_ = std::thread([this]() {
            try {
                io_context_.run();
                Logger::getInstance()->info("io_context finished");
            } catch (const std::exception& e) {
                Logger::getInstance()->error("Error in io_context thread: {}", e.what());
            }
        });
        Logger::getInstance()->info("blabla");
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Error in io_context: {}", e.what());
    }
}

void ANetwork::stop() {
    io_context_.stop();
    if (io_thread_.joinable()) {
        io_thread_.join();
    }
    Logger::getInstance()->info("io_context stopped.");
}
