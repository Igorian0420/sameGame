// COptionDialog.cpp: файл реализации
//

#include "pch.h"
#include "SameGame.h"
#include "OptionDialog.h"
#include "afxdialogex.h"


// Диалоговое окно COptionDialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent)
{
}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_ctrlStaticText1);
	DDX_Control(pDX, IDC_STATIC_TEXT_2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()


void COptionDialog::OnBnClickedButtonDefaults()
{

	//oтдельно рассматриваем два варианта
	if (m_bRowColumnDialog)
		m_nValue1 = m_nValue2 = 15; //размер доски 15x15
	else
		m_nValue1 = m_nValue2 = 35; //размер блоков 35x35

	  //oбновляем параметры элементов до новых значений
	UpdateData(false);
}

BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (m_bRowColumnDialog)
	{
		//обновляем заголовок диалогового окна
		SetWindowText(_T("Update block count"));

		//обновдяем элементы "Static Text"
		m_ctrlStaticText1.SetWindowText(_T("Строк"));
		m_ctrlStaticText2.SetWindowTextW(_T("Столбцов"));
	}
	else
	{
		//обновляем заголовок диалогового окна
		SetWindowText(_T("Update block size"));

		//обновдяем элементы "Static Text"
		m_ctrlStaticText1.SetWindowText(_T("Ширина блока"));
		m_ctrlStaticText2.SetWindowTextW(_T("Высота блока"));
	}
	return TRUE;
}