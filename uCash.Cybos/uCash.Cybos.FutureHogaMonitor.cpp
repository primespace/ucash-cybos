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
#include "uCash.Cybos.FutureHogaData.h"

#include "uCash.Cybos.CpObject.h"
#include "uCash.Cybos.CpFutureJpBid.h"
#include "uCash.Cybos.FutureHogaMonitor.h"

namespace uCash { namespace Cybos {

	_ATL_FUNC_INFO  FutureHogaMonitor::ReceivedInfo = { CC_STDCALL, VT_EMPTY, 0, { VT_EMPTY } };

	FutureHogaMonitor::FutureHogaMonitor()
		: m_callback(NULL)
	{
	}

	FutureHogaMonitor::~FutureHogaMonitor()
	{
		if(m_obj.IsCreated()) {
			Destroy();
		}
	}


	bool FutureHogaMonitor::Create()
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

	void FutureHogaMonitor::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);
		
		m_obj.Release();
	}

	bool FutureHogaMonitor::Subscribe(LPCTSTR code)
	{
		if(m_obj.IsSubscribed()) return true;

		m_obj.SetInputValue(0, code);

		return (m_obj.Subscribe() == true);
	}

	void FutureHogaMonitor::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

	void __stdcall FutureHogaMonitor::OnReceivedData()
	{
		m_obj.GetHeaderValue<std::string>(0, m_data.Code);

		m_obj.GetHeaderValue<long>(1, m_data.Time);
	
		m_obj.GetHeaderValue<float>(2, m_data.SelPoint[0]);
		m_obj.GetHeaderValue<float>(3, m_data.SelPoint[1]);
		m_obj.GetHeaderValue<float>(4, m_data.SelPoint[2]);
		m_obj.GetHeaderValue<float>(5, m_data.SelPoint[3]);
		m_obj.GetHeaderValue<float>(6, m_data.SelPoint[4]);

		m_obj.GetHeaderValue<long>(7, m_data.SelVolumn[0]);
		m_obj.GetHeaderValue<long>(8, m_data.SelVolumn[1]);
		m_obj.GetHeaderValue<long>(9, m_data.SelVolumn[2]);
		m_obj.GetHeaderValue<long>(10, m_data.SelVolumn[3]);
		m_obj.GetHeaderValue<long>(11, m_data.SelVolumn[4]);
	
		m_obj.GetHeaderValue<long>(12, m_data.TotalSelVolumn);

		m_obj.GetHeaderValue<long>(13, m_data.SelCount[0]);
		m_obj.GetHeaderValue<long>(14, m_data.SelCount[1]);
		m_obj.GetHeaderValue<long>(15, m_data.SelCount[2]);
		m_obj.GetHeaderValue<long>(16, m_data.SelCount[3]);
		m_obj.GetHeaderValue<long>(17, m_data.SelCount[4]);

		m_obj.GetHeaderValue<long>(18, m_data.TotalSelCount);

		m_obj.GetHeaderValue<float>(19, m_data.BuyPoint[0]);
		m_obj.GetHeaderValue<float>(20, m_data.BuyPoint[1]);
		m_obj.GetHeaderValue<float>(21, m_data.BuyPoint[2]);
		m_obj.GetHeaderValue<float>(22, m_data.BuyPoint[3]);
		m_obj.GetHeaderValue<float>(23, m_data.BuyPoint[4]);

		m_obj.GetHeaderValue<long>(24, m_data.BuyVolumn[0]);
		m_obj.GetHeaderValue<long>(25, m_data.BuyVolumn[1]);
		m_obj.GetHeaderValue<long>(26, m_data.BuyVolumn[2]);
		m_obj.GetHeaderValue<long>(27, m_data.BuyVolumn[3]);
		m_obj.GetHeaderValue<long>(28, m_data.BuyVolumn[4]);
	
		m_obj.GetHeaderValue<long>(29, m_data.TotalBuyVolumn);

		m_obj.GetHeaderValue<long>(30, m_data.BuyCount[0]);
		m_obj.GetHeaderValue<long>(31, m_data.BuyCount[1]);
		m_obj.GetHeaderValue<long>(32, m_data.BuyCount[2]);
		m_obj.GetHeaderValue<long>(33, m_data.BuyCount[3]);
		m_obj.GetHeaderValue<long>(34, m_data.BuyCount[4]);

		m_obj.GetHeaderValue<long>(35, m_data.TotalBuyCount);

		m_obj.GetHeaderValue<short>(36, m_data.State);

		if(m_callback) {
			m_callback(m_data);
		}
	}

	void FutureHogaMonitor::SetCallback(FutureHogaMonitorCallback callback)
	{
		m_callback = callback;
	}

}} // namespace uCash::Cybos