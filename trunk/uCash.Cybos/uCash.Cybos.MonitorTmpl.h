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

	template<class D, class T, class CpObject, class IEvent>
	class MonitorTmpl 
		: public IDispEventSimpleImpl<CpObject::EVENT_ID,
				MonitorTmpl<D,T,CpObject,IEvent>, &__uuidof(IEvent)>
	{
	public:
		
		typedef IDispEventSimpleImpl<CpObject::EVENT_ID,
				MonitorTmpl<D,T,CpObject,IEvent>, &__uuidof(IEvent)> BaseClass;

		typedef MonitorTmpl<D,T,CpObject,IEvent> ThisClass;

		MonitorTmpl(void);

		~MonitorTmpl(void);

		virtual bool Create();

		virtual void Destroy();

		void allocator(ACE_Allocator* allocator);

		ACE_Allocator* allocator();

		BEGIN_SINK_MAP(ThisClass)		
			SINK_ENTRY_INFO(CpObject::EVENT_ID, __uuidof(IEvent), 1, OnReceivedDataImpl, &ReceivedInfo)
		END_SINK_MAP()

		bool Subscribe();

		void Unsubscribe();

	protected:

		void __stdcall OnReceivedDataImpl();

		static _ATL_FUNC_INFO  ReceivedInfo;

		CpObject m_obj;

		ACE_Allocator* m_allocator;

	};

	template<class D, class T, class CpObject, class IEvent>
	MonitorTmpl<D,T,CpObject,IEvent>::MonitorTmpl(void)
		: m_allocator(NULL)
	{
	}

	template<class D, class T, class CpObject, class IEvent>
	MonitorTmpl<D,T,CpObject,IEvent>::~MonitorTmpl(void)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
		}
	}

	template<class D, class T, class CpObject, class IEvent>
	bool MonitorTmpl<D,T,CpObject,IEvent>::Create()
	{
		if(m_allocator == NULL) {
			m_allocator = new ACE_Dynamic_Cached_Allocator<ACE_Thread_Mutex>(10000, sizeof(T));
		}

		if(m_obj.IsCreated()) {
			return true;
		}
		if(!m_obj.CreateInstance()) {
			ACE_DEBUG((LM_DEBUG, "CpObject CreateInstance failed."));
			return false;
		}

		HRESULT hr = BaseClass::DispEventAdvise((IUnknownPtr)m_obj);
		if(FAILED(hr)) {
			m_obj.Release();
			return false;
		}

		return true;
	}

	template<class D, class T, class CpObject, class IEvent>
	void MonitorTmpl<D,T,CpObject,IEvent>::Destroy()
	{
		m_obj.Unsubscribe();

		BaseClass::DispEventUnadvise((IUnknownPtr)m_obj);

		m_obj.Release();
	}

	template<class D, class T, class CpObject, class IEvent>
	void MonitorTmpl<D,T,CpObject,IEvent>::OnReceivedDataImpl()
	{
		D* pDrived = (D*)this;
		T* data = (T*)m_allocator->malloc(sizeof(T));
		data->SetData(m_obj);
		pDrived->OnReceivedData(data);
		m_allocator->free(data);
	}

	template<class D, class T, class CpObject, class IEvent>
	void MonitorTmpl<D,T,CpObject,IEvent>::allocator(ACE_Allocator* allocator)
	{
		if(m_allocator != NULL) {
			delete m_allocator;
			m_allocator = allocator;
		}
	}

	template<class D, class T, class CpObject, class IEvent>
	ACE_Allocator* MonitorTmpl<D,T,CpObject,IEvent>::allocator()
	{
		return m_allocator;
	}

	template<class D, class T, class CpObject, class IEvent>
	bool MonitorTmpl<D,T,CpObject,IEvent>::Subscribe()
	{
		if(m_obj.IsSubscribed()) {
			return true;
		}
		return (m_obj.Subscribe() == true);
	}

	template<class D, class T, class CpObject, class IEvent>
	void MonitorTmpl<D,T,CpObject,IEvent>::Unsubscribe()
	{
		m_obj.Unsubscribe();
	}

}} // namespace uCash::Cybos