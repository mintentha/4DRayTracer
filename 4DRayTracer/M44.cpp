#include "M44.h"

M44::M44(V4 row1, V4 row2, V4 row3, V4 row4) {
	rows[0] = row1;
	rows[1] = row2;
	rows[2] = row3;
	rows[3] = row4;
}

M44::M44(const M44& mat) {
	rows[0] = mat.rows[0];
	rows[1] = mat.rows[1];
	rows[2] = mat.rows[2];
	rows[3] = mat.rows[3];
}

M44::M44(float f) {
	rows[0] = V4(f);
	rows[1] = V4(f);
	rows[2] = V4(f);
	rows[3] = V4(f);
}

V4& M44::operator[](int i) {
	return rows[i];
}

M44& M44::operator=(M44 mat) {
	rows[0] = mat[0];
	rows[1] = mat[1];
	rows[2] = mat[2];
	rows[3] = mat[3];
	return *this;
}

M44& M44::operator+=(M44 mat) {
	rows[0] += mat[0];
	rows[1] += mat[1];
	rows[2] += mat[2];
	rows[3] += mat[3];
	return *this;
}

M44& M44::operator-=(M44 mat) {
	rows[0] -= mat[0];
	rows[1] -= mat[1];
	rows[2] -= mat[2];
	rows[3] -= mat[3];
	return *this;
}

M44& M44::operator*=(M44 mat) {
	return *this = *this * mat;
}

M44& M44::operator*=(float scf) {
	rows[0] *= scf;
	rows[1] *= scf;
	rows[2] *= scf;
	rows[3] *= scf;
	return *this;
}

M44& M44::operator%=(M44 mat) {
	rows[0] %= mat[0];
	rows[1] %= mat[1];
	rows[2] %= mat[2];
	rows[3] %= mat[3];
	return *this;
}

M44 operator+(M44 mat1, M44 mat2) {
	return mat1 += mat2;
}

M44 operator-(M44 mat1, M44 mat2) {
	return mat1 -= mat2;
}

M44 M44::operator*(M44 mat) {
	return M44(*this * mat.GetColumn(0), *this * mat.GetColumn(1), *this * mat.GetColumn(2), *this * mat.GetColumn(3)).Transposed();
}

M44 operator*(M44 mat, float scf) {
	return mat *= scf;
}

M44 operator*(float scf, M44 mat) {
	return mat *= scf;
}

V4 M44::operator*(V4 v) {
	return V4(rows[0] * v, rows[1] * v, rows[2] * v, rows[3] * v);
}

M44 operator%(M44 mat1, M44 mat2) {
	return mat1 %= mat2;
}

V4 M44::GetColumn(int i) {
	return V4(
		rows[0][i],
		rows[1][i],
		rows[2][i],
		rows[3][i]
	);
}

void M44::SetColumn(int i, V4 colv) {
	rows[0][i] = colv[0];
	rows[1][i] = colv[1];
	rows[2][i] = colv[2];
	rows[3][i] = colv[3];
}

M44 M44::Transposed() {
	return M44(
		GetColumn(0),
		GetColumn(1),
		GetColumn(2),
		GetColumn(3)
	);
}

M44& M44::Transpose() {
	*this = this->Transposed();
	return *this;
}

std::ostream& operator<<(std::ostream& ostr, M44& mat) {

	return ostr << mat[0] << " " << mat[1] << " " << mat[2];

}

std::istream& operator>>(std::istream& istr, M44& mat) {
	return istr >> mat[0] >> mat[1] >> mat[2];
}