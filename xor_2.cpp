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
    vector<matrix> gradients_w;
    vector<matrix>gradients_b;
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

void gradients(matrix actual, matrix in)
{
    vector<matrix> delta(weights.size());
    gradients_w.assign(weights.size(), matrix(1,1));  // pre-sized, placeholder shape, overwritten below
    gradients_b.assign(weights.size(), matrix(1,1));

    for (int i = weights.size()-1; i >= 0; i--)
    {
        matrix ones(1, activations[i].cols);
        for (int c = 0; c < ones.cols; c++) ones.mat[0][c] = 1;

        matrix deriv = activations[i].hadamard(ones.subtract(activations[i]));

        if (i == weights.size()-1)
        {
            matrix error = activations[i].subtract(actual);
            delta[i] = error.hadamard(deriv);
        }
        else
        {
            delta[i] = delta[i+1].multiply(weights[i+1].transpose()).hadamard(deriv);
        }

        matrix prev_activation = (i == 0) ? in : activations[i-1];
        gradients_w[i] = prev_activation.transpose().multiply(delta[i]);
        gradients_b[i] = delta[i];
    }
}
void update(double lr)
{
    

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