#if !defined(USB4761EX_H)
#define USB4761EX_H


#include <string>
#include <bitset>
#include <algorithm>
#include <vector>
#include <map>
#include "bdaqctrl.h"

#pragma once

using namespace Automation::BDaq;
using namespace std;

typedef unsigned char BYTE;

#define PORT_COUNT 1
#define BUF_SIZE 1  // 8bit channel == 1port
#define BRD_NO 0
#define RET_PASS 1
#define RET_FAIL 0
#define DEV_MAXSIZE 8
#define CH_SIZE  8

#define WM_UPDATELIST           (WM_USER + 0x1002)

typedef enum DI_SIGNAL
{
	DI_SET_DONE = 0x1,
	DI_EXT_DONE = 0x2,
	NUM_OF_DIDSIG
};
typedef enum DO_SIGNAL
{
	DO_SET_WAIT = 0x1,
	DO_EXT_WAIT = 0x2,
	NUM_OF_DOSIG
};

typedef enum ACT_DIO
{
	ACT_WRITE = 0,
	ACT_READ = 1,
	ACT_NONE = 2
};

class CUSB4761Comm
{
protected:	

private:
	InstantDoCtrl* m_insDo;
	InstantDiCtrl* m_insDi;

	int32 m_portDo;
	int32 m_portDi;

	string m_strPfPath;
	string m_strPfName;

	BYTE m_bufWrite[DEV_MAXSIZE];
	BYTE m_bufWrite_check[DEV_MAXSIZE];
	BYTE m_bufRead[DEV_MAXSIZE];

	int m_eventCount;

	vector< DeviceTreeNode > m_usbdevNode;

	BOOL m_bLoadPf;
	int  m_iDevSize;

public:
	CUSB4761Comm();
	~CUSB4761Comm();

	int cmOpenPtr( const string& szPathName, const string& szFileName);
	void cmClosePrt();
	int cmReset( const string& szFullPathName, const string& szFileName);

	int cmLoadProfile( ACT_DIO iact=ACT_NONE);


	int cmWrite(BYTE setData, int iIndex=0);
	int cmWrite_Read( BYTE& getData, int iIndex=0);
	int cmWrite_Check(BOOL& bResult, int iIndex=0);

	int cmRead(BYTE& getData, int iIndex=0);

	int cmWriteBit( int iPos, BYTE setData, int iIndex=0);
	int cmReadBit( int iPos, BYTE& getData, int iIndex=0);

	void cmIntToBin( unsigned int iHex, string& szBin);

	void cmGetBitfromByte( BYTE setData, int iPos, BOOL& getData);
	BYTE cmGetWriteData( int iIndex=0);

	int cmLoadPfSelectDev(  InstantDoCtrl* outsig, int iIndex=0 );
	int cmLoadPfSelectDev(  InstantDiCtrl* insig, int iIndex=0 );

	int cmGetDevSize();
	int cmGetChSize() { return CH_SIZE;}
	int cmGetDevNo( int iIndex ) { return m_usbdevNode[iIndex].DeviceNumber;}
	void cmGetDevDesp( string& szDesp );

	static void  BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam);


};

#endif