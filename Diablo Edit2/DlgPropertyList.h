#pragma once

#include "D2Item.h"

// CDlgPropertyList 对话框

class CDlgPropertyList : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPropertyList)
	CPropertyList * m_pPropList = NULL;

	void EnableEditing(BOOL enable);
public:
	CDlgPropertyList(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPropertyList();
	void SetPropList(CPropertyList * prop);

// 对话框数据
	enum { IDD = IDD_DIALOG_PropertyList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_lstProperty;
	CEdit m_edParam[3];
};
