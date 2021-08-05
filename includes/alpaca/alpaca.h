//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_ALPACA_H
#define APITEST_ALPACA_H

#include <utility>
#include "live_broker.h"
#include "alpaca/reflections.h"

#define BOOST_LOG_DYN_LINK 1



using std::vector;

namespace broker
{

    class Alpaca : public LiveBroker {

    public:
        enum OrderStatus{
        OPEN,
        CLOSED,
        ALL
        };

    private:

        void authenticate(RequestBuilder& builder) override
        {
            builder.Header("APCA-API-KEY-ID", API_KEY)
            .Header("APCA-API-SECRET-KEY", SECRET_KEY);
        }

    public:
        explicit Alpaca(bool live):
        LiveBroker(live ? "https://api.alpaca.markets" : "https://paper-api.alpaca.markets",
                   getenv("ALPACA_API_KEY"),
                   getenv("ALPACA_SECRET_KEY")){

        }

        auto GetAccount()
        {
            set_method("account");
            return Get<Account>();
        }

        auto GetOrders(OrderStatus type, vector<std::string> const& symbols)
        {
            std::string  sym, order_status;
            for(auto const& s: symbols)
                sym += (s + ',');

            sym.pop_back();
            order_status = type == OrderStatus::OPEN ? "open" : OrderStatus::CLOSED == type ? "closed" : "all";

            set_method("orders");
            try{
                return Get<vector<Order>>([&order_status, &sym](RequestBuilder& builder){
                    builder
                    .Argument("status", order_status)
                    .Argument("symbols", sym);
                });
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }

            return vector<Order>{};
        }

        std::optional<Order>  GetOrder(std::string const& order_id)
        {
            set_method("orders/"s.append(order_id));
            return Get<Order>();
        }

        std::optional<Order>  GetOrderWithClientID(std::string const& client_order_id)
        {
            set_method("orders:by_client_order_id");
            return Get<Order>([&client_order_id](RequestBuilder& builder){
                builder
                .Argument("client_order_id", client_order_id);
            });
        }

        std::optional<Order> PlaceMarketOrder(string const& symbol, float qty, bool buy) {
            OrderRequest body;
            body.symbol = symbol;
            body.qty = std::to_string(qty);
            body.side = buy ? "buy" : "sell";
            body.type = "market";
            body.time_in_force = "day";

            set_method("orders");

            return Post<Order>([&](RequestBuilder& builder){
                builder
                .Data(body)
                .Execute();
            });
        }

        auto CancelAllOpenOrders() {
            set_method("orders");
            Delete();
        }

        auto CancelOrder(std::string const& order_id) {
            set_method("orders/"s.append(order_id));
            Delete();
        }

       vector<Position> GetOpenPositions(){
           set_method("positions");
           return Get<vector<Position>>();
       }

       auto GetAnOpenPosition(std::string const& symbol)
       {
           set_method("positions/"s.append(symbol));
           return Get<Position>();
       }

       bool CloseAllPositions()
       {
           set_method("positions");
           Delete([](RequestBuilder& builder){
               builder.
               Argument("cancel_orders", true);
           });
       }

       bool CloseAnOpenPosition(std::string const& symbol)
       {
            set_method("positions/"s.append(symbol));
            Delete([](RequestBuilder& builder){
                builder.
                Argument("cancel_orders", true);
            });
       }

       PortfolioHistory GetAccountPortfolioHistory(PortfolioHistoryRequest const& portfolioHistory)
       {
            set_method("account/portfolio/history");

            return Get<PortfolioHistory>([&portfolioHistory](RequestBuilder& builder){
                builder.
                Data(portfolioHistory);
            });
       }

       vector<Asset> GetAssets(string const& status,
                               string const& asset_class="us_equity") {

            set_method("account/assets");

            return Get<vector<Asset>>([&](RequestBuilder& builder)
            {
                builder
                .Argument("status", status)
                .Argument("asset_class", asset_class);
            });
       }

       Asset GetAnAsset(string const& asset_id) {

            set_method("account/assets/"s.append(asset_id));
            return Get<Asset>();

        }

        auto GetClock()
        {
            set_method("account/clock");
            return Get<Clock>();
        }

        vector<Calender> GetCalender(string const& start,
                                     string const& end) {
            set_method("account/calender");

            return Get<vector<Calender>>([&](RequestBuilder& builder)
            {
                builder
                .Argument("start", start)
                .Argument("end", end);
            });
        }


       ~Alpaca()
       {
            client->CloseWhenReady(true);
       }

    };


}



#endif //APITEST_ALPACA_H
