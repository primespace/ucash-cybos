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

#include <string>

namespace uCash { namespace Cybos {

	template<class P, class U>
	class CpFutureCodeObject
	{
	public:

		CpFutureCodeObject();

		bool CreateInstance();

		bool IsCreated();

		void Release();

		operator IUnknownPtr ();

		short GetCount();

		void GetData(short type, short index, std::string& data);

		void CodeToName(const std::string& code, std::string& name);

	protected:

		P m_ptr;
	};

	// Implementation CpFutureCodeObject

	template<class P, class U>
	CpFutureCodeObject<P,U>::CpFutureCodeObject()
		: m_ptr(0)
	{
	}

	template<class P, class U>
	bool CpFutureCodeObject<P,U>::CreateInstance()
	{
		return SUCCEEDED(m_ptr.CreateInstance(__uuidof(U)));
	}

	template<class P, class U>
	bool CpFutureCodeObject<P,U>::IsCreated()
	{
		return (m_ptr != 0);
	}

	template<class P, class U>
	void CpFutureCodeObject<P,U>::Release()
	{
		m_ptr.Release();
	}

	template<class P, class U>
	CpFutureCodeObject<P,U>::operator IUnknownPtr ()
	{
		return m_ptr;
	}

	template<class P, class U>
	short CpFutureCodeObject<P,U>::GetCount()
	{
		return m_ptr->GetCount();
	}


	template<class P, class U>
	void CpFutureCodeObject<P,U>::GetData(short type, short index, std::string& data)
	{
		data = (char*)(_bstr_t)(m_ptr->GetData(type, index));
	}

	template<class P, class U>
	void CpFutureCodeObject<P,U>::CodeToName(const std::string& code, std::string& name)
	{
		name = (char*)(_bstr_t)(m_ptr->CodeToName((_bstr_t)code.c_str()));
	}

}} // namespace uCash::Cybos