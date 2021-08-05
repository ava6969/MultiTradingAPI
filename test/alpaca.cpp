#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <iostream>
#include "alpaca/alpaca.h"

TEST_CASE("Alpaca"){

    const string API_KEY = "AK77Y19ZEHJ3K764M9GR";
    const string SECRET_KEY = "KwjAOHWFgIFnmfFXfw9kTqjdciEILjP7QT6kOiMf";

    const string PAPER_API_KEY = "PKU8PRISWFDX7M3H67ZN";
    const string PAPER_SECRET_KEY = "nYU6cPkk4TmmHwdcPd8ykoikQ11TnOuMV5MDlEoh";

    setenv("ALPACA_API_KEY", PAPER_API_KEY.c_str(), 1);
    setenv("ALPACA_SECRET_KEY", PAPER_SECRET_KEY.c_str(), 1);

    broker::Alpaca alpaca1(false);

    std::cout << "All Orders:\n";

    for(auto const& order : alpaca1.GetOrders(broker::Alpaca::ALL, {"AAPL"}))
    {
        std::cout << order.id << "\t" << order.status << "\t" << order.symbol << "\n";
    }

//    auto order = alpaca1.PlaceMarketOrder("AAPL", 22, false);

    std::cout << alpaca1.GetAccount().portfolio_value << "\n";

//    auto history = alpaca1.GetAccountPortfolioHistory(
//            {"7D",
//             "1Min",
//             "",
//             false });
//
//    std::cout << history.base_value << "\n";
//    std::cout << history.timeframe << "\n";
//
//    auto equity_it = history.equity.begin();
//    auto pl_it = history.profit_loss.begin();
//    auto pl_pct_it = history.profit_loss_pct.begin();
//
//    for(auto const& ts : history.timestamp)
//    {
//        std::cout << ts << "\t" << *equity_it << "\t" << *pl_it << "\t" << *pl_pct_it << "\n";
//        equity_it++;
//        pl_it++;
//        pl_pct_it++;
//    }

//    std::cout << order->id << "\n";

//    std::cout << "Get An Order:\n";
//    auto order_ = alpaca1.GetOrderWithClientID(order->client_order_id);
//    std::cout << order_->id << "\t" << order_->status << "\t" << order_->symbol << "\n";

//    alpaca1.CancelOrder(order_->id);

//    auto position = alpaca1.GetAnOpenPosition("AAPL");
//    std::cout << position.asset_id << "\t" << position.symbol << "\t" << position.side
//    << "\t" << position.qty << "\t" << position.market_value << "\n";
//
//    alpaca1.CloseAllPositions();
//
//    for(auto const& position : alpaca1.GetOpenPositions())
//        std::cout << position.asset_id << "\t" << position.symbol << "\t" << position.side
//        << "\t" << position.qty << "\t" << position.market_value << "\n";


}
