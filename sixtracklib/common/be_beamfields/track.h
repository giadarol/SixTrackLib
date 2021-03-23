#ifndef SIXTRACKLIB_COMMON_BE_BEAMFIELDS_TRACK_BEAMFIELDS_H__
#define SIXTRACKLIB_COMMON_BE_BEAMFIELDS_TRACK_BEAMFIELDS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/physics_constants.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(BeamBeam4D);
struct NS(SCCoasting);
struct NS(SCQGaussProfile);
struct NS(SCInterpolatedProfile);
struct NS(BeamBeam6D);

SIXTRL_STATIC SIXTRL_FN NS(track_status_t)
NS(Track_particle_beam_beam_4d)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam4D) *const SIXTRL_RESTRICT bb );

SIXTRL_STATIC SIXTRL_FN NS(track_status_t)
NS(Track_particle_beam_beam_6d)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t)  const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam6D) *const SIXTRL_RESTRICT bb );

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN NS(track_status_t)
NS(Track_particle_space_charge_coasting)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SCCoasting) *const
        SIXTRL_RESTRICT sc_elem )  SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(track_status_t)
NS(Track_particle_space_charge_qgaussian_profile)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SCQGaussProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(track_status_t)
NS(Track_particle_space_charge_interpolated_profile)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SCInterpolatedProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/constants.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/be_beamfields/be_beamfields.h"
    #include "sixtracklib/common/internal/math_qgauss.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* BeamBeam4D: */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_beam_beam_4d)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const NS(BeamBeam4D) *const SIXTRL_RESTRICT bb )
{
    typedef SIXTRL_REAL_T real_t;
    typedef SIXTRL_BE_DATAPTR_DEC NS(BB4D_data)* data_ptr_t;

    data_ptr_t bb4ddata = ( data_ptr_t )NS(BeamBeam4D_const_data)( bb );

    /*
    // Test data transfer
    printf("4D: q_part = %e\n",bb4ddata->q_part);
    printf("4D: N_part = %e\n",bb4ddata->N_part);
    printf("4D: sigma_x = %e\n",bb4ddata->sigma_x);
    printf("4D: sigma_y = %e\n",bb4ddata->sigma_y);
    printf("4D: beta_s = %e\n",bb4ddata->beta_s);
    printf("4D: min_sigma_diff = %e\n",bb4ddata->min_sigma_diff);
    printf("4D: Delta_x = %e\n",bb4ddata->Delta_x);
    printf("4D: Delta_y = %e\n",bb4ddata->Delta_y);
    printf("4D: Dpx_sub = %e\n",bb4ddata->Dpx_sub);
    printf("4D: Dpy_sub = %e\n",bb4ddata->Dpy_sub);
    printf("4D: enabled = %ld\n",bb4ddata->enabled); */

    SIXTRL_ASSERT( NS(Particles_get_state_value)( p, ii )
        == ( NS(particle_num_elements_t) )1 );

    if (bb4ddata->enabled > 0.) {

        real_t px = NS(Particles_get_px_value)( p, ii );
        real_t py = NS(Particles_get_py_value)( p, ii );

        real_t qratio = 1.;// To be generalized for multi-ion!
        real_t charge = qratio*NS(Particles_get_q0_value)( p, ii )*SIXTRL_QELEM;

        real_t x = NS(Particles_get_x_value)( p, ii ) - bb4ddata->Delta_x;
        real_t y = NS(Particles_get_y_value)( p, ii ) - bb4ddata->Delta_y;

        real_t chi = NS(Particles_get_chi_value)( p, ii );

        real_t beta = NS(Particles_get_beta0_value)( p, ii ) \
                        /NS(Particles_get_rvv_value)( p, ii );
        real_t p0c = NS(Particles_get_p0c_value)( p, ii )*SIXTRL_QELEM;

        real_t Ex, Ey, Gx, Gy;
        NS(get_Ex_Ey_Gx_Gy_gauss)(x, y, bb4ddata->sigma_x, bb4ddata->sigma_y,
                bb4ddata->min_sigma_diff, 1,
                &Ex, &Ey, &Gx, &Gy);

        real_t fact_kick = chi * bb4ddata->N_part * bb4ddata->q_part * charge * \
            (1. + beta * bb4ddata->beta_s)/(p0c*(beta + bb4ddata->beta_s));

        px += (fact_kick*Ex - bb4ddata->Dpx_sub);
        py += (fact_kick*Ey - bb4ddata->Dpy_sub);

        NS(Particles_set_px_value)( p, ii, px );
        NS(Particles_set_py_value)( p, ii, py );
    }

    return SIXTRL_TRACK_SUCCESS;
}

/* ************************************************************************* */
/* NS(SCCoasting): */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_space_charge_coasting)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const NS(SCCoasting) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_REAL_T real_t;

    SIXTRL_ARGPTR_DEC real_t Ex;
    SIXTRL_ARGPTR_DEC real_t Ey;
    SIXTRL_ARGPTR_DEC real_t Gx;
    SIXTRL_ARGPTR_DEC real_t Gy;

    real_t const charge = NS(PhysConst_charge0_si)() *
        NS(Particles_get_q0_value)( particles, ii );

    real_t const beta0 = NS(Particles_get_beta0_value)( particles, ii );
    real_t const pc0   = NS(Particles_get_p0c_value)( particles, ii ) *
                         NS(PhysConst_charge0_si)();

    real_t fact_kick =
        NS(SCCoasting_number_of_particles)( sc_elem ) *
        NS(SCCoasting_length)( sc_elem ) *
        NS(Particles_get_chi_value)( particles, ii ) *
        NS(Particles_get_charge_ratio_value)( particles, ii ) *
        charge * charge * ( ( real_t )1 - beta0 * beta0 );

    fact_kick /= NS(SCCoasting_circumference)( sc_elem ) *
                 pc0 * beta0 * NS(Particles_get_rvv_value)( particles, ii );

    NS(get_Ex_Ey_Gx_Gy_gauss)(
        NS(Particles_get_x_value)( particles, ii ) -
            NS(SCCoasting_x_co)( sc_elem ),
        NS(Particles_get_y_value)( particles, ii ) -
            NS(SCCoasting_y_co)( sc_elem ),
        NS(SCCoasting_sigma_x)( sc_elem ),
        NS(SCCoasting_sigma_y)( sc_elem ),
        NS(SCCoasting_min_sigma_diff)( sc_elem ),
        ( int )1, &Ex, &Ey, &Gx, &Gy );

    NS(Particles_add_to_px_value)( particles, ii, fact_kick * Ex );
    NS(Particles_add_to_py_value)( particles, ii, fact_kick * Ey );

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

/* ************************************************************************* */
/* NS(SCQGaussProfile) */

SIXTRL_INLINE NS(track_status_t)
NS(Track_particle_space_charge_qgaussian_profile)( SIXTRL_PARTICLE_ARGPTR_DEC
        NS(Particles)* SIXTRL_RESTRICT p, NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const NS(SCQGaussProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_REAL_T real_t;

    SIXTRL_ARGPTR_DEC real_t Ex;
    SIXTRL_ARGPTR_DEC real_t Ey;
    SIXTRL_ARGPTR_DEC real_t Gx;
    SIXTRL_ARGPTR_DEC real_t Gy;

    real_t const charge = NS(PhysConst_charge0_si)() *
        NS(Particles_get_q0_value)( p, ii );

    real_t const beta0 = NS(Particles_get_beta0_value)( p, ii );
    real_t const beta  = beta0 * NS(Particles_get_rvv_value)( p, ii );
    real_t const pc0   = NS(Particles_get_p0c_value)( p, ii ) *
                         NS(PhysConst_charge0_si)();

    real_t const z = NS(Particles_get_zeta_value)( p, ii ) /
                     NS(Particles_get_rvv_value)( p, ii );

    real_t const bunchlength_rms =
        NS(SCQGaussProfile_bunchlength_rms)( sc_elem );

    real_t fact_kick =
        NS(Particles_get_chi_value)( p, ii ) *
        NS(Particles_get_charge_ratio_value)( p, ii ) *
        NS(SCQGaussProfile_length)( sc_elem ) *
        charge * charge * ( ( real_t )1 - beta0 * beta );

    SIXTRL_ASSERT( NS(Type_comp_all_more)(
        NS(Particles_get_rvv_value)( p, ii ), ( real_t )0 ) );

    SIXTRL_ASSERT( NS(Type_comp_all_more)(
        NS(Particles_get_beta0_value)( p, ii ), ( real_t )0 ) );

    SIXTRL_ASSERT( NS(Type_comp_all_less_or_equal)(
        NS(Particles_get_beta0_value)( p, ii ), ( real_t )1 ) );

    fact_kick *=
        NS(SCQGaussProfile_number_of_particles)( sc_elem );

    fact_kick *= NS(Math_q_gauss)( z,
        NS(SCQGaussProfile_q_param)( sc_elem ),
        NS(Math_q_gauss_sqrt_beta_from_gauss_sigma)( bunchlength_rms ),
        NS(SCQGaussProfile_cq)( sc_elem ) );

    fact_kick /= pc0 * beta;
    NS(get_Ex_Ey_Gx_Gy_gauss)(
            NS(Particles_get_x_value)( p, ii ) -
                NS(SCQGaussProfile_x_co)( sc_elem ),
            NS(Particles_get_y_value)( p, ii ) -
                NS(SCQGaussProfile_y_co)( sc_elem ),
            NS(SCQGaussProfile_sigma_x)( sc_elem ),
            NS(SCQGaussProfile_sigma_y)( sc_elem ),
            NS(SCQGaussProfile_min_sigma_diff)( sc_elem ),
            ( int )1, &Ex, &Ey, &Gx, &Gy );

    NS(Particles_add_to_px_value)( p, ii, fact_kick * Ex );
    NS(Particles_add_to_py_value)( p, ii, fact_kick * Ey );

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

/* ************************************************************************* */
/* NS(SCInterpolatedProfile) */

SIXTRL_INLINE NS(track_status_t)
NS(Track_particle_space_charge_interpolated_profile)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    SIXTRL_BE_ARGPTR_DEC const NS(SCInterpolatedProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT
{
    typedef SIXTRL_REAL_T real_t;

    SIXTRL_ARGPTR_DEC real_t Ex;
    SIXTRL_ARGPTR_DEC real_t Ey;
    SIXTRL_ARGPTR_DEC real_t Gx;
    SIXTRL_ARGPTR_DEC real_t Gy;

    real_t const charge = NS(PhysConst_charge0_si)() *
        NS(Particles_get_q0_value)( particles, ii );

    real_t const beta0 = NS(Particles_get_beta0_value)( particles, ii );
    real_t const beta  = beta0 * NS(Particles_get_rvv_value)( particles, ii );
    real_t const pc0   = NS(Particles_get_p0c_value)( particles, ii ) *
                         NS(PhysConst_charge0_si)();

    real_t fact_kick =
        NS(Particles_get_chi_value)( particles, ii ) *
        NS(Particles_get_charge_ratio_value)( particles, ii ) *
        NS(SCInterpolatedProfile_length)( sc_elem ) *
        NS(SCInterpolatedProfile_number_of_particles)( sc_elem ) *
        charge * charge * ( ( real_t )1 - beta0 * beta );

    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData) const* interpol =
        NS(SCInterpolatedProfile_const_line_density_profile_data)(
            sc_elem );

    if( ( interpol != SIXTRL_NULLPTR ) &&
        ( NS(LineDensityProfileData_method)( interpol ) !=
          NS(MATH_INTERPOL_NONE) ) &&
        ( NS(LineDensityProfileData_num_values)( interpol ) >
          ( NS(math_abscissa_idx_t) )0 ) )
    {
        fact_kick *= NS(LineDensityProfileData_interpolate_value)(
            interpol, NS(Particles_get_zeta_value)( particles, ii ) );
    }
    else
    {
        fact_kick *=
        NS(SCInterpolatedProfile_line_density_prof_fallback)( sc_elem );
    }

    fact_kick /= ( pc0 * beta );

    NS(get_Ex_Ey_Gx_Gy_gauss)(
            NS(Particles_get_x_value)( particles, ii ) -
                NS(SCInterpolatedProfile_x_co)( sc_elem ),
            NS(Particles_get_y_value)( particles, ii ) -
                NS(SCInterpolatedProfile_y_co)( sc_elem ),
            NS(SCInterpolatedProfile_sigma_x)( sc_elem ),
            NS(SCInterpolatedProfile_sigma_y)( sc_elem ),
            NS(SCInterpolatedProfile_min_sigma_diff)( sc_elem ),
            ( int )1, &Ex, &Ey, &Gx, &Gy );

    NS(Particles_add_to_px_value)( particles, ii, fact_kick * Ex );
    NS(Particles_add_to_py_value)( particles, ii, fact_kick * Ey );

    return ( NS(track_status_t) )SIXTRL_TRACK_SUCCESS;
}

/* ************************************************************************* */
/* BeamBeam6D: */

SIXTRL_INLINE NS(track_status_t) NS(Track_particle_beam_beam_6d)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t)  const ii,
    SIXTRL_BE_ARGPTR_DEC const NS(BeamBeam6D) *const SIXTRL_RESTRICT bb )
{
    typedef SIXTRL_REAL_T real_t;
    typedef SIXTRL_BE_DATAPTR_DEC NS(BB6D_data)* data_ptr_t;

    int i_slice;

    // Start Gianni's part
    data_ptr_t bb6ddata = ( data_ptr_t )NS(BeamBeam6D_const_data)( bb );

    SIXTRL_ASSERT( NS(Particles_get_state_value)( particles, ii )
        == ( NS(particle_num_elements_t) )1 );

    if (bb6ddata->enabled > 0.) {

        // Get pointers
        SIXTRL_BE_DATAPTR_DEC real_t* N_part_per_slice = SIXTRL_BB_GET_PTR(bb6ddata, N_part_per_slice);
		SIXTRL_BE_DATAPTR_DEC real_t* x_slices_star = SIXTRL_BB_GET_PTR(bb6ddata, x_slices_star);
		SIXTRL_BE_DATAPTR_DEC real_t* y_slices_star = SIXTRL_BB_GET_PTR(bb6ddata, y_slices_star);
		SIXTRL_BE_DATAPTR_DEC real_t* sigma_slices_star = SIXTRL_BB_GET_PTR(bb6ddata, sigma_slices_star);


        int N_slices = (int)(bb6ddata->N_slices);

        /*
        // Check data transfer
        printf("sphi=%e\n",(bb6ddata->parboost).sphi);
        printf("calpha=%e\n",(bb6ddata->parboost).calpha);
        printf("S33=%e\n",(bb6ddata->Sigmas_0_star).Sig_33_0);
        printf("N_slices=%d\n",N_slices);
        printf("N_part_per_slice[0]=%e\n",N_part_per_slice[0]);
        printf("N_part_per_slice[1]=%e\n",N_part_per_slice[1]);
        printf("x_slices_star[0]=%e\n",x_slices_star[0]);
        printf("x_slices_star[1]=%e\n",x_slices_star[1]);
        printf("y_slices_star[0]=%e\n",y_slices_star[0]);
        printf("y_slices_star[1]=%e\n",y_slices_star[1]);
        printf("sigma_slices_star[0]=%e\n",sigma_slices_star[0]);
        printf("sigma_slices_star[1]=%e\n",sigma_slices_star[1]);
        */

        real_t x = NS(Particles_get_x_value)( particles, ii );
        real_t px = NS(Particles_get_px_value)( particles, ii );
        real_t y = NS(Particles_get_y_value)( particles, ii );
        real_t py = NS(Particles_get_py_value)( particles, ii );
        real_t zeta = NS(Particles_get_zeta_value)( particles, ii );
        real_t delta = NS(Particles_get_delta_value)( particles, ii );

        real_t q0 = SIXTRL_QELEM*NS(Particles_get_q0_value)( particles, ii );
        real_t p0c = NS(Particles_get_p0c_value)( particles, ii ); // eV

        real_t P0 = p0c/SIXTRL_C_LIGHT*SIXTRL_QELEM;

        // Change reference frame
        real_t x_star =     x     - bb6ddata->x_CO    - bb6ddata->delta_x;
        real_t px_star =    px    - bb6ddata->px_CO;
        real_t y_star =     y     - bb6ddata->y_CO    - bb6ddata->delta_y;
        real_t py_star =    py    - bb6ddata->py_CO;
        real_t sigma_star = zeta  - bb6ddata->sigma_CO;
        real_t delta_star = delta - bb6ddata->delta_CO;

        // Boost coordinates of the weak beam
        NS(BeamBeam6D_boost)(
            &(bb6ddata->parboost), &x_star, &px_star, &y_star, &py_star,
            &sigma_star, &delta_star);


        // Synchro beam
        for (i_slice=0; i_slice<N_slices; i_slice++)
        {
            real_t sigma_slice_star = sigma_slices_star[i_slice];
            real_t x_slice_star = x_slices_star[i_slice];
            real_t y_slice_star = y_slices_star[i_slice];

            //Compute force scaling factor
            real_t Ksl = N_part_per_slice[i_slice]*bb6ddata->q_part*q0/(P0* SIXTRL_C_LIGHT);

            //Identify the Collision Point (CP)
            real_t S = 0.5*(sigma_star - sigma_slice_star);

            // Propagate sigma matrix
            real_t Sig_11_hat_star, Sig_33_hat_star, costheta, sintheta;
            real_t dS_Sig_11_hat_star, dS_Sig_33_hat_star, dS_costheta, dS_sintheta;

            // Get strong beam shape at the CP
            NS(BeamBeam6D_propagate_Sigma_matrix)(
                &(bb6ddata->Sigmas_0_star),
                S, bb6ddata->threshold_singular, 1,
                &Sig_11_hat_star, &Sig_33_hat_star,
                &costheta, &sintheta,
                &dS_Sig_11_hat_star, &dS_Sig_33_hat_star,
                &dS_costheta, &dS_sintheta);

            // Evaluate transverse coordinates of the weake baem w.r.t. the strong beam centroid
            real_t x_bar_star = x_star + px_star*S - x_slice_star;
            real_t y_bar_star = y_star + py_star*S - y_slice_star;

            // Move to the uncoupled reference frame
            real_t x_bar_hat_star = x_bar_star*costheta +y_bar_star*sintheta;
            real_t y_bar_hat_star = -x_bar_star*sintheta +y_bar_star*costheta;

            // Compute derivatives of the transformation
            real_t dS_x_bar_hat_star = x_bar_star*dS_costheta +y_bar_star*dS_sintheta;
            real_t dS_y_bar_hat_star = -x_bar_star*dS_sintheta +y_bar_star*dS_costheta;

            // Get transverse fieds
            real_t Ex, Ey;
            real_t Gx = ( real_t )0.0;
            real_t Gy = ( real_t )0.0;
            NS(get_Ex_Ey_Gx_Gy_gauss)(x_bar_hat_star, y_bar_hat_star,
                sqrt(Sig_11_hat_star), sqrt(Sig_33_hat_star), bb6ddata->min_sigma_diff, 0,
                &Ex, &Ey, &Gx, &Gy);

            // Compute kicks
            real_t Fx_hat_star = Ksl*Ex;
            real_t Fy_hat_star = Ksl*Ey;
            real_t Gx_hat_star = Ksl*Gx;
            real_t Gy_hat_star = Ksl*Gy;

            // Move kisks to coupled reference frame
            real_t Fx_star = Fx_hat_star*costheta - Fy_hat_star*sintheta;
            real_t Fy_star = Fx_hat_star*sintheta + Fy_hat_star*costheta;

            // Compute longitudinal kick
            real_t Fz_star = 0.5*(Fx_hat_star*dS_x_bar_hat_star  + Fy_hat_star*dS_y_bar_hat_star+
                           Gx_hat_star*dS_Sig_11_hat_star + Gy_hat_star*dS_Sig_33_hat_star);

            // Apply the kicks (Hirata's synchro-beam)
            delta_star = delta_star + Fz_star+0.5*(
                        Fx_star*(px_star+0.5*Fx_star)+
                        Fy_star*(py_star+0.5*Fy_star));
            x_star = x_star - S*Fx_star;
            px_star = px_star + Fx_star;
            y_star = y_star - S*Fy_star;
            py_star = py_star + Fy_star;


        }

        // Inverse boost on the coordinates of the weak beam
        NS(BeamBeam6D_inv_boost)(
            &(bb6ddata->parboost), &x_star, &px_star, &y_star, &py_star,
            &sigma_star, &delta_star);


        // Go back to original reference frame and remove dipolar effect
        x =     x_star     + bb6ddata->x_CO   + bb6ddata->delta_x  - bb6ddata->Dx_sub;
        px =    px_star    + bb6ddata->px_CO                       - bb6ddata->Dpx_sub;
        y =     y_star     + bb6ddata->y_CO   + bb6ddata->delta_y  - bb6ddata->Dy_sub;
        py =    py_star    + bb6ddata->py_CO                       - bb6ddata->Dpy_sub;
        zeta =  sigma_star + bb6ddata->sigma_CO                    - bb6ddata->Dsigma_sub;
        delta = delta_star + bb6ddata->delta_CO                    - bb6ddata->Ddelta_sub;


        NS(Particles_set_x_value)( particles, ii, x );
        NS(Particles_set_px_value)( particles, ii, px );
        NS(Particles_set_y_value)( particles, ii, y );
        NS(Particles_set_py_value)( particles, ii, py );
        NS(Particles_set_zeta_value)( particles, ii, zeta );
        NS(Particles_update_delta_value)( particles, ii, delta );
    }

    return SIXTRL_TRACK_SUCCESS;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BE_BEAMFIELDS_TRACK_BEAMFIELDS_H__ */
