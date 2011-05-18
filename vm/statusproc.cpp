void __stdcall StatusProc(HINTERNET hInternet, DWORD dwContext,
							 DWORD dwInternetStatus,
							 LPVOID lpvStatusInformation,
							 DWORD dwStatusInformationLength)
{
	REQUEST_CONTEXT *cpContext;
	char szBuffer[512];
	cpContext= (REQUEST_CONTEXT*)dwContext;

	
	

	switch (dwInternetStatus)
	{
		case INTERNET_STATUS_CLOSING_CONNECTION:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: CLOSING_CONNECTION (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_CONNECTED_TO_SERVER:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: CONNECTED_TO_SERVER (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_CONNECTING_TO_SERVER:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: CONNECTING_TO_SERVER (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_CONNECTION_CLOSED:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: CONNECTION_CLOSED (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_HANDLE_CLOSING:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: HANDLE_CLOSING (%d)",
				cpContext->szMemo, dwStatusInformationLength);

			StringCchPrintf(cpContext->szMemo, 512, "Closed");
			
			//check if the both resource handles are closing
			//if so, enable the download button.
			if ((strcmp(rcContext1.szMemo,"Closed")) ||
				(strcmp(rcContext2.szMemo,"Closed")))
			{
				hButton = GetDlgItem(cpContext->hWindow, IDC_Download);
				EnableWindow(hButton,1);
			}
			break;
		case INTERNET_STATUS_HANDLE_CREATED:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: HANDLE_CREATED (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_INTERMEDIATE_RESPONSE:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: INTERMEDIATE_RESPONSE (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_NAME_RESOLVED:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: NAME_RESOLVED (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_RECEIVING_RESPONSE:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: RECEIVEING_RESPONSE (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_RESPONSE_RECEIVED:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: RESPONSE_RECEIVED (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_REDIRECT:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: REDIRECT (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_REQUEST_COMPLETE:

			//check for errors
			if (LPINTERNET_ASYNC_RESULT(lpvStatusInformation)->dwError == 0)
			{
				//check if the completed request is from AsyncDirect
				if (strcmp(cpContext->szMemo, "AsyncDirect"))
				{
					//set the resource handle to the HINTERNET handle
					//returned in the callback
					cpContext->hResource = HINTERNET(
						LPINTERNET_ASYNC_RESULT(lpvStatusInformation)->dwResult);

					//write the callback information to the buffer
					StringCchPrintf(szBuffer,512,"%s: REQUEST_COMPLETE (%d)",
						cpContext->szMemo, dwStatusInformationLength);

					//create a thread to handle the header and
					//resource download
					cpContext->hThread = CreateThread(NULL, 0,
						(LPTHREAD_START_ROUTINE)Threader,LPVOID(cpContext), 0,
						&cpContext->dwThreadID);

				}
				else
				{
					StringCchPrintf(szBuffer,512,"%s(%d): REQUEST_COMPLETE (%d)",
						cpContext->szMemo,
						cpContext->nURL, dwStatusInformationLength);
				}

			}
			else
			{
				StringCchPrintf(szBuffer,512,
					"%s: REQUEST_COMPLETE (%d) Error (%d) encountered",
					cpContext->szMemo, dwStatusInformationLength,
					GetLastError());
			}			
			break;
		case INTERNET_STATUS_REQUEST_SENT:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: REQUEST_SENT (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_RESOLVING_NAME:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: RESOLVING_NAME (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_SENDING_REQUEST:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: SENDING_REQUEST (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		case INTERNET_STATUS_STATE_CHANGE:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: STATE_CHANGE (%d)",
				cpContext->szMemo, dwStatusInformationLength);
			break;
		default:
			//write the callback information to the buffer
			StringCchPrintf(szBuffer,512,"%s: Unknown: Status %d Given", cpContext->szMemo, dwInternetStatus);
			break;
	}

	//add the callback information to the callback list box
	SendDlgItemMessage(cpContext->hWindow,IDC_CallbackList,
		LB_ADDSTRING,0,(LPARAM)szBuffer);
	
}
