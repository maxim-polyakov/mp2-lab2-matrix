// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
public:
  ValType *pVector;
  int Size;       // размер вектора
  int strtidx; // индекс первого элемента вектора

  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  virtual ~TVector();
  int GetSize()      { return Size;       }; // размер вектора
  int GetStartIndex(){ return strtidx; }; // индекс первого элемента
  ValType& operator[](int pos)const;             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение
  friend istream& operator>>(istream &in, TVector &v){ for (int i = 0; i < v.Size; i++)
	  in >> v.pVector;
    return in;};
	friend ostream& operator<<(ostream &out, const TVector &v){ for (int i = 0; i < v.Size; i++)
		out << v.pVector << ' ';
    return out;};
  // ввод-вывод
};
  template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)const
{
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	pVector = new ValType[s];
	Size = s; strtidx = si;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	strtidx = v.strtidx;
	pVector = new ValType[v.Size];
	memcpy(pVector, v.pVector, sizeof(ValType)*Size);

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
//	if (pos<0)
	//	 {
	//	throw invalid_argument("[] pos<0");
	//	};
	//if (pos>MAX_VECTOR_SIZE)
	//	 {
	//	throw invalid_argument("[] MAX_VECTOR_SIZE<pos");
	//	};
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.GetSize() || strtidx != v.GetStartIndex())
		 {
		return false;
		}
	for (int i = 0; i < Size; i++) {
		if ((*this)[i] != v[i]) {
			return false;
			
		}
		
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (!(*this == v)){return true;};
}; /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (*this != v){
		if (Size != v.Size){
			delete[]pVector;
			pVector = new ValType[v.Size];
		};
		Size = v.Size; strtidx = v.strtidx;
		for (int i = 0; i < Size; i++){ pVector[i] = v.pVector[i]; };
	};
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	for (int i = 0; i < GetSize(); i++) {
		(*this)[i] = (*this)[i] + val;
		
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	for (int i = 0; i < GetSize(); i++) {
	(*this)[i] = (*this)[i] - val;
		
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	for (int i = 0; i < GetSize(); i++)
		 {
		(*this)[i] = (*this)[i] * val;
		}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (GetSize() == v.GetSize()) {
		TVector<ValType> result(GetSize());
		
			for (int i = 0; i < GetSize(); i++) {
			result[i] = (*this)[i] + v[i];
			
		}
		return result;
		
	}
	throw invalid_argument("Сложение векторов разной длины");
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (GetSize() == v.GetSize()) {
		TVector<ValType> result(GetSize());
		
			for (int i = 0; i < GetSize(); i++) {
			result[i] = (*this)[i] - v[i];
			
		}
		return result;
		
	}
	throw invalid_argument("Вычитание векторов разной длины");
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType result = 0;
	if (GetSize() == v.GetSize()) {
		for (int i = 0; i < GetSize(); i++) {
			result = result + (*this)[i] * v[i];
			
		}
		return result;
		
	}
	throw invalid_argument("Скалярное произведение векторов разной длины");
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s<0)
		 {
		throw "s<0";
		}
	if (s>MAX_MATRIX_SIZE) {
		throw "MAX_MATRIX_SIZE<s";
		
	}
	for (int i = 0; i < s; i++)
		 {
		pVector[i] = TVector<ValType>(s - i, i);
		}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
TVector<TVector<ValType> >(mt) { }

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
TVector<TVector<ValType> >(mt) { return *this; }

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) {
		return true;

	}

	if (Size != mt.Size) {
		return false;

	}

	for (int i = StartIndex; i < Size; i++) {
		if (pVector[i] != mt.pVector[i])
			return false;

	}

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt) {
		if (Size != mt.Size) {
			delete[]pVector;
			pVector = new TVector<ValType>[mt.Size];
			
		}
		Size = mt.Size;
		strtidx = mt.strtidx;
		for (int i = 0; i < Size; i++) {
			pVector[i] = mt.pVector[i];
			
		}
		
	}
	return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return *this;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
