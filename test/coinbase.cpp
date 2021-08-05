#include <iostream>
#include "catch2/catch.hpp"
#include "coinbase/coinbase.h"

TEST_CASE("CoinBase Account"){

    const char* API_KEY = "0L4Rj05foc6J1rTj";
    const char* SECRET_KEY = "cHFSSklDnZFGPJ1sNjZ5bO1wyQz2RNkT";

#ifdef _WIN32
    _putenv_s("COINBASE_API_KEY", API_KEY);
    _putenv_s("COINBASE_SECRET_KEY", SECRET_KEY);
#else
    setenv("COINBASE_API_KEY", API_KEY, 1);
    setenv("COINBASE_SECRET_KEY", SECRET_KEY, 1);
#endif
    broker::Coinbase coinbase;

//    auto user = coinbase.GetUser();
    auto account = coinbase.GetAccount();

    std::cout << account.name << "\n";
}
