

#include "stdafx.h"
#include "usb4761ex.h"


CUSB4761Comm::CUSB4761Comm()
{

}
CUSB4761Comm::~CUSB4761Comm()
{

}

int CUSB4761Comm::cmOpenPtr( const string& szPathName, const string& szFileName)
{

	m_portDo = 0;
	m_portDi = 0;	

	for( int i=0;i<DEV_MAXSIZE ; i++)
	{
		m_bufWrite[i] = 0 ;
		m_bufWrite_check[i] = 0;
		m_bufRead[i] = 0;
	}
	m_eventCount = 0;
	m_iDevSize = 0;

	m_strPfPath = szPathName;
	m_strPfName = szFileName;

	m_insDo = InstantDoCtrl::Create();
	m_insDi = InstantDiCtrl::Create();

	m_insDi->addInterruptHandler( OnDiSnapEvent, this);  // TODO

	Array<DeviceTreeNode>* sptedDevices = m_insDo->getSupportedDevices();

	int iCount = sptedDevices->getCount();
	if( iCount == 0)
	{
		// TODO
		return RET_FAIL; 
	}

	// START ----------------------------------------------------------->
	// have to set DeviceInformation by DeviceTreeNode( not if error invoked in x64 platform )
	// Error Msg : 모호한 오버로딩
		
	wstring wszDesp = L"";
	string szDesp = "";
	string::size_type iPos = 0;
	for( int i=0; i<iCount ; i++)
	{	
		DeviceTreeNode const & node = sptedDevices->getItem(i);
		TRACE( "%d, %s\n", node.DeviceNumber, node.Description );
		wszDesp = node.Description ;		
		szDesp.assign( wszDesp.begin(), wszDesp.end());
		iPos = szDesp.find("USB");

		if(  iPos != string::npos )
		{
			//DeviceInformation devInfo( node.DeviceNumber );  
			//m_usbdevInfo.push_back( make_pair(node.DeviceNumber, &devInfo) );
			m_usbdevNode.push_back( node );
			//m_insDo->setSelectedDevice(devInfo);
			//m_insDi->setSelectedDevice(devInfo);
		}	
	}
	m_iDevSize = (int)m_usbdevNode.size();
	sptedDevices->Dispose();
	//
	// __END ----------------------------------------------------------->
	int iret = cmLoadProfile();

	return iret;

}
void CUSB4761Comm::cmClosePrt()
{
	m_insDo->Dispose();
	m_insDi->Dispose();
}

int CUSB4761Comm::cmReset( const string& szFullPathName, const string& szFileName)
{
	cmClosePrt();
	int iret = cmOpenPtr(szFullPathName, szFileName);

	return iret;
}


int CUSB4761Comm::cmLoadProfile( ACT_DIO iAct)
{
	string  szProfilePath = "";
	wstring wszProfilePath = L"";
	ErrorCode eCode;
	m_bLoadPf = TRUE;

	szProfilePath = m_strPfPath + "\\" + m_strPfName;
	wszProfilePath.assign( szProfilePath.begin(), szProfilePath.end());	

	if( iAct == ACT_NONE || iAct == ACT_WRITE )
	{
		eCode = m_insDo->LoadProfile( wszProfilePath.c_str());
		if( eCode != Success )
		{
			// TODO
			m_bLoadPf = FALSE;
			//return RET_FAIL;
		}
	}
	if( iAct == ACT_NONE || iAct == ACT_READ)
	{
		eCode = m_insDi->LoadProfile( wszProfilePath.c_str());
		if( eCode != Success )
		{
			// TODO
			m_bLoadPf = FALSE;
			//return RET_FAIL;
		}
	}
	return RET_PASS;
}

int CUSB4761Comm::cmWrite( BYTE setData, int iIndex)
{
	if( cmLoadPfSelectDev( m_insDo, iIndex) == RET_PASS ) 
	{
		m_bufWrite[iIndex] = setData;
		m_insDo->Write( m_portDo, PORT_COUNT, &m_bufWrite[iIndex]);
		return RET_PASS;
	}
	else
	{
		m_bufWrite[iIndex] = 0;
		return RET_FAIL;
	}
}
int CUSB4761Comm::cmWrite_Read( BYTE& getData, int iIndex)
{	
	if( cmLoadPfSelectDev( m_insDo, iIndex) == RET_PASS ) 
	{
		m_insDo->Read( m_portDo, PORT_COUNT, &m_bufWrite_check[iIndex] );
		getData = m_bufWrite_check[iIndex];
		return RET_PASS;
	}
	else
	{
		getData = m_bufWrite_check[iIndex] = 0;
		return RET_FAIL;
	}
}

int CUSB4761Comm::cmWrite_Check( BOOL& bResult, int iIndex)
{
	bResult = TRUE;
	BYTE getData = 0x0;
	if( cmWrite_Read( (BYTE&)getData, iIndex) == RET_PASS )
	{
		if( m_bufWrite[iIndex] != getData)
		{
			bResult = FALSE;  // false
		}	
		return RET_PASS;	
	}
	else
	{
		return RET_FAIL;
	}
}

int CUSB4761Comm::cmRead( BYTE& getData, int iIndex)
{	
	if( cmLoadPfSelectDev( m_insDi, iIndex) == RET_PASS ) 
	{
		m_insDi->Read( m_portDi, PORT_COUNT, &getData );
		m_bufRead[iIndex] = getData;
		return RET_PASS;
	}
	else
	{
		getData = m_bufRead[iIndex] = 0;
		return RET_FAIL;
	}
}

int  CUSB4761Comm::cmWriteBit( int iPos, BYTE setData, int iIndex)
{
	if( cmLoadPfSelectDev( m_insDo, iIndex) == RET_PASS ) 
	{
		m_bufWrite[iIndex] = setData;
		m_insDo->WriteBit( m_portDo, iPos, setData);
		return RET_PASS;
	}
	else
	{
		m_bufWrite[iIndex] = 0;
		return RET_FAIL;
	}
}
int CUSB4761Comm::cmReadBit( int iPos, BYTE& getData, int iIndex)
{
	if( cmLoadPfSelectDev( m_insDi, iIndex) == RET_PASS ) 
	{		
		m_insDi->ReadBit( m_portDi, iPos, &getData );
		m_bufRead[iIndex] = (getData << iPos) & 0xFF;	
		return RET_PASS;
	}
	else
	{
		return RET_FAIL;
	}
}

void CUSB4761Comm::cmGetBitfromByte( BYTE setData, int iPos, BOOL& getData)
{
	int iResult = 0;
	iResult = ( setData >> iPos ) & 0x1;
	getData = (iResult == 1)? TRUE:FALSE;

}
void CUSB4761Comm::cmIntToBin( unsigned int iHex, string& szBin)
{
	bitset<8> outbit = iHex;

	szBin = outbit.to_string();	
}
BYTE CUSB4761Comm::cmGetWriteData(int iIndex)
{
	return m_bufWrite[iIndex];

}


int CUSB4761Comm::cmLoadPfSelectDev( InstantDoCtrl* outsig,  int iIndex)
{
	DeviceInformation devinfo( m_usbdevNode[iIndex].DeviceNumber ); 
	outsig->setSelectedDevice( devinfo );
	if( !m_bLoadPf) cmLoadProfile( ACT_WRITE);

	if( m_bLoadPf) return RET_PASS;
	else return RET_FAIL;
}

int CUSB4761Comm::cmLoadPfSelectDev( InstantDiCtrl* insig, int iIndex )
{
	DeviceInformation devinfo( m_usbdevNode[iIndex].DeviceNumber ); 
	insig->setSelectedDevice( devinfo );
	if( !m_bLoadPf) cmLoadProfile( ACT_READ);

	if( m_bLoadPf) return RET_PASS;
	else return RET_FAIL;
}
int CUSB4761Comm::cmGetDevSize()
{
	return m_iDevSize;
}

void CUSB4761Comm::cmGetDevDesp( string& szDesp )
{ 
	wstring wszDesp = m_usbdevNode[0].Description;
	szDesp.assign( wszDesp.begin(), wszDesp.end());
}

void CUSB4761Comm::OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam)
{
	//CUSB4761Comm * uParam = (CUSB4761Comm *)userParam;
	//uParam->m_eventCount++;
	//::SendMessage(hWnd,WM_UPDATELIST,uParam->m_eventCount,(LPARAM)args);
}