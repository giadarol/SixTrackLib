#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include "sixtracklib/testlib/common/beam_elements/be_limit_ellipse.h"
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/be_limit/definitions.h"
    #include "sixtracklib/common/be_limit/be_limit_ellipse.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

void NS(LimitEllipse_print)( SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const NS(LimitEllipse) *const SIXTRL_RESTRICT limit )
{
    if( ( fp != SIXTRL_NULLPTR ) && ( limit != SIXTRL_NULLPTR ) )
    {
        fprintf( fp,
                "|limit_ellipse    | half-axis x = %+16.12f m;\r\n"
                "                  | half-axis y = %+16.12f m;\r\n",
                NS(LimitEllipse_x_half_axis)( limit ),
                NS(LimitEllipse_y_half_axis)( limit ) );
    }

    return;
}

#endif /* !defined( _GPUCODE ) */

/* end: tests/sixtracklib/testlib/common/beam_elements/be_limit_rect.c */
