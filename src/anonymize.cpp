/* Copyright (c) 2009-2010 Satoshi Nakamoto
   Copyright (c) 2009-2012 The Bitcoin developers
   Copyright (c) 2013-2014 The StealthCoin/StealthSend Developers */
/* Copyright (c) 2014, BritCoin Developers */
/* See LICENSE for licensing information */

#include "anonymize.h"
#include "util.h"

#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <cstring>

char const* anonymize_tor_data_directory(
) {
    static std::string const retrieved = (
        GetDefaultDataDir(
        ) / "tor"
    ).string(
    );
    return retrieved.c_str(
    );
}

char const* anonymize_service_directory(
) {
    static std::string const retrieved = (
        GetDefaultDataDir(
        ) / "onion"
    ).string(
    );
    return retrieved.c_str(
    );
}

int check_interrupted() {
    return boost::this_thread::interruption_requested() ? 1 : 0;
}
