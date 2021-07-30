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
#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/RequestBuilder.h"

using namespace restc_cpp;
using std::string;
using std::setfill;
using namespace std::string_literals;

namespace live_broker
{
    class Coinbase {


    private:
        const std::string API_KEY, SECRET_KEY;

        std::unique_ptr<RestClient> client;

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

        auto AccessSign()
        {

        }

    public:
        Coinbase(std::string  API_KEY, std::string  SECRET_KEY)
        :API_KEY(std::move(API_KEY)),
        SECRET_KEY(std::move(SECRET_KEY)),
        client(RestClient::Create())
        {

        }

        auto GetAccount()
        {
            try {
                auto account = client->ProcessWithPromiseT<CoinBaseAccount>([&](Context& ctx){

                    CoinBaseAccount account;
                    auto request_path = "/v2/accounts"s;
                    auto request = "https://api.coinbase.com"s.append(request_path);
                    std::string ts = std::to_string(std::chrono::duration_cast<std::chrono::seconds>
                            (std::chrono::high_resolution_clock::now().time_since_epoch()).count());
                    auto sign = ts + "GET"s + request_path + "";

                    sign = hmac(SECRET_KEY, sign);

                    SerializeFromJson(account, RequestBuilder(ctx).Get(request)
                    // Add some headers for good taste
                    .Header("CB-ACCESS-KEY", API_KEY)
                    .Header("CB-ACCESS-SIGN", sign)
                    .Header("CB-ACCESS-TIMESTAMP", ts).Execute());
                    return account;
                        }).get();
            }catch(std::exception const& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }
    };

}


#endif //APITEST_COINBASE_H
