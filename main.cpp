#include <iostream>
#include "alpaca/alpaca.h"



int main() {

//    std::string CB_ACCESS_KEY = "FeO3wfCOmrCMZ69W",
//    SECRET_KEY = "Pews0p9mq3I1qmJTVNW2MSMwUgponbuR";


    const string API_KEY = "AK77Y19ZEHJ3K764M9GR";
    const string SECRET_KEY = "KwjAOHWFgIFnmfFXfw9kTqjdciEILjP7QT6kOiMf";

    const string PAPER_API_KEY = "PKU8PRISWFDX7M3H67ZN";
    const string PAPER_SECRET_KEY = "nYU6cPkk4TmmHwdcPd8ykoikQ11TnOuMV5MDlEoh";

    live_broker::Alpaca alpaca1(false, PAPER_API_KEY, PAPER_SECRET_KEY);

    auto account = alpaca1.GetAccount();
    for(auto const& order : alpaca1.GetOrders())
    {
        std::cout << order.id << "\n";
    }

    auto order = alpaca1.PlaceNewOrder("AAPL", 1, true);
    std::cout << order.id << "\n";

    for(auto const& _order : alpaca1.GetOrders())
    {
        std::cout << _order.id << "\n";
    }

    std::cout << account.buying_power << "\n";

    return 0;
}
