//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_RESPONSE_H
#define APITEST_RESPONSE_H

#include <boost/lexical_cast.hpp>
#include <boost/fusion/adapted.hpp>

using std::string;

struct Account {
    bool account_blocked;
    std::string account_number;
    std::string buying_power;
    std::string cash;
    std::string created_at;
    std::string currency;
    int daytrade_count;
    std::string daytrading_buying_power;
    std::string equity;
    std::string id;
    std::string initial_margin;
    std::string last_equity;
    std::string last_maintenance_margin;
    std::string long_market_value;
    std::string maintenance_margin;
    std::string multiplier;
    bool pattern_day_trader;
    std::string portfolio_value;
    std::string regt_buying_power;
    std::string short_market_value;
    bool shorting_enabled;
    std::string sma;
    std::string status;
    bool trade_suspended_by_user;
    bool trading_blocked;
    bool transfers_blocked;
};

struct Order {
    std::string asset_class;
    std::string asset_id;
    std::string canceled_at;
    std::string client_order_id;
    std::string created_at;
    std::string expired_at;
    bool extended_hours;
    std::string failed_at;
    std::string filled_at;
    std::string filled_avg_price;
    std::string filled_qty;
    std::string id;
    bool legs;
    std::string limit_price;
    std::string qty;
    std::string side;
    std::string status;
    std::string stop_price;
    std::string submitted_at;
    std::string symbol;
    std::string time_in_force;
    std::string type;
    std::string updated_at;

};

class Asset{
    std::string asset_class;
    bool easy_to_borrow;
    std::string exchange;
    std::string id;
    bool marginable;
    bool shortable;
    std::string status;
    std::string symbol;
    bool tradable;
};

class Position{

    std::string asset_class;
    std::string asset_id;
    std::string avg_entry_price;
    std::string change_today;
    std::string cost_basis;
    std::string current_price;
    std::string exchange;
    std::string lastday_price;
    std::string market_value;
    std::string qty;
    std::string side;
    std::string symbol;
    std::string unrealized_intraday_pl;
    std::string unrealized_intraday_plpc;
    std::string unrealized_pl;
    std::string unrealized_plpc;
};

struct Portfolio{
    double base_value;
    std::vector<double> equity;
    std::vector<double> profit_loss;
    std::vector<double> profit_loss_pct;
    std::string timeframe;
    std::vector<uint64_t> timestamp;
};



#endif //APITEST_RESPONSE_H
