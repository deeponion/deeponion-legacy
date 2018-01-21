/* Copyright (c) 2014, BritCoin Developers */
/* See LICENSE for licensing information */

/**
 * \file anonymize.h
 * \brief Headers for anonymize.cpp
 **/

#ifndef TOR_ANONYMIZE_H
#define TOR_ANONYMIZE_H

#ifdef __cplusplus
extern "C" {
#endif

    char const* anonymize_tor_data_directory(void);
    char const* anonymize_service_directory(void);
    int check_interrupted(void);

#ifdef __cplusplus
}
#endif

#endif

