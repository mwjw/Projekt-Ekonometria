#include <vcl.h>
class matrix {
      int m; //rows number
      int n; //columns number
      double a[50][50]; //matrix as a class field
public:
       //constructors:
       matrix() {}
       matrix(int mm); //square matrix
       matrix(int mm,int nn); //rectangular matrix
       matrix(int mm,double b[][50]); //square matrix with 2d table
       matrix(int mm,int nn,double b[][50]); //rectangular matrix with 2d table
       //methods:
       // - operator overloading
       double &operator()(int rowIndex,int colIndex);//matrix element A(rowI,colI)
       matrix operator+(matrix X); //matrix addition
       matrix operator+(double f); //add to each matrix element double number
       void operator+=(matrix X); //A+=X, which means A=A+X
       void operator+=(double f); //A+=f, which means A=A+f
       matrix operator*(matrix X); //matrix multiplicity
       matrix operator*(double f); //multiply each matrix element by double number 
       matrix operator-(matrix X); //matrix subtraction
       matrix operator-(double f); //subtract double number from each matrix element
       matrix operator-(void); //opposite matrix
       void operator-=(matrix X); //A-=X, which means A=A-X
       void operator-=(double f); //A-=f, whioch means A=A-f
       
       // - standard matrix operatoions:
       int rows() {return m;} //number of rows in matrix
       int cols() {return n;} //number of columns in matrix
       void setRows(int mm) {m=mm;} //set number of rows
       void setCols(int nn) {n=nn;} //set number of columns
       matrix transpose(void); //return transposed matrix X
       matrix submatrix(int row1,int row2,int col1,int col2); //return submatrix with data
                                                              //from rows row1:2, col1:2
       matrix ludcmp(int *indx,double *d); //Given a square matrix a, return LU decomposition
                                           //of a, indx (vector of indexes), d=+-1 
                                           //(see www.nr.com for more informations)
       void lubksb(int *indx,matrix *b);//Solve set of linear equations, indx is result of 
                                       //ludcmp, solution is stored in vector b
       matrix solve(matrix b); //solve set of linear equations Ax=b, return solution
       matrix inverse(void); //inverse matrix
       double det(void); //determinant of a matrix                                                                                                                                                                                                                      
       double wart(int i,int j);
       void setwart(double w,int i,int j);
       AnsiString wypisz(AnsiString nazwa);
       AnsiString wypisz(AnsiString nazwa,int row,int col);
        AnsiString wypisz(AnsiString nazwa,int srow,int row,int scol,int col);
};
