#include "OrioksHandler.hpp"

using namespace net;

OrioksHandler::OrioksHandler() {
    init();
}

OrioksHandler::~OrioksHandler() { }

void OrioksHandler::init() {
    session.SetUrl(cpr::Url{__ORIOKS_API_URL__});
    session.SetTimeout(cpr::Timeout{7000});
    session.SetHeader(cpr::Header{{"Accept",    "application/json"},
                                  {"User-Agent","ProOrioks/" __APP_VERSION__ " " __BUILD_OS__}});
}
