#include<iostream>
#include<cmath>
#include<vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
class brain{
    public:
    float dw5,dw6,db3,dw1,dw2,dw3,dw4,db1,db2;
    vector<vector<float>>cells;
    vector<float> z = vector<float>(3);
    vector<float> a = vector<float>(3);
    float cost;
    float lastcost;
    float delta3;
    float lr = 0.55f;

    brain(){
        cells = vector<vector<float>>(3, vector<float>(3));

        ifstream fin("xor.nn");

    if(fin)
    {
        fin.close();
        loadModel("xor.nn");
    }
    else
    {
        initializeModel();
        saveModel("xor.nn");
    }

    }

    double sigmoid(double x) 
    {
    return 1.0 / (1.0 + exp(-x));
    }


    void initializeModel()
{
    srand(time(0));

    cells = vector<vector<float>>(3, vector<float>(3));

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            float r = (float)rand() / RAND_MAX;   // 0 to 1
            cells[i][j] = r * 2.0f - 1.0f;        // -1 to 1
        }
    }
}


void outputGradients(float actual,float x, float y)
{
    delta3 = (a[2] - actual) * (a[2] * (1 - a[2]));

dw5 = delta3 * a[0];
dw6 = delta3 * a[1];
db3 = delta3;

float delta1 = delta3 * cells[2][0] * a[0] * (1-a[0]);
float delta2 = delta3 * cells[2][1] * a[1] * (1-a[1]);

dw1 = delta1 * x;
dw2 = delta1 * y;
db1 = delta1;

dw3 = delta2 * x;
dw4 = delta2 * y;
db2 = delta2;
   
}


void gradientDescent()
    {
   cells[2][0] -= lr * dw5;
   cells[2][1] -= lr * dw6;
   cells[2][2] -= lr * db3;
   cells[0][0] -= lr * dw1;
   cells[0][1] -= lr * dw2;
   cells[0][2] -= lr * db1;
   cells[1][0] -= lr * dw3;
   cells[1][1] -= lr * dw4;
   cells[1][2] -= lr * db2;

    }
    void saveModel(string filename)
{
    ofstream fout(filename);

    if(!fout)
    {
        cout<<"Unable to create model file.\n";
        return;
    }

    fout<<"LearningRate\n";
    fout<<lr<<"\n\n";

    fout<<"HiddenNeuron1\n";
    fout<<"w1 "<<cells[0][0]<<'\n';
    fout<<"w2 "<<cells[0][1]<<'\n';
    fout<<"b1 "<<cells[0][2]<<"\n\n";

    fout<<"HiddenNeuron2\n";
    fout<<"w3 "<<cells[1][0]<<'\n';
    fout<<"w4 "<<cells[1][1]<<'\n';
    fout<<"b2 "<<cells[1][2]<<"\n\n";

    fout<<"OutputNeuron\n";
    fout<<"w5 "<<cells[2][0]<<'\n';
    fout<<"w6 "<<cells[2][1]<<'\n';
    fout<<"b3 "<<cells[2][2]<<'\n';

    fout.close();
}
void loadModel(string filename)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout<<"Model file not found.\n";
        return;
    }

    string temp;

    fin>>temp;
    fin>>lr;

    fin>>temp;

    fin>>temp>>cells[0][0];
    fin>>temp>>cells[0][1];
    fin>>temp>>cells[0][2];

    fin>>temp;

    fin>>temp>>cells[1][0];
    fin>>temp>>cells[1][1];
    fin>>temp>>cells[1][2];

    fin>>temp;

    fin>>temp>>cells[2][0];
    fin>>temp>>cells[2][1];
    fin>>temp>>cells[2][2];

    fin.close();
}

    float neuron(float x, float y)
    {
        vector<float>cal(3);
        int i = 0;
        for(i = 0;i<2;i++)
        {
            z[i] = cells[i][0]*x+cells[i][1]*y+cells[i][2];
            a[i]=sigmoid(z[i]);
        }
        z[i]=cells[i][0]*a[0]+cells[i][1]*a[1]+cells[i][2];
        a[i]=sigmoid(z[i]);
        return a[i];
    }
    float costing(float val,float ans)
    {
        float c =(val-ans);
        return c*c*0.5;
    }
    void train(float x, float y, float actual)
    {
        float pred = neuron(x, y);
        lastcost = costing(pred,actual);
        outputGradients(actual,x,y);
        gradientDescent();
    }
};

int main(){
    brain b;
    for(int epoch = 0; epoch < 10001; epoch++)
  {
    b.train(0,0,0);

    b.train(0,1,1);

    b.train(1,0,1);

    b.train(1,1,0);

    if(epoch % 1000 == 0)
    {
        cout << "Epoch: " << epoch << endl;
        cout << "Cost: " << b.lastcost << endl;
    }
    
   }
   b.saveModel("xor.nn");
   cout<<"\nPredictions\n";
   cout<<"1 and 0 "<<b.neuron(1,0)<<endl;
   cout<<"0 and 1 "<<b.neuron(0,1)<<endl;
   cout<<"0 and 0 "<<b.neuron(0,0)<<endl;
   cout<<"1 and 1 "<<b.neuron(1,1)<<endl;

    return 0;
}
