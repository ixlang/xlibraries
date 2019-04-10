// xfftw.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#define XFFTW_EXPORT extern "C"

XNLEXPORT xptr XI_CDECL alloc_complex(xint size){
	return fftw_malloc(sizeof(fftw_complex) * size);
}

XNLEXPORT void XI_CDECL free_complex(xptr p){
	fftw_free(p);
}


XNLEXPORT void XI_CDECL fill_complex_double2(xptr p, xint offset, xint size, xint eoffset, double *rnp, double * inp){
	fftw_complex * fp = (fftw_complex *)p;
	int sv = eoffset - offset;

	for (xint i = offset; i < size; ++i){
		fp[i][0] = rnp[i + sv];
		fp[i][1] = inp[i + sv];
	}
}



XNLEXPORT void XI_CDECL fill_complex_double(xptr p, xint offset, xint size, xint eoffset, double *rnp){
	fftw_complex * fp = (fftw_complex *)p;
	int sv = eoffset - offset;
	for (xint i = offset; i < size; ++i){
		fp[i][0] = rnp[i + sv];
		fp[i][1] = 0;
	}
}

XNLEXPORT void XI_CDECL extract_complex_double2(xptr p, xint offset, xint size, xint eoffset, double *rnp, double * inp){
	fftw_complex * fp = (fftw_complex *)p;
	int sv = eoffset - offset;
	for (xint i = offset; i < size; ++i){
		rnp[i + sv] = fp[i][0];
		inp[i + sv] = fp[i][1];
	}
}

XNLEXPORT void XI_CDECL extract_complex_double(xptr p, xint offset, xint size, xint eoffset, double *rnp){
	fftw_complex * fp = (fftw_complex *)p;
	int sv = eoffset - offset;

	for (xint i = offset; i < size; ++i){
		rnp[i + sv] = fp[i][0];
	}
}

XNLEXPORT double XI_CDECL get_complex_double(xptr p, xint index, xbool bi){
	fftw_complex * fp = (fftw_complex *)p;
	return bi ? fp[index][0] : fp[index][1];
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_dft_3d(xint n0, xint n1, xint n2, fftw_complex * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_3d(n0, n1, n2, in, out, sign, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_dft_2d(xint n0, xint n1, fftw_complex * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_2d(n0, n1, in, out, sign, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_dft_1d(xint n, fftw_complex * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_1d(n,  in, out, sign, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_c2r_1d(xint n, fftw_complex * in, double * out, xint sign, xint flag){
	return fftw_plan_dft_c2r_1d(n, in, out, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_r2c_1d(xint n, double * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_r2c_1d(n, in, out, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_c2r_2d(xint n0, xint n1, fftw_complex * in, double * out, xint sign, xint flag){
	return fftw_plan_dft_c2r_2d(n0, n1, in, out, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_r2c_2d(xint n0, xint n1, double * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_r2c_2d(n0, n1, in, out, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_c2r_3d(xint n0, xint n1, xint n2, fftw_complex * in, double * out, xint sign, xint flag){
	return fftw_plan_dft_c2r_3d(n0, n1, n2, in, out, flag);
}

XNLEXPORT xptr XI_CDECL create_fftw_plan_r2c_3d(xint n0, xint n1, xint n2, double * in, fftw_complex * out, xint sign, xint flag){
	return fftw_plan_dft_r2c_3d(n0, n1, n2, in, out, flag);
}

XNLEXPORT void XI_CDECL execute_fftw(xptr p){
	fftw_execute((fftw_plan)p);
}

XNLEXPORT void XI_CDECL free_plan(xptr p){
	fftw_destroy_plan((fftw_plan)p);
}