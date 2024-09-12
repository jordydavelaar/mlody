/*
 * File: mlody.c
 * Author: Jordy
 * Description: This file contains the implementation of the mlody function
 *              which performs calculations based on a machine learning model.
 *              The function uses the publicly avaibale keras2cpp under the MIT Public License.
 *              Keras2cpp is a C++ library to load and run Keras TensorFlow models.
 *              keras2cpp can be found at: https://github.com/gosha20777/keras2cpp
 * 
 * Date: 09/12/2024
 * 
 */

#include "model-ml.h"
#include "definitions.h"
#include "functions.h"
#include <iostream>
#include <math.h>

// Rest of the code...
using keras2cpp::Model;
using keras2cpp::Tensor;

auto model  = Model::load("mlody.model");

double xmin[3];
double xmax[3];

double ymin[8];
double ymax[8];


void init_ml_model(){
/**
 * @brief Initializes the machine learning model by reading model parameters from a file.
 * 
 * This function reads the model parameters from the "minmax.txt" file and initializes the machine learning model accordingly.
 * The file should contain the minimum and maximum values for each parameter, separated by a space.
 * The function expects the file to be located in the same directory as the source file.
 * 
 * @note The function will exit with an error message if the file cannot be read.
 * 
 * @requirements
 * - The "minmax.txt" file must exist in the same directory as the source file.
 * - The file must contain the correct number of minimum and maximum values for each parameter.
 * - The minimum and maximum values must be separated by a space.
 * - The function should be called before using the machine learning model.
 */
    FILE *input;

    input = fopen("minmax.txt", "r");
    if (input == NULL) {
        fprintf(stderr, "Can't read file %s! Aborting", "minmax.txt");
        exit(1);
    }

    // Model parameters
    for(int i=0;i<3;i++){
	fscanf(input, "%lf %lf", &xmin[i],&xmax[i]);
	 
   }

    for(int i=0;i<8;i++){
	fscanf(input, "%lf %lf", &ymin[i],&ymax[i]);
    }


}

void mlody(double nu_p,struct GRMHD  modvar, double pitch_ang, 
             double *jI, double *aI, double *jQ, double *aQ, double *rQ, 
             double *jV, double *aV, double *rV){
/**
 * @brief Performs calculations based on a machine learning model.
 * 
 * This function takes in various parameters and uses a machine learning model to perform calculations.
 * The function modifies the values of the output variables jI, aI, jQ, aQ, rQ, jV, aV, and rV.
 * 
 * @note The function will exit with an error message if input parameters are out of bounds.
 * 
 * @param nu_p The value of nu_p.
 * @param modvar The GRMHD struct containing modvar parameters.
 * @param pitch_ang The value of pitch_ang.
 * @param jI Pointer to the output variable jI.
 * @param aI Pointer to the output variable aI.
 * @param jQ Pointer to the output variable jQ.
 * @param aQ Pointer to the output variable aQ.
 * @param rQ Pointer to the output variable rQ.
 * @param jV Pointer to the output variable jV.
 * @param aV Pointer to the output variable aV.
 * @param rV Pointer to the output variable rV.
 * 
 * @requirements
 * - The modvar struct must contain the necessary parameters.
 * - The output variables must be valid pointers.
 * - The function init_ml_model() must be called before using this function.
 */
    double nuc = modvar.B * ELECTRON_CHARGE/(2*M_PI*ELECTRON_MASS*SPEED_OF_LIGHT);

    double mu=cos(pitch_ang);
    double X[3]={log10(nu_p/nuc),log10(modvar.theta_e),mu};

    X[0]=(X[0]-xmin[0])/xmax[0];
    X[1]=(X[1]-xmin[1])/xmax[1];
    X[2]=(X[2]-xmin[2])/xmax[2];

    Tensor in{3};
    in.data_ = {X[0], X[1], X[2]};

    if(X[0]<-1 || X[0]>1 || X[1]<-1 || X[1]>1 || X[2]<-1 || X[2]>1){ 
        fprintf(stderr,"Out of bounds, aborting!\n");
	    exit(1);
    }

    Tensor out = model(in);
    double jfac = ELECTRON_CHARGE*ELECTRON_CHARGE * nuc /SPEED_OF_LIGHT;
    double afac = ELECTRON_CHARGE*ELECTRON_CHARGE/(nu_p*ELECTRON_MASS*SPEED_OF_LIGHT);

    *jI = modvar.n_e*pow(10.,out.data_[0]*ymax[0]+ymin[0])*jfac;
    *aI = modvar.n_e*pow(10.,out.data_[1]*ymax[1]+ymin[1])*afac;

    *jQ = modvar.n_e*pow(10.,out.data_[2]*ymax[2]+ymin[2])*jfac;
    *aQ = modvar.n_e*pow(10.,out.data_[3]*ymax[3]+ymin[3])*afac;
    *rQ = -modvar.n_e *sign(out.data_[4])*powf(out.data_[4]*ymax[4],4.0);

    *jV = mu*modvar.n_e*pow(10.,out.data_[5]*ymax[5]+ymin[5])*jfac;
    *aV = mu*modvar.n_e*pow(10.,out.data_[6]*ymax[6]+ymin[6])*afac;
    *rV = modvar.n_e *sign(out.data_[7])*powf(out.data_[7]*ymax[7],4.0);
}


