//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_ALPACA_H
#define APITEST_ALPACA_H

#include <utility>

#include "alpaca/reflections.h"
#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/RequestBuilder.h"

#define BOOST_LOG_DYN_LINK 1
using namespace std::string_literals;

using namespace restc_cpp;
using std::vector;

namespace live_broker
{

    class Alpaca {

    public:
        enum OrderStatus{
        OPEN,
        CLOSED,
        ALL
        };

    private:
        const std::string API_KEY, SECRET_KEY, BASE_URL;
        std::unique_ptr<RestClient> client;
        std::string base;


        void Delete(std::function<std::unique_ptr<Reply>(RequestBuilder&&)>&& reply_fn) {
            try {
                return client->Process([&](Context& ctx)
                {
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Delete(base)
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));
                    auto result = reply->GetResponseCode();
                });
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        template<typename T>
        T Get(std::function<std::unique_ptr<Reply>(RequestBuilder&&)>&& reply_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Get(base)
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));
                    auto result = reply->GetResponseCode();
                    SerializeFromJson(data, std::move(reply));
                    return data;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        template<typename T>
        T GetRaw(std::function<std::unique_ptr<Reply>(RequestBuilder&&)>&& reply_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Get(base)
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));
                    auto result = reply->GetResponseCode();
                    SerializeFromJson(data, std::move(reply));
                    return data;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }


        template<typename T>
        T Post(std::function<std::unique_ptr<Reply>(RequestBuilder&&)>&& reply_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Post(base)
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));
                    auto result = reply->GetResponseCode();
                    SerializeFromJson(data, std::move(reply));
                    return data;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        auto set_method(std::string const& method)
        {
            base = BASE_URL + "/v2/"s.append(method);
        }

    public:
        Alpaca(bool live, std::string  API_KEY, std::string  SECRET_KEY)
        :API_KEY(std::move(API_KEY)),
        SECRET_KEY(std::move(SECRET_KEY)),
        client(RestClient::Create()),
        BASE_URL(live ? "https://api.alpaca.markets" : "https://paper-api.alpaca.markets" )
        {

        }

        auto GetAccount()
        {
            set_method("account");
            return Get<Account>([](RequestBuilder&& builder)
            {
                return builder.Execute();
            });
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
                return Get<vector<Order>>([&order_status, &sym](RequestBuilder&& builder){
                    return builder
                    .Argument("status", order_status)
                    .Argument("symbols", sym)
                    .Execute();
                });
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }

            return vector<Order>{};
        }

        std::optional<Order>  GetOrder(std::string const& order_id)
        {
            try{
                set_method("orders/"s.append(order_id));
                return Get<Order>([](RequestBuilder&& builder){
                    return builder
                    .Execute();
                });
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }
            return std::nullopt;

        }

        std::optional<Order>  GetOrderWithClientID(std::string const& client_order_id)
        {
            set_method("orders:by_client_order_id");
            try{
                return Get<Order>([&client_order_id](RequestBuilder&& builder){
                    return builder
                    .Argument("client_order_id", client_order_id)
                    .Execute();
                });
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }
            return std::nullopt;
        }

        std::optional<Order> PlaceMarketOrder(string const& symbol, float qty, bool buy) {
            OrderRequest body;
            body.symbol = symbol;
            body.qty = std::to_string(qty);
            body.side = buy ? "buy" : "sell";
            body.type = "market";
            body.time_in_force = "day";

            set_method("orders");

            try {
                return Post<Order>([&](RequestBuilder&& builder){
                    return builder
                    .Data(body)
                    .Execute();
                });
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }
            return std::nullopt;
        }

        auto CancelAllOpenOrders() {

            set_method("orders");
            try {
                Delete([&](RequestBuilder&& builder){
                    return builder
                    .Execute();
                });
                return true;
            }catch(std::exception const& ex)
            {
                std::cerr << ex.what() << "\n";
            }
            return false;
        }

        auto CancelOrder(std::string const& order_id) {
            set_method("orders/"s.append(order_id));
            try {
                Delete([&](RequestBuilder&& builder){
                    return builder
                    .Execute();
                });
                return true;
            }catch(std::runtime_error const& ex)
            {
                std::cerr << ex.what() << "\n";
            }
            return false;

        }

       vector<Position> GetOpenPositions()
       {
           set_method("positions");
           return Get<vector<Position>>([](RequestBuilder&& builder){
               return builder.Execute();
           });
       }

       auto GetAnOpenPosition(std::string const& symbol)
       {
           set_method("positions/"s.append(symbol));
           return Get<Position>([](RequestBuilder&& builder){
               return builder
               .Execute();
           });
       }

       bool CloseAllPositions()
       {
           try {
               set_method("positions");
               Delete([](RequestBuilder&& builder){
                   return builder.
                   Argument("cancel_orders", true).
                   Execute();
               });
               return true;
           }catch (const std::exception& ex) {
               std::cout << "Caught exception: " << ex.what() << std::endl;
           }
           return false;
       }

       bool CloseAnOpenPosition(std::string const& symbol)
       {
            try {
                set_method("positions/"s.append(symbol));
                Delete([](RequestBuilder&& builder){
                    return builder.
                    Argument("cancel_orders", true).
                    Execute();
                });
                return true;
            }catch (const std::exception& ex) {
                std::cout << "Caught exception: " << ex.what() << std::endl;
            }
            return false;
       }

       PortfolioHistory GetAccountPortfolioHistory(PortfolioHistoryRequest const& portfolioHistory)
       {
            try {
                set_method("account/portfolio/history");

                return Get<PortfolioHistory>([&portfolioHistory](RequestBuilder&& builder){
                    return builder.
                    Data(portfolioHistory).
                    Execute();
                });
            }catch (const std::exception& ex) {
                std::cout << "Caught exception: " << ex.what() << std::endl;
            }
            return {};
       }

       ~Alpaca()
       {
            client->CloseWhenReady(true);
       }

    };
}



#endif //APITEST_ALPACA_H
