
// FreeCellDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FreeCell.h"
#include "FreeCellDlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"
#include <ctime> 
#include <cstdlib>  
#include <algorithm> 
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int LITTLE_MARGIN = 110;
int START_CELL_MARGIN = 130;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFreeCellDlg dialog



CFreeCellDlg::CFreeCellDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FREECELL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeCellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFreeCellDlg message handlers

BOOL CFreeCellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitializeCards();
	std::srand(unsigned(std::time(0)));

	//this code gets the images matched up with the correct card indexes
	for (int index = 0; index < 52; index++) {
		mCardImages[index].Destroy();
		CString cardPath;
		cardPath += "Scooby_Doo75by111\\"; //adds to default directory path.
		if (index % 4 == 0) {
			cardPath += "club_";
		}
		if (index % 4 == 1) {
			cardPath += "diamond_";
		}
		if (index % 4 == 2) {
			cardPath += "heart_";
		}
		if (index % 4 == 3) {
			cardPath += "spade_";
		}
		int rank = index / 4 + 1;
		char buffer[10];
		sprintf(buffer, "%i", rank);
		cardPath += buffer;
		cardPath += ".jpg";
		mCardImages[index].Load(cardPath);
	}
	
	//INITIALIZE Cells
	int l=100, r = 200;
	int t, b;

	for (int i = 0; i < 16; i++) {
		if (i < 4) {
		// free cells
			t = 10;
			b = 140;
			mCells[i] = new FreeCell(l, t, r, b);
			l += LITTLE_MARGIN;
			r += LITTLE_MARGIN;
		}
			
		else if (i >= 4 && i < 8) {
			// end cells
			if (i == 4) {
				l += 150;
				r += 150;
			}
			t = 10;
			b = 140;
			mCells[i] = new EndCell(l, t, r, b);
			l += LITTLE_MARGIN;
			r += LITTLE_MARGIN;
		}
		
		else if (i >= 8 && i < 16) {
			//start cells
			if (i == 8) { // reset left and right for start cells
				l = 100;
				r = 200;
			}
			t = 300;
			b = 600;
			mCells[i] = new StartCell(l, t, r, b);
			l += START_CELL_MARGIN;
			r += START_CELL_MARGIN;
		}
		
	}
	
	
	// get a vector of cards, then shuffle
	std::vector< int > cards;
	for ( int i = 0; i < 52; i++) {
		cards.push_back(i);
	}
	//shuffle cards
	std::random_shuffle(cards.begin(), cards.end());
	//Add Cards to Cells for Initialization
	for (int i = 0; i < cards.size(); i++) {
		if (i >= 0 && i <= 7) {
			mCells[8]->AddCard(cards[i]);
		}
		if (i > 7 && i <= 14) {
			mCells[9]->AddCard(cards[i]);
		}
		if (i > 14 && i <= 21 ) {
			mCells[10]->AddCard(cards[i]);
		}
		if (i > 21 && i <= 27) {
			mCells[11]->AddCard(cards[i]);
		}
		if (i > 27 && i <= 33) {
			mCells[12]->AddCard(cards[i]);
		}
		if (i > 33 && i <= 39) {
			mCells[13]->AddCard(cards[i]);
		}
		if (i > 39 && i <= 45) {
			mCells[14]->AddCard(cards[i]);
		}
		if (i > 45 && i <= 51) {
			mCells[15]->AddCard(cards[i]);
		}

	}
	// set it to an invalid number on intilization so there is no selected cell
	mSelectedCell = -1; 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreeCellDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFreeCellDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CPaintDC dc(this);
		// DRAW CELLS
		for (int i = 0; i < 16; i++) {
			mCells[i]->Draw( dc, mCardImages );
		}


		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeCellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool second_click = false;
int previous_selected_cell = -1;
int selected_card = -1;

void CFreeCellDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (second_click == true) {
		second_click = false;
		// on second click, ask all the cells if they were clicked on
		for (int i = 0; i < 16; i++) {
			mCells[i]->setSelected(false);
			if (mCells[i]->isClicked(point.x, point.y)) {
				// if one says yes, ask that cell if it can accept the top card from the previous selected cell
				bool accepts = mCells[i]->CanAcceptCard(selected_card);
				if (accepts) {
					mCells[i]->AddCard(selected_card);
					mCells[previous_selected_cell]->RemoveCard();
				}

			}
		}

	}
	else if (second_click == false) {
		second_click = true;
		// on first click, ask all the cells if they were clicked on
		for (int i = 0; i < 16; i++) {
			if (mCells[i]->isClicked(point.x, point.y)) {
				// if one says yes, ask that cell if you can remove a card from it
				if (mCells[i]->CanRemoveCard()) {
					// if it says yes, then it is the selected cell now
					mCells[i]->setSelected(true);
					selected_card = mCells[i]->takeTopCard();
					previous_selected_cell = i;
				}
			}
		}
	}
	
	
	
	


	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}
