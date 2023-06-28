/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/

#ifndef	_NINJA_VAL_H_
#define	_NINJA_VAL_H_

extern  NJS_SCREEN	_nj_screen_;
extern  NJS_VIEW	*_nj_view_;
extern  NJS_MATRIX  _nj_view_matrix_;
DataRef(NJS_MATRIX*,	_nj_current_matrix_ptr_,	0x01A557FC);
DataRef(NJS_MATRIX*,	_nj_base_matrix_ptr_,		0x0267053C);
DataRef(NJS_MATRIX*,	_nj_max_matrix_ptr_,		0x0267053C);	/* Maximum Matrix Stack Pointer */
extern  NJS_POINT2  _nj_2d_clip_[2];
extern  float32       _nj_near_clip_;
extern  float32       _nj_far_clip_;
extern  float32       _nj_scr_aspect_x_;
extern  float32       _nj_scr_aspect_y_;
extern 	sint32			_nj_display_mode_;
extern	sint32			_nj_frame_mode_;
extern	sint32			_nj_waitvsync_count;

DataRef(uint32, _nj_control_3d_flag_, 0x25F02D8);

extern uint32 _nj_vertex_buffer_op_;
extern uint32 _nj_vertex_buffer_om_;
extern uint32 _nj_vertex_buffer_tp_;
extern uint32 _nj_vertex_buffer_tm_;
extern uint32 _nj_vertex_buffer_pt_;


extern uint32 _nj_start_vertex_op;
extern uint32 _nj_start_vertex_om;
extern uint32 _nj_start_vertex_tp;
extern uint32 _nj_start_vertex_tm;
extern uint32 _nj_start_vertex_pt;

extern sint32 _nj_frame_size_w;
extern sint32 _nj_frame_size_h;

/******************************/
/* Global Variable for Model  */
DataRef(NJS_VERTEX_BUF*, _nj_vertex_buf_, 0x025EFE48);
extern	sint32	_nj_vertex_num_;

extern	sint32	_nj_calc_vertex_;
extern	sint32	_nj_calc_polygon_;
extern	sint32	_nj_draw_polygon_;
DataRef(uint32, _nj_constant_attr_and_, 0x25F0268);
DataRef(uint32, _nj_constant_attr_or_, 0x025F02D4);
DataRef(NJS_ARGB, _nj_constant_material_, 0x025EFFD0);
extern	uint32	_nj_cnk_blend_mode_;

extern	uint32	_nj_vsync_count_;
extern	float32	_nj_depth_near_;
extern	float32	_nj_depth_far_;
extern	float32	_nj_depth_range_;
extern	float32	_nj_vertex_offset_;
extern	sint32		_nj_depth_enable_;

extern  sint32	volatile _nj_fatal_err_callback_;

/******************************/
/* Global Variable for Motion */
extern NJS_CAMERA _nj_motion_camera_;

/******************************/
/* Global Variable for Light  */

extern	NJS_LIGHT_MATERIAL		_nj_light_material_;/* the info.from Material */

/******************************/
/* Global Variable for Matrix */

extern sint32   _stack_size_;         /* Number of Matrices pushed on the Stack */

//extern NJS_MATRIX   _unit_matrix_;
DataRef(NJS_MATRIX, _nj_unit_matrix_, 0x025F02A0); /* This is likely the above thing, but named different for some reason?? */

/*******************************/
/* Global Variable for Texture */
extern NJS_TEXLIST *_nj_current_texlist;        /* current texture list pointer */
extern NJS_TEXMEMLIST *_nj_texmemlist;          /* texture memory list pointer */
extern uint32 _nj_texmemsize;                   /* texture momory list size */
extern sint32 _nj_tex_count;
extern uint32 _nj_current_texture;              /* current texture globalIndex */
extern uint32 _nj_current_texture_bank;
extern char _nj_current_texture_path[256];

extern uint32 _nj_tex_max_free_size;
extern uint32 _nj_user_globalIndex;
extern sint32 _nj_texglobal_color_;
extern NJS_TEXERRSTAT _nj_texerr_;
extern sint32 _nj_loadtexreq_mode_;
extern sint32 _nj_loadtexreq_i_;

extern sint8	*_nj_texture_buffer_st;
extern uint32 _nj_texture_buffer_max_size;
#endif
