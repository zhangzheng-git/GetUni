// GetUniqueDlg.h : 头文件
//

#pragma once
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>

#include <algorithm> //sort
using namespace std;
typedef vector<string> VecSim;

// CGetUniqueDlg 对话框
class CGetUniqueDlg : public CDialog
{
// 构造
public:
	CGetUniqueDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETUNIQUE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedFilebuts();

    //vectore去重
    VecSim UniqueElementInVector(VecSim vec);
    void BStrReplace1(string &SrcStr, const char *OldValue, const char *NewValue);
    CEdit *m_SEDIT,*m_XEDIT;
    CStatic *m_STATIC;
    CString m_SrcPath,m_SXPath,m_DestPath;
    string m_strInfo;
    VecSim m_vecSrc,m_vecDest,m_vecSrcUni,m_vecDestUni;

    afx_msg void OnBnClickedFilebutx();
    afx_msg void OnBnClickedOk();
};
