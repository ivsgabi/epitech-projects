=============================
Networking Library Documentation
=============================

Table of Contents
-----------------
1. `Overview <#overview>`_
2. `Key Features <#key-features>`_
3. `Dependencies <#dependencies>`_
4. `Setup <#setup>`_
5. `Usage <#usage>`_
   - `Server Setup <#server-setup>`_
   - `Client Setup <#client-setup>`_
6. `Packet Types <#packet-types>`_
7. `Internal Architecture <#internal-architecture>`_
8. `Extending the Library <#extending-the-library>`_

---

Overview
--------
The networking library provides an abstraction over TCP sockets for client-server communication using the `asio` library. It enables sending and receiving custom packets that are serialized into binary format.

The library is divided into two main components:
- **ServerNetwork**: Handles multiple clients, processes incoming packets, and dispatches responses.
- **ClientNetwork**: Connects to a server, sends packets, and processes responses asynchronously.

---

Key Features
------------
- **TCP Client-Server Communication**: Reliable data transfer using `asio::ip::tcp`.
- **Packet-Based Messaging**: Structured communication using `Packet` objects.
- **Asynchronous I/O**: Non-blocking communication for scalability.
- **Multi-Client Support**: The server can handle multiple clients simultaneously.
- **Custom Packet Types**: Easy to define new message types (e.g., `CONNECT`, `SUCCESS_CONNECT`).

---

Dependencies
------------
- **C++ Standard Library**: Requires C++17 or higher.
- **Asio Library**: For networking operations.
- **spdlog**: For logging.

---

Setup
-----
1. **Install Dependencies**:
   Install `asio` and `spdlog` libraries on your system.

2. **Clone the Repository**:
   .. code-block:: bash

      git clone <repo_url>
      cd <repo_directory>

3. **Build the Library**:
   Use CMake to build the library:

   .. code-block:: bash

      mkdir build && cd build
      cmake ..
      make

4. **Link the Library**:
   Add the library to your project and link it:

   .. code-block:: cmake

      target_link_libraries(my_app PRIVATE client_networking server_networking)

---

Usage
-----
### Server Setup
To set up a server that listens for client connections and processes packets:

.. code-block:: cpp

   #include "server/ServerNetwork.hpp"
   #include "Logger.hpp"

   int main() {
       Logger::setLevel(spdlog::level::info);

       ServerNetwork server(8080);

       try {
           server.connectTCP();
           server.run();
       } catch (const std::exception& e) {
           Logger::getInstance()->error("Server error: {}", e.what());
       }

       return 0;
   }

### Client Setup
To set up a client that connects to the server and sends packets:

.. code-block:: cpp

   #include "client/ClientNetwork.hpp"
   #include "Logger.hpp"

   int main() {
       Logger::setLevel(spdlog::level::info);

       ClientNetwork client("127.0.0.1", 8080);

       try {
           client.connectTCP();
           client.sendConnectPacket(1, "Player1");
           client.receiveAndDispatch(); // Begin receiving and dispatching packets
           client.run(); // Start the io_context loop
       } catch (const std::exception& e) {
           Logger::getInstance()->error("Client error: {}", e.what());
       }

       return 0;
   }

---

Packet Types
------------
Packets are used for communication between the client and server.
Each packet has a type and a payload.

- **CONNECT**: Sent by the client when connecting.
- **SUCCESS_CONNECT**: Sent by the server as an acknowledgment.

**Example Packet Creation**:

For `CONNECT`:

.. code-block:: cpp

   Packet packet = Packet::createConnectPacket(entity_id, "PlayerName");
   client.sendPacketTCP(packet);

For `SUCCESS_CONNECT`:

.. code-block:: cpp

   Packet response = Packet::createSuccessConnectPacket(entity_id);
   server.sendPacketTCP(response);

---

Internal Architecture
----------------------
The library uses `asio` for asynchronous communication and provides abstractions via `ANetwork`, `ServerNetwork`, and `ClientNetwork` classes.

### Class Diagram
- **ANetwork**: Base class for networking functionality.
  - Handles `tcp_socket_` initialization and common methods like `sendPacketTCP`, `receivePacket`, and `run`.

- **ServerNetwork** (inherits from ANetwork):
  - Manages a TCP acceptor for incoming connections.
  - Stores multiple client sockets in a map.
  - Dispatches packets to appropriate handlers.

- **ClientNetwork** (inherits from `ANetwork`):
  - Connects to the server via TCP.
  - Sends packets and receives responses asynchronously.

### Packet Flow
1. **Client Sends Packet**:
   - The client creates a packet using the `Packet` class.
   - Calls `sendPacketTCP()` to send the serialized packet to the server.

2. **Server Receives Packet**:
   - The server asynchronously reads incoming data.
   - Deserializes the data into a `Packet` object.
   - Dispatches the packet to the appropriate handler.

3. **Server Responds**:
   - The server creates a response packet.
   - Sends it back to the client using `sendPacketTCP()`.

4. **Client Receives Response**:
   - The client asynchronously reads the response packet.
   - Dispatches it to the appropriate handler based on the packet type.

---

Extending the Library
---------------------
To add new packet types and handlers:

1. **Update `PacketType` Enum**:

   .. code-block:: cpp

      enum class PacketType {
          CONNECT,
          SUCCESS_CONNECT,
          NEW_TYPE // Add your new packet type here
      };

2. **Add Serialization/Deserialization**:
   - Update the `Packet` class to handle the new packet type.

3. **Add a Handler**:
   - In `ServerNetwork::dispatchPacket` and `ClientNetwork::dispatchPacket`, add a case for the new packet type.

4. **Send and Handle the Packet**:
   - Use `sendPacketTCP()` to send and add a handler function to process the new packet.

---

Conclusion
----------
This networking library provides a solid foundation for building client-server applications using TCP and structured packets. It is modular, extensible, and built with asynchronous communication in mind.
