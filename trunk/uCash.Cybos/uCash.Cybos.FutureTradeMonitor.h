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

namespace uCash { namespace Cybos {

	typedef void (CALLBACK* FutureTradeMonitorCallback)(FutureTradeData& data);

	class UCASHCYBOS_API FutureTradeMonitor
		: public IDispEventSimpleImpl<FUTURETRADEMONITOR_EVENT_ID,
				FutureTradeMonitor, &__uuidof(CpDib::_IDibEvents)>
	{
	public:

		typedef IDispEventSimpleImpl<FUTURETRADEMONITOR_EVENT_ID, 
			FutureTradeMonitor, 
			&__uuidof(CpDib::_IDibEvents)> BaseClass;

		FutureTradeMonitor(void);

		~FutureTradeMonitor(void);

		bool Create();

		void Destroy();

		bool Subscribe(LPCTSTR code);

		void Unsubscribe();

		void SetCallback(FutureTradeMonitorCallback callback);

		BEGIN_SINK_MAP(FutureTradeMonitor)		
			SINK_ENTRY_INFO(FUTURETRADEMONITOR_EVENT_ID, __uuidof(CpDib::_IDibEvents), 1, OnReceivedData, &ReceivedInfo)
		END_SINK_MAP()

	private:

		static _ATL_FUNC_INFO  ReceivedInfo;

		void __stdcall OnReceivedData();

		FutureTradeData m_data;

		CpFutureCurOnly m_obj;

		CpFutureBid1 m_bid1;

		FutureTradeMonitorCallback m_callback;
	};

}}