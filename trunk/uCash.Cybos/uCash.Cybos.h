/*
 * uCash.Cybos Copyright (c) 2011 Taeyoung Park (primespace@naver.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <string>
#include <atlbase.h>
#include <atlcom.h>
#include <atlsafe.h>

#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "uCash.Cybosd.lib")
#else
#pragma comment(lib, "uCash.Cybos.lib")
#endif

#include "uCash.Cybos.Export.h"

#include "uCash.Cybos.Define.h"
#include "uCash.Cybos.Api.h"
#include "uCash.Cybos.CpCybosObject.h"
#include "uCash.Cybos.CpCybos.h"
#include "uCash.Cybos.CpObject.h"
#include "uCash.Cybos.CpFutureCodeObject.h"
#include "uCash.Cybos.CpStockCodeObject.h"
#include "uCash.Cybos.CpFutureCode.h"
#include "uCash.Cybos.Event.h"
#include "uCash.Cybos.CpFutureCurOnly.h"
#include "uCash.Cybos.CpFutureBid1.h"
#include "uCash.Cybos.CpFutureJpBid.h"
#include "uCash.Cybos.FutureWide.h"
#include "uCash.Cybos.CpFutureMst.h"
#include "uCash.Cybos.CpStockCode.h"

#include "uCash.Cybos.FutureTradeData.h"
#include "uCash.Cybos.FutureTradeMonitor.h"
#include "uCash.Cybos.FutureTradeMonitorTmpl.h"

#include "uCash.Cybos.FutureHogaData.h"
#include "uCash.Cybos.FutureHogaMonitor.h"
#include "uCash.Cybos.FutureHogaMonitorTmpl.h"

#include "uCash.Cybos.CpMarketWatch.h"
#include "uCash.Cybos.MarketWatchData.h"
#include "uCash.Cybos.MarketWatchMonitor.h"

#include "uCash.Cybos.MonitorTmpl.h"

#include "uCash.Cybos.CpStockChart.h"
#include "uCash.Cybos.CandleLoader.h"

#include "uCash.Cybos.StockCode.h"
#include "uCash.Cybos.CodeLoader.h"