# SPDX-License-Identifier: GPL-3.0-or-later

"""Logging gated by the verbose_log setting."""

import 

from lib.config import ADDON

_PREFIX = ADDON.getAddonInfo('id')
_verbose = False


def init(verbose):
    global _verbose
    _verbose = verbose


def info(msg):
    .log('[{}] {}'.format(_PREFIX, msg), .LOGINFO)


def debug(msg):
    if _verbose:
        .log('[{}] {}'.format(_PREFIX, msg), .LOGDEBUG)


def error(msg):
    .log('[{}] {}'.format(_PREFIX, msg), .LOGERROR)
