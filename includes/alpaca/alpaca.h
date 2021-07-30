//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_ALPACA_H
#define APITEST_ALPACA_H

#include <utility>

#include "alpaca/resp_reflection.h"
#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/RequestBuilder.h"

#define BOOST_LOG_DYN_LINK 1

using namespace restc_cpp;
using std::vector;
namespace live_broker
{
    class Alpaca {

    private:
        const std::string API_KEY, SECRET_KEY, BASE_URL;
        std::unique_ptr<RestClient> client;

        template<typename T>
        T Get(std::function<std::unique_ptr<Reply>(RequestBuilder&&)>&& reply_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Get(BASE_URL + "/v2/account")
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));

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
                    auto reply = reply_fn(std::move(RequestBuilder(ctx).Post(BASE_URL + "/v2/account")
                            // Add some headers for good taste
                            .Header("APCA-API-KEY-ID", API_KEY)
                            .Header("APCA-API-SECRET-KEY", SECRET_KEY)));

                    SerializeFromJson(data, std::move(reply));
                    return data;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
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
            return Get<Account>([](RequestBuilder&& builder)
            {
                return builder.Execute();
            });
        }

        auto GetOrders()
        {
            try {
                return client->ProcessWithPromiseT<vector<Order>>([&](Context& ctx)
                {
                    vector<Order> orders;

                    SerializeFromJson(orders, RequestBuilder(ctx).Get(BASE_URL + "/v2/orders")
                    // Add some headers for good taste
                    .Header("APCA-API-KEY-ID", API_KEY)
                    .Header("APCA-API-SECRET-KEY", SECRET_KEY).Execute());
                    return orders;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        auto GetOrder(Order const& order)
        {
            try {
                return client->ProcessWithPromiseT<vector<Order>>([&](Context& ctx)
                {
                    vector<Order> orders;
                    SerializeFromJson(orders, RequestBuilder(ctx).Get(BASE_URL + "/v2/orders")
                    .Argument("order_id", order.id)
                    // Add some headers for good taste
                    .Header("APCA-API-KEY-ID", API_KEY)
                    .Header("APCA-API-SECRET-KEY", SECRET_KEY).Execute());
                    return orders;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        auto PlaceNewMarketOrder(string const& symbol, float amt, float qty, bool buy) {
            try {
                return client->ProcessWithPromiseT<Order>([&](Context& ctx)
                {
                    Order order;
                    SerializeFromJson(order, RequestBuilder(ctx).Post(BASE_URL + "/v2/orders")
                    .Argument("symbol", symbol)
                    .Argument("qty", std::to_string(qty))
                    .Argument("notional", std::to_string(amt))
                    .Argument("side", buy ? "buy" : "sell")
                    .Argument("type", "market")
                    .Argument("time_in_force", "gtc")
                    .Argument("limit_", "gtc")
                    .Header("APCA-API-KEY-ID", API_KEY)
                    .Header("APCA-API-SECRET-KEY", SECRET_KEY).Execute());
                    return order;
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

       vector<Position> GetOpenPositions()
       {
            return {};
       }


       ~Alpaca()
       {
            client->CloseWhenReady(true);
       }

    };
}



#endif //APITEST_ALPACA_H
