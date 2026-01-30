#ifndef ORIOKS_HANDLER_HPP
#define ORIOKS_HANDLER_HPP

#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "config.hpp"

namespace net {
    class OrioksHandler {
    public:
        OrioksHandler();
        ~OrioksHandler();

        void init();

    private:
        cpr::Session session{};

        std::string base_url{__ORIOKS_API_URL__};
        std::string api_token{};
    };
}

#endif // ORIOKS_HANDLER_HPP
