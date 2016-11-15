// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;;
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->EmuKrnlAv.cpp
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2016 Patrick van Logchem <pvanlogchem@gmail.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#define _CXBXKRNL_INTERNAL
#define _XBOXKRNL_DEFEXTRN_

// prevent name collisions
namespace xboxkrnl
{
	#include <xboxkrnl/xboxkrnl.h> // For AvGetSavedDataAddress, etc.
};

#include "Logging.h" // For LOG_FUNC()
#include "Emu.h" // For EmuWarning()
#include "EmuAlloc.h" // For CxbxFree(), CxbxMalloc(), etc.

// Global Variable(s)
PVOID g_pPersistedData = NULL;

using namespace xboxkrnl;

// ******************************************************************
// * 0x0001 AvGetSavedDataAddress()
// ******************************************************************
XBSYSAPI EXPORTNUM(1) xboxkrnl::PVOID NTAPI xboxkrnl::AvGetSavedDataAddress()
{
	LOG_FUNC();

	__asm int 3;

	// Allocate a buffer the size of the screen buffer and return that.
	// TODO: Fill this buffer with the contents of the front buffer.
	// TODO: This isn't always the size we need...

	if (g_pPersistedData)
	{
		CxbxFree(g_pPersistedData);
		g_pPersistedData = NULL;
	}

	g_pPersistedData = CxbxMalloc(640 * 480 * 4);

#if 0
	// Get a copy of the front buffer
	IDirect3DSurface8* pFrontBuffer = NULL;

	if (SUCCEEDED(g_pD3DDevice8->GetFrontBuffer(pFrontBuffer)))
	{
		D3DLOCKED_RECT LockedRect;
		pFrontBuffer->LockRect(0, NULL, &LockedRect);

		CopyMemory(g_pPersistedData, LockRect.pBits, 640 * 480 * 4);

		pFrontBuffer->UnlockRect();
	}
#endif

	// TODO: We might want to return something sometime...
	/*if( !g_pPersistedData )
	{
	FILE* fp = fopen( "PersistedSurface.bin", "rb" );
	fseek( fp, 0, SEEK_END );
	long size = ftell( fp );
	g_pPersistedData = malloc( size );
	fread( g_pPersistedData, size, 1, fp );
	fclose(fp);
	}*/

	return NULL;//g_pPersistedData;
}

// ******************************************************************
// * 0x0002 AvSendTVEncoderOption()
// ******************************************************************
XBSYSAPI EXPORTNUM(2) VOID NTAPI xboxkrnl::AvSendTVEncoderOption
(
	IN  PVOID   RegisterBase,
	IN  ULONG   Option,
	IN  ULONG   Param,
	OUT ULONG   *Result
)
{
	LOG_FUNC_BEGIN
		LOG_FUNC_ARG(RegisterBase)
		LOG_FUNC_ARG(Option)
		LOG_FUNC_ARG(Param)
		LOG_FUNC_ARG_OUT(Result)
		LOG_FUNC_END;

	// TODO: What does this do?

	EmuWarning("AvSendTVEncoderOption ignored!");
}

