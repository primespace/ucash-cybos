/*
 * uCash.Cybos Copyright (c) 2011 Taeyoung Park (primespace@naver.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <algorithm>

#include "uCash.Tech.Define.h"
#include "uCash.Tech.Candle.h"
#include "uCash.Tech.List.h"

#ifdef min
#undef min
#endif

namespace uCash { namespace Tech {


	class CandleList : public List<Candle>
	{
	public:

		CandleList()
			: Period(0)
		{}

		void GetMinMax(float& min, float& max, int nBeginIndex, int nCount)
		{
			for(int i = 0; i < nCount; ++i) {
				Candle& candle = this->GetFront(i + nBeginIndex);
				if(max < (float)candle.high) max = (float)candle.high;
				if(min > (float)candle.low) min = (float)candle.low;
			}
		}

		CandleType	CandleType;
		int			Period;


	};

}} // namespace uCash::Tech