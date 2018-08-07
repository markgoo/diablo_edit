// DlgPropertyList.cpp: 实现文件
//

#include "stdafx.h"
#include "Diablo Edit2.h"
#include "DlgPropertyList.h"
#include "afxdialogex.h"


// CDlgPropertyList 对话框

IMPLEMENT_DYNAMIC(CDlgPropertyList, CDialogEx)

CDlgPropertyList::CDlgPropertyList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PropertyList, pParent)
{}

CDlgPropertyList::~CDlgPropertyList() {}

void CDlgPropertyList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstProperty);
	DDX_Control(pDX, IDC_EDIT1, m_edParam[0]);
	DDX_Control(pDX, IDC_EDIT2, m_edParam[1]);
	DDX_Control(pDX, IDC_EDIT3, m_edParam[2]);
}

void CDlgPropertyList::SetPropList(CPropertyList * prop) {
	m_pPropList = prop;
	if (m_pPropList) {

	} else
		EnableEditing(FALSE);

}

void CDlgPropertyList::EnableEditing(BOOL enable) {
	m_lstProperty.EnableWindow(enable);
	for (auto & ed : m_edParam)
		ed.EnableWindow(enable);
}

BEGIN_MESSAGE_MAP(CDlgPropertyList, CDialogEx)
END_MESSAGE_MAP()


// CDlgPropertyList 消息处理程序
