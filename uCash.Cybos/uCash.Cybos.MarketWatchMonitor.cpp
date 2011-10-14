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

#include "stdafx.h"

#include "uCash.Cybos.Export.h"
#include "uCash.Cybos.Define.h"
#include "uCash.Cybos.CpObject.h"
#include "uCash.Cybos.CpMarketWatch.h"
#include "uCash.Cybos.MarketWatchData.h"
#include "uCash.Cybos.MarketWatchMonitor.h"

namespace uCash { namespace Cybos {

	_ATL_FUNC_INFO  MarketWatchMonitor::ReceivedInfo = { CC_STDCALL, VT_EMPTY, 0, { VT_EMPTY } };

	MarketWatchMonitor::MarketWatchMonitor(void)
		: m_callback(NULL)
	{}

	MarketWatchMonitor::~MarketWatchMonitor(void)
	{
		if(m_obj.IsCreated()) {
			Destroy();
		}
	}

	bool MarketWatchMonitor::Create()
	{
		if(m_obj.IsCreated()) return true;
		
		if(!m_obj.CreateInstance()) return false;

		HRESULT hr = BaseClass::DispEventAdvise((IUnknownPtr)m_obj);
		if(FAILED(hr)) {
			m_obj.Release();
			return false;
		}

		return true;
	}

	void MarketWatchMonitor::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);
		
		m_obj.Release();
	}

	bool MarketWatchMonitor::Subscribe()
	{
		if(m_obj.IsSubscribed()) return true;

		return (m_obj.Subscribe() == true);
	}

	void MarketWatchMonitor::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

	void MarketWatchMonitor::SetCallback(MarketWatchMonitorCallback callback)
	{
		m_callback = callback;
	}

	void __stdcall MarketWatchMonitor::OnReceivedData()
	{
		m_obj.GetHeaderValue<char>(0, m_data.Type);
		m_obj.GetHeaderValue<std::string>(1, m_data.Code);
		m_obj.GetHeaderValue<short>(2, m_data.Time);
		m_obj.GetHeaderValue<std::string>(3, m_data.Name);
		m_obj.GetHeaderValue<short>(4, m_data.ItemType);
		m_obj.GetHeaderValue<std::string>(5, m_data.Content);

		if(m_callback) {
			m_callback(m_data);
		}
	}

}} // namespace uCash::Cybos