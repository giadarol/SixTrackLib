#ifndef SIXTRACKLIB_COMMON_PARTICLES_H__
#define SIXTRACKLIB_COMMON_PARTICLES_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
    #include "sixtracklib/common/impl/buffer_defines.h"
    #include "sixtracklib/common/impl/buffer_type.h"
    #include "sixtracklib/common/impl/particles_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */

typedef SIXTRL_INT64_T  NS(particle_index_t);
typedef SIXTRL_REAL_T   NS(particle_real_t);
typedef SIXTRL_INT64_T  NS(particle_num_elements_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t)*
        NS(particle_real_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_real_t) const*
        NS(particle_real_const_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t)*
        NS(particle_index_ptr_t);

typedef SIXTRL_PARTICLE_DATAPTR_DEC NS(particle_index_t) const*
        NS(particle_index_const_ptr_t);

#if ( !defined( _GPUCODE ) ) && ( !defined( __cplusplus ) )

SIXTRL_STATIC_VAR NS(buffer_size_t) const
    NS(PARTICLES_NUM_DATAPTRS) = ( NS(buffer_size_t) )20u;

#else /* ( !defined( _GPUCODE ) ) && ( !defined( __cplusplus ) ) */

typedef enum
{
    NS(PARTICLES_NUM_DATAPTRS) = 20
}
NS(_ParticlesGlobalConstants);

#endif /* ( !defined( _GPUCODE ) ) && ( !defined( __cplusplus ) ) */

typedef struct NS(Particles)
{
    NS(particle_num_elements_t) num_particles              SIXTRL_ALIGN( 8 );

    NS(particle_real_ptr_t)  SIXTRL_RESTRICT q0            SIXTRL_ALIGN( 8 ); /* C */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT mass0         SIXTRL_ALIGN( 8 ); /* eV */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT beta0         SIXTRL_ALIGN( 8 ); /* nounit */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT gamma0        SIXTRL_ALIGN( 8 ); /* nounit */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT p0c           SIXTRL_ALIGN( 8 ); /* eV */

    NS(particle_real_ptr_t)  SIXTRL_RESTRICT s             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT x             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT y             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT px            SIXTRL_ALIGN( 8 ); /* Px/P0 */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT py            SIXTRL_ALIGN( 8 ); /* Py/P0 */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT zeta          SIXTRL_ALIGN( 8 ); /* */

    NS(particle_real_ptr_t)  SIXTRL_RESTRICT psigma        SIXTRL_ALIGN( 8 ); /* (E-E0) / (beta0 P0c) conjugate of sigma */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT delta         SIXTRL_ALIGN( 8 ); /* P/P0-1 = 1/rpp-1 */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT rpp           SIXTRL_ALIGN( 8 ); /* ratio P0 /P */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT rvv           SIXTRL_ALIGN( 8 ); /* ratio beta / beta0 */
    NS(particle_real_ptr_t)  SIXTRL_RESTRICT chi           SIXTRL_ALIGN( 8 ); /* q/q0 * m/m0  */

    NS(particle_index_ptr_t) SIXTRL_RESTRICT particle_id   SIXTRL_ALIGN( 8 );
    NS(particle_index_ptr_t) SIXTRL_RESTRICT at_element_id SIXTRL_ALIGN( 8 );
    NS(particle_index_ptr_t) SIXTRL_RESTRICT at_turn       SIXTRL_ALIGN( 8 );
    NS(particle_index_ptr_t) SIXTRL_RESTRICT state         SIXTRL_ALIGN( 8 );
}
NS(Particles);


typedef struct NS(ParticlesGenericAddr)
{
    NS(particle_num_elements_t) num_particles            SIXTRL_ALIGN( 8 );

    NS(buffer_addr_t) q0_addr            SIXTRL_ALIGN( 8 ); /* C */
    NS(buffer_addr_t) mass0_addr         SIXTRL_ALIGN( 8 ); /* eV */
    NS(buffer_addr_t) beta0_addr         SIXTRL_ALIGN( 8 ); /* nounit */
    NS(buffer_addr_t) gamma0_addr        SIXTRL_ALIGN( 8 ); /* nounit */
    NS(buffer_addr_t) p0c_addr           SIXTRL_ALIGN( 8 ); /* eV */

    NS(buffer_addr_t) s_addr             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(buffer_addr_t) x_addr             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(buffer_addr_t) y_addr             SIXTRL_ALIGN( 8 ); /* [m] */
    NS(buffer_addr_t) px_addr            SIXTRL_ALIGN( 8 ); /* Px/P0 */
    NS(buffer_addr_t) py_addr            SIXTRL_ALIGN( 8 ); /* Py/P0 */
    NS(buffer_addr_t) zeta_addr          SIXTRL_ALIGN( 8 ); /* */

    NS(buffer_addr_t) psigma_addr        SIXTRL_ALIGN( 8 ); /* (E-E0) / (beta0 P0c) conjugate of sigma */
    NS(buffer_addr_t) delta_addr         SIXTRL_ALIGN( 8 ); /* P/P0-1 = 1/rpp-1 */
    NS(buffer_addr_t) rpp_addr           SIXTRL_ALIGN( 8 ); /* ratio P0 /P */
    NS(buffer_addr_t) rvv_addr           SIXTRL_ALIGN( 8 ); /* ratio beta / beta0 */
    NS(buffer_addr_t) chi_addr           SIXTRL_ALIGN( 8 ); /* q/q0 * m/m0  */

    NS(buffer_addr_t) particle_id_addr   SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t) at_element_id_addr SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t) at_turn_addr       SIXTRL_ALIGN( 8 );
    NS(buffer_addr_t) state_addr         SIXTRL_ALIGN( 8 );
}
NS(ParticlesGenericAddr);


SIXTRL_FN SIXTRL_STATIC int NS(Particles_from_generic_addr_data)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticlesGenericAddr)
        *const SIXTRL_RESTRICT input_data,
    NS(buffer_size_t) const index_offset );

SIXTRL_FN SIXTRL_STATIC int NS(Particles_back_to_generic_addr_data)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticlesGenericAddr)* SIXTRL_RESTRICT output_data,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT particles,
    NS(buffer_size_t) const index_offset );

/* ========================================================================= */

#if !defined( _GPUCODE )

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Particles_get_required_num_slots)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Particles_get_required_num_dataptrs)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles );

SIXTRL_FN SIXTRL_STATIC bool NS(Particles_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_new)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_add)( SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const  num_particles,
    NS(particle_real_ptr_t)  q0_ptr,        NS(particle_real_ptr_t)  mass0_ptr,
    NS(particle_real_ptr_t)  beta0_ptr,     NS(particle_real_ptr_t)  gamma0_ptr,
    NS(particle_real_ptr_t)  p0c_ptr,       NS(particle_real_ptr_t)  s_ptr,
    NS(particle_real_ptr_t)  x_ptr,         NS(particle_real_ptr_t)  y_ptr,
    NS(particle_real_ptr_t)  px_ptr,        NS(particle_real_ptr_t)  py_ptr,
    NS(particle_real_ptr_t)  zeta_ptr,      NS(particle_real_ptr_t)  psigma_ptr,
    NS(particle_real_ptr_t)  delta_ptr,     NS(particle_real_ptr_t)  rpp_ptr,
    NS(particle_real_ptr_t)  rvv_ptr,       NS(particle_real_ptr_t)  chi_ptr,
    NS(particle_index_ptr_t) particle_id_ptr,
    NS(particle_index_ptr_t) at_element_id_ptr,
    NS(particle_index_ptr_t) at_turn_ptr,
    NS(particle_index_ptr_t) state_ptr );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p );

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
NS(Particles_preset)( SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_preset_values)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC NS(particle_num_elements_t)
NS(Particles_get_num_of_particles)( const SIXTRL_PARTICLE_ARGPTR_DEC
    NS(Particles) *const SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_num_of_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const num_of_particles );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Particles_get_num_dataptrs)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles) const*
NS(BufferIndex_get_const_particles)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT index );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(BufferIndex_get_particles)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT index );

SIXTRL_FN SIXTRL_STATIC NS(particle_num_elements_t)
NS(BufferIndex_get_total_num_of_particles_in_range)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t)
NS(BufferIndex_get_total_num_of_particle_blocks_in_range)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end );

SIXTRL_FN SIXTRL_STATIC SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
NS(BufferIndex_get_index_object_by_global_index_from_range)(
    NS(particle_num_elements_t) const global_index,
    NS(particle_num_elements_t) const begin_index_offset,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(particle_num_elements_t)*
        SIXTRL_RESTRICT ptr_result_index_offset );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_clear_single)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT praticles,
    NS(particle_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_clear_range)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT praticles,
    NS(particle_num_elements_t) const start_index,
    NS(particle_num_elements_t) const end_index );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT praticles );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_copy_single)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    NS(particle_num_elements_t) const destination_index,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source,
    NS(particle_num_elements_t) const source_index );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_copy_range)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
        SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT source,
    NS(particle_num_elements_t) const start_index,
    NS(particle_num_elements_t) const end_index );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_copy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT source );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_calculate_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT diff );

SIXTRL_FN SIXTRL_STATIC void NS( Particles_get_max_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(particle_num_elements_t)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT source );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE ) || defined( __CUDACC__ )

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_is_particles_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const buffer );

SIXTRL_FN SIXTRL_STATIC NS(particle_num_elements_t)
NS(Particles_buffer_get_total_num_of_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t)
NS(Particles_buffer_get_num_of_particle_blocks)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
NS(Particles_buffer_get_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const particle_obj_index  );

SIXTRL_FN SIXTRL_STATIC SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const*
NS(Particles_buffer_get_const_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const particle_obj_index );

SIXTRL_FN SIXTRL_STATIC bool NS(Particles_buffers_have_same_structure)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT rhs );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_buffers_calculate_difference)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT rhs,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT diff );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_buffer_get_max_value )(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT destination,
    SIXTRL_BUFFER_ARGPTR_DEC NS(particle_num_elements_t)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT source );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_buffer_clear_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer );

#endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_q0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
    NS(Particles_get_const_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_q0s );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_q0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const q0_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_q0s );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_mass0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t)
NS(Particles_get_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_mass0s );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_mass0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const mass0_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_mass0s );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_beta0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t)
NS(Particles_get_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_beta0s );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_beta0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const beta0_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_beta0s );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_gamma0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_gamma0s );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_gamma0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const gamma0_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_gamma0s );


/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_p0c_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t) NS(Particles_get_const_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_p0cs );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_p0c_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const p0c_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_p0cs );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t) NS(Particles_get_const_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_ss );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const s_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_ss );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const s_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_s_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT s_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const s_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_xs );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const x_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_xs );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const s_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_x_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT s_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const s_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t) NS(Particles_get_const_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_ys );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const y_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_ys );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const y_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_y_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT y_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const y_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_pxs );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const px_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_pxs );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const px_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_px_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT px_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const px_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_pys );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const py_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_pys );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const py_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_py_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT py_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const py_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t)
NS(Particles_get_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_zetas );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const zeta_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_zetas );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const zeta_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_zeta_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT zeta_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const zeta_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(Particles_get_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_psigmas );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const psigma_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_psigmas );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const psigma_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_psigma_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT psigma_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const psigma_diff_value );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index, NS(particle_real_t) const energy );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_energies );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const energy );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_energy_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_delta_energies );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t)
NS(Particles_get_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_deltas );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const delta_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_deltas );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const delta_diff_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_delta_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT delta_diff_values );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const delta_diff_value );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Particles_update_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const new_delta_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_update_delta_value_increment)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const delta_value_diff );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_deltas );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_rpp_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_rpps );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_rpp_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const rpp_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_rpps );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_rvv_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_rvvs );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_rvv_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const rvv_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_rvvs );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_real_t) NS(Particles_get_chi_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_const_ptr_t)
NS(Particles_get_const_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_real_ptr_t) NS(Particles_get_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_chis );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_chi_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const chi_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_chis );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_index_t) NS(Particles_get_particle_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_const_ptr_t)
NS(Particles_get_const_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_ptr_t)
NS(Particles_get_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_particle_ids );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_particle_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const particle_id_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_particle_ids );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_index_t)
NS(Particles_get_at_element_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_const_ptr_t)
NS(Particles_get_const_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_ptr_t)
NS(Particles_get_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_at_element_ids );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_at_element_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const at_element_id_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_at_element_ids );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_index_t)
NS(Particles_get_at_turn_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_const_ptr_t)
NS(Particles_get_const_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_ptr_t)
NS(Particles_get_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_at_turns );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_at_turn_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const at_turn_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_at_turns );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(particle_index_t) NS(Particles_get_state_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const ii );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_const_ptr_t)
NS(Particles_get_const_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC  const NS(Particles) *const SIXTRL_RESTRICT p );

SIXTRL_FN SIXTRL_STATIC NS(particle_index_ptr_t) NS(Particles_get_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_states );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_set_state_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const state_value );

SIXTRL_FN SIXTRL_STATIC void NS(Particles_assign_ptr_to_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC  NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_states );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====             Implementation of inline functions                ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #if !defined( _GPUCODE ) || defined( __CUDACC__ )
    #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE int NS(Particles_from_generic_addr_data)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(ParticlesGenericAddr) *const SIXTRL_RESTRICT in,
    NS(buffer_size_t) const offset )
{
    int success = -1;

    if( ( in != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) )
    {
        typedef NS(particle_num_elements_t)   num_elements_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T  const* ptr_in_real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T const* ptr_in_index_t;

        num_elements_t jj = ( num_elements_t )0u;
        num_elements_t ii = offset;

        num_elements_t const out_num_particles =
            NS(Particles_get_num_of_particles)( p );

        ptr_in_real_t  in_q0          = ( ptr_in_real_t  )in->q0_addr;
        ptr_in_real_t  in_mass0       = ( ptr_in_real_t  )in->mass0_addr;
        ptr_in_real_t  in_beta0       = ( ptr_in_real_t  )in->beta0_addr;
        ptr_in_real_t  in_gamma0      = ( ptr_in_real_t  )in->mass0_addr;
        ptr_in_real_t  in_p0c         = ( ptr_in_real_t  )in->p0c_addr;
        ptr_in_real_t  in_s           = ( ptr_in_real_t  )in->s_addr;
        ptr_in_real_t  in_x           = ( ptr_in_real_t  )in->x_addr;
        ptr_in_real_t  in_y           = ( ptr_in_real_t  )in->y_addr;
        ptr_in_real_t  in_px          = ( ptr_in_real_t  )in->px_addr;
        ptr_in_real_t  in_py          = ( ptr_in_real_t  )in->py_addr;
        ptr_in_real_t  in_zeta        = ( ptr_in_real_t  )in->zeta_addr;
        ptr_in_real_t  in_psigma      = ( ptr_in_real_t  )in->psigma_addr;
        ptr_in_real_t  in_delta       = ( ptr_in_real_t  )in->delta_addr;
        ptr_in_real_t  in_rpp         = ( ptr_in_real_t  )in->rpp_addr;
        ptr_in_real_t  in_rvv         = ( ptr_in_real_t  )in->rvv_addr;
        ptr_in_real_t  in_chi         = ( ptr_in_real_t  )in->chi_addr;
        ptr_in_index_t in_particle_id = ( ptr_in_index_t )in->particle_id_addr;
        ptr_in_index_t in_element_id  = ( ptr_in_index_t )in->at_element_id_addr;
        ptr_in_index_t in_turn        = ( ptr_in_index_t )in->at_turn_addr;
        ptr_in_index_t in_state       = ( ptr_in_index_t )in->state_addr;

        SIXTRL_ASSERT( in->num_particles > ( num_elements_t )offset );
        SIXTRL_ASSERT( in->num_particles >= ( out_num_particles + ii ) );

        SIXTRL_ASSERT( NS(Particles_get_q0)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_mass0)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_beta0)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_gamma0)( p )        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_p0c)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_s)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_x)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_y)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_px)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_py)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_zeta)( p )          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_psigma)( p )        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_delta)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_rpp)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_rvv)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_chi)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_particle_id)( p )   != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_at_element_id)( p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_at_turn)( p )       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_state)( p )         != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( in_q0           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_mass0        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_beta0        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_gamma0       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_p0c          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_s            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_x            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_y            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_px           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_py           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_zeta         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_psigma       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_delta        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_rpp          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_rvv          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_chi          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_particle_id  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_element_id   != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_turn         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( in_state        != SIXTRL_NULLPTR );

        success = 0;

        for( ; jj < out_num_particles ; ++jj, ++ii )
        {
            NS(Particles_set_q0_value)(            p, jj, in_q0[ ii ] );
            NS(Particles_set_mass0_value)(         p, jj, in_mass0[ ii ] );
            NS(Particles_set_beta0_value)(         p, jj, in_beta0[ ii ] );
            NS(Particles_set_gamma0_value)(        p, jj, in_gamma0[ ii ] );
            NS(Particles_set_p0c_value)(           p, jj, in_p0c[ ii ] );
            NS(Particles_set_s_value)(             p, jj, in_s[ ii ] );
            NS(Particles_set_x_value)(             p, jj, in_x[ ii ] );
            NS(Particles_set_y_value)(             p, jj, in_y[ ii ] );
            NS(Particles_set_px_value)(            p, jj, in_px[ ii ] );
            NS(Particles_set_py_value)(            p, jj, in_py[ ii ] );
            NS(Particles_set_zeta_value)(          p, jj, in_zeta[ ii ] );
            NS(Particles_set_psigma_value)(        p, jj, in_psigma[ ii ] );
            NS(Particles_set_delta_value)(         p, jj, in_delta[ ii ] );
            NS(Particles_set_rpp_value)(           p, jj, in_rpp[ ii ] );
            NS(Particles_set_rvv_value)(           p, jj, in_rvv[ ii ] );
            NS(Particles_set_chi_value)(           p, jj, in_chi[ ii ] );
            NS(Particles_set_particle_id_value)(   p, jj, in_particle_id[ ii ] );
            NS(Particles_set_at_element_id_value)( p, jj, in_element_id[ ii ] );
            NS(Particles_set_at_turn_value)(       p, jj, in_turn[ ii ] );
            NS(Particles_set_state_value)(         p, jj, in_state[ ii ] );
        }
    }

    return success;
}

SIXTRL_INLINE int NS(Particles_back_to_generic_addr_data)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(ParticlesGenericAddr)* SIXTRL_RESTRICT out,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(buffer_size_t) const offset )
{
    int success = -1;

    if( ( out != SIXTRL_NULLPTR ) && ( p != SIXTRL_NULLPTR ) )
    {
        typedef NS(particle_num_elements_t)   num_elements_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_REAL_T*  ptr_out_real_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC SIXTRL_INT64_T* ptr_out_index_t;

        num_elements_t ii = offset;
        num_elements_t jj = ( num_elements_t )0u;

        num_elements_t const in_num_particles =
            NS(Particles_get_num_of_particles)( p );

        ptr_out_real_t  out_q0          = ( ptr_out_real_t  )out->q0_addr;
        ptr_out_real_t  out_mass0       = ( ptr_out_real_t  )out->mass0_addr;
        ptr_out_real_t  out_beta0       = ( ptr_out_real_t  )out->beta0_addr;
        ptr_out_real_t  out_gamma0      = ( ptr_out_real_t  )out->mass0_addr;
        ptr_out_real_t  out_p0c         = ( ptr_out_real_t  )out->p0c_addr;
        ptr_out_real_t  out_s           = ( ptr_out_real_t  )out->s_addr;
        ptr_out_real_t  out_x           = ( ptr_out_real_t  )out->x_addr;
        ptr_out_real_t  out_y           = ( ptr_out_real_t  )out->y_addr;
        ptr_out_real_t  out_px          = ( ptr_out_real_t  )out->px_addr;
        ptr_out_real_t  out_py          = ( ptr_out_real_t  )out->py_addr;
        ptr_out_real_t  out_zeta        = ( ptr_out_real_t  )out->zeta_addr;
        ptr_out_real_t  out_psigma      = ( ptr_out_real_t  )out->psigma_addr;
        ptr_out_real_t  out_delta       = ( ptr_out_real_t  )out->delta_addr;
        ptr_out_real_t  out_rpp         = ( ptr_out_real_t  )out->rpp_addr;
        ptr_out_real_t  out_rvv         = ( ptr_out_real_t  )out->rvv_addr;
        ptr_out_real_t  out_chi         = ( ptr_out_real_t  )out->chi_addr;
        ptr_out_index_t out_particle_id = ( ptr_out_index_t )out->particle_id_addr;
        ptr_out_index_t out_element_id  = ( ptr_out_index_t )out->at_element_id_addr;
        ptr_out_index_t out_turn        = ( ptr_out_index_t )out->at_turn_addr;
        ptr_out_index_t out_state       = ( ptr_out_index_t )out->state_addr;

        SIXTRL_ASSERT( ( num_elements_t )offset  <= out->num_particles );
        SIXTRL_ASSERT( ( in_num_particles + jj ) <= out->num_particles );

        SIXTRL_ASSERT( NS(Particles_get_const_q0)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_mass0)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_beta0)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_gamma0)( p )        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_p0c)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_s)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_x)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_y)( p )             != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_px)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_py)( p )            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_zeta)( p )          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_psigma)( p )        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_delta)( p )         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_rpp)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_rvv)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_chi)( p )           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_particle_id)( p )   != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_at_element_id)( p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_at_turn)( p )       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_state)( p )         != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( out_q0           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_mass0        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_beta0        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_gamma0       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_p0c          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_s            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_x            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_y            != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_px           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_py           != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_zeta         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_psigma       != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_delta        != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_rpp          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_rvv          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_chi          != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_particle_id  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_element_id   != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_turn         != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( out_state        != SIXTRL_NULLPTR );

        success = 0;

        for( ; jj < in_num_particles ; ++jj, ++ii )
        {
            out_q0[ ii ]          = NS(Particles_get_q0_value)(            p, jj );
            out_mass0[ ii ]       = NS(Particles_get_mass0_value)(         p, jj );
            out_beta0[ ii ]       = NS(Particles_get_beta0_value)(         p, jj );
            out_gamma0[ ii ]      = NS(Particles_get_gamma0_value)(        p, jj );
            out_p0c[ ii ]         = NS(Particles_get_p0c_value)(           p, jj );
            out_s[ ii ]           = NS(Particles_get_s_value)(             p, jj );
            out_x[ ii ]           = NS(Particles_get_x_value)(             p, jj );
            out_y[ ii ]           = NS(Particles_get_y_value)(             p, jj );
            out_px[ ii ]          = NS(Particles_get_px_value)(            p, jj );
            out_py[ ii ]          = NS(Particles_get_py_value)(            p, jj );
            out_zeta[ ii ]        = NS(Particles_get_zeta_value)(          p, jj );
            out_psigma[ ii ]      = NS(Particles_get_psigma_value)(        p, jj );
            out_delta[ ii ]       = NS(Particles_get_delta_value)(         p, jj );
            out_rpp[ ii ]         = NS(Particles_get_rpp_value)(           p, jj );
            out_rvv[ ii ]         = NS(Particles_get_rvv_value)(           p, jj );
            out_chi[ ii ]         = NS(Particles_get_chi_value)(           p, jj );
            out_particle_id[ ii ] = NS(Particles_get_particle_id_value)(   p, jj );
            out_element_id[ ii ]  = NS(Particles_get_at_element_id_value)( p, jj );
            out_turn[ ii ]        = NS(Particles_get_at_turn_value)(       p, jj );
            out_state[ ii ]       = NS(Particles_get_state_value)(         p, jj );
        }
    }

    return success;
}


#if !defined( _GPUCODE )
SIXTRL_INLINE NS(buffer_size_t) NS(Particles_get_required_num_slots)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles )
{
    typedef NS(buffer_size_t) buf_size_t;

    buf_size_t const num_dataptrs = NS(PARTICLES_NUM_DATAPTRS);

    SIXTRL_STATIC_VAR buf_size_t const real_size =
        sizeof( NS(particle_real_t) );

    SIXTRL_STATIC_VAR buf_size_t const index_size =
        sizeof( NS(particle_index_t) );

    buf_size_t const sizes[] =
    {
        real_size,  real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,  real_size,
        index_size, index_size, index_size, index_size
    };

    buf_size_t const counts[] =
    {
        num_particles, num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles
    };

    buf_size_t const slot_size = ( buffer != SIXTRL_NULLPTR )
        ? NS(Buffer_get_slot_size)( buffer )
        : NS(BUFFER_DEFAULT_SLOT_SIZE);

    buf_size_t requ_num_slots = NS(ManagedBuffer_predict_required_num_slots)(
        SIXTRL_NULLPTR, sizeof( NS(Particles) ), num_dataptrs,
            sizes, counts, slot_size );

    return requ_num_slots;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Particles_get_required_num_dataptrs)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles )
{
    typedef NS(buffer_size_t) buf_size_t;

    ( void )buffer;
    buf_size_t const num_dataptrs = NS(PARTICLES_NUM_DATAPTRS);
    return num_particles * num_dataptrs;
}

SIXTRL_INLINE bool NS(Particles_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_dataptrs )
{
    typedef NS(buffer_size_t) buf_size_t;

    buf_size_t const num_dataptrs = NS(PARTICLES_NUM_DATAPTRS);
    buf_size_t const real_size    = sizeof( NS(particle_real_t) );
    buf_size_t const index_size   = sizeof( NS(particle_index_t) );

    buf_size_t const sizes[] =
    {
        real_size,  real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,  real_size,
        index_size, index_size, index_size, index_size
    };

    buf_size_t const counts[] =
    {
        num_particles, num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles
    };

    return NS(Buffer_can_add_object)( buffer, sizeof( NS(Particles) ),
        num_dataptrs, sizes, counts, requ_objects, requ_slots, requ_dataptrs );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)* NS(Particles_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles )
{
    typedef NS(Particles)                          particles_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC particles_t* ptr_to_particles_t;

    NS(buffer_size_t) const real_size  = sizeof( SIXTRL_REAL_T  );
    NS(buffer_size_t) const int64_size = sizeof( SIXTRL_INT64_T );

    NS(buffer_size_t) const offsets[] =
    {
        offsetof( particles_t, q0 ),
        offsetof( particles_t, mass0 ),
        offsetof( particles_t, beta0 ),
        offsetof( particles_t, gamma0 ),
        offsetof( particles_t, p0c ),
        offsetof( particles_t, s ),
        offsetof( particles_t, x ),
        offsetof( particles_t, y ),
        offsetof( particles_t, px ),
        offsetof( particles_t, py ),
        offsetof( particles_t, zeta ),
        offsetof( particles_t, psigma ),
        offsetof( particles_t, delta ),
        offsetof( particles_t, rpp ),
        offsetof( particles_t, rvv ),
        offsetof( particles_t, chi ),
        offsetof( particles_t, particle_id ),
        offsetof( particles_t, at_element_id ),
        offsetof( particles_t, at_turn ),
        offsetof( particles_t, state )
    };

    NS(buffer_size_t) const sizes[] =
    {
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        int64_size, int64_size, int64_size, int64_size
    };

    NS(buffer_size_t) const counts[] =
    {
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles
    };

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Buffer_has_datastore)( buffer ) );
    SIXTRL_ASSERT( NS(Buffer_allow_append_objects)( buffer ) );
    SIXTRL_ASSERT( NS(PARTICLES_NUM_DATAPTRS) == 20u );

    NS(Particles) particles;
    NS(Particles_preset)( &particles );
    NS(Particles_set_num_of_particles)( &particles, num_particles );

    return ( ptr_to_particles_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &particles, sizeof( NS(Particles) ),
            NS(OBJECT_TYPE_PARTICLE), NS(PARTICLES_NUM_DATAPTRS),
                offsets, sizes, counts ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)* NS(Particles_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const num_particles,
    NS(particle_real_ptr_t)  q0_ptr,
    NS(particle_real_ptr_t)  mass0_ptr,
    NS(particle_real_ptr_t)  beta0_ptr,
    NS(particle_real_ptr_t)  gamma0_ptr,
    NS(particle_real_ptr_t)  p0c_ptr,
    NS(particle_real_ptr_t)  s_ptr,
    NS(particle_real_ptr_t)  x_ptr,
    NS(particle_real_ptr_t)  y_ptr,
    NS(particle_real_ptr_t)  px_ptr,
    NS(particle_real_ptr_t)  py_ptr,
    NS(particle_real_ptr_t)  zeta_ptr,
    NS(particle_real_ptr_t)  psigma_ptr,
    NS(particle_real_ptr_t)  delta_ptr,
    NS(particle_real_ptr_t)  rpp_ptr,
    NS(particle_real_ptr_t)  rvv_ptr,
    NS(particle_real_ptr_t)  chi_ptr,
    NS(particle_index_ptr_t) particle_id_ptr,
    NS(particle_index_ptr_t) at_element_id_ptr,
    NS(particle_index_ptr_t) at_turn_ptr,
    NS(particle_index_ptr_t) state_ptr )
{
    typedef NS(Particles)                          particles_t;
    typedef SIXTRL_BUFFER_DATAPTR_DEC particles_t* ptr_to_particles_t;

    NS(buffer_size_t) const real_size  = sizeof( SIXTRL_REAL_T  );
    NS(buffer_size_t) const int64_size = sizeof( SIXTRL_INT64_T );

    NS(buffer_size_t) const offsets[] =
    {
        offsetof( particles_t, q0 ),
        offsetof( particles_t, mass0 ),
        offsetof( particles_t, beta0 ),
        offsetof( particles_t, gamma0 ),
        offsetof( particles_t, p0c ),
        offsetof( particles_t, s ),
        offsetof( particles_t, x ),
        offsetof( particles_t, y ),
        offsetof( particles_t, px ),
        offsetof( particles_t, py ),
        offsetof( particles_t, zeta ),
        offsetof( particles_t, psigma ),
        offsetof( particles_t, delta ),
        offsetof( particles_t, rpp ),
        offsetof( particles_t, rvv ),
        offsetof( particles_t, chi ),
        offsetof( particles_t, particle_id ),
        offsetof( particles_t, at_element_id ),
        offsetof( particles_t, at_turn ),
        offsetof( particles_t, state )
    };

    NS(buffer_size_t) const sizes[] =
    {
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        real_size,  real_size,  real_size,  real_size,
        int64_size, int64_size, int64_size, int64_size
    };

    NS(buffer_size_t) const counts[] =
    {
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles,
        num_particles, num_particles, num_particles, num_particles
    };

    SIXTRL_ASSERT( buffer != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Buffer_has_datastore)( buffer ) );
    SIXTRL_ASSERT( NS(Buffer_allow_append_objects)( buffer ) );
    SIXTRL_ASSERT( NS(PARTICLES_NUM_DATAPTRS) == 20u );

    NS(Particles) particles;
    NS(Particles_set_num_of_particles)(           &particles, num_particles );

    NS(Particles_assign_ptr_to_q0)(            &particles, q0_ptr );
    NS(Particles_assign_ptr_to_mass0)(         &particles, mass0_ptr );
    NS(Particles_assign_ptr_to_beta0)(         &particles, beta0_ptr );
    NS(Particles_assign_ptr_to_gamma0)(        &particles, gamma0_ptr );
    NS(Particles_assign_ptr_to_p0c)(           &particles, p0c_ptr );

    NS(Particles_assign_ptr_to_s)(             &particles, s_ptr );
    NS(Particles_assign_ptr_to_x)(             &particles, x_ptr );
    NS(Particles_assign_ptr_to_y)(             &particles, y_ptr );
    NS(Particles_assign_ptr_to_px)(            &particles, px_ptr );
    NS(Particles_assign_ptr_to_py)(            &particles, py_ptr );
    NS(Particles_assign_ptr_to_zeta)(          &particles, zeta_ptr );

    NS(Particles_assign_ptr_to_psigma)(        &particles, psigma_ptr );
    NS(Particles_assign_ptr_to_delta)(         &particles, delta_ptr );
    NS(Particles_assign_ptr_to_rpp)(           &particles, rpp_ptr );
    NS(Particles_assign_ptr_to_rvv)(           &particles, rvv_ptr );
    NS(Particles_assign_ptr_to_chi)(           &particles, chi_ptr );

    NS(Particles_assign_ptr_to_particle_id)(   &particles, particle_id_ptr );
    NS(Particles_assign_ptr_to_at_element_id)( &particles, at_element_id_ptr );
    NS(Particles_assign_ptr_to_at_turn)(       &particles, at_turn_ptr );
    NS(Particles_assign_ptr_to_state)(         &particles, state_ptr );

    return ( ptr_to_particles_t )( uintptr_t )NS(Object_get_begin_addr)(
        NS(Buffer_add_object)( buffer, &particles, sizeof( NS(Particles) ),
            NS(OBJECT_TYPE_PARTICLE), NS(PARTICLES_NUM_DATAPTRS),
                offsets, sizes, counts ) );
}

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(Particles)*
NS(Particles_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p )
{
    return NS(Particles_add)(
        buffer, NS(Particles_get_num_of_particles)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_q0)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_mass0)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_beta0)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_gamma0)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_p0c)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_s)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_x)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_y)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_px)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_py)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_zeta)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_psigma)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_delta)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_rpp)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_rvv)( p ),
        ( NS(particle_real_ptr_t) )NS(Particles_get_const_chi)( p ),
        ( NS(particle_index_ptr_t ) )NS(Particles_get_const_particle_id)( p ),
        ( NS(particle_index_ptr_t ) )NS(Particles_get_const_at_element_id)( p ),
        ( NS(particle_index_ptr_t ) )NS(Particles_get_const_at_turn)( p ),
        ( NS(particle_index_ptr_t ) )NS(Particles_get_const_state)( p ) );
}

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* NS(Particles_preset)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    if( particles != SIXTRL_NULLPTR )
    {
        particles->q0            = SIXTRL_NULLPTR;
        particles->mass0         = SIXTRL_NULLPTR;
        particles->beta0         = SIXTRL_NULLPTR;
        particles->gamma0        = SIXTRL_NULLPTR;
        particles->p0c           = SIXTRL_NULLPTR;

        particles->s             = SIXTRL_NULLPTR;
        particles->x             = SIXTRL_NULLPTR;
        particles->px            = SIXTRL_NULLPTR;
        particles->y             = SIXTRL_NULLPTR;
        particles->py            = SIXTRL_NULLPTR;
        particles->zeta          = SIXTRL_NULLPTR;

        particles->psigma        = SIXTRL_NULLPTR;
        particles->delta         = SIXTRL_NULLPTR;
        particles->rpp           = SIXTRL_NULLPTR;
        particles->rvv           = SIXTRL_NULLPTR;
        particles->chi           = SIXTRL_NULLPTR;

        particles->particle_id   = SIXTRL_NULLPTR;
        particles->at_element_id = SIXTRL_NULLPTR;
        particles->at_turn       = SIXTRL_NULLPTR;
        particles->state         = SIXTRL_NULLPTR;

        NS(Particles_set_num_of_particles)(
            particles, ( NS(particle_num_elements_t) )0 );
    }

    return particles;
}

SIXTRL_INLINE void NS(Particles_preset_values)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p )
{
    typedef NS(buffer_size_t)           buf_size_t;
    typedef NS(particle_num_elements_t) elem_size_t;

    elem_size_t const temp_num_particles =
        NS(Particles_get_num_of_particles)( p );

    buf_size_t const num_of_particles = ( temp_num_particles >= 0 )
        ? ( buf_size_t )temp_num_particles : ( buf_size_t )0u;

    if( ( p != SIXTRL_NULLPTR ) &&
        ( num_of_particles > ( buf_size_t )0u ) )
    {
        buf_size_t ii = 0;

        NS(particle_real_t)  const ZERO_REAL      = ( NS(particle_real_t)  )0;
        NS(particle_index_t) const PARTICLE_ID    = ( NS(particle_index_t) )-1;
        NS(particle_index_t) const ELEMENT_ID     = ( NS(particle_index_t) )-1;
        NS(particle_index_t) const TURN_ID        = ( NS(particle_index_t) )-1;
        NS(particle_index_t) const PARTICLE_STATE = ( NS(particle_index_t) )-1;

        SIXTRL_ASSERT( NS(Particles_get_const_q0)(     p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_beta0)(  p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_mass0)(  p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_gamma0)( p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_p0c)(    p ) != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( NS(Particles_get_const_s)(      p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_x)(      p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_y)(      p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_px)(     p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_py)(     p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_zeta)(   p ) != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( NS(Particles_get_const_psigma)( p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_delta)(  p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_rpp)(    p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_rvv)(    p ) != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( NS(Particles_get_const_chi)(    p ) != SIXTRL_NULLPTR );

        SIXTRL_ASSERT( SIXTRL_NULLPTR !=
            NS(Particles_get_const_particle_id)( p ) );

        SIXTRL_ASSERT( SIXTRL_NULLPTR !=
            NS(Particles_get_const_at_element_id)( p ) );

        SIXTRL_ASSERT( SIXTRL_NULLPTR !=
            NS(Particles_get_const_at_turn)( p ) );

        SIXTRL_ASSERT( SIXTRL_NULLPTR !=
            NS(Particles_get_const_state)( p ) );


        for( ; ii < num_of_particles ; ++ii )
        {
            NS(Particles_set_q0_value)(            p, ii, ZERO_REAL );
            NS(Particles_set_beta0_value)(         p, ii, ZERO_REAL );
            NS(Particles_set_mass0_value)(         p, ii, ZERO_REAL );
            NS(Particles_set_gamma0_value)(        p, ii, ZERO_REAL );
            NS(Particles_set_p0c_value)(           p, ii, ZERO_REAL );

            NS(Particles_set_s_value)(             p, ii, ZERO_REAL );
            NS(Particles_set_x_value)(             p, ii, ZERO_REAL );
            NS(Particles_set_y_value)(             p, ii, ZERO_REAL );
            NS(Particles_set_px_value)(            p, ii, ZERO_REAL );
            NS(Particles_set_py_value)(            p, ii, ZERO_REAL );
            NS(Particles_set_zeta_value)(          p, ii, ZERO_REAL );

            NS(Particles_set_psigma_value)(        p, ii, ZERO_REAL );
            NS(Particles_set_delta_value)(         p, ii, ZERO_REAL );
            NS(Particles_set_rpp_value)(           p, ii, ZERO_REAL );
            NS(Particles_set_rvv_value)(           p, ii, ZERO_REAL );
            NS(Particles_set_chi_value)(           p, ii, ZERO_REAL );

            NS(Particles_set_particle_id_value)(   p, ii, PARTICLE_ID );
            NS(Particles_set_at_element_id_value)( p, ii, ELEMENT_ID  );
            NS(Particles_set_at_turn_value)(       p, ii, TURN_ID );
            NS(Particles_set_state_value)(         p, ii, PARTICLE_STATE );
        }
    }

    return;
}

SIXTRL_INLINE NS(particle_num_elements_t)
NS(Particles_get_num_of_particles)(
    const SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) *const SIXTRL_RESTRICT p )
{
    return ( p != SIXTRL_NULLPTR )
        ? p->num_particles : ( NS(particle_num_elements_t) )0;
}

SIXTRL_INLINE void NS(Particles_set_num_of_particles)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const num_of_particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->num_particles = num_of_particles;
    return;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Particles_get_num_dataptrs)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p )
{
    ( void ) p;
    return NS(PARTICLES_NUM_DATAPTRS);
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles) const*
NS(BufferIndex_get_const_particles)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT obj_index )
{
    typedef NS(Particles) particles_t;
    typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC particles_t const* ptr_to_particles_t;
    ptr_to_particles_t ptr_to_particles = SIXTRL_NULLPTR;

    if( ( obj_index != SIXTRL_NULLPTR ) &&
        ( NS(Object_get_type_id)( obj_index ) == NS(OBJECT_TYPE_PARTICLE) ) &&
        ( NS(Object_get_size)( obj_index ) > sizeof( NS(Particles) ) ) )
    {
        ptr_to_particles = ( ptr_to_particles_t )( uintptr_t
            )NS(Object_get_begin_addr)( obj_index );
    }

    return ptr_to_particles;
}

SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles)*
NS(BufferIndex_get_particles)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT index )
{
    typedef NS(Particles) particles_t;
    typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC particles_t* ptr_to_particles_t;
    return ( ptr_to_particles_t )NS(BufferIndex_get_const_particles)( index );
}


SIXTRL_INLINE NS(particle_num_elements_t)
NS(BufferIndex_get_total_num_of_particles_in_range)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end )
{
    typedef NS(particle_num_elements_t) num_elem_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

    num_elem_t total_num_particles = ( num_elem_t )0u;

    if( it != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( ( ( uintptr_t )it ) <= ( ( uintptr_t )end ) );

        for( ; it != end ; ++it )
        {
            if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
            {
                total_num_particles += NS(Particles_get_num_of_particles)(
                    ( ptr_particles_t )( uintptr_t )NS(Object_get_begin_addr)(
                        it ) );
            }
        }
    }

    return total_num_particles;
}


SIXTRL_INLINE NS(buffer_size_t)
NS(BufferIndex_get_total_num_of_particle_blocks_in_range)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end )
{
    typedef NS(buffer_size_t) buf_size_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

    buf_size_t num_particle_blocks = ( buf_size_t )0u;

    if( it != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( ( ( uintptr_t )it ) <= ( ( uintptr_t )end ) );

        for( ; it != end ; ++it )
        {
            if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
            {
                ptr_particles_t ptr_particles = ( ptr_particles_t )( uintptr_t
                    )NS(Object_get_begin_addr)( it );

                if( ptr_particles != SIXTRL_NULLPTR )
                {
                    ++num_particle_blocks;
                }
            }
        }
    }

    return num_particle_blocks;
}


SIXTRL_INLINE SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
NS(BufferIndex_get_index_object_by_global_index_from_range)(
    NS(particle_num_elements_t) const global_index,
    NS(particle_num_elements_t) const begin_index_offset,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(particle_num_elements_t)*
        SIXTRL_RESTRICT ptr_result_index_offset )
{
    typedef NS(particle_num_elements_t)                     num_elem_t;
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)  const* obj_iter_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

    obj_iter_t ptr_index = SIXTRL_NULLPTR;
    num_elem_t block_begin_index = begin_index_offset;
    num_elem_t block_end_index   = begin_index_offset;

    SIXTRL_ASSERT( ( ( uintptr_t )it ) <= ( ( uintptr_t )end ) );
    SIXTRL_ASSERT( global_index >= begin_index_offset );
    SIXTRL_ASSERT( begin_index_offset >= ( num_elem_t )0u );

    for( ; it != end ; ++it )
    {
        if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
        {
            ptr_particles_t particles = ( ptr_particles_t )( uintptr_t
                )NS(Object_get_begin_addr)( it );

            num_elem_t const num_particles =
                NS(Particles_get_num_of_particles)( particles );

            SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( num_particles > ( num_elem_t )0u );

            block_end_index += num_particles;

            if( ( block_begin_index <= global_index ) &&
                ( block_end_index   >  global_index ) )
            {
                ptr_index = it;
                break;
            }

            block_begin_index = block_end_index;
        }
    }

    if( ptr_index != SIXTRL_NULLPTR )
    {
        SIXTRL_ASSERT( block_begin_index <= global_index );
        SIXTRL_ASSERT( block_end_index   >  global_index );

        if(  ptr_result_index_offset != SIXTRL_NULLPTR )
        {
            *ptr_result_index_offset  = block_begin_index;
        }
    }
    else if( it == end )
    {
        SIXTRL_ASSERT( block_end_index == block_begin_index );
        ptr_index = end;

        if(  ptr_result_index_offset != SIXTRL_NULLPTR )
        {
            *ptr_result_index_offset  = block_end_index;
        }
    }
    else
    {
        /* Never should get here -> we'll return SIXTRL_NULLPTR and
         * set the offset to -1 for good measure, in case somebody is
         * not checking on the return value :-) */

        if(  ptr_result_index_offset != SIXTRL_NULLPTR )
        {
            *ptr_result_index_offset  = -1;
        }
    }

    return ptr_index;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE void NS(Particles_copy_single)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    NS(particle_num_elements_t) const destination_idx,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source,
    NS(particle_num_elements_t) const source_idx )
{
    SIXTRL_ASSERT(
        ( destination != 0 ) && ( source != 0 ) &&
        ( NS(Particles_get_num_of_particles)( destination ) > destination_idx ) &&
        ( NS(Particles_get_num_of_particles)( source )      > source_idx      ) );

    NS(Particles_set_q0_value)( destination, destination_idx,
          NS(Particles_get_q0_value)( source, source_idx ) );

    NS(Particles_set_mass0_value)( destination, destination_idx,
        NS(Particles_get_mass0_value)( source, source_idx ) );

    NS(Particles_set_beta0_value)( destination, destination_idx,
        NS(Particles_get_beta0_value)( source, source_idx ) );

    NS(Particles_set_gamma0_value)( destination, destination_idx,
        NS(Particles_get_gamma0_value)( source, source_idx ) );

    NS(Particles_set_p0c_value)( destination, destination_idx,
        NS(Particles_get_p0c_value)( source, source_idx ) );

    NS(Particles_set_s_value)( destination, destination_idx,
        NS(Particles_get_s_value)( source, source_idx ) );

    NS(Particles_set_x_value)( destination, destination_idx,
        NS(Particles_get_x_value)( source, source_idx ) );

    NS(Particles_set_y_value)( destination, destination_idx,
        NS(Particles_get_y_value)( source, source_idx ) );

    NS(Particles_set_px_value)( destination, destination_idx,
        NS(Particles_get_px_value)( source, source_idx ) );

    NS(Particles_set_py_value)( destination, destination_idx,
        NS(Particles_get_py_value)( source, source_idx ) );

    NS(Particles_set_zeta_value)( destination, destination_idx,
        NS(Particles_get_zeta_value)( source, source_idx ) );

    NS(Particles_set_psigma_value)( destination, destination_idx,
        NS(Particles_get_psigma_value)( source, source_idx ) );

    NS(Particles_set_delta_value)( destination, destination_idx,
        NS(Particles_get_delta_value)( source, source_idx ) );

    NS(Particles_set_rpp_value )( destination, destination_idx,
        NS(Particles_get_rpp_value)( source, source_idx ) );

    NS(Particles_set_rvv_value)( destination, destination_idx,
        NS( Particles_get_rvv_value)( source, source_idx ) );

    NS(Particles_set_chi_value)( destination, destination_idx,
        NS(Particles_get_chi_value)( source, source_idx ) );

    NS(Particles_set_particle_id_value)( destination, destination_idx,
        NS(Particles_get_particle_id_value)( source, source_idx ) );

    NS(Particles_set_at_element_id_value)( destination, destination_idx,
        NS( Particles_get_at_element_id_value)( source, source_idx ) );

    NS(Particles_set_at_turn_value)( destination, destination_idx,
        NS(Particles_get_at_turn_value)( source, source_idx ) );

    NS(Particles_set_state_value)( destination, destination_idx,
        NS(Particles_get_state_value)( source, source_idx ) );

    return;
}

SIXTRL_INLINE void NS(Particles_copy_range)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source,
    NS(particle_num_elements_t) const start,
    NS(particle_num_elements_t) const end )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_to_copy = ( start <= end )
        ? ( end - start ) : ( num_elem_t )0;

    SIXTRL_ASSERT(
        ( destination != SIXTRL_NULLPTR ) &&
        ( source      != SIXTRL_NULLPTR ) && ( start >= 0 ) &&
        ( NS(Particles_get_num_of_particles)( destination ) >= end ) &&
        ( NS(Particles_get_num_of_particles)( source )      >= end ) );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->q0[ start ],
                             &source->q0[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->beta0[ start ],
                             &source->beta0[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->mass0[ start ],
                             &source->mass0[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->gamma0[ start ],
                             &source->gamma0[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->p0c[ start ],
                             &source->p0c[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->s[ start ],
                             &source->s[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->x[ start ],
                             &source->x[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->y[ start ],
                             &source->y[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->px[ start ],
                             &source->px[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->py[ start ],
                             &source->py[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->zeta[ start ],
                             &source->zeta[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->psigma[ start ],
                             &source->psigma[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->delta[ start ],
                             &source->delta[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->rpp[ start ],
                             &source->rpp[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->rvv[ start ],
                             &source->rvv[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), &destination->chi[ start ],
                             &source->chi[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_index_t),
                             &destination->particle_id[ start ],
                             &source->particle_id[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_index_t),
                             &destination->at_element_id[ start ],
                             &source->at_element_id[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_index_t),
                             &destination->at_turn[ start ],
                             &source->at_turn[ start ], num_to_copy );

    SIXTRACKLIB_COPY_VALUES( NS(particle_index_t),
                             &destination->state[ start ],
                             &source->state[ start ], num_to_copy );

    return;
}

SIXTRL_INLINE void NS(Particles_copy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num = NS(Particles_get_num_of_particles)( source );

    SIXTRL_ASSERT(
        ( destination != SIXTRL_NULLPTR ) &&
        ( source      != SIXTRL_NULLPTR ) &&
        ( num >  ( num_elem_t )0u ) &&
        ( num == ( NS(Particles_get_num_of_particles)( destination ) ) ) );

    NS(Particles_copy_range)( destination, source, 0, num );
    return;
}

SIXTRL_INLINE void NS(Particles_calculate_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT diff )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles = NS(Particles_get_num_of_particles)( lhs );

    if( ( lhs  != SIXTRL_NULLPTR ) &&
        ( rhs  != SIXTRL_NULLPTR ) &&
        ( diff != SIXTRL_NULLPTR ) &&
        ( num_particles >  ( num_elem_t )0u ) &&
        ( num_particles == NS(Particles_get_num_of_particles)( rhs  ) ) &&
        ( num_particles == NS(Particles_get_num_of_particles)( diff ) ) )
    {
        num_elem_t ii = 0;

        for( ; ii < num_particles ; ++ii )
        {
            NS(Particles_set_q0_value)( diff, ii,
                NS(Particles_get_q0_value)( lhs, ii ) -
                NS(Particles_get_q0_value)( rhs, ii ) );

            NS(Particles_set_mass0_value)( diff, ii,
                NS(Particles_get_mass0_value)( lhs, ii ) -
                NS(Particles_get_mass0_value)( rhs, ii ) );

            NS(Particles_set_beta0_value)( diff, ii,
                NS(Particles_get_beta0_value)( lhs, ii ) -
                NS(Particles_get_beta0_value)( rhs, ii ) );

            NS(Particles_set_gamma0_value)( diff, ii,
                NS(Particles_get_gamma0_value)( lhs, ii ) -
                NS(Particles_get_gamma0_value)( rhs, ii ) );

            NS(Particles_set_p0c_value)( diff, ii,
                NS(Particles_get_p0c_value)( lhs, ii ) -
                NS(Particles_get_p0c_value)( rhs, ii ) );

            NS(Particles_set_s_value)( diff, ii,
                NS(Particles_get_s_value)( lhs, ii ) -
                NS(Particles_get_s_value)( rhs, ii ) );

            NS(Particles_set_x_value)( diff, ii,
                NS(Particles_get_x_value)( lhs, ii ) -
                NS(Particles_get_x_value)( rhs, ii ) );

            NS(Particles_set_y_value)( diff, ii,
                NS(Particles_get_y_value)( lhs, ii ) -
                NS(Particles_get_y_value)( rhs, ii ) );

            NS(Particles_set_px_value)( diff, ii,
                NS(Particles_get_px_value)( lhs, ii ) -
                NS(Particles_get_px_value)( rhs, ii ) );

            NS(Particles_set_py_value)( diff, ii,
                NS(Particles_get_py_value)( lhs, ii ) -
                NS(Particles_get_py_value)( rhs, ii ) );

            NS(Particles_set_zeta_value)( diff, ii,
                NS(Particles_get_zeta_value)( lhs, ii ) -
                NS(Particles_get_zeta_value)( rhs, ii ) );

            NS(Particles_set_psigma_value)( diff, ii,
                NS(Particles_get_psigma_value)( lhs, ii ) -
                NS(Particles_get_psigma_value)( rhs, ii ) );

            NS(Particles_set_delta_value)( diff, ii,
                NS(Particles_get_delta_value)( lhs, ii ) -
                NS(Particles_get_delta_value)( rhs, ii ) );

            NS(Particles_set_rpp_value)( diff, ii,
                NS(Particles_get_rpp_value)( lhs, ii ) -
                NS(Particles_get_rpp_value)( rhs, ii ) );

            NS(Particles_set_rvv_value)( diff, ii,
                NS(Particles_get_rvv_value)( lhs, ii ) -
                NS(Particles_get_rvv_value)( rhs, ii ) );

            NS(Particles_set_chi_value)( diff, ii,
                NS(Particles_get_chi_value)( lhs, ii ) -
                NS(Particles_get_chi_value)( rhs, ii ) );

            NS(Particles_set_particle_id_value)( diff, ii,
                NS(Particles_get_particle_id_value)( lhs, ii ) -
                NS(Particles_get_particle_id_value)( rhs, ii ) );

            NS(Particles_set_at_element_id_value)( diff, ii,
                NS(Particles_get_at_element_id_value)( lhs, ii ) -
                NS(Particles_get_at_element_id_value)( rhs, ii ) );

            NS(Particles_set_at_turn_value)( diff, ii,
                NS(Particles_get_at_turn_value)( lhs, ii ) -
                NS(Particles_get_at_turn_value)( rhs, ii ) );

            NS(Particles_set_state_value)( diff, ii,
                NS(Particles_get_state_value)( lhs, ii ) -
                NS(Particles_get_state_value)( rhs, ii ) );
        }
    }

    return;
}

SIXTRL_INLINE void NS(Particles_get_max_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(particle_num_elements_t)* SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT source )
{
    typedef NS(buffer_size_t)        buf_size_t;
    typedef NS(particle_real_ptr_t)  real_ptr_t;
    typedef NS(particle_real_t)      real_t;
    typedef NS(particle_index_ptr_t) index_ptr_t;
    typedef NS(particle_index_t)     index_t;

    SIXTRL_STATIC_VAR real_t const     ZERO      = ( real_t )0;
    SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

    if( ( destination != SIXTRL_NULLPTR ) &&
        ( source      != SIXTRL_NULLPTR ) &&
        ( NS(Particles_get_num_of_particles)( destination ) > 0u ) &&
        ( NS(Particles_get_num_of_particles)( source      ) > 0u ) )
    {
        buf_size_t dummy_max_value_indices[ 20 ] =
        {
            ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE,
            ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE,
            ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE,
            ZERO_SIZE, ZERO_SIZE, ZERO_SIZE, ZERO_SIZE
        };

        real_ptr_t out_real_values_begin[ 16 ] =
        {
            NS(Particles_get_q0)(     destination ),
            NS(Particles_get_beta0)(  destination ),
            NS(Particles_get_mass0)(  destination ),
            NS(Particles_get_gamma0)( destination ),
            NS(Particles_get_p0c)(    destination ),
            NS(Particles_get_s)(      destination ),
            NS(Particles_get_x)(      destination ),
            NS(Particles_get_y)(      destination ),
            NS(Particles_get_px)(     destination ),
            NS(Particles_get_py)(     destination ),
            NS(Particles_get_zeta)(   destination ),
            NS(Particles_get_psigma)( destination ),
            NS(Particles_get_delta)(  destination ),
            NS(Particles_get_rpp)(    destination ),
            NS(Particles_get_rvv)(    destination ),
            NS(Particles_get_chi)(    destination )
        };

        index_ptr_t out_index_values_begin[ 4 ] =
        {
            ( index_ptr_t )NS(Particles_get_particle_id)(   destination ),
            ( index_ptr_t )NS(Particles_get_at_element_id)( destination ),
            ( index_ptr_t )NS(Particles_get_at_turn)(       destination ),
            ( index_ptr_t )NS(Particles_get_state)(         destination )
        };

        real_ptr_t in_real_values_begin[ 16 ] =
        {
            ( real_ptr_t )NS(Particles_get_const_q0)(     source ),
            ( real_ptr_t )NS(Particles_get_const_beta0)(  source ),
            ( real_ptr_t )NS(Particles_get_const_mass0)(  source ),
            ( real_ptr_t )NS(Particles_get_const_gamma0)( source ),
            ( real_ptr_t )NS(Particles_get_const_p0c)(    source ),
            ( real_ptr_t )NS(Particles_get_const_s)(      source ),
            ( real_ptr_t )NS(Particles_get_const_x)(      source ),
            ( real_ptr_t )NS(Particles_get_const_y)(      source ),
            ( real_ptr_t )NS(Particles_get_const_px)(     source ),
            ( real_ptr_t )NS(Particles_get_const_py)(     source ),
            ( real_ptr_t )NS(Particles_get_const_zeta)(   source ),
            ( real_ptr_t )NS(Particles_get_const_psigma)( source ),
            ( real_ptr_t )NS(Particles_get_const_delta)(  source ),
            ( real_ptr_t )NS(Particles_get_const_rpp)(    source ),
            ( real_ptr_t )NS(Particles_get_const_rvv)(    source ),
            ( real_ptr_t )NS(Particles_get_const_chi)(    source )
        };

        index_ptr_t in_index_values_begin[ 4 ] =
        {
            ( index_ptr_t )NS(Particles_get_const_particle_id)(   source ),
            ( index_ptr_t )NS(Particles_get_const_at_element_id)( source ),
            ( index_ptr_t )NS(Particles_get_const_at_turn)(       source ),
            ( index_ptr_t )NS(Particles_get_const_state)(         source )
        };

        buf_size_t ii = 0;
        buf_size_t jj = 0;

        buf_size_t const num_particles =
            NS(Particles_get_num_of_particles)( destination );

        real_ptr_t in_real_values_end[ 16 ] =
        {
            in_real_values_begin[  0 ] + num_particles,
            in_real_values_begin[  1 ] + num_particles,
            in_real_values_begin[  2 ] + num_particles,
            in_real_values_begin[  3 ] + num_particles,
            in_real_values_begin[  4 ] + num_particles,
            in_real_values_begin[  5 ] + num_particles,
            in_real_values_begin[  6 ] + num_particles,
            in_real_values_begin[  7 ] + num_particles,
            in_real_values_begin[  8 ] + num_particles,
            in_real_values_begin[  9 ] + num_particles,
            in_real_values_begin[ 10 ] + num_particles,
            in_real_values_begin[ 11 ] + num_particles,
            in_real_values_begin[ 12 ] + num_particles,
            in_real_values_begin[ 13 ] + num_particles,
            in_real_values_begin[ 14 ] + num_particles,
            in_real_values_begin[ 15 ] + num_particles
        };

        index_ptr_t in_index_values_end[ 4 ] =
        {
            in_index_values_begin[  0 ] + num_particles,
            in_index_values_begin[  1 ] + num_particles,
            in_index_values_begin[  2 ] + num_particles,
            in_index_values_begin[  3 ] + num_particles
        };

        for( ; ii < 16 ; ++ii )
        {
            real_ptr_t in_it     = in_real_values_begin[ ii ];
            real_ptr_t in_end    = in_real_values_end[ ii ];

            real_t max_value     = ( real_t )0.0;
            real_t cmp_max_value = max_value;

            buf_size_t kk = ZERO_SIZE;
            dummy_max_value_indices[ ii ] = ZERO_SIZE;

            for( ; in_it != in_end ; ++in_it, ++kk )
            {
                real_t const value     = *in_it;
                real_t const cmp_value = ( value >= ZERO ) ? value : -value;

                if( cmp_max_value < cmp_value )
                {
                    max_value = value;
                    cmp_max_value = cmp_value;
                    dummy_max_value_indices[ ii ] = kk;
                }
            }

            *out_real_values_begin[ ii ] = max_value;
        }

        for( ii = 0, jj = 16 ; ii < 4 ; ++ii, ++jj )
        {
            index_ptr_t in_it     = in_index_values_begin[ ii ];
            index_ptr_t in_end    = in_index_values_end[ ii ];

            index_t max_value     = ( index_t )0;
            index_t cmp_max_value = max_value;

            buf_size_t kk = ZERO_SIZE;
            dummy_max_value_indices[ jj ] = ZERO_SIZE;

            for( ; in_it != in_end ; ++in_it, ++kk )
            {
                index_t const value     = *in_it;
                index_t const cmp_value = ( value > 0 ) ? value : -value;

                if( cmp_max_value < cmp_value )
                {
                    cmp_max_value = cmp_value;
                    max_value     = value;
                    dummy_max_value_indices[ jj ] = kk;
                }
            }

            *out_index_values_begin[ ii ] = max_value;
        }

        if( max_value_index != 0 )
        {
            SIXTRACKLIB_COPY_VALUES( buf_size_t, max_value_index,
                                     &dummy_max_value_indices[ 0 ], 20 );

            max_value_index = max_value_index + 20;
        }
    }

    return;
}

SIXTRL_INLINE void NS(Particles_clear_single)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index )
{
    typedef NS(particle_num_elements_t) num_elem_t;
    typedef NS(particle_real_t)         real_t;
    typedef NS(particle_index_t)        index_t;

    num_elem_t const num_particles = NS(Particles_get_num_of_particles)( p );

    if( ( index >= ( num_elem_t )0u ) &&
        ( index < num_particles ) )
    {
        SIXTRL_STATIC_VAR real_t  const ZERO = ( real_t )0;

        NS(Particles_set_q0_value)(     p, index, ZERO );
        NS(Particles_set_mass0_value)(  p, index, ZERO );
        NS(Particles_set_beta0_value)(  p, index, ZERO );
        NS(Particles_set_gamma0_value)( p, index, ZERO );
        NS(Particles_set_p0c_value)(    p, index, ZERO );

        NS(Particles_set_s_value)(      p, index, ZERO );
        NS(Particles_set_x_value)(      p, index, ZERO );
        NS(Particles_set_y_value)(      p, index, ZERO );
        NS(Particles_set_px_value)(     p, index, ZERO );
        NS(Particles_set_py_value)(     p, index, ZERO );
        NS(Particles_set_zeta_value)(   p, index, ZERO );
        NS(Particles_set_psigma_value)( p, index, ZERO );

        NS(Particles_set_delta_value)(  p, index, ZERO );
        NS(Particles_set_rpp_value)(    p, index, ZERO );
        NS(Particles_set_rvv_value)(    p, index, ZERO );
        NS(Particles_set_chi_value)(    p, index, ZERO );

        NS(Particles_set_particle_id_value)(   p, index, ( index_t )0 );
        NS(Particles_set_at_element_id_value)( p, index, ( index_t )0 );
        NS(Particles_set_at_turn_value)(       p, index, ( index_t )0 );
        NS(Particles_set_state_value)(         p, index, ( index_t )0 );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_clear_range)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const start_index,
    NS(particle_num_elements_t) const end_index )
{
    typedef NS(particle_num_elements_t) num_elem_t;
    typedef NS(particle_real_t)         real_t;
    typedef NS(particle_index_t)        index_t;

    num_elem_t const num_particles = NS(Particles_get_num_of_particles)( p );

    if( ( start_index   >= ( num_elem_t )0u ) &&
        ( end_index     >= start_index ) &&
        ( num_particles >= end_index ) )
    {
        SIXTRL_STATIC_VAR real_t  const ZERO = ( real_t )0;
        SIXTRL_STATIC_VAR index_t const ZERO_INDEX = ( index_t )0;

        num_elem_t const len = ( end_index - start_index );

        NS(particle_real_ptr_t)  real_begin  = NS(Particles_get_q0)( p );
        NS(particle_index_ptr_t) index_begin = NS(Particles_get_particle_id)( p );

        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_mass0)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_beta0)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_gamma0)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_p0c)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_s)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_x)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_y)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_px)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_py)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_zeta)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_psigma)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_delta)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_rpp)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_rvv)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        real_begin = NS(Particles_get_chi)( p );
        SIXTRL_ASSERT( real_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( real_t, real_begin + start_index, len, ZERO );

        /* ----------------------------------------------------------------- */

        index_begin = NS(Particles_get_particle_id)( p );
        SIXTRL_ASSERT( index_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( index_t, index_begin + start_index,
                                len, ZERO_INDEX );

        index_begin = NS(Particles_get_at_element_id)( p );
        SIXTRL_ASSERT( index_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( index_t, index_begin + start_index,
                                len, ZERO_INDEX );

        index_begin = NS(Particles_get_at_turn)( p );
        SIXTRL_ASSERT( index_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( index_t, index_begin + start_index,
                                len, ZERO_INDEX );

        index_begin = NS(Particles_get_state)( p );
        SIXTRL_ASSERT( index_begin != SIXTRL_NULLPTR );
        SIXTRACKLIB_SET_VALUES( index_t, index_begin + start_index,
                                len,  ZERO_INDEX );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_clear)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    NS(Particles_clear_range)(
        particles, 0, NS(Particles_get_num_of_particles)( particles ) );

    return;
}

#if !defined( _GPUCODE ) || defined( __CUDACC__ )

SIXTRL_INLINE bool NS(Buffer_is_particles_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const buffer )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    buf_size_t const num_blocks = NS(Buffer_get_num_of_objects)( buffer );

    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( buffer ) );

    return ( ( num_blocks > ZERO ) && ( num_blocks ==
        NS(Particles_buffer_get_num_of_particle_blocks)( buffer ) ) );
}

SIXTRL_INLINE NS(particle_num_elements_t)
NS(Particles_buffer_get_total_num_of_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC  NS(Object) const* obj_ptr_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

    NS(particle_num_elements_t) total_num_particles =
        ( NS(particle_num_elements_t) )0u;

    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( buffer ) );

    if( NS(Buffer_get_num_of_objects)( buffer ) > ( NS(buffer_size_t) )0u )
    {
        obj_ptr_t it  = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( buffer );

        obj_ptr_t end = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( buffer );

        SIXTRL_ASSERT( it  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( end != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ( end - it ) > ( ptrdiff_t )0 );

        for( ; it != end ; ++it )
        {
            if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
            {
                ptr_particles_t particles = ( ptr_particles_t )( uintptr_t
                    )NS(Object_get_begin_addr)( it );

                SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );

                total_num_particles +=
                    NS(Particles_get_num_of_particles)( particles );
            }
        }
    }

    return total_num_particles;
}

SIXTRL_INLINE NS(buffer_size_t)
NS(Particles_buffer_get_num_of_particle_blocks)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_size_t)                               buf_size_t;
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC  NS(Object) const* obj_ptr_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

    NS(buffer_size_t) num_particle_blocks = ZERO_SIZE;

    NS(buffer_size_t) const total_num_blocks =
        NS(Buffer_get_num_of_objects)( buffer );

    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( buffer ) );

    if( total_num_blocks > ZERO_SIZE )
    {
        obj_ptr_t it  = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( buffer );

        obj_ptr_t end = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( buffer );

        SIXTRL_ASSERT( it  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( end != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ( end - it ) > ( ptrdiff_t )0 );

        for( ; it != end ; ++it )
        {
            if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
            {
                ptr_particles_t particles = ( ptr_particles_t )( uintptr_t
                    )NS(Object_get_begin_addr)( it );

                SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );

                if( ( particles != SIXTRL_NULLPTR ) &&
                    ( ( NS(particle_num_elements_t) )0u <
                      NS(Particles_get_num_of_particles)( particles ) ) )
                {
                    ++num_particle_blocks;
                }
            }
        }
    }

    SIXTRL_ASSERT( num_particle_blocks <= total_num_blocks );

    return num_particle_blocks;
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
NS(Particles_buffer_get_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const particle_block_index )
{
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* ptr_particles_t;
    return ( ptr_particles_t )NS(Particles_buffer_get_const_particles)(
        buffer, particle_block_index );
}

SIXTRL_INLINE SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const*
NS(Particles_buffer_get_const_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const particle_block_index )
{
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* ptr_obj_t;

    ptr_obj_t ptr_particle_obj = ( ptr_obj_t )( uintptr_t
        )NS(Buffer_get_objects_begin_addr)( buffer );

    SIXTRL_ASSERT( ptr_particle_obj != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( particle_block_index <
        NS(Buffer_get_num_of_objects)( buffer ) );

    ptr_particle_obj = ptr_particle_obj + particle_block_index;

    return NS(BufferIndex_get_const_particles)( ptr_particle_obj );
}

SIXTRL_INLINE bool NS(Particles_buffers_have_same_structure)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT rhs )
{
    bool have_same_structure = false;

    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( lhs ) );
    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( rhs ) );

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) &&
        ( NS(Buffer_get_num_of_objects)( lhs ) ==
          NS(Buffer_get_num_of_objects)( rhs ) ) )
    {
        typedef NS(Object)                                      object_t;
        typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC object_t const*    ptr_object_t;
        typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const* ptr_particles_t;

        ptr_object_t lhs_it = ( ptr_object_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( lhs );

        ptr_object_t lhs_end = ( ptr_object_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( lhs );

        ptr_object_t rhs_it  = ( ptr_object_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( rhs );

        if( ( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
              ( rhs_it != SIXTRL_NULLPTR ) ) ||
            ( ( lhs_it == SIXTRL_NULLPTR ) && ( lhs_end == SIXTRL_NULLPTR ) &&
              ( rhs_it == SIXTRL_NULLPTR ) ) )
        {
            have_same_structure = true;

            for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
            {
                ptr_particles_t lhs_particles = SIXTRL_NULLPTR;
                ptr_particles_t rhs_particles = SIXTRL_NULLPTR;

                if( ( NS(Object_get_type_id)( lhs_it ) !=
                      NS(OBJECT_TYPE_PARTICLE) ) ||
                    ( NS(Object_get_type_id)( rhs_it ) !=
                      NS(OBJECT_TYPE_PARTICLE) ) )
                {
                    have_same_structure = false;
                    break;
                }

                lhs_particles = ( ptr_particles_t )( uintptr_t
                    )NS(BufferIndex_get_const_particles)( lhs_it );

                rhs_particles = ( ptr_particles_t )( uintptr_t
                    )NS(BufferIndex_get_const_particles)( rhs_it );

                if( NS(Particles_get_num_of_particles)( lhs_particles ) !=
                    NS(Particles_get_num_of_particles)( rhs_particles ) )
                {
                    have_same_structure = false;
                    break;
                }
            }
        }
    }

    return have_same_structure;
}

SIXTRL_INLINE void NS(Particles_buffers_calculate_difference)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT rhs,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT diff )
{
    if( ( NS(Particles_buffers_have_same_structure)( lhs, diff ) ) &&
        ( NS(Particles_buffers_have_same_structure)( rhs, diff ) ) )
    {
        typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* obj_const_ptr_t;
        typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)*       obj_ptr_t;

        typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles) const*
                ptr_const_particles_t;

        typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
                ptr_particles_t;

        obj_const_ptr_t lhs_it  = ( obj_const_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( lhs );

        obj_const_ptr_t lhs_end = ( obj_const_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( lhs );

        obj_const_ptr_t rhs_it  = ( obj_const_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( rhs );

        obj_ptr_t diff_it = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( diff );

        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it, ++diff_it )
        {
            ptr_const_particles_t lhs_particles =
                NS(BufferIndex_get_const_particles)( lhs_it );

            ptr_const_particles_t rhs_particles =
                NS(BufferIndex_get_const_particles)( rhs_it );

            ptr_particles_t diff_particles =
                NS(BufferIndex_get_particles)( diff_it );

            NS(Particles_calculate_difference)(
                lhs_particles, rhs_particles, diff_particles );
        }
    }

    return;
}

SIXTRL_INLINE void NS(Particles_buffer_get_max_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLE_ARGPTR_DEC
        NS(particle_num_elements_t)* SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT source )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_source_objects =
        NS(Buffer_get_num_of_objects)( source );

    num_elem_t const num_destination_objects =
        NS(Buffer_get_num_of_objects)( destination );

    if( (  num_source_objects == num_destination_objects ) &&
        (  num_source_objects >  ( num_elem_t )0 ) )
    {
        typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* obj_const_ptr_t;
        typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)*       obj_ptr_t;

        obj_const_ptr_t src_it  = ( obj_const_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( source );

        obj_const_ptr_t src_end = ( obj_const_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( source );

        obj_ptr_t dest_it = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( destination );

        for( ; src_it != src_end ; ++src_end, ++dest_it )
        {
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles) const* source_particles =
                NS(BufferIndex_get_const_particles)( src_it );

            SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles)* dest_particles =
                NS(BufferIndex_get_particles)( dest_it );

            NS(Particles_get_max_value)(
                dest_particles, max_value_index, source_particles );

            if( max_value_index != SIXTRL_NULLPTR )
            {
                max_value_index = max_value_index + NS(PARTICLES_NUM_DATAPTRS);
            }
        }
    }

    return;
}

SIXTRL_INLINE void NS(Particles_buffer_clear_particles)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC  NS(Object)* obj_ptr_t;
    typedef SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* ptr_particles_t;

    SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( buffer ) );

    if( NS(Buffer_get_num_of_objects)( buffer ) > ( NS(buffer_size_t) )0u )
    {
        obj_ptr_t it  = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_begin_addr)( buffer );

        obj_ptr_t end = ( obj_ptr_t )( uintptr_t
            )NS(Buffer_get_objects_end_addr)( buffer );

        SIXTRL_ASSERT( it  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( end != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ( end - it ) > ( ptrdiff_t )0 );

        for( ; it != end ; ++it )
        {
            if( NS(Object_get_type_id)( it ) == NS(OBJECT_TYPE_PARTICLE ) )
            {
                ptr_particles_t particles = ( ptr_particles_t )( uintptr_t
                    )NS(Object_get_begin_addr)( it );

                SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );

                NS(Particles_clear)( particles );
            }
        }
    }

    return;
}

#endif /* !defined( _GPUCODE ) || defined( __CUDACC__ ) */

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_q0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->q0[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->q0;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_q0)( particles );
}

SIXTRL_INLINE void NS(Particles_set_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_q0s )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_q0s != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->q0, ptr_to_q0s, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_q0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const q0_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->q0[ ii ] = q0_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_q0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_q0s )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->q0 = ptr_to_q0s;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_mass0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->mass0[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->mass0;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_mass0)( particles );
}

SIXTRL_INLINE void NS(Particles_set_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_mass0s )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_mass0s != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->mass0, ptr_to_mass0s, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_mass0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const mass0_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->mass0[ ii ] = mass0_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_mass0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_mass0s )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->mass0 = ptr_to_mass0s;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_beta0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->beta0[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->beta0;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_beta0)( particles );
}

SIXTRL_INLINE void NS(Particles_set_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_beta0s )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_beta0s != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->beta0, ptr_to_beta0s, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_beta0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const beta0_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->beta0[ ii ] = beta0_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_beta0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_beta0s )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->beta0 = ptr_to_beta0s;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_gamma0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->gamma0[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->gamma0;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_gamma0)( particles );
}

SIXTRL_INLINE void NS(Particles_set_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_gamma0s )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_gamma0s != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->gamma0, ptr_to_gamma0s, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_gamma0_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const gamma0_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->gamma0[ ii ] = gamma0_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_gamma0)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_gamma0s )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->gamma0 = ptr_to_gamma0s;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_p0c_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->p0c[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->p0c;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_p0c)( particles );
}

SIXTRL_INLINE void NS(Particles_set_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_p0cs )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_p0cs != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->p0c, ptr_to_p0cs, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_p0c_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const p0c_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->p0c[ ii ] = p0c_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_p0c)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_p0cs )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->p0c = ptr_to_p0cs;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->s[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->s;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_s)( particles );
}

SIXTRL_INLINE void NS(Particles_set_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_ss )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_ss != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->s, ptr_to_ss, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const s_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->s[ ii ] = s_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_ss )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->s = ptr_to_ss;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_s_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const s_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->s != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->s[ index ] += s_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_s_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT s_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( s_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_s_value)( particles, ii, s_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_s)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const s_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_s_value)( particles, ii, s_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->x[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->x;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_x)( particles );
}

SIXTRL_INLINE void NS(Particles_set_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_xs )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_xs != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->x, ptr_to_xs, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const x_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->x[ ii ] = x_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_xs )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->x = ptr_to_xs;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_x_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const x_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->x != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->x[ index ] += x_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_x_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT x_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( x_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_x_value)( particles, ii, x_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_x)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const x_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_x_value)( particles, ii, x_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->y[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->y;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_y)( particles );
}

SIXTRL_INLINE void NS(Particles_set_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_ys )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_ys != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->y, ptr_to_ys, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const y_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->y[ ii ] = y_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_ys )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->y = ptr_to_ys;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_y_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const y_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->y != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->y[ index ] += y_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_y_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT y_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( y_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_y_value)( particles, ii, y_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_y)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const y_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_y_value)( particles, ii, y_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->px[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->px;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_px)( particles );
}

SIXTRL_INLINE void NS(Particles_set_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_pxs )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_pxs != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->px, ptr_to_pxs, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const px_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->px[ ii ] = px_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_pxs )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->px = ptr_to_pxs;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_px_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const px_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->px != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->px[ index ] += px_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_px_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT px_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( px_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_px_value)( particles, ii, px_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_px)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const px_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_px_value)( particles, ii, px_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->py[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->py;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_py)( particles );
}

SIXTRL_INLINE void NS(Particles_set_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_pys )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_pys != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->py, ptr_to_pys, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const py_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->py[ ii ] = py_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_pys )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->py = ptr_to_pys;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_py_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const py_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->py != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->py[ index ] += py_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_py_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT py_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( py_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_py_value)( particles, ii, py_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_py)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const py_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_py_value)( particles, ii, py_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->zeta[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->zeta;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_zeta)( particles );
}

SIXTRL_INLINE void NS(Particles_set_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_zetas )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_zetas != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->zeta, ptr_to_zetas, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const zeta_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->zeta[ ii ] = zeta_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_zetas )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->zeta = ptr_to_zetas;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_zeta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const zeta_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->zeta != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->zeta[ index ] += zeta_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_zeta_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT zeta_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( zeta_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_zeta_value)( particles, ii,
                                         zeta_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_zeta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const zeta_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_zeta_value)( particles, ii, zeta_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->psigma[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->psigma;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_psigma)( particles );
}

SIXTRL_INLINE void NS(Particles_set_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_psigmas )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_psigmas != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->psigma, ptr_to_psigmas, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const psigma_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->psigma[ ii ] = psigma_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_psigmas )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->psigma = ptr_to_psigmas;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_psigma_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const psigma_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->psigma != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->psigma[ index ] += psigma_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_psigma_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT psigma_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( psigma_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_psigma_value)(
            particles, ii, psigma_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_psigma)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const psigma_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_psigma_value)( particles, ii, psigma_diff_value );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index )
{
    typedef NS(particle_real_t) real_t;

    real_t const p0c    = NS(Particles_get_p0c_value)( p, index );
    real_t const beta0  = NS(Particles_get_beta0_value)( p, index );
    real_t const psigma = NS(Particles_get_psigma_value)( p, index );
    real_t const ptau   = psigma * beta0;
    real_t const energy = ptau * p0c;

    return energy;

}

SIXTRL_INLINE void NS(Particles_set_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index, NS(particle_real_t) const energy )
{
    typedef NS(particle_real_t) real_t;

    real_t const beta0       = NS(Particles_get_beta0_value)( p, index );
    real_t const p0c         = NS(Particles_get_p0c_value)( p, index );

    real_t const ptau_beta0  = ( beta0 * energy ) / p0c;
    real_t const beta0_squ   = beta0 * beta0;
    real_t const beta0_plus_delta_beta0 = sqrt(
        ptau_beta0 * ptau_beta0 + ( real_t )2 * ptau_beta0 + beta0_squ );

    real_t const psigma = ptau_beta0 / beta0_squ;
    real_t const delta  = ( beta0_plus_delta_beta0 - beta0 ) / beta0;
    real_t const rpp    = beta0 / beta0_plus_delta_beta0;
    real_t const rvv    = ( beta0_plus_delta_beta0 ) /
                          ( beta0 + ptau_beta0 * beta0 );

    SIXTRL_ASSERT( beta0     > ( real_t )0 );
    SIXTRL_ASSERT( p0c       > ( real_t )0 );
    SIXTRL_ASSERT( beta0_squ > ( real_t )0 );
    SIXTRL_ASSERT( ( ptau_beta0 * ptau_beta0 +
        ( real_t )2 * ptau_beta0 + beta0_squ ) > ( real_t )0 );

    NS(Particles_set_delta_value)(  p, index, delta  );
    NS(Particles_set_rpp_value)(    p, index, rpp    );
    NS(Particles_set_rvv_value)(    p, index, rvv    );
    NS(Particles_set_psigma_value)( p, index, psigma );

    return;
}

SIXTRL_INLINE void NS(Particles_set_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_energies )
{
    NS(particle_num_elements_t) const num_particles =
        NS(Particles_get_num_of_particles)( p );

    NS(particle_num_elements_t) ii = ( NS(particle_num_elements_t) )0u;

    SIXTRL_ASSERT( ptr_to_energies != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_set_energy_value)( p, ii, ptr_to_energies[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_energy_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const delta_energy )
{
    typedef NS(particle_real_t) real_t;

    real_t const current_energy = NS(Particles_get_energy_value)( p, index );
    NS(Particles_set_energy_value)( p, index, current_energy + delta_energy );

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_energy_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_delta_energies )
{
    NS(particle_num_elements_t) const num_particles =
        NS(Particles_get_num_of_particles)( p );

    NS(particle_num_elements_t) ii = ( NS(particle_num_elements_t) )0u;

    SIXTRL_ASSERT( ptr_to_delta_energies != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_energy_value)( p, ii, ptr_to_delta_energies[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_energy)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_t) const delta_energy )
{
    NS(particle_num_elements_t) const num_particles =
        NS(Particles_get_num_of_particles)( p );

    NS(particle_num_elements_t) ii = ( NS(particle_num_elements_t) )0u;

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_energy_value)( p, ii, delta_energy );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->delta[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->delta;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_delta)( particles );
}

SIXTRL_INLINE void NS(Particles_set_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_deltas )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_deltas != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->delta, ptr_to_deltas, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const delta_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->delta[ ii ] = delta_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_deltas )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->delta = ptr_to_deltas;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_add_to_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const delta_diff_value )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particles->delta != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( index < NS(Particles_get_num_of_particles)( particles ) );

    particles->delta[ index ] += delta_diff_value;
    return;
}

SIXTRL_INLINE void NS(Particles_add_to_delta_detailed)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT delta_diff_values )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( delta_diff_values != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_delta_value)(
            particles, ii, delta_diff_values[ ii ] );
    }

    return;
}

SIXTRL_INLINE void NS(Particles_add_to_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_t) const delta_diff_value )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_add_to_delta_value)(
            particles, ii, delta_diff_value );
    }

    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Particles_update_delta_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const new_delta_value )
{
    typedef NS(particle_real_t) real_t;

    SIXTRL_STATIC_VAR real_t const ONE = ( real_t )1;

    real_t const beta0 = NS(Particles_get_beta0_value)( p, index );
    real_t const delta_beta0 = new_delta_value * beta0;
    real_t const ptau_beta0  = sqrt( delta_beta0 * delta_beta0 +
        ( real_t )2 * delta_beta0 * beta0 + ONE ) - ONE;

    real_t const one_plus_delta = ONE + new_delta_value;
    real_t const rvv    = ( one_plus_delta ) / ( ONE + ptau_beta0 );
    real_t const rpp    = ONE / one_plus_delta;
    real_t const psigma = ptau_beta0 / ( beta0 * beta0 );

    #if !defined( NDEBUG ) && !defined( _GPUCODE )
    SIXTRL_STATIC_VAR real_t const EPS  = ( real_t )1e-9;
    SIXTRL_STATIC_VAR real_t const ZERO = ( real_t )0;

    SIXTRL_ASSERT(   beta0              > ZERO );
    SIXTRL_ASSERT( ( beta0 * beta0    ) > EPS  );
    SIXTRL_ASSERT( ( one_plus_delta   ) > EPS  );
    SIXTRL_ASSERT( ( ONE + ptau_beta0 ) > EPS  );
    SIXTRL_ASSERT( ( delta_beta0 * delta_beta0 +
        ( real_t )2 * delta_beta0 * beta0 + ONE ) > ZERO );

    #endif /* !defined( NDEBUG ) && !defined( _GPUCODE ) */

    NS(Particles_set_delta_value)(  p, index, new_delta_value );
    NS(Particles_set_rvv_value)(    p, index, rvv );
    NS(Particles_set_rpp_value)(    p, index, rpp );
    NS(Particles_set_psigma_value)( p, index, psigma );

    return;
}

SIXTRL_INLINE void NS(Particles_update_delta_value_increment)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_num_elements_t) const index,
    NS(particle_real_t) const delta_value_diff )
{
    typedef NS(particle_real_t) real_t;

    real_t const current_delta = NS(Particles_get_delta_value)( p, index );
    real_t const new_delta     = current_delta + delta_value_diff;

    NS(Particles_update_delta_value)( p, index, new_delta );
    return;
}

SIXTRL_INLINE void NS(Particles_update_delta)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_deltas )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0;
    num_elem_t const num_particles = NS(Particles_get_num_of_particles)( p );

    SIXTRL_ASSERT( ptr_to_deltas != SIXTRL_NULLPTR );

    for( ; ii < num_particles ; ++ii )
    {
        NS(Particles_update_delta_value)( p, ii, ptr_to_deltas[ ii ] );
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_rpp_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->rpp[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->rpp;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_rpp)( particles );
}

SIXTRL_INLINE void NS(Particles_set_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_rpps )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_rpps != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->rpp, ptr_to_rpps, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_rpp_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const rpp_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->rpp[ ii ] = rpp_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_rpp)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_rpps )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->rpp = ptr_to_rpps;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_rvv_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->rvv[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->rvv;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_rvv)( particles );
}

SIXTRL_INLINE void NS(Particles_set_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_rvvs )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_rvvs != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->rvv, ptr_to_rvvs, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_rvv_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const rvv_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->rvv[ ii ] = rvv_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_rvv)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_rvvs )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->rvv = ptr_to_rvvs;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_real_t) NS(Particles_get_chi_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->chi[ ii ];
}

SIXTRL_INLINE NS(particle_real_const_ptr_t) NS(Particles_get_const_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->chi;
}

SIXTRL_INLINE NS(particle_real_ptr_t) NS(Particles_get_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_real_ptr_t) )NS(Particles_get_const_chi)( particles );
}

SIXTRL_INLINE void NS(Particles_set_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_const_ptr_t) SIXTRL_RESTRICT ptr_to_chis )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_chis != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES(
        NS(particle_real_t), particles->chi, ptr_to_chis, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_chi_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_real_t) const chi_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->chi[ ii ] = chi_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_chi)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_real_ptr_t) ptr_to_chis )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->chi = ptr_to_chis;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particles_get_particle_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->particle_id[ ii ];
}

SIXTRL_INLINE NS(particle_index_const_ptr_t)
NS(Particles_get_const_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->particle_id;
}

SIXTRL_INLINE NS(particle_index_ptr_t)
NS(Particles_get_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p )
{
    return ( NS(particle_index_ptr_t) )NS(Particles_get_const_particle_id)( p );
}

SIXTRL_INLINE void NS(Particles_set_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_particle_ids )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_particle_ids != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), particles->particle_id,
                             ptr_to_particle_ids, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_particle_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const particle_id_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->particle_id[ ii ] = particle_id_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_particle_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_particle_ids )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->particle_id = ptr_to_particle_ids;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particles_get_at_element_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->at_element_id[ ii ];
}

SIXTRL_INLINE NS(particle_index_const_ptr_t)
NS(Particles_get_const_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->at_element_id;
}

SIXTRL_INLINE NS(particle_index_ptr_t)
NS(Particles_get_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p )
{
    return ( NS(particle_index_ptr_t) )NS(Particles_get_const_at_element_id)( p );
}

SIXTRL_INLINE void NS(Particles_set_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_at_element_ids )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_at_element_ids != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), particles->at_element_id,
                             ptr_to_at_element_ids, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_at_element_id_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const at_element_id_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->at_element_id[ ii ] = at_element_id_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_at_element_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_at_element_ids )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->at_element_id = ptr_to_at_element_ids;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particles_get_at_turn_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->at_turn[ ii ];
}

SIXTRL_INLINE NS(particle_index_const_ptr_t)
NS(Particles_get_const_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->at_turn;
}

SIXTRL_INLINE NS(particle_index_ptr_t)
NS(Particles_get_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT p )
{
    return ( NS(particle_index_ptr_t) )NS(Particles_get_const_at_turn)( p );
}

SIXTRL_INLINE void NS(Particles_set_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_at_turns )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_at_turns != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), particles->at_turn,
                             ptr_to_at_turns, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_at_turn_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const at_turn_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->at_turn[ ii ] = at_turn_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_at_turns )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->at_turn = ptr_to_at_turns;
    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(particle_index_t) NS(Particles_get_state_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    return particles->state[ ii ];
}

SIXTRL_INLINE NS(particle_index_const_ptr_t)
NS(Particles_get_const_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles)
        *const SIXTRL_RESTRICT particles )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    return particles->state;
}

SIXTRL_INLINE NS(particle_index_ptr_t)
NS(Particles_get_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles )
{
    return ( NS(particle_index_ptr_t) )NS(Particles_get_const_state)( particles );
}

SIXTRL_INLINE void NS(Particles_set_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_const_ptr_t) SIXTRL_RESTRICT ptr_to_states )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    SIXTRL_ASSERT( ( particles  != SIXTRL_NULLPTR ) &&
                   ( ptr_to_states != SIXTRL_NULLPTR ) &&
                   ( num_particles > ( num_elem_t )0u ) );

    SIXTRACKLIB_COPY_VALUES( NS(particle_real_t), particles->state,
                             ptr_to_states, num_particles );

    return;
}

SIXTRL_INLINE void NS(Particles_set_state_value)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const ii,
    NS(particle_index_t) const state_value )
{
    SIXTRL_ASSERT( ( particles != SIXTRL_NULLPTR ) &&
                   ( ii < NS(Particles_get_num_of_particles)( particles ) ) );

    particles->state[ ii ] = state_value;
    return;
}

SIXTRL_INLINE void NS(Particles_assign_ptr_to_state)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_ptr_t) ptr_to_states )
{
    SIXTRL_ASSERT( particles != SIXTRL_NULLPTR );
    particles->state = ptr_to_states;
    return;
}

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_H__ */

/* end: sixtracklib/common/particles.h */
