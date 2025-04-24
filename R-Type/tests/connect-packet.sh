#!/bin/bash

SERVER="./r-type_server ./config/rtypegame.json"
CLIENT="./r-type_client"

cleanup() {
    echo "Cleaning up..."
    pkill -f r-type_server || echo "Server already stopped."
    pkill -f r-type_client || echo "Client already stopped."
}
trap cleanup EXIT

echo "Starting server..."
$SERVER > server.log 2>&1 &
SERVER_PID=$!
sleep 1

echo "Starting client and waiting for SUCCESS_CONNECT packet..."
$CLIENT --name "Player1" > client.log 2>&1 &
CLIENT_PID=$!

sleep 5

if grep -q "Received UDP packet" server.log; then
    echo "Test passed: Server received CONNECT packet from client."
else
    echo "Test failed: Server did not receive CONNECT packet from client."
    echo "Server logs:"
    cat server.log
    TEST_FAILED=true
fi

if grep -q "Received SUCCESS_CONNECT" client.log; then
    echo "Test passed: Client received SUCCESS_CONNECT packet."
else
    echo "Test failed: Client did not receive SUCCESS_CONNECT packet."
    echo "Client logs:"
    cat client.log
    TEST_FAILED=true
fi

if [ "$TEST_FAILED" = true ]; then
    echo "Some tests failed."
    exit 0
else
    echo "All tests passed!"
    exit 0
fi
