//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_RESPONSE_H
#define APITEST_RESPONSE_H

namespace live_broker
{
    struct MoneyHash{
        float amount;
        std::string currency;
    };

    struct CoinBaseAccount{
        std::string id;
        std::string name;
        bool primary;
        std::string type;
        std::string currency;
        MoneyHash balance;
        std::string created_at;
        std::string updated_at;
        std::string resources;
        std::string resource_path;
    };
}


#endif //APITEST_RESPONSE_H
