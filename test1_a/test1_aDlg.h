
// test1_aDlg.h : 헤더 파일
//

using namespace std;
#include <string>
#include <map>
#include <list>
#include <vector>
#include "usb4761ex.h"
#pragma once


static CStringList* ListMsg; // C2248 Error Solution :: local --> global & ListMsg have to be declared just one.

static list<string> stdListMsg; // C2248 Error Solution :: local --> global & ListMsg have to be declared just one.

static vector<string> vecMsg;

struct ST_Node 
{
	string name_;
	map<string, ST_Node> children_;

	ST_Node() : name_() {}
	ST_Node(string name) : name_(name) {}
	ST_Node(const ST_Node& r) 
	{
		name_ = r.name_;
		children_ = r.children_;
	}
	void write(int indent) 
	{
		// for (int i = 0; i < indent * 4; i++) cout << " ";
		// cout << name_ << endl;
		string strData;
		string strData2;
		for (int i = 0; i < indent * 4; i++) 
		{			
			strData += " ";
		}
		strData2 = strData + name_ + "\n";
		ListMsg->AddTail((CString)strData2.c_str());
		stdListMsg.push_back( strData2);
		vecMsg.push_back( strData2 );
		
		for ( map<string, ST_Node>::iterator it = children_.begin(); it != children_.end(); it++) 
		{
			it->second.write(indent + 1);
		}
	}
};


// Ctest1_aDlg 대화 상자
class Ctest1_aDlg : public CDialog
{
// 생성입니다.
public:
	Ctest1_aDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~Ctest1_aDlg() { closeUsbDevice();};

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEST1_A_DIALOG };
	// USB4761 Test
	CString m_szInSigValue;
	CString m_szInSigValue2;
	CString m_szOutSignChkValue;
	CString m_szOutSignChkValue2;
	BOOL  m_bOutSig[2][8]; // (1) CHECK BOX
	CString m_szProfileName;
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	afx_msg void OnBtnClickedOutSigChk();


// 구현입니다.
protected:
	HICON m_hIcon;
	CString m_strMsg; // (1)
	CString m_strMsg2;
	CString m_szInput; // (11)

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOK();
	void OnSendOutSignal( UINT iPos ); // (2) CHECK BOX
	afx_msg void OnGetInputSignal(); // (11) 

public:
	int m_iSelectColor;
	afx_msg void OnBnClickedRdSelectColor();
	void testSortDepth();
	void testString();
	void testVirtualFunc();
	void test_ex1();
	void test_stopswatch();

	void getToken( const string& strSet, vector<string>& tok, const string& delimit = " ");
	list<string> stringToList(string str);


	CUSB4761Comm* m_usbInst;
	int  openUsbDevice();
	int  openUsbDevice2();
	int  closeUsbDevice();
	CUSB4761Comm* GetUsbInst() {return m_usbInst;}

	void dispWriteCheckData(  CUSB4761Comm& usbCm, BYTE chkData, int iIndex=0);
	void refreshWriteData(  CUSB4761Comm& usbCm, BYTE setData, int iIndex=0);
	void refreshReadData(  CUSB4761Comm& usbCm, BYTE chkData, int iIndex=0);


	int GetIndexRefIds( vector< CString > vecRefId );
	int WriteLog( string strMsg );

};


class CParent
{
	string s;
public:
	string msg;
	CParent():s("Parent"){;}
	virtual string what()
	{
		return s;
	}
};

class CChild : public CParent
{
	string s;
public:
	CChild():s("Child"), CParent() {;}
	string what()
	{
		return s;
	}
};
