#include <iostream>
#include "TQueue.cpp"
#include "TJobStream.h"
#include "TProc.h"
using namespace std;

int main()
{
    int queue_size=20;
    int broj_taktova=100;
    double intenzitet_poslova=0.7;
    double jacina_poslova=0.5;
    double sposobnost_procesora=0.2;
    int broj_zauzetih_taktova=0;

    cout<<"Enter the size of Queue: ";
    cin >> queue_size;

    cout<<"Enter Number of tactssssss: ";
    cin >> broj_taktova;

    cout<<"Enter the intensity of flow: ";
    cin >> intenzitet_poslova;

    cout<<"Enter the capabilty of processor: ";
    cin >>sposobnost_procesora;

    TQueue q(queue_size);	// velicina Queue-a
    TJobStream jbs(intenzitet_poslova);
    TProc procesor(sposobnost_procesora);

    int t;
    int moj_posao;
    int sledeci_posao;
    int predatih_poslova=0;
    int odbijenih_poslova=0;
    int rez_put;
    for (t=0;t<broj_taktova;t++)
    {
        moj_posao=jbs.GetNewJob();
        cout<<"My Job="<<moj_posao<<endl;
        rez_put=-2;
        if (moj_posao>0)
            rez_put=q.Put(moj_posao);
        if (rez_put==0) predatih_poslova+=1;
        else if (rez_put==-2) {}
        else  odbijenih_poslova+=1; //jobs rejected

        if (1==procesor.IsProcBusy())
        {
            ++broj_zauzetih_taktova;
            cout<<"Tact busy"<<endl;
        }
        else
        {
            sledeci_posao=q.Get();
            if (sledeci_posao>0)
            {
                procesor.RunNewJob(sledeci_posao);
                cout<<"New Job"<<endl;
            }
            else
            {
                cout<<"No jobs"<<endl;

            }
        }
//		q.print();
    }
    cout<< "Number of busy tacts: " <<broj_zauzetih_taktova<<endl;
    cout<< "Percentage of busy tacts"<< 100*(double) broj_zauzetih_taktova/broj_taktova<<endl;
    cout<< "Left on queue="<<q.QSize()<<endl;
    cout<< "Jobs: "<< predatih_poslova + odbijenih_poslova<<endl;
    cout<< "Given: "<<predatih_poslova<<endl;
    cout<< "Rejected: "<<odbijenih_poslova<<endl;

/*
 }
