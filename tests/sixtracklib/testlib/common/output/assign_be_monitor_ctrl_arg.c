#include "sixtracklib/testlib/common/output/assign_be_monitor_ctrl_arg.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/argument_base.h"
#include "sixtracklib/common/be_monitor/be_monitor.h"
#include "sixtracklib/common/be_monitor/output_buffer.h"

#include "sixtracklib/testlib/common/particles/particles.h"

NS(arch_status_t) NS(TestBeamMonitorCtrlArg_prepare_assign_output_buffer)(
    NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    NS(buffer_size_t) const num_particle_sets,
    NS(buffer_size_t) const* particle_set_indices_begin,
    NS(ArgumentBase)* SIXTRL_RESTRICT beam_elements_arg,
    NS(Buffer)* SIXTRL_RESTRICT beam_elements_buffer,
    NS(ArgumentBase)* SIXTRL_RESTRICT output_arg,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(particle_index_t) const min_turn_id,
    NS(buffer_size_t)* ptr_output_buffer_index_offset,
    NS(ArgumentBase)* SIXTRL_RESTRICT result_arg )
{
    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);

    typedef NS(buffer_size_t) buf_size_t;

    if( ( particles_buffer != SIXTRL_NULLPTR ) &&
        ( num_particle_sets > ( NS(buffer_size_t) )0u ) &&
        ( particle_set_indices_begin != SIXTRL_NULLPTR ) &&
        ( beam_elements_arg != SIXTRL_NULLPTR ) &&
        ( beam_elements_buffer != SIXTRL_NULLPTR ) &&
        ( output_arg != SIXTRL_NULLPTR ) &&
        ( output_buffer != SIXTRL_NULLPTR ) &&
        ( ( NS(Buffer_get_num_of_objects)( output_buffer ) ==
                ( buf_size_t )0u ) ||
          ( NS(Buffer_is_particles_buffer)( output_buffer ) ) ) )
    {
        NS(buffer_size_t) output_buffer_index_offset = ( NS(buffer_size_t) )0u;

        status = NS(BeamMonitor_prepare_output_buffer_for_particle_sets)(
            beam_elements_buffer, output_buffer, particles_buffer,
                num_particle_sets, particle_set_indices_begin,
                    &output_buffer_index_offset );

        if( ptr_output_buffer_index_offset != SIXTRL_NULLPTR )
        {
            *ptr_output_buffer_index_offset = output_buffer_index_offset;
        }

        if( status == NS(ARCH_STATUS_SUCCESS) )
        {
            status = NS(BeamMonitor_assign_output_buffer_from_offset)(
                beam_elements_buffer, output_buffer, min_turn_id,
                    output_buffer_index_offset );
        }

        if( status == NS(ARCH_STATUS_SUCCESS) )
        {
            status = NS(Argument_send_buffer)(
                beam_elements_arg, beam_elements_buffer );
        }

        if( status == NS(ARCH_STATUS_SUCCESS) )
        {
            status = NS(Argument_send_buffer)( output_arg, output_buffer );
        }

        if( ( status == NS(ARCH_STATUS_SUCCESS) ) &&
            ( result_arg != SIXTRL_NULLPTR ) )
        {
            NS(arch_debugging_t) result_register =
                SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY;

            status = NS(Argument_send_raw_argument)(
                result_arg, &result_register, sizeof( result_register ) );
        }
    }

    return status;
}

NS(arch_status_t) NS(TestBeamMonitorCtrlArg_evaluate_assign_output_buffer)(
    NS(ArgumentBase)* SIXTRL_RESTRICT beam_elements_arg,
    NS(Buffer)* SIXTRL_RESTRICT beam_elements_buffer,
    NS(ArgumentBase)* SIXTRL_RESTRICT output_arg,
    NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const output_buffer_index_offset,
    NS(buffer_size_t) const num_beam_monitors,
    NS(ArgumentBase)* SIXTRL_RESTRICT result_arg )
{
    typedef NS(buffer_addr_t) address_t;
    typedef NS(buffer_addr_diff_t) addr_diff_t;
    typedef NS(BeamMonitor) const* ptr_be_monitor_t;
    typedef SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* obj_iter_t;

    NS(arch_status_t) status = NS(ARCH_STATUS_GENERAL_FAILURE);
    NS(buffer_size_t) const nn = output_buffer_index_offset + num_beam_monitors;

    if( ( beam_elements_arg != SIXTRL_NULLPTR ) &&
        ( beam_elements_buffer != SIXTRL_NULLPTR ) &&
        ( output_arg != SIXTRL_NULLPTR ) &&
        ( output_buffer != SIXTRL_NULLPTR ) &&
        ( NS(Buffer_get_num_of_objects)( output_buffer ) >= nn ) &&
        ( NS(Buffer_is_particles_buffer)( output_buffer ) ) )
    {
        NS(buffer_size_t) const slot_size =
            NS(Buffer_get_slot_size)( output_buffer );

        address_t host_base_addr = ( address_t )0u;
        address_t remote_base_addr = ( address_t )0u;

        SIXTRL_ASSERT( slot_size > ( NS(buffer_size_t) )0u );

        status = NS(Argument_receive_buffer)(
            beam_elements_arg, beam_elements_buffer );

        if( ( result_arg != SIXTRL_NULLPTR ) &&
            ( status == NS(ARCH_STATUS_SUCCESS) ) )
        {
            NS(arch_debugging_t) result_register =
                SIXTRL_ARCH_DEBUGGING_GENERAL_FAILURE;

            status = NS(Argument_receive_raw_argument)(
                result_arg, &result_register, sizeof( result_register ) );

            if( ( status == NS(ARCH_STATUS_SUCCESS) ) &&
                ( result_register != SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY ) )
            {
                if( NS(DebugReg_has_status_flags_set)( result_register ) )
                {
                    status = NS(DebugReg_get_stored_arch_status)(
                        result_register );
                }
                else
                {
                    status = NS(ARCH_STATUS_GENERAL_FAILURE);
                }

                SIXTRL_ASSERT( status != NS(ARCH_STATUS_SUCCESS) );
            }

            SIXTRL_ASSERT( ( status != NS(ARCH_STATUS_SUCCESS) ) ||
                ( result_register == SIXTRL_ARCH_DEBUGGING_REGISTER_EMPTY ) );
        }

        if( status == NS(ARCH_STATUS_SUCCESS) )
        {
            NS(Buffer_clear)( output_buffer, true );
            NS(Buffer_reset)( output_buffer );

            status = NS(Argument_receive_buffer_without_remap)(
                output_arg, output_buffer );

            if( status == NS(ARCH_STATUS_SUCCESS) )
            {
                remote_base_addr = NS(ManagedBuffer_get_stored_begin_addr)(
                    NS(Buffer_get_data_begin)( output_buffer ), slot_size );

                host_base_addr = NS(ManagedBuffer_get_buffer_begin_addr)(
                    NS(Buffer_get_data_begin)( output_buffer ), slot_size );

                NS(Buffer_remap)( output_buffer );

                if( ( NS(Buffer_needs_remapping)( output_buffer ) ) ||
                    ( NS(Buffer_get_num_of_objects)( output_buffer ) < nn ) )
                {
                    status = NS(ARCH_STATUS_GENERAL_FAILURE);
                }
            }
        }

        if( status ==NS(ARCH_STATUS_SUCCESS) )
        {
            status = NS(ARCH_STATUS_GENERAL_FAILURE);

            if( ( remote_base_addr != ( address_t )0u ) &&
                ( host_base_addr   != ( address_t )0u ) )
            {
                NS(buffer_size_t) ii = output_buffer_index_offset;

                obj_iter_t be_it  = NS(Buffer_get_const_objects_begin)(
                    beam_elements_buffer );

                obj_iter_t be_end = NS(Buffer_get_const_objects_end)(
                    beam_elements_buffer );

                /* host = remote + diff_addr => diff_addr = host - remote */
                NS(buffer_addr_diff_t) const diff_addr =
                    ( host_base_addr >= remote_base_addr )
                    ? ( addr_diff_t )( host_base_addr - remote_base_addr )
                    : -( ( addr_diff_t )( remote_base_addr - host_base_addr ) );

                status = NS(ARCH_STATUS_SUCCESS);

                for( ; be_it != be_end ; ++be_it )
                {
                    ptr_be_monitor_t be_monitor = SIXTRL_NULLPTR;
                    address_t cmp_out_addr = ( address_t )0u;
                    address_t be_out_addr  = ( address_t )0u;

                    if( NS(Object_get_type_id)( be_it ) !=
                        NS(OBJECT_TYPE_BEAM_MONITOR) )
                    {
                        continue;
                    }

                    be_monitor = ( ptr_be_monitor_t )( uintptr_t
                        )NS(Object_get_begin_addr)( be_it );

                    be_out_addr = NS(BeamMonitor_out_address)( be_monitor );

                    cmp_out_addr = ( address_t )( uintptr_t
                        )NS(Particles_buffer_get_const_particles)(
                            output_buffer, ii++ );

                    if( ( diff_addr >= ( NS(buffer_addr_diff_t) )0u ) ||
                        ( ( -diff_addr ) <= (
                            NS(buffer_addr_diff_t) )be_out_addr ) )
                    {
                        be_out_addr += diff_addr;

                        if( be_out_addr != cmp_out_addr )
                        {
                            status = NS(ARCH_STATUS_GENERAL_FAILURE);
                            break;
                        }
                    }
                    else
                    {
                        status = NS(ARCH_STATUS_GENERAL_FAILURE);
                        break;
                    }

                    ++ii;

                    if( ii >= nn )
                    {
                        break;
                    }
                }
            }
        }
    }

    return status;
}

/* tests/sixtracklib/testlib/common/output/assign_elem_by_elem_ctrl_arg.c */
