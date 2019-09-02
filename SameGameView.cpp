
// SameGameView.cpp: реализация класса CSameGameView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "OptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()

	ON_COMMAND(ID_32776, &CSameGameView::On32776)
	ON_UPDATE_COMMAND_UI(ID_32776, &CSameGameView::OnUpdate32776)
	ON_COMMAND(ID_32775, &CSameGameView::On32775)
	ON_UPDATE_COMMAND_UI(ID_32775, &CSameGameView::OnUpdate32775)
	ON_COMMAND(ID_32774, &CSameGameView::On32774)
	ON_UPDATE_COMMAND_UI(ID_32774, &CSameGameView::OnUpdate32774)
	ON_COMMAND(ID_32773, &CSameGameView::On32773)
	ON_UPDATE_COMMAND_UI(ID_32773, &CSameGameView::OnUpdate32773)
	ON_COMMAND(ID_32772, &CSameGameView::On32772)
	ON_UPDATE_COMMAND_UI(ID_32772, &CSameGameView::OnUpdate32772)
	ON_COMMAND(ID_32777, &CSameGameView::On32777)
	ON_COMMAND(ID_32778, &CSameGameView::On32778)
	ON_COMMAND(ID_32771, &CSameGameView::On32771)
	ON_UPDATE_COMMAND_UI(ID_32771, &CSameGameView::OnUpdate32771)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC)
{
	//создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//сохраняем текущее состояние контнкста устройства
	int nDCSave = pDC->SaveDC();

	//получаем размеры клиентской области
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->getBoardSpace(-1, -1);

	//сначала отрисовываем фон
	pDC->FillSolidRect(&rcClient, clr);

	//создаем кисть для рисования
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	//рисуем блоки
	for (int row = 0; row < pDoc->getRows(); row++)
	{
		for (int col = 0; col < pDoc->getColumns(); col++)
		{
			clr = pDoc->getBoardSpace(row, col);

			//вычисляем размер и позицию игрового пространства
			CRect rcBlock;
			rcBlock.top = row * pDoc->getHeight();
			rcBlock.left = col * pDoc->getWidth();
			rcBlock.right = rcBlock.left + pDoc->getWidth();
			rcBlock.bottom = rcBlock.top + pDoc->getHeight();

			//заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, clr);

			//рисуем контур
			pDC->Rectangle(&rcBlock);
		}
	}
	//восстанавливаем контекст устройства
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//изменяем размер окна
	resizeWindow();
}

void CSameGameView::resizeWindow()
{
	//создаем указатель на document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//получаем размеры клиентской области
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	//изменяем размеры окна на основе размеров нашей доски
	rcWindow.right = rcWindow.left + pDoc->getWidth() * pDoc->getColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top + pDoc->getHeight() * pDoc->getRows() + nHeightDiff;

	//функция MoveWindow изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//получаем индекс строки и столбца елемента, по которому был осуществлен клик мышки
	int row = point.y / pDoc->getHeight();
	int col = point.x / pDoc->getWidth();

	//удаляем блоки из Document
	int count = pDoc->DeleteBlocks(row, col);

	//проверяем удаление блоков
	if (count > 0)
	{
		//перерисовываем view
		Invalidate();
		UpdateWindow();

		//проверяем закончилась ли игра
		if (pDoc->IsGameOver())
		{
			//получаем количество оставшихся блоков
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"), remaining);

			//отображаем результат игры
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::setColorCount(int numColors)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//устанвливаем количество цветов
	pDoc->SetNumColors(numColors);

	//переписываем view
	Invalidate();
	UpdateWindow();
}

void CSameGameView::On32776()
{
	setColorCount(7);
}


void CSameGameView::OnUpdate32776(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
}


void CSameGameView::On32775()
{
	setColorCount(6);
}

void CSameGameView::OnUpdate32775(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
}


void CSameGameView::On32774()
{
	setColorCount(5);
}


void CSameGameView::OnUpdate32774(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
}


void CSameGameView::On32773()
{
	setColorCount(4);
}


void CSameGameView::OnUpdate32773(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
}


void CSameGameView::On32772()
{
	setColorCount(3);
}

void CSameGameView::OnUpdate32772(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);
}



void CSameGameView::On32777()
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//создаем диалоговое окно
	COptionDialog dlg(true, this);

	//устанавливаем параметры строк и столбцов
	dlg.m_nValue1 = pDoc->getRows();
	dlg.m_nValue2 = pDoc->getColumns();

	//отображаем полученное окно 
	if (dlg.DoModal() == IDOK)
	{
		//сначала удаляем игровое поле
		pDoc->deleteBoard();

		//устанавливаем значения, переданные пользователем
		pDoc->setRows(dlg.m_nValue1);
		pDoc->setColumns(dlg.m_nValue2);

		//обновляем игровое поле
		pDoc->setupBoard();

		//изменяем размеры view
		resizeWindow();
	}
}


void CSameGameView::On32778()
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//создаем диалоговое окно
	COptionDialog dlg(true, this);

	//устанавливаем параметры ширины и высоты
	dlg.m_nValue1 = pDoc->getWidth();
	dlg.m_nValue2 = pDoc->getHeight();

	//отображаем полученное окно 
	if (dlg.DoModal() == IDOK)
	{
		//удаляем игровое поле
		pDoc->deleteBoard();

		//устанавливаем значения, переданные пользователем
		pDoc->setWidth(dlg.m_nValue1);
		pDoc->setHeight(dlg.m_nValue2);

		//обновляем игровое поле
		pDoc->setupBoard();

		//изменяем размеры view
		resizeWindow();
	}
}


void CSameGameView::On32771()
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RedoLast();

	//переписываем view
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdate32771(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//включаем опцию, если она доступна
	pCmdUI->Enable(pDoc->CanRedo());
}


void CSameGameView::OnEditUndo()
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->UndoLast();

	//переписываем view
	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	//получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//включаем опцию, если она доступна
	pCmdUI->Enable(pDoc->CanUndo());
}
