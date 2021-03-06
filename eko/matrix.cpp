#include <iostream>
#include <math.h>

#include "matrix.h"
#define TINY 1.0e-20 //small number

using namespace std;

matrix::matrix(int mm)
{
   int i,j;
   
   m=mm;
   n=mm;
   for (i=0;i<mm;i++)
   for (j=0;j<mm;j++)
      a[i][j]=0;
}

matrix::matrix(int mm,int nn)
{
   int i,j;
   
   m=mm;
   n=nn;
   for (i=0;i<mm;i++)
   for (j=0;j<nn;j++)
      a[i][j]=0;
}

matrix::matrix(int mm,double b[][50])
{
   int i,j;
   
   m=mm;
   n=mm;
   for (i=0;i<mm;i++)
   for (j=0;j<mm;j++)
      a[i][j]=b[i][j];
}

matrix::matrix(int mm,int nn,double b[][50])
{
   int i,j;
   
   m=mm;
   n=nn;
   for (i=0;i<mm;i++)
   for (j=0;j<nn;j++)
      a[i][j]=b[i][j];
}

double & matrix::operator()(int rowIndex,int colIndex)
{
   return a[rowIndex][colIndex];
}

matrix matrix::operator+(matrix X)
{
   matrix sum;
   if (m==X.m && n==X.n)
   {
      sum.m=m;
      sum.n=n;
      for (int i=0;i<m;i++)
      for (int j=0;j<n;j++)
         sum.a[i][j]=a[i][j]+X.a[i][j];
   }
   else
   {
      cout<<"Error! Number of rows and number of columns in both matrixes have to be the same"<<endl;
      return sum;
   }
   return sum;
}

matrix matrix::operator+(double f)
{
   matrix sum(m,n,a);
   
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      sum.a[i][j]+=f;
   
   return sum;
}

void matrix::operator+=(matrix X)
{
   if (m==X.m && n==X.n)
      for (int i=0;i<m;i++)
      for (int j=0;j<n;j++)
         a[i][j]+=X.a[i][j];
   else
   {
      cout<<"Error! Number of rows and number of columns in both matrixes have to be the same"<<endl;
      return;
   }
}

void matrix::operator+=(double f)
{
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      a[i][j]+=f;
}

matrix matrix::operator*(matrix X)
{
  matrix multi;
  double f;
  if (n==X.m)
  {
     multi.m=m;
     multi.n=X.n;
     for (int i=0;i<m;i++)
     for (int j=0;j<X.n;j++)
     {
        f=0.0;
        for (int k=0;k<n;k++)
           f+=a[i][k]*X.a[k][j];
        multi.a[i][j]=f;
     }
  }
  else
  {
     cout<<"Error! Number of column in first matrix have to be the same as number of rows in second matrix"<<endl;
     return multi;
  }
  return multi;
}

matrix matrix::operator*(double f)
{
   matrix multi(m,n,a);
   
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      multi.a[i][j]*=f;
   return multi;
}

matrix matrix::operator-(matrix X)
{
   matrix sub;
   if (m==X.m && n==X.n)
   {
      sub.m=m;
      sub.n=n;
      for (int i=0;i<m;i++)
      for (int j=0;j<n;j++)
         sub.a[i][j]=a[i][j]+X.a[i][j];
   }
   else
   {
      cout<<"Error! Number of rows and number of columns in both matrixes have to be the same"<<endl;
      return sub;
   }
   return sub;
}


matrix matrix::operator-(double f)
{
   matrix sub(m,n,a);
   
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      sub.a[i][j]+=f;
   
   return sub;
}

matrix matrix::operator-(void)
{
   matrix opposite(m,n);
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      opposite.a[i][j]=-a[i][j];
   return opposite;
}

void matrix::operator-=(matrix X)
{
   if (m==X.m && n==X.n)
      for (int i=0;i<m;i++)
      for (int j=0;j<n;j++)
         a[i][j]-=X.a[i][j];
   else
   {
      cout<<"Error! Number of rows and number of columns in both matrixes have to be the same"<<endl;
      return;
   }
}

void matrix::operator-=(double f)
{
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      a[i][j]-=f;
}

matrix matrix::transpose(void)
{
   matrix aux(n,m);
   for (int i=0;i<m;i++)
   for (int j=0;j<n;j++)
      aux.a[j][i]=a[i][j];
   return aux;
}

matrix matrix::submatrix(int row1,int row2,int col1,int col2)
{
   matrix aux;
   if (row1>row2 || col1>col2 || row1<0 || row2>m-1 || col1<0 || col2>n-1)
   {
      cout<<"Error! Incorrect range"<<endl;
      return aux;
   }
   else
   {
      aux.m=row2-row1+1;
      aux.n=col2-col1+1;
      for (int i=row1;i<=row2;i++)
      for (int j=col1;j<=col2;j++)
         aux.a[i][j]=a[i][j];
   }
   return aux;
}

matrix matrix::ludcmp(int *indx,double *d)
{
   int i,imax,j,k;
   double big,dum,sum,temp;
   double *vv=new double[m];
   matrix aux(m,a);
   
   *d=1.0;
   for (i=1;i<=m;i++)
   {
      big=0.0;
      for (j=1;j<=m;j++)
         if ((temp=fabs(aux.a[i-1][j-1]))>big) big=temp;
      if (big==0.0)
      {
         cout<<"Error! singular matrix in ludcmp"<<endl;
         return aux;
      }
      vv[i-1]=1.0/big;
   }
   for (j=1;j<=m;j++)
   {
      for (i=1;i<j;i++)
      {
         sum=aux.a[i-1][j-1];
         for (k=1;k<i;k++)
            sum-=aux.a[i-1][k-1]*aux.a[k-1][j-1];
         aux.a[i-1][j-1]=sum;
      }
      big=0.0;
      for (i=j;i<=m;i++)
      {
         sum=aux.a[i-1][j-1];
         for (k=1;k<j;k++)
            sum-=aux.a[i-1][k-1]*aux.a[k-1][j-1];
         aux.a[i-1][j-1]=sum;
         if ((dum=vv[i-1]*fabs(sum))>=big)
         {
            big=dum;
            imax=i;
         }
      }  
      if (j!=imax)
      {
         for (k=1;k<=m;k++)
         {
            dum=aux.a[imax-1][k-1];
            aux.a[imax-1][k-1]=aux.a[j-1][k-1];
            aux.a[j-1][k-1]=dum;
         }
         *d=-(*d);
         vv[imax-1]=vv[j-1];
      }
      indx[j-1]=imax-1;
      if (aux.a[j-1][j-1]==0.0) aux.a[j-1][j-1]=TINY;
      if (j!=m)
      {
         dum=1.0/(aux.a[j-1][j-1]);
         for (i=j+1;i<=m;i++) aux.a[i-1][j-1]*=dum;
      }
   }      
                     
   delete vv;
   return aux; 
}

void matrix::lubksb(int *indx,matrix *b)
{
   int i,ii=0,ip,j;
   double sum;
   
   for (i=1;i<=m;i++)
   {
      ip=indx[i-1];
      sum=b->a[ip][0];
      b->a[ip][0]=b->a[i-1][0];
      if (ii)
         for (j=ii;j<=i-1;j++)
            sum-=a[i-1][j-1]*b->a[j-1][0];
      else
         if (sum) ii=i;
      b->a[i-1][0]=sum;
   }
   for (i=m;i>=1;i--)
   {
      sum=b->a[i-1][0];
      for (j=i+1;j<=m;j++)
         sum-=a[i-1][j-1]*b->a[j-1][0];
      b->a[i-1][0]=sum/a[i-1][i-1];
   }
}

matrix matrix::solve(matrix b)
{
   int *indx=new int[m];
   double d;
   matrix aux(m),x(m,1,b.a);
   
   aux=ludcmp(indx,&d);
   aux.lubksb(indx,&x);
   
   return x;
}

matrix matrix::inverse(void)
{
   int i,j,*indx=new int[m];
   double d;
   matrix col(m,1),aux(m),aux1(m);
   
   aux=ludcmp(indx,&d);
   for (j=1;j<=m;j++)
   {
      for (i=1;i<=m;i++) col.a[i-1][0]=0.0;
      col.a[j-1][0]=1.0;
      aux.lubksb(indx,&col);
      for (i=1;i<=m;i++)
         aux1.a[i-1][j-1]=col.a[i-1][0];
   }
   return aux1;
}

double matrix::det(void)
{
   double d;
   int i,*indx=new int[m];
   matrix aux(m);
   
   aux=ludcmp(indx,&d);
   for (i=1;i<=m;i++) d*=aux.a[i-1][i-1];
   
   return d;
}

 double matrix::wart(int i,int j){
       return a[i][j];
 }

  void matrix::setwart(double w,int i,int j){
        a[i][j] = w;
 }

 AnsiString matrix::wypisz(AnsiString nazwa){
 AnsiString t,t2;
 int i,j;
          t = nazwa;

          for (i=0;i<m;i++) //   kazdy wiersz
          {
                t+= t2.sprintf("\n");// nowy wiersz i tab
                for (j=0;j<n;j++) //dla kazdej kolumny
                {
                t+= t2.sprintf("%.3f",a[i][j]);
                }
          }
 return t;
 }

 AnsiString matrix::wypisz(AnsiString nazwa,int row,int col){
 AnsiString t,t2;
 int i,j;
          t = nazwa;

          for (i=0;i<row;i++) //   kazdy wiersz
          {
                t+= t2.sprintf("\n");// nowy wiersz i tab
                for (j=0;j<col;j++) //dla kazdej kolumny
                {
                t+= t2.sprintf("%.3f",a[i][j]);
                }
          }
 return t;
 }

 AnsiString matrix::wypisz(AnsiString nazwa,int srow,int row,int scol,int col){
 AnsiString t,t2;
 int i,j;
          t = nazwa;

          for (i=srow;i<row;i++) //   kazdy wiersz
          {
                t+= t2.sprintf("\n");// nowy wiersz i tab
                for (j=scol;j<col;j++) //dla kazdej kolumny
                {
                t+= t2.sprintf("%.3f",a[i][j]);
                }
          }
 return t;
 }
