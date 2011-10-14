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
	class FutureHogaMonitorTmpl 
		: public IDispEventSimpleImpl<FUTUREHOGAMONITOR_EVENT_ID,
				FutureHogaMonitorTmpl<D,T>, &__uuidof(CpSysDib::_ISysDibEvents)>
	{
	public:
		
		typedef IDispEventSimpleImpl<FUTUREHOGAMONITOR_EVENT_ID,
				FutureHogaMonitorTmpl<D,T>, 
				&__uuidof(CpSysDib::_ISysDibEvents)> BaseClass;

		typedef FutureHogaMonitorTmpl<D,T> ThisClass;

		FutureHogaMonitorTmpl(void);

		~FutureHogaMonitorTmpl(void);

		virtual bool Create();

		virtual void Destroy();

		void allocator(ACE_Allocator* allocator);

		ACE_Allocator* allocator();

		BEGIN_SINK_MAP(ThisClass)		
			SINK_ENTRY_INFO(FUTUREHOGAMONITOR_EVENT_ID, __uuidof(CpSysDib::_ISysDibEvents), 1, OnReceivedDataImpl, &ReceivedInfo)
		END_SINK_MAP()

		bool Subscribe(const char* code);

		void Unsubscribe();

	protected:

		void __stdcall OnReceivedDataImpl();

		static _ATL_FUNC_INFO  ReceivedInfo;

		CpFutureJpBid m_obj;

		ACE_Allocator* m_allocator;

	};

	template<class D, class T>
	FutureHogaMonitorTmpl<D,T>::FutureHogaMonitorTmpl(void)
		: m_allocator(NULL)
	{
	}

	template<class D, class T>
	FutureHogaMonitorTmpl<D,T>::~FutureHogaMonitorTmpl(void)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
		}
	}

	template<class D, class T>
	bool FutureHogaMonitorTmpl<D,T>::Create()
	{
		if(m_allocator == NULL) {
			m_allocator = new ACE_Dynamic_Cached_Allocator<ACE_Thread_Mutex>(10000, sizeof(T));
		}

		if(m_obj.IsCreated()) {
			return true;
		}
		if(!m_obj.CreateInstance()) {
			ACE_DEBUG((LM_DEBUG, "CpFutureJpBid CreateInstance failed."));
			return false;
		}

		HRESULT hr = BaseClass::DispEventAdvise((IUnknownPtr)m_obj);
		if(FAILED(hr)) {
			m_obj.Release();
			return false;
		}

		return true;
	}

	template<class D, class T>
	void FutureHogaMonitorTmpl<D,T>::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);

		m_obj.Release();
	}

	template<class D, class T>
	void FutureHogaMonitorTmpl<D,T>::OnReceivedDataImpl()
	{
		D* pDrived = (D*)this;
		T* data = (T*)m_allocator->malloc(sizeof(T));

		std::string code;
		m_obj.GetHeaderValue<std::string>(0, code);
		strncpy(data->Code, code.c_str(), 8);

		m_obj.GetHeaderValue<long>(1, data->Time);
	
		m_obj.GetHeaderValue<float>(2, data->SelPoint[0]);
		m_obj.GetHeaderValue<float>(3, data->SelPoint[1]);
		m_obj.GetHeaderValue<float>(4, data->SelPoint[2]);
		m_obj.GetHeaderValue<float>(5, data->SelPoint[3]);
		m_obj.GetHeaderValue<float>(6, data->SelPoint[4]);

		m_obj.GetHeaderValue<long>(7, data->SelVolumn[0]);
		m_obj.GetHeaderValue<long>(8, data->SelVolumn[1]);
		m_obj.GetHeaderValue<long>(9, data->SelVolumn[2]);
		m_obj.GetHeaderValue<long>(10, data->SelVolumn[3]);
		m_obj.GetHeaderValue<long>(11, data->SelVolumn[4]);
	
		m_obj.GetHeaderValue<long>(12, data->TotalSelVolumn);

		m_obj.GetHeaderValue<long>(13, data->SelCount[0]);
		m_obj.GetHeaderValue<long>(14, data->SelCount[1]);
		m_obj.GetHeaderValue<long>(15, data->SelCount[2]);
		m_obj.GetHeaderValue<long>(16, data->SelCount[3]);
		m_obj.GetHeaderValue<long>(17, data->SelCount[4]);

		m_obj.GetHeaderValue<long>(18, data->TotalSelCount);

		m_obj.GetHeaderValue<float>(19, data->BuyPoint[0]);
		m_obj.GetHeaderValue<float>(20, data->BuyPoint[1]);
		m_obj.GetHeaderValue<float>(21, data->BuyPoint[2]);
		m_obj.GetHeaderValue<float>(22, data->BuyPoint[3]);
		m_obj.GetHeaderValue<float>(23, data->BuyPoint[4]);

		m_obj.GetHeaderValue<long>(24, data->BuyVolumn[0]);
		m_obj.GetHeaderValue<long>(25, data->BuyVolumn[1]);
		m_obj.GetHeaderValue<long>(26, data->BuyVolumn[2]);
		m_obj.GetHeaderValue<long>(27, data->BuyVolumn[3]);
		m_obj.GetHeaderValue<long>(28, data->BuyVolumn[4]);
	
		m_obj.GetHeaderValue<long>(29, data->TotalBuyVolumn);

		m_obj.GetHeaderValue<long>(30, data->BuyCount[0]);
		m_obj.GetHeaderValue<long>(31, data->BuyCount[1]);
		m_obj.GetHeaderValue<long>(32, data->BuyCount[2]);
		m_obj.GetHeaderValue<long>(33, data->BuyCount[3]);
		m_obj.GetHeaderValue<long>(34, data->BuyCount[4]);

		m_obj.GetHeaderValue<long>(35, data->TotalBuyCount);

		m_obj.GetHeaderValue<short>(36, data->State);

		pDrived->OnReceivedData(data);
	}

	template<class D, class T>
	void FutureHogaMonitorTmpl<D,T>::allocator(ACE_Allocator* allocator)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
			m_allocator = allocator;
		}
	}

	template<class D, class T>
	ACE_Allocator* FutureHogaMonitorTmpl<D,T>::allocator()
	{
		return m_allocator;
	}

	template<class D, class T>
	bool FutureHogaMonitorTmpl<D,T>::Subscribe(const char* code)
	{
		if(m_obj.IsSubscribed()) {
			return true;
		}

		m_obj.SetInputValue(0, code);

		return (m_obj.Subscribe() == true);
	}

	template<class D, class T>
	void FutureHogaMonitorTmpl<D,T>::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

}} // namespace uCash::Cybos