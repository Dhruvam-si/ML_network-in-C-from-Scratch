#include<iostream>
#include"matrix.h"
#include<stdexcept>
#include<vector>
#include<ctime>
#include<cmath>
#include<cstdlib>

using namespace std;
double sigmoid(double x) 
 {
    return 1.0 / (1.0 + exp(-x));
 }
class Network
{
    public:
    vector<matrix>weights;
    vector<matrix>biases;
    vector<matrix>z;
    vector<matrix>activations;
     Network(vector<int>layer_sizes)
     {
        int layer = 0;
        int neurons_in = layer_sizes[layer];       // how many values feed into this layer
        int neurons_out = layer_sizes[layer+1];    // how many neurons this layer computes
        for (layer = 0; layer < layer_sizes.size() - 1; layer++) 
        {

         matrix W(layer_sizes[layer], layer_sizes[layer+1]);
         for (int r = 0; r < W.rows; r++) 
         {
          for (int c = 0; c < W.cols; c++) 
           {
            float rnd = (float)rand() / RAND_MAX;
            W.mat[r][c] = rnd * 2.0f - 1.0f;
            }
        }
        weights.push_back(W);
        matrix b(1, layer_sizes[layer+1]);
         for (int c = 0; c < b.cols; c++)
        {
           float rnd = (float)rand() / RAND_MAX;
           b.mat[0][c] = rnd * 2.0f - 1.0f;
        }
        biases.push_back(b);
   }
}
 matrix forward(double x, double y)
{
    matrix current(1,2);
    current.mat[0][0]=x;
    current.mat[0][1]=y;
    for (int layer = 0; layer < weights.size(); layer++)
    {
        matrix z_layer = current.multiply(weights[layer]).add(biases[layer]);
        z.push_back(z_layer);
        current = z_layer.applyFunctions(sigmoid);
        activations.push_back(current);

    }
    return current;

}

double costCal(matrix output,matrix actual)
{
    double n = 0;
    double summation = 0;
    for(int i = 0;i<output.rows;i++)
    {
        for(int j = 0;j<output.cols;j++)
        {
            summation = summation + (0.5*(output.mat[i][j]-actual.mat[i][j])*(output.mat[i][j]-actual.mat[i][j]));
            n++;
        }

    }
    return (summation/n);
}

void gradients(matrix actual)
{
    matrix one(1,1);
    one.mat[0][0]=1;
    matrix error = activations[1].subtract(actual);           // (a - actual)
    matrix one_minus_a = one.subtract(activations[1]);         // (1 - a)
    matrix deriv = activations[1].hadamard(one_minus_a);        // a*(1-a)
    matrix delta_output = error.hadamard(deriv);                // (a-actual) * a*(1-a)
}
matrix ret()
    {
     return weights[0];
    }
    
};
int main(){
srand(time(0));  
vector<int>layers{2,2,1};
Network n(layers);
matrix c = n.ret();
 for(int i =0;i<c.rows;i++)
 {
    for(int j = 0;j<c.cols;j++)
     {
         cout<<c.mat[i][j]<<endl;
     }
 }

return 0;
}