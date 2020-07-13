#pragma once
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#include <winscard.h>
#include <tchar.h>
#include <cstdio>
#include <iostream>
#include <cstdint>
#include "CardCommunication.h"

class DeviceManager
{
public:
	DeviceManager();

	~DeviceManager();

	virtual uint64_t ObtainReaders();
	virtual uint64_t WaitForCardPresent();
	virtual uint64_t WaitForCardRemoval();
	virtual uint64_t ActivateCard();
	virtual uint64_t Disconnect();
	virtual uint64_t ReleaseContext();
	virtual uint64_t ReleaseMemory();
	virtual void SetSelectedReader(LPSTR selected_reader);

	virtual std::vector<LPSTR>& getReaders();

	virtual CardCommunication*	getCardCommunication();

private:

	std::vector<LPSTR>	sc_readers;					// Smart cards readers list
	SCARDCONTEXT		m_hContext;					// Resource manager handle 
	SCARDHANDLE			m_hCard;					// Card Handle
	TCHAR				m_szSelectedReader[256];	// Selected card reader name.
	DWORD				m_dwActiveProtocol;			// Active protocol (T=0, T=1 or undefined).
	LPTSTR				pszaReaders[16];			// Name of the readers
	LPTSTR				pmszReaders = NULL;
	CardCommunication*  cardCommunication;


	virtual LPCTSTR SCardGetErrorString(uint64_t lRetValue);
	virtual int64_t getOptionFromUser(uint64_t nOfOptions);
};

#endif // !DEVICEMANAGER_H
