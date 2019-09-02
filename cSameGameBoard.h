#pragma once
#include <windef.h>
class cSameGameBoard
{
public:
	cSameGameBoard(void);

	//конструктор глубокого копирования
	cSameGameBoard(const cSameGameBoard& board);

	~cSameGameBoard(void);
	
	//метод для рандомной расстановки блоков в начаде игры
	void setupBoard(void); 

	//получение цвета в определенном участке поля
	COLORREF getBoardSpace(int row, int col);

	//геттеры и сеттеры для получения информации о параметрах игрового поля
	int getWidth(void) const { return m_nWidth; }
	void setWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }

	int getHeight(void) const { return m_nHeight; }
	void setHeight(int nHeight) { m_nHeight = (nHeight >= 3) ? nHeight : 3; }

	int getColumns(void) const { return m_nColumns; }
	void setColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }

	int getRows(void) const { return m_nRows; }
	void setRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }

	//геттеры и сеттеры для получения количества цветов
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors) { m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors; }

	//мы закончили игру?
	bool IsGameOver(void) const;

	//подсчет количества оставшихся блоков
	int GetRemainingCount(void) const { return m_nRemaining; }

	//функия для удаления всех примыкающих блоков
	int DeleteBlocks(int row, int col);

	//функция для удаления игрового поля и освобождения памяти
	void deleteBoard(void);


private:
	//функция для создания игрового поля и выделения память под него
	void createBoard(void);

	//переччисление с вариантами направления (откуда мы пришли) потребуется для удаления блоков
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	//вспомогательная рекурсивная функция для удаления примыкающих блоков 
	int DeleteNeghborBlocks(int row, int col, int color, Direction direction);

	//функия для сжатия доски после того, как были удалены блоки
	void CompactBoard(void);

	//указатель на двумерный массив
	int** m_arrBoard;

	//список цветов, 0 - цвет фона, 1-7 - цвета блоков
	COLORREF m_arrColors[8];

	//информация о размере поля
	int m_nWidth;
	int m_nHeight;
	int m_nColumns;
	int m_nRows;
	int m_nRemaining;
	int m_nColors;
};

