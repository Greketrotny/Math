#ifndef MATRIX_H
#define MATRIX_H

namespace Math
{
	template <class T> class matrix
	{
	private:
		typedef unsigned int uint;
		size_t rows, columns;
		T *storage = nullptr;
		T default_value;


	public:
		matrix(const matrix<T>& M)
			:rows(M.rows), columns(M.columns), default_value(M.default_value)
		{
			storage = new T[rows * columns];
			*this = M;
		}
		matrix(matrix<T>&& M)
			: rows(M.rows), columns(M.columns), default_value(M.default_value)
		{
			storage = M.storage;
			M.storage = nullptr;

			M.rows = 0;
			M.columns = 0;
		}
		matrix(unsigned int rows, unsigned int columns, T default_value = (T)0.0)
		{
			if (rows < 1) rows = 1;
			if (columns < 1) columns = 1;

			this->rows = rows;
			this->columns = columns;
			this->default_value = default_value;

			storage = new T[rows * columns];
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Value(i, j, default_value);
				}
			}
		}
		~matrix()
		{
			delete[] storage;
		}


		// -- operators -- //
	public:
		matrix<T> operator+(const matrix<T>& M)
		{
			if ((rows == M.rows) && (columns == M.columns))
			{
				// create result matrix
				matrix<T> Result(rows, columns, default_value);

				// add values
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						Result.Value(i, j) = Value(i, j) + M.Value(i, j);
					}
				}
				return Result;
			}
			return *this;
		}
		matrix<T> operator-(const matrix<T>& M)
		{
			if ((rows == M.rows) && (columns == M.columns))
			{
				// create result matrix
				matrix<T> Result(rows, columns, default_value);

				// add values
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						Result.Value(i, j) = Value(i, j) - M.Value(i, j);
					}
				}
				return Result;
			}
			return *this;
		}
		matrix<T> operator*(const matrix<T>& M)
		{
			if (columns == M.rows)
			{
				matrix<T> Result(rows, M.columns, default_value);

				// multiplication
				T sum = (T)0.0;
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < M.columns; j++)
					{
						for (unsigned int k = 0; k < columns; k++)
						{
							sum += Value(i, k) * M.Value(k, j);
						}
						Result.Value(i, j) = sum;
						sum = (T)0.0;
					}
				}
				return Result;
			}
			return *this;
		}
		matrix<T> operator*(T scalar)
		{
			matrix Result(rows, columns, default_value);

			// multiplication
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Result.Value(i, j) = Value(i, j) * scalar;
				}
			}
			return Result;
		}
		matrix<T> operator/(T scalar)
		{
			if (scalar == 0.0)
				return *this;

			matrix<T> Result(rows, columns, default_value);

			// legal division
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Result.Value(i, j) = Value(i, j) / scalar;
				}
			}

			return Result;
		}
		matrix<T>& operator+=(const matrix<T>& M)
		{
			if ((rows == M.rows) && (columns == M.columns))
			{
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						this->Value(i, j) += M.Value(i, j);
					}
				}
			}
			return *this;
		}
		matrix<T>& operator-=(const matrix<T>& M)
		{
			if ((rows == M.rows) && (columns == M.columns))
			{
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						this->Value(i, j) -= M.Value(i, j);
					}
				}
			}
			return *this;
		}
		matrix<T>& operator*=(const matrix<T>& M)
		{
			if (columns == M.rows)
			{
				// create result matrix
				matrix<T> Result(rows, M.columns, default_value);

				// do multiplication to result matrix
				T sum = (T)0.0;

				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < M.columns; j++)
					{
						for (unsigned int k = 0; k < columns; k++)
						{
							sum += Value(i, k) * M.Value(k, j);
						}
						Result.Value(i, j) = sum;
						sum = (T)0.0;
					}
				}

				// copy values to this matrix
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						Value(i, j) = Result.Value(i, j);
					}
				}
			}
			return *this;
		}
		matrix<T>& operator*=(T scalar)
		{
			// multiplication
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Value(i, j) *= scalar;
				}
			}
			return *this;
		}
		matrix<T>& operator/=(T scalar)
		{
			if (scalar == 0.0)
				return *this;

			// legal division
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Value(i, j) /= scalar;
				}
			}

			return *this;
		}
		matrix<T>& operator=(const matrix<T>& M)
		{
			// when selfassignment
			if (&M == this)
				return *this;

			// check storage size
			if (rows * columns != M.rows * M.columns)
			{
				// when rows and columns number doesn't match
				delete[] storage;
				storage = new T[M.rows * M.columns];
			}

			// copy values
			rows = M.rows;
			columns = M.columns;
			default_value = M.default_value;

			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					Value(i, j) = M.Value(i, j);
				}
			}

			// return updated *this
			return *this;
		}
		matrix<T>& operator=(matrix<T>&& M)
		{
			// check selfassignment
			if (&M == this)
				return *this;

			// transfer data
			if (storage) delete[] storage;
			storage = M.storage;
			M.storage = nullptr;

			rows = M.rows;
			columns = M.columns;
			default_value = M.default_value;

			return *this;
		}
		T& operator[](unsigned int index)
		{
			return storage[index];
		}
		T& operator()(const unsigned int& row, const unsigned int& column)
		{
			return storage[row * columns + column];
		}

		// -- static functions -- //
	public:
		static matrix<T> Add(const matrix<T>& M1, const matrix<T>& M2)
		{
			matrix<T> Result = M1;
			Result += M2;
			return Result;
		}
		static matrix<T> Substract(const matrix<T>& M1, const matrix<T>& M2)
		{
			matrix<T> Result = M1;
			Result -= M2;
			return Result;
		}
		static matrix<T> DotProduct(const matrix<T>& M1, const matrix<T>& M2)
		{
			if ((M1.columns == M2.rows))
			{
				// create result matrix
				matrix<T> Result(M1.rows, M2.columns, M1.default_value);

				// do multiplication
				T sum = (T)0u;
				for (unsigned int i = 0; i < M1.rows; i++)
				{
					for (unsigned int j = 0; j < M2.columns; j++)
					{
						for (unsigned int k = 0; k < M1.columns; k++)
						{
							sum += M1.Value(i, k) * M2.Value(k, j);
						}
						Result.Value(i, j) = sum;
						sum = (T)0.0;
					}
				}

				// return result matrix
				return Result;
			}
			return M1;
		}
		static matrix<T> HadamardProduct(const matrix<T>& M1, const matrix<T>& M2)
		{
			if (M1.rows == M2.rows && M1.columns == M2.columns)
			{
				matrix<T> Result(M1.rows, M1.columns, M1.default_value);

				for (unsigned int i = 0; i < M1.rows; i++)
				{
					for (unsigned int j = 0; j < M1.columns; j++)
					{
						Result.Value(i, j) = M1.Value(i, j) * M2.Value(i, j);
					}
				}

				return Result;
			}
			return M1;
		}


		// -- methods -- //
	public:
		void Add(const matrix<T>& M)
		{
			*this += M;
		}
		void Substract(const matrix<T>& M)
		{
			*this -= M;
		}
		void DotProduct(const matrix<T>& M)
		{
			*this = matrix::DotProduct(*this, M);
		}
		void HadamardProduct(const matrix<T>& M)
		{
			if (this->rows == M.rows && this->columns == M.columns)
			{
				for (unsigned int i = 0; i < this->rows; i++)
				{
					for (unsigned int j = 0; j < this->columns; j++)
					{
						this->Value(i, j) *= M.Value(i, j);
					}
				}
			}
		}
		void Transpose()
		{
			// transpose matrix to new storage
			T *storage_copy = new T[rows * columns];
			for (unsigned int i = 0; i < rows; i++)
			{
				for (unsigned int j = 0; j < columns; j++)
				{
					storage_copy[j * rows + i] = storage[i * columns + j];
				}
			}
			delete[] storage;
			storage = storage_copy;

			// swap rows and columns
			unsigned int temp = rows;
			rows = columns;
			columns = temp;
		}
		T Trace()
		{
			if (rows == columns)
			{
				T sum = (T)0.0;
				for (unsigned int i = 0; i < rows; i++)
				{
					sum += Value(i, i);
				}
			}
			return 0.0;
		}
		void MakeIdentity()
		{
			if (rows == columns)
			{
				for (unsigned int i = 0; i < rows; i++)
				{
					for (unsigned int j = 0; j < columns; j++)
					{
						if (i == j) Value(i, j) = 0.0;
						else		Value(i, j) = 1.0;
					}
				}
			}
		}


		// -- getters and setters -- //
	public:
		T& Value(unsigned int row, unsigned int column)
		{
			return storage[row * columns + column];
		}
		const T& Value(unsigned int row, unsigned int column) const
		{
			return storage[row * columns + column];
		}
		void Value(unsigned int row, unsigned int column, const T& value)
		{
			Value(row, column) = value;
		}

		unsigned int GetRows()
		{
			return rows;
		}
		unsigned int GetRows() const
		{
			return rows;
		}
		unsigned int GetColumns()
		{
			return columns;
		}
		unsigned int GetColumns() const
		{
			return columns;
		}

		T DefaultValue()
		{
			return default_value;
		}
		const T DefaultValue() const
		{
			return default_value;
		}
		void DefaultValue(T new_value)
		{
			default_value = new_value;
		}
	};
}

#endif // !MATRIX_H