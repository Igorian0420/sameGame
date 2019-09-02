
// SameGameDoc.h: интерфейс класса CSameGameDoc 
//


#pragma once
#include "cSameGameBoard.h"
#include <stack>

class CSameGameDoc : public CDocument
{
protected: // создать только из сериализации
	CSameGameDoc() noexcept;
	//virtual ~CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

// Атрибуты
public:

// Операции
public:
	//геттеры для получения информации о параметрах игрового поля
	COLORREF getBoardSpace(int row, int col)
	{
		return m_board->getBoardSpace(row, col);
	}
	void setupBoard(void) { m_board->setupBoard(); }

	int getWidth(void) { return m_board->getWidth(); }
	void setWidth(int nWidth) { m_board->setWidth(nWidth); }

	int getHeight(void) { return m_board->getHeight(); }
	void setHeight(int nHeight) { m_board->setHeight(nHeight); }

	int getColumns(void) { return m_board->getColumns(); }
	void setColumns(int nColumns) { m_board->setColumns(nColumns); }

	int getRows(void) { return m_board->getRows(); }
	void setRows(int nRows) { m_board->setRows(nRows); }

	void deleteBoard(void) { m_board->deleteBoard(); }
	bool IsGameOver(void) { return m_board->IsGameOver(); }
	int DeleteBlocks(int row, int col);
	int GetRemainingCount() { return m_board->GetRemainingCount(); }

	int GetNumColors() { return m_board->GetNumColors(); }
	void SetNumColors(int nColors);

	//aункции Отмены/Повтора 
	void UndoLast();
	bool CanUndo();
	void RedoLast();
	bool CanRedo();

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	//CSameGameDoc();
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//функции для очистки стеков "Отмены/Повтора" 
	void ClearUndo();
	void ClearRedo();

	//экземпляр обьекта нашей игровой доски
	cSameGameBoard* m_board;

	//стек "Отмена"
	std::stack<cSameGameBoard*> m_undo;

	//стек "Повтор"
	std::stack<cSameGameBoard*> m_redo;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
