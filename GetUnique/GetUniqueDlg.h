// GetUniqueDlg.h : ͷ�ļ�
//

#pragma once
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>

#include <algorithm> //sort
using namespace std;
typedef vector<string> VecSim;

// CGetUniqueDlg �Ի���
class CGetUniqueDlg : public CDialog
{
// ����
public:
	CGetUniqueDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETUNIQUE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedFilebuts();

    //vectoreȥ��
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
