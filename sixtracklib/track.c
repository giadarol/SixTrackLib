//SixTrackLib
//
//Authors: R. De Maria, G. Iadarola, D. Pellegrini, H. Jasim
//
//Copyright 2017 CERN. This software is distributed under the terms of the GNU
//Lesser General Public License version 2.1, copied verbatim in the file
//`COPYING''.
//
//In applying this licence, CERN does not waive the privileges and immunities
//granted to it by virtue of its status as an Intergovernmental Organization or
//submit itself to any jurisdiction.


#ifndef _GPUCODE

#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846

#endif


#define CLIGHT 299792458

#include "particle.h"

#include "track.h"

inline int Drift_track(Particle* p, CLGLOBAL Drift *el){
  double xp, yp;
  double length=el->length;
  xp = p->px * p->rpp;
  yp = p->py * p->rpp;
  p->x += xp * length;
  p->y += yp * length;
  p->sigma += length * (1 - p->rvv*( 1 + (xp*xp+yp*yp)/2 ) );
  p->s+=length;
//  _DP("Drift_track: length=%g\n",length);
  return 1;
};


inline int DriftExact_track(Particle* p, CLGLOBAL DriftExact *el){
  double lpzi, lbzi, px, py, opd;
  double length = el->length;
  opd=1+p->delta;
  px=p->px; py=p->py;
  lpzi= length/sqrt(opd*opd-px*px-py*py);
  lbzi=(p->beta0*p->beta0*p->psigma+1)*lpzi;
  p->x += px*lpzi ;
  p->y += py*lpzi ;
  p->sigma += length - lbzi;
  p->s += length ;
  return 1;
}

inline int Multipole_track(Particle* p, CLGLOBAL Multipole *el){
  double x,y,chi,dpx,dpy,zre,zim,b1l,a1l,hxx,hyy;
  long int order=el->order;
  double hxl=el->hxl;
  double hyl=el->hyl;
  double l=el->l;
  CLGLOBAL double *bal = el->bal;
  dpx=bal[order*2];
  dpy=bal[order*2+1];
  x=p->x; y=p->y; chi=p->chi;
//  _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  for (int ii=order-1;ii>=0;ii--){
    zre=(dpx*x-dpy*y);
    zim=(dpx*y+dpy*x);
//    _DP("Multipole_track: y,x=%g %G\n",x,y);
    dpx=bal[ii*2]+zre;
    dpy=bal[ii*2+1]+zim;
//    _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  }
  dpx=-chi*dpx ;
  dpy=chi*dpy ;
//  _DP("Multipole_track: dpx,y=%g %G\n",dpx,dpy);
  if (l>0){
     b1l=chi*bal[0]; a1l=chi*bal[1];
     hxx=hxl/l*x; hyy=hyl/l*y;
     dpx+=hxl + hxl*p->delta - b1l*hxx;
     dpy-=hyl + hyl*p->delta - a1l*hyy;
     p->sigma-=chi*(hxx-hyy)*l*p->rvv;
  }
  p->px+=dpx ;  p->py+=dpy ;
  return 1 ;
}

inline int Cavity_track(Particle* p, CLGLOBAL Cavity *el){
  double volt = el->volt;
  double freq = el->freq;
  double lag = el->lag;
  double phase, pt, opd;
  phase=lag-2*M_PI/CLIGHT*freq*p->sigma/p->beta0;
  //printf("ggg00 %e %e\n",p->psigma,p->psigma+p->chi*volt/(p->p0c));
  p->psigma+=p->chi*volt*sin(phase)/(p->p0c*p->beta0);
  pt=p->psigma * p->beta0;
  opd=sqrt( pt*pt+ 2*p->psigma + 1 );
  p->delta=opd - 1;
  p->beta=opd/(1/p->beta0+pt);
  //p->gamma=1/sqrt(1-p->beta*p->beta);
  p->gamma=(pt*p->beta0+1)*p->gamma0;
  p->rpp=1/opd;
  p->rvv=p->beta0/p->beta;
  //printf("ggg2 %e %e %e\n",pt,opd,p->delta);
  return 1;
}

inline int Align_track(Particle* p, CLGLOBAL Align *el){
  double xn,yn;
  double cz = el->cz;
  double sz = el->sz;
  double dx = el->dx;
  double dy = el->dy;
  xn= cz*p->x-sz*p->y - dx;
  yn= sz*p->x+cz*p->y - dy;
  p->x=xn;
  p->y=yn;
  xn= cz*p->px+sz*p->py;
  yn=-sz*p->px+cz*p->py;
  p->px=xn;
  p->py=yn;
  return 1;
};

