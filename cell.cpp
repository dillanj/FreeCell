#include "pch.h"
#include "cell.h"
#include "WindowsCards.h"


Cell::Cell(double l, double t, double r, double b) {
	mLeft = l;
	mTop = t;
	mRight = r;
	mBottom = b;
	mSelected = false;
}


void Cell::Draw( CDC& dc, CImage images[] ) {
	CBrush cellBackgroundColor(RGB(128, 128, 128));
	dc.SelectObject(cellBackgroundColor);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	int left = mLeft;
	int top = mTop;
	

	//draw each card that belongs to the cell
	for ( int i = 0; i < mCards.size(); i++) {
		int index = mCards[i];
		DrawCard(dc, mLeft, top, index, mSelected); // index is 0 to mCards.size, for the different cards.
		top += 30;
	}




	/* SCOOB SETTINGS - NEED FIXING 
	int index = mCards[mCards.size() - 1]; // getting last card
	images[1].StretchBlt(dc, mLeft + 2, mTop + 2, mRight - mLeft, mBottom - mTop, SRCCOPY);
	*/
}


void Cell::AddCard(int card_index) {
	// check to see if we can accept card
	mCards.push_back(card_index);
}


void Cell::RemoveCard() {
	if (this->CanRemoveCard()) {
		mCards.pop_back();
	}
}

bool Cell::CanRemoveCard() {
	return mCards.size() > 0;
}


bool Cell::CanAcceptCard(int card_index) {
	// check to see if we can
	return true;
}


bool Cell::isClicked(int x, int y) {
	return (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom);	
}

void Cell::setSelected(bool selected) {
	mSelected = selected;
}

int Cell::takeTopCard() {
	if ( mCards.size() )
		return mCards[mCards.size() - 1];
	return -1;
}



//////// START CELL ////////


StartCell::StartCell(double l, double t, double r, double b) : Cell(l, t, r, b) {
}

void StartCell::Draw(CDC& dc, int w, int h, CImage images[]) {
	CBrush cellBackgroundColor(RGB(12, 128, 12));
	dc.SelectObject(cellBackgroundColor);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	if (mCards.size() > 0) {
		DrawCard(dc, mLeft + 2, mTop + 2, mCards[mCards.size() - 1]);
	}
}

bool StartCell::CanAcceptCard(int card_index) {
	if (mCards.size() == 0) {
		return true;
	}
	int top = takeTopCard();
	switch (top % 4) {
	case (0): // clubs
		if (card_index == top - 2 || card_index == top - 3) { return true; }

	case (1): // diamonds
		if (card_index == top - 2 || card_index == top - 5) { return true; }

	case (2): // hearts
		if (card_index == top - 3 || card_index == top - 6) { return true; }

	case (3): // spaids
		if (card_index == top - 5 || card_index == top - 6) { return true; }
	}

	return false;
}



//////// END CELL ////////


EndCell::EndCell(double l, double t, double r, double b) : Cell(l,t,r,b) {
}

bool EndCell::CanRemoveCard() {
	return false;
}

bool EndCell::CanAcceptCard(int card_index) {
	// check to see if top card will allow this one.
	// if it is the next num of that suit or if it is the first in the end cell and is an ace
	if (card_index == takeTopCard() + 4 || ( mCards.size() == 0 &&  card_index < 4 ) )
	{
		return true;
	}
	return false;
}





//////// FREE CELL ////////

FreeCell::FreeCell(double l, double t, double r, double b) : Cell(l, t, r, b) {

}

bool FreeCell::CanRemoveCard() {
	return true;
}

bool FreeCell::CanAcceptCard(int card_index) {
	// check to see if the free cell is empty. if so it can acccept. else false.
	if ( mCards.size() ) {
		return false;
	}
	return true;
}





