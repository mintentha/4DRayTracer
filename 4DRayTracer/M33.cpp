#include "M33.h"

M33::M33(V3 row1, V3 row2, V3 row3) {
	rows[0] = row1;
	rows[1] = row2;
	rows[2] = row3;
}

M33::M33(const M33& mat) {
	rows[0] = mat.rows[0];
	rows[1] = mat.rows[1];
	rows[2] = mat.rows[2];
}

M33::M33(float f) {
	rows[0] = V3(f);
	rows[1] = V3(f);
	rows[2] = V3(f);
}

V3& M33::operator[](int i) {
	return rows[i];
}

M33& M33::operator=(M33 mat) {
	rows[0] = mat[0];
	rows[1] = mat[1];
	rows[2] = mat[2];
	return *this;
}

M33& M33::operator+=(M33 mat) {
	rows[0] += mat[0];
	rows[1] += mat[1];
	rows[2] += mat[2];
	return *this;
}

M33& M33::operator-=(M33 mat) {
	rows[0] -= mat[0];
	rows[1] -= mat[1];
	rows[2] -= mat[2];
	return *this;
}

M33& M33::operator*=(M33 mat) {
	return *this = *this * mat;
}

M33& M33::operator*=(float scf) {
	rows[0] *= scf;
	rows[1] *= scf;
	rows[2] *= scf;
	return *this;
}

M33& M33::operator%=(M33 mat) {
	rows[0] %= mat[0];
	rows[1] %= mat[1];
	rows[2] %= mat[2];
	return *this;
}

M33 operator+(M33 mat1, M33 mat2) {
	return mat1 += mat2;
}

M33 operator-(M33 mat1, M33 mat2) {
	return mat1 -= mat2;
}

M33 M33::operator*(M33 mat) {
	return M33(*this * mat.GetColumn(0), *this * mat.GetColumn(1), *this * mat.GetColumn(2)).Transposed();
}

M33 operator*(M33 mat, float scf) {
	return mat *= scf;
}

M33 operator*(float scf, M33 mat) {
	return mat *= scf;
}

V3 M33::operator*(V3 v) {
	return V3(rows[0] * v, rows[1] * v, rows[2] * v);
}

M33 operator%(M33 mat1, M33 mat2) {
	return mat1 %= mat2;
}

V3 M33::GetColumn(int i) {
	return V3(
		rows[0][i],
		rows[1][i],
		rows[2][i]
	);
}

void M33::SetColumn(int i, V3 colv) {
	rows[0][i] = colv[0];
	rows[1][i] = colv[1];
	rows[2][i] = colv[2];
}

M33 M33::Inverted() {
	V3 a = GetColumn(0), b = GetColumn(1), c = GetColumn(2);
	V3 _a = b ^ c; _a = _a / (a * _a);
	V3 _b = c ^ a; _b = _b / (b * _b);
	V3 _c = a ^ b; _c = _c / (c * _c);
	return M33(_a, _b, _c);

}

M33& M33::Invert() {
	*this = this->Inverted();
	return *this;
}

M33 M33::Transposed() {
	return M33(
		GetColumn(0),
		GetColumn(1),
		GetColumn(2)
	);
}

M33& M33::Transpose() {
	*this = this->Transposed();
	return *this;
}

float M33::determinant() {
	return
		rows[0][0] * (rows[1][1] * rows[2][2] - rows[1][2] * rows[2][1]) -
		rows[0][1] * (rows[1][0] * rows[2][2] - rows[1][2] * rows[2][0]) +
		rows[0][2] * (rows[1][0] * rows[2][1] - rows[1][1] * rows[2][0]);
}

std::ostream& operator<<(std::ostream& ostr, M33& mat) {
	return ostr << mat[0] << std::endl << mat[1] << std::endl << mat[2];
}

std::istream& operator>>(std::istream& istr, M33& mat) {
	return istr >> mat[0] >> mat[1] >> mat[2];
}