#include<iostream>
#include<cmath>
using namespace std;

int main() {

	 //Input Data

	        cout<<"\n\nInput number of variables..";
        	int n;
   		cin>>n;
	        double x[n];
        	int ER;
	        int c;
        	cout<<"\n\nInput number of constraint equations..";
	        cin>>c;

        	//total elements
	        int t=n+c;

        	double C[c][t+1]; //={0};
	        cout<<"\n\nInput the constrait equations";
        	for (int i=0; i<c; i++){
	                for(int j=0; j<t+1; j++){
        	                cin>>C[i][j];
	                }
        	}

	        double Zc[t]; //={0};
        	cout<<"\n\nInput coefficients of variables in objective function..";
	        for(int i = 0; i<t; i++) {
        	        cin>>Zc[i];
                	}


        //Verification of the input data

	        cout<<"\n\nThe Objective Function is Z = ";
       
                	for (int i=0; i<n; i++) {
                        	cout<<Zc[i]<<"x"<<i+1<<"+";
                        	}



	                for (int i=n; i<t; i++) {
        	                cout<<Zc[i]<<"S"<<i-n+1;
                	         if (i<t-1){ cout<<"+"; }

                	}


	//Contition for iteration

		double Zsol[t+1];	//Zj array
		double ratio[c];	//Ratio array
 		double Bv[c];		//basic values array
		

		for (int i=0; i<c; i++){
			Bv[i]=0;
		}

		double Zfin[t];
		double Zfin_max;
		Zfin_max = 1;
		int Ce;

		double ratio_min;
		int Re;
	

		int iter;
		iter = 1;

		
			//compute Zj

				cout<<"\n\nZj = ";
				for(int j=0; j<=t; j++){
					for(int i=0; i<c; i++){
						Zsol[j] += Bv[i]*C[i][j];		
					}
					cout<<Zsol[j]<<"\t";
				}


			//compute Cj-Zj	

				cout<<"\n\nCj - Zj = ";
				for(int i=0; i<t; i++){
					Zfin[i] = Zc[i] - Zsol[i];
					//cout<<Zfin<<"\t";
				}


			//Compute (Cj - Zj)max == Zfin_max

				Zfin_max = Zfin[0];
				Ce = 0;
				for(int i=1; i<t; i++){
					if( Zfin_max < Zfin[i]) {
						Zfin_max = Zfin[i] ;
						Ce=i;
					}

					else {
						cout<<"\n\nChosing nex Cj-Zj";
					}
				}

				cout<<"\n\n\nMaximum value of Cj - Zj = "<<Zfin_max<<"\nEntering Column is "<<Ce+1;



			//compute Ratio

				cout<<"\n\n\nRatio array is R = ";
				for(int i=0; i<c; i++){
					ratio[i] = C[i][t]/C[i][Ce];
					cout<<ratio[i]<<"\t";
				}


			//Compute min Ratio

				cout<<"\n\n\nMinimum value f ratio is ";
				ratio_min = 2500;
				Re = 0;

				for (int i=0; i<c; i++){
					if(ratio_min > fabs(ratio[i]) ){
						ratio_min = fabs(ratio[i]) ;
						Re = i;
					}
				}

				cout<<ratio_min<<"\n\n\nExiting row is "<<Re+1;


		double Iter_C[c][t+1];
		


		while(Zfin_max>0){

			cout<<"\n\n\nIteration "<<iter;

			//Entering column and exiting row
			cout<<"\n\nEntering column is "<<Ce+1<<"\nVariable coeff is "<<Zc[Ce]<<"\n\nExiting row is "<<Re+1<<"\nVariable coeff is "<<Bv[Re];
			cout<<"\n\nKeyElement is "<<C[Re][Ce];
			Bv[Re] = Zc[Ce];


			//Calculation for  rows
			//	cout<<"\n\nEntering row coeff are ";
				cout<<"\n\nFor entering row, old values and new values  are ";

				for(int j=0; j<n+c+1; j++){
					cout<<"\t"<<C[Re][j];
					Iter_C[Re][j] = C[Re][j] / C[Re][Ce];
					cout<<"\t"<<Iter_C[Re][j];
				}
		
			//	cout<<"\n\nOther columns coeff are ";	
				cout<<"\n\nFor other rows, old values and new values  are ";
				for(int i=0; i<c; i++) {
					if (i != Re){
						for(int j=0; j<=t; j++){
							cout<<"\t"<<C[i][j];
							double a = C[i][Ce] * C[Re][j] / C[Re][Ce];
							Iter_C[i][j] = C[i][j] - a;
							cout<<"\t"<<Iter_C[i][j];
						}
					cout<<"\n";
					}
				}


			
			//compute Zj

				cout<<"\n\n\nZj = ";

				//re-assigning Zj to 0
				for(int i=0; i<=t; i++){
					Zsol[i] = 0;
				}

				for(int j=0; j<=t; j++){
					for(int i=0; i<c; i++){
						Zsol[j] += Bv[i]*Iter_C[i][j];		
					}
					cout<<Zsol[j]<<"\t";
				}


			//compute Cj-Zj	

				cout<<"\n\n\nCj - Zj = ";
				for(int i=0; i<t; i++){
					Zfin[i] = Zc[i] - Zsol[i];
					//cout<<Zfin<<"\t";
				}


			//Compute (Cj - Zj)max == Zfin_max

				Zfin_max = Zfin[0];
				Ce = 0;
				for(int i=1; i<t; i++){
					if(Zfin_max<Zfin[i]){
						Zfin_max=Zfin[i];
						Ce=i;
					}

					else {
					//	cout<<"\n\nChosing nex Cj-Zj";
					}
				}

				cout<<"\n\n\nMaximum value of Cj - Zj = "<<Zfin_max<<"\nEntering Column is "<<Ce+1;

				if(Zfin_max<0) {
					goto end;
				}
		


				

			//compute Ratio

				cout<<"\n\n\nRatio array is R = ";
				for(int i=0; i<c; i++){
					ratio[i] = Iter_C[i][t]/Iter_C[i][Ce];
					cout<<ratio[i]<<"\t";
				}


			//Compute min Ratio

				cout<<"\n\n\nMinimum value f ratio is ";
				ratio_min =2500;
				Re = 0;

				for (int i=0; i<c; i++){
					if(ratio_min > fabs(ratio[i]) ){
						ratio_min = fabs(ratio[i]);
						Re = i;
					}
				}

				cout<<ratio_min<<"\n\n\nExiting row is "<<Re+1;


			for(int i=0; i<c; i++){
				for(int j=0; j<=t; j++){
					C[i][j] = Iter_C[i][j];
				}
			}

		iter++;

		end:cout<<"\n\nPlease check ";
	}

	cout<<"\n\n\n";

	for(int i=0; i<c; i++){
		for(int j=0; j<=t; j++){
			cout<<Iter_C[i][j]<<"\t";
		}
	cout<<"\n";
	}


	
	cout<<"\nValues of solution are "<<Iter_C[0][t]<<" "<<Iter_C[1][t]<<" "<<" "<<Zsol[t];
	
	
	cout<<"\n Solution is optimal"<<endl;

	return 0;
 }
