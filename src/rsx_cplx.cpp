////////////////////////////////////////////////////////////////
// rsx_math.c
////////////////////////////////////////////////////////////////
//
// By: stephen c. ferguson
// http://home1.gte.net/itriazon/
// email: itriazon@gte.net
//
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <math.h>
#include "rsx_file.h"

///////////////////////////////////////////////////////////////
// Complex Functions
///////////////////////////////////////////////////////////////

Complex cexp_z()
    {
    Z.real(exp(z.real()) * cos(z.imag()));
    Z.imag(exp(z.real()) * sin(z.imag()));

    return Z;
    }

Complex clog_z()
    {
    //cmplx(log(ABS(sum_sqrs(Z),atan2(y,x));}

    Z.real(log(sqrt(z.real() * z.real() + z.imag() * z.imag())));
    Z.imag(atan2(z.imag(), z.real()));

    return Z;
    }

Complex clog_t()
    {
    //cmplx(log(ABS(sum_sqrs(Z),atan2(y,x));}

    Z.real(log(sqrt(t.real() * t.real() + t.imag() * t.imag())));
    Z.imag(atan2(t.imag(), t.real()));

    return Z;
    }

Complex ccos_z()
    {
    Z.real(.5 * (exp(z.imag()) + 1. / exp(z.imag())) * cos(z.real()));
    Z.imag(-sin(z.real()) * .5 * (exp(z.imag()) - 1. / exp(z.imag())));

    return Z;
    }

Complex ccos_c()
    {
    C.real(.5 * (exp(c.imag()) + 1. / exp(c.imag())) * cos(c.real()));
    C.imag(-sin(c.real()) * .5 * (exp(c.imag()) - 1. / exp(c.imag())));

    return C;
    }

Complex csin_z()
    {
    Z.real(.5 * (exp(z.imag()) + 1. / exp(z.imag())) * sin(z.real()));
    Z.imag(cos(z.real()) * .5 * (exp(z.imag()) - 1. / exp(z.imag())));

    return Z;
    }

Complex csin_t()
    {
    Z.real(.5 * (exp(t.imag()) + 1. / exp(t.imag())) * sin(t.real()));
    Z.imag(cos(t.real()) * .5 * (exp(t.imag()) - 1. / exp(t.imag())));

    return Z;
    }

double sum_sqrs_z()
    {
    return z.real() * z.real() + z.imag() * z.imag();
    }

double sum_sqrs_c()
    {
    return c.real() * c.real() + c.imag() * c.imag();
    }

double magnitude_z()
    {
    return sqrt(z.real() * z.real() + z.imag() * z.imag());
    }

double sum_sqrs_z1()
    {
    return z1.real() * z1.real() + z1.imag() * z1.imag();
    }

double sum_sqrs_z3()
    {
    return z3.real() * z3.real() + z3.imag() * z3.imag();
    }

double sum_sqrs_zd()
    {
    return zd.real() * zd.real() + zd.imag() * zd.imag();
    }

double real_csin_z4()
    {
    return .5 * (exp(z4.imag()) + 1. / exp(z4.imag())) * sin(z4.real());
    }

double imag_csin_z4()
    {
    return cos(z4.real()) * .5 * (exp(z4.imag()) - 1. / exp(z4.imag()));
    }