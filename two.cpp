
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#define N	0.70

#ifndef NUMT
#define NUMT	3
#endif

#ifndef NUMNODES
#define NUMNODES	100
#endif

float Height( int, int );	// function prototype

int main( int argc, char *argv[ ] )
{

	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though)
    omp_set_num_threads( NUMT );	// set the number of threads to use in parallelizing the for-loop:`
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );
	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for loop and a reduction:
    float area = 0.;
    double time1 =0;
    double time0 = 0;
    double maxTime = 9999;
    float maxArea=0;
    for(int j = 0; j< 10; j++){
    area = 0;
    time0 = omp_get_wtime( );
    #pragma omp parallel for default(none)  shared( fullTileArea) reduction(+:area) 
    for( int i = 0; i < NUMNODES*NUMNODES; i++ )
    {
        int iu = i % NUMNODES;
        int iv = i / NUMNODES;
        float z = Height( iu, iv );
        if(iu == 0 || iu == NUMNODES - 1 || iv == 0 || iv == NUMNODES - 1){
            if(
                ((iu == 0) && (iv == 0)) 
                || ((iu == 0) && (iv == (NUMNODES - 1)))
                || ((iu == (NUMNODES - 1)) && (iv == 0))
                || ((NUMNODES - 1) && (iv == NUMNODES - 1))
                ){
                    area += (1/4 * fullTileArea * z);
                }
            else{
                area += (1/2 * fullTileArea * z);
            }
        }
        else {
            area += (fullTileArea * z) ;
        }
    }
    time1 = omp_get_wtime( );
    if((time1-time0) < maxTime){
        maxTime = (time1 - time0);
        // maxArea = area*2.;
    }
    }
    printf("%2d,%2d,%8f,%8f,%8f\n",NUMT,NUMNODES,((double)NUMNODES* (double)NUMNODES)/ maxTime / 1000000.,area*2.,maxTime);
    // printf("Final AREA %8.3f\n",area*2.);
    // printf("Time = %8.3f\n",(time1-time0));
}
float Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float r = 1. - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(float)N );
	return height;
}