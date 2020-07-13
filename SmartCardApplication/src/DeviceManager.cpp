#include "DeviceManager.h"

#define CHECK_STATUS(lRetValue, msg)						        \
		if(lRetValue != SCARD_S_SUCCESS)					        \
		{													        \
			_tprintf(_T("\n   " msg  ": Error 0x%04X %s\n\n"),		\
				   lRetValue,this->SCardGetErrorString(lRetValue)); \
			return lRetValue;								        \
	    }

#define CHECK_ERROR(lRetValue, msg)				                        \
		if(lRetValue != SCARD_S_SUCCESS)					            \
		{													            \
			_tprintf(_T("\n   " msg  ": Error 0x%04X %s\n\n"),		    \
				   lRetValue,this->SCardGetErrorString(lRetValue));     \
			return lRetValue;								            \
		}

DeviceManager::DeviceManager() {}

DeviceManager::~DeviceManager() = default;

// Public functions 
uint64_t DeviceManager::ObtainReaders()
{
	LONG			lRetValue;
	LPTSTR          pszReader;
	DWORD           cch = SCARD_AUTOALLOCATE;
	INT				iNumberOfReaders;
	INT				iSelectedReader;

    sc_readers.clear();
    // Get CONTEXT for sdcard reader
    lRetValue = SCardEstablishContext(
        SCARD_SCOPE_USER,       // Scope of the resource manager context.
        NULL,                   // r.f.u
        NULL,                   // r.f.u
        &this->m_hContext);	    // Returns the resource manager handle.

    CHECK_STATUS(lRetValue, "SCardEstablishContext");

    // Now get the readers
    lRetValue = SCardListReaders(
        this->m_hContext,               // Resource manager handle. 
        NULL,                           // NULL: list all readers in the system 
        (LPTSTR)&pmszReaders,           // Returs the card readers list.
        &cch);

    CHECK_STATUS(lRetValue, "SCardListReaders");

    iNumberOfReaders = 0;
    pszReader = pmszReaders;

    if (pszReader == nullptr)
        return -1;


    while ( *pszReader != '\0' )
    {
        pszaReaders[iNumberOfReaders] = (LPTSTR)pszReader;
        sc_readers.push_back(pszaReaders[iNumberOfReaders]);
        pszReader = pszReader + _tcslen(pszReader) + 1;
        iNumberOfReaders++;
    }

    if (iNumberOfReaders == 0)
        return -1;
     
    CHECK_ERROR(lRetValue, "SCardFreeMemory");

	return lRetValue;
}

uint64_t DeviceManager::ReleaseMemory()
{
    // Release memory
    return SCardFreeMemory(m_hContext, pmszReaders);
}

void DeviceManager::SetSelectedReader(LPSTR selected_reader)
{
    _tcscpy_s(m_szSelectedReader, selected_reader);
}

std::vector<LPSTR>& DeviceManager::getReaders()
{
    return sc_readers;
}

uint64_t DeviceManager::WaitForCardPresent()
{
    SCARD_READERSTATE sReaderState;
    uint64_t lRetValue;

    sReaderState.szReader       = (LPCTSTR)this->m_szSelectedReader;
    sReaderState.dwCurrentState = SCARD_STATE_UNAWARE;
    sReaderState.dwEventState   = SCARD_STATE_UNAWARE;

    _tprintf(_T("Checking for the presence of a card...\n"));
    // SCardGetStatusChange waits until card is inserted
    // so, show message, and wait
    lRetValue = SCardGetStatusChange(
        m_hContext,     // Resource manager handle.
        30, //Max. amount of time (in milliseconds) to wait for an action.
        &sReaderState,  // Reader state
        1);             // Number of readers
    
    CHECK_STATUS(lRetValue, _T("SCardGetStatusChange"));

    // Now check if the card is present
    if ((sReaderState.dwEventState & SCARD_STATE_PRESENT) == SCARD_STATE_PRESENT)
    {
        _tprintf(_T("Card found continue the execution...\n"));
    }
    else
    {
        _tprintf(_T("Card not found, waiting for card...\n"));

        lRetValue = -1;
    }

    return lRetValue;
}

uint64_t DeviceManager::WaitForCardRemoval()
{
    SCARD_READERSTATE sReaderState;
    uint64_t lRetValue;

    sReaderState.szReader       = m_szSelectedReader;
    sReaderState.dwCurrentState = SCARD_STATE_UNAWARE;
    sReaderState.dwEventState   = SCARD_STATE_UNAWARE;

    // Call as in WaitForCardPresent to GetStatusChange
    lRetValue = SCardGetStatusChange(
                    m_hContext,         // Resource manager handle.
                    30,                 // Max. amount of time (milliseconds) to wait
                    &sReaderState,      // Reader state
                    1);                 // Number of readers
    
    CHECK_STATUS(lRetValue, _T("SCardGetStatusChange"));

    if ((sReaderState.dwEventState & SCARD_STATE_EMPTY) == 0)
    {
        do
        {
            lRetValue = SCardGetStatusChange(m_hContext, 30, &sReaderState, 1);
            CHECK_ERROR(lRetValue, _T("SCardGetStatusChange"));
            Sleep(100);
        } while ((sReaderState.dwEventState & SCARD_STATE_EMPTY) == 0);
    }
    printf("Card Removed...\n");

    return lRetValue;
}

uint64_t DeviceManager::ActivateCard()
{
    uint64_t lRetValue;

    // Connect to a card contained by specific reader
    lRetValue = SCardConnect(
                    m_hContext,             // Resource manager handle
                    m_szSelectedReader,     // Reader name
                    SCARD_SHARE_EXCLUSIVE,  // Share Mode. (Exclusive)
                    SCARD_PROTOCOL_Tx,      // Preferred protocols (T=0 or T=1)
                    &m_hCard,               // handler
                    &m_dwActiveProtocol);   // Active protocol

    CHECK_STATUS(lRetValue, _T("SCardConnect"));

    switch (m_dwActiveProtocol)
    {
    case SCARD_PROTOCOL_T0:
        _tprintf(_T("Card activated via T=0 protocol\n"));
        break;
    case SCARD_PROTOCOL_T1:
        _tprintf(_T("Card activated via T=1 protocol\n"));
        break;
    case SCARD_PROTOCOL_UNDEFINED:
        _tprintf(_T("Unknown protocol, can't connect...\n"));
        lRetValue = -1;
        break;
    default:
        _tprintf(_T("WT...\n"));
        lRetValue = -1;
        break;
    }

    if (lRetValue != -1)
        this->cardCommunication = new CardCommunication(this->m_hContext, this->m_hCard, this->m_dwActiveProtocol);

    return lRetValue;
}

uint64_t DeviceManager::Disconnect()
{
    uint64_t lRetValue;

    _tprintf(_T("Disconnecting the smart card\n"));
    // Terminates smart card connection
    lRetValue = SCardDisconnect(
                    m_hCard,        // Card handle
                    SCARD_UNPOWER_CARD); // Action to take on the card

    CHECK_STATUS(lRetValue, _T("SCardDisconnect"));
    return lRetValue;
}

uint64_t DeviceManager::ReleaseContext()
{
    uint64_t lRetValue;

    // Release the Resource Manager Context.
    lRetValue = SCardReleaseContext(m_hContext);
    m_hContext = NULL;

    return lRetValue;
}

CardCommunication*	DeviceManager::getCardCommunication()
{
    return this->cardCommunication;
}

// Private functions
LPCTSTR DeviceManager::SCardGetErrorString(uint64_t lRetValue)
{
    switch (lRetValue)
    {
    case 0x0l:
        return _T("SCard OK");
        break;

    case 0x80100001:
        return _T("SCard internal error");
        break;

    case 0x80100002:
        return _T("SCard cancelled");
        break;

    case 0x80100003:
        return _T("SCard invalid handle");
        break;

    case 0x80100004:
        return _T("SCard invalid parameter");
        break;

    case 0x80100005:
        return _T("SCard invalid target");
        break;

    case 0x80100006:
        return _T("SCard no memory");
        break;

    case 0x80100007:
        return _T("SCard waited too long");
        break;

    case 0x80100008:
        return _T("SCard insufficient buffer");
        break;

    case 0x80100009:
        return _T("SCard unknown reader");
        break;

    case 0x8010000a:
        return _T("SCard timeout");
        break;

    case 0x8010000b:
        return _T("SCard sharing violation");
        break;

    case 0x8010000c:
        return _T("SCard no smartcard");
        break;

    case 0x8010000d:
        return _T("SCard unknown card");
        break;

    case 0x8010000e:
        return _T("SCard cant dispose");
        break;

    case 0x8010000f:
        return _T("SCard proto mismatch");
        break;

    case 0x80100010:
        return _T("SCard not ready");
        break;

    case 0x80100011:
        return _T("SCard invalid value");
        break;

    case 0x80100012:
        return _T("SCard system cancelled");
        break;

    case 0x80100013:
        return _T("SCard communications error");
        break;

    case 0x80100014:
        return _T("SCard unknown error");
        break;

    case 0x80100015:
        return _T("SCard invalid atr");
        break;

    case 0x80100016:
        return _T("SCard not transacted");
        break;

    case 0x80100017:
        return _T("SCard reader unavailable");
        break;

    case 0x80100018:
        return _T("SCard p shutdown");
        break;

    case 0x80100019:
        return _T("SCard pci too small");
        break;

    case 0x8010001a:
        return _T("SCard reader unsupported");
        break;

    case 0x8010001b:
        return _T("SCard duplicate reader");
        break;

    case 0x8010001c:
        return _T("SCard card unsupported");
        break;

    case 0x8010001d:
        return _T("SCard no service");
        break;

    case 0x8010001e:
        return _T("SCard service stopped");
        break;

    case 0x8010001f:
        return _T("SCard unexpected");
        break;

    case 0x80100020:
        return _T("SCard icc installation");
        break;

    case 0x80100021:
        return _T("SCard icc createorder");
        break;

    case 0x80100022:
        return _T("SCard unsupported feature");
        break;

    case 0x80100023:
        return _T("SCard dir not found");
        break;

    case 0x80100024:
        return _T("SCard file not  ound");
        break;

    case 0x80100025:
        return _T("SCard no dir");
        break;

    case 0x80100026:
        return _T("SCard no file");
        break;

    case 0x80100027:
        return _T("SCard no access");
        break;

    case 0x80100028:
        return _T("SCard write too many");
        break;

    case 0x80100029:
        return _T("SCard bad seek");
        break;

    case 0x8010002a:
        return _T("SCard invalid chv");
        break;

    case 0x8010002b:
        return _T("SCard unknown res mng");
        break;

    case 0x8010002c:
        return _T("SCard no such certificate");
        break;

    case 0x8010002d:
        return _T("SCard certificate unavailable");
        break;

    case 0x8010002e:
        return _T("SCard no readers available");
        break;

    case 0x80100065:
        return _T("SCard warning unsupported card");
        break;

    case 0x80100066:
        return _T("SCard warning unresponsive card");
        break;

    case 0x80100067:
        return _T("SCard warning unpowered card");
        break;

    case 0x80100068:
        return _T("SCard warning reset card");
        break;

    case 0x80100069:
        return _T("SCard warning removed card");
        break;

    case 0x8010006a:
        return _T("SCard warning security violation");
        break;

    case 0x8010006b:
        return _T("SCard warning wrong chv");
        break;

    case 0x8010006c:
        return _T("SCard warning chv blocked");
        break;

    case 0x8010006d:
        return _T("SCard warning eof");
        break;

    case 0x8010006e:
        return _T("SCard warning cancelled by user");
        break;

    case 0x0000007b:
        return _T("SCard inaccessible boot device");
        break;

    default:
        return _T("invalid error code");
    }
}

int64_t DeviceManager::getOptionFromUser(uint64_t nOfOptions)
{
    int64_t selectedOption = -1;

    if (nOfOptions == 0)
        return -1;

    while (selectedOption == -1)
    {
        system("cls");

        _tprintf(_T("Please select a reader (0..n)\n"));
        for (size_t i = 0; i < nOfOptions; i++)
        {
            _tprintf(_T("%d:\t%s\n"), i, pszaReaders[i]);
        }

        _tprintf(_T("\n\n>> "));

        selectedOption = getchar();

        while ((getchar()) != '\n');

        selectedOption -= '0';

        if ((selectedOption < 0) || (selectedOption > 9))
            selectedOption = -1;

        if (selectedOption > (nOfOptions - 1))
            selectedOption = -1;
    }

    return selectedOption;
}