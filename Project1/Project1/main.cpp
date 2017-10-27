#include <iostream>
#include <vector>

struct auctioneer;

// observer
struct bidder {
    bidder(auctioneer *a);
    void imUpdatingTheBid(int bid);
    void update(int new_bid);
private:
    auctioneer *m_auctioneer;
    int global_bid;
};

// subject
struct auctioneer {
    auctioneer() { bid = 10; }
    void add_bidder(bidder *b);
    void set_bid(int new_bid);
    int get_bid() const { return bid; }
private:
    void notify();
private:
    std::vector<bidder *> bidders;
    int bid;
};

bidder::bidder(auctioneer *a) : m_auctioneer(a), global_bid(m_auctioneer->get_bid()) {
    m_auctioneer->add_bidder(this);
}

void bidder::imUpdatingTheBid(int bid) {
    m_auctioneer->set_bid(bid);
    std::cout << "global bid: " << global_bid << '\n';
}
void bidder::update(int new_global_bid) {
    global_bid = new_global_bid;
}

void auctioneer::add_bidder(bidder *b) { bidders.push_back(b); }
void auctioneer::set_bid(int new_bid) { 
    if(new_bid >= 5) { 
        bid += new_bid;
        notify();
    } 
}
void auctioneer::notify() {
    for(auto bidder : bidders)
        bidder->update(bid);
}

int main() {

    auctioneer *a = new auctioneer;

    bidder *b1 = new bidder(a);
    bidder *b2 = new bidder(a);
    bidder *b3 = new bidder(a);
    bidder *b4 = new bidder(a);

    b1->imUpdatingTheBid(6);
    std::cout << "-------------------------------\n";

    b3->imUpdatingTheBid(8);
    std::cout << "-------------------------------\n";

    b4->imUpdatingTheBid(4);
    std::cout << "-------------------------------\n";

    b2->imUpdatingTheBid(10);
    std::cout << "-------------------------------\n";

    std::cin.get();
    return 0;
}
