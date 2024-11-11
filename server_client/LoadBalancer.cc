#include <omnetpp.h>

using namespace omnetpp;

// Load balancer that distributes requests between two servers
class LoadBalancer : public cSimpleModule {
  private:
    int nextServerIndex = 0;  // To alternate between server[0] and server[1]

  protected:
    virtual void handleMessage(cMessage *msg) override {
        // Send request to the next server in a round-robin fashion
        send(msg, "out", nextServerIndex);

        // Alternate between server[0] and server[1]
        nextServerIndex = (nextServerIndex + 1) % 2;
    }
};

Define_Module(LoadBalancer);
