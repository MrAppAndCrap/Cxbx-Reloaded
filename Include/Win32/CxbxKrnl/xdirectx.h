// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->xdirectx.h
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
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef XDIRECTX_H
#define XDIRECTX_H

#include <d3d8.h>
#include <d3dx8tex.h>
#include <dsound.h>
#include <windows.h>

#include "Emu.h"

// Todo: Fill out this enumeration table for convienance
typedef DWORD X_D3DFORMAT;

/**
// Oops: Well, heres PC->Xbox if you ever need it... :]
// ******************************************************************
// * Convert from PC D3D to Xbox D3D enumeration
// ******************************************************************
// TODO: XDK-Specific Tables? So far they are the same
if((uint32)State < 4)
    State = (D3DTRANSFORMSTATETYPE)(State - 2);
else if((uint32)State < 20)
    State = (D3DTRANSFORMSTATETYPE)(State - 14);
else if((uint32)State > 255)
    State = (D3DTRANSFORMSTATETYPE)(State - 250);
else
    EmuCleanup("Unknown Transform State Type (%d)", State);
*/

// ******************************************************************
// * func: EmuXB2PC_D3DTS
// ******************************************************************
inline D3DTRANSFORMSTATETYPE EmuXB2PC_D3DTS(D3DTRANSFORMSTATETYPE State)
{
    if((uint32)State < 2)
        return (D3DTRANSFORMSTATETYPE)(State + 2);
    else if((uint32)State < 6)
        return (D3DTRANSFORMSTATETYPE)(State + 14);
    else if((uint32)State < 10)
        return D3DTS_WORLDMATRIX(State-6);

    EmuCleanup("Unknown Transform State Type (%d)", State);

    return State;
}

// Todo: Fill out this enumeration tabel for convienance
typedef DWORD X_D3DBLENDOP;

// ******************************************************************
// * func: EmuXB2PC_D3DBLENDOP
// ******************************************************************
inline D3DBLENDOP EmuXB2PC_D3DBLENDOP(X_D3DBLENDOP Value)
{
    switch(Value)
    {
        case 0x8006:
            return D3DBLENDOP_ADD;
    }

    EmuCleanup("Unknown D3DBLENDOP (0x%.08X)", Value);

    return (D3DBLENDOP)Value;
}

// Todo: Fill out this enumeration table for convienance
typedef DWORD X_D3DBLEND;

// ******************************************************************
// * func: EmuXB2PC_D3DBLEND
// ******************************************************************
inline D3DBLEND EmuXB2PC_D3DBLEND(X_D3DBLEND Value)
{
    if(Value < 2)
        return (D3DBLEND)(Value + 1);
    else if(Value < 0x309)
        return (D3DBLEND)((Value & 0xF) + 3);

    EmuCleanup("Unknown Xbox D3DBLEND Extension (0x%.08X)", Value);

    return (D3DBLEND)Value;
}

// Todo: Fill out this enumeration table for convienance
typedef DWORD X_D3DCMPFUNC;

// ******************************************************************
// * func: EmuXB2PC_D3DCMPFUNC
// ******************************************************************
inline D3DCMPFUNC EmuXB2PC_D3DCMPFUNC(X_D3DCMPFUNC Value)
{
    return (D3DCMPFUNC)((Value & 0xF) + 1);
}

// Todo: Fill out this enumeration table for convienance
typedef DWORD X_D3DFILLMODE;

// ******************************************************************
// * func: EmuXB2PC_D3DFILLMODE
// ******************************************************************
inline D3DFILLMODE EmuXB2PC_D3DFILLMODE(X_D3DFILLMODE Value)
{
    return (D3DFILLMODE)((Value & 0xF) + 1);
}

// ******************************************************************
// * func: EmuXB2PC_D3DFormat
// ******************************************************************
inline D3DFORMAT EmuXB2PC_D3DFormat(X_D3DFORMAT Format)
{
    switch(Format)
    {
        case 0:
            return (D3DFORMAT)NULL;

        case 0x04: // Swizzled   (X_D3DFMT_A4R4G4B4)
            return D3DFMT_A4R4G4B4;

        case 0x11: // Linear     (X_D3DFMT_LIN_R5G6B5)
        case 0x05: // Swizzled   (X_D3DFMT_R5G6B5)
            return D3DFMT_R5G6B5;

        case 0x12: // Linear     (X_D3DFMT_LIN_A8R8G8B8)
        case 0x06: // Swizzled   (X_D3DFMT_A8R8G8B8)
            return D3DFMT_A8R8G8B8;

        case 0x07: // Swizzled   (X_D3DFMT_X8R8G8B8)
            return D3DFMT_X8R8G8B8;

        case 0x0C: // Compressed (X_D3DFMT_DXT1)
            return D3DFMT_DXT1;

        case 0x0E: // Compressed (X_D3DFMT_DXT2)
            return D3DFMT_DXT2;

        case 0x0F: // Compressed (X_D3DFMT_DXT3)
            return D3DFMT_DXT3;

        case 0x2E: // Linear     (X_D3DFMT_LIN_D24S8)
        case 0x2A: // Swizzled   (X_D3DFMT_D24S8)
            return D3DFMT_D24S8;

        case 0x30: // Linear     (X_D3DFMT_LIN_D16)
        case 0x2C: // Swizzled   (X_D3DFMT_D16)
            return D3DFMT_D16;
    }

    EmuCleanup("EmuXB2PC_D3DFormat: Unknown Format (0x%.08X)", Format);

    return (D3DFORMAT)Format;
}

// ******************************************************************
// * func: EmuPC2XB_D3DFormat
// ******************************************************************
inline X_D3DFORMAT EmuPC2XB_D3DFormat(D3DFORMAT Format)
{
    switch(Format)
    {
        case D3DFMT_R5G6B5:
            return 0x05;
        case D3DFMT_D24S8:
            return 0x2A;
        case D3DFMT_X8R8G8B8:
            return 0x07;
        case D3DFMT_A8R8G8B8:
            return 0x06;
    }

    EmuCleanup("EmuPC2XB_D3DFormat: Unknown Format (%d)", Format);

    return Format;
}

// ******************************************************************
// * X_D3DRESOURCETYPE
// ******************************************************************
// NOTE: HACK: These enumerations are not equivalent when > 7!
typedef D3DRESOURCETYPE X_D3DRESOURCETYPE;

// ******************************************************************
// * X_D3DDISPLAYMODE
// ******************************************************************
typedef struct _X_D3DDISPLAYMODE
{
    UINT        Width;
    UINT        Height;
    UINT        RefreshRate;
    DWORD       Flags;
    X_D3DFORMAT Format;
}
X_D3DDISPLAYMODE;

// ******************************************************************
// * X_D3DSURFACEDESC
// ******************************************************************
typedef struct _X_D3DSURFACE_DESC
{
    X_D3DFORMAT         Format;
    X_D3DRESOURCETYPE   Type;
    DWORD               Usage;
    UINT                Size;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT                Width;
    UINT                Height;
}
X_D3DSURFACE_DESC;

// ******************************************************************
// * X_D3DPRESENT_PARAMETERS
// ******************************************************************
typedef struct _X_D3DPRESENT_PARAMETERS
{
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    X_D3DFORMAT         BackBufferFormat;
    UINT                BackBufferCount;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    D3DSWAPEFFECT       SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    X_D3DFORMAT         AutoDepthStencilFormat;
    DWORD               Flags;
    UINT                FullScreen_RefreshRateInHz; 
    UINT                FullScreen_PresentationInterval;
    IDirect3DSurface8  *BufferSurfaces[3];
    IDirect3DSurface8  *DepthStencilSurface;
}
X_D3DPRESENT_PARAMETERS;

// ******************************************************************
// * X_D3DVertexShader
// ******************************************************************
struct X_D3DVertexShader
{
    union
    {
        DWORD   UnknownA;
        DWORD   Handle;
    };

    DWORD UnknownB;
    DWORD Flags;
    DWORD UnknownC[0x59];
};

// ******************************************************************
// * D3DResource "Common" Masks
// ******************************************************************
#define X_D3DCOMMON_REFCOUNT_MASK      0x0000FFFF

#define X_D3DCOMMON_TYPE_MASK          0x00070000
#define X_D3DCOMMON_TYPE_SHIFT         16
#define X_D3DCOMMON_TYPE_VERTEXBUFFER  0x00000000
#define X_D3DCOMMON_TYPE_INDEXBUFFER   0x00010000
#define X_D3DCOMMON_TYPE_PUSHBUFFER    0x00020000
#define X_D3DCOMMON_TYPE_PALETTE       0x00030000
#define X_D3DCOMMON_TYPE_TEXTURE       0x00040000
#define X_D3DCOMMON_TYPE_SURFACE       0x00050000
#define X_D3DCOMMON_TYPE_FIXUP         0x00060000

#define X_D3DCOMMON_INTREFCOUNT_MASK   0x00780000
#define X_D3DCOMMON_INTREFCOUNT_SHIFT  19

#define X_D3DCOMMON_D3DCREATED         0x01000000

#define X_D3DCOMMON_UNUSED_MASK        0xFE000000
#define X_D3DCOMMON_UNUSED_SHIFT       25

// ******************************************************************
// * D3DTexture "Size" Masks
// ******************************************************************
#define X_D3DSIZE_WIDTH_MASK              0x00000FFF   // Width  (Texels - 1)
#define X_D3DSIZE_HEIGHT_MASK             0x00FFF000   // Height (Texels - 1)
#define X_D3DSIZE_HEIGHT_SHIFT            12
#define X_D3DSIZE_PITCH_MASK              0xFF000000   // Pitch / 64 - 1
#define X_D3DSIZE_PITCH_SHIFT             24

// ******************************************************************
// * X_D3DResource
// ******************************************************************
struct X_D3DResource
{
    DWORD Common;
    DWORD Data;

    union
    {
        DWORD                   Lock;
        IDirect3DResource8     *EmuResource8;
        IDirect3DBaseTexture8  *EmuBaseTexture8;
        IDirect3DTexture8      *EmuTexture8;
        IDirect3DSurface8      *EmuSurface8;
        IDirect3DVertexBuffer8 *EmuVertexBuffer8;
        IDirect3DIndexBuffer8  *EmuIndexBuffer8;
    };
};

// ******************************************************************
// * X_D3DVertexBuffer
// ******************************************************************
struct X_D3DVertexBuffer : public X_D3DResource
{

};

// ******************************************************************
// * X_D3DIndexBuffer
// ******************************************************************
struct X_D3DIndexBuffer : public X_D3DResource
{

};

// ******************************************************************
// * X_D3DPixelContainer "Format" Masks
// ******************************************************************
#define X_D3DFORMAT_RESERVED1_MASK        0x00000003      // Must be zero
                                        
#define X_D3DFORMAT_DMACHANNEL_MASK       0x00000003
#define X_D3DFORMAT_DMACHANNEL_A          0x00000001      // DMA channel A - the default for all system memory
#define X_D3DFORMAT_DMACHANNEL_B          0x00000002      // DMA channel B - unused
#define X_D3DFORMAT_CUBEMAP               0x00000004      // Set if the texture if a cube map
#define X_D3DFORMAT_BORDERSOURCE_COLOR    0x00000008
#define X_D3DFORMAT_DIMENSION_MASK        0x000000F0      // # of dimensions
#define X_D3DFORMAT_DIMENSION_SHIFT       4
#define X_D3DFORMAT_FORMAT_MASK           0x0000FF00
#define X_D3DFORMAT_FORMAT_SHIFT          8
#define X_D3DFORMAT_MIPMAP_MASK           0x000F0000 
#define X_D3DFORMAT_MIPMAP_SHIFT          16
#define X_D3DFORMAT_USIZE_MASK            0x00F00000      // Log 2 of the U size of the base texture
#define X_D3DFORMAT_USIZE_SHIFT           20
#define X_D3DFORMAT_VSIZE_MASK            0x0F000000      // Log 2 of the V size of the base texture
#define X_D3DFORMAT_VSIZE_SHIFT           24
#define X_D3DFORMAT_PSIZE_MASK            0xF0000000      // Log 2 of the P size of the base texture
#define X_D3DFORMAT_PSIZE_SHIFT           28

// ******************************************************************
// * X_D3DPixelContainer
// ******************************************************************
struct X_D3DPixelContainer : public X_D3DResource
{
    X_D3DFORMAT Format;
    DWORD       Size;
};

// ******************************************************************
// * X_D3DBaseTexture
// ******************************************************************
struct X_D3DBaseTexture : public X_D3DPixelContainer
{

};

// ******************************************************************
// * X_D3DTexture
// ******************************************************************
struct X_D3DTexture : public X_D3DBaseTexture
{

};

// ******************************************************************
// * X_D3DSurface
// ******************************************************************
struct X_D3DSurface : public X_D3DPixelContainer
{

};

// ******************************************************************
// * X_D3DTILE
// ******************************************************************
struct X_D3DTILE
{
    DWORD   Flags;
    PVOID   pMemory;
    DWORD   Size;
    DWORD   Pitch;
    DWORD   ZStartTag;
    DWORD   ZOffset;
};

// Todo: Fill out this enumeration table for convienance
typedef DWORD X_D3DPRIMITIVETYPE;

// ******************************************************************
// * EmuD3DVertexToPrimitive
// ******************************************************************
extern UINT EmuD3DVertexToPrimitive[11][2];

// ******************************************************************
// * D3DVertexToPrimitiveCount
// ******************************************************************
#define EmuD3DVertex2PrimitiveCount(PrimitiveType, VertexCount)    \
	(((VertexCount)-EmuD3DVertexToPrimitive[PrimitiveType][1])/EmuD3DVertexToPrimitive[PrimitiveType][0])

// ******************************************************************
// * EmuD3DRenderStateSimpleEncoded
// ******************************************************************
#define X_D3DRSSE_UNK 0x7fffffff
extern CONST DWORD EmuD3DRenderStateSimpleEncoded[174];

// ******************************************************************
// * EmuD3DTileCache (8 Tiles Max)
// ******************************************************************
extern X_D3DTILE EmuD3DTileCache[0x08];

// ******************************************************************
// * EmuD3DDeferredRenderState
// ******************************************************************
#define X_D3DRS_UNK 0x7fffffff
extern DWORD *EmuD3DDeferredRenderState;

// ******************************************************************
// * EmuD3DDeferredTextureState
// ******************************************************************
#define X_D3DTSS_UNK 0x7fffffff
extern DWORD *EmuD3DDeferredTextureState;

// ******************************************************************
// * EmuPrimitiveType
// ******************************************************************
extern D3DPRIMITIVETYPE EmuPrimitiveTypeLookup[];

// ******************************************************************
// * EmuPrimitiveType
// ******************************************************************
static inline D3DPRIMITIVETYPE EmuPrimitiveType(X_D3DPRIMITIVETYPE PrimitiveType)
{
    if((DWORD)PrimitiveType == 0x7FFFFFFF)
        return D3DPT_FORCE_DWORD;

    return EmuPrimitiveTypeLookup[PrimitiveType];
}

// ******************************************************************
// * func: EmuIDirect3D8_CreateDevice
// ******************************************************************
HRESULT WINAPI EmuIDirect3D8_CreateDevice
(
    UINT                        Adapter,
    D3DDEVTYPE                  DeviceType,
    HWND                        hFocusWindow,
    DWORD                       BehaviorFlags,
    X_D3DPRESENT_PARAMETERS    *pPresentationParameters,
    IDirect3DDevice8          **ppReturnedDeviceInterface
);

// ******************************************************************
// * func: EmuIDirect3D8_GetAdapterModeCount
// ******************************************************************
UINT WINAPI EmuIDirect3D8_GetAdapterModeCount
(
    UINT                        Adapter
);

// ******************************************************************
// * func: EmuIDirect3D8_GetAdapterDisplayMode
// ******************************************************************
HRESULT WINAPI EmuIDirect3D8_GetAdapterDisplayMode
(
    UINT                        Adapter,
    X_D3DDISPLAYMODE           *pMode
);

// ******************************************************************
// * func: EmuIDirect3D8_EnumAdapterModes
// ******************************************************************
HRESULT WINAPI EmuIDirect3D8_EnumAdapterModes
(
    UINT                        Adapter,
    UINT                        Mode,
    X_D3DDISPLAYMODE           *pMode
);

// ******************************************************************
// * func: EmuIDirect3D8_KickOffAndWaitForIdle
// ******************************************************************
VOID WINAPI EmuIDirect3D8_KickOffAndWaitForIdle();

// ******************************************************************
// * func: EmuIDirect3DDevice8_CopyRects
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CopyRects
(
    X_D3DSurface       *pSourceSurface,
    CONST RECT         *pSourceRectsArray,
    UINT                cRects,
    X_D3DSurface       *pDestinationSurface,
    CONST POINT        *pDestPointsArray
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateImageSurface
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CreateImageSurface
(
    UINT                Width,
    UINT                Height,
    X_D3DFORMAT         Format,
    X_D3DSurface      **ppBackBuffer
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetBackBuffer2
// ******************************************************************
X_D3DSurface* WINAPI EmuIDirect3DDevice8_GetBackBuffer2
(
    INT                 BackBuffer
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetBackBuffer
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_GetBackBuffer
(
    INT                 BackBuffer,
    D3DBACKBUFFER_TYPE  Type,
    X_D3DSurface      **ppBackBuffer
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetRenderTarget
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_GetRenderTarget
(
    X_D3DSurface  **ppRenderTarget
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetRenderTarget
// ******************************************************************
X_D3DSurface * WINAPI EmuIDirect3DDevice8_GetRenderTarget2();

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetDepthStencilSurface
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_GetDepthStencilSurface
(
    X_D3DSurface  **ppZStencilSurface
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetDepthStencilSurface
// ******************************************************************
X_D3DSurface * WINAPI EmuIDirect3DDevice8_GetDepthStencilSurface2();

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetTile
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_GetTile
(
    DWORD           Index,
    X_D3DTILE      *pTile
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetTileNoWait
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetTileNoWait
(
    DWORD               Index,
    CONST X_D3DTILE    *pTile
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateVertexShader
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CreateVertexShader
(
    CONST DWORD    *pDeclaration,
    CONST DWORD    *pFunction,
    DWORD          *pHandle,
    DWORD           Usage
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetVertexShaderConstant
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetVertexShaderConstant
(
    INT         Register,
    CONST PVOID pConstantData,
    DWORD       ConstantCount
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreatePixelShader
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CreatePixelShader
(
    CONST DWORD    *pFunction,
    DWORD          *pHandle
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetPixelShader
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetPixelShader
(
    DWORD           Handle
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateTexture2
// ******************************************************************
X_D3DResource * WINAPI EmuIDirect3DDevice8_CreateTexture2
(
    UINT                Width,
    UINT                Height,
    UINT                Depth,
    UINT                Levels,
    DWORD               Usage,
    D3DFORMAT           Format,
    D3DRESOURCETYPE     D3DResource
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateTexture
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CreateTexture
(
    UINT                Width,
    UINT                Height,
    UINT                Levels,
    DWORD               Usage,
    D3DFORMAT           Format,
    D3DPOOL             Pool,
    X_D3DResource     **ppTexture
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetIndices
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetIndices
(
    X_D3DIndexBuffer   *pIndexData,
    UINT                BaseVertexIndex
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetTexture
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetTexture
(
    DWORD           Stage,
    X_D3DResource  *pTexture
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SwitchTexture
// ******************************************************************
VOID __fastcall EmuIDirect3DDevice8_SwitchTexture
(
    DWORD           Method,
    DWORD           Data,
    DWORD           Format
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetDisplayMode
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_GetDisplayMode
(
    X_D3DDISPLAYMODE         *pMode
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_Clear
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_Clear
(
    DWORD                  Count,
    CONST D3DRECT         *pRects,
    DWORD                  Flags,
    D3DCOLOR               Color,
    float                  Z,
    DWORD                  Stencil
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_Present
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_Present
(
    CONST RECT* pSourceRect,
    CONST RECT* pDestRect,
    PVOID       pDummy1,
    PVOID       pDummy2
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_Swap
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_Swap
(
    DWORD Flags
);

// ******************************************************************
// * func: EmuIDirect3DResource8_Register
// ******************************************************************
HRESULT WINAPI EmuIDirect3DResource8_Register
(
    X_D3DResource      *pThis,
    PVOID               pBase
);

// ******************************************************************
// * func: EmuIDirect3DResource8_Release
// ******************************************************************
ULONG WINAPI EmuIDirect3DResource8_Release
(
    X_D3DResource      *pThis
);

// ******************************************************************
// * func: EmuIDirect3DResource8_IsBusy
// ******************************************************************
BOOL WINAPI EmuIDirect3DResource8_IsBusy
(
    X_D3DResource      *pThis
);

// ******************************************************************
// * func: EmuGet2DSurfaceDesc
// ******************************************************************
VOID WINAPI EmuGet2DSurfaceDesc
(
    X_D3DPixelContainer *pPixelContainer,
    DWORD                dwLevel,
    X_D3DSURFACE_DESC   *pDesc
);

// ******************************************************************
// * func: EmuIDirect3DSurface8_GetDesc
// ******************************************************************
HRESULT WINAPI EmuIDirect3DSurface8_GetDesc
(
    X_D3DResource      *pThis,
    X_D3DSURFACE_DESC  *pDesc
);

// ******************************************************************
// * func: EmuIDirect3DSurface8_LockRect
// ******************************************************************
HRESULT WINAPI EmuIDirect3DSurface8_LockRect
(
    X_D3DResource  *pThis,
    D3DLOCKED_RECT *pLockedRect,
    CONST RECT     *pRect,
    DWORD           Flags
);

// ******************************************************************
// * func: EmuIDirect3DBaseTexture8_GetLevelCount
// ******************************************************************
HRESULT WINAPI EmuIDirect3DBaseTexture8_GetLevelCount
(
    X_D3DBaseTexture   *pThis
);

// ******************************************************************
// * func: EmuIDirect3DTexture8_GetSurfaceLevel
// ******************************************************************
X_D3DResource * WINAPI EmuIDirect3DTexture8_GetSurfaceLevel2
(
    X_D3DTexture   *pThis,
    UINT            Level
);

// ******************************************************************
// * func: EmuIDirect3DTexture8_LockRect
// ******************************************************************
HRESULT WINAPI EmuIDirect3DTexture8_LockRect
(
    X_D3DTexture   *pThis,
    UINT            Level,
    D3DLOCKED_RECT *pLockedRect,
    CONST RECT     *pRect,
    DWORD           Flags
);

// ******************************************************************
// * func: EmuIDirect3DTexture8_GetSurfaceLevel
// ******************************************************************
HRESULT WINAPI EmuIDirect3DTexture8_GetSurfaceLevel
(
    X_D3DTexture   *pThis,
    UINT            Level,
    X_D3DSurface  **ppSurfaceLevel
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateVertexBuffer
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_CreateVertexBuffer
(
    UINT                Length,
    DWORD               Usage,
    DWORD               FVF,
    D3DPOOL             Pool,
    X_D3DVertexBuffer **ppVertexBuffer
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_CreateVertexBuffer
// ******************************************************************
X_D3DVertexBuffer* WINAPI EmuIDirect3DDevice8_CreateVertexBuffer2
(
    UINT Length
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetTextureState_TexCoordIndex
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetTextureState_TexCoordIndex
(
    DWORD Stage,
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_NormalizeNormals
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_NormalizeNormals
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_TextureFactor
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_TextureFactor
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_ZBias
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_ZBias
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_EdgeAntiAlias
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_EdgeAntiAlias
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_FillMode
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_FillMode
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_FogColor
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_FogColor
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_Dxt1NoiseEnable
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_Dxt1NoiseEnable
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_Simple
// ******************************************************************
VOID __fastcall EmuIDirect3DDevice8_SetRenderState_Simple
(
    DWORD Method,
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_CullMode
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_CullMode
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_ZEnable
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_ZEnable
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_StencilEnable
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_StencilEnable
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetRenderState_MultiSampleAntiAlias
(
    DWORD Value
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetTransform
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_SetTransform
(
    D3DTRANSFORMSTATETYPE State,
    CONST D3DMATRIX      *pMatrix
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_GetTransform
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_GetTransform
(
    D3DTRANSFORMSTATETYPE State,
    D3DMATRIX            *pMatrix
);

// ******************************************************************
// * func: EmuIDirect3DVertexBuffer8_Lock
// ******************************************************************
VOID WINAPI EmuIDirect3DVertexBuffer8_Lock
(
    X_D3DVertexBuffer   *ppVertexBuffer,
    UINT                OffsetToLock,
    UINT                SizeToLock,
    BYTE              **ppbData,
    DWORD               Flags
);

// ******************************************************************
// * func: EmuIDirect3DVertexBuffer8_Lock2
// ******************************************************************
BYTE* WINAPI EmuIDirect3DVertexBuffer8_Lock2
(
    X_D3DVertexBuffer  *ppVertexBuffer,
    DWORD               Flags
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetStreamSource
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetStreamSource
(
    UINT                StreamNumber,
    X_D3DVertexBuffer  *pStreamData,
    UINT                Stride
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetVertexShader
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetVertexShader
(
    DWORD            Handle
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_DrawVertices
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_DrawVertices
(
    X_D3DPRIMITIVETYPE  PrimitiveType,
    UINT                StartVertex,
    UINT                VertexCount
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_DrawVerticesUP
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_DrawVerticesUP
(
    X_D3DPRIMITIVETYPE  PrimitiveType,
    UINT                VertexCount,
    CONST PVOID         pVertexStreamZeroData,
    UINT                VertexStreamZeroStride
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_DrawIndexedVertices
// ******************************************************************
VOID WINAPI EmuIDirect3DDevice8_DrawIndexedVertices
(
    X_D3DPRIMITIVETYPE  PrimitiveType,
    UINT                VertexCount,
    CONST PWORD         pIndexData
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetLight
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetLight
(
    DWORD            Index,
    CONST D3DLIGHT8 *pLight
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_SetMaterial
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_SetMaterial
(
    CONST D3DMATERIAL8 *pMaterial
);

// ******************************************************************
// * func: EmuIDirect3DDevice8_LightEnable
// ******************************************************************
HRESULT WINAPI EmuIDirect3DDevice8_LightEnable
(
    DWORD            Index,
    BOOL             bEnable
);

// ******************************************************************
// * func: EmuDirectSoundCreate
// ******************************************************************
HRESULT WINAPI EmuDirectSoundCreate
(
    LPVOID          pguidDeviceId,
    LPDIRECTSOUND8 *ppDirectSound,
    LPUNKNOWN       pUnknown
);

// ******************************************************************
// * func: EmuIDirectSound8_CreateSoundBuffer
// ******************************************************************
HRESULT WINAPI EmuIDirectSound8_CreateSoundBuffer
(
    LPDIRECTSOUND8       pThis,
    LPCDSBUFFERDESC      pdsbd,
    LPDIRECTSOUNDBUFFER *ppBuffer,
    LPUNKNOWN            pUnkOuter
);

// ******************************************************************
// * func: EmuIDirectSoundBuffer8_SetBufferData
// ******************************************************************
HRESULT WINAPI EmuIDirectSoundBuffer8_SetBufferData
(
    LPDIRECTSOUNDBUFFER8    pThis,
    LPVOID                  pvBufferData,
    DWORD                   dwBufferBytes
);

// ******************************************************************
// * func: EmuIDirectSoundBuffer8_SetPlayRegion
// ******************************************************************
HRESULT WINAPI EmuIDirectSoundBuffer8_SetPlayRegion
(
    LPDIRECTSOUNDBUFFER8    pThis,
    DWORD                   dwPlayStart,
    DWORD                   dwPlayLength
);

// ******************************************************************
// * func: EmuIDirectSoundBuffer8_SetLoopRegion
// ******************************************************************
HRESULT WINAPI EmuIDirectSoundBuffer8_SetLoopRegion
(
    LPDIRECTSOUNDBUFFER8    pThis,
    DWORD                   dwLoopStart,
    DWORD                   dwLoopLength
);

#endif