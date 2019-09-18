// GetUniqueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetUnique.h"
#include "GetUniqueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGetUniqueDlg 对话框




CGetUniqueDlg::CGetUniqueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetUniqueDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_strInfo = "";
}

void CGetUniqueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGetUniqueDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_FILEBUTS, &CGetUniqueDlg::OnBnClickedFilebuts)
    ON_BN_CLICKED(IDC_FILEBUTX, &CGetUniqueDlg::OnBnClickedFilebutx)
    ON_BN_CLICKED(IDOK, &CGetUniqueDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetUniqueDlg 消息处理程序

BOOL CGetUniqueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
    

    m_SEDIT = (CEdit*)GetDlgItem(IDC_SEDIT);
    m_XEDIT = (CEdit*)GetDlgItem(IDC_XEDIT);
    m_STATIC = (CStatic*)GetDlgItem(IDC_STATICW);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetUniqueDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetUniqueDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetUniqueDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetUniqueDlg::OnBnClickedFilebuts()
{
   m_strInfo = "";
   m_STATIC->SetWindowText(m_strInfo.c_str());
   CFileDialog SrcFile(TRUE,NULL,NULL,0,"txt文件(*.txt)|*.txt||");
   if (SrcFile.DoModal()==IDOK)
   {
       m_SrcPath = SrcFile.GetPathName();
       m_SEDIT->SetWindowText(m_SrcPath);
   }  

    //获取源文件
   //ifstream fpSrcFile(m_SrcPath);
   ifstream fpSrcFile;
   setlocale(LC_ALL, "Chinese-simplified");		//设置中文环境，否则一旦文件路径中存在中文，ifstream::open就会打开失败
   fpSrcFile.open(m_SrcPath,ios::in);
   setlocale(LC_ALL,"C");           //还原环境
   if (fpSrcFile.is_open()==false)
   {
       AfxMessageBox("文件打开失败");
   }
   string strSrc;
   while (getline(fpSrcFile,strSrc))
   {
       if (strSrc.empty())
       {
           continue;
       }
       BStrReplace1(strSrc," ","");
       m_vecSrc.push_back(strSrc);
   }
   fpSrcFile.close();
   char buffer[1024]={0};
   sprintf(buffer,"源文件中:%d条数据\r\n",m_vecSrc.size());
   m_strInfo += buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());
    
   //剔除源文件中的重复项
   m_vecSrcUni = UniqueElementInVector(m_vecSrc);
    
   sprintf(buffer,"去重后:%d条数据\r\n",m_vecSrcUni.size());
   m_strInfo += buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());
}

VecSim CGetUniqueDlg::UniqueElementInVector( VecSim vec )
{

    vector<string>::iterator it;
    sort(vec.begin(),vec.end());
    it = unique(vec.begin(),vec.end());
    if (it != vec.end())
    {
        vec.erase(it,vec.end());
    }
    return vec;
}




void CGetUniqueDlg::OnBnClickedFilebutx()
{
   CFileDialog SXFile(TRUE,NULL,NULL,0,"txt文件(*.txt)|*.txt||");
   if (SXFile.DoModal()==IDOK)
   {
       m_SXPath = SXFile.GetPathName();
       m_XEDIT->SetWindowText(m_SXPath);
   }

    //获取筛选文件
   ifstream fpDestFile;
   setlocale(LC_ALL,"Chinese-simplified");
   fpDestFile.open(m_SXPath,ios::in);
   setlocale(LC_ALL,"C");
   if (fpDestFile.is_open()==FALSE)
   {
       AfxMessageBox("打开文件失败");
   }
   string strDest;
   while (getline(fpDestFile,strDest))
   {
       if (strDest.empty())
       {
           continue;
       }
       BStrReplace1(strDest," ","");
       m_vecDest.push_back(strDest);
   }
   fpDestFile.close();
   char buffer[1024]={0};
   sprintf(buffer,"筛选文件中:%d条数据\r\n",m_vecDest.size());
   m_strInfo +=buffer; 
   m_STATIC->SetWindowText(m_strInfo.c_str());

   m_vecDestUni = UniqueElementInVector(m_vecDest);
   sprintf(buffer,"去重后:%d条数据\r\n",m_vecDestUni.size());
   m_strInfo += buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());

}

void CGetUniqueDlg::OnBnClickedOk()
{
   
   //提取两文件中的唯一值
   vector<string>::iterator itDest;
   for (int i=0;i<m_vecSrcUni.size();i++)
   {
       for (itDest=m_vecDestUni.begin();itDest!=m_vecDestUni.end();)
       {
           if (m_vecSrcUni[i]==(*itDest))
           {
             itDest  =  m_vecDestUni.erase(itDest);
             continue;
           }
           else{
             itDest++;
           }
          
       }
   }
  
   //输出结果文件到指定路径
   string str = m_SXPath.GetBuffer();
   int nPose = str.rfind('\\');
   str = str.substr(0,nPose+1);
   str +="JumpDevices.csv";
   FILE *fp = fopen(str.c_str(),"w");

   for(int i=0;i<m_vecDestUni.size();i++)
   {
       m_vecDestUni[i] +=",103.56.76.163,9600,103.56.76.163,9600,\n";
       fwrite(m_vecDestUni[i].c_str(),1,m_vecDestUni[i].length(),fp);
   }
   fclose(fp);
   char buffer[1024]={0};
   sprintf(buffer,"合计%d条数据已成功提取到 %s",m_vecDestUni.size(),str.c_str());

   //sprintf(buffer,"       提取到唯一数据:%d条",m_vecDest.size());
   m_strInfo +=buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());

   m_vecDest.clear();
   m_vecSrc.clear();
   m_vecSrcUni.clear();
   m_vecDestUni.clear();
   AfxMessageBox(buffer);
}



//将原文中所有的指定字符串全部替换成另一个字符串，只从头到尾扫一遍，例如将12212中的12换成21，最后将得到21221
void CGetUniqueDlg::BStrReplace1(string &SrcStr, const char *OldValue, const char *NewValue)
{
  int NewLen = strlen(NewValue);
  for (int Pos=0; Pos!=string::npos; Pos += NewLen)
     {
       Pos = SrcStr.find(OldValue, Pos);
       if (Pos != string::npos)
          { SrcStr.replace(Pos, strlen(OldValue), NewValue); }
       else
          { break; }
     }
}