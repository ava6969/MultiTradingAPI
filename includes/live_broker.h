//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_LIVE_BROKER_H
#define APITEST_LIVE_BROKER_H

#include <utility>
#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/RequestBuilder.h"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;
using namespace restc_cpp;
using namespace std::string_literals;

namespace broker
{
    class LiveBroker{

    protected:
        const std::string API_KEY, SECRET_KEY, BASE_URL;
        std::unique_ptr<RestClient> client;
        std::string base, command_type;

        virtual void set_method(std::string const& method)
        {
            base = BASE_URL + "/v2/"s.append(method);
        }

        virtual void authenticate(RequestBuilder& builder)=0;

        template<typename T>
        T Get(std::function<void(RequestBuilder&)>&& option_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;
                    command_type = "GET";
                    RequestBuilder builder(ctx);
                    authenticate(builder.Get(base));
                    option_fn(builder);

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();
                    SerializeFromJson(data, std::move(reply));
                    return data;

                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
            return {};
        }

        template<typename T> T Get() {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;

                    RequestBuilder builder(ctx);
                    command_type = "GET";

                    authenticate(builder.Get(base));

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                    SerializeFromJson(data, std::move(reply));

                    return data;

                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
            return {};
        }

        void Delete() {
            try {
                return client->Process([&](Context& ctx)
                {
                    RequestBuilder builder(ctx);

                    command_type = "DELETE";
                    authenticate(builder.Delete(base));
                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                });
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        void Delete(std::function<void(RequestBuilder&)>&& option_fn) {
            try {
                return client->Process([&](Context& ctx)
                {
                    RequestBuilder builder(ctx);
                    command_type = "DELETE";
                    authenticate(builder.Delete(base));
                    option_fn(builder);

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                });
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

        template<typename T>
        T Post(std::function<void(RequestBuilder&)>&& options_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    T data;

                    RequestBuilder builder(ctx);
                    command_type = "POST";
                    authenticate(builder.Get(base));
                    options_fn(builder);

                    auto reply = builder.Execute();
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
        T GetRaw(std::function<void(RequestBuilder&)>&& option_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    command_type = "GET";
                    RequestBuilder builder(ctx);
                    authenticate(builder.Get(base));
                    option_fn(builder);

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                    return T(nlohmann::json::parse(reply->GetBodyAsString()));
                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
            return {};
        }

        template<typename T> T GetRaw() {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    RequestBuilder builder(ctx);
                    command_type = "GET";

                    authenticate(builder.Get(base));

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                    return T(nlohmann::json::parse(reply->GetBodyAsString()));

                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
            return {};
        }

        template<typename T>
        T PostRaw(std::function<void(RequestBuilder&)>&& options_fn) {
            try {
                return client->ProcessWithPromiseT<T>([&](Context& ctx)
                {
                    RequestBuilder builder(ctx);
                    command_type = "POST";
                    authenticate(builder.Get(base));
                    options_fn(builder);

                    auto reply = builder.Execute();
                    auto result = reply->GetResponseCode();

                    return T(nlohmann::json::parse(reply->GetBodyAsString()));

                }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }

    public:
        LiveBroker(std::string  base_url,
                   std::string  API_KEY,
                   std::string  SECRET_KEY):
        API_KEY(std::move(API_KEY)),
        SECRET_KEY(std::move(SECRET_KEY)),
        BASE_URL(std::move(base_url)),
        client(RestClient::Create())
        {}



    };
}


#endif //APITEST_LIVE_BROKER_H
