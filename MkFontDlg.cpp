// MkFontDlg.cpp : implementation file
//
/********************************************
 history : 
         1.0  support GB2312 & ascII
         2.0  support GBK 
         3.0  support BIG need <big-five.txt> & <>
         3.1  修正16点阵以上字体BUG
********************************************/
    

#include "stdafx.h"
#include "hzk.h"
#include "MkFontDlg.h"
//#include "cdxCRot90DC.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMkFontDlg dialog

CMkFontDlg::CMkFontDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMkFontDlg::IDD, pParent)
	, m_nRotate(0)
{
	//{{AFX_DATA_INIT(CMkFontDlg)
	m_iwitdh = 12;
	m_iheight = 12;
	m_ichsel = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMkFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMkFontDlg)
	DDX_Text(pDX, IDC_WITDH, m_iwitdh);
	DDX_Text(pDX, IDC_HEIGHT, m_iheight);
	DDX_Radio(pDX, IDC_RADIO4, m_ichsel);
	//}}AFX_DATA_MAP
	DDX_CBIndex(pDX, IDC_COMBO_ROTATE, m_nRotate);
}

BEGIN_MESSAGE_MAP(CMkFontDlg, CDialog)
	//{{AFX_MSG_MAP(CMkFontDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_SELEFONT, OnBtSelefont)
	ON_BN_CLICKED(IDC_BT_CREATE, OnBtCreate)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_WITDH, OnChangeWitdh)
	ON_EN_CHANGE(IDC_HEIGHT, OnChangeHeight)
	ON_BN_CLICKED(IDC_BT_BROWS, OnBtBrows)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BT_LOCK, OnBtLock)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SP_WIDTH, OnOutofmemorySpWidth)
	ON_CBN_SELCHANGE(IDC_CB_FONT, OnSelchangeCbFont)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_WIDTH, OnDeltaposSpWidth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_HEIGHT, OnDeltaposSpHeight)
    ON_BN_CLICKED(IDC_RADIO5, OnRadio4)
    ON_BN_CLICKED(IDC_RADIO6, OnRadio4)
    ON_BN_CLICKED(IDC_RADIO7, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMkFontDlg message handlers
void CMkFontDlg::OnDestroy() 
{

	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	
	if( m_pSrcDC ) delete m_pSrcDC;
	if( m_pDstDC ) delete m_pDstDC;	
}

BYTE g_revtBits[256];

BOOL CMkFontDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CWnd * pt = this->GetDlgItem(IDC_CANVASE);
	m_pSrcDC = new CClientDC(pt);
	if(m_pSrcDC ==NULL)  return false;
	m_Srcdc.CreateCompatibleDC(m_pSrcDC);

	pt = this->GetDlgItem(IDC_PAINT);
	m_pDstDC = new CClientDC(pt);   //从pt所指定的窗口中获得dc的指针
	if(m_pDstDC ==NULL)  return false;
	m_Dstdc.CreateCompatibleDC(m_pDstDC);
	
	m_opcb_fon[0]=(CComboBox *)GetDlgItem(IDC_CB_FONT);
	m_opcb_fon[1]=(CComboBox *)GetDlgItem(IDC_CB_SIZE);

	::EnumFonts(m_pSrcDC->GetSafeHdc(),NULL,EnumFontsProc,(LPARAM)m_opcb_fon[0]);

	m_opcb_fon[0]->SetCurSel(m_opcb_fon[0]->FindString(0,"宋体") );


	pt = this->GetDlgItem(IDC_TXT_FILE);
    char pathname[512];
    GetModuleFileName(NULL,pathname,512);
    CString str = pathname;
    str = str.Left(str.ReverseFind('\\')+1);
    str += "HZK1212.FON";
	pt->SetWindowText(str);
	m_iftsize = 100;
	m_bLocked = true;	
	OnBtLock();
	CFont ft;
	ft.CreatePointFont(m_iftsize,"宋体");
	m_pSrcDC->SelectObject(&ft);
	// TODO: Add extra initialization here
	int id[2] = {IDC_SP_WIDTH,IDC_SP_HEIGHT};
	for(int i=0;i<2;i++)
	{
		CSpinButtonCtrl * pspin =(CSpinButtonCtrl *)GetDlgItem(id[i]);
		pspin->SetRange32(1,100);
		pspin->SetBase(0);
		pspin->SetPos(12);
	}

    m_opcb_fon[1]->SetCurSel(0);
    
    memset(g_revtBits, 0, 256);
    for(int r=0 ; r<256; r++)
    {
        for(int sft=0; sft<8;sft++)
        {
            BYTE t = (1<<sft) ;
            if( r & t )
            {
                g_revtBits[r] |=  (0x80>>sft);
            }
        }
    }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
#define MCOLOR(x)   RGB(color[x],colorB[x],color[x] )
#define ABS(x)  (x<0? -x:x)
void CMkFontDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		CRect r;
		CWnd * pw = GetDlgItem(IDC_CANVASE);
		pw->GetWindowRect(&r);
		r.OffsetRect(-r.left ,-r.top );
		m_pSrcDC->FillSolidRect(&r,RGB(255,255,255));
		
		pw = GetDlgItem(IDC_PAINT);
		pw->GetWindowRect(&r);
		r.OffsetRect(-r.left ,-r.top );
		m_pDstDC->FillSolidRect(&r,RGB(255,255,255));

        this->UpdateData();
        if( m_ichsel < 1)
            m_pSrcDC->TextOut(2,2,"R");
        else if( m_ichsel < 3)
		    m_pSrcDC->TextOut(2,2,"汉");
        else
            m_pSrcDC->TextOut(2,2,"漢");


		m_pDstDC->BitBlt(0,0,m_iwitdh + 2,m_iheight+ 2,m_pSrcDC,0,0,SRCCOPY);

		CPen open(PS_SOLID, 1, RGB(255,0,0));
		CPen * popenold = m_pDstDC->SelectObject(&open);
		m_pDstDC->MoveTo(1,1);
		m_pDstDC->LineTo(m_iwitdh+2,1);
		m_pDstDC->LineTo(m_iwitdh+2,m_iheight+2);
		m_pDstDC->LineTo(1,m_iheight+2);
		m_pDstDC->LineTo(1,1);
		CPen open2(PS_SOLID, 1, RGB(0,0,255));
		m_pDstDC->SelectObject(popenold);

		popenold = m_pSrcDC->SelectObject(&open2);
		LOGFONT  lft;
		CFont * pft = m_pSrcDC->GetCurrentFont( );
		if( pft == NULL ) return;
		CFont ft;
		pft->GetLogFont (&lft);
		int iw,ih;

		ih = lft.lfHeight != 0? ABS(lft.lfHeight):ABS(lft.lfWidth);
		iw = lft.lfWidth != 0? ABS(lft.lfWidth):ih;
		m_pSrcDC->MoveTo(1,1);
		m_pSrcDC->LineTo(iw+1,1);
		m_pSrcDC->LineTo(iw+1,ih +1);
		m_pSrcDC->LineTo(1,ih+1);
		m_pSrcDC->LineTo(1,1);

		m_pSrcDC->SelectObject(popenold);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMkFontDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMkFontDlg::OnBtSelefont() 
{
	// TODO: Add your control notification handler code here
	//CFontDialog ( LPLOGFONT lplfInitial = NULL, DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS, CDC* pdcPrinter = NULL, CWnd* pParentWnd = NULL );
	LOGFONT  lft;
	//lfHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	/*lft.lfHeight = 11;// -MulDiv(9, GetDeviceCaps(dc.m_hDC, DT_CHARSTREAM), 72);  //???
	lft.lfWidth = 0;
	lft.lfWeight  = FW_NORMAL;//粗细   FW_HEAVY;//
	lft.lfItalic = false;    //斜体
	lft.lfUnderline = false; //下划线
	lft.lfCharSet = GB2312_CHARSET; //字符集
	lft.lfStrikeOut = false;  //删除线
	strcpy(lft.lfFaceName,"宋体");*/
	
	CFont * pft = m_pSrcDC->GetCurrentFont( );
	if( pft == NULL ) return;
	CFont ft;
    pft->GetLogFont (&lft);

	CFontDialog fdlg(&lft,CF_EFFECTS | CF_SCREENFONTS, m_pSrcDC, this);
	if ( fdlg.DoModal() == IDOK )
	{
	    fdlg.GetCurrentFont( &lft );
		ft.CreateFontIndirect(&lft);
		m_pSrcDC->SelectObject(&ft);
		this->OnPaint();
	}
}

#define WORDSWAP(w)		(((w) >> 8) | \
						(((w) << 8) & 0xFF00))


WORD * wbig_gbk_table;

int ReadBig5ToGBK(WORD * table)
{
    FILE * fp = fopen("BIG5_GBK.dat","rb");
    if( fp == NULL) return 0;
    int i=0;
    while( !feof(fp) )
    {        
        WORD index , data;
        if( fread(&index,1,2,fp) != 2 ) break;
        if( fread(&data,1,2,fp) != 2 ) break;
        table[index] = data;
    }
    return 1;
}

WORD BIG5toGBK(WORD bigcode, char *txt)
{
    WORD GbkCode = wbig_gbk_table[bigcode];
    if( GbkCode != 0 )
    {
        GbkCode = WORDSWAP(GbkCode);
        memcpy(txt,&GbkCode,2);
        return 1;
    }
    else
    {
        txt[0] = (BYTE)0xa1;
        txt[1] = (BYTE)0x40;
    }
    return 0;
}


FILE * CMkFontDlg::GetFile()
{
	CWnd * pWnd = GetDlgItem(IDC_TXT_FILE);
	if ( !pWnd ) return NULL;
	CString strFile;
	pWnd->GetWindowText(strFile); 
    if( strFile.IsEmpty() ) return NULL;
	FILE * fp =  fopen((LPCTSTR) strFile, "w+b");

    return fp;
}

FILE * CMkFontDlg::GetListFile(FILE * fp)
{
	CWnd * pWnd = GetDlgItem(IDC_TXT_FILE);
	if ( !pWnd ) return NULL;
	CString strFile;
	pWnd->GetWindowText(strFile); 
    if( strFile.IsEmpty() ) return NULL;

    CString strlist = strFile;
    strlist = strlist.Left(strlist.ReverseFind('.')+1);
    strlist+="lst";            
    FILE * fplst = fopen((LPCTSTR) strlist,"w+b");
    if( !fplst ) 
    {
        fclose(fp);
    }
    return fplst;
}

//WORD spHz[] ={0, 0x66AE, 0X83E6, 0x6D8f};
const char  g_spHz[] ={"\0\0甪鎯弇吅囧玥骙鋆祐瀼灈嵖洧硃浉酂垕垱堽瀍堌硚喆"
                            "焗镕埼孖堃垵喺俵抦艸呎疍氹哋咁硡碁璟睏冇妳爿沛卐"};

WORD CMkFontDlg::GetNextHzCode(BYTE* hzcode, int coderange)
{
    switch(coderange)
    {
    case 2:  //GBK
        if( 1 )
        {
            INT nMaxChars = sizeof(g_spHz)/sizeof(WORD);
            WORD *  spHz = (WORD *)g_spHz;
            for(int i=0; i<nMaxChars; i++)
            {
                if( *(WORD*)hzcode == spHz[i] )
                {
                    if( (++i) >= nMaxChars )
                    {
                        return 0;
                    }
                    *(WORD*)hzcode = spHz[i];
                    return 1;
                }

            }
            return 0;
        }
        else
        {
            if(hzcode[0] ==0 || hzcode[1] ==0 )
            {
                hzcode[0] = 0x81 ; hzcode[1] = 0x40;
            }
            else
            {
                if( ++hzcode[1] == 0x7f )
                    ++hzcode[1];
                if( hzcode[1] == 0xff )
                {
                    if(hzcode[0] == 0xfE ) return 0;
                    hzcode[1] = 0x40;
                    ++hzcode[0];
                }
           }
        }
        break;
    case 1:  //GB2312
            if(hzcode[0] ==0 || hzcode[1] ==0 )
            {
                hzcode[0] = 0xa1 ; hzcode[1] = 0xa1;
            }
            else
            {
                if( ++hzcode[1] == 0xff )
                {
                    if(hzcode[0] == 0xf7 ) 
                        return 0;
                    hzcode[1]=0xa1;
                    ++hzcode[0];
                }
            }
        break;
    case 3:
            if( hzcode[0] ==0 || hzcode[1] ==0 )
            {
                hzcode[0] = 0xa1; hzcode[1] = 0x40;
            }
            else
            {
                if( ++hzcode[1] == 0x7f )
                    hzcode[1] = 0xa1; 
                if( hzcode[1] == 0xff )
                {
                    if(hzcode[0] == 0xf9 ) return 0;
                    hzcode[1] = 0x40;
                    ++hzcode[0];
                }
                if( hzcode[0] == 0xf9 )
                {
                    if( hzcode[1] = 0xd6) return 0;
                }
           }
            break;
    case 0: //ASC
            if( hzcode[0] == 0xff ) return 0;
            ++hzcode[0];
        break;
    default:
        return 0;
    }
    TRACE("\r\n%X,%X", hzcode[0],hzcode[1]);
    return 1;
}




void CMkFontDlg::RotateBits(BYTE * pbuf, int w, int wc, int h)
{
    int wb = (wc+7)/8;
    int nsize = wb * h ;

	switch (m_nRotate) {
	case ROTATE_0: {
		DWORD* pdw = (DWORD*)pbuf;
		int len = nsize / sizeof(DWORD);
		for (int i = 0; i < len; i++)
			pdw[i] = ~pdw[i];
		}
		break;
	case ROTATE_90:  break;
	case ROTATE_180: break;
	case ROTATE_270: break;
	case ROTATE_MIRROR_0:  break;
	case ROTATE_MIRROR_90:  break;
	case ROTATE_MIRROR_180: break;
	case ROTATE_MIRROR_270: break;

	}

    

}

void CMkFontDlg::OnBtCreate() 
{
	this->UpdateData();
	int iw = (m_iwitdh+7)&~7, ih = m_iheight;  //iw = bit_font width
    int iwbitmap = (m_iwitdh+15) &~15; //Bitmap aliagn with 16 bits!
    int nsize = iwbitmap * ih / 8;

    FILE * fp = GetFile();
    FILE * fplst = GetListFile(fp);
    if( fp == NULL || fplst == NULL ) return;

    LOGFONT  lft;
	CFont * pft = m_pSrcDC->GetCurrentFont( );
	if( pft == NULL ) return;
	pft->GetLogFont (&lft);
    int ish = lft.lfHeight != 0? ABS(lft.lfHeight):ABS(lft.lfWidth);
	int isw = lft.lfWidth != 0? ABS(lft.lfWidth):ish;


	CRect rsrc;
	CWnd * pw = GetDlgItem(IDC_CANVASE);
	pw->GetWindowRect(&rsrc);
	rsrc.OffsetRect(-rsrc.left ,-rsrc.top );

	CDC   	memDC;
	CWindowDC	dc(pw);
	char buf[100*100+8];
	CBitmap 	bitmap;
	bitmap.CreateBitmap(iw,ih,1,1,buf);
	memDC.CreateCompatibleDC(&dc);
	CBitmap*   pOldBitmap = memDC.SelectObject(&bitmap);
    
    BYTE hzcode[] = {0,0,0,0};
    WORD  code = GetNextHzCode(hzcode,m_ichsel);
    memDC.FillSolidRect(0,0,iw,ih,RGB(255,255,255));


    BYTE * bits = new BYTE[100*100+8]; 

    while(code)
    { 
        m_pSrcDC->FillSolidRect(&rsrc,RGB(255,255,255));  //clear last time
        m_pSrcDC->TextOut(1,1,hzcode); //Print text to left box, 
        memDC.BitBlt(0, 0, m_iwitdh+2,m_iheight, &dc, 1, 1, SRCCOPY); //Convert Print text to 1bit Gray CDC
        m_pDstDC->BitBlt(2,2,m_iwitdh+2,m_iheight,m_pSrcDC,0,0,SRCCOPY);//Print text to right box

        memset(bits,0xff,nsize);
        bitmap.GetBitmapBits(nsize,bits); //horizontal scan lines are multiples of 16 bits.
        
        RotateBits(bits, m_iwitdh, iw,  ih);

        if( iwbitmap - iw < 1)
            fwrite(bits,1,nsize,fp);
        else
        {
            BYTE * ptr = bits;
            for( int h=0;h<ih;h++)
            {
                fwrite(ptr,1,iw/8,fp);
                ptr += iwbitmap/8;
            }
        }
        
        if( fplst )
            fwrite(hzcode,1,2,fplst);
        code = GetNextHzCode(hzcode,m_ichsel);
    }



	fcloseall();
	memDC.SelectObject(pOldBitmap);
	delete[] bits;
	return;
}



BOOL WriteDIB( LPTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits	= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, GlobalSize(hDIB) );
	fcloseall();

	return TRUE;
}

BOOL WriteWindowToDIB( LPTSTR szFile, CWnd *pWnd )
{
	CRect		rect;
	pWnd->GetWindowRect(rect);  rect.right = rect.left + 16; rect.bottom = rect.top + 16;
    //用窗口区域大小定义一个内存DC ，并将窗口图像暂存其中 

	CBitmap 	bitmap;
	CWindowDC	dc(pWnd);
	CDC 		memDC;

	memDC.CreateCompatibleDC(&dc);

//  bitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height() );  
	char buf[64];
	bitmap.CreateBitmap(16,16,1,1,buf);

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc, 0, 0, SRCCOPY);

#if 1
	char ret[64];
	bitmap.GetBitmapBits(32,ret);
	memDC.SelectObject(pOldBitmap);
	return TRUE;
#else
	// 如果设备支持调色板，创建调色板
	CPalette pal;
	if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries =
			GetSystemPaletteEntries( dc, 0, 255, pLP->palPalEntry );

		// Create the palette
		pal.CreatePalette( pLP );

		delete[] pLP;
	}
	memDC.SelectObject(pOldBitmap);

	// 转换 bitmap 到 a DIB
	HANDLE hDIB = DDBToDIB( bitmap, BI_RGB, &pal );

	if( hDIB == NULL )
		return FALSE;

	// Write it to file
	WriteDIB( szFile, hDIB );

	// Free the memory allocated by DDBToDIB for the DIB
	GlobalFree( hDIB );
	return TRUE;
#endif
}

HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal )
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver
	// will calculate the biSizeImage field
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(NULL,hDC);
	return hDIB;
}

 

void CMkFontDlg::OnChangeWitdh() 
{
	this->UpdateData();
	if( this->m_iwitdh >= 100)
	{
		m_iwitdh /= 10;
		this->UpdateData(false);
		return;
	}
}


void CMkFontDlg::OnChangeHeight() 
{
	this->UpdateData();
	if( this->m_iheight >= 100)
	{
		m_iheight  /= 10;
		this->UpdateData(false);
		return;
	}
	
}

void CMkFontDlg::OnBtBrows() 
{
	CWnd * pw = GetDlgItem(IDC_TXT_FILE);
	CString str;
	pw->GetWindowText(str); 
	CFileDialog	fileDialog( false , (LPCTSTR)str , 	"*.*" , 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,
			"All Files(*.*)|*.*||" ) ; 

	if( fileDialog.DoModal() == IDOK )
	{
		CString	pathName	=fileDialog.GetPathName() ;
		pw->SetWindowText((LPCTSTR)pathName);
	}
}

void CMkFontDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
    OnPaint();	
}

void CMkFontDlg::OnBtLock() 
{
	// TODO: Add your control notification handler code here
	CButton * pbtn =(CButton * ) GetDlgItem(IDC_BT_LOCK);
	HICON hicon;
	if( !m_bLocked )
	{
		hicon=AfxGetApp()->LoadIcon(IDI_LOCKED);  //index = 0
		SetIcon(hicon, false);
		pbtn->SetIcon(hicon);
		m_bLocked = true;
	}
	else
	{
		hicon=AfxGetApp()->LoadIcon(IDI_UNLOCK);  //index = 0
		SetIcon(hicon, false);
		pbtn->SetIcon(hicon);
		m_bLocked = true;
	}
}

void CMkFontDlg::OnOutofmemorySpWidth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

int CMkFontDlg::EnumFontsProc(CONST LOGFONTA *lplf, CONST TEXTMETRICA *lptm,
							    DWORD dwType, LPARAM lpData)
{
	CComboBox * pt = (CComboBox * )lpData;
	pt->AddString (lplf->lfFaceName );
	return 1;
}

void CMkFontDlg::OnSelchangeCbFont() 
{
	CString str;
	((CComboBox *)GetDlgItem(IDC_CB_FONT))->GetWindowText(str);
	CFont ft;
	ft.CreatePointFont(m_iftsize,(LPCTSTR)str);
	m_pSrcDC->SelectObject(&ft);
	OnPaint();	
}

void CMkFontDlg::OnDeltaposSpWidth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMUPDOWN * pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData();	
	CSpinButtonCtrl * pspin =(CSpinButtonCtrl *)GetDlgItem(IDC_SP_WIDTH);
	int ipos = pspin->GetPos() ;
	ipos += pNMUpDown->iDelta;

	pspin->SetPos(ipos);	
	m_iwitdh = m_iwitdh + pNMUpDown->iDelta;
	if( m_iwitdh < 1 ) m_iwitdh = 1;
	if( m_iwitdh > 100 ) m_iwitdh = 100;

	UpdateData(false);	
 
	this->OnPaint();
	*pResult = 0;
}

void CMkFontDlg::OnDeltaposSpHeight(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData();	
	CSpinButtonCtrl * pspin =(CSpinButtonCtrl *)GetDlgItem(IDC_SP_HEIGHT);
	int ipos = pspin->GetPos() ;
	ipos += pNMUpDown->iDelta;
	pspin->SetPos(ipos);	
	m_iheight = m_iheight + pNMUpDown->iDelta;
	if( m_iheight < 1 ) m_iheight = 1;
	if( m_iheight > 100 ) m_iheight = 100;
	UpdateData(false);	
	this->OnPaint();
	
	*pResult = 0;
}

