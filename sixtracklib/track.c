// SixTrackLib
//
// Authors: R. De Maria, G. Iadarola, D. Pellegrini, H. Jasim
//
// Copyright 2017 CERN. This software is distributed under the terms of the GNU
// Lesser General Public License version 2.1, copied verbatim in the file
//`COPYING''.
//
// In applying this licence, CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization or
// submit itself to any jurisdiction.

#ifndef _GPUCODE

#include <math.h>
#include <stdio.h>

#ifndef __APPLE__
#define M_PI 3.14159265358979323846
#endif

#endif

#define CLIGHT 299792458

#include "particle.h"

int Drift_track(Particles *p, uint64_t ip, double length) {
  double xp, yp;
  xp = p->px[ip] * p->rpp[ip];
  yp = p->py[ip] * p->rpp[ip];
  p->x[ip] += xp * length;
  p->y[ip] += yp * length;
  p->sigma[ip] += length * (1 - p->rvv[ip] * (1 + (xp * xp + yp * yp) / 2));
  p->s[ip] += length;
  //  _DP("Drift_track: length=%g\n",length);
  return 1;
};

int DriftExact_track(Particles *p, uint64_t ip, double length) {
  double lpzi, lbzi, px, py, opd;
  opd = 1 + p->delta[ip];
  px = p->px[ip];
  py = p->py[ip];
  lpzi = length / sqrt(opd * opd - px * px - py * py);
  lbzi = (p->beta0[ip] * p->beta0[ip] * p->psigma[ip] + 1) * lpzi;
  p->x[ip] += px * lpzi;
  p->y[ip] += py * lpzi;
  p->sigma[ip] += length - lbzi;
  p->s[ip] += length;
  return 1;
}

int Multipole_track(Particles *p, uint64_t ip, uint64_t order, double l,
                    double hxl, double hyl, CLGLOBAL double *bal) {
  double x, y, chi, dpx, dpy, zre, zim, b1l, a1l, hxx, hyy;

  // printf("multipole: partid:%d, order:%d, bal[2]:%g \n",
  //        ip,order,bal[2]);

  dpx = bal[order * 2];
  dpy = bal[order * 2 + 1];
  x = p->x[ip];
  y = p->y[ip];
  chi = p->chi[ip];
  //  _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  for (int ii = order - 1; ii >= 0; ii--) {
    zre = (dpx * x - dpy * y);
    zim = (dpx * y + dpy * x);
    //    _DP("Multipole_track: y,x=%g %G\n",x,y);
    dpx = bal[ii * 2] + zre;
    dpy = bal[ii * 2 + 1] + zim;
    //    _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  }
  dpx = -chi * dpx;
  dpy = chi * dpy;
  //  _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  if (l > 0) {
    b1l = chi * bal[0];
    a1l = chi * bal[1];
    hxx = hxl / l * x;
    hyy = hyl / l * y;
    dpx += hxl + hxl * p->delta[ip] - b1l * hxx;
    dpy -= hyl + hyl * p->delta[ip] - a1l * hyy;
    p->sigma[ip] -= chi * (hxx - hyy) * l * p->rvv[ip];
  }
  p->px[ip] += dpx;
  p->py[ip] += dpy;
  return 1;
}

int Cavity_track(Particles *p, uint64_t ip, double volt, double freq,
                 double lag) {

  double phase, pt, opd, beta;
  phase = lag - 2 * M_PI / CLIGHT * freq * p->sigma[ip] / p->beta0[ip];
  p->psigma[ip] += p->chi[ip] * volt * sin(phase) / (p->p0c[ip] * p->beta0[ip]);
  pt = p->psigma[ip] * p->beta0[ip];
  opd = sqrt(pt * pt + 2 * p->psigma[ip] + 1);
  p->delta[ip] = opd - 1;
  beta = opd / (1 / p->beta0[ip] + pt);
  p->rpp[ip] = 1 / opd;
  p->rvv[ip] = p->beta0[ip] / beta;

  return 1;
}

int Cavity_track2(Particles *p, uint64_t ip, double volt, double freq,
                  double lag) {

  double sigma = Particles_sigma(p, ip);
  double beta0 = Particles_beta0(p, ip);
  double phase = lag - 2 * M_PI / CLIGHT * freq * p->sigma[ip] / p->beta0[ip];
  Particles_addto_energy(p, ip, volt * sin(phase));
  return 1;
}

int Align_track(Particles *p, uint64_t ip, double cz, double sz, double dx,
                double dy) {
  double xn, yn;
  xn = cz * p->x[ip] - sz * p->y[ip] - dx;
  yn = sz * p->x[ip] + cz * p->y[ip] - dy;
  p->x[ip] = xn;
  p->y[ip] = yn;
  xn = cz * p->px[ip] + sz * p->py[ip];
  yn = -sz * p->px[ip] + cz * p->py[ip];
  p->px[ip] = xn;
  p->py[ip] = yn;
  return 1;
};

int Rotation_track(Particles *p, uint64_t ip, double cx, double sx, double cpx, double spx, double cy, double sy, double cpy, double spy, double ap, double h, double fRF) {
                   
  double xn, yn, xpn, ypn;
  
  xn  = cx  * p->x[ip]  + sx  * p->px[ip];
  xpn = cpx * p->x[ip]  + spx * p->px[ip];
  yn  = cy  * p->y[ip]  + sy  * p->py[ip];
  ypn = cpy * p->y[ip]  + spy * p->py[ip];

  p->x[ip]  = xn;
  p->px[ip] = xpn;
  p->y[ip]  = yn;
  p->py[ip] = ypn;

  // sigma = sigma -b0*c_light*t=sigma-b0*c_light*t/t0*t0=
  // =sigma-b0*c_light*eta*psigma*t0 = sigma - b0*c_light*eta*psigma*1/frev=
  // = sigma - b0*c_light*eta*psigma*h/frf = sigma - (b0*c_light*h*eta/frf)*p  //sigma
  p->sigma[ip] -= (CLIGHT*h*ap/fRF)*p->psigma[ip];
  return 1;
};
