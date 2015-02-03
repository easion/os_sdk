
typedef enum
{
    GI_RENDER_OP_CLEAR			= 0x00,
    GI_RENDER_OP_SRC			= 0x01,
    GI_RENDER_OP_DST			= 0x02,
    GI_RENDER_OP_OVER			= 0x03,
    GI_RENDER_OP_OVER_REVERSE		= 0x04,
    GI_RENDER_OP_IN			= 0x05,
    GI_RENDER_OP_IN_REVERSE		= 0x06,
    GI_RENDER_OP_OUT			= 0x07,
    GI_RENDER_OP_OUT_REVERSE		= 0x08,
    GI_RENDER_OP_ATOP			= 0x09,
    GI_RENDER_OP_ATOP_REVERSE		= 0x0a,
    GI_RENDER_OP_XOR			= 0x0b,
    GI_RENDER_OP_ADD			= 0x0c,
    GI_RENDER_OP_SATURATE			= 0x0d,

    GI_RENDER_OP_DISJOINT_CLEAR		= 0x10,
    GI_RENDER_OP_DISJOINT_SRC		= 0x11,
    GI_RENDER_OP_DISJOINT_DST		= 0x12,
    GI_RENDER_OP_DISJOINT_OVER		= 0x13,
    GI_RENDER_OP_DISJOINT_OVER_REVERSE	= 0x14,
    GI_RENDER_OP_DISJOINT_IN		= 0x15,
    GI_RENDER_OP_DISJOINT_IN_REVERSE	= 0x16,
    GI_RENDER_OP_DISJOINT_OUT		= 0x17,
    GI_RENDER_OP_DISJOINT_OUT_REVERSE	= 0x18,
    GI_RENDER_OP_DISJOINT_ATOP		= 0x19,
    GI_RENDER_OP_DISJOINT_ATOP_REVERSE	= 0x1a,
    GI_RENDER_OP_DISJOINT_XOR		= 0x1b,

    GI_RENDER_OP_CONJOINT_CLEAR		= 0x20,
    GI_RENDER_OP_CONJOINT_SRC		= 0x21,
    GI_RENDER_OP_CONJOINT_DST		= 0x22,
    GI_RENDER_OP_CONJOINT_OVER		= 0x23,
    GI_RENDER_OP_CONJOINT_OVER_REVERSE	= 0x24,
    GI_RENDER_OP_CONJOINT_IN		= 0x25,
    GI_RENDER_OP_CONJOINT_IN_REVERSE	= 0x26,
    GI_RENDER_OP_CONJOINT_OUT		= 0x27,
    GI_RENDER_OP_CONJOINT_OUT_REVERSE	= 0x28,
    GI_RENDER_OP_CONJOINT_ATOP		= 0x29,
    GI_RENDER_OP_CONJOINT_ATOP_REVERSE	= 0x2a,
    GI_RENDER_OP_CONJOINT_XOR		= 0x2b,

    GI_RENDER_OP_MULTIPLY                  = 0x30,
    GI_RENDER_OP_SCREEN                    = 0x31,
    GI_RENDER_OP_OVERLAY                   = 0x32,
    GI_RENDER_OP_DARKEN                    = 0x33,
    GI_RENDER_OP_LIGHTEN                   = 0x34,
    GI_RENDER_OP_COLOR_DODGE               = 0x35,
    GI_RENDER_OP_COLOR_BURN                = 0x36,
    GI_RENDER_OP_HARD_LIGHT                = 0x37,
    GI_RENDER_OP_SOFT_LIGHT                = 0x38,
    GI_RENDER_OP_DIFFERENCE                = 0x39,
    GI_RENDER_OP_EXCLUSION                 = 0x3a,
    GI_RENDER_OP_HSL_HUE			= 0x3b,
    GI_RENDER_OP_HSL_SATURATION		= 0x3c,
    GI_RENDER_OP_HSL_COLOR			= 0x3d,
    GI_RENDER_OP_HSL_LUMINOSITY		= 0x3e,

#ifdef GI_RENDER_USE_INTERNAL_API
    GI_RENDER_N_OPERATORS,
    GI_RENDER_OP_NONE = GI_RENDER_N_OPERATORS
#endif
} gi_render_op_t;



 enum
{
    GI_RENDER_REPEAT_NONE,
    GI_RENDER_REPEAT_NORMAL,
    GI_RENDER_REPEAT_PAD,
    GI_RENDER_REPEAT_REFLECT
} ;

 enum
{
    GI_RENDER_FILTER_FAST,
    GI_RENDER_FILTER_GOOD,
    GI_RENDER_FILTER_BEST,
    GI_RENDER_FILTER_NEAREST,
    GI_RENDER_FILTER_BILINEAR,
    GI_RENDER_FILTER_CONVOLUTION
} ;


typedef struct {
    uint16_t   red;
    uint16_t   green;
    uint16_t   blue;
    uint16_t   alpha;
} gi_render_color_t;


typedef struct 
{
    int32_t	matrix[3][3];
}gi_render_transform_t;




enum{
	RENDER_CALL_FILTER=1,
	RENDER_CALL_CLIPRGN,
	RENDER_CALL_CREATE_WIN,
	RENDER_CALL_CREATE_DATA,
	RENDER_CALL_SF,
	RENDER_CALL_FREE,
	RENDER_CALL_COMP,
	RENDER_CALL_FILLRECTS,
	RENDER_CALL_TRANS,
	RENDER_CALL_REPEAT,
	RENDER_CALL_INFO,
	RENDER_CALL_ADD_TRAP,
	RENDER_CALL_GRADIENT,
	RENDER_CALL_ALPHA_MAP,
	RENDER_CALL_SET_ATTR,
	RENDER_CALL_COMP_ALPHA,
};

struct gi_point_fixed
{
    int32_t	x;
    int32_t	y;
};

struct gi_line_fixed
{
    struct gi_point_fixed	p1, p2;
};

typedef struct 
{
    int32_t	top, bottom;
    struct gi_line_fixed	left, right;
} gi_trapezoid_t;

typedef struct 
{
	int width,height,stride,depth;
}gi_render_info_t;


typedef struct  {
    int32_t x;
	gi_render_color_t color;
    //xRenderColor color;
} gi_gradient_stop_t;


typedef struct  {
    int nstops;
    gi_gradient_stop_t *stops;
    int stopRange;

	union{
		struct 
		{
		struct gi_point_fixed p1;
		struct gi_point_fixed p2;
		}linear;

		struct 
		{
		struct gi_point_fixed c1;
		struct gi_point_fixed c2;
		int32_t radius1;
		int32_t radius2;
		}radial;

		struct 
		{
		struct gi_point_fixed center;
		int32_t                angle;
		}conical;
	};

} gi_gradient_t;


struct gi_render_span_fix
{
    int32_t	l, r, y;
};

typedef struct 
{
    struct gi_render_span_fix	top, bot;
}gi_render_trap_t;


