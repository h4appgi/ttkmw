#ifndef TTKLOGGER_H
#define TTKLOGGER_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QDebug>
#include <QDateTime>

#define CURRENT_DATE QDate::currentDate().toString("yyyy-MM-dd")
#define CURRENT_TIME QTime::currentTime().toString("hh:mm:ss:zzz")

#if QT_VERSION < QT_VERSION_CHECK(5,4,0)
#  define TTK_LOG_OUTPUT qDebug()
#else
#  define TTK_LOG_OUTPUT qDebug().noquote()
#endif

// log stream base macro
#define TTK_LOG_STREAM(level, msg) TTK_LOG_OUTPUT << QString("[%1 %2][%3][%4(%5)] ").arg(CURRENT_DATE, CURRENT_TIME, level, __FILE__, QString::number(__LINE__)) << msg
// log once base macro
#define TTK_LOG_STREAM_ONCE(level, msg) \
  static bool __hit__ = false; \
  if(!__hit__) \
  { \
    __hit__ = true; \
    TTK_LOG_STREAM(level, msg); \
  }
// log stream throttle base macro
#define TTK_LOG_STREAM_THROTTLE(period, level, msg) \
  static qint64 __last__ = 0.0; \
  const qint64 __now__ = QDateTime::currentMSecsSinceEpoch(); \
  if(__last__ + period * 1000 <= __now__ || __now__ < __last__) \
  { \
    __last__ = __now__; \
    TTK_LOG_STREAM(level, msg); \
  }

#define TTK_TRACE_STREAM(msg) { TTK_LOG_STREAM("I", msg); }
#define TTK_DEBUG_STREAM(msg) { TTK_LOG_STREAM("D", msg); }
#define TTK_INFO_STREAM(msg)  { TTK_LOG_STREAM("W", msg); }
#define TTK_WARN_STREAM(msg)  { TTK_LOG_STREAM("T", msg); }
#define TTK_ERROR_STREAM(msg) { TTK_LOG_STREAM("E", msg); }
#define TTK_FATAL_STREAM(msg) { TTK_LOG_STREAM("F", msg); }

#define TTK_TRACE_STREAM_ONCE(msg) { TTK_LOG_STREAM_ONCE("I", msg) }
#define TTK_DEBUG_STREAM_ONCE(msg) { TTK_LOG_STREAM_ONCE("D", msg) }
#define TTK_INFO_STREAM_ONCE(msg)  { TTK_LOG_STREAM_ONCE("W", msg) }
#define TTK_WARN_STREAM_ONCE(msg)  { TTK_LOG_STREAM_ONCE("T", msg) }
#define TTK_ERROR_STREAM_ONCE(msg) { TTK_LOG_STREAM_ONCE("E", msg) }
#define TTK_FATAL_STREAM_ONCE(msg) { TTK_LOG_STREAM_ONCE("F", msg) }

#define TTK_TRACE_STREAM_THROTTLE(period, msg) { TTK_LOG_STREAM_THROTTLE(period, "I", msg) }
#define TTK_DEBUG_STREAM_THROTTLE(period, msg) { TTK_LOG_STREAM_THROTTLE(period, "D", msg) }
#define TTK_INFO_STREAM_THROTTLE(period, msg)  { TTK_LOG_STREAM_THROTTLE(period, "W", msg) }
#define TTK_WARN_STREAM_THROTTLE(period, msg)  { TTK_LOG_STREAM_THROTTLE(period, "T", msg) }
#define TTK_ERROR_STREAM_THROTTLE(period, msg) { TTK_LOG_STREAM_THROTTLE(period, "E", msg) }
#define TTK_FATAL_STREAM_THROTTLE(period, msg) { TTK_LOG_STREAM_THROTTLE(period, "F", msg) }

#endif // TTKLOGGER_H
