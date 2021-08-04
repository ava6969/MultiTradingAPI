//
// Created by dewe on 8/2/21.
//

#ifndef APITEST_REQUEST_H
#define APITEST_REQUEST_H

struct TakeProfit{
    std::string limit_price;
};

struct StopLoss{
    std::string stop_price, limit_price;
};

struct OrderRequest{
    std::string symbol,
    qty,
    national,
    side,
    type,
    time_in_force,
    limit_price,
    stop_price,
    trail_price,
    trail_percent,
    extended_hours,
    client_order_id,
    order_class;
    TakeProfit take_profit;
    StopLoss stop_loss;
};

struct PortfolioHistoryRequest{
    std::string period;
    std::string timeframe;
    std::string date_end;
    bool extended_hours;
};

#endif //APITEST_REQUEST_H
