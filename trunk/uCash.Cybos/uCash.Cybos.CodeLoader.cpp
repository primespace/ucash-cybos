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
#include "uCash.Cybos.CpStockCodeObject.h"
#include "uCash.Cybos.CpStockCode.h"
#include "uCash.Cybos.StockCode.h"
#include "uCash.Cybos.CodeLoader.h"

namespace uCash { namespace Cybos {

	CodeLoader::CodeLoader()
	{
	}

	CodeLoader::~CodeLoader()
	{
	}


	void CodeLoader::Release()
	{
		if(m_stock.IsCreated()) {
			m_stock.Release();
		}
	}

	void CodeLoader::Load(StockCodeList& codeList)
	{
		if(!m_stock.IsCreated()) {
			m_stock.CreateInstance();
		}

		int nCount = m_stock.GetCount();
		for(int i = 0; i < nCount; ++i)
		{
			StockCode sc;
			m_stock.GetData(0, i, sc.Code);
			m_stock.GetData(1, i, sc.Name);
			codeList.AddBack(sc);
		}
	}

}}