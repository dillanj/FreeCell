#pragma once
#include <vector>

class Cell {
public:
	Cell(double l, double t, double r, double b);
	virtual void Draw( CDC& dc, CImage images[] );
	void AddCard( int card_index );
	void RemoveCard();

	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard( int card_index );
	

	bool isSelected() { return mSelected;  }
	bool isClicked( int x, int y );
	void setSelected(bool selected);
	//implement a take top card method
	int takeTopCard();

protected:
	std::vector<int> mCards;
	double mLeft, mTop, mRight, mBottom;
	bool mSelected;
};

class StartCell : public Cell {
public:
	StartCell(double l, double t, double r, double b);
	void Draw(CDC& dc, int w, int h, CImage images[]);
	bool CanAcceptCard(int card_index);
};


class EndCell : public Cell {
public:
	EndCell(double l, double t, double r, double b);
	// drawing is same as inherited cell class
	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int card_index);
};


class FreeCell : public Cell {
public:
	FreeCell(double l, double t, double r, double b);
	// drawing is same as inherited cell class
	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard( int card_index );
};


