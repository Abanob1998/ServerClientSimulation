#include <omnetpp.h>

using namespace omnetpp;

// Client node that sends requests at regular intervals
class ClientNode : public cSimpleModule {
  private:
    cMessage *sendRequestEvent;

  protected:
    virtual void initialize() override {
        // Initialize and schedule the first request event
        sendRequestEvent = new cMessage("sendRequest");
        scheduleAt(simTime() + par("sendInterval").doubleValue(), sendRequestEvent);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == sendRequestEvent) {
            // Send a new request to the load balancer
            cMessage *request = new cMessage("request");
            send(request, "out");

            // Schedule the next request
            scheduleAt(simTime() + par("sendInterval").doubleValue(), sendRequestEvent);
        } else {
            // Receive response from server and delete message
            delete msg;
        }
    }

    virtual ~ClientNode() {
        cancelAndDelete(sendRequestEvent);
    }
};

Define_Module(ClientNode);
