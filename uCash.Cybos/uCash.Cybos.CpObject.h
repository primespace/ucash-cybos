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

namespace uCash { namespace Cybos {
		
	template<class P, class U>
	class CpObject
	{
	public:

		CpObject();

		bool CreateInstance();

		bool IsCreated();

		void Release();

		operator IUnknownPtr ();

		bool BlockRequest();
		
		bool SetInputValue(short type, CComSafeArray<long>& value);

		bool SetInputValue(short type, LPCTSTR value);

		bool SetInputValue(short type, int value); 

		bool SetInputValue(short type, unsigned short value);

		template<class T>
		void GetHeaderValue(short type, T& value);
	
		template<class T>
		void GetHeaderValue(short type, std::string& value);

		template<class T>
		void GetDataValue(short field, short index, T& value);

		bool Subscribe();

		bool IsSubscribed();

		void Unsubscribe();

		long GetContinue();

	protected:

		bool m_subscribed;

		P m_ptr;
	};

	// Implementation CpObject

	template<class P, class U>
	CpObject<P,U>::CpObject()
		: m_ptr(0), m_subscribed(false)
	{
	}

	template<class P, class U>
	bool CpObject<P,U>::CreateInstance()
	{
		return SUCCEEDED(m_ptr.CreateInstance(__uuidof(U)));
	}

	template<class P, class U>
	bool CpObject<P,U>::IsCreated()
	{
		return (m_ptr != 0);
	}

	template<class P, class U>
	void CpObject<P,U>::Release()
	{
		m_ptr.Release();
	}

	template<class P, class U>
	CpObject<P,U>::operator IUnknownPtr ()
	{
		return m_ptr;
	}

	template<class P, class U>
	bool CpObject<P,U>::BlockRequest()
	{
		return SUCCEEDED(m_ptr->BlockRequest());
	}

	template<class P, class U>
	bool CpObject<P,U>::SetInputValue(short type, CComSafeArray<long>& value)
	{
		return SUCCEEDED(m_ptr->SetInputValue(type, CComVariant(value.Detach())));
	}

	template<class P, class U>
	bool CpObject<P,U>::SetInputValue(short type, LPCTSTR value)
	{
		_variant_t varValue = value;
		return SUCCEEDED(m_ptr->SetInputValue(type, varValue));
	}

	template<class P, class U>
	bool CpObject<P,U>::SetInputValue(short type, int value)
	{
		return SUCCEEDED(m_ptr->SetInputValue(type, value));
	}

	template<class P, class U>
	bool CpObject<P,U>::SetInputValue(short type, unsigned short value)
	{
		return SUCCEEDED(m_ptr->SetInputValue(type, value));
	}

	template<class P, class U>
	bool CpObject<P,U>::Subscribe()
	{
		if(m_subscribed) {
			return true;
		} else {
			if(SUCCEEDED(m_ptr->Subscribe())) {
				m_subscribed = true;
				return true;
			} else {
				m_subscribed = false;
				return false;
			}
		}
	}

	template<class P, class U>
	bool CpObject<P,U>::IsSubscribed()
	{
		return m_subscribed;
	}

	template<class P, class U>
	void CpObject<P,U>::Unsubscribe()
	{
		if(m_subscribed) {
			m_ptr->Unsubscribe();
			m_subscribed = false;
		}
	}

	template<class P, class U>
	template<class T>
	void CpObject<P,U>::GetHeaderValue(short type, T& value)
	{
		value = m_ptr->GetHeaderValue(type);
	}

	template<class P, class U>
	template<class T>
	void CpObject<P,U>::GetHeaderValue(short type, std::string& value)
	{
		value = (char*)(_bstr_t)(_variant_t)m_ptr->GetHeaderValue(type);
	}

	template<class P, class U>
	template<class T>
	void CpObject<P,U>::GetDataValue(short field, short index, T& value)
	{
		value = (T)(_variant_t)m_ptr->GetDataValue(field, index);
	}

	template<class P, class U>
	long CpObject<P,U>::GetContinue()
	{
		return m_ptr->GetContinue();
	}

}} // namespace uCash::Cybos

