//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_RESP_REFLECTION_H
#define APITEST_RESP_REFLECTION_H

#include "alpaca/response.h"
#include "alpaca/request.h"
#include "coinbase/response.h"
#include "coinbase/request.h"

BOOST_FUSION_ADAPT_STRUCT(
        Account,
        (bool, account_blocked),
        (string, account_number),
        (string, buying_power),
        (string, cash),
        (std::string, created_at),
        (std::string, currency),
        (int, daytrade_count),
        (string, daytrading_buying_power),
        (std::string, equity),
        (std::string, id),
        (string, initial_margin),
        (string, last_equity),
        (string, last_maintenance_margin),
        (string, long_market_value),
        (string, maintenance_margin),
        (string, multiplier),
        (bool, pattern_day_trader),
        (string, portfolio_value),
        (string, regt_buying_power),
        (string, short_market_value),
        (bool, shorting_enabled),
        (string, sma),
        (std::string, status),
        (bool, trade_suspended_by_user),
        (bool, trading_blocked),
        (bool, transfers_blocked))

BOOST_FUSION_ADAPT_STRUCT(
        Order,
        (std::string, asset_class),
        (std::string, asset_id),
        (std::string, canceled_at),
        (std::string, client_order_id),
        (std::string, created_at),
        (std::string, expired_at),
        (bool, extended_hours),
        (std::string, failed_at),
        (std::string, filled_at),
        (std::string, filled_avg_price),
        (std::string, filled_qty),
        (std::string, id),
        (bool, legs),
        (std::string, limit_price),
        (std::string, qty),
        (std::string, side),
        (std::string, status),
        (std::string, stop_price),
        (std::string, submitted_at),
        (std::string, symbol),
        (std::string, time_in_force),
        (std::string, type),
        (std::string, updated_at))

BOOST_FUSION_ADAPT_STRUCT(
        TakeProfit,
        (std::string, limit_price))

BOOST_FUSION_ADAPT_STRUCT(
        StopLoss,
        (std::string, stop_price),
        (std::string, limit_price))

BOOST_FUSION_ADAPT_STRUCT(
        OrderRequest,
        (std::string, symbol),
        (std::string, qty),
        (std::string, national),
        (std::string, side),
        (std::string, type),
        (std::string, time_in_force),
        (std::string, limit_price),
        (std::string, stop_price),
        (std::string, trail_price),
        (std::string, trail_percent),
        (std::string, extended_hours),
        (std::string, limit_price),
        (std::string, client_order_id),
        (std::string, order_class),
        (TakeProfit, take_profit),
        (StopLoss, stop_loss))

BOOST_FUSION_ADAPT_STRUCT(
        Position,
        (std::string, asset_class),
        (std::string, asset_id),
        (std::string, avg_entry_price),
        (std::string, change_today),
        (std::string, cost_basis),
        (std::string, current_price),
        (std::string, exchange),
        (std::string, lastday_price),
        (std::string, market_value),
        (std::string, qty),
        (std::string, side),
        (std::string, symbol),
        (std::string, unrealized_intraday_pl),
        (std::string, unrealized_intraday_plpc),
        (std::string, unrealized_pl),
        (std::string, unrealized_plpc))

BOOST_FUSION_ADAPT_STRUCT(
        PortfolioHistoryRequest,
        (std::string, period),
        (std::string, timeframe),
        (std::string, date_end),
        (bool, extended_hours))

BOOST_FUSION_ADAPT_STRUCT(
        PortfolioHistory,
        (double, base_value),
        (std::vector<double>, equity),
        (std::vector<double>, profit_loss),
        (std::vector<double>, profit_loss_pct),
        (std::string, timeframe),
        (std::vector<uint64_t>, timestamp))

BOOST_FUSION_ADAPT_STRUCT(
        CoinBaseUser,
        (std::string, id),
        (std::string, name),
        (std::string, username),
        (std::string, profile_location),
        (std::string, profile_bio),
        (std::string, profile_url),
        (std::string, avatar_url),
        (std::string, resource),
        (std::string, resource_path))

#endif //APITEST_RESP_REFLECTION_H
