
// test1_aDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "test1_a.h"
#include "test1_aDlg.h"
#include "stdafx.h"
#include <direct.h>


#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// Ctest1_aDlg 대화 상자

// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//



Ctest1_aDlg::Ctest1_aDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ctest1_aDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ListMsg = new CStringList();
	
}

void Ctest1_aDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RD_RED, m_iSelectColor);
	DDX_Text(pDX, IDC_MSG, m_strMsg); // (2) 
	DDX_Text(pDX, IDC_MSG2, m_strMsg2);
	DDX_Text(pDX, IDC_EDIT_EX, m_szInput); // (12)

	// USB4761
	DDX_Text(pDX, IDC_ST_INSIG_DISP, m_szInSigValue );
	DDX_Text(pDX, IDC_ST_INSIG_DISP2, m_szInSigValue2 );
	DDX_Text(pDX, IDC_ST_OUTSIG_CHK_DISP, m_szOutSignChkValue);
	DDX_Text(pDX, IDC_ST_OUTSIG_CHK_DISP2, m_szOutSignChkValue2);
	DDX_Text(pDX, IDC_GRP_OUTSIG, m_szProfileName);
	DDX_Check(pDX, IDC_CK_OUTSIG1, m_bOutSig[0][0]);
	DDX_Check(pDX, IDC_CK_OUTSIG2, m_bOutSig[0][1]);
	DDX_Check(pDX, IDC_CK_OUTSIG3, m_bOutSig[0][2]);
	DDX_Check(pDX, IDC_CK_OUTSIG4, m_bOutSig[0][3]);
	DDX_Check(pDX, IDC_CK_OUTSIG5, m_bOutSig[0][4]);
	DDX_Check(pDX, IDC_CK_OUTSIG6, m_bOutSig[0][5]);
	DDX_Check(pDX, IDC_CK_OUTSIG7, m_bOutSig[0][6]);
	DDX_Check(pDX, IDC_CK_OUTSIG8, m_bOutSig[0][7]);
	DDX_Check(pDX, IDC_CK_OUTSIG9, m_bOutSig[1][0]);
	DDX_Check(pDX, IDC_CK_OUTSIG10, m_bOutSig[1][1]);
	DDX_Check(pDX, IDC_CK_OUTSIG11, m_bOutSig[1][2]);
	DDX_Check(pDX, IDC_CK_OUTSIG12, m_bOutSig[1][3]);
	DDX_Check(pDX, IDC_CK_OUTSIG13, m_bOutSig[1][4]);
	DDX_Check(pDX, IDC_CK_OUTSIG14, m_bOutSig[1][5]);
	DDX_Check(pDX, IDC_CK_OUTSIG15, m_bOutSig[1][6]);
	DDX_Check(pDX, IDC_CK_OUTSIG16, m_bOutSig[1][7]);
}

BEGIN_MESSAGE_MAP(Ctest1_aDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RD_RED, OnBnClickedRdSelectColor)
	ON_BN_CLICKED(IDC_RD_YELLOW, OnBnClickedRdSelectColor)
	ON_BN_CLICKED(IDC_RD_BLUE, OnBnClickedRdSelectColor)

	ON_BN_CLICKED( IDC_BTN_OUTSIG_CHK, OnBtnClickedOutSigChk) // USB4761


	ON_CONTROL_RANGE( BN_CLICKED, IDC_CK_OUTSIG1, IDC_CK_OUTSIG16, OnSendOutSignal) // (3) CHECK BOX
	/*
	ON_BN_CLICKED( IDC_CK_OUTSIG1, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG2, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG3, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG4, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG5, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG6, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG7, OnSendOutSignal);  // (3) CHECK BOX
	ON_BN_CLICKED( IDC_CK_OUTSIG8, OnSendOutSignal);  // (3) CHECK BOX
*/

	ON_BN_CLICKED( IDC_BTN_INSIG, OnGetInputSignal) // (22) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Ctest1_aDlg 메시지 처리기

BOOL Ctest1_aDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_iSelectColor = 1;	


	// USB4761 Test
	for( int i=0;i<8;i++) 
	{
		m_bOutSig[0][i] = FALSE;
		m_bOutSig[1][i] = FALSE;
	}
	m_szInSigValue = _T("syjun");
	m_szOutSignChkValue = _T("");
	m_szOutSignChkValue2 = _T("");	


	if( openUsbDevice() == RET_FAIL ) // USB4761
	{
		AfxMessageBox(_T(">> The USB Port opening is failed. Pleaes, refer it."));
	}
	UpdateData(FALSE);  // val2Ctrl

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Ctest1_aDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Ctest1_aDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Ctest1_aDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ctest1_aDlg::OnBnClickedRdSelectColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


list<string> Ctest1_aDlg::stringToList(string str) 
{
	istringstream f(str);
	string s;
	list<string> res;

	while (getline(f, s, '/')) 
		res.push_back(s);
	return res;
}

void Ctest1_aDlg::testSortDepth()
{

	ListMsg->RemoveAll();
	vecMsg.clear();
	stdListMsg.clear();
	m_strMsg = _T("");
	m_strMsg2 = _T("");
	UpdateData(false);
	
	string inputs[] = {
		"/비둘기/기러기/호랑이/사자",
			"/비둘기/기러기/호랑이/여우",
			"/비둘기/기러기/고양이",
			"/비둘기/기러기/강아지",
			"/짬타이거"
	};  // ( Updated by C++11 )
	
/*
	string inputs[5] = {
		"/A/B/C/F",
		"/A/B/C/G",
		"/A/B/D",
		"/A/B/E",
		"/H"
	};  // ( Updated by C++11 )
*/
	int count = sizeof(inputs) / sizeof(string);
	
	ST_Node root;
	list<string>::iterator itr;
	string s;
	for (int i = 0; i < count; i++) 
	{
		list<string> inputList = stringToList(inputs[i]);
		ST_Node* current = &root;
		// for (string s : inputList)  //  (Updated by C++11)

		for( itr = inputList.begin(); itr!=inputList.end();++itr)
		{
			s = itr->c_str();
			if (current->children_.find(s) == current->children_.end()) 
			{
				ST_Node newNode(s);
				current->children_[s] = newNode;
			}
			current = &current->children_[s];
		}
	}
	root.write(-2);

	m_strMsg.Append( _T("---------1. CStringlist"));
	// display :: using CStringList
	POSITION pos = ListMsg->GetHeadPosition();
	CString strGet2 = _T("");
	
	while(pos)
	{
		strGet2 = ListMsg->GetNext(pos);
		m_strMsg.Append( strGet2 );
	}

	/*
	m_strMsg2.Append( _T("---------2. list"));
	// display2 :: using list<string>	
	list<string>::iterator itr_2;
	strGet2 = _T("");
	for( itr_2 = stdListMsg.begin() ; itr_2 != stdListMsg.end() ; ++itr_2 )
	{
		strGet2 = (CString)itr_2->c_str();
		m_strMsg2.Append( strGet2 );
	}
	*/
	
	m_strMsg2.Append( _T("---------3. vector"));
	strGet2 = _T("");
	// display2 :: using list<string>	
	vector<string>::iterator itr_3;
	for( itr_3 = vecMsg.begin() ; itr_3 != vecMsg.end() ; ++itr_3 )
	{
		strGet2 = (CString)itr_3->c_str();
		m_strMsg2.Append( strGet2 );
	}
	
	UpdateData(false);
	
	//return 0;

}

void Ctest1_aDlg::getToken( const string& strSet, vector<string>& tok, const string& delim )
{
	if( delim.empty())
	{

		stringstream ssm( strSet );
		string strBuf;
		while( ssm >> strBuf )
		{
			tok.push_back( strBuf );
		}
	}
	else
	{

		string::size_type iLastPos = strSet.find_first_not_of( delim, 0 );
		string::size_type iPos = strSet.find_first_of( delim, iLastPos);

		while( iLastPos!=string::npos || iPos!=string::npos )
		{
			tok.push_back( strSet.substr( iLastPos, iPos-iLastPos));
			iLastPos = strSet.find_first_not_of( delim, iPos+1 );
			iPos = strSet.find_first_of(delim, iLastPos);
		}
		// display using cout
		copy( tok.begin(), tok.end(), ostream_iterator<string>(cout, ", "));
	
	}

}
void Ctest1_aDlg::testString()
{
	vector<string> tokens;
	string str("CLang Python Java Caffe What.");
	CString szMsg;
	CStringA szMsg_A;


	/*

	string::size_type iPos = str.find_first_of( " .");
	int i=0;
	while( iPos != string::npos )
	{
		szMsg.Format( _T(" %d : %d \n"), i++, iPos);
		m_strMsg.Append( szMsg );		
		iPos = str.find_first_of( " .",iPos + 1);
	}
	*/
	
	getToken( str, tokens, "\0");
	vector<string>::iterator itr;
	for( itr = tokens.begin(); itr!=tokens.end(); itr++ )
	{
		szMsg = (CString)itr->c_str();
		m_strMsg.Append( szMsg + _T("\n") );

	}
	
	// 1) string --> CString


	// 2) CString --> string

	// 3) int --> string

	// 4) string --> int 



	UpdateData(false);
}
void Ctest1_aDlg::testVirtualFunc()
{
	CParent p;
	CChild c;
	CChildChild cc;

	m_strMsg.Append( _T("--- Pointer version ---\n") );
	CParent* ptr_p = &c;
	CParent* ptr_p2 = &p;
	CParent* ptr_p3 = &cc;
	string szData = ptr_p->what();

	m_strMsg.Append( (CString)szData.c_str() + _T("\n"));  // print child

	szData = ptr_p2->what();

	m_strMsg.Append( (CString)szData.c_str() + _T("\n")); // print parent


	szData = ptr_p3->what2();

	m_strMsg.Append( (CString)szData.c_str()); // print child child

	szData = ptr_p3->what();

	m_strMsg.Append( (CString)szData.c_str()); // print child child
	

	UpdateData(false);	

}


void Ctest1_aDlg::OnBtnClickedOutSigChk()
{
	// TODO
	UpdateData();

	BYTE getData = 0x0;
	CUSB4761Comm* usbCm = GetUsbInst();
	for( int i=0; i< usbCm->cmGetDevSize(); i++)
	{
		getData = 0x0;
		usbCm->cmWrite_Read( (BYTE&)getData, i);
		Sleep(1);

		refreshWriteData( (CUSB4761Comm&)usbCm, getData, i);
		dispWriteCheckData( (CUSB4761Comm&)usbCm, getData, i);
	}
	UpdateData(FALSE); // val to ctrl

}

void Ctest1_aDlg::OnSendOutSignal( UINT iPos )
{
	UpdateData();

	BYTE setData = 0x0;
	BYTE getData = 0x0;

	int iIndex = 0;
	int iMok = 0;
	
	iMok =  (iPos - IDC_CK_OUTSIG1) / CH_SIZE ; // 0 or 1
	iIndex = iPos - (IDC_CK_OUTSIG1 + CH_SIZE*iMok); // 0 ~ 7

	CUSB4761Comm* usbCm = GetUsbInst();
	int iDevSize = usbCm->cmGetDevSize();
	if( iMok >= iDevSize)
	{
		if( m_bOutSig[iMok][iIndex] == TRUE)
		{
			m_bOutSig[iMok][iIndex] = FALSE;
			UpdateData(FALSE);
		}
		CString szMsg = _T("");
		szMsg.Format( (_T(">> Error :: Device Order is %d. But, Device is %d.")), iMok, iDevSize);
		AfxMessageBox( szMsg );
		return ;
	}
	

	setData = m_bOutSig[iMok][iIndex] & 0xFF;		
	usbCm->cmWriteBit( iIndex, setData, iMok);
	Sleep(1);

	getData = 0x0;
	usbCm->cmWrite_Read( (BYTE&)getData, iMok);
	Sleep(1);

	refreshWriteData( (CUSB4761Comm&)usbCm, getData, iMok);
	dispWriteCheckData( (CUSB4761Comm&)usbCm, getData, iMok);

	UpdateData(FALSE);

}

void Ctest1_aDlg::OnGetInputSignal()
{
	UpdateData();

	BYTE getData = 0x0;
	CUSB4761Comm* usbCm = GetUsbInst();

	for( int i=0; i<usbCm->cmGetDevSize() ; i++)
	{
		getData = 0x0;
		if( usbCm->cmRead( (BYTE&)getData, i) == RET_PASS )
		{
			Sleep(1);
			refreshReadData( (CUSB4761Comm&)usbCm, getData, i);
		}
		else
		{
			m_szInSigValue = _T("can not read");
			m_szInSigValue2 = _T("can not read");
			break;
		}
	}

	UpdateData(FALSE);

}
void Ctest1_aDlg::dispWriteCheckData( CUSB4761Comm& usbCm, BYTE chkData, int iIndex)
{

	string szData = "";	
	usbCm.cmIntToBin( chkData, (string&)szData );
	if( iIndex == 0) m_szOutSignChkValue = szData.c_str();
	else m_szOutSignChkValue2 = szData.c_str();
}


void Ctest1_aDlg::refreshWriteData( CUSB4761Comm& usbCm, BYTE setData, int iIndex)
{
	for( int i=0;i<usbCm.cmGetChSize();i++)
	{
		m_bOutSig[iIndex][i] = (setData >> i) & 0x1;
	}

}
void Ctest1_aDlg::refreshReadData( CUSB4761Comm& usbCm, BYTE chkData, int iIndex)
{

	string szData = "";	
	usbCm.cmIntToBin( chkData, (string&)szData );
	if( iIndex == 0) 	m_szInSigValue = szData.c_str();
	else   	m_szInSigValue2 = szData.c_str();

}


int  Ctest1_aDlg::openUsbDevice()
{
	char cCurPath[1024];
	string szCurPath = "" ;
	string szProfileName = "USB-4761.xml";

	_getcwd( cCurPath, 1024);
	szCurPath.assign( cCurPath, strlen(cCurPath));

	m_usbInst = new CUSB4761Comm();

	if( GetUsbInst()->cmOpenPtr(szCurPath, szProfileName) == RET_FAIL )
	{
		// FAIL
		return RET_FAIL;
	}

	CString szMsg = _T("");
	string strDevDesp = "";
	m_strMsg = _T("");
	int iDevSize = GetUsbInst()->cmGetDevSize();
	GetUsbInst()->cmGetDevDesp(strDevDesp);

	szMsg.Format( _T("%s%d\n"), _T("Device Size = "),  iDevSize);
	m_strMsg.Append( szMsg );	
	szMsg = strDevDesp.c_str();
	szMsg += _T("\n");
	szMsg += _T("\n");
	m_strMsg.Append( szMsg );

	string szSum = szCurPath + "\\" + szProfileName;
	m_szProfileName = szSum.c_str();

	if( iDevSize == 1 )
	{
		for( int i=0; i< GetUsbInst()->cmGetChSize(); i++) 
		{
			GetDlgItem( IDC_CK_OUTSIG9 + i)->EnableWindow( FALSE );
		}	
	}

	for( int i=0;i< iDevSize ; i++)
	{
		szMsg.Format( (_T("Device#%d No. is %d\n")), i, GetUsbInst()->cmGetDevNo(i) );
		m_strMsg.Append( szMsg );
	}
	TRACE( (LPCTSTR)m_strMsg );

	return RET_PASS;

}


int  Ctest1_aDlg::openUsbDevice2()
{
	char cCurPath[1024];
	string szCurPath = "" ;
	string szProfileName = "USB-4761.xml";

	_getcwd( cCurPath, 1024);
	szCurPath.assign( cCurPath, strlen(cCurPath));

	m_usbInst = new CUSB4761Comm();

	if( GetUsbInst()->cmOpenPtr(szCurPath, szProfileName) == RET_FAIL )
	{
		// FAIL
		return RET_FAIL;
	}

	string szMsg = "";
	string szAllMsg = "";
	string strDevDesp = "";
	ostringstream oss;
	
	int iDevSize = GetUsbInst()->cmGetDevSize();
	GetUsbInst()->cmGetDevDesp(strDevDesp);

	oss << iDevSize;
	szMsg = "Device Size = " + oss.str();
	szAllMsg.append( szMsg );
	szAllMsg.append( strDevDesp );

	string szSum = szCurPath + "\\" + szProfileName;
	m_szProfileName = szSum.c_str();

	if( iDevSize == 1 )
	{
		for( int i=0; i< GetUsbInst()->cmGetChSize(); i++) 
		{
			GetDlgItem( IDC_CK_OUTSIG9 + i)->EnableWindow( FALSE );
		}	
	}


	ostringstream oss2;
	for( int i=0;i< iDevSize ; i++)
	{
		oss << i;
		oss2 << GetUsbInst()->cmGetDevNo(i);
		szMsg = "Device#" + oss.str() + " No. is " + oss2.str() ;
		szAllMsg.append ( szMsg );
	}
	m_strMsg = szAllMsg.c_str();
	TRACE( (LPCTSTR)m_strMsg );

	return RET_PASS;

}
int  Ctest1_aDlg::closeUsbDevice()
{
	m_usbInst->cmClosePrt();
	delete m_usbInst;

	return RET_PASS;
}

void Ctest1_aDlg::test_ex1()
{
	UpdateData(); // TRUE :: ctrl 2 val

	string strInData;

	// 0x... : 16, 0 : 8, 
	string::size_type iPos = strInData.find_first_of( '0');
	if( iPos == 0)
	{
		iPos = strInData.find_first_of( 'x', iPos);
		if( iPos ==1)
		{
			// hexa
			string strTmp;
			strTmp = strInData.substr(2, string::npos);
			
		}
		else
		{
			// oct
		}
	}
	else 
	{
		// decimal

	}
}

void Ctest1_aDlg::test_stopswatch()
{
	

}

int Ctest1_aDlg::GetIndexRefIds( vector< string > vecRefId )
{
	vector< string >::iterator vItr_J = find( vecRefId.begin(), vecRefId.end(), "-");

	if( vItr_J != vecRefId.end() )
	{
		int iIndex = (int)distance( vecRefId.begin(), vItr_J);
		return iIndex;		
	}
	else 
	{
		vItr_J = find( vecRefId.begin(), vecRefId.end(), "NG");
		if( vItr_J != vecRefId.end() )
		{
			int iIndex = (int)distance( vecRefId.begin(), vItr_J);
			return iIndex;		
		}
		else
		{
			vItr_J = find( vecRefId.begin(), vecRefId.end(), "OK");
			if( vItr_J != vecRefId.end() )
			{
				int iIndex = (int)distance( vecRefId.begin(), vItr_J);
				return iIndex;		
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

int Ctest1_aDlg::GetIndexTargets( vector< string > vecTarget, vector< string > vecDelim )
{
	
	int iIndex = -1;
	vector< string >::iterator vItr_T;
	vector< string >::iterator vItr_D;
	// vecTarget <--- searching vecDelim

	vItr_D = vecDelim.begin();
	for( ; vItr_D != vecDelim.end() ; vItr_D++)
	{
		vItr_T = find( vecTarget.begin(), vecTarget.end(), *vItr_D );
		if( vItr_T != vecTarget.end())
		{
			iIndex = distance( vecTarget.begin(), vItr_T);
			break;
		}
	}
	if( iIndex < 0)
	{
		iIndex = 0;
	}
	return iIndex;			
}

int Ctest1_aDlg::WriteLog( string strMsg )
{

	// make file name
	const int CHAR_SIZE = 1024;
	string szFileName = "";
	string szCurPath = "";
	string szFullName = "";
	wstring wszFullName = L"";
	char cCurPath[CHAR_SIZE];
	char cDate[CHAR_SIZE];
	ofstream hFile;

	// current directory + date 
	memset( cCurPath, 0x0, CHAR_SIZE);
	_getcwd( cCurPath, CHAR_SIZE);
	szCurPath.assign( cCurPath, strlen(cCurPath));

	// make file name by current date
	memset( cDate, 0x0, CHAR_SIZE);
	time_t now = time(NULL);
	struct tm* timeinfo;
	timeinfo = localtime( &now );
	strftime( cDate, CHAR_SIZE, "%Y%m%d_%H", timeinfo); // %M%S ( minute, second )
	szFileName.assign( cDate, strlen(cDate));

	// open file 
	szFullName = szCurPath + "\\" + szFileName + ".log"; 	
	wszFullName.assign(szFullName.begin(), szFullName.end());
	hFile.open( wszFullName.c_str(), ios::out | ios::app);
	if( hFile.is_open() )
	{
		hFile << strMsg << endl;
		hFile.close();
		return 1;
	}
	return 0;
}


void Ctest1_aDlg::OnOK()
{

	//testSortDepth();
	// testString();
	// testVirtualFunc();
	//test_ex1();


/*
	vector< string > vec1;
	vector< string > vec2;

	vec1.push_back("0") ;
	vec1.push_back("2") ;
	vec1.push_back("NG") ;
	vec1.push_back("0") ;

	vec2.push_back( "-");
	vec2.push_back( "NG");
	vec2.push_back( "OK");

	int iIndex = GetIndexRefIds( vec1 );

	int iIndex2 = GetIndexTargets( vec1, vec2);
*/
	// ascii code --> unicode --------------> START
	CString szMsg;
	CStringA szMsg_A;
	CString szResult;

	szMsg_A = "I'm Ascii Code, using Multi-byte. I will be changed the UniCode.";
	szMsg = CString(szMsg_A);

	szResult.Format(_T("%s : %s"), szMsg, (CString)szMsg_A);
	// ascii code --> unicode --------------> __END

	// WriteLog("apple");

	///CDialog::OnOK();
}