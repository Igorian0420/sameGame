#pragma once
#include <windef.h>
class cSameGameBoard
{
public:
	cSameGameBoard(void);

	//����������� ��������� �����������
	cSameGameBoard(const cSameGameBoard& board);

	~cSameGameBoard(void);
	
	//����� ��� ��������� ����������� ������ � ������ ����
	void setupBoard(void); 

	//��������� ����� � ������������ ������� ����
	COLORREF getBoardSpace(int row, int col);

	//������� � ������� ��� ��������� ���������� � ���������� �������� ����
	int getWidth(void) const { return m_nWidth; }
	void setWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }

	int getHeight(void) const { return m_nHeight; }
	void setHeight(int nHeight) { m_nHeight = (nHeight >= 3) ? nHeight : 3; }

	int getColumns(void) const { return m_nColumns; }
	void setColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }

	int getRows(void) const { return m_nRows; }
	void setRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }

	//������� � ������� ��� ��������� ���������� ������
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors) { m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors; }

	//�� ��������� ����?
	bool IsGameOver(void) const;

	//������� ���������� ���������� ������
	int GetRemainingCount(void) const { return m_nRemaining; }

	//������ ��� �������� ���� ����������� ������
	int DeleteBlocks(int row, int col);

	//������� ��� �������� �������� ���� � ������������ ������
	void deleteBoard(void);


private:
	//������� ��� �������� �������� ���� � ��������� ������ ��� ����
	void createBoard(void);

	//������������� � ���������� ����������� (������ �� ������) ����������� ��� �������� ������
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	//��������������� ����������� ������� ��� �������� ����������� ������ 
	int DeleteNeghborBlocks(int row, int col, int color, Direction direction);

	//������ ��� ������ ����� ����� ����, ��� ���� ������� �����
	void CompactBoard(void);

	//��������� �� ��������� ������
	int** m_arrBoard;

	//������ ������, 0 - ���� ����, 1-7 - ����� ������
	COLORREF m_arrColors[8];

	//���������� � ������� ����
	int m_nWidth;
	int m_nHeight;
	int m_nColumns;
	int m_nRows;
	int m_nRemaining;
	int m_nColors;
};

