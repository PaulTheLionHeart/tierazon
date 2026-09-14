////////////////////////////////////////////////////////////////
// rsx_filt.c
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

int CALLBACK _filter(double zx, double zy, int _ncolor)
    {
    n_color = _ncolor;
    z.real(zx);
    z.imag(zy);
    Do_Filter();
    return n_color;
    }

//////////////////////////////////////////////////////
// Filters
//////////////////////////////////////////////////////

void Do_Filter()
    {
    switch (filter)
	{
	    case 1:  // Stalks I			
		//wsprintf (cstr, "step 1");
			//MessageBox(NULL, cstr, "Debug", MB_OK);

		d_real = fabs(z.real() / z.imag());
		if (d_real < dStrands)
		    {
		    //if (xtot == 0)
			    //xtot = 1;
	    //wsprintf (cstr, "step 1");
		    //MessageBox(NULL, cstr, "Debug", MB_OK);
		    xtot += 30 * pow((1 - d_real / dStrands), n_color);
		    xsav = z.real();
		    }

		d_imag = fabs(z.imag() / z.real());
		if (d_imag < dStrands)
		    {
		    //if (ytot == 0)
			    //ytot = 1;
	    //wsprintf (cstr, "step 1");
		    //MessageBox(NULL, cstr, "Debug", MB_OK);
		    ytot += 30 * pow((1 - d_imag / dStrands), n_color);
		    ysav = z.imag();
		    }

		break;

	    case 2:  // Bubbles I
	    case 8:  // Bubbles II
		temp = sum_sqrs_z();
		if (filter == 2)
		    {
		    if (temp < dStrands)
			{
			ztot += 5 * pow((1 - temp / dStrands), n_color);
			xsav = ysav = temp;
			}
		    }
		else
		    {
		    if (temp < dStrands)
			{
			ztot += 10 * pow((1 - temp / dStrands), n_color);
			xsav = ysav = temp;
			}
		    }

		d_real = fabs(z.real()) + fabs(z.imag());
		if (d_real < dStrands)
		    {
		    xtot += 2 * (1 - d_real / dStrands);
		    xsav = d_real;
		    }

		d_imag = fabs(z.imag()) + fabs(z.real());
		if (d_imag < dStrands)
		    {
		    ytot += 2 * (1 - d_imag / dStrands);
		    ysav = d_imag;
		    }

		break;

	    case 3:
		if (sum_sqrs_z() >= maxsize)  // 1e6
		    return;

		xtot = xtot + fabs(z.real());
		xavg = xtot / n_color;
		xdif = xavg - xsav;
		xsav = xavg;
		if (fabs(xdif) < dStrands)
		    d_color_x = fabs(xdif);

		ytot = ytot + fabs(z.imag());
		yavg = ytot / n_color;
		ydif = yavg - ysav;
		ysav = yavg;
		if (fabs(ydif) < dStrands)
		    d_color_y = fabs(ydif);
		break;

	    case 4:
		if (sum_sqrs_z() >= maxsize)	// 1e6
		    return;

		ztot = ztot + sum_sqrs_z();
		zavg = ztot / n_color;
		zdif = zavg - zsav;
		zsav = zavg;
		if (fabs(zdif) < dStrands)
		    {
		    d_color_z = fabs(zdif);
		    xsav = z.real();
		    ysav = z.imag();
		    }
		break;

	    case 5:  // log(log(...))
		xsav = z.real();
		ysav = z.imag();
		break;

	    case 6:  // Bubbles I
		temp = fabs(z.real() * z.imag()) * 2;
		if (temp < dStrands)
		    {
		    ztot += 30 * pow((1 - temp / dStrands), n_color);
		    xsav = z.real();
		    ysav = z.imag();
		    n_color_z = n_color;
		    }
		break;

	    case 7:  // dual bubbles
		temp = fabs(z.real() * z.imag()) * 2;
		if (temp < dStrands)
		    {
		    ztot += 30 * pow((1 - temp / dStrands), n_color);
		    xsav = z.real();
		    ysav = z.imag();
		    n_color_z = n_color;
		    }

		if (temp < dStrands / DUAL_BFACTOR)
		    {
		    ztot += 30 * pow((1 - temp / dStrands), n_color);
		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 9:  // Stalks II
		d_real = fabs(z.real() / z.imag());
		if (d_real < dStrands)
		    {
		    xtot += 100 * pow((1 - d_real / dStrands), n_color);
		    xsav = z.real();
		    }

		d_imag = fabs(z.imag() / z.real());
		if (d_imag < dStrands)
		    {
		    ytot += 100 * pow((1 - d_imag / dStrands), n_color);
		    ysav = z.imag();
		    }
		break;

	    case 10:  // Rings I
		ssq1 = sqrt(sum_sqrs_z());
		// (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
		if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;
		    xsav = z.real();
		    ysav = z.imag();
		    n_color = maxit;
		    }
		break;

	    case 11:  // Rings II
	    case 12:  // Rings III
		ssq1 = 1 / sum_sqrs_z();
		//if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
		if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;
		    xsav = z.real();
		    ysav = z.imag();
		    n_color = maxit;
		    }
		break;

	    case 13: // Hi Lo I
		dzx = fabs(z.real());
		dzy = fabs(z.imag());

		if (dzx < dStrands_HI_cx &&
		    dzx > dStrands_LO_cx)
		    {
		    xtot += (dStrands_HI_cx - dzx) / dStrands_cxd;
		    xsav = z.real();
		    }

		if (dzy < dStrands_HI_cy &&
		    dzy > dStrands_LO_cy)
		    {
		    ytot += (dStrands_LO_cy - dzy) / dStrands_cyd;
		    ysav = z.imag();
		    }

		break;

	    case 14:  // testing
		ssq1 = (sqrt((sum_sqrs_z())));
		if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav == 0)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;
		    xsav = z.real();
		    ysav = z.imag();
		    n_color = maxit;
		    }
		break;

	    case 17:
		if ((fabs(z.real())) < dStrands && xtot == 0)
		    {
		    xtot = 1;
		    xsav += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real()));
		    n_color_x = n_color;
		    }

		if ((fabs(z.imag())) < dStrands && ytot == 0)
		    {
		    ytot = 1;
		    ysav += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real()));
		    n_color_y = n_color;
		    }

		break;

	    case 18:
		if (sum_sqrs_z() < dStrands)
		    {
		    zsav += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real())) * dFactor_2;
		    xsav = z.real();
		    ysav = z.imag();
		    n_color_z = n_color;
		    }
		break;

	    case 19:  //
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands)
		    {
		    ztot += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real()))
			* (1 + (1 - (ssq1 / dStrands)));
		    xsav = z.real();
		    ysav = z.imag();
		    n_color_z = n_color;
		    }

		break;

	    case 20:
		ssq1 = sqrt(sum_sqrs_z());
		if (ssq1 < dStrands && ssq1 > zsav)
		    {
		    ztot += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real())) * 4 * dFactor_2;
		    zsav = ssq1;
		    n_color_z = n_color;
		    xsav = z.real();
		    ysav = z.imag();
		    }
		break;

	    case 21:  // Flowers I
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands && zsav == 0)
		    //if (ssq1 < dStrands)
		    {
		    zsav = ssq1;
		    ztot += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real())) * 10;

		    dif_test = (ztot + (dStrands - zsav) * 10 * dFactor_2);  // 1300
		    if (dif_test < m_lower || dif_test > m_upper)
			{
			ztot = 0;
			zsav = 0;
			n_color_z = 0;
			}
		    else
			{
			n_color_z = n_color;
			zsav = dif_test;
			n_color = maxit;
			}

		    xsav = z.real();
		    ysav = z.imag();

		    }
		break;

	    case 22:  // Flowers II
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands && zsav == 0)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;
		    ztot += (atan(fabs(z.real() / z.imag())) -
			atan(fabs(z.imag() / z.real()))) * 10;

		    dif_test = ztot + (dStrands - zsav) * 10 * dFactor_2;
		    if (dif_test < m_lower || dif_test > m_upper)
			{
			ztot = 0;
			zsav = 0;
			n_color_z = 0;
			}
		    else
			{
			n_color_z = n_color;
			zsav = dif_test;
			n_color = maxit;
			}

		    xsav = z.real();
		    ysav = z.imag();

		    }
		break;

	    case 23:  // Flowers III
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands && zsav == 0)
		    {
		    zsav = ssq1;

		    ztot += (atan(fabs(z.real() / z.imag()))) * 10;

		    //dt = z.real() * z.imag();
		    dif_test = ztot + (dStrands - zsav) * 10 * dFactor_2;
		    if (dif_test < m_lower || dif_test > m_upper)
			{
			ztot = 0;
			zsav = 0;
			n_color_z = 0;
			}
		    else
			{
			n_color_z = n_color;
			zsav = dif_test;
			n_color = maxit;
			}

		    xsav = z.real();
		    ysav = z.imag();

		    }
		break;

	    case 24:  // Flowers IV
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands && zsav == 0)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;

		    ztot += (sin(z.real() * z.real() * 10) -
			sin(z.imag() * z.imag() * 10) * 10);

		    dif_test = ztot + (dStrands - zsav) * 10 * dFactor_2;  // 1300
		    if (dif_test < m_lower || dif_test > m_upper)
			{
			ztot = 0;
			zsav = 0;
			n_color_z = 0;
			}
		    else
			{
			n_color_z = n_color;
			zsav = dif_test;
			n_color = maxit;
			}

		    xsav = z.real();
		    ysav = z.imag();

		    }
		break;

	    case 25:  // Flowers V
		ssq1 = sum_sqrs_z();
		if (ssq1 < dStrands && zsav == 0)
		    {
		    zsav = ssq1;
		    n_color_z = n_color;
		    ztot += (sin(z.real() * z.real() * 10) *
			sin(z.imag() * z.imag() * 10)) * 10;
		    dt = z.real() * z.imag();

		    dif_test = ztot + (dStrands - zsav) * 1000 * dFactor_2;
		    if (dif_test < m_lower || dif_test > m_upper)  // 40
			{
			ztot = 0;
			zsav = 0;
			n_color_z = 0;
			xsav = z.real();
			ysav = z.imag();
			}
		    }
		break;

	    case 26:  // testing
		ssq1 = sqrt(sum_sqrs_z());
		if (ssq1 < dStrands && zsav == 0)
		    {
		    ztot += atan(fabs(z.real() / z.imag())) *
			atan(fabs(z.imag() / z.real())) * 4 * dFactor_2;
		    zsav = ssq1;
		    n_color_z = n_color;
		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 27:  // fractal dimensions		 
	    case 28:  // standard deviations
		pXTemp[n_color] = z.real() * 100;
		pYTemp[n_color] = z.imag() * 100;
		xsav = z.real();
		ysav = z.imag();
		break;

	    case 29:  // Square Stalks & Bubbles			
	    case 30:
		temp = (fabs(z.real()) + fabs(z.imag()));
		if (temp < dStrands)
		    {
		    xtot = 10 * (1 - temp / dStrands);
		    ytot = xtot;
		    xsav = z.real();
		    ysav = z.imag();
		    n_color_z = n_color;
		    }

		break;

	    case 31:
	    case 32:
		if (fabs(z.real()) < dStrands)
		    {
		    b = (1 - fabs(z.real()) / dStrands) * dFactor_2;
		    b = b * .3;
		    xtot = xtot + b - xtot * b;
		    n_color_x++;
		    xsav = z.real();
		    }

		if (fabs(z.imag()) < dStrands)
		    {
		    b = (1 - fabs(z.imag()) / dStrands) * dFactor_2;
		    b = b * .3;
		    ytot = ytot + b - ytot * b;
		    n_color_y++;
		    ysav = z.imag();
		    }

		break;

	    case 33:  // fractal dimensions of orbit traps			
	    case 34:  // stalks standard deviation
		if (fabs(z.real()) < dStrands)
		    {
		    pXTemp[n_color] = (1 - fabs(z.real()) / dStrands); // 100
		    n_color_x++;
		    xsav = z.real();
		    }
		else
		    pXTemp[n_color] = 1; ////////////

		if (fabs(z.imag()) < dStrands)
		    {
		    pYTemp[n_color] = (1 - fabs(z.imag()) / dStrands); // 100
		    n_color_y++;
		    ysav = z.imag();
		    }
		else
		    pYTemp[n_color] = 1; /////////

		break;

	    case 35:  //  Hi/Lo stalks dimension
	    case 36:
		ssq1 = fabs(z.real());
		if (ssq1 < dStrands_HI_cx && ssq1 > dStrands_LO_cx)
		    {
		    n_color_z++;
		    pXTemp[n_color] = 1 - (dStrands_HI_cx - ssq1) / (dStrands_HI_cx - dStrands_LO_cx) * 100;
		    xsav = z.real();
		    }
		else
		    {
		    pXTemp[n_color] = 1;
		    }

		ssq1 = fabs(z.imag());
		if (ssq1 < dStrands_HI_cy && ssq1 > dStrands_LO_cy)
		    {
		    n_color_z++;
		    pYTemp[n_color] = 1 - (dStrands_HI_cy - ssq1) / (dStrands_HI_cy - dStrands_LO_cy) * 100;
		    ysav = z.imag();
		    }
		else
		    {
		    pYTemp[n_color] = 1;
		    }

		break;

	    case 37:
		if (fabs(z.real()) < dStrands_HI_cx &&
		    fabs(z.real()) > dStrands_LO_cx)
		    {
		    n_color_z++;
		    pXTemp[n_color] = 1 - (dStrands_HI_cx - fabs(z.real())) / (dStrands_cxd);
		    xsav = z.real();
		    }
		else
		    {
		    pXTemp[n_color] = 1;
		    }

		if (fabs(z.imag()) < dStrands_HI_cy &&
		    fabs(z.imag()) > dStrands_LO_cy)
		    {
		    n_color_z++;
		    pYTemp[n_color] = 1 - (dStrands_HI_cy - fabs(z.imag())) / (dStrands_cyd);
		    ysav = z.imag();
		    }
		else
		    {
		    pYTemp[n_color] = 1;
		    }

		break;

	    case 38:
		pXTemp[n_color] = atan(fabs(z.real() / z.imag())) * 100;
		pYTemp[n_color] = atan(fabs(z.imag() / z.real())) * 100;
		xsav = z.real();
		ysav = z.imag();

		break;

	    case 39:	// xray stalks
		if (fabs(z.real()) < dStrands)
		    {
		    xsav = fabs(z.real());
		    temp = dStrands / xsav;
		    xtot += log(temp);
		    }

		if (fabs(z.imag()) < dStrands)
		    {
		    ysav = fabs(z.imag());
		    temp = dStrands / ysav;
		    ytot += log(temp);
		    }

		//xsav = z.real();
		//ysav = z.imag();
		break;

	    case 40:		// xray bubbles
		if (sum_sqrs_z() < dStrands)
		    {
		    zsav = sum_sqrs_z();
		    //n_color_z++;

		    temp = log(2 + dStrands / zsav);

		    if (n_color % 2 == 0)
			xtot += temp;
		    else
			ytot += temp;

		    xsav = z.real();
		    ysav = z.imag();
		    }
		break;

	    case 41:  // xray rings
		ssq1 = sqrt(sum_sqrs_z());
		if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
		    {
		    temp = log(2 + dStrands_df / (fabs(limit - ssq1)));

		    if (n_color % 2 == 0)
			xtot += temp;
		    else
			ytot += temp;

		    xsav = fabs(limit - ssq1) * 2;
		    ysav = fabs(limit - ssq1) * 2;
		    }

		break;

	    case 42:
		dzx = fabs(z.real());
		dzy = fabs(z.imag());

		if (dzx < dStrands_HI_cx &&
		    dzx > dStrands_LO_cx)
		    {
		    xsav = fabs(limit_cxd - dzx);
		    temp = log(10 + limit_cxd / xsav);
		    xtot += temp;
		    xsav *= 2;
		    }

		if (dzy < dStrands_HI_cy &&
		    dzy > dStrands_LO_cy)
		    {
		    ysav = fabs(limit_cyd - dzy);
		    temp = log(10 + limit_cyd / ysav);
		    ytot += temp;
		    ysav *= 2;
		    }

		break;

	    case 43:
		if (fabs(z.real()) < dStrands)
		    {
		    xsav = fabs(z.real());
		    xtot += atan(fabs(z.imag() / z.real())) *
			atan(fabs(z.real() / z.imag())) * 2;
		    }

		if (fabs(z.imag()) < dStrands)
		    {
		    ysav = fabs(z.imag());
		    ytot += atan(fabs(z.imag() / z.real())) *
			atan(fabs(z.real() / z.imag())) * 2;
		    }

		break;

	    case 44:
		if (fabs(z.real()) < dStrands
		    || fabs(z.imag()) < dStrands)
		    {
		    /*
		    if (n_color >= m_upper)
		    {
			    wsprintf (cstr, "step 1");
			    MessageBox(NULL, cstr, "Debug", MB_OK);
		    }
		    */

		    if (fabs(z.real()) < dStrands)
			xtot += 100 * (1 - fabs(z.real()) / dStrands);

		    if (fabs(z.imag()) < dStrands)
			ytot += 100 * (1 - fabs(z.imag()) / dStrands);

		    if (xtot > maxit * dFactor_2 || ytot > maxit * dFactor_2)
			n_color = maxit;

		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 45:
		if (fabs(z.real()) * fabs(z.imag()) < dStrands)
		    {
		    ztot += 100 * (1 - (fabs(z.real()) * fabs(z.imag()) / dStrands));

		    if (ztot > maxit * dFactor_2)
			n_color = maxit;

		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 46:
		if (sum_sqrs_z() < dStrands)
		    {
		    ztot += 30 * (30 * dFactor_2 / (n_color)) * (1 - (sum_sqrs_z() / dStrands));

		    n_color_z = n_color;
		    if (ztot > maxit * 10)
			n_color = maxit;

		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 47:
		temp = sum_sqrs_z();
		if (temp < dStrands)
		    {
		    ztot += 10 * dFactor_2 * (100 / (n_color)) *
			(1 - (temp / dStrands));

		    n_color_z = n_color;
		    if (ztot > maxit * 10)
			n_color = maxit;

		    xsav = z.real();
		    ysav = z.imag();
		    }

		break;

	    case 48:
		ztot = sum_sqrs_z();
		if (ztot < dStrands)
		    {
		    pYTemp[n_color] = pXTemp[n_color] = (dStrands / ztot) * 100;
		    n_color_z = n_color;
		    }
		else
		    {
		    pXTemp[n_color] = 0;
		    pYTemp[n_color] = 0;
		    }
		xsav = z.real();
		ysav = z.imag();

		break;

	    case 49:
		ztot = sum_sqrs_z();
		if (ztot < dStrands)
		    {
		    pYTemp[n_color] = pXTemp[n_color] = log(dStrands * 100 / ztot) * 100000;
		    n_color_z = n_color;
		    }
		else
		    {
		    pXTemp[n_color] = 0;
		    pYTemp[n_color] = 0;
		    }
		xsav = z.real();
		ysav = z.imag();

		break;

	    case 50:
		d_real = fabs(z.real() / z.imag());
		d_imag = fabs(z.imag() / z.real());

		if (d_real <= dStrands)
		    {
		    xtot += (1 - d_real / dStrands);
		    //xsav = z.real();
		    xsav = d_real;
		    }

		if (d_imag < dStrands)
		    {
		    ytot += (1 - d_imag / dStrands);
		    //ysav = z.imag();		 
		    ysav = d_imag;
		    }

		break;

	    case 51:  // Stalks & Bubbles			
	    case 52:
		if (fabs(z.real()) < dStrands
		    && n_color > m_lower && n_color < m_upper)
		    {
		    xsav = z.real();
		    n_color_x = n_color;
		    //n_color_x++;
		    }

		if (fabs(z.imag()) < dStrands
		    && n_color > m_lower && n_color < m_upper)
		    {
		    ysav = z.imag();
		    n_color_y = n_color;
		    //n_color_y++;
		    }

		if (sum_sqrs_z() < dStrands
		    && n_color > m_lower && n_color < m_upper)
		    {
		    zsav = sum_sqrs_z();
		    //n_color_z = n_color;
		    n_color_z++;
		    ysav = z.imag();
		    xsav = z.real();
		    }
		break;

	    default:  // last z values (gradients)
		// Case 15, 16, 17
		xsav = z.real();
		ysav = z.imag();
		break;
	}
    }

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

RGB_IDATA CALLBACK _filter_complete()
    {
    z.real(xsav);
    z.imag(ysav);

    Filter_Complete();

    if (fabs(xsav) < minsize)
	{
	if (xsav > 0)
	    xsav = minsize;
	else
	    xsav = -minsize;
	}

    if (fabs(ysav) < minsize)
	{
	if (ysav > 0)
	    ysav = minsize;
	else
	    ysav = -minsize;
	}

    if (fabs(xsav) > maxsize)
	{
	if (xsav > 0)
	    xsav = maxsize;
	else
	    xsav = -maxsize;
	}

    if (fabs(ysav) > maxsize)
	{
	if (ysav > 0)
	    ysav = maxsize;
	else
	    ysav = -maxsize;
	}

    switch (filter)
	{
	    case 27:  // Check for a fractal Dimension filter
	    case 28:  // standard deviation filter
	    case 33:
	    case 34:
	    case 35:
	    case 36:
	    case 37:
	    case 38:
	    case 48:
	    case 49:

		FDimension();
		break;

	    default:
		break;
	}

    if (size_x <= 640 && size_y <= 480 && nUsingBuffers)
	{
	pXSave[px + py * size_x] = xsav;
	pYSave[px + py * size_x] = ysav;

	/*
	if (px == 1 && py == 1)
	{
		sprintf(cstr, "step 1, xsav = %f, ysav=%f, i = %d, rj = %f, gj = %f",
			xsav, ysav, i, rj, gj);
		MessageBox(NULL, cstr, "bug", MB_OK);
	}
	*/

	rjData[px + py * size_x] = rj;
	gjData[px + py * size_x] = gj;
	bjData[px + py * size_x] = bj;
	}

    if (nColorMethod)
	color_methods();

    //MessageBox(NULL, "step 5", "bug", MB_OK);

    rgbColor.i = j;
    rgbColor.rj = rj;
    rgbColor.gj = gj;
    rgbColor.bj = bj;

    return rgbColor;

    }

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void Filter_Complete()
    {
    static int nCount = 0;

    rj = gj = bj = n_color;
    j = static_cast<int>(rj);

    switch (filter)
	{
	    case 1:
	    case 9:
	    case 13:
	    case 39:
	    case 40:
	    case 41:
	    case 42:
	    case 43:

		//wsprintf (cstr, "step 3");
		  //MessageBox(NULL, cstr, "Debug", MB_OK);

			       //return;

		if (xsav || ysav)
		    {
		    xtot *= dFactor;
		    ytot *= dFactor;
		    d = sqrt(xtot * xtot + ytot * ytot);

		    rj = d + xtot;
		    gj = d + ytot;
		    bj = d;

		    }
		else
		    {
		    rj = gj = bj = 0;
		    j = 0;
		    }
		break;

	    case 2:
	    case 8:
		if (ztot)
		    {
		    rj = gj = bj = ztot * dFactor;
		    }
		else
		    j = 0;

		if (xtot || ytot)
		    {
		    d = sqrt(xtot * xtot + ytot * ytot);
		    gj = d + xtot * dFactor;
		    bj = d + ytot * dFactor;
		    }

		break;

	    case 3:
		if (d_color_x || d_color_y)
		    {
		    if (d_color_x)
			rj = xtot = (dStrands - d_color_x) * 1000 * dFactor;

		    if (d_color_y)
			gj = ytot = (dStrands - d_color_y) * 1000 * dFactor;

		    n_color = static_cast<int>(n_color + (xtot + ytot) / 2);
		    bj = n_color;
		    }
		else
		    j = 0;

		break;

	    case 4:  // Moving average II
		if (d_color_z)
		    {
		    ztot = (dStrands - d_color_z) * 1000 * dFactor;

		    n_color = static_cast<int>(n_color + ztot);
		    }
		else
		    j = 0;

		rj = gj = bj = n_color;
		break;

	    case 5:
		if (n_color < maxit)
		    {
		    if (sum_sqrs_z() > 1)
			n_color = static_cast<int>((n_color - log(log(sum_sqrs_z())) / log(2)) * 50 * dFactor);
		    }
		else
		    j = 0;

		rj = gj = bj = n_color;
		break;

	    case 6:
		rj = ztot * dFactor;
		gj = rj + xsav * 10 * dFactor + n_color_z;
		bj = rj + ysav * 10 * dFactor + n_color_z;

		break;

	    case 7:
		rj = ztot * dFactor;
		gj = rj + xsav * 10 * dFactor + n_color_z;
		bj = rj + ysav * 10 * dFactor + n_color_z;


		break;

	    case 10:   // Rings I
		//if (n_color_z > 2)
		if (n_color_z)
		    {
		    ztot = fabs(limit - zsav) * 3000 * dFactor;  // 500
		    n_color = static_cast<int>(ztot);
		    rj = gj = bj = n_color;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			rj = gj = bj = 0;
			}
		    }
		break;

	    case 11:   // Rings II
		//if (n_color_z > 2)
		if (n_color_z)
		    {
		    ztot = fabs(limit - zsav) * 3000 * dFactor;  // 500
		    if (n_color_z % 2 == 0)
			{
			n_color = static_cast<int>(ztot);
			rj = bj = gj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(ztot + OFFSET_COLOR);
			rj = bj = gj = n_color;
			}
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			rj = gj = bj = 0;
			}
		    }
		break;

	    case 12:  // Rings III
		//if (n_color_z >= 1)
		if (n_color_z)
		    {
		    ztot = fabs(limit - zsav) * 3000 * dFactor;  // 500
		    if (n_color_z % 2 == 0)
			{
			n_color = static_cast<int>(ztot);
			rj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(ztot + OFFSET_COLOR);
			gj = n_color;
			}
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			rj = gj = bj = n_color;
			}
		    }

		bj = rj + gj;

		break;

	    case 14:   // Rings I
		if (n_color_z)
		    {
		    //ztot = (fabs(dStrands_HI - zsav))*50*dFactor;
		    ztot = (((dStrands_HI - zsav) * .5) / (dStrands_HI - dStrands_LO)) * 500 * dFactor;
		    rj = ztot * xsav;
		    gj = ztot * ysav;
		    bj = (rj + gj) / 2;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }
		break;

	    case 15:
		if (n_color >= maxit)
		    {
		    n_color = static_cast<int>(
			fabs(sin(z.real() * z.real() * 100)) *
			fabs(sin(z.imag() * z.imag() * 100)) *
			200 * dFactor);
		    }
		else
		    {
		    ssq1 = sum_sqrs_z();
		    if (ssq1 <= 2)
			ssq1 = 2;
		    n_color = static_cast<int>((n_color - log(log(ssq1)) / log(2)) * 10 * dFactor_2);
		    }
		rj = gj = bj = n_color;
		break;

	    case 16:
		if (n_color >= maxit)
		    {
		    n_color = static_cast<int>(
			fabs(sin(z.real() * z.real() * 100)) *
			fabs(sin(z.imag() * z.imag() * 100)) *
			200 * dFactor);
		    rj = gj = bj = n_color;
		    }
		else
		    {
		    ztot = atan(fabs(z.real() / z.imag())) -
			atan(fabs(z.imag() / z.real())) *
			60 * dFactor_2;

		    if (n_color % 2 == 0)
			{
			n_color = static_cast<int>(ztot);
			rj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(ztot + OFFSET_COLOR);
			gj = n_color;
			}

		    bj = rj + gj + n_color;
		    }
		break;

	    case 17:
		if (n_color_x || n_color_y)
		    {
		    if (n_color_x)
			xtot = xsav * 200 * dFactor;

		    if (n_color_y)
			ytot = ysav * 200 * dFactor;

		    if (n_color < maxit)
			{
			n_color = static_cast<int>(sqrt(xtot * xtot + ytot * ytot));
			rj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(
			    n_color + sqrt(xtot * xtot + ytot * ytot));
			gj = n_color;
			}

		    bj = rj + gj + n_color;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }

		break;

	    case 18:
		n_color_z = static_cast<int>(n_color_z + zsav * 3 * dFactor);
		rj = gj = bj = n_color_z;
		break;

	    case 19:
		if (n_color_z)
		    {
		    //if (n_color_z%2==0)
		      //n_color = n_color_z*2 + ztot*2*dFactor;
		    //else
		      //n_color = n_color_z*2 + ztot*2*dFactor + OFFSET_COLOR;

		    if (n_color_z % 2 == 0)
			{
			rj = ztot * 2 * dFactor;
			gj = ztot * 2 * dFactor + OFFSET_COLOR;
			}
		    else
			{
			rj = ztot * 2 * dFactor + OFFSET_COLOR;
			gj = ztot * 2 * dFactor;
			}

		    bj = (rj + gj) / 2;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }
		break;

	    case 20:
		if (n_color_z && n_color > 1)
		    {
		    ztot += (dStrands - zsav) * 1000 * dFactor;
		    if (n_color_z % 2 == 0)
			{
			n_color = static_cast<int>((n_color_z * 2 + ztot) / 2);
			rj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(
			    (n_color_z * 2 + ztot) / 2 + OFFSET_COLOR);
			gj = n_color;
			}
		    bj = rj + gj + n_color;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }

		break;

	    case 21:   // Flowers I
	    case 22:   // Flowers II
	    case 23:   // Flowers III
	    case 24:   // Flowers IV
	    case 25:   // Flowers V
		if (n_color < maxit && n_color_z == 0)
		    {
		    j = n_color = 0;
		    n_color_z = -1;  // sets the background to black
		    rj = gj = bj = n_color;
		    }

		if (n_color_z == 0)
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }

		if (n_color_z > 0)
		    {
		    //ztot += n_color_z
		      //+ (1 - zsav/dStrands)*1000*dFactor;  // 1300

		    if (n_color_z % 2 == 0)
			ztot = dif_test * 2 * dFactor;
		    else
			ztot = dif_test * 2 * dFactor + OFFSET_COLOR;

		    rj = ztot;
		    gj = ztot;
		    bj = ztot;

		    }
		break;

	    case 26:  // testing
		if (n_color_z && n_color > 1)
		    {
		    if (n_color_z % 2 == 0)
			{
			n_color = static_cast<int>(
			    n_color_z + ztot * 10 * dFactor);
			rj = n_color;
			}
		    else
			{
			n_color = static_cast<int>(
			    n_color_z + ztot * 10 * dFactor + OFFSET_COLOR);
			gj = n_color;
			}
		    bj = rj + gj + n_color;
		    }
		else
		    {
		    if (n_color < maxit)
			{
			j = n_color = 0;
			n_color_z = -1;
			}
		    rj = gj = bj = n_color;
		    }
		break;

	    case 27:  // Fractal Dimension
		break;

	    case 29:
		xtot *= dFactor;
		ytot *= dFactor;

		rj = (xtot * xtot + ytot * ytot);
		gj = rj;
		bj = rj;

		break;

	    case 30:
		xtot *= dFactor;
		ytot *= dFactor;

		rj = xtot * xtot;
		gj = (xtot * xtot + ytot * ytot);
		bj = ytot * ytot;

		break;

	    case 31:
		rj = gj = bj = 0;
		n_color_x = static_cast<int>(xtot * 1000 * dFactor);
		n_color_y = static_cast<int>(ytot * 1000 * dFactor);

		if (n_color_x || n_color_y)
		    {
		    if (n_color_x > n_color_y)
			{
			if (n_color_x < 256)
			    {
			    rj = n_color_x;
			    }
			else
			    if (n_color_x >= 256 && n_color_x < 512)
				{
				rj = 255;
				gj = n_color_x - 256;
				}
			    else
				if (n_color_x >= 512 && n_color_x < 768)
				    {
				    rj = gj = 255;
				    bj = n_color_x - 512;
				    }
				else
				    if (n_color_x >= 768)
					{
					rj = gj = bj = 255;
					}
			}
		    else
			{
			if (n_color_y < 256)
			    {
			    bj = n_color_y;
			    }
			else
			    if (n_color_y >= 256 && n_color_y < 512)
				{
				bj = 255;
				rj = n_color_y - 256;
				}
			    else
				if (n_color_y >= 512 && n_color_y < 768)
				    {
				    bj = rj = 255;
				    gj = n_color_y - 512;
				    }
				else
				    if (n_color_y >= 768)
					{
					rj = gj = bj = 255;
					}
			}
		    }
		else
		    j = 0;

		break;

	    case 32:
		rj = gj = bj = 0;

		if (n_color_x || n_color_y)
		    {
		    if (n_color_x)
			xtot = n_color_x + xtot * 100 * dFactor;

		    if (n_color_y)
			ytot = n_color_y + ytot * 100 * dFactor;

		    d = (xtot + ytot) / 2;

		    rj = d + xtot;
		    gj = d + ytot;
		    bj = d;
		    }
		else
		    j = 0;

		break;

	    case 33:  // FD Strands
	    case 34:
		if (n_color_x || n_color_y)
		    j = n_color;
		else
		    j = 0;

		break;

	    case 35:
	    case 36:
		if (n_color_z)
		    j = n_color;
		else
		    j = 0;
		break;

	    case 37:
		if (n_color_z)
		    j = n_color;
		else
		    j = 0;
		break;

	    case 38:
		j = n_color;
		break;

	    case 45:
		xtot = ztot;
		ytot = ztot;

	    case 44:  // diamonds
		if (xtot || ytot)
		    {
		    rj = xtot * dFactor;
		    gj = ytot * dFactor;
		    bj = (rj + gj) / 2;
		    }
		else
		    rj = gj = bj = 0;

		break;

	    case 46:
	    case 47:
		xtot = ztot;
		ytot = ztot;
		if (xtot || ytot)
		    {
		    if (n_color_z % 2 == 0)
			{
			rj = xtot * dFactor;
			gj = ytot * dFactor;
			bj = (rj + gj) / 2;
			}
		    else
			{
			gj = xtot * dFactor + OFFSET_COLOR;
			bj = ytot * dFactor + OFFSET_COLOR;
			rj = (bj + gj) / 2;
			}
		    }
		else
		    rj = gj = bj = 0;

		break;

	    case 48:
	    case 49:
		if (n_color_z)
		    j = n_color;
		else
		    j = 0;
		break;

	    case 50:

		if (xtot || ytot)
		    {
		    rj = xtot * dFactor * 5;  // *5
		    gj = ytot * dFactor * 5;	// *5		
		    //bj = sqrt(rj*rj + gj*gj);
		    bj = (rj + gj) / 2;
		    }
		else
		    rj = gj = bj = 0;

		/*
			if (xsav || ysav)
			{
				xtot*=dFactor;
				ytot*=dFactor;

				d = n_color + (xtot + ytot)/2;
				//d = sqrt(xtot*xtot + ytot*ytot);

				rj = d + xtot;
				gj = d + ytot;
				bj = d;

			}
			else
				j = rj = gj = bj = 0;


			xtot = sqrt(xtot*xtot + ytot*ytot);
			if (xtot)
			{
				if (xtot < 256)
				{
					rj += xtot;
				}
				else
				if (xtot >= 256 && xtot < 512)
				{
					rj = 255;
					gj += xtot - 256;
				}
				else
				if (xtot >= 512 && xtot < 768)
				{
					rj = gj = 255;
					bj += xtot - 512;
				}
			}
			else
				j = 0;

			*/

		break;

	    case 51:
		if (n_color_x || n_color_y)
		    {
		    if (n_color_x)
			//xtot = (dStrands - fabs(xsav))*1000*dFactor;
			xtot = (1 - fabs(xsav) / dStrands) * 100 * dFactor;

		    if (n_color_y)
			//ytot = (dStrands - fabs(ysav))*1000*dFactor;
			ytot = (1 - fabs(ysav) / dStrands) * 100 * dFactor;

		    d = (double)n_color + (xtot + ytot) / 2;

		    rj = d + (xtot) / 2;
		    gj = d + (ytot) / 2;
		    bj = d;
		    }
		else
		    j = 0;

		if (n_color_z)
		    {
		    ztot = (1 - zsav / dStrands) * 100 * dFactor;
		    rj += ztot;
		    gj += ztot;
		    bj += ztot;
		    }
		break;

	    case 52:
		if (n_color_x || n_color_y)
		    {
		    if (n_color_x)
			//xtot = (dStrands - fabs(xsav))*1000*dFactor;
			xtot = (1 - fabs(xsav) / dStrands) * 100 * dFactor;

		    if (n_color_y)
			//ytot = (dStrands - fabs(ysav))*1000*dFactor;
			ytot = (1 - fabs(ysav) / dStrands) * 100 * dFactor;

		    //d = (double) (n_color_y + n_color_x) + (xtot + ytot)/2;

		    rj = xtot;
		    bj = ytot;

		    if (rj > bj)
			gj = rj;
		    else
			gj = bj;

		    }

		if (n_color_z)
		    {
		    //ztot = (dStrands - zsav)*1000*dFactor;
		    ztot = (1 - zsav / dStrands) * 100 * dFactor;
		    rj += ztot;
		    gj += ztot;
		    bj += ztot;
		    }

		if (n_color_x || n_color_y)
		    {
		    if (n_color_x > n_color_y)
			{
			if (n_color_x < 256)
			    {
			    rj += n_color_x;
			    }
			else
			    if (n_color_x >= 256 && n_color_x < 512)
				{
				rj = 255;
				gj += n_color_x - 256;
				}
			    else
				if (n_color_x >= 512 && n_color_x < 768)
				    {
				    rj = gj = 255;
				    bj += n_color_x - 512;
				    }
			//else
			//if (n_color_x >= 768)
			//{
			//	rj = gj = bj = 255;
			//}
			}
		    else
			{
			if (n_color_y < 256)
			    {
			    bj += n_color_y;
			    }
			else
			    if (n_color_y >= 256 && n_color_y < 512)
				{
				bj = 255;
				rj += n_color_y - 256;
				}
			    else
				if (n_color_y >= 512 && n_color_y < 768)
				    {
				    bj = rj = 255;
				    gj += n_color_y - 512;
				    }
			//else
			//if (n_color_y >= 768)
			//{
			//	rj = gj = bj = 255;
			//}
			}
		    }
		else
		    j = 0;

		break;

	    default:
		break;
	}
    }

