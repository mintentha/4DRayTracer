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

M33 M44::SubMatrix(int i, int j) {
	// Remove the ith row and jth column
	M33 ret;
	for (size_t row = 0; row < 3; row++) {
		size_t _row = row < i ? row : row + 1;
		for (size_t col = 0; col < 3; col++) {
			size_t _col = col < j ? col : col + 1;
			ret[row][col] = rows[_row][_col];
		}
	}
	return ret;
}


M44 M44::Inverted() {
	V4 a = GetColumn(0);
	V4 b = GetColumn(1);
	V4 c = GetColumn(2);
	V4 d = GetColumn(3);
	V4 _a = b ^ c ^ d;
	_a /= a * _a;
	V4 _b = c ^ d ^ a;
	_b /= b * _b;
	V4 _c = d ^ a ^ b;
	_c /= c * _c;
	V4 _d = a ^ b ^ c;
	_d /= d * _d;
	return M44(_a, _b, _c, _d);
}

/*
 * This is an implementation using Cramer's rule instead. I'm pretty sure they both work, 
 * but if there is ever an issue with the first one, this one definitely works
 * I don't know which one requires more computation
 * Above implementation ^ takes 4 cross products, each cross product takes 4 3d determinants, for a total of 16
 * Below implementation takes 16 3d determinants, one for each entry, plus the determinant of the 4x4 matrix,
 * which is 4 more 3d determinants, so 20 3d determinants
 * So Cramer's rule seem's marginally slower, unless I'm missing something
M44 M44::Inverted() {
	M44 ret;
	float det = determinant();
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			float entry = SubMatrix(j, i).determinant() / det;
			if ((i + j) % 2) {
				entry *= -1;
			}
			ret[i][j] = entry;
		}
	}
	return ret;
}
*/

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


M44& M44::Invert() {
	*this = this->Inverted();
	return *this;
}

float M44::determinant() {
	return rows[0][0] * SubMatrix(0, 0).determinant() -
		   rows[0][1] * SubMatrix(0, 1).determinant() +
		   rows[0][2] * SubMatrix(0, 2).determinant() -
		   rows[0][3] * SubMatrix(0, 3).determinant();
}

std::ostream& operator<<(std::ostream& ostr, M44& mat) {

	return ostr << mat[0] << std::endl << mat[1] << std::endl << mat[2] << std::endl << mat[3];

}

std::istream& operator>>(std::istream& istr, M44& mat) {
	return istr >> mat[0] >> mat[1] >> mat[2] >> mat[4];
}