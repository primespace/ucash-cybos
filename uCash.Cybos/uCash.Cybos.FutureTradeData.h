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

	class UCASHCYBOS_API FutureTradeData
	{
	public:

		FutureTradeData(void);

		~FutureTradeData(void);

		std::string Code;     // 종목코드

		double	CurPrice; // 현재가
		double	Ratio; // 전일대비
		double	TheroyFutureIndex; // 이론선물지수
		double Kospi200Index; // 코스피200 지수
		double Basis; // 베이시스
		double StandardPrice; // 기준가격
		double Open; // 시가
		double High; // 고가
		double Low; // 저가
		double MaxHigh; // 최고가
		double MinLow; // 최저가
		long LastDate; // 최종거래일
		long AccumVolumn; // 누적거래량
		double NotAccountPromise; // 미결제약정
		long Time; // 시간

		double Value16; // 최근월물 의제약정가격
		double Value17; // 원월물 의제약정가격
		double Value18; // 최우선매도호가
		double Value19; // 최우선매수호가
		double Value20; // 최우선매도호가잔량
		double Value21; // 최우선매수호가잔량

		unsigned long AccumTreatySel; // 누적 체결 매도
		unsigned long AccumTreatyBuy; // 누적 체결 매수
		char TreatyType; // 체결구분

		unsigned long BasicAssetPrice; // 기초자산종목코드 현재가
		unsigned long AccumAmount; // 누적거래대금(백만원)
		long PrevPrice; // 직전가격
		short TreatyCode; // 체결유형코드

		long LastAccumVolumn; // 마지막 누적 거래량.
		long CurVolumn; // 체결량

	};

}}