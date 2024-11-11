package server_client;

// Define the network with a load balancer, two servers, and five clients
network MultiServerNetwork {
    submodules:
        balancer: LoadBalancer;              // Load balancer to distribute requests
        server[2]: ServerNode;               // Two server nodes
        client[5]: ClientNode;               // Five client nodes
    connections allowunconnected:
        for i=0..4 {
            client[i].out --> balancer.in[i];            // Connect each client to the balancer's inputs
            balancer.out[i % 2] --> server[i % 2].in;    // Alternate connections to the two servers
            server[i % 2].out --> client[i].in;          // Each server connects back to its client
        }
}

// Define the server node
simple ServerNode {
    parameters:
        double processingTime @unit(s);    // Server processing time in seconds
    gates:
        input in;                          // Input gate for receiving messages
        output out;                        // Output gate for sending messages
}

// Define the client node
simple ClientNode {
    parameters:
        double sendInterval @unit(s);      // Client send interval in seconds
    gates:
        input in;                          // Input gate for receiving responses
        output out;                        // Output gate for sending requests
}

// Define the load balancer node
simple LoadBalancer {
    gates:
        input in[5];                       // Input gates to receive messages from clients
        output out[2];                     // Output gates to distribute messages to two servers
}
