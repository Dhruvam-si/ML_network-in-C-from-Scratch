#include<vector>
#include <stdexcept>

#ifndef MATRIX_H
#define MATRIX_H

 class matrix{
    public:
    std::vector<std::vector<double>> mat;
    int rows;
    int cols;
    
    matrix(int r,int c)
    {
      rows = r;
      cols = c;
      mat.resize(r,std::vector<double>(c,0.0));
    }
    matrix add(matrix other) {
    if (rows == other.rows && cols == other.cols) {
      int i = 0;
        matrix result(rows, cols);
        for(i=0;i<rows;i++){
         int j = 0;
         for(j=0;j<cols;j++){
       result.mat[i][j] = mat[i][j] + other.mat[i][j];
         }
       }
        return result;
    }
    else 
    {
        throw std::invalid_argument("Matrices must be the same size to add");
    }
}
matrix subtract(matrix other) {
    if (rows == other.rows && cols == other.cols) {
      int i = 0;
        matrix result(rows, cols);
        for(i=0;i<rows;i++){
         int j = 0;
         for(j=0;j<cols;j++){
       result.mat[i][j] = mat[i][j] - other.mat[i][j];
         }
       }
        return result;
    }
    else 
    {
        throw std::invalid_argument("Matrices must be the same size to subtract");
    }
}
matrix hadamard(matrix other) {
    if (rows == other.rows && cols == other.cols) {
      int i = 0;
        matrix result(rows, cols);
        for(i=0;i<rows;i++){
         int j = 0;
         for(j=0;j<cols;j++){
       result.mat[i][j] = mat[i][j] * other.mat[i][j];
         }
       }
        return result;
    }
    else 
    {
        throw std::invalid_argument("Matrices must be the same size to Multiply");
    }
}
matrix transpose() {
      int i = 0;
        matrix result(cols, rows);
        for(i=0;i<cols;i++){
         int j = 0;
         for(j=0;j<rows;j++){
       result.mat[i][j] = mat[j][i];
         }
       }
        return result;
}

matrix applyFunctions(double (*func) (double))
{
   matrix result(rows,cols);
   for(int i = 0;i<rows;i++){
      for(int j = 0;j<cols;j++){
         result.mat[i][j] = func(mat[i][j]);
      }
   }
   return result;
}

matrix multiply(matrix other){
  if(cols==other.rows)
   {
    matrix result(rows,other.cols);
    for(int i = 0; i<rows;i++){
      for(int j=0;j<other.cols;j++)
       {
        double iteration = 0;
        for(int k =0;k<cols;k++) //this works as cols of mat(*this) == other.rows we checked.
        {
        iteration = (mat[i][k]*other.mat[k][j]) + iteration;
        }
      result.mat[i][j]=iteration;
       }
   
    }
    return result;
  }
 else 
  {
  throw std::invalid_argument("Matrices must be the same size to Multiply");
  }
}

};
 #endif