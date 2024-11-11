#include <omnetpp.h>

using namespace omnetpp;

// Server node that processes requests with a delay
class ServerNode : public cSimpleModule {
  protected:
    virtual void handleMessage(cMessage *msg) override {
        // Simulate processing delay
        scheduleAt(simTime() + par("processingTime").doubleValue(), msg);
        send(msg, "out");  // Send response back to client after delay
    }
};

Define_Module(ServerNode);
