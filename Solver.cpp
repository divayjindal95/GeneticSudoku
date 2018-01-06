#include<iostream>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<list>
#include<cmath>
using namespace std;

void initialize_pop(int **sudoku , int ***init_pop , int n);

void cross_over(int ***init_pop  , int ***final_pop  , int n );

void mutation(int ***final_pop , int n ,int **blueprint);

int elitism(int ***final_pop , int n , int ***init_pop );

int f(int gen , int i ,int j , int k , int l , int ***final_pop);

void quickSort(int arr[], int l, int h , int b[]);

int partition (int arr[], int l, int h,int b[]);

time_t t1;

int rowf=0 , columnf=0 , squaref=0 , fitness=0;

int main(){
    int i , j , k=0 , flag=0;
    int n=9;
    //cout<<rand();

    int **sudoku;
    sudoku=new int*[n];
    for(i=0;i<n;i++)
        sudoku[i]=new int[n];

    int **blueprint;
    blueprint=new int*[n];
    for(i=0;i<n;i++)
        blueprint[i]=new int[n];

    int ***init_pop;
    init_pop = new int**[n];
    for( i=0; i<n; i++){
        init_pop[i]= new int*[n];
        for( j=0; j<n; j++)
            init_pop[i][j] = new int[10*n];
    }

    int ***init_pop2;
    init_pop2 = new int**[n];
    for( i=0; i<n; i++){
        init_pop2[i]= new int*[n];
        for( j=0; j<n; j++)
            init_pop2[i][j] = new int[10*n];
    }

    int ***final_pop;
    final_pop = new int**[n];
    for( i=0; i<n; i++){
        final_pop[i]= new int*[n];
        for( j=0; j<n; j++)
            final_pop[i][j] = new int[20*n];
    }


    int level;


    cout<<"                 This is the program to solve the given Sudoku."<<"\n"<<"\n";
    cout << "\t \"1\" for EASY Level.\n";
    cout << "\t \"2\" for MEDIUM Level.\n";
    cout << "\t \"3\" for HARD Level.\n ";
    cout << "\t \"4\" for EXTRA Problem.\n ";
    cin >> level;

  // Read sudoku from a file
   ifstream readsudoku;

   switch (level)
   {
     case 1 :
        readsudoku.open("Easy.txt", ios::in);
           for( i=0; i<n; i++)
           {
             for(j=0; j<n; j++)
               {
                 readsudoku>>*(*(sudoku+j)+i) ;
               }
           }
           break;

     case 2 :
          readsudoku.open("Medium.txt", ios::in);
           for( i=0; i<n; i++)
           {
             for( j=0; j<n; j++)
               {
                 readsudoku>>*(*(sudoku+j)+i) ;
               }
           }
           break;

      case 3 :
          readsudoku.open("Hard.txt", ios::in);
           for( i=0; i<n; i++)
           {
             for( j=0; j<n; j++)
               {
                 readsudoku>>*(*(sudoku+j)+i) ;
               }
           }
           break;

       case 4 :
          readsudoku.open("Extra.txt", ios::in);
           for( i=0; i<n; i++)
           {
             for( j=0; j<n; j++)
               {
                 readsudoku>>*(*(sudoku+j)+i) ;
               }
           }
           break;

      default :
         readsudoku.open("Extra.txt", ios::in);
            for( i=0; i<n; i++)
            {
              for( j=0; j<n; j++)
                {
                  readsudoku>>*(*(sudoku+j)+i) ;
                }
            }

     }// End of switch.

     readsudoku.close();

    /*for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>sudoku[j][i];*/



    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(sudoku[j][i]!=0)
                blueprint[j][i]=1;

    for(i=0;i<5000;i++){
        if(i==0)
            initialize_pop(sudoku , init_pop  ,  n);
        cross_over(init_pop , final_pop ,n);
        mutation(final_pop , n , blueprint);
        flag=elitism(final_pop , n , init_pop);
        cout<<"   generation   "<<i<<"\n";
        if(flag==1){
            cout<<"generation"<<i<"\n";
            break;
        }
    }


    /*for(j=0;j<n;j++){
            for(k=0;k<n;k++)
                cout<<init_pop[k][j][10*n-1]<<" ";
            cout<<"\n";
        }
*/


}


/************************************************************************************************************/
/************************************************************************************************************/



void initialize_pop(int **sudoku , int ***init_pop , int n){
    time(&t1);
    srand(t1);
    int i , j , k;
    int dist_row[10] , dist_variable , dist_row_element;
    dist_row[0]=1;
    for(i=0;i<10*n;i++){

        for(j=0;j<n;j++){

            dist_row[0]=1;
            for(k=0;k<=n;k++)
                dist_row[k]=0;

            for(k=0;k<n;k++){
                if(sudoku[k][j]!=0){
                    dist_row_element=sudoku[k][j];
                    dist_row[dist_row_element]=1;
                }
            }
            //cout<<"hello divay ";
            //for(k=0;k<=n;k++)
              //  cout<<dist_row[k]<<" ";
            for(k=0;k<n;k++){

                if(sudoku[k][j]==0){
                    dist_variable=rand()%9+1;
                    while(dist_row[dist_variable]!=0)
                        dist_variable=rand()%9+1;
                    init_pop[k][j][i]=dist_variable;
                    dist_row[dist_variable]=1;
                }
                else
                    init_pop[k][j][i]=sudoku[k][j];

            }

        }

    }
    /*for(i=0;i<10*n;i++){                                  //Prints the matrices
        for(j=0;j<n;j++){
            for(k=0;k<n;k++)
                cout<<init_pop[k][j][i]<<" ";
            cout<<"\n";
        }
        cout<<"\n";
    }*/
}


/*****************************************************************************************************/
/*****************************************************************************************************/


void cross_over(int ***init_pop  , int ***final_pop  , int n ){
    time(&t1);
    srand(t1);
    float cross_prob;
    int i , j , k ;

    for(i=0;i<10*n;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
                final_pop[k][j][i]=init_pop[k][j][i];

    for(i=10*n;i<20*n;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
                final_pop[k][j][i]=init_pop[k][j][i-10*n];


    for(i=10*n;i<20*n;i+=2){
        cross_prob=(rand()%100)/100;
        if(cross_prob<=0.8){
            for(j=0;j<n;j+=2){
                for(k=0;k<n;k++)
                    swap(final_pop[k][j][i],final_pop[k][j][i+1]);
            }
        }
    }
}


/*******************************************************************************************/
/*******************************************************************************************/


void swap(int *a , int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void mutation(int ***final_pop , int n  , int **blueprint){
    time(&t1);
    srand(t1);
    int i , j , k , row , col1 , col2;
    float mut_prob;
    for(i=10*n;i<20*n;i++){
        //for(j=0;j<n;j++){
            mut_prob=(rand()%100)/100;
            if(mut_prob<=0.1){
                row=rand()%9;
                col1=rand()%9;
                col2=rand()%9;
                while(blueprint[col1][row]!=0||blueprint[col2][row]!=0){
                    col1=rand()%9;
                    col2=rand()%9;
                }
                swap(final_pop[col1][row][i],final_pop[col2][row][i]);

        }

    }
}

int elitism(int ***final_pop , int n  , int ***init_pop){
    int i , j , k, l;
    int arr_for_sort[20*n] , array_index[20*n] , z ,q ,r , s;


    for(i=0;i<20*n;i++){
        array_index[i]=i;
        arr_for_sort[i]=0;
    }
/*************************************************         ROW FITNESS IS ALWAYS 324      ******************************************************/
    for(i=0;i<20*n;i++){
        /*rowf=0;
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                for(l=k;l<n;l++){
                        rowf+=f(i,j,k,j,l , final_pop);
                        //fitness++;
                }
            }
        }*/
        arr_for_sort[i]+=324;

    }

/*****************************************************       ROW FITNESS FUNCTION          ****************************************************/

    //COLUMN FITNESS
    for(i=0;i<20*n;i++){
        columnf=0;
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                for(l=k;l<n;l++){
                        columnf+=f(i,k,j,l,j , final_pop);
                        //fitness++;
                }
            }
        }
        arr_for_sort[i]+=columnf;
        //cout<<columnf<<"\n";
    }

    //SQUARE FITNESS
    for(i=0;i<20*n;i++){

        squaref=0;
        for(z=1;z<=n;z++){

            for(q=1;q<=sqrt(n);q++){

                for(j=1+(q-1)*sqrt(n);j<=q*sqrt(n)-1;j++){
                    for(l=j+1;l<=q*sqrt(n);l++)
                        squaref+=f(i,z-1,j-1,z-1,l-1,final_pop);
                }


                    for(r=1+(q-1)*sqrt(n);r<=q*sqrt(n);r++){
                        if(z%(int)sqrt(n)==0)
                            continue;
                        for(k=z+1;k<=z+sqrt(n)-z%(int)sqrt(n);k++){
                            for(s=1+(q-1)*sqrt(n);s<=q*sqrt(n);s++)
                                squaref+=f(i,z-1,r-1,k-1,s-1,final_pop);
                        }
                    }


            }
        }
        arr_for_sort[i]+=squaref;
        cout<<arr_for_sort[i]<<"\n";
        if(arr_for_sort[i]==972){
              for(j=0;j<n;j++){
                    for(k=0;k<n;k++)
                        cout<<final_pop[k][j][i]<<" ";
                    cout<<"\n";
              }
              return 1;
        }
    }


    quickSort(arr_for_sort,0,20*n-1,array_index);

    //for(i=10*n;i<20*n;i++)
       // cout<<arr_for_sort[i]<<"\n";

    for(i=0;i<10*n;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
                init_pop[k][j][i]=final_pop[k][j][array_index[i+10*n]];
    //cout<<"hello";
    //return init_pop;
}

int f(int gen , int i ,int j , int k , int l , int ***final_pop){
    if(final_pop[j][i][gen]==final_pop[l][k][gen])
        return 0;
    return 1;
}

int partition (int arr[], int l, int h,int b[])
{
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap(&arr[i], &arr[j]);
            swap(&b[i] , &b[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    swap(&b[i+1] , &b[h]);
    return (i + 1);
}

void quickSort(int arr[], int l, int h , int b[])
{
    if (l < h)
    {
        int p = partition(arr, l, h,b);
        quickSort(arr, l, p - 1 , b);
        quickSort(arr, p + 1, h,b);
    }
}
