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

#include <cassert>
#include <deque>
#include <vector>

namespace uCash { namespace Tech {


	template<class T>
	class List
	{
	public:

		void AddBack(const T& v);

		void AddFront(const T& v);

		T& GetBack(int i);

		T& GetFront(int i);

		void SetBack(int i, const T& v);

		void SetFront(int i, const T& v);

		int Count() const;

		void RemoveAll();

		void Reserve(int n);

	private:

		std::deque<T> m_list;

	};

	template<class T>
	void List<T>::AddBack(const T& v)
	{
		m_list.push_back(v);
	}

	template<class T>
	void List<T>::AddFront(const T& v)
	{
		m_list.push_front(v);
	}

	template<class T>
	T& List<T>::GetBack(int i)
	{
		assert(0 <= i && (size_t)i < m_list.size());
		return m_list.at(Count() - i - 1);
	}

	template<class T>
	T& List<T>::GetFront(int i)
	{
		assert(0 <= i && (size_t)i < m_list.size());
		return m_list.at(i);
	}

	template<class T>
	void List<T>::SetBack(int i, const T& v)
	{
		assert(0 <= i && (size_t)i < m_list.size());
		GetBack(Count() - i - 1) = v;
	}

	template<class T>
	void List<T>::SetFront(int i, const T& v)
	{
		assert(0 <= i && (size_t)i < m_list.size());
		GetFront(i) = v;
	}

	template<class T>
	int List<T>::Count() const
	{
		return (int)m_list.size();
	}

	template<class T>
	void List<T>::Reserve(int n)
	{

	}

	template<class T>
	void List<T>::RemoveAll()
	{
		m_list.clear();
	}

}}