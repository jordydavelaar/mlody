
typedef struct GRMHD {
    double n_e;
    double B;
    double theta_e;
} GRMHD;

#define sign(x) (((x) < 0) ? -1 : ((x) > 0))

// CONSTANTS
////////////

// PHYSICAL CONSTANTS
#define ELECTRON_CHARGE (4.80320425e-10)
#define ELECTRON_MASS (9.1093829e-28)
#define PROTON_MASS (1.6726219e-24)
#define BOLTZMANN_CONSTANT (1.3806488e-16)
#define SPEED_OF_LIGHT (2.99792458e10)
#define PLANCK_CONSTANT (6.62606885e-27)
#define MPCL2 (0.0015033)
#define GGRAV (6.674e-8)
#define MSUN (1.989e33)
#define KPCTOCM (3.086e21)
#define MPoME (PROTON_MASS / ELECTRON_MASS)
