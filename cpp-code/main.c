
 /*
 * MLody
 * Author: Jordy
 *              Public code to compute polarized synchrotron coefficients using a machine learning model.
 *              Network trained with Keras and converted to C++ using keras2cpp.
 *              The keras2cpp library was not written by the main author of this code.
 *              keras2cpp is a public code under the MIT Public License.
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

int main() {
    struct GRMHD modvar;
    double pitch_angle;
    double frequency;
    double jI, aI, jQ, aQ,rQ, jU, aU, rU, jV, aV, rV;

    init_ml_model();

    modvar.B = 10;
    modvar.n_e= 1e4;
    modvar.theta_e= 1;
    frequency = 230e9;
    pitch_angle = 0.5 * M_PI;

    fprintf(stdout, "Input Variables\n");
    fprintf(stdout, "B = %f\n", modvar.B);
    fprintf(stdout, "n_e = %f\n", modvar.n_e);
    fprintf(stdout, "theta_e = %f\n", modvar.theta_e);
    fprintf(stdout, "frequency = %f\n", frequency);
    fprintf(stdout, "pitch_angle = %f\n", pitch_angle);


    mlody(frequency, modvar, pitch_angle, &jI, &aI, &jQ, &aQ, &rQ, &jU, &aU, &rU, &jV, &aV, &rV);

    fprintf(stdout, "Stokes I\n");
    fprintf(stdout, "jI = %f\n", jI);
    fprintf(stdout, "aI = %f\n", aI);

    fprintf(stdout, "Stokes Q\n");
    fprintf(stdout, "jQ = %f\n", jQ);
    fprintf(stdout, "aQ = %f\n", aQ);
    fprintf(stdout, "rQ = %f\n", rQ);

    fprintf(stdout, "Stokes U\n");
    fprintf(stdout, "jU = %f\n", jU);
    fprintf(stdout, "aU = %f\n", aU);
    fprintf(stdout, "rU = %f\n", rU);

    fprintf(stdout, "Stokes V\n");
    fprintf(stdout, "jV = %f\n", jV);
    fprintf(stdout, "aV = %f\n", aV);
    fprintf(stdout, "rV = %f\n", rV);
        
    return 0;
}