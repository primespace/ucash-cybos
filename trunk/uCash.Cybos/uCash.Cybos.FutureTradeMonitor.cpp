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
#include "uCash.Cybos.CpFutureBid1.h"
#include "uCash.Cybos.CpFutureCurOnly.h"
#include "uCash.Cybos.FutureTradeData.h"
#include "uCash.Cybos.FutureTradeMonitor.h"


namespace uCash { namespace Cybos {

	_ATL_FUNC_INFO  FutureTradeMonitor::ReceivedInfo = { CC_STDCALL, VT_EMPTY, 0, { VT_EMPTY } };

	FutureTradeMonitor::FutureTradeMonitor(void)
		: m_callback(NULL)
	{
	}

	FutureTradeMonitor::~FutureTradeMonitor(void)
	{
			
	}

	void __stdcall FutureTradeMonitor::OnReceivedData()
	{
		m_obj.GetHeaderValue<std::string>(0, m_data.Code);
			
		m_obj.GetHeaderValue<double>(1, m_data.CurPrice);
		m_obj.GetHeaderValue<double>(2, m_data.Ratio);
		m_obj.GetHeaderValue<double>(3, m_data.TheroyFutureIndex);
		m_obj.GetHeaderValue<double>(4, m_data.Kospi200Index);

		m_obj.GetHeaderValue<double>(5, m_data.Basis);
		m_obj.GetHeaderValue<double>(6, m_data.StandardPrice);
		m_obj.GetHeaderValue<double>(7, m_data.Open);
		m_obj.GetHeaderValue<double>(8, m_data.High);
		m_obj.GetHeaderValue<double>(9, m_data.Low);
		m_obj.GetHeaderValue<double>(10, m_data.MaxHigh);
		m_obj.GetHeaderValue<double>(11, m_data.MinLow);
		m_obj.GetHeaderValue<long>(12, m_data.LastDate);
		m_obj.GetHeaderValue<long>(13, m_data.AccumVolumn);

		m_data.CurVolumn = m_data.AccumVolumn - m_data.LastAccumVolumn;
		m_data.LastAccumVolumn = m_data.AccumVolumn;

		m_obj.GetHeaderValue<double>(14, m_data.NotAccountPromise);
		m_obj.GetHeaderValue<long>(15, m_data.Time);

		m_obj.GetHeaderValue<double>(16, m_data.Value16);
		m_obj.GetHeaderValue<double>(17, m_data.Value17);
		m_obj.GetHeaderValue<double>(18, m_data.Value18);
		m_obj.GetHeaderValue<double>(19, m_data.Value19);
		m_obj.GetHeaderValue<double>(20, m_data.Value20);
		m_obj.GetHeaderValue<double>(21, m_data.Value21);
	
		m_obj.GetHeaderValue<unsigned long>(22, m_data.AccumTreatySel);
		m_obj.GetHeaderValue<unsigned long>(23, m_data.AccumTreatyBuy);
		m_obj.GetHeaderValue<char>(24, m_data.TreatyType);

		m_obj.GetHeaderValue<unsigned long>(25, m_data.BasicAssetPrice);
		m_obj.GetHeaderValue<unsigned long>(26, m_data.AccumAmount);
		m_obj.GetHeaderValue<long>(27, m_data.PrevPrice);
		m_obj.GetHeaderValue<short>(28, m_data.TreatyCode);

		if(m_callback) {
			m_callback(m_data);
		}
	}

	bool FutureTradeMonitor::Create()
	{
		if(m_obj.IsCreated()) {
			return true;
		}
		if(!m_obj.CreateInstance()) {
			return false;
		}

		HRESULT hr = BaseClass::DispEventAdvise((IUnknownPtr)m_obj);
		if(FAILED(hr)) {
			m_obj.Release();
			return false;
		}

		if(!m_bid1.CreateInstance()) {
			m_obj.Release();
			return false;
		}

		return true;
	}

	void FutureTradeMonitor::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);

		m_bid1.Release();
		m_obj.Release();
		
	}

	bool FutureTradeMonitor::Subscribe(LPCTSTR code)
	{
		if(m_obj.IsSubscribed()) {
			return true;
		}

		m_bid1.SetInputValue(0, code);
		m_bid1.SetInputValue(1, 1);
		if(!m_bid1.BlockRequest()) {
			return false;
		}
			
		m_bid1.GetDataValue<long>(6, 0, m_data.LastAccumVolumn);

		m_obj.SetInputValue(0, code);

		return (m_obj.Subscribe() == true);
	}

	void FutureTradeMonitor::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

	void FutureTradeMonitor::SetCallback(FutureTradeMonitorCallback callback)
	{
		m_callback = callback;
	}


}} // namespace uCash::Cybos