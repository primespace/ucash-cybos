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

#include <ace\ACE.h>
#include <ace\Malloc_T.h>
#include <ace\Singleton.h>
#include <ace\Mutex.h>

namespace uCash { namespace Cybos {

	template<class D, class T>
	class FutureTradeMonitorTmpl
		: public IDispEventSimpleImpl<FUTURETRADEMONITOR_EVENT_ID,
				FutureTradeMonitorTmpl<D,T>, &__uuidof(CpDib::_IDibEvents)>
	{
	public:

		typedef IDispEventSimpleImpl<FUTURETRADEMONITOR_EVENT_ID,
				FutureTradeMonitorTmpl<D,T>, 
				&__uuidof(CpDib::_IDibEvents)> BaseClass;

		typedef FutureTradeMonitorTmpl<D,T> ThisClass;

		FutureTradeMonitorTmpl(void);

		~FutureTradeMonitorTmpl(void);

		virtual bool Create();

		virtual void Destroy();

		void allocator(ACE_Allocator* allocator);

		ACE_Allocator* allocator();

		BEGIN_SINK_MAP(ThisClass)		
			SINK_ENTRY_INFO(FUTURETRADEMONITOR_EVENT_ID, __uuidof(CpDib::_IDibEvents), 1, OnReceivedDataImpl, &ReceivedInfo)
		END_SINK_MAP()

		bool Subscribe(const char* code);

		void Unsubscribe();

	protected:

		void __stdcall OnReceivedDataImpl();

		CpFutureCurOnly m_obj;

		CpFutureBid1 m_bid1;

		long m_LastAccumVolumn;

		static _ATL_FUNC_INFO  ReceivedInfo;

		ACE_Allocator* m_allocator;

	};

	template<class D, class T>
	FutureTradeMonitorTmpl<D,T>::FutureTradeMonitorTmpl(void)
		: m_allocator(NULL)
	{
	}

	template<class D, class T>
	FutureTradeMonitorTmpl<D,T>::~FutureTradeMonitorTmpl(void)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
		}
	}

	template<class D, class T>
	bool FutureTradeMonitorTmpl<D,T>::Create()
	{
		if(m_allocator == NULL) {
			m_allocator = new ACE_Dynamic_Cached_Allocator<ACE_Thread_Mutex>(10000, sizeof(T));
		}

		if(m_obj.IsCreated()) {
			return true;
		}
		if(!m_obj.CreateInstance()) {
			ACE_DEBUG((LM_DEBUG, "CpFutureCurOnly CreateInstance failed."));
			return false;
		}

		HRESULT hr = BaseClass::DispEventAdvise((IUnknownPtr)m_obj);
		if(FAILED(hr)) {
			m_obj.Release();
			return false;
		}

		if(!m_bid1.CreateInstance()) {
			m_obj.Release();
			ACE_DEBUG((LM_DEBUG, "CpFutureBid1 CreateInstance failed."));
			return false;
		}

		return true;
	}

	template<class D, class T>
	void FutureTradeMonitorTmpl<D,T>::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);

		m_bid1.Release();
		m_obj.Release();
	}

	template<class D, class T>
	void FutureTradeMonitorTmpl<D,T>::OnReceivedDataImpl()
	{
		D* pDrived = (D*)this;
		T* data = (T*)m_allocator->malloc(sizeof(T));
		
		// set data..

		std::string code;
		m_obj.GetHeaderValue<std::string>(0, code);
		strncpy(data->Code, code.c_str(), 8);
			
		m_obj.GetHeaderValue<float>(1, data->CurPrice);
		m_obj.GetHeaderValue<float>(2, data->Ratio);
		m_obj.GetHeaderValue<float>(3, data->TheroyFutureIndex);
		m_obj.GetHeaderValue<float>(4, data->Kospi200Index);

		m_obj.GetHeaderValue<float>(5, data->Basis);
		m_obj.GetHeaderValue<float>(6, data->StandardPrice);
		m_obj.GetHeaderValue<float>(7, data->Open);
		m_obj.GetHeaderValue<float>(8, data->High);
		m_obj.GetHeaderValue<float>(9, data->Low);
		m_obj.GetHeaderValue<float>(10, data->MaxHigh);
		m_obj.GetHeaderValue<float>(11, data->MinLow);
		m_obj.GetHeaderValue<long>(12, data->LastDate);

		m_obj.GetHeaderValue<long>(13, data->AccumVolumn);

		data->CurVolumn = data->AccumVolumn - m_LastAccumVolumn;
		m_LastAccumVolumn = data->AccumVolumn;

		m_obj.GetHeaderValue<long>(14, data->NotAccountPromise);
		m_obj.GetHeaderValue<long>(15, data->Time);

		//m_obj.GetHeaderValue<double>(16, data->Value16);
		//m_obj.GetHeaderValue<double>(17, data->Value17);
		m_obj.GetHeaderValue<float>(18, data->FirstPrioritySelPrice);
		m_obj.GetHeaderValue<float>(19, data->FirstPriorityBuyPrice);
		m_obj.GetHeaderValue<unsigned long>(20, data->FirstPrioritySelCount);
		m_obj.GetHeaderValue<unsigned long>(21, data->FirstPriorityBuyCount);
	
		m_obj.GetHeaderValue<unsigned long>(22, data->AccumTreatySel);
		m_obj.GetHeaderValue<unsigned long>(23, data->AccumTreatyBuy);
		m_obj.GetHeaderValue<char>(24, data->TreatyType);

		m_obj.GetHeaderValue<unsigned long>(25, data->BasicAssetPrice);
		m_obj.GetHeaderValue<unsigned long>(26, data->AccumAmount);
		m_obj.GetHeaderValue<long>(27, data->PrevPrice);
		m_obj.GetHeaderValue<short>(28, data->TreatyCode);

		pDrived->OnReceivedData(data);
	}

	template<class D, class T>
	void FutureTradeMonitorTmpl<D,T>::allocator(ACE_Allocator* allocator)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
			m_allocator = allocator;
		}
	}

	template<class D, class T>
	ACE_Allocator* FutureTradeMonitorTmpl<D,T>::allocator()
	{
		return m_allocator;
	}

	template<class D, class T>
	bool FutureTradeMonitorTmpl<D,T>::Subscribe(const char* code)
	{
		if(m_obj.IsSubscribed()) {
			return true;
		}

		m_bid1.SetInputValue(0, code);
		m_bid1.SetInputValue(1, 1);
		if(!m_bid1.BlockRequest()) {
			return false;
		}
			
		m_bid1.GetDataValue<long>(6, 0, m_LastAccumVolumn);

		m_obj.SetInputValue(0, code);

		return (m_obj.Subscribe() == true);
	}

	template<class D, class T>
	void FutureTradeMonitorTmpl<D,T>::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

}} // namespace uCash::Cybos