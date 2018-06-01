#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(){
    // STAŁE
    const int N = 100;
    int pchelki[2*N];
    int tmax = 1000;
    double srednioPchel[tmax];

    //
    for (int i = 0; i < tmax; i++){
        srednioPchel[i] = 0;
    }

    int ileParPsow = 1000;
    fstream plik;


    //
    for (int ilePar = 1; ilePar <= ileParPsow; ilePar++){
        // 
        for(int i = 0; i < 2*N; i++){
            pchelki[i] = 1;
        }
        
        // 
            
        int losowa;
        int mu, m;
        mu = 0;
        double SBN;     //cos z entropią i Boltzmanem
        // plik.open("wynik.txt",fstream::out);

        //
        for(int i = 1; i < 2*N; i++){
            m = mu - N;
            SBN = 2*N*log(2*N) - (N+m)*log(N+m) - (N-m)*log(N-m);
        }

        // 
        for(int t = 1; t < tmax; t++){
            losowa = rand()%(2*N);
            if(pchelki[losowa] == 0){
                pchelki[losowa] = 1;
            }else{
                pchelki[losowa] = 0;
            }
            mu = 0;

            // ilość pcheł
            for(int i = 0; i < 2*N; i++){
                mu += pchelki[i];
            }

            // 
            m = mu - N;
            SBN = 2*N*log(2*N) - (N+m)*log(N+m) - (N-m)*log(N-m);
            // cout << t << "\t" << m << "\t" << SBN/(2*N) << "\t" << endl;
            // plik << t << "\t" << m << "\t" << SBN/(2*N) << "\t" << endl;
            srednioPchel[t] += (double)m/(double)ileParPsow;
        }
    }

    plik.open("wynik2.txt",fstream::out);
    for(int t = 0; t < tmax; t++){
        plik << t << "\t" << srednioPchel[t] << endl; 
    }
    plik.close();
    return 0;
}
