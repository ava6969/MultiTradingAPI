#include <iostream>
#include "catch2/catch.hpp"
#include "coinbase/coinbase.h"

TEST_CASE("CoinBase Account"){

    setenv("COINBASE_API_KEY", "0L4Rj05foc6J1rTj", 1);
    setenv("COINBASE_SECRET_KEY", "cHFSSklDnZFGPJ1sNjZ5bO1wyQz2RNkT", 1);

    broker::Coinbase coinbase;

//    auto user = coinbase.GetUser();
    auto account = coinbase.GetAccount();

    std::cout << account.name << "\n";
}
