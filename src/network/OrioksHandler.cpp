#include "OrioksHandler.hpp"
#include <cstdint>

using namespace net;

cpr::Header operator+(const cpr::Header& lh, const cpr::Header& rh) {
    cpr::Header result = lh;
    for (const auto& [key, value] : rh) {
        result[key] = value;
    }
    return result;
}

OrioksHandler::OrioksHandler() {
    init();
}

OrioksHandler::~OrioksHandler() { }

void OrioksHandler::init() { }

cpr::Response OrioksHandler::get(const std::string& extra_path, const cpr::Header& extra_header) {
    if(api_token_.empty())
        throw std::runtime_error("API token is not set");
    cpr::Session session{};
    session.SetUrl(make_url(extra_path));
    cpr::Header auth_header = {{"Authorization","Bearer " + api_token_}};
    session.SetHeader(make_header(extra_header + auth_header));
    session.SetTimeout(cpr::Timeout{7000});
    return session.Get();
}

cpr::Response OrioksHandler::checkConnection() {
    cpr::Session check_session{};
    check_session.SetUrl(cpr::Url{__TEST_JSON_API_URL__});
    check_session.SetTimeout(cpr::Timeout{7000});
    return check_session.Get();
}

cpr::Url OrioksHandler::make_url(const std::string& extra_path) {
    return cpr::Url{base_url_ + extra_path};
}

cpr::Header OrioksHandler::make_header(const cpr::Header& extra_header) {
    cpr::Header header = standard_header;
    for (const auto& [key, value] : extra_header) {
        header[key] = value;
    }
    return header;
}
