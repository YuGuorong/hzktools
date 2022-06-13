/***********************************************************************
*  字库分析软件
*  定义字库的行列和文件名即可
*  original ，Yu Guorong
************************************************************************/
// hzkView.cpp : implementation of the CHzkView class
//

#include "stdafx.h"
#include "hzk.h"
#include "DlgInput.h"


#include "hzkDoc.h"
#include "hzkView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TMR_ID_PAINT_REFRESH   3473
//用户所定

#define CIRCUMGYRATE    //定义旋转270度  
//#define INVERTBIT		//定义反色
//#define BYTEONE_TO_TWO	//定义1bit象素变为2bit

//int nCharWidth =   16;
//int nCharHight =   12;
//char g_FileName[1024]={"hzk12"};

int nCharWidth =   16;
int nCharHight =   12;
char g_FileName[1024]={"HZK1212.FON"};

const unsigned short g_iOneBit2TwoBitMap[256] =
{
    0x0000, 0x0003, 0x000C, 0x000F, 0x0030, 0x0033, 0x003C, 0x003F, 
    0x00C0, 0x00C3, 0x00CC, 0x00CF, 0x00F0, 0x00F3, 0x00FC, 0x00FF, 
    0x0300, 0x0303, 0x030C, 0x030F, 0x0330, 0x0333, 0x033C, 0x033F, 
    0x03C0, 0x03C3, 0x03CC, 0x03CF, 0x03F0, 0x03F3, 0x03FC, 0x03FF, 
    0x0C00, 0x0C03, 0x0C0C, 0x0C0F, 0x0C30, 0x0C33, 0x0C3C, 0x0C3F, 
    0x0CC0, 0x0CC3, 0x0CCC, 0x0CCF, 0x0CF0, 0x0CF3, 0x0CFC, 0x0CFF, 
    0x0F00, 0x0F03, 0x0F0C, 0x0F0F, 0x0F30, 0x0F33, 0x0F3C, 0x0F3F, 
    0x0FC0, 0x0FC3, 0x0FCC, 0x0FCF, 0x0FF0, 0x0FF3, 0x0FFC, 0x0FFF, 
    0x3000, 0x3003, 0x300C, 0x300F, 0x3030, 0x3033, 0x303C, 0x303F, 
    0x30C0, 0x30C3, 0x30CC, 0x30CF, 0x30F0, 0x30F3, 0x30FC, 0x30FF, 
    0x3300, 0x3303, 0x330C, 0x330F, 0x3330, 0x3333, 0x333C, 0x333F, 
    0x33C0, 0x33C3, 0x33CC, 0x33CF, 0x33F0, 0x33F3, 0x33FC, 0x33FF, 
    0x3C00, 0x3C03, 0x3C0C, 0x3C0F, 0x3C30, 0x3C33, 0x3C3C, 0x3C3F, 
    0x3CC0, 0x3CC3, 0x3CCC, 0x3CCF, 0x3CF0, 0x3CF3, 0x3CFC, 0x3CFF, 
    0x3F00, 0x3F03, 0x3F0C, 0x3F0F, 0x3F30, 0x3F33, 0x3F3C, 0x3F3F, 
    0x3FC0, 0x3FC3, 0x3FCC, 0x3FCF, 0x3FF0, 0x3FF3, 0x3FFC, 0x3FFF, 
    0xC000, 0xC003, 0xC00C, 0xC00F, 0xC030, 0xC033, 0xC03C, 0xC03F, 
    0xC0C0, 0xC0C3, 0xC0CC, 0xC0CF, 0xC0F0, 0xC0F3, 0xC0FC, 0xC0FF, 
    0xC300, 0xC303, 0xC30C, 0xC30F, 0xC330, 0xC333, 0xC33C, 0xC33F, 
    0xC3C0, 0xC3C3, 0xC3CC, 0xC3CF, 0xC3F0, 0xC3F3, 0xC3FC, 0xC3FF, 
    0xCC00, 0xCC03, 0xCC0C, 0xCC0F, 0xCC30, 0xCC33, 0xCC3C, 0xCC3F, 
    0xCCC0, 0xCCC3, 0xCCCC, 0xCCCF, 0xCCF0, 0xCCF3, 0xCCFC, 0xCCFF, 
    0xCF00, 0xCF03, 0xCF0C, 0xCF0F, 0xCF30, 0xCF33, 0xCF3C, 0xCF3F, 
    0xCFC0, 0xCFC3, 0xCFCC, 0xCFCF, 0xCFF0, 0xCFF3, 0xCFFC, 0xCFFF, 
    0xF000, 0xF003, 0xF00C, 0xF00F, 0xF030, 0xF033, 0xF03C, 0xF03F, 
    0xF0C0, 0xF0C3, 0xF0CC, 0xF0CF, 0xF0F0, 0xF0F3, 0xF0FC, 0xF0FF, 
    0xF300, 0xF303, 0xF30C, 0xF30F, 0xF330, 0xF333, 0xF33C, 0xF33F, 
    0xF3C0, 0xF3C3, 0xF3CC, 0xF3CF, 0xF3F0, 0xF3F3, 0xF3FC, 0xF3FF, 
    0xFC00, 0xFC03, 0xFC0C, 0xFC0F, 0xFC30, 0xFC33, 0xFC3C, 0xFC3F, 
    0xFCC0, 0xFCC3, 0xFCCC, 0xFCCF, 0xFCF0, 0xFCF3, 0xFCFC, 0xFCFF, 
    0xFF00, 0xFF03, 0xFF0C, 0xFF0F, 0xFF30, 0xFF33, 0xFF3C, 0xFF3F, 
    0xFFC0, 0xFFC3, 0xFFCC, 0xFFCF, 0xFFF0, 0xFFF3, 0xFFFC, 0xFFFF
} ;

/////////////////////////////////////////////////////////////////////////////
// CHzkView

IMPLEMENT_DYNCREATE(CHzkView, CView)

BEGIN_MESSAGE_MAP(CHzkView, CView)
	//{{AFX_MSG_MAP(CHzkView)
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_BUTTON32772, OnButton32772)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_COMMAND(IDB_12_ROTATION, On12Rotation)
	ON_COMMAND(ID_BTNROTATE, On12Rotation)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_COMMAND(ID_BTN_NEW, &CHzkView::OnBtnNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHzkView construction/destruction

int g_add;	
CHzkView::CHzkView()
{
	// TODO: add construction code here
	m_bDrawing = FALSE;
	g_add = 0;	
}

CHzkView::~CHzkView()
{
	delete m_obitmap ;
}

BOOL CHzkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	m_obitmap  = NULL;
	BOOL bret =CView::PreCreateWindow(cs);
	return bret;
}

/////////////////////////////////////////////////////////////////////////////
// CHzkView drawing
int ReadHZK(char * &pBuf,int nLen = 0, int nSeek=0);
char Mask[8]={0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};

UINT CHzkView::DrawFont(CDC *pDC)
{
	int i,j,k=0;
	char * pbuf;
	DWORD seek =0;
	int nRead = ReadHZK( pbuf,0,0) ;
	if( nRead == 0 || !pbuf ) return -1;

	int npage = this->GetScrollPos(1);
	if( npage != 0) 
		seek = npage * m_npage_size ;

	char * pp = pbuf;
	char * pend = pbuf + nRead;
#if 0
    while( pp < pend )
    {
        BYTE tmp = pp[1];
        pp[1] = pp[0];
        pp[0] = tmp;
        pp+= 2;
    }
#endif
    pp = pbuf;
	pp += g_add + seek;

	CRect r;
	this->GetWindowRect(&r);
	pDC->FillSolidRect( 0,0,r.Width(),r.Height() ,RGB(255,255,255));

	int x =4 ,y = 4 ;
	int chnum = (8 * nRead)/ (nCharWidth * nCharHight);
	int xchar = 0;
	for(int z=0;z<chnum;z++)  //多少字符
	{
		for(j=0;j<nCharHight;j++) //列
		{
			for(i=0;i<nCharWidth;i++)  //行
			{
				if( (Mask[k] & *pp) !=0 )
				{
					pDC->SetPixel(x+i,y+j,RGB(0,0,0) );
				}
				if(k++==7)
				{
					k = 0;
					if( ++pp > pend) goto endl;
				}
			}
		}
		x +=nCharWidth;
		if( xchar != -1 ) xchar ++;
		if(x+ nCharWidth + 12   >= r.Width()) 
		{
			if(xchar != -1)
			{
				m_nXchar = xchar;  //第一行字数
				xchar = -1;
			}
			x=4;
			y+=nCharHight;
			if(y + 12>= r.Height()) break;
		}
	}
	{
		int nput = pp-pbuf;
		if( npage == 0 )
		{
			m_npage_size = nput ;
			m_npages = (nRead + nput - 1) /nput;
			this->SetScrollRange(1,0,m_npages-1,true);
		}
	}
endl:
	delete  pbuf;

	return 0;
}

void CHzkView::OnDraw(CDC* pDC)
{
	CHzkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect r;
	this->GetWindowRect(&r);
/*  //if draw in mem and put dc when output ,remove / * & * /
	if(m_obitmap == NULL)
	{
		m_obitmap  = new CBitmap;
		m_obitmap->CreateCompatibleBitmap(pDC,r.Width(),r.Height());
		m_dc.CreateCompatibleDC(NULL);
		m_dc.SelectObject(m_obitmap );
		m_dc.FillSolidRect(0,0,r.Width() ,r.Height(),RGB(255,255,255));
	}
	pDC->BitBlt(0,0,r.Width(),r.Height(),&m_dc,0,0,SRCCOPY);
*/
	SetTimer(TMR_ID_PAINT_REFRESH, 200, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CHzkView printing

BOOL CHzkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHzkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CHzkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CHzkView diagnostics

#ifdef _DEBUG
void CHzkView::AssertValid() const
{
	CView::AssertValid();
}

void CHzkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHzkDoc* CHzkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHzkDoc)));
	return (CHzkDoc*)m_pDocument;
}
#endif //_DEBUG

int ReadHZK(char * &pBuf,int nLen,int nSeek)
{
	FILE * fp = NULL;

	fp = fopen(g_FileName,"r+b");
	if(fp == NULL ) return  0;
	if(nLen == 0)
	{
		fseek(fp,0,SEEK_END);
		nLen = ftell(fp);
	}
	pBuf = new char[nLen+8];
	if(pBuf == NULL) return 0;

	if(fseek(fp,nSeek,SEEK_SET) != 0)  
	{
		fclose(fp);
		return 0;
	}

	int len =fread(pBuf,1, nLen, fp);
	fclose(fp);

	return len;
}
/////////////////////////////////////////////////////////////////////////////
// CHzkView message handlers

void CHzkView::OnButtonadd() 
{
	g_add++;	
	char pstut[256] ;
	sprintf(pstut,"bias %d",g_add);
	this->Refresh();
	CMainFrame * pparent = (CMainFrame *)(AfxGetApp())->m_pMainWnd;
	pparent->m_wndStatusBar.SetPaneText(0,pstut); 

}

void CHzkView::OnFileOpen() 
{
	this->SetScrollPos(1,0,false);
	g_add = 0;
	CFileDialog fdlg(true,"*.*",g_FileName );
	if( fdlg.DoModal() == IDOK)
	{
		strcpy(g_FileName,(LPCTSTR)(fdlg.GetPathName()));
		
		CMainFrame * pparent = (CMainFrame *)(AfxGetApp())->m_pMainWnd;
		pparent->SetWindowText((LPCTSTR)(fdlg.GetPathName()));
		this->Refresh()	;
	}
}

void CHzkView::OnButton32772() 
{
	CDlgInput	dlg(nCharWidth ,nCharHight );
	if (dlg.DoModal() == IDOK)
	{
		nCharWidth = dlg.m_nCharWidth ;
		nCharHight = dlg.m_nCharHeigh ;
		this->Refresh();
	}
}

void CHzkView::OnFileSave() 
{
	CFileDialog fdlg(false,"",g_FileName );
	char filesave[1024];
	if( fdlg.DoModal() == IDOK)
	{
		strcpy(filesave,(LPCTSTR)(fdlg.GetFileName())); 
		MakeRataFond(filesave , g_FileName);
	}
	
}

int GetPiex(char * buf,int x,int y, int nwidth)
{
	int bits = y*nwidth+x;
	char * pdst = buf + bits/8;
	if( *pdst & Mask[bits%8] )
		return 1;
	else 
		return 0;
}

void SetPiex(char * buf,int x,int y,int nwidth)
{
	int bits = y*nwidth+x;
	char * pdst = buf + bits/8;
	*pdst |=  Mask[bits%8] ;
}

void CHzkView::MakeRataFond(char *filesave, char *filesrc)
{
	if(!(filesave || filesrc) ) return ;
	FILE * fpsrc = fopen(filesrc,"r+b");
	FILE * fpsav = fopen(filesave,"w+b");
	if(!(fpsrc || fpsav) )
	{
		fcloseall();
		return ;
	}

	int nSize = nCharWidth * nCharHight /  8;
	char * psrcbuf = new char [nSize+4];
	int height = ((nCharHight +7 )/8)  * 8;
	int nact_size = nCharWidth * height /8 ;
	char * pdstbuf = new char [nact_size+4];

	int nindex = 0;
	while(!feof(fpsrc))
	{
		if( fread(psrcbuf,1,nSize,fpsrc) != (unsigned int)nSize )
			break;
		memset(pdstbuf,0,nact_size+2);

		if( nindex++ == 836)
		{
			while(nindex++ <= 1400)
			{
				fwrite(pdstbuf,1,nact_size,fpsav);
			}
		}

		for(int y=0;y<nCharHight;y++)
		{
			for(int x=0;x<nCharWidth;x++)
			{
				if(GetPiex(psrcbuf,x,y,nCharWidth) == 1)
				{
					SetPiex(pdstbuf,nCharHight - y - 1,x,height);
				}
			}
		}
		fwrite(pdstbuf,1,nact_size,fpsav);
	}
	fcloseall();
	delete psrcbuf;
	delete pdstbuf;
}

void CHzkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bDrawing) return;
	CView::OnLButtonDown(nFlags, point);
	CMainFrame * pparent = (CMainFrame *)(AfxGetApp())->m_pMainWnd;
	char pstatus[256];
	int x  = (point.x + 4)/nCharWidth ;
	int y = (point.y-4)/nCharHight;
	sprintf(pstatus,"index = %d:  x=%d; y+%d",m_nXchar * y + x,x,y);
	pparent->m_wndStatusBar.SetPaneText(0,pstatus); 
}

void CHzkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDrawing) return;
	CView::OnMouseMove(nFlags, point);
	CMainFrame * pparent = (CMainFrame *)(AfxGetApp())->m_pMainWnd;
	char pstatus[256];
	int x  = (point.x + 4)/nCharWidth ;
	int y = (point.y-4)/nCharHight;
	sprintf(pstatus,"index=%d:  x=%d; y=%d",m_nXchar * y + x,x,y);
	pparent->m_wndStatusBar.SetPaneText(0,pstatus); 
}

BOOL CHzkView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	return CView::OnScroll(nScrollCode, nPos, bDoScroll);
}

void CHzkView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
	switch(nSBCode)
	{
	case SB_LINEUP://0:
	case SB_PAGEUP://2:
		nPos = this->GetScrollPos(1);
		if(nPos > 0 )
			nPos--;
		else
			return;
		break;
	case SB_LINEDOWN ://1:
	case SB_PAGEDOWN: //3:
		nPos = this->GetScrollPos(1);
		if(nPos < m_npages-1 ) 
			nPos++;
		else 
			return;
		break;
	case SB_TOP: 
		nPos = 0;
		break;
	case 8:
		return;
	}
	if (m_bDrawing) return;
	this->SetScrollPos(1,nPos);	
	this->Refresh();

	char pstatus[256];
	int x  = nSBCode ;
	int y = nPos;
	sprintf(pstatus,"x=%d; y=%d",x,y);
	CMainFrame * pparent = (CMainFrame *)(AfxGetApp())->m_pMainWnd;
	pparent->m_wndStatusBar.SetPaneText(0,pstatus); 

}

void CHzkView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CDC * pdc = GetDC();
	CHzkView::SetScrollRange(1,0,0,false);
	m_bDrawing = FALSE;
	// TODO: Add your specialized code here and/or call the base class
	
}


void CHzkView::Refresh()
{
	//this->DrawFont(&m_dc);
	Invalidate();
}

void CHzkView::On12Rotation() 
{
    FILE * fp = fopen(g_FileName,"rb");

    CString strfile = g_FileName;
    int nfind  = strfile.ReverseFind('.');
    if( nfind == -1 ) nfind = strlen(g_FileName);
    strfile = strfile.Left( nfind )  ;
    strfile += "_r.fon";

    FILE * fpout = fopen(strfile,"w+b");

    if( fp == NULL )         return;
    char buf[24], outbuf[24];
    while( !feof(fp))
    {
        memset(buf, 0, 24);
        memset(outbuf, 0, 24);
        fread(buf,1,24,fp);
        for( int y= 0;y< 12;y++)
        {
            for( int x=0;x<12;x++)
            {
				if(GetPiex(buf,x,y,16) == 1)
				{
					SetPiex(outbuf,y ,12 - x -1,16);
				}
            }
        }
        fwrite(outbuf,1,24,fpout);
    }
    fcloseall();
	CString str;
	str.Format("转换输出文件：[%s]", (LPCTSTR)strfile);
	this->MessageBox(str, "转换结束", MB_OK);
    
}


void bltfromfont(CDC* pdc, CRect &r) {
	int y = 0, x = 0;
	int wcav = ((nCharWidth + 7) & ~7);
	CDC   	foutDC;
	CBitmap 	bmpfount;
	char buf[256];
	bmpfount.CreateBitmap(wcav, nCharHight, 1, 1, buf);
	foutDC.CreateCompatibleDC(pdc);
	foutDC.SelectObject(&bmpfount);


	char* pfont;

	DWORD seek = 0;
	int imgsize = (wcav * nCharHight);
	int nRead = ReadHZK(pfont, 0, 0);
	if (nRead == 0 || !pfont) return;

	DWORD* pdw = (DWORD*)pfont;
	for (int i = 0; i < (nRead + 8) / 4; i++) {
		pdw[i] = ~pdw[i];
	}

	for (int rx = 0; rx < nRead; rx += imgsize/8) {
		//memcpy(buf, pfont + rx, ftsz);
		bmpfount.SetBitmapBits(imgsize/8, pfont + rx);
		pdc->BitBlt(x, y, nCharWidth, nCharHight, &foutDC, 0, 0, SRCCOPY);
		x += nCharWidth;
		if (x + nCharWidth > r.Width()) {
			y += nCharHight;
			x = 0;
		}
	}
	delete[]pfont;
		 
}

void CHzkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
		case TMR_ID_PAINT_REFRESH:
		{
			KillTimer(nIDEvent);
			m_bDrawing = TRUE;
			CClientDC  vdc(this);
			CRect r;
			this->GetClientRect(&r);
			CDC   	memDC;
			CBitmap 	bitmap;
			bitmap.CreateCompatibleBitmap(&vdc, r.Width(), r.Height());
			memDC.CreateCompatibleDC(&vdc);
			memDC.SelectObject(&bitmap);
			CMainFrame* pparent = (CMainFrame*)(AfxGetApp())->m_pMainWnd;
			pparent->m_wndStatusBar.SetPaneText(0, "打开字库中 ...");

			//if( DrawFont(&memDC) == 0 )
			//	vdc.BitBlt(0, 0, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);
			bltfromfont(&vdc, r);


			pparent->m_wndStatusBar.SetPaneText(0, "字库显示完毕");
			m_bDrawing = FALSE;
		}
		break;

	}

	CView::OnTimer(nIDEvent);
}


//void CHzkView::OnBtnrotate()
//{
//	// TODO: 在此添加命令处理程序代码
//}

#include "MkFontDlg.h"
void CHzkView::OnBtnNew()
{
	// TODO: 在此添加命令处理程序代码
	CMkFontDlg dlg;
	dlg.DoModal();
	this->Invalidate();
}
