//
// Created by dewe on 7/30/21.
//

#pragma once

#include <nlohmann/json.hpp>
// for convenience

#define PARSE(attr) this->attr = data[# attr].is_null() ? "" : data[# attr]
#define PARSE_FLOAT(attr) this->attr = data[# attr].is_null() ? 0.f : std::stof(data[# attr].get<std::string>())
#define PARSE_BOOL(attr) this->attr = data[# attr].is_null() ? false : data[# attr].get<std::string>() == "true"
#define PARSE_MONEY_HASH(attr) this->attr = data[# attr].is_null() ? MoneyHash{} : MoneyHash(data[# attr]);

using json = nlohmann::json;

struct MoneyHash{
    float amount{};
    std::string currency{};

    MoneyHash()=default;
    explicit MoneyHash(nlohmann::json const& data)
    {
        PARSE(currency);
        PARSE_FLOAT(amount);
    }
};

struct CoinBaseAccount{
    std::string id;
    std::string name;
    bool primary{};
    std::string type;
    std::string currency;
    MoneyHash balance;
    std::string created_at;
    std::string updated_at;
    std::string resources;
    std::string resource_path;

    CoinBaseAccount()=default;
    explicit CoinBaseAccount(nlohmann::json const& _json)
    {
        auto data = _json["data"][0];
        PARSE(name);
        PARSE(id);
        PARSE_BOOL(primary);
        PARSE(type);
        PARSE(currency);
        PARSE_MONEY_HASH(balance);
        PARSE(created_at);
        PARSE(updated_at);
        PARSE(resources);
        PARSE(resource_path);
    }
};

struct CoinBaseUser{

    std::string id;
    std::string name;
    std::string username,
    profile_location,
    profile_bio,
    profile_url,
    avatar_url,
    resource,
    resource_path;

    CoinBaseUser()=default;
    explicit CoinBaseUser(nlohmann::json const& _json)
    {
        auto data = _json["data"];

        PARSE(name);
        PARSE(id);
        PARSE(avatar_url);
        PARSE(username);
        PARSE(profile_location);
        PARSE(profile_bio);
        PARSE(profile_url);
        PARSE(resource);
        PARSE(resource_path);
    }
};

struct Resource{

    std::string id;
    std::string status;
    std::string payment_method,
    transaction;

    MoneyHash amount,
    total,
    subtotal,
    fee;

    std::string created_at,
    updated_at,
    resource,
    resource_path,
    profile_bio,
    payout_at;

    bool committed{},
    instant{};

    Resource()=default;
    explicit Resource(nlohmann::json const& _json)
    {
        auto data = _json["data"];

        PARSE(status);
        PARSE(id);
        PARSE(payment_method);
        PARSE(transaction);
        PARSE(created_at);
        PARSE(updated_at);
        PARSE(resource);
        PARSE(resource_path);
        PARSE(profile_bio);
        PARSE(payout_at);
        PARSE_MONEY_HASH(amount);
        PARSE_MONEY_HASH(total);
        PARSE_MONEY_HASH(subtotal);
        PARSE_MONEY_HASH(fee);
        PARSE_BOOL(committed);
        PARSE_BOOL(instant);
    }
};

struct Transaction{

    std::string id;
    std::string type;
    std::string status, description;

    MoneyHash amount,
    native_amount;

    std::string created_at,
    updated_at,
    resource,
    resource_path,
    details,
    network,to, from, address, application;

    Transaction()=default;
    explicit Transaction(nlohmann::json const& _json)
    {
        auto data = _json["data"];

        PARSE(status);
        PARSE(id);
        PARSE(type);
        PARSE(description);
        PARSE(created_at);
        PARSE(updated_at);
        PARSE(resource);
        PARSE(resource_path);
        PARSE(network);
        PARSE(to);
        PARSE(from);
        PARSE(address);
        PARSE(application);
        PARSE(details);

        PARSE_MONEY_HASH(amount);
        PARSE_MONEY_HASH(native_amount);
    }
};