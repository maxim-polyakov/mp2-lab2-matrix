#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include "tvector.h"

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector {
protected:
	ValType *pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // ����������� �����������
	virtual ~TVector();
	int GetSize() const { return Size; } // ������ �������
	int GetStartIndex() const { return StartIndex; } // ������ ������� ��������
	ValType& operator[](int pos) const;             // ������
	bool operator==(const TVector &v) const;  // ���������
	bool operator!=(const TVector &v) const;  // ���������
	TVector& operator=(const TVector &v);     // ������������

	// ��������� ��������
	TVector  operator+(const ValType &val);   // ��������� ������
	TVector  operator-(const ValType &val);   // ������� ������
	TVector  operator*(const ValType &val);   // �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector &v);     // ��������
	TVector  operator-(const TVector &v);     // ���������
	ValType  operator*(const TVector &v);     // ��������� ������������

	// ����-�����
	friend istream& operator>>(istream &in, TVector &v) {
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream &out, const TVector &v) {
		for (int i = 0; i < v.Size + v.StartIndex; i++)
			out << v[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si = 0) {
	if (s>MAX_VECTOR_SIZE) {
		throw invalid_argument("����������� MAX_VECTOR_SIZE<s");
	}
	if (s<0) {
		throw invalid_argument("����������� s<0");
	}
	if (si<0) {
		throw invalid_argument("����������� si<0");
	}
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = ValType();
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType> &v) {
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];

	for (int i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector() {
	delete[]pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos) const {
	if (pos<0) {
		throw invalid_argument("[] pos<0");
	}
	if (pos >= StartIndex + Size) {
		throw invalid_argument("[] pos>MAX_VECTOR_SIZE");
	}
	if (pos<StartIndex) {
		return *new ValType();
	}
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/


template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector &v) const {
	if (Size != v.GetSize()) {
		return false;
	}
	if (StartIndex != v.GetStartIndex()) {
		return false;
	}

	for (int i = StartIndex; i < Size + StartIndex; i++) {
		if ((*this)[i] != v[i]) {
			return false;
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector &v) const {
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
	if (this != &v) {
		if (Size != v.GetSize()) {
			delete[]pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.GetSize();
		StartIndex = v.GetStartIndex();
		for (int i = StartIndex; i < Size + StartIndex; i++) {
			(*this)[i] = v[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val) {
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = (*this)[i] + val;
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val) {
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = (*this)[i] - val;
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val) {
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = (*this)[i] * val;
	}

	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) {

	if (GetSize() != v.GetSize() || GetStartIndex() != v.GetStartIndex()) {
		throw invalid_argument("�������� �������� ������ �����");
	}

	TVector<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size + StartIndex; i++) {
		result[i] = (*this)[i] + v[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) {
	if (GetSize() == v.GetSize()) {
		TVector<ValType> result(GetSize(), GetStartIndex());

		for (int i = StartIndex; i < Size + StartIndex; i++) {
			result[i] = (*this)[i] - v[i];
		}
		return result;
	}
	throw invalid_argument("��������� �������� ������ �����");
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
	ValType result = 0;
	if (GetSize() == v.GetSize()) {
		for (int i = StartIndex; i < Size + StartIndex; i++) {
			result = result + (*this)[i] * v[i];
		}
		return result;
	}
	throw invalid_argument("��������� ������������ �������� ������ �����");
} /*-------------------------------------------------------------------------*/
#endif