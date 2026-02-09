#ifndef PROORIOKS_SRC_NETWORK_ORIOKS_HANDLER_HPP
#define PROORIOKS_SRC_NETWORK_ORIOKS_HANDLER_HPP

#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include "config.hpp"

cpr::Header operator+(const cpr::Header& lh, const cpr::Header& rh);

namespace net {
    class OrioksHandler {
    public:
        OrioksHandler();
        ~OrioksHandler();

        void init();

        const std::string& get_base_url() const  { return base_url_; }

        void set_base_url(const std::string& url)    { base_url_ = url; }
        void set_api_token(const std::string& token) { api_token_ = token; }

        bool is_api_token_set() const { return !api_token_.empty(); }

        cpr::Response get(const std::string& extra_path, const cpr::Header& extra_header = {});
        cpr::Response checkConnection();

        cpr::Url make_url(const std::string& extra_path);

        cpr::Header make_header(const cpr::Header& extra_header);
        cpr::Header standard_header = {{"Accept",    "application/json"},
                                       {"User-Agent","ProOrioks/" __APP_VERSION__ " " __BUILD_OS__}};

    private:
        std::string base_url_{__ORIOKS_API_URL__};
        std::string api_token_{};
    };
}

#endif // PROORIOKS_SRC_NETWORK_ORIOKS_HANDLER_HPP
