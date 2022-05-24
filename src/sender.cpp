#include "spoofy/sender.h"

#include <memory>
#include <tins/tins.h>

// Context
Sender::Sender(std::unique_ptr<SendingStrategy> sender) : sender_(std::move(sender)) {}
Sender::~Sender() = default;
void Sender::send_packet(Tins::Packet &p) { sender_->send(*p.pdu()); } // might not work as expected
void Sender::set_sender(std::unique_ptr<SendingStrategy> sending_strategy) { sender_ = std::move(sending_strategy); }

// Sending packets to Apache Kafka
void KafkaSender::send(Tins::PDU &p) {
    //TODO next ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// Sending packets over the network
NetworkSender::NetworkSender(const char *interface) : 
    interface_(interface), packet_sender_(std::move(Tins::PacketSender(interface_))) {}
void NetworkSender::set_interface(const char* interface) {
    packet_sender_.default_interface(Tins::NetworkInterface(interface));
}
void NetworkSender::send(Tins::PDU &pdu) {
    packet_sender_.send(pdu);
}
