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
#include "uCash.Cybos.CpObject.h"
#include "uCash.Cybos.CpStockChart.h"
#include "uCash.Cybos.CandleLoader.h"

namespace uCash { namespace Cybos {


	CandleLoader::CandleLoader()
	{}

	CandleLoader::~CandleLoader()
	{
		Release();
	}

	void CandleLoader::Release()
	{
		if(m_chart.IsCreated())
			m_chart.Release();
	}

	void CandleLoader::Load(uCash::Tech::CandleList& candleList,
			const char* code,
			uCash::Tech::CandleType candleType,
			int nCount,
			unsigned short period)
	{
		candleList.RemoveAll();
		candleList.CandleType = candleType;
		candleList.Period = period;

		if(!m_chart.IsCreated()) {
			m_chart.CreateInstance();
		}

		m_chart.SetInputValue(0, code);
		m_chart.SetInputValue(1, '2');
		m_chart.SetInputValue(4, nCount);

		long fields[] = { 0, 1, 2, 3, 4, 5, 6, 8, 12, 13, 37 };

		CComSafeArray<long> sa(sizeof(fields)/sizeof(long));
		for(long i = 0; i < sizeof(fields)/sizeof(long); ++i) sa[i] = fields[i];

		m_chart.SetInputValue(5, sa);

		char ch = 'D';
		switch(candleType)
		{
		case uCash::Tech::CANDLE_DAY: ch = 'D'; break;
		case uCash::Tech::CANDLE_WEEK: ch = 'W'; break;
		case uCash::Tech::CANDLE_MONTH: ch = 'M'; break;
		case uCash::Tech::CANDLE_MIN: ch = 'm'; break;
		default:
			assert(false);
		};

		m_chart.SetInputValue(6, ch);
		m_chart.SetInputValue(7, period);
		m_chart.SetInputValue(8, '1');
		m_chart.SetInputValue(9, '1');

		uCash::Tech::Candle candle;

		do
		{
			bool b = m_chart.BlockRequest();

			short count = 0;
			m_chart.GetHeaderValue<short>(3, count);

			for(short i = 0; i < count; ++i)
			{
				m_chart.GetDataValue<long>(0, i, candle.date);
				m_chart.GetDataValue<long>(1, i, candle.time);
				m_chart.GetDataValue<long>(2, i, candle.open);
				m_chart.GetDataValue<long>(3, i, candle.high);
				m_chart.GetDataValue<long>(4, i, candle.low);
				m_chart.GetDataValue<long>(5, i, candle.close);
				m_chart.GetDataValue<long>(6, i, candle.diff);
				m_chart.GetDataValue<long>(7, i, candle.volumn);
				m_chart.GetDataValue<long>(8, i, candle.stocks);
				m_chart.GetDataValue<__int64>(9, i, candle.amount);
				m_chart.GetDataValue<char>(10, i, candle.difftype);

				candleList.AddFront(candle);
			}
		}
		while(m_chart.GetContinue() > 1);
	}


}} // namespace uCash::Cybos