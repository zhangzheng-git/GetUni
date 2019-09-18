// GetUniqueDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetUnique.h"
#include "GetUniqueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGetUniqueDlg �Ի���




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


// CGetUniqueDlg ��Ϣ�������

BOOL CGetUniqueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
    

    m_SEDIT = (CEdit*)GetDlgItem(IDC_SEDIT);
    m_XEDIT = (CEdit*)GetDlgItem(IDC_XEDIT);
    m_STATIC = (CStatic*)GetDlgItem(IDC_STATICW);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetUniqueDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGetUniqueDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetUniqueDlg::OnBnClickedFilebuts()
{
   m_strInfo = "";
   m_STATIC->SetWindowText(m_strInfo.c_str());
   CFileDialog SrcFile(TRUE,NULL,NULL,0,"txt�ļ�(*.txt)|*.txt||");
   if (SrcFile.DoModal()==IDOK)
   {
       m_SrcPath = SrcFile.GetPathName();
       m_SEDIT->SetWindowText(m_SrcPath);
   }  

    //��ȡԴ�ļ�
   //ifstream fpSrcFile(m_SrcPath);
   ifstream fpSrcFile;
   setlocale(LC_ALL, "Chinese-simplified");		//�������Ļ���������һ���ļ�·���д������ģ�ifstream::open�ͻ��ʧ��
   fpSrcFile.open(m_SrcPath,ios::in);
   setlocale(LC_ALL,"C");           //��ԭ����
   if (fpSrcFile.is_open()==false)
   {
       AfxMessageBox("�ļ���ʧ��");
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
   sprintf(buffer,"Դ�ļ���:%d������\r\n",m_vecSrc.size());
   m_strInfo += buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());
    
   //�޳�Դ�ļ��е��ظ���
   m_vecSrcUni = UniqueElementInVector(m_vecSrc);
    
   sprintf(buffer,"ȥ�غ�:%d������\r\n",m_vecSrcUni.size());
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
   CFileDialog SXFile(TRUE,NULL,NULL,0,"txt�ļ�(*.txt)|*.txt||");
   if (SXFile.DoModal()==IDOK)
   {
       m_SXPath = SXFile.GetPathName();
       m_XEDIT->SetWindowText(m_SXPath);
   }

    //��ȡɸѡ�ļ�
   ifstream fpDestFile;
   setlocale(LC_ALL,"Chinese-simplified");
   fpDestFile.open(m_SXPath,ios::in);
   setlocale(LC_ALL,"C");
   if (fpDestFile.is_open()==FALSE)
   {
       AfxMessageBox("���ļ�ʧ��");
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
   sprintf(buffer,"ɸѡ�ļ���:%d������\r\n",m_vecDest.size());
   m_strInfo +=buffer; 
   m_STATIC->SetWindowText(m_strInfo.c_str());

   m_vecDestUni = UniqueElementInVector(m_vecDest);
   sprintf(buffer,"ȥ�غ�:%d������\r\n",m_vecDestUni.size());
   m_strInfo += buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());

}

void CGetUniqueDlg::OnBnClickedOk()
{
   
   //��ȡ���ļ��е�Ψһֵ
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
  
   //�������ļ���ָ��·��
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
   sprintf(buffer,"�ϼ�%d�������ѳɹ���ȡ�� %s",m_vecDestUni.size(),str.c_str());

   //sprintf(buffer,"       ��ȡ��Ψһ����:%d��",m_vecDest.size());
   m_strInfo +=buffer;
   m_STATIC->SetWindowText(m_strInfo.c_str());

   m_vecDest.clear();
   m_vecSrc.clear();
   m_vecSrcUni.clear();
   m_vecDestUni.clear();
   AfxMessageBox(buffer);
}



//��ԭ�������е�ָ���ַ���ȫ���滻����һ���ַ�����ֻ��ͷ��βɨһ�飬���罫12212�е�12����21����󽫵õ�21221
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