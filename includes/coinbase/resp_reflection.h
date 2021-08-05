//
// Created by dewe on 7/30/21.
//

#ifndef APITEST_RESP_REFLECTION_H
#define APITEST_RESP_REFLECTION_H

#include <boost/lexical_cast.hpp>
#include <boost/fusion/adapted.hpp>
#include "coinbase/response.h"

BOOST_FUSION_ADAPT_STRUCT(
        CoinBaseAccount,
        (std::string, id),
        (std::string, name),
        (bool, primary),
        (std::string, type),
        (std::string, currency),
        (MoneyHash, balance),
        (std::string, created_at),
        (std::string, updated_at),
        (std::string, resources),
        (std::string, resource_path))

BOOST_FUSION_ADAPT_STRUCT(
        MoneyHash,
        (float, amount),
        (std::string, currency))



#endif //APITEST_RESP_REFLECTION_H
