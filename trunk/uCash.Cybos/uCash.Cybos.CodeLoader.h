#pragma once

namespace uCash { namespace Cybos {

	class UCASHCYBOS_API CodeLoader
	{
	public:

		CodeLoader();

		virtual ~CodeLoader();

		void Release();

		virtual void Load(StockCodeList& codeList);

	private:

		CpStockCode m_stock;
	};

}}