#include "sixtracklib/common/be_beamfields/be_beamfields.h"

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/math_interpol.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #include "sixtracklib/common/be_beamfields/gauss_fields.h"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* ************************************************************************* */
/* BeamBeam4D: */

NS(object_type_id_t) NS(BeamBeam4D_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return NS(BeamBeam4D_type_id)();
}

NS(buffer_size_t) NS(BeamBeam4D_data_addr_offset_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(BeamBeam4D) *const SIXTRL_RESTRICT bb_elem ) SIXTRL_NOEXCEPT
{
    return NS(BeamBeam4D_data_addr_offset)( bb_elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(arch_status_t) NS(BeamBeam4D_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam4D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        offsets[ 0 ] = offsetof( NS(BeamBeam4D), data_addr );
        SIXTRL_ASSERT( offsets[ 0 ] % slot_size == ( NS(buffer_size_t) )0u );

        if( max_num_offsets > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_offsets ; ++ii )
                    offsets[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

NS(arch_status_t) NS(BeamBeam4D_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam4D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        sizes[ 0 ] = sizeof( SIXTRL_REAL_T );
        if( max_num_sizes > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_sizes ; ++ii )
                sizes[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(BeamBeam4D_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam4D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( max_num_counts >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        counts[ 0 ] = NS(BeamBeam4D_data_size)( elem );
        if( max_num_counts > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_counts ; ++ii )
                counts[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(BeamBeam4D_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const data_size,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    typedef NS(buffer_size_t)  buf_size_t;

    bool can_be_added = false;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    NS(BeamBeam4D) temp;
    NS(BeamBeam4D_preset)( &temp );
    status = NS(BeamBeam4D_set_data_size)( &temp, data_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ];
        SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ];

        status = NS(BeamBeam4D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            status = NS(BeamBeam4D_attributes_counts)(
                &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            buf_size_t const ndataptrs = NS(BeamBeam4D_num_dataptrs)( &temp );
            if( ndataptrs == ( buf_size_t )1 )
            {
                can_be_added = NS(Buffer_can_add_object)( buffer, sizeof(
                    NS(BeamBeam4D) ), ndataptrs, &sizes[ 0 ], &counts[ 0 ],
                        ptr_requ_objects, ptr_requ_slots, ptr_requ_dataptrs );
            }
        }
    }

    return can_be_added;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* NS(BeamBeam4D_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const data_size )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* added_elem = SIXTRL_NULLPTR;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );
    NS(BeamBeam4D) temp;
    NS(BeamBeam4D_preset)( &temp );
    status = NS(BeamBeam4D_set_data_size)( &temp, data_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam4D_num_dataptrs)( &temp );
        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                    &temp, sizeof( NS(BeamBeam4D) ), NS(BeamBeam4D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* NS(BeamBeam4D_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const  data_size,
    NS(buffer_addr_t) data_addr )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* added_elem = SIXTRL_NULLPTR;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    NS(BeamBeam4D) temp;
    NS(BeamBeam4D_preset)( &temp );
    status  = NS(BeamBeam4D_set_data_size)( &temp, data_size );
    status |= NS(BeamBeam4D_set_data_addr)( &temp, data_addr );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam4D_num_dataptrs)( &temp );
        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                    &temp, sizeof( NS(BeamBeam4D) ), NS(BeamBeam4D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* NS(BeamBeam4D_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(BeamBeam4D) *const SIXTRL_RESTRICT orig )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* added_elem = SIXTRL_NULLPTR;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    NS(arch_status_t) status = NS(BeamBeam4D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, orig, slot_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, orig, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam4D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, orig, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam4D_num_dataptrs)( orig );

        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam4D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer, orig,
                    sizeof( NS(BeamBeam4D) ), NS(BeamBeam4D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

/* ************************************************************************* */
/* NS(BeamBeam6D) */

NS(object_type_id_t) NS(BeamBeam6D_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return NS(BeamBeam6D_type_id)();
}

NS(buffer_size_t) NS(BeamBeam6D_data_addr_offset_ext)( SIXTRL_BE_ARGPTR_DEC
    const NS(BeamBeam6D) *const SIXTRL_RESTRICT bb_elem ) SIXTRL_NOEXCEPT
{
    return NS(BeamBeam6D_data_addr_offset)( bb_elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(arch_status_t) NS(BeamBeam6D_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam6D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( offsets != SIXTRL_NULLPTR ) &&
        ( max_num_offsets >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        offsets[ 0 ] = offsetof( NS(BeamBeam6D), data_addr );
        SIXTRL_ASSERT( offsets[ 0 ] % slot_size == ( NS(buffer_size_t) )0u );

        if( max_num_offsets > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_offsets ; ++ii )
                    offsets[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

NS(arch_status_t) NS(BeamBeam6D_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam6D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( sizes != SIXTRL_NULLPTR ) &&
        ( max_num_sizes >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        sizes[ 0 ] = sizeof( SIXTRL_REAL_T );

        if( max_num_sizes > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_sizes ; ++ii )
                sizes[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_EXTERN SIXTRL_HOST_FN NS(arch_status_t) NS(BeamBeam6D_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(BeamBeam6D) *const SIXTRL_RESTRICT elem,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( counts != SIXTRL_NULLPTR ) &&
        ( max_num_counts >= ( NS(buffer_size_t) )1 ) &&
        ( slot_size > ( NS(buffer_size_t) )0 ) )
    {
        counts[ 0 ] = NS(BeamBeam6D_data_size)( elem );
        if( max_num_counts > ( NS(buffer_size_t) )1 )
        {
            NS(buffer_size_t) ii = ( NS(buffer_size_t) )1u;
            for( ; ii < max_num_counts ; ++ii )
                counts[ ii ] = ( NS(buffer_size_t) )0u;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool NS(BeamBeam6D_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const data_size,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    typedef NS(buffer_size_t)  buf_size_t;

    bool can_be_added = false;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    NS(BeamBeam6D) temp;
    NS(BeamBeam6D_preset)( &temp );
    status = NS(BeamBeam6D_set_data_size)( &temp, data_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ];
        SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ];

        status = NS(BeamBeam6D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            status = NS(BeamBeam6D_attributes_counts)(
                &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            buf_size_t const ndataptrs = NS(BeamBeam6D_num_dataptrs)( &temp );

            if( ndataptrs == ( buf_size_t )1 )
            {
                can_be_added = NS(Buffer_can_add_object)( buffer, sizeof(
                    NS(BeamBeam6D) ), ndataptrs, &sizes[ 0 ], &counts[ 0 ],
                        ptr_requ_objects, ptr_requ_slots, ptr_requ_dataptrs );
            }
        }
    }

    return can_be_added;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* NS(BeamBeam6D_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const data_size )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* added_elem = SIXTRL_NULLPTR;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    NS(BeamBeam6D) temp;
    NS(BeamBeam6D_preset)( &temp );
    status = NS(BeamBeam6D_set_data_size)( &temp, data_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam6D_num_dataptrs)( &temp );
        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                    &temp, sizeof( NS(BeamBeam6D) ), NS(BeamBeam6D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* NS(BeamBeam6D_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const data_size,
    NS(buffer_addr_t) const data_addr )
{
    typedef NS(buffer_size_t) buf_size_t;

    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* added_elem = SIXTRL_NULLPTR;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    NS(BeamBeam6D) temp;
    NS(BeamBeam6D_preset)( &temp );
    status  = NS(BeamBeam6D_set_data_size)( &temp, data_size );
    status |= NS(BeamBeam6D_set_data_addr)( &temp, data_addr );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, &temp, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam6D_num_dataptrs)( &temp );
        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                    &temp, sizeof( NS(BeamBeam6D) ), NS(BeamBeam6D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* NS(BeamBeam6D_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(BeamBeam6D) *const SIXTRL_RESTRICT orig )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* added_elem = SIXTRL_NULLPTR;

    SIXTRL_ARGPTR_DEC buf_size_t offsets[ 1 ] = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t sizes[ 1 ]   = { ( buf_size_t )0 };
    SIXTRL_ARGPTR_DEC buf_size_t counts[ 1 ]  = { ( buf_size_t )0 };

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    NS(arch_status_t) status = NS(BeamBeam6D_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )1u, orig, slot_size );

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_offsets)(
            &offsets[ 0 ], ( buf_size_t )1u, orig, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        status = NS(BeamBeam6D_attributes_counts)(
            &counts[ 0 ], ( buf_size_t )1u, orig, slot_size );
    }

    if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
    {
        buf_size_t const ndataptrs = NS(BeamBeam6D_num_dataptrs)( orig );
        if( ndataptrs == ( buf_size_t )1 )
        {
            added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(BeamBeam6D)* )( uintptr_t
                )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer, orig,
                    sizeof( NS(BeamBeam6D) ), NS(BeamBeam6D_type_id)(),
                        ndataptrs, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

/* ************************************************************************* */
/* SCCoasting: */

NS(object_type_id_t) NS(SCCoasting_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(object_type_id_t) )NS(OBJECT_TYPE_SC_COASTING);
}

/* ------------------------------------------------------------------------- */

SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) const*
NS(SCCoasting_const_from_buffer)( SIXTRL_BUFFER_ARGPTR_DEC
        const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCCoasting_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)*
NS(SCCoasting_from_buffer)( SIXTRL_BUFFER_ARGPTR_DEC
        NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCCoasting_from_obj_index)(
        NS(Buffer_get_object)( buffer, index ) );
}

NS(arch_status_t) NS(SCCoasting_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCCoasting) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( offsets != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_offsets > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, offsets, max_num_offsets, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

NS(arch_status_t) NS(SCCoasting_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCCoasting)
        *const SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( sizes != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_sizes > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, sizes, max_num_sizes, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

NS(arch_status_t) NS(SCCoasting_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCCoasting)
        *const SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( counts != SIXTRL_NULLPTR ) && ( slot_size > ( buf_size_t )0 ) &&
        ( max_num_counts > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, counts, max_num_counts, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */

bool NS(SCCoasting_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT
        ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    bool can_be_added = false;

    buf_size_t num_dataptrs = ( buf_size_t )0u;
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) sc_elem;
    NS(arch_status_t) status = NS(SCCoasting_clear)( &sc_elem );
    num_dataptrs = NS(SCCoasting_num_dataptrs)( &sc_elem );

    can_be_added = (
        ( num_dataptrs == ( buf_size_t )0u ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
        ( NS(Buffer_can_add_object)( buffer, sizeof( NS(SCCoasting) ),
            num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR, ptr_requ_objects,
                ptr_requ_slots, ptr_requ_dataptrs ) ) );

    return can_be_added;
}

SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* added_elem = SIXTRL_NULLPTR;
    NS(buffer_size_t) num_dataptrs = ( NS(buffer_size_t) )0u;

    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting) sc_elem;
    NS(arch_status_t) status = NS(SCCoasting_clear)( &sc_elem );
    num_dataptrs = NS(SCCoasting_num_dataptrs)( &sc_elem );

    if( ( num_dataptrs == ( NS(buffer_size_t) )0u ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
        ( buffer != SIXTRL_NULLPTR ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* )(
            uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                &sc_elem, sizeof( sc_elem ), NS(SCCoasting_type_id)(),
                    num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                        SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const number_of_particles, SIXTRL_REAL_T const circumference,
    SIXTRL_REAL_T const sigma_x, SIXTRL_REAL_T const sigma_y,
    SIXTRL_REAL_T const length, SIXTRL_REAL_T const x_co,
    SIXTRL_REAL_T const y_co, SIXTRL_REAL_T const min_sigma_diff,
    bool const enabled )
{
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* added_elem = SIXTRL_NULLPTR;
    NS(buffer_size_t) num_dataptrs = ( NS(buffer_size_t) )0u;

    NS(SCCoasting) sc_elem;
    NS(arch_status_t) status = NS(SCCoasting_clear)( &sc_elem );
    status |= NS(SCCoasting_set_number_of_particles)(
        &sc_elem, number_of_particles );

    status |= NS(SCCoasting_set_circumference)(
        &sc_elem, circumference );

    status |= NS(SCCoasting_set_sigma_x)( &sc_elem, sigma_x );
    status |= NS(SCCoasting_set_sigma_y)( &sc_elem, sigma_y );
    status |= NS(SCCoasting_set_length)( &sc_elem, length );
    status |= NS(SCCoasting_set_x_co)( &sc_elem, x_co );
    status |= NS(SCCoasting_set_y_co)( &sc_elem, y_co );
    status |= NS(SCCoasting_set_min_sigma_diff)(
        &sc_elem, min_sigma_diff );

    status |= NS(SCCoasting_set_enabled)( &sc_elem, enabled );

    num_dataptrs = NS(SCCoasting_num_dataptrs)( &sc_elem );

    if( ( buffer != SIXTRL_NULLPTR ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
        ( num_dataptrs == ( NS(buffer_size_t) )0u ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* )(
            uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                &sc_elem, sizeof( sc_elem ), NS(SCCoasting_type_id)(),
                    num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR,
                        SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* NS(SCCoasting_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(SCCoasting) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT
{
    SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* added_elem = SIXTRL_NULLPTR;

    NS(buffer_size_t) const num_dataptrs =
        NS(SCCoasting_num_dataptrs)( orig );

    if( ( orig != SIXTRL_NULLPTR ) && ( buffer != SIXTRL_NULLPTR ) &&
        ( num_dataptrs == ( NS(buffer_size_t) )0u ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCCoasting)* )(
            uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                orig, sizeof( NS(SCCoasting) ),
                    NS(SCCoasting_type_id)(), num_dataptrs,
                        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

/* *************************************************************************  */
/* NS(SCQGaussProfile): */

NS(object_type_id_t)
NS(SCQGaussProfile_type_id_ext)( void ) SIXTRL_NOEXCEPT
{
    return ( NS(object_type_id_t) )NS(OBJECT_TYPE_SC_QGAUSSIAN_PROF);
}

/* ------------------------------------------------------------------------- */

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) const*
NS(SCQGaussProfile_const_from_buffer)( SIXTRL_BUFFER_ARGPTR_DEC
        const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCQGaussProfile_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_from_buffer)( SIXTRL_BUFFER_ARGPTR_DEC
        NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCQGaussProfile_from_obj_index)(
        NS(Buffer_get_object)( buffer, index ) );
}

NS(arch_status_t) NS(SCQGaussProfile_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCQGaussProfile) *const
        SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( offsets != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_offsets > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, offsets, max_num_offsets, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

NS(arch_status_t) NS(SCQGaussProfile_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCQGaussProfile)
        *const SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( sizes != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_sizes > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, sizes, max_num_sizes, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

NS(arch_status_t) NS(SCQGaussProfile_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCQGaussProfile)
        *const SIXTRL_RESTRICT SIXTRL_UNUSED( sc_elem ),
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;

    if( ( counts != SIXTRL_NULLPTR ) && ( slot_size > ZERO ) &&
        ( max_num_counts > ZERO ) )
    {
        SIXTRACKLIB_SET_VALUES( buf_size_t, counts, max_num_counts, ZERO );
    }

    return ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
}

/* ------------------------------------------------------------------------- */

bool NS(SCQGaussProfile_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT
        ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    bool can_be_added = false;

    buf_size_t ndataptrs = ( buf_size_t )0u;
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) sc_elem;
    NS(arch_status_t) const status =
        NS(SCQGaussProfile_clear)( &sc_elem );
    ndataptrs = NS(SCQGaussProfile_num_dataptrs)( &sc_elem );

    can_be_added = ( ( ndataptrs == ( buf_size_t )0 ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
        ( NS(Buffer_can_add_object)( buffer,
            sizeof( NS(SCQGaussProfile) ), ndataptrs,
                SIXTRL_NULLPTR, SIXTRL_NULLPTR, ptr_requ_objects,
                    ptr_requ_slots, ptr_requ_dataptrs ) ) );

    return can_be_added;
}

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
        added_elem = SIXTRL_NULLPTR;

    NS(buffer_size_t) ndataptrs = ( NS(buffer_size_t) )0u;

    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile) sc_elem;
    NS(arch_status_t) const status =
        NS(SCQGaussProfile_clear)( &sc_elem );

    ndataptrs = NS(SCQGaussProfile_num_dataptrs)( &sc_elem );

    if( ( ndataptrs == ( NS(buffer_size_t) )0u ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* )(
        uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
            &sc_elem, sizeof( NS(SCQGaussProfile) ),
                NS(SCQGaussProfile_type_id)(), ndataptrs,
                    SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const number_of_particles, SIXTRL_REAL_T const bunchlength_rms,
    SIXTRL_REAL_T const sigma_x, SIXTRL_REAL_T const sigma_y,
    SIXTRL_REAL_T const length,
    SIXTRL_REAL_T const x_co, SIXTRL_REAL_T const y_co,
    SIXTRL_REAL_T const min_sigma_diff,
    SIXTRL_REAL_T const q_param, bool const enabled )
{
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
        added_elem = SIXTRL_NULLPTR;

    NS(buffer_size_t) num_dataptrs = ( NS(buffer_size_t) )0u;

    NS(SCQGaussProfile) sc_elem;
    NS(arch_status_t) status =
        NS(SCQGaussProfile_clear)( &sc_elem );

    status |= NS(SCQGaussProfile_set_number_of_particles)(
        &sc_elem, number_of_particles );

    status |= NS(SCQGaussProfile_set_bunchlength_rms)(
        &sc_elem, bunchlength_rms );

    status |= NS(SCQGaussProfile_set_sigma_x)( &sc_elem, sigma_x );
    status |= NS(SCQGaussProfile_set_sigma_y)( &sc_elem, sigma_y );
    status |= NS(SCQGaussProfile_set_length)( &sc_elem, length );
    status |= NS(SCQGaussProfile_set_x_co)( &sc_elem, x_co );
    status |= NS(SCQGaussProfile_set_y_co)( &sc_elem, y_co );

    status |= NS(SCQGaussProfile_set_min_sigma_diff)(
        &sc_elem, min_sigma_diff );

    status |= NS(SCQGaussProfile_set_q_param)( &sc_elem, q_param );
    status |= NS(SCQGaussProfile_set_enabled)( &sc_elem, enabled );

    num_dataptrs = NS(SCQGaussProfile_num_dataptrs)( &sc_elem );
    SIXTRL_ASSERT( num_dataptrs == ( NS(buffer_size_t) )0u );

    if( ( buffer != SIXTRL_NULLPTR ) &&
        ( num_dataptrs == ( NS(buffer_size_t) )0 ) &&
        ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* )(
            uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                &sc_elem, sizeof( sc_elem ),
                    NS(SCQGaussProfile_type_id)(), num_dataptrs,
                        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
NS(SCQGaussProfile_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(SCQGaussProfile) *const
        SIXTRL_RESTRICT orig ) SIXTRL_NOEXCEPT
{
    SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)*
        added_elem = SIXTRL_NULLPTR;

    NS(buffer_size_t) const num_dataptrs =
        NS(SCQGaussProfile_num_dataptrs)( orig );

    if( ( orig != SIXTRL_NULLPTR ) && ( buffer != SIXTRL_NULLPTR ) &&
        ( num_dataptrs == ( NS(buffer_size_t) )0 ) )
    {
        added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCQGaussProfile)* )(
            uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
                orig, sizeof( NS(SCQGaussProfile) ),
                    NS(SCQGaussProfile_type_id)(), num_dataptrs,
                        SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );
    }

    return added_elem;
}

/* ************************************************************************* */
/* NS(LineDensityProfileData) */

NS(object_type_id_t) NS(LineDensityProfileData_type_id_ext)(
    void ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_type_id)();
}

NS(buffer_size_t) NS(LineDensityProfileData_values_offset_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_values_offset)( data );
}

NS(buffer_size_t) NS(LineDensityProfileData_derivatives_offset_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_derivatives_offset)( data );
}

NS(arch_status_t) NS(LineDensityProfileData_prepare_interpolation_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    NS(math_abscissa_idx_t) const num_values =
        NS(LineDensityProfileData_num_values)( data );

    if( ( data != SIXTRL_NULLPTR ) &&
        ( num_values > ( NS(math_abscissa_idx_t) )1 ) )
    {
        NS(math_interpol_t) const interpol_method =
            NS(LineDensityProfileData_method)( data );

        if( interpol_method == NS(MATH_INTERPOL_LINEAR) )
        {
            status = NS(LineDensityProfileData_prepare_interpolation)(
                data, SIXTRL_NULLPTR );
        }
        else if( interpol_method == NS(MATH_INTERPOL_CUBIC) )
        {
            SIXTRL_REAL_T* temp_data = ( SIXTRL_REAL_T* )malloc(
                sizeof( SIXTRL_REAL_T ) * num_values * 6u );

            status = NS(LineDensityProfileData_prepare_interpolation)(
                data, temp_data );

            free( temp_data );
        }
    }

    return status;
}

SIXTRL_REAL_T NS(LineDensityProfileData_z0_ext)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_z0)( data );
}

SIXTRL_REAL_T NS(LineDensityProfileData_dz_ext)( SIXTRL_BUFFER_DATAPTR_DEC const
    NS(LineDensityProfileData) *const SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_dz)( data );
}

SIXTRL_REAL_T NS(LineDensityProfileData_z_min_ext)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_z_min)( data );
}

SIXTRL_REAL_T NS(LineDensityProfileData_z_max_ext)( SIXTRL_BUFFER_DATAPTR_DEC
    const NS(LineDensityProfileData) *const SIXTRL_RESTRICT
        data ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_z_max)( data );
}

NS(math_abscissa_idx_t) NS(LineDensityProfileData_find_idx_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data,
    SIXTRL_REAL_T const z ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_find_idx)( data, z );
}


SIXTRL_REAL_T NS(LineDensityProfileData_interpolate_value_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data, SIXTRL_REAL_T const z ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_interpolate_value)( data, z );
}

SIXTRL_REAL_T NS(LineDensityProfileData_interpolate_1st_derivative_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data, SIXTRL_REAL_T const z ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_interpolate_1st_derivative)( data, z );
}

SIXTRL_REAL_T NS(LineDensityProfileData_interpolate_2nd_derivative_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data, SIXTRL_REAL_T const z ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_interpolate_2nd_derivative)( data, z );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(arch_status_t) NS(LineDensityProfileData_set_z0_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)* SIXTRL_RESTRICT data,
    SIXTRL_REAL_T const z0 ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_set_z0)( data, z0 );
}

NS(arch_status_t) NS(LineDensityProfileData_set_dz_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)* SIXTRL_RESTRICT data,
    SIXTRL_REAL_T const dz ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_set_dz)( data, dz );
}

NS(arch_status_t) NS(LineDensityProfileData_set_values_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)* SIXTRL_RESTRICT data,
    NS(buffer_addr_t) const values_addr ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_set_values_addr)( data, values_addr );
}

NS(arch_status_t) NS(LineDensityProfileData_set_derivatives_addr_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)* SIXTRL_RESTRICT data,
    NS(buffer_addr_t) const derivatives_addr ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_set_derivatives_addr)( data, derivatives_addr );
}

NS(arch_status_t) NS(LineDensityProfileData_set_method_ext)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)* SIXTRL_RESTRICT data,
    NS(math_interpol_t) const method ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_set_method)( data, method );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData) const*
NS(LineDensityProfileData_const_from_buffer_ext)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
NS(LineDensityProfileData_from_buffer_ext)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(LineDensityProfileData_from_obj_index)(
        NS(Buffer_get_object)( buffer, index ) );
}

/* ------------------------------------------------------------------------- */

NS(arch_status_t) NS(LineDensityProfileData_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( offsets != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( slot_size > ZERO ) && ( max_num_offsets >= ( buf_size_t )2u ) )
    {
        offsets[ 0 ] = ( buf_size_t )offsetof(
            NS(LineDensityProfileData), values_addr );

        offsets[ 1 ] = ( buf_size_t )offsetof(
            NS(LineDensityProfileData), derivatives_addr );

        SIXTRL_ASSERT( offsets[ 0 ] % slot_size == ( buf_size_t )0 );
        SIXTRL_ASSERT( offsets[ 0 ] % slot_size == ( buf_size_t )0 );

        if( max_num_offsets > ( buf_size_t )2u )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, &offsets[ 2 ], max_num_offsets - 2u, ZERO );
        }

        status = NS(ARCH_STATUS_SUCCESS);
    }

    return status;
}

NS(arch_status_t) NS(LineDensityProfileData_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData)
        *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( sizes != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( slot_size > ZERO ) && ( max_num_sizes >= ( buf_size_t )2u ) )
    {
        sizes[ 0 ] = sizeof( SIXTRL_REAL_T );
        sizes[ 1 ] = sizeof( SIXTRL_REAL_T );

        if( max_num_sizes > ( buf_size_t )2u )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, &sizes[ 2 ], max_num_sizes - 2u, ZERO );
        }

        status = NS(ARCH_STATUS_SUCCESS);
    }

    return status;
}

NS(arch_status_t) NS(LineDensityProfileData_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(LineDensityProfileData)
        *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( counts != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( max_num_counts >= ( buf_size_t )2u ) &&
        ( slot_size > ( NS(buffer_size_t) )0u ) &&
        ( NS(LineDensityProfileData_capacity)( data ) >=
          ( NS(math_abscissa_idx_t) )0u ) )
    {
        counts[ 0 ] = ( buf_size_t )NS(LineDensityProfileData_capacity)( data );
        counts[ 1 ] = ( buf_size_t )NS(LineDensityProfileData_capacity)( data );
        status = NS(ARCH_STATUS_SUCCESS);

        if( max_num_counts > ( buf_size_t )2u )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, &counts[ 2 ], max_num_counts - 2u, ZERO );
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

bool NS(LineDensityProfileData_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(math_abscissa_idx_t) const capacity,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)*
        SIXTRL_RESTRICT ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    bool can_be_added = false;

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );
    buf_size_t ndataptrs = ( buf_size_t )0u;

    NS(LineDensityProfileData) data;
    NS(arch_status_t) status = NS(LineDensityProfileData_clear)( &data );
    status |= NS(LineDensityProfileData_set_capacity)( &data, capacity );
    status |= NS(LineDensityProfileData_set_num_values)( &data, capacity );
    ndataptrs = NS(LineDensityProfileData_num_dataptrs)( &data );

    if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
        ( ndataptrs == ( buf_size_t )2u ) && ( slot_size > ( buf_size_t )0 ) &&
        ( buffer != SIXTRL_NULLPTR ) &&
        ( capacity > ( NS(math_abscissa_idx_t) )0 ) )
    {
        NS(buffer_size_t) sizes[ 2 ];
        NS(buffer_size_t) counts[ 2 ];

        status = NS(LineDensityProfileData_attributes_sizes)(
            &sizes[ 0 ], ( buf_size_t )2u, &data, slot_size );

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            status = NS(LineDensityProfileData_attributes_counts)(
                &counts[ 0 ], ( buf_size_t )2u, &data, slot_size );
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            can_be_added = NS(Buffer_can_add_object)( buffer, sizeof(
                NS(LineDensityProfileData) ), ndataptrs, SIXTRL_NULLPTR,
                    SIXTRL_NULLPTR, ptr_requ_objects, ptr_requ_slots,
                        ptr_requ_dataptrs );
        }
    }

    return can_be_added;
}

SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
NS(LineDensityProfileData_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(math_abscissa_idx_t) const capacity )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        added_elem = SIXTRL_NULLPTR;

    if( ( buffer != SIXTRL_NULLPTR ) &&
        ( capacity > ( NS(math_abscissa_idx_t) )0 ) )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        SIXTRL_ARGPTR_DEC buf_size_t sizes[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t counts[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t offsets[ 2u ];

        buf_size_t num_dataptrs = ( buf_size_t )0u;

        NS(LineDensityProfileData) data;
        NS(arch_status_t) status = NS(LineDensityProfileData_clear)( &data );
        status |= NS(LineDensityProfileData_set_capacity)( &data, capacity );
        status |= NS(LineDensityProfileData_set_num_values)( &data, capacity );
        num_dataptrs = NS(LineDensityProfileData_num_dataptrs)( &data );

        if( ( num_dataptrs == ( buf_size_t )2u ) &&
            ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
            ( slot_size > ( buf_size_t )0 ) && ( buffer != SIXTRL_NULLPTR ) )
        {
            status = NS(LineDensityProfileData_attributes_offsets)(
                &offsets[ 0 ], ( buf_size_t )2u, &data, slot_size );

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_sizes)(
                    &sizes[ 0 ], ( buf_size_t )2u, &data, slot_size );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_counts)(
                    &counts[ 0 ], ( buf_size_t )2u, &data, slot_size );
            }
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            added_elem = ( SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
                )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)(
                    buffer, &data, sizeof( data ),
                        NS(LineDensityProfileData_type_id)(), num_dataptrs,
                            &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC NS(LineDensityProfileData)* NS(LineDensityProfileData_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(math_interpol_t) const method, NS(math_abscissa_idx_t) num_values,
    NS(buffer_addr_t) const values_addr,
    NS(buffer_addr_t) const derivatives_addr,
    SIXTRL_REAL_T const z0, SIXTRL_REAL_T const dz,
    NS(math_abscissa_idx_t) capacity )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        added_elem = SIXTRL_NULLPTR;

    if( num_values < ( NS(math_abscissa_idx_t) )0 )
    {
        num_values = ( NS(math_abscissa_idx_t) )0;
    }

    if( ( capacity < num_values ) &&
        ( num_values > ( NS(math_abscissa_idx_t) )0 ) )
    {
        capacity = num_values;
    }

    if( ( buffer != SIXTRL_NULLPTR ) &&
        ( capacity > ( NS(math_abscissa_idx_t) )0 ) )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        SIXTRL_ARGPTR_DEC buf_size_t sizes[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t counts[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t offsets[ 2u ];

        buf_size_t num_dataptrs = ( buf_size_t )0u;

        NS(LineDensityProfileData) data;
        NS(arch_status_t) status = NS(LineDensityProfileData_clear)( &data );
        status |= NS(LineDensityProfileData_set_capacity)( &data, capacity );
        status |= NS(LineDensityProfileData_set_num_values)( &data, num_values );
        status |= NS(LineDensityProfileData_set_method)( &data, method );
        status |= NS(LineDensityProfileData_set_values_addr)( &data, values_addr );
        status |= NS(LineDensityProfileData_set_z0)( &data, z0 );
        status |= NS(LineDensityProfileData_set_z0)( &data, dz );
        status |= NS(LineDensityProfileData_set_derivatives_addr)(
                        &data, derivatives_addr );
        num_dataptrs = NS(LineDensityProfileData_num_dataptrs)( &data );

        if( ( num_dataptrs == ( buf_size_t )2u ) &&
            ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) )
        {
            status = NS(LineDensityProfileData_attributes_offsets)(
                &offsets[ 0 ], ( buf_size_t )2u, &data, slot_size );

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_sizes)(
                    &sizes[ 0 ], ( buf_size_t )2u, &data, slot_size );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_counts)(
                    &counts[ 0 ], ( buf_size_t )2u, &data, slot_size );
            }
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            added_elem = ( SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
                )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)(
                    buffer, &data, sizeof( data ),
                        NS(LineDensityProfileData_type_id)(), num_dataptrs,
                            &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;

}

SIXTRL_BE_ARGPTR_DEC NS(LineDensityProfileData)*
NS(LineDensityProfileData_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(LineDensityProfileData) *const
        SIXTRL_RESTRICT data ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
        added_elem = SIXTRL_NULLPTR;

    if( ( buffer != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

        SIXTRL_ARGPTR_DEC buf_size_t sizes[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t counts[ 2u ];
        SIXTRL_ARGPTR_DEC buf_size_t offsets[ 2u ];

        buf_size_t num_dataptrs = ( buf_size_t )0u;
        num_dataptrs = NS(LineDensityProfileData_num_dataptrs)( data );

        if( num_dataptrs == ( buf_size_t )2u )
        {
            status = NS(LineDensityProfileData_attributes_offsets)(
                &offsets[ 0 ], ( buf_size_t )2u, data, slot_size );

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_sizes)(
                    &sizes[ 0 ], ( buf_size_t )2u, data, slot_size );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status = NS(LineDensityProfileData_attributes_counts)(
                    &counts[ 0 ], ( buf_size_t )2u, data, slot_size );
            }
        }

        if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
        {
            added_elem = ( SIXTRL_BUFFER_DATAPTR_DEC NS(LineDensityProfileData)*
                )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)(
                    buffer, data, sizeof( NS(LineDensityProfileData) ),
                        NS(LineDensityProfileData_type_id)(), num_dataptrs,
                            &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
        }
    }

    return added_elem;
}

/* ************************************************************************* */
/* NS(SCInterpolatedProfile): */

NS(object_type_id_t) NS(SCInterpolatedProfile_type_id_ext)(
    void ) SIXTRL_NOEXCEPT
{
    return NS(SCInterpolatedProfile_type_id)();
}

NS(buffer_size_t)
NS(SCInterpolatedProfile_interpol_data_addr_offset_ext)(
    SIXTRL_BE_ARGPTR_DEC const NS(SCInterpolatedProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT
{
    return NS(SCInterpolatedProfile_interpol_data_addr_offset)(
        sc_elem );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile) const*
NS(SCInterpolatedProfile_const_from_buffer)( SIXTRL_BUFFER_ARGPTR_DEC
        const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCInterpolatedProfile_const_from_obj_index)(
        NS(Buffer_get_const_object)( buffer, index ) );
}

SIXTRL_BE_ARGPTR_DEC
NS(SCInterpolatedProfile)* NS(SCInterpolatedProfile_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index ) SIXTRL_NOEXCEPT
{
    return NS(SCInterpolatedProfile_from_obj_index)(
        NS(Buffer_get_object)( buffer, index ) );
}

NS(arch_status_t) NS(SCInterpolatedProfile_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets, SIXTRL_BUFFER_DATAPTR_DEC const
        NS(SCInterpolatedProfile) *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( offsets_begin != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( slot_size > ZERO ) )
    {
        status = NS(ARCH_STATUS_SUCCESS);

        if( max_num_offsets > ZERO )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, offsets_begin, max_num_offsets, ZERO );
        }
    }

    return status;
}

NS(arch_status_t) NS(SCInterpolatedProfile_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCInterpolatedProfile) *const
        SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( sizes_begin != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( slot_size > ZERO ) )
    {
        status = NS(ARCH_STATUS_SUCCESS);

        if( max_num_sizes > ZERO )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, sizes_begin, max_num_sizes, ZERO );
        }
    }

    return status;
}

NS(arch_status_t) NS(SCInterpolatedProfile_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(SCInterpolatedProfile)
        *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_STATIC_VAR buf_size_t const ZERO = ( buf_size_t )0u;
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    if( ( counts_begin != SIXTRL_NULLPTR ) && ( data != SIXTRL_NULLPTR ) &&
        ( slot_size > ( NS(buffer_size_t) )0u ) )
    {
        status = NS(ARCH_STATUS_SUCCESS);

        if( max_num_counts > ZERO )
        {
            SIXTRACKLIB_SET_VALUES(
                buf_size_t, counts_begin, max_num_counts, ZERO );
        }
    }

    return status;
}

/* ------------------------------------------------------------------------- */

bool NS(SCInterpolatedProfile_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)*
        SIXTRL_RESTRICT ptr_requ_dataptrs ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    bool can_be_added = false;

    buf_size_t num_dataptrs = ( buf_size_t )0u;
    NS(SCInterpolatedProfile) sc_elem;
    NS(SCInterpolatedProfile_preset)( &sc_elem );

    num_dataptrs = NS(SCInterpolatedProfile_num_dataptrs)( &sc_elem );
    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )0u );

    can_be_added = NS(Buffer_can_add_object)( buffer, sizeof(
        NS(SCInterpolatedProfile) ), num_dataptrs, SIXTRL_NULLPTR,
            SIXTRL_NULLPTR, ptr_requ_objects, ptr_requ_slots, ptr_requ_dataptrs );

    return can_be_added;
}

SIXTRL_BE_ARGPTR_DEC
NS(SCInterpolatedProfile)* NS(SCInterpolatedProfile_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        added_elem = SIXTRL_NULLPTR;

    buf_size_t num_dataptrs = ( buf_size_t )0u;

    NS(SCInterpolatedProfile) sc_elem;
    NS(SCInterpolatedProfile_preset)( &sc_elem );

    num_dataptrs = NS(SCInterpolatedProfile_num_dataptrs)(
        &sc_elem );
    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )0u );

    added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
            &sc_elem, sizeof( sc_elem ),
                NS(SCInterpolatedProfile_type_id)(), num_dataptrs,
                    SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC
NS(SCInterpolatedProfile)* NS(SCInterpolatedProfile_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_REAL_T const number_of_particles,
    SIXTRL_REAL_T const sigma_x, SIXTRL_REAL_T const sigma_y,
    SIXTRL_REAL_T const length, SIXTRL_REAL_T const x_co,
    SIXTRL_REAL_T const y_co,
    SIXTRL_REAL_T const line_density_prof_fallback,
    NS(buffer_addr_t) const interpol_data_addr,
    SIXTRL_REAL_T const min_sigma_diff, bool const enabled )
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        added_elem = SIXTRL_NULLPTR;

    buf_size_t num_dataptrs = ( buf_size_t )0u;

    NS(SCInterpolatedProfile) sc_elem;
    NS(SCInterpolatedProfile_preset)( &sc_elem );
    NS(SCInterpolatedProfile_set_number_of_particles)(
        &sc_elem, number_of_particles );

    NS(SCInterpolatedProfile_set_sigma_x)( &sc_elem, sigma_x );
    NS(SCInterpolatedProfile_set_sigma_y)( &sc_elem, sigma_y );
    NS(SCInterpolatedProfile_set_length)( &sc_elem, length );
    NS(SCInterpolatedProfile_set_x_co)( &sc_elem, x_co );
    NS(SCInterpolatedProfile_set_y_co)( &sc_elem, y_co );
    NS(SCInterpolatedProfile_set_enabled)( &sc_elem, enabled );

    NS(SCInterpolatedProfile_set_interpol_data_addr)(
        &sc_elem, interpol_data_addr );

    NS(SCInterpolatedProfile_set_line_density_prof_fallback)(
        &sc_elem, line_density_prof_fallback );

    NS(SCInterpolatedProfile_set_min_sigma_diff)(
        &sc_elem, min_sigma_diff );

    num_dataptrs = NS(SCInterpolatedProfile_num_dataptrs)( &sc_elem );
    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )0u );

    added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
        &sc_elem, sizeof( sc_elem ), NS(SCInterpolatedProfile_type_id)(),
            num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );

    return added_elem;
}

SIXTRL_BE_ARGPTR_DEC
NS(SCInterpolatedProfile)* NS(SCInterpolatedProfile_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(SCInterpolatedProfile) *const
        SIXTRL_RESTRICT sc_elem ) SIXTRL_NOEXCEPT
{
    typedef NS(buffer_size_t) buf_size_t;
    SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        added_elem = SIXTRL_NULLPTR;

    buf_size_t num_dataptrs =
        NS(SCInterpolatedProfile_num_dataptrs)( sc_elem );
    SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )0u );

    added_elem = ( SIXTRL_BE_ARGPTR_DEC NS(SCInterpolatedProfile)*
        )( uintptr_t )NS(Object_get_begin_addr)( NS(Buffer_add_object)( buffer,
        sc_elem, sizeof( NS(SCInterpolatedProfile) ),
            NS(SCInterpolatedProfile_type_id)(), num_dataptrs,
                SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR ) );

    return added_elem;
}

/* end: sixtracklib/common/be_beamfields/be_beamfields.c */
