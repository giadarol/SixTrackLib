#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_OBJECT_H__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_OBJECT_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/buffer_object_defines.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(Object)
{
    NS(buffer_addr_t)    begin_addr       SIXTRL_ALIGN( 8u );
    NS(object_type_id_t) type_id          SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    size             SIXTRL_ALIGN( 8u );
}
NS(Object);

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)*
NS(Object_preset)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t) NS(Object_get_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN void NS(Object_set_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_addr_t) const begin_addr );

SIXTRL_STATIC SIXTRL_FN  NS(object_type_id_t) NS(Object_get_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(object_type_id_t) const type_id );

SIXTRL_STATIC SIXTRL_FN  NS(buffer_size_t) NS(Object_get_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob,
    NS(buffer_size_t) const size );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_size_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob,
    NS(buffer_size_t) const size );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char const*
NS(Object_get_const_begin_ptr)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char*
NS(Object_get_begin_ptr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN void NS(Object_set_begin_ptr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob,
    SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT begin_ptr );

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN SIXTRL_ARGPTR_DEC NS(Object)*
NS(Object_preset_priv)( SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_size_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_size_t) const obj_size );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_begin_addr_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_addr_t) const address );

SIXTRL_STATIC SIXTRL_FN  void NS(Object_set_type_id_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(object_type_id_t) const type_id );

SIXTRL_STATIC SIXTRL_FN void NS(Object_set_begin_ptr_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ob,
    SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT begin_ptr );

/* ========================================================================= */

SIXTRL_STATIC SIXTRL_FN void NS(Object_print_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj,
    NS(buffer_size_t) const num_slots_to_print );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* *
 * *****         Implementation of inline functions and methods        ***** *
 * ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */

SIXTRL_INLINE SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* NS(Object_preset)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object )
{
    if( object != SIXTRL_NULLPTR )
    {
        NS(Object_set_begin_addr)( object, 0u );
        NS(Object_set_type_id)( object, 0u );
        NS(Object_set_size)( object, 0u );
    }

    return object;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_addr_t) NS(Object_get_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT object )
{
    #if !defined( NDEBUG )
    typedef unsigned char const*    ptr_to_raw_t;
    #endif /* !defined( NDEBUG ) */

    typedef NS(buffer_addr_t)       address_t;

    SIXTRL_ASSERT(
        (   sizeof( ptr_to_raw_t ) >= sizeof( address_t ) ) ||
        ( ( sizeof( ptr_to_raw_t ) == 4u ) &&
          ( sizeof( address_t    ) == 8u ) &&
          ( ( ( object != SIXTRL_NULLPTR ) &&
              ( ( ( address_t )NS(ManagedBuffer_get_limit_offset_max)() >
                object->begin_addr ) ) ) ||
            (   object == SIXTRL_NULLPTR ) ) ) );

    return ( object != SIXTRL_NULLPTR ) ? object->begin_addr : ( address_t )0u;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Object_set_begin_addr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_addr_t) const begin_addr )
{
    #if !defined( NDEBUG )
    typedef unsigned char const*    ptr_to_raw_t;
    typedef NS(buffer_addr_t)       address_t;

    SIXTRL_ASSERT(
        (   sizeof( ptr_to_raw_t ) >= sizeof( address_t ) ) ||
        ( ( sizeof( ptr_to_raw_t ) == 4u ) &&
          ( sizeof( address_t    ) == 8u ) &&
          ( ( address_t )NS(ManagedBuffer_get_limit_offset_max)() >
              begin_addr ) ) );
    #endif /* !defined( NDEBUG ) */

    if( object != SIXTRL_NULLPTR ) object->begin_addr = begin_addr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(object_type_id_t) NS(Object_get_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT object )
{
    return ( object != SIXTRL_NULLPTR )
        ? object->type_id : ( NS(object_type_id_t ) )0;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Object_set_type_id)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(object_type_id_t) const type_id )
{
    if( object != SIXTRL_NULLPTR ) object->type_id = type_id;
    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(Object_get_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT object )
{
    return ( object != SIXTRL_NULLPTR )
        ? object->size : ( NS(buffer_size_t) )0u;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(Object_set_size)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_size_t) const size )
{
    if( object != SIXTRL_NULLPTR )
    {
        object->size = size;
    }

    return;
}

SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char const*
NS(Object_get_const_begin_ptr)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
    NS(Object) *const SIXTRL_RESTRICT object )
{
    typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char const* ptr_to_raw_t;
    return ( ptr_to_raw_t )( uintptr_t )NS(Object_get_begin_addr)( object );
}

SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char*
NS(Object_get_begin_ptr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object )
{
    return ( SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char*
        )NS(Object_get_const_begin_ptr)( object );
}

SIXTRL_INLINE void NS(Object_set_begin_ptr)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT begin_ptr )
{
    typedef NS(buffer_addr_t) address_t;
    NS(Object_set_begin_addr)( object, ( address_t )( uintptr_t )begin_ptr );
    return;
}

/* ------------------------------------------------------------------------ */

SIXTRL_INLINE SIXTRL_ARGPTR_DEC NS(Object)*
NS(Object_preset_priv)( SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object )
{
    if( object != SIXTRL_NULLPTR )
    {
        NS(Object_set_begin_addr_priv)( object, 0u );
        NS(Object_set_type_id_priv)( object, 0u );
        NS(Object_set_size_priv)( object, 0u );
    }

    return object;
}

SIXTRL_INLINE  void NS(Object_set_type_id_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(object_type_id_t) const type_id )
{
    if( object != SIXTRL_NULLPTR ) object->type_id = type_id;
    return;
}

SIXTRL_INLINE  void NS(Object_set_size_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_size_t) const obj_size )
{
    if( object != SIXTRL_NULLPTR ) object->size = obj_size;
    return;
}

SIXTRL_INLINE  void NS(Object_set_begin_addr_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    NS(buffer_addr_t) const address )
{
    if( object != SIXTRL_NULLPTR ) object->begin_addr = address;
    return;
}

SIXTRL_INLINE void NS(Object_set_begin_ptr_priv)(
    SIXTRL_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT object,
    SIXTRL_BUFFER_OBJ_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT begin_ptr )
{
    typedef NS(buffer_addr_t) address_t;
    NS(Object_set_begin_addr_priv)( object,
        ( address_t )( uintptr_t )begin_ptr );

    return;
}

/* ------------------------------------------------------------------------ */


SIXTRL_INLINE void NS(Object_print_slots)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT obj,
    NS(buffer_size_t) const num_slots_to_print )
{
    typedef NS(buffer_addr_t)    address_t;
    typedef NS(buffer_size_t)    buf_size_t;
    typedef NS(object_type_id_t) type_id_t;

    type_id_t const type_id = NS(Object_get_type_id)( obj );

    buf_size_t const slot_size = ( buf_size_t )8u;
    buf_size_t const obj_size  = NS(Object_get_size)( obj );
    buf_size_t const num_slots = obj_size / slot_size;

    SIXTRL_BUFFER_OBJ_DATAPTR_DEC address_t const* ptr_slots =
        ( SIXTRL_BUFFER_OBJ_DATAPTR_DEC address_t const* )NS(Object_get_begin_addr)(
            obj );

    buf_size_t ii = ( buf_size_t )0u;
    buf_size_t nn = num_slots;

    if( ( num_slots_to_print > ( buf_size_t )0u ) &&
        ( num_slots_to_print < num_slots ) )
    {
        nn = num_slots_to_print;
    }

    printf( "type_id            : %8d\r\n", ( int )type_id );
    printf( "obj size           : %8d\r\n", ( int )obj_size );
    printf( "num_slots          : %8d\r\n", ( int )num_slots );
    printf( "num_slots to print : %8d\r\n", ( int )nn );

    for( ; ii < nn ; ++ii )
    {
        if( ii < 21 )
        {
            printf( "slot_id = %8lu | slot addr = %20lu | slot_value = %20lu\r\n",
                ( unsigned long )ii,
                ( unsigned long )&ptr_slots[ ii ],
                ( unsigned long )ptr_slots[ ii ] );
        }
        else
        {
            printf( "slot_id = %8lu | slot addr = %20lu | slot_value = %+19.12f\r\n",
                ( unsigned long )ii,
                ( unsigned long )&ptr_slots[ ii ],
                *( ( SIXTRL_BUFFER_OBJ_DATAPTR_DEC double const* )&ptr_slots[ ii ] ) );
        }
    }

    return;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_OBJECT_H__ */

/* end: sixtracklib/common/buffer/buffer_object.h */
