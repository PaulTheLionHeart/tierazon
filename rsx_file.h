///////////////////////////////////////////
// rsx_file.h
///////////////////////////////////////////
//
// By: stephen c. ferguson
// http://home1.gte.net/itriazon/
// email: itriazon@gte.net
//
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <math.h>
#include <complex>

using Complex = std::complex<double>;

inline Complex operator+(const Complex& a, int b)
    {
    return a + static_cast<double>(b);
    }

inline Complex operator+(int a, const Complex& b)
    {
    return static_cast<double>(a) + b;
    }

inline Complex operator-(const Complex& a, int b)
    {
    return a - static_cast<double>(b);
    }

inline Complex operator-(int a, const Complex& b)
    {
    return Complex(static_cast<double>(a), 0.0) - b;
    }

inline Complex operator*(const Complex& a, int b)
    {
    return a * static_cast<double>(b);
    }

inline Complex operator*(int a, const Complex& b)
    {
    return static_cast<double>(a) * b;
    }

inline Complex operator/(const Complex& a, int b)
    {
    return a / static_cast<double>(b);
    }

inline Complex operator-(const Complex& a)
    {
    return Complex(-a.real(), -a.imag());
    }

inline Complex operator/(int a, const Complex& b)
    {
    return Complex(static_cast<double>(a), 0.0) / b;
    }

#define pi 3.141592653589793238462643383279
#define rad 57.2958

typedef struct tagRGB_IDATA
{
	double i;
	double rj;
	double gj;
	double bj;
} RGB_IDATA;

#define DUAL_BFACTOR 3
#define OFFSET_COLOR 64  //64

// variable declarations
extern Complex z, z1, z2, z3, z4, z5, z8, zd, z12, z16, z24, z36, z48;
extern Complex c, c1, c2, c3;
extern Complex t, t1, t2, t3, X, Y, Z, C, ca, cb, ca2, caa3;
extern Complex ci1;

// debug string attributes
extern char cstr[100];
extern int bug;

// FDimension Data array pointers
extern double				*pXTemp;
extern double				*pYTemp;

// Color method save buffers
extern double				*pXSave;
extern double				*pYSave;

extern double				*rjData;
extern double				*gjData;
extern double				*bjData;

extern int						size_x, size_y;
extern int						px, py;

extern int						nUsingBuffers;

// formula attributes
extern int formula, filter, bailout, maxit, n_color, maxit_save, nFDOption;
extern int jul, jul_save;

extern double d, minsize, maxsize;
extern int nRed, nGrn, nBlu, nRedStart, nGrnStart, nBluStart;

extern double mx, my, zz;

// Color attributes
extern RGB_IDATA rgbColor;
extern double rj, gj, bj;
extern int nColorMethod;

// filter attributes
extern int i, j, n_color_x, n_color_y, n_color_z, n_color_z1;
extern double m_lower, m_upper;

extern double d_color, d_color_x, d_color_y, d_color_z;
extern double xavg, yavg, zavg, zsav, xsav, ysav, xdif, ydif, zdif;
extern double zmin, zmax, zsav1, xsav_, ysav_;
extern double dt, dif_test, dStrands, dFactor, dFactor_2;
extern double limit, dStrands_HI, dStrands_LO;
extern double dStrands_HI_cx, dStrands_LO_cx;
extern double dStrands_HI_cy, dStrands_LO_cy;
extern double dStrands_cxd, dStrands_cyd;
extern double dStrands_df, limit_cxd, limit_cyd;

extern double avg, tot, sav, dif, ssq1, ssq2;
extern double dif_save;
extern double ztot, xtot, ytot;
extern double d_real, d_imag;
extern double dzx, dzy;
extern double a, b, x, y;
extern double zx_save, zy_save;

extern double dzx_save, dzy_save;
extern double temp, x_size, y_size, deg;

///////////////////////////////////////////	
// Fractal dimension variables
extern int						i2, jrw, bDimensionVariant;
extern double				x_std, y_std, dm, da;
extern double				denominator, x_rmin, x_rmax, y_rmin, y_rmax;

// Data array pointers
//double				*pXTemp;
//double				*pYTemp;

extern Complex    z_std;

extern Complex    z_rmin;
extern Complex    z_rmax;

extern Complex 		cx_std;
extern Complex 		cy_std;
extern Complex 		cz_std;

extern Complex 		cFDx;
extern Complex 		cFDy;
extern Complex 		cFDz;

extern Complex 		cRng_x;
extern Complex 		cRng_y;
extern Complex 		cRng_z;

extern Complex 		cNMAX;

extern double				dFDx;	// Fractal Dimension x
extern double				dFDy; // Fractal Dimension y
extern double				dFDz; // Fractal Dimension z

extern double				dFDx_0;	// Initial F Dimension x
extern double				dFDy_0; // Initial F Dimension y

extern int						nDIter_x;
extern int						nDIter_y;
extern int						NMAX_Save;
extern int						min, max;
extern int						ntemp;

// Average variables
extern double				x_mean;
extern double				y_mean;
extern Complex 		z_mean;

///////////////////////////////////
// implementions
///////////////////////////////////

// Filters
void Do_Filter();
void Filter_Complete();

// Complex functions
Complex  clog_z();
Complex  clog_t();
Complex  ccos_z();
Complex  ccos_c();
Complex  csin_z();
Complex  csin_t();
Complex  cexp_z();

double sum_sqrs_z();
double sum_sqrs_c();
double magnitude_z();
double sum_sqrs_z1();
double sum_sqrs_z3();
double sum_sqrs_zd();
double real_csin_z4();
double imag_csin_z4();

// Formulas
void Formula_01();
void Formula_02();
void Formula_03();
void Formula_04();
void Formula_05();
void Formula_06();
void Formula_07();
void Formula_08();
void Formula_09();
void Formula_10();
void Formula_11();
void Formula_12();
void Formula_13();
void Formula_14();
void Formula_15();
void Formula_16();
void Formula_17();
void Formula_18();
void Formula_19();
void Formula_20();
void Formula_21();
void Formula_22();
void Formula_23();
void Formula_24();
void Formula_25();
void Formula_26();
void Formula_27();
void Formula_28();
void Formula_29();
void Formula_30();
void Formula_31();
void Formula_32();
void Formula_33();
void Formula_34();
void Formula_35();
void Formula_36();
void Formula_37();
void Formula_38();
void Formula_39();
void Formula_40();
void Formula_41();
void Formula_42();
void Formula_43();
void Formula_44();
void Formula_45();
void Formula_46();
void Formula_47();
void Formula_48();
void Formula_49();
void Formula_50();
void Formula_51();
void Formula_52();
void Formula_53();
void Formula_54();
void Formula_55();
void Formula_56();
void Formula_57();
void Formula_58();
void Formula_59();
void Formula_60();
void Formula_61();
void Formula_62();
void Formula_63();
void Formula_64();
void Formula_65();
void Formula_66();
void Formula_67();
void Formula_68();
void Formula_69();
void Formula_70();
void Formula_71();
void Formula_72();
void Formula_73();
void Formula_74();
void Formula_75();
void Formula_76();
void Formula_77();
void Formula_78();
void Formula_79();
void Formula_80();
void Formula_81();
void Formula_82();
void Formula_83();
void Formula_84();
void Formula_85();
void Formula_86();
void Formula_87();
void Formula_88();
void Formula_89();
void Formula_90();
void Formula_91();
void Formula_92();
void Formula_93();
void Formula_94();
void Formula_95();
void Formula_96();
void Formula_97();
void Formula_98();
void Formula_99();
void Formula_100(); 
void Formula_101();
void Formula_102();
void Formula_103();
void Formula_104();
void Formula_105();
void Formula_106();
void Formula_107();
void Formula_108();
void Formula_109();
void Formula_110();
void Formula_111();
void Formula_112();
void Formula_113();
void Formula_114();
void Formula_115();
void Formula_116();
void Formula_117();

void color_methods();
void FDimension();
double x_y_to_degrees(double x_, double y_);
void Generalized_Coloring_Method1();		
void Generalized_Coloring_Method2();		
void Generalized_Coloring_Method3();		
void Generalized_Coloring_Method4();		
void Generalized_Coloring_Method5();		
void Generalized_Coloring_Method6();		
void Generalized_Coloring_Method7();		
void Generalized_Coloring_Method8();		
void Generalized_Coloring_Method9();		
void Generalized_Coloring_Method10();		
void Generalized_Coloring_Method11();		
void Generalized_Coloring_Method12();		
void Generalized_Coloring_Method13();		
void Generalized_Coloring_Method14();		
void Generalized_Coloring_Method15();		
void Generalized_Coloring_Method18();		
void Generalized_Coloring_Method19();		
void Generalized_Coloring_Method20();		
void Generalized_Coloring_Method21();		
void Generalized_Coloring_Method22();		
void Generalized_Coloring_Method23();		
void Generalized_Coloring_Method24();		
void Generalized_Coloring_Method25();		
void Generalized_Coloring_Method26();		
void Generalized_Coloring_Method27();		
void Generalized_Coloring_Method28();		
void Generalized_Coloring_Method29();		
void Generalized_Coloring_Method30();		
void Generalized_Coloring_Method31();		
void Generalized_Coloring_Method32();		
void Generalized_Coloring_Method33();		
void Generalized_Coloring_Method34();		
void Generalized_Coloring_Method35();		
void Generalized_Coloring_Method36();		
void Generalized_Coloring_Method37();		
void Generalized_Coloring_Method38();		
void Generalized_Coloring_Method39();		

