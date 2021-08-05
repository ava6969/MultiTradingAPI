//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_COINBASE_H
#define APITEST_COINBASE_H

#include "picosha2.h"
#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/ossl_typ.h"
#include "coinbase/response.h"
#include "coinbase/resp_reflection.h"
#include "live_broker.h"

using std::string;
using std::setfill;

namespace broker
{
    class Coinbase : public LiveBroker{

        enum OrderStatus{
            OPEN,
            PENDING,
            CLOSED,
            ALL
        };
    private:

        std::string signature, request_path, timestamp, body_str;
        string hmac(string const& key, string const& data)
        {
            unsigned int hash_sz = EVP_MAX_MD_SIZE;
            HMAC_CTX* ctx = HMAC_CTX_new();
            unsigned char* digest = HMAC(EVP_sha256(), key.c_str(), key.size(),
                                         (unsigned char*)data.c_str(), data.size(), NULL, &hash_sz);

            std::stringstream ss;
            ss<< std::setfill('0');
            for(int i=0;i< hash_sz ;++i){
                ss << std::hex << std::setw(2) << (unsigned int) digest[i];
            }
            HMAC_CTX_free(ctx);
            return ss.str();

        }

        void authenticate(RequestBuilder &builder) override
        {
            timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>
                    (std::chrono::high_resolution_clock::now().time_since_epoch()).count());

            auto message = timestamp + command_type + request_path + body_str;

            signature = hmac(SECRET_KEY, message);

            builder
            .Header("CB-ACCESS-KEY", API_KEY)
            .Header("CB-ACCESS-SIGN", signature)
            .Header("CB-ACCESS-TIMESTAMP", timestamp);
        }

        void set_method(std::string const& method) override
        {
            LiveBroker::set_method(method);
            request_path = "/v2/" + method;
        }

    public:
        Coinbase():
        LiveBroker("https://api.coinbase.com",
                   getenv("COINBASE_API_KEY"),
                   getenv("COINBASE_SECRET_KEY"))
        {

        }

        auto GetUser(){
            set_method("user");
            return GetRaw<CoinBaseUser>();
        }

        CoinBaseAccount GetAccount(){
            set_method("accounts");
            return GetRaw<CoinBaseAccount>();
        }

        auto GetOrders(OrderStatus type,
                       std::vector<std::string> const& account_ids)
        {

            for(auto id: account_ids)
            {
                set_method("accounts/");
            }

        }

    };

}


#endif //APITEST_COINBASE_H
