/*
 * BlueALSA - log.h
 * Copyright (c) 2016-2022 Arkadiusz Bokowy
 *
 * This file is a part of bluez-alsa.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#pragma once
#ifndef BLUEALSA_SHARED_LOG_H_
#define BLUEALSA_SHARED_LOG_H_

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdbool.h>
#include <stddef.h>
#include <syslog.h>

#include "shared/defs.h"

#if DEBUG_TIME
# define BLUEALSA_LOGTIME true
#else
# define BLUEALSA_LOGTIME false
#endif

void log_open(const char *ident, bool syslog, bool time);
void log_message(int priority, const char *format, ...) __attribute__ ((format(printf, 2, 3)));

#if DEBUG
# define DEBUG_LOG_PREFIX __FILE__ ":" STRINGIZE(__LINE__) ": "
# define error(M, ...) log_message(LOG_ERR, DEBUG_LOG_PREFIX M, ## __VA_ARGS__)
# define warn(M, ...) log_message(LOG_WARNING, DEBUG_LOG_PREFIX M, ## __VA_ARGS__)
# define info(M, ...) log_message(LOG_INFO, DEBUG_LOG_PREFIX M, ## __VA_ARGS__)
# define debug(M, ...) log_message(LOG_DEBUG, DEBUG_LOG_PREFIX M, ## __VA_ARGS__)
#else
# define error(M, ...) log_message(LOG_ERR, M, ## __VA_ARGS__)
# define warn(M, ...) log_message(LOG_WARNING, M, ## __VA_ARGS__)
# define info(M, ...) log_message(LOG_INFO, M, ## __VA_ARGS__)
# define debug(M, ...) do {} while (0)
#endif

#if DEBUG
void callstackdump_(const char *label);
# define callstackdump(M) callstackdump_(DEBUG_LOG_PREFIX M)
#else
# define callstackdump(M) do {} while (0)
#endif

#if DEBUG
void hexdump_(const char *label, const void *data, size_t len, bool compact);
# define hexdump(M, D, L, C) hexdump_(DEBUG_LOG_PREFIX M, D, L, C)
#else
# define hexdump(M, D, L, C) do {} while (0)
#endif

#endif
