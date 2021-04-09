//xlang Source, Name:qt5/widgets/QOpenGLFunctions_1_0.x 
//Date: Tue Mar 21:31:32 2021 

package Qt{
    public class QOpenGLFunctions_1_1 : QAbstractOpenGLFunctions{
        public QOpenGLFunctions_1_1(){
            
        }
        public QOpenGLFunctions_1_1(long h){
            super(h);
        }
        
        public bool initializeOpenGLFunctions() {
            return QtXnl.widget_get_bool_value(nativehandle,  Constant.QOPENGLFUNCTIONS_1_1_INITIALIZEOPENGLFUNCTIONS);
        }
        
        public void glViewport(int x, int y, int width, int height){ qfn_1_1_glViewport(nativehandle, x, y, width, height); }
        public void glDepthRange(double nearVal, double farVal){ qfn_1_1_glDepthRange(nativehandle, nearVal, farVal); }
        public bool glIsEnabled(int cap){ return qfn_1_1_glIsEnabled(nativehandle, cap); }
        public void glGetTexLevelParameteriv(int target, int level, int pname, int  [] params){ qfn_1_1_glGetTexLevelParameteriv(nativehandle, target, level, pname, params); }
        public void glGetTexLevelParameterfv(int target, int level, int pname, float  [] params){ qfn_1_1_glGetTexLevelParameterfv(nativehandle, target, level, pname, params); }
        public void glGetTexParameteriv(int target, int pname, int  [] params){ qfn_1_1_glGetTexParameteriv(nativehandle, target, pname, params); }
        public void glGetTexParameterfv(int target, int pname, float  [] params){ qfn_1_1_glGetTexParameterfv(nativehandle, target, pname, params); }
        public void glGetTexImage(int target, int level, int format, int type, byte  [] pixels){ qfn_1_1_glGetTexImage(nativehandle, target, level, format, type, pixels); }
        public String glGetString(int name){ return qfn_1_1_glGetString(nativehandle, name); }
        public void glGetIntegerv(int pname, int  [] params){ qfn_1_1_glGetIntegerv(nativehandle, pname, params); }
        public void glGetFloatv(int pname, float  [] params){ qfn_1_1_glGetFloatv(nativehandle, pname, params); }
        public int glGetError(){ return qfn_1_1_glGetError(nativehandle); }
        public void glGetDoublev(int pname, double  [] params){ qfn_1_1_glGetDoublev(nativehandle, pname, params); }
        public void glGetBooleanv(int pname, bool  [] params){ qfn_1_1_glGetBooleanv(nativehandle, pname, params); }
        public void glReadPixels(int x, int y, int width, int height, int format, int type, byte  [] pixels){ qfn_1_1_glReadPixels(nativehandle, x, y, width, height, format, type, pixels); }
        public void glReadBuffer(int mode){ qfn_1_1_glReadBuffer(nativehandle, mode); }
        public void glPixelStorei(int pname, int param){ qfn_1_1_glPixelStorei(nativehandle, pname, param); }
        public void glPixelStoref(int pname, float param){ qfn_1_1_glPixelStoref(nativehandle, pname, param); }
        public void glDepthFunc(int func){ qfn_1_1_glDepthFunc(nativehandle, func); }
        public void glStencilOp(int fail, int zfail, int zpass){ qfn_1_1_glStencilOp(nativehandle, fail, zfail, zpass); }
        public void glStencilFunc(int func, int ref, int mask){ qfn_1_1_glStencilFunc(nativehandle, func, ref, mask); }
        public void glLogicOp(int opcode){ qfn_1_1_glLogicOp(nativehandle, opcode); }
        public void glBlendFunc(int sfactor, int dfactor){ qfn_1_1_glBlendFunc(nativehandle, sfactor, dfactor); }
        public void glFlush(){ qfn_1_1_glFlush(nativehandle); }
        public void glFinish(){ qfn_1_1_glFinish(nativehandle); }
        public void glEnable(int cap){ qfn_1_1_glEnable(nativehandle, cap); }
        public void glDisable(int cap){ qfn_1_1_glDisable(nativehandle, cap); }
        public void glDepthMask(bool flag){ qfn_1_1_glDepthMask(nativehandle, flag); }
        public void glColorMask(bool red, bool green, bool blue, bool alpha){ qfn_1_1_glColorMask(nativehandle, red, green, blue, alpha); }
        public void glStencilMask(int mask){ qfn_1_1_glStencilMask(nativehandle, mask); }
        public void glClearDepth(double depth){ qfn_1_1_glClearDepth(nativehandle, depth); }
        public void glClearStencil(int s){ qfn_1_1_glClearStencil(nativehandle, s); }
        public void glClearColor(float red, float green, float blue, float alpha){ qfn_1_1_glClearColor(nativehandle, red, green, blue, alpha); }
        public void glClear(int mask){ qfn_1_1_glClear(nativehandle, mask); }
        public void glDrawBuffer(int mode){ qfn_1_1_glDrawBuffer(nativehandle, mode); }
        public void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, /*IN*/ byte  [] pixels){ qfn_1_1_glTexImage2D(nativehandle, target, level, internalformat, width, height, border, format, type, pixels); }
        public void glTexImage1D(int target, int level, int internalformat, int width, int border, int format, int type, /*IN*/ byte  [] pixels){ qfn_1_1_glTexImage1D(nativehandle, target, level, internalformat, width, border, format, type, pixels); }
        public void glTexParameteriv(int target, int pname, /*IN*/ int  [] params){ qfn_1_1_glTexParameteriv(nativehandle, target, pname, params); }
        public void glTexParameteri(int target, int pname, int param){ qfn_1_1_glTexParameteri(nativehandle, target, pname, param); }
        public void glTexParameterfv(int target, int pname, /*IN*/ float  [] params){ qfn_1_1_glTexParameterfv(nativehandle, target, pname, params); }
        public void glTexParameterf(int target, int pname, float param){ qfn_1_1_glTexParameterf(nativehandle, target, pname, param); }
        public void glScissor(int x, int y, int width, int height){ qfn_1_1_glScissor(nativehandle, x, y, width, height); }
        public void glPolygonMode(int face, int mode){ qfn_1_1_glPolygonMode(nativehandle, face, mode); }
        public void glPointSize(float size){ qfn_1_1_glPointSize(nativehandle, size); }
        public void glLineWidth(float width){ qfn_1_1_glLineWidth(nativehandle, width); }
        public void glHint(int target, int mode){ qfn_1_1_glHint(nativehandle, target, mode); }
        public void glFrontFace(int mode){ qfn_1_1_glFrontFace(nativehandle, mode); }
        public void glCullFace(int mode){ qfn_1_1_glCullFace(nativehandle, mode); }
        public void glIndexubv(/*IN*/ byte  [] c){ qfn_1_1_glIndexubv(nativehandle, c); }
        public void glIndexub(byte c){ qfn_1_1_glIndexub(nativehandle, c); }
        public bool glIsTexture(int texture){ return qfn_1_1_glIsTexture(nativehandle, texture); }
        public void glGenTextures(int n, int  [] textures){ qfn_1_1_glGenTextures(nativehandle, n, textures); }
        public void glDeleteTextures(int n, /*IN*/ int  [] textures){ qfn_1_1_glDeleteTextures(nativehandle, n, textures); }
        public void glBindTexture(int target, int texture){ qfn_1_1_glBindTexture(nativehandle, target, texture); }
        public void glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, /*IN*/ byte  [] pixels){ qfn_1_1_glTexSubImage2D(nativehandle, target, level, xoffset, yoffset, width, height, format, type, pixels); }
        public void glTexSubImage1D(int target, int level, int xoffset, int width, int format, int type, /*IN*/ byte  [] pixels){ qfn_1_1_glTexSubImage1D(nativehandle, target, level, xoffset, width, format, type, pixels); }
        public void glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height){ qfn_1_1_glCopyTexSubImage2D(nativehandle, target, level, xoffset, yoffset, x, y, width, height); }
        public void glCopyTexSubImage1D(int target, int level, int xoffset, int x, int y, int width){ qfn_1_1_glCopyTexSubImage1D(nativehandle, target, level, xoffset, x, y, width); }
        public void glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border){ qfn_1_1_glCopyTexImage2D(nativehandle, target, level, internalformat, x, y, width, height, border); }
        public void glCopyTexImage1D(int target, int level, int internalformat, int x, int y, int width, int border){ qfn_1_1_glCopyTexImage1D(nativehandle, target, level, internalformat, x, y, width, border); }
        public void glPolygonOffset(float factor, float units){ qfn_1_1_glPolygonOffset(nativehandle, factor, units); }
        public void glGetPointerv(int pname, Object params){ qfn_1_1_glGetPointerv(nativehandle, pname, params); }
        public void glDrawElements(int mode, int count, int type, /*IN*/ byte  [] indices){ qfn_1_1_glDrawElements(nativehandle, mode, count, type, indices); }
        public void glDrawArrays(int mode, int first, int count){ qfn_1_1_glDrawArrays(nativehandle, mode, first, count); }
        public void glTranslatef(float x, float y, float z){ qfn_1_1_glTranslatef(nativehandle, x, y, z); }
        public void glTranslated(double x, double y, double z){ qfn_1_1_glTranslated(nativehandle, x, y, z); }
        public void glScalef(float x, float y, float z){ qfn_1_1_glScalef(nativehandle, x, y, z); }
        public void glScaled(double x, double y, double z){ qfn_1_1_glScaled(nativehandle, x, y, z); }
        public void glRotatef(float angle, float x, float y, float z){ qfn_1_1_glRotatef(nativehandle, angle, x, y, z); }
        public void glRotated(double angle, double x, double y, double z){ qfn_1_1_glRotated(nativehandle, angle, x, y, z); }
        public void glPushMatrix(){ qfn_1_1_glPushMatrix(nativehandle); }
        public void glPopMatrix(){ qfn_1_1_glPopMatrix(nativehandle); }
        public void glOrtho(double left, double right, double bottom, double top, double zNear, double zFar){ qfn_1_1_glOrtho(nativehandle, left, right, bottom, top, zNear, zFar); }
        public void glMultMatrixd(/*IN*/ double  [] m){ qfn_1_1_glMultMatrixd(nativehandle, m); }
        public void glMultMatrixf(/*IN*/ float  [] m){ qfn_1_1_glMultMatrixf(nativehandle, m); }
        public void glMatrixMode(int mode){ qfn_1_1_glMatrixMode(nativehandle, mode); }
        public void glLoadMatrixd(/*IN*/ double  [] m){ qfn_1_1_glLoadMatrixd(nativehandle, m); }
        public void glLoadMatrixf(/*IN*/ float  [] m){ qfn_1_1_glLoadMatrixf(nativehandle, m); }
        public void glLoadIdentity(){ qfn_1_1_glLoadIdentity(nativehandle); }
        public void glFrustum(double left, double right, double bottom, double top, double zNear, double zFar){ qfn_1_1_glFrustum(nativehandle, left, right, bottom, top, zNear, zFar); }
        public bool glIsList(int list){ return qfn_1_1_glIsList(nativehandle, list); }
        public void glGetTexGeniv(int coord, int pname, int  [] params){ qfn_1_1_glGetTexGeniv(nativehandle, coord, pname, params); }
        public void glGetTexGenfv(int coord, int pname, float  [] params){ qfn_1_1_glGetTexGenfv(nativehandle, coord, pname, params); }
        public void glGetTexGendv(int coord, int pname, double  [] params){ qfn_1_1_glGetTexGendv(nativehandle, coord, pname, params); }
        public void glGetTexEnviv(int target, int pname, int  [] params){ qfn_1_1_glGetTexEnviv(nativehandle, target, pname, params); }
        public void glGetTexEnvfv(int target, int pname, float  [] params){ qfn_1_1_glGetTexEnvfv(nativehandle, target, pname, params); }
        public void glGetPolygonStipple(byte  [] mask){ qfn_1_1_glGetPolygonStipple(nativehandle, mask); }
        public void glGetPixelMapusv(int map, short  [] values){ qfn_1_1_glGetPixelMapusv(nativehandle, map, values); }
        public void glGetPixelMapuiv(int map, int  [] values){ qfn_1_1_glGetPixelMapuiv(nativehandle, map, values); }
        public void glGetPixelMapfv(int map, float  [] values){ qfn_1_1_glGetPixelMapfv(nativehandle, map, values); }
        public void glGetMaterialiv(int face, int pname, int  [] params){ qfn_1_1_glGetMaterialiv(nativehandle, face, pname, params); }
        public void glGetMaterialfv(int face, int pname, float  [] params){ qfn_1_1_glGetMaterialfv(nativehandle, face, pname, params); }
        public void glGetMapiv(int target, int query, int  [] v){ qfn_1_1_glGetMapiv(nativehandle, target, query, v); }
        public void glGetMapfv(int target, int query, float  [] v){ qfn_1_1_glGetMapfv(nativehandle, target, query, v); }
        public void glGetMapdv(int target, int query, double  [] v){ qfn_1_1_glGetMapdv(nativehandle, target, query, v); }
        public void glGetLightiv(int light, int pname, int  [] params){ qfn_1_1_glGetLightiv(nativehandle, light, pname, params); }
        public void glGetLightfv(int light, int pname, float  [] params){ qfn_1_1_glGetLightfv(nativehandle, light, pname, params); }
        public void glGetClipPlane(int plane, double  [] equation){ qfn_1_1_glGetClipPlane(nativehandle, plane, equation); }
        public void glDrawPixels(int width, int height, int format, int type, /*IN*/ byte  [] pixels){ qfn_1_1_glDrawPixels(nativehandle, width, height, format, type, pixels); }
        public void glCopyPixels(int x, int y, int width, int height, int type){ qfn_1_1_glCopyPixels(nativehandle, x, y, width, height, type); }
        public void glPixelMapusv(int map, int mapsize, /*IN*/ short  [] values){ qfn_1_1_glPixelMapusv(nativehandle, map, mapsize, values); }
        public void glPixelMapuiv(int map, int mapsize, /*IN*/ int  [] values){ qfn_1_1_glPixelMapuiv(nativehandle, map, mapsize, values); }
        public void glPixelMapfv(int map, int mapsize, /*IN*/ float  [] values){ qfn_1_1_glPixelMapfv(nativehandle, map, mapsize, values); }
        public void glPixelTransferi(int pname, int param){ qfn_1_1_glPixelTransferi(nativehandle, pname, param); }
        public void glPixelTransferf(int pname, float param){ qfn_1_1_glPixelTransferf(nativehandle, pname, param); }
        public void glPixelZoom(float xfactor, float yfactor){ qfn_1_1_glPixelZoom(nativehandle, xfactor, yfactor); }
        public void glAlphaFunc(int func, float ref){ qfn_1_1_glAlphaFunc(nativehandle, func, ref); }
        public void glEvalPoint2(int i, int j){ qfn_1_1_glEvalPoint2(nativehandle, i, j); }
        public void glEvalMesh2(int mode, int i1, int i2, int j1, int j2){ qfn_1_1_glEvalMesh2(nativehandle, mode, i1, i2, j1, j2); }
        public void glEvalPoint1(int i){ qfn_1_1_glEvalPoint1(nativehandle, i); }
        public void glEvalMesh1(int mode, int i1, int i2){ qfn_1_1_glEvalMesh1(nativehandle, mode, i1, i2); }
        public void glEvalCoord2fv(/*IN*/ float  [] u){ qfn_1_1_glEvalCoord2fv(nativehandle, u); }
        public void glEvalCoord2f(float u, float v){ qfn_1_1_glEvalCoord2f(nativehandle, u, v); }
        public void glEvalCoord2dv(/*IN*/ double  [] u){ qfn_1_1_glEvalCoord2dv(nativehandle, u); }
        public void glEvalCoord2d(double u, double v){ qfn_1_1_glEvalCoord2d(nativehandle, u, v); }
        public void glEvalCoord1fv(/*IN*/ float  [] u){ qfn_1_1_glEvalCoord1fv(nativehandle, u); }
        public void glEvalCoord1f(float u){ qfn_1_1_glEvalCoord1f(nativehandle, u); }
        public void glEvalCoord1dv(/*IN*/ double  [] u){ qfn_1_1_glEvalCoord1dv(nativehandle, u); }
        public void glEvalCoord1d(double u){ qfn_1_1_glEvalCoord1d(nativehandle, u); }
        public void glMapGrid2f(int un, float u1, float u2, int vn, float v1, float v2){ qfn_1_1_glMapGrid2f(nativehandle, un, u1, u2, vn, v1, v2); }
        public void glMapGrid2d(int un, double u1, double u2, int vn, double v1, double v2){ qfn_1_1_glMapGrid2d(nativehandle, un, u1, u2, vn, v1, v2); }
        public void glMapGrid1f(int un, float u1, float u2){ qfn_1_1_glMapGrid1f(nativehandle, un, u1, u2); }
        public void glMapGrid1d(int un, double u1, double u2){ qfn_1_1_glMapGrid1d(nativehandle, un, u1, u2); }
        public void glMap2f(int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, /*IN*/ float  [] points){ qfn_1_1_glMap2f(nativehandle, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
        public void glMap2d(int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, /*IN*/ double  [] points){ qfn_1_1_glMap2d(nativehandle, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
        public void glMap1f(int target, float u1, float u2, int stride, int order, /*IN*/ float  [] points){ qfn_1_1_glMap1f(nativehandle, target, u1, u2, stride, order, points); }
        public void glMap1d(int target, double u1, double u2, int stride, int order, /*IN*/ double  [] points){ qfn_1_1_glMap1d(nativehandle, target, u1, u2, stride, order, points); }
        public void glPushAttrib(int mask){ qfn_1_1_glPushAttrib(nativehandle, mask); }
        public void glPopAttrib(){ qfn_1_1_glPopAttrib(nativehandle); }
        public void glAccum(int op, float value){ qfn_1_1_glAccum(nativehandle, op, value); }
        public void glIndexMask(int mask){ qfn_1_1_glIndexMask(nativehandle, mask); }
        public void glClearIndex(float c){ qfn_1_1_glClearIndex(nativehandle, c); }
        public void glClearAccum(float red, float green, float blue, float alpha){ qfn_1_1_glClearAccum(nativehandle, red, green, blue, alpha); }
        public void glPushName(int name){ qfn_1_1_glPushName(nativehandle, name); }
        public void glPopName(){ qfn_1_1_glPopName(nativehandle); }
        public void glPassThrough(float token){ qfn_1_1_glPassThrough(nativehandle, token); }
        public void glLoadName(int name){ qfn_1_1_glLoadName(nativehandle, name); }
        public void glInitNames(){ qfn_1_1_glInitNames(nativehandle); }
        public int glRenderMode(int mode){ return qfn_1_1_glRenderMode(nativehandle, mode); }
        public void glSelectBuffer(int size, int  [] buffer){ qfn_1_1_glSelectBuffer(nativehandle, size, buffer); }
        public void glFeedbackBuffer(int size, int type, float  [] buffer){ qfn_1_1_glFeedbackBuffer(nativehandle, size, type, buffer); }
        public void glTexGeniv(int coord, int pname, /*IN*/ int  [] params){ qfn_1_1_glTexGeniv(nativehandle, coord, pname, params); }
        public void glTexGeni(int coord, int pname, int param){ qfn_1_1_glTexGeni(nativehandle, coord, pname, param); }
        public void glTexGenfv(int coord, int pname, /*IN*/ float  [] params){ qfn_1_1_glTexGenfv(nativehandle, coord, pname, params); }
        public void glTexGenf(int coord, int pname, float param){ qfn_1_1_glTexGenf(nativehandle, coord, pname, param); }
        public void glTexGendv(int coord, int pname, /*IN*/ double  [] params){ qfn_1_1_glTexGendv(nativehandle, coord, pname, params); }
        public void glTexGend(int coord, int pname, double param){ qfn_1_1_glTexGend(nativehandle, coord, pname, param); }
        public void glTexEnviv(int target, int pname, /*IN*/ int  [] params){ qfn_1_1_glTexEnviv(nativehandle, target, pname, params); }
        public void glTexEnvi(int target, int pname, int param){ qfn_1_1_glTexEnvi(nativehandle, target, pname, param); }
        public void glTexEnvfv(int target, int pname, /*IN*/ float  [] params){ qfn_1_1_glTexEnvfv(nativehandle, target, pname, params); }
        public void glTexEnvf(int target, int pname, float param){ qfn_1_1_glTexEnvf(nativehandle, target, pname, param); }
        public void glShadeModel(int mode){ qfn_1_1_glShadeModel(nativehandle, mode); }
        public void glPolygonStipple(/*IN*/ byte  [] mask){ qfn_1_1_glPolygonStipple(nativehandle, mask); }
        public void glMaterialiv(int face, int pname, /*IN*/ int  [] params){ qfn_1_1_glMaterialiv(nativehandle, face, pname, params); }
        public void glMateriali(int face, int pname, int param){ qfn_1_1_glMateriali(nativehandle, face, pname, param); }
        public void glMaterialfv(int face, int pname, /*IN*/ float  [] params){ qfn_1_1_glMaterialfv(nativehandle, face, pname, params); }
        public void glMaterialf(int face, int pname, float param){ qfn_1_1_glMaterialf(nativehandle, face, pname, param); }
        public void glLineStipple(int factor, short pattern){ qfn_1_1_glLineStipple(nativehandle, factor, pattern); }
        public void glLightModeliv(int pname, /*IN*/ int  [] params){ qfn_1_1_glLightModeliv(nativehandle, pname, params); }
        public void glLightModeli(int pname, int param){ qfn_1_1_glLightModeli(nativehandle, pname, param); }
        public void glLightModelfv(int pname, /*IN*/ float  [] params){ qfn_1_1_glLightModelfv(nativehandle, pname, params); }
        public void glLightModelf(int pname, float param){ qfn_1_1_glLightModelf(nativehandle, pname, param); }
        public void glLightiv(int light, int pname, /*IN*/ int  [] params){ qfn_1_1_glLightiv(nativehandle, light, pname, params); }
        public void glLighti(int light, int pname, int param){ qfn_1_1_glLighti(nativehandle, light, pname, param); }
        public void glLightfv(int light, int pname, /*IN*/ float  [] params){ qfn_1_1_glLightfv(nativehandle, light, pname, params); }
        public void glLightf(int light, int pname, float param){ qfn_1_1_glLightf(nativehandle, light, pname, param); }
        public void glFogiv(int pname, /*IN*/ int  [] params){ qfn_1_1_glFogiv(nativehandle, pname, params); }
        public void glFogi(int pname, int param){ qfn_1_1_glFogi(nativehandle, pname, param); }
        public void glFogfv(int pname, /*IN*/ float  [] params){ qfn_1_1_glFogfv(nativehandle, pname, params); }
        public void glFogf(int pname, float param){ qfn_1_1_glFogf(nativehandle, pname, param); }
        public void glColorMaterial(int face, int mode){ qfn_1_1_glColorMaterial(nativehandle, face, mode); }
        public void glClipPlane(int plane, /*IN*/ double  [] equation){ qfn_1_1_glClipPlane(nativehandle, plane, equation); }
        public void glVertex4sv(/*IN*/ short  [] v){ qfn_1_1_glVertex4sv(nativehandle, v); }
        public void glVertex4s(short x, short y, short z, short w){ qfn_1_1_glVertex4s(nativehandle, x, y, z, w); }
        public void glVertex4iv(/*IN*/ int  [] v){ qfn_1_1_glVertex4iv(nativehandle, v); }
        public void glVertex4i(int x, int y, int z, int w){ qfn_1_1_glVertex4i(nativehandle, x, y, z, w); }
        public void glVertex4fv(/*IN*/ float  [] v){ qfn_1_1_glVertex4fv(nativehandle, v); }
        public void glVertex4f(float x, float y, float z, float w){ qfn_1_1_glVertex4f(nativehandle, x, y, z, w); }
        public void glVertex4dv(/*IN*/ double  [] v){ qfn_1_1_glVertex4dv(nativehandle, v); }
        public void glVertex4d(double x, double y, double z, double w){ qfn_1_1_glVertex4d(nativehandle, x, y, z, w); }
        public void glVertex3sv(/*IN*/ short  [] v){ qfn_1_1_glVertex3sv(nativehandle, v); }
        public void glVertex3s(short x, short y, short z){ qfn_1_1_glVertex3s(nativehandle, x, y, z); }
        public void glVertex3iv(/*IN*/ int  [] v){ qfn_1_1_glVertex3iv(nativehandle, v); }
        public void glVertex3i(int x, int y, int z){ qfn_1_1_glVertex3i(nativehandle, x, y, z); }
        public void glVertex3fv(/*IN*/ float  [] v){ qfn_1_1_glVertex3fv(nativehandle, v); }
        public void glVertex3f(float x, float y, float z){ qfn_1_1_glVertex3f(nativehandle, x, y, z); }
        public void glVertex3dv(/*IN*/ double  [] v){ qfn_1_1_glVertex3dv(nativehandle, v); }
        public void glVertex3d(double x, double y, double z){ qfn_1_1_glVertex3d(nativehandle, x, y, z); }
        public void glVertex2sv(/*IN*/ short  [] v){ qfn_1_1_glVertex2sv(nativehandle, v); }
        public void glVertex2s(short x, short y){ qfn_1_1_glVertex2s(nativehandle, x, y); }
        public void glVertex2iv(/*IN*/ int  [] v){ qfn_1_1_glVertex2iv(nativehandle, v); }
        public void glVertex2i(int x, int y){ qfn_1_1_glVertex2i(nativehandle, x, y); }
        public void glVertex2fv(/*IN*/ float  [] v){ qfn_1_1_glVertex2fv(nativehandle, v); }
        public void glVertex2f(float x, float y){ qfn_1_1_glVertex2f(nativehandle, x, y); }
        public void glVertex2dv(/*IN*/ double  [] v){ qfn_1_1_glVertex2dv(nativehandle, v); }
        public void glVertex2d(double x, double y){ qfn_1_1_glVertex2d(nativehandle, x, y); }
        public void glTexCoord4sv(/*IN*/ short  [] v){ qfn_1_1_glTexCoord4sv(nativehandle, v); }
        public void glTexCoord4s(short s, short t, short r, short q){ qfn_1_1_glTexCoord4s(nativehandle, s, t, r, q); }
        public void glTexCoord4iv(/*IN*/ int  [] v){ qfn_1_1_glTexCoord4iv(nativehandle, v); }
        public void glTexCoord4i(int s, int t, int r, int q){ qfn_1_1_glTexCoord4i(nativehandle, s, t, r, q); }
        public void glTexCoord4fv(/*IN*/ float  [] v){ qfn_1_1_glTexCoord4fv(nativehandle, v); }
        public void glTexCoord4f(float s, float t, float r, float q){ qfn_1_1_glTexCoord4f(nativehandle, s, t, r, q); }
        public void glTexCoord4dv(/*IN*/ double  [] v){ qfn_1_1_glTexCoord4dv(nativehandle, v); }
        public void glTexCoord4d(double s, double t, double r, double q){ qfn_1_1_glTexCoord4d(nativehandle, s, t, r, q); }
        public void glTexCoord3sv(/*IN*/ short  [] v){ qfn_1_1_glTexCoord3sv(nativehandle, v); }
        public void glTexCoord3s(short s, short t, short r){ qfn_1_1_glTexCoord3s(nativehandle, s, t, r); }
        public void glTexCoord3iv(/*IN*/ int  [] v){ qfn_1_1_glTexCoord3iv(nativehandle, v); }
        public void glTexCoord3i(int s, int t, int r){ qfn_1_1_glTexCoord3i(nativehandle, s, t, r); }
        public void glTexCoord3fv(/*IN*/ float  [] v){ qfn_1_1_glTexCoord3fv(nativehandle, v); }
        public void glTexCoord3f(float s, float t, float r){ qfn_1_1_glTexCoord3f(nativehandle, s, t, r); }
        public void glTexCoord3dv(/*IN*/ double  [] v){ qfn_1_1_glTexCoord3dv(nativehandle, v); }
        public void glTexCoord3d(double s, double t, double r){ qfn_1_1_glTexCoord3d(nativehandle, s, t, r); }
        public void glTexCoord2sv(/*IN*/ short  [] v){ qfn_1_1_glTexCoord2sv(nativehandle, v); }
        public void glTexCoord2s(short s, short t){ qfn_1_1_glTexCoord2s(nativehandle, s, t); }
        public void glTexCoord2iv(/*IN*/ int  [] v){ qfn_1_1_glTexCoord2iv(nativehandle, v); }
        public void glTexCoord2i(int s, int t){ qfn_1_1_glTexCoord2i(nativehandle, s, t); }
        public void glTexCoord2fv(/*IN*/ float  [] v){ qfn_1_1_glTexCoord2fv(nativehandle, v); }
        public void glTexCoord2f(float s, float t){ qfn_1_1_glTexCoord2f(nativehandle, s, t); }
        public void glTexCoord2dv(/*IN*/ double  [] v){ qfn_1_1_glTexCoord2dv(nativehandle, v); }
        public void glTexCoord2d(double s, double t){ qfn_1_1_glTexCoord2d(nativehandle, s, t); }
        public void glTexCoord1sv(/*IN*/ short  [] v){ qfn_1_1_glTexCoord1sv(nativehandle, v); }
        public void glTexCoord1s(short s){ qfn_1_1_glTexCoord1s(nativehandle, s); }
        public void glTexCoord1iv(/*IN*/ int  [] v){ qfn_1_1_glTexCoord1iv(nativehandle, v); }
        public void glTexCoord1i(int s){ qfn_1_1_glTexCoord1i(nativehandle, s); }
        public void glTexCoord1fv(/*IN*/ float  [] v){ qfn_1_1_glTexCoord1fv(nativehandle, v); }
        public void glTexCoord1f(float s){ qfn_1_1_glTexCoord1f(nativehandle, s); }
        public void glTexCoord1dv(/*IN*/ double  [] v){ qfn_1_1_glTexCoord1dv(nativehandle, v); }
        public void glTexCoord1d(double s){ qfn_1_1_glTexCoord1d(nativehandle, s); }
        public void glRectsv(/*IN*/ short  [] v1, /*IN*/ short  [] v2){ qfn_1_1_glRectsv(nativehandle, v1, v2); }
        public void glRects(short x1, short y1, short x2, short y2){ qfn_1_1_glRects(nativehandle, x1, y1, x2, y2); }
        public void glRectiv(/*IN*/ int  [] v1, /*IN*/ int  [] v2){ qfn_1_1_glRectiv(nativehandle, v1, v2); }
        public void glRecti(int x1, int y1, int x2, int y2){ qfn_1_1_glRecti(nativehandle, x1, y1, x2, y2); }
        public void glRectfv(/*IN*/ float  [] v1, /*IN*/ float  [] v2){ qfn_1_1_glRectfv(nativehandle, v1, v2); }
        public void glRectf(float x1, float y1, float x2, float y2){ qfn_1_1_glRectf(nativehandle, x1, y1, x2, y2); }
        public void glRectdv(/*IN*/ double  [] v1, /*IN*/ double  [] v2){ qfn_1_1_glRectdv(nativehandle, v1, v2); }
        public void glRectd(double x1, double y1, double x2, double y2){ qfn_1_1_glRectd(nativehandle, x1, y1, x2, y2); }
        public void glRasterPos4sv(/*IN*/ short  [] v){ qfn_1_1_glRasterPos4sv(nativehandle, v); }
        public void glRasterPos4s(short x, short y, short z, short w){ qfn_1_1_glRasterPos4s(nativehandle, x, y, z, w); }
        public void glRasterPos4iv(/*IN*/ int  [] v){ qfn_1_1_glRasterPos4iv(nativehandle, v); }
        public void glRasterPos4i(int x, int y, int z, int w){ qfn_1_1_glRasterPos4i(nativehandle, x, y, z, w); }
        public void glRasterPos4fv(/*IN*/ float  [] v){ qfn_1_1_glRasterPos4fv(nativehandle, v); }
        public void glRasterPos4f(float x, float y, float z, float w){ qfn_1_1_glRasterPos4f(nativehandle, x, y, z, w); }
        public void glRasterPos4dv(/*IN*/ double  [] v){ qfn_1_1_glRasterPos4dv(nativehandle, v); }
        public void glRasterPos4d(double x, double y, double z, double w){ qfn_1_1_glRasterPos4d(nativehandle, x, y, z, w); }
        public void glRasterPos3sv(/*IN*/ short  [] v){ qfn_1_1_glRasterPos3sv(nativehandle, v); }
        public void glRasterPos3s(short x, short y, short z){ qfn_1_1_glRasterPos3s(nativehandle, x, y, z); }
        public void glRasterPos3iv(/*IN*/ int  [] v){ qfn_1_1_glRasterPos3iv(nativehandle, v); }
        public void glRasterPos3i(int x, int y, int z){ qfn_1_1_glRasterPos3i(nativehandle, x, y, z); }
        public void glRasterPos3fv(/*IN*/ float  [] v){ qfn_1_1_glRasterPos3fv(nativehandle, v); }
        public void glRasterPos3f(float x, float y, float z){ qfn_1_1_glRasterPos3f(nativehandle, x, y, z); }
        public void glRasterPos3dv(/*IN*/ double  [] v){ qfn_1_1_glRasterPos3dv(nativehandle, v); }
        public void glRasterPos3d(double x, double y, double z){ qfn_1_1_glRasterPos3d(nativehandle, x, y, z); }
        public void glRasterPos2sv(/*IN*/ short  [] v){ qfn_1_1_glRasterPos2sv(nativehandle, v); }
        public void glRasterPos2s(short x, short y){ qfn_1_1_glRasterPos2s(nativehandle, x, y); }
        public void glRasterPos2iv(/*IN*/ int  [] v){ qfn_1_1_glRasterPos2iv(nativehandle, v); }
        public void glRasterPos2i(int x, int y){ qfn_1_1_glRasterPos2i(nativehandle, x, y); }
        public void glRasterPos2fv(/*IN*/ float  [] v){ qfn_1_1_glRasterPos2fv(nativehandle, v); }
        public void glRasterPos2f(float x, float y){ qfn_1_1_glRasterPos2f(nativehandle, x, y); }
        public void glRasterPos2dv(/*IN*/ double  [] v){ qfn_1_1_glRasterPos2dv(nativehandle, v); }
        public void glRasterPos2d(double x, double y){ qfn_1_1_glRasterPos2d(nativehandle, x, y); }
        public void glNormal3sv(/*IN*/ short  [] v){ qfn_1_1_glNormal3sv(nativehandle, v); }
        public void glNormal3s(short nx, short ny, short nz){ qfn_1_1_glNormal3s(nativehandle, nx, ny, nz); }
        public void glNormal3iv(/*IN*/ int  [] v){ qfn_1_1_glNormal3iv(nativehandle, v); }
        public void glNormal3i(int nx, int ny, int nz){ qfn_1_1_glNormal3i(nativehandle, nx, ny, nz); }
        public void glNormal3fv(/*IN*/ float  [] v){ qfn_1_1_glNormal3fv(nativehandle, v); }
        public void glNormal3f(float nx, float ny, float nz){ qfn_1_1_glNormal3f(nativehandle, nx, ny, nz); }
        public void glNormal3dv(/*IN*/ double  [] v){ qfn_1_1_glNormal3dv(nativehandle, v); }
        public void glNormal3d(double nx, double ny, double nz){ qfn_1_1_glNormal3d(nativehandle, nx, ny, nz); }
        public void glNormal3bv(/*IN*/ byte  [] v){ qfn_1_1_glNormal3bv(nativehandle, v); }
        public void glNormal3b(byte nx, byte ny, byte nz){ qfn_1_1_glNormal3b(nativehandle, nx, ny, nz); }
        public void glIndexsv(/*IN*/ short  [] c){ qfn_1_1_glIndexsv(nativehandle, c); }
        public void glIndexs(short c){ qfn_1_1_glIndexs(nativehandle, c); }
        public void glIndexiv(/*IN*/ int  [] c){ qfn_1_1_glIndexiv(nativehandle, c); }
        public void glIndexi(int c){ qfn_1_1_glIndexi(nativehandle, c); }
        public void glIndexfv(/*IN*/ float  [] c){ qfn_1_1_glIndexfv(nativehandle, c); }
        public void glIndexf(float c){ qfn_1_1_glIndexf(nativehandle, c); }
        public void glIndexdv(/*IN*/ double  [] c){ qfn_1_1_glIndexdv(nativehandle, c); }
        public void glIndexd(double c){ qfn_1_1_glIndexd(nativehandle, c); }
        public void glEnd(){ qfn_1_1_glEnd(nativehandle); }
        public void glEdgeFlagv(/*IN*/ bool  [] flag){ qfn_1_1_glEdgeFlagv(nativehandle, flag); }
        public void glEdgeFlag(bool flag){ qfn_1_1_glEdgeFlag(nativehandle, flag); }
        public void glColor4usv(/*IN*/ short  [] v){ qfn_1_1_glColor4usv(nativehandle, v); }
        public void glColor4us(short red, short green, short blue, short alpha){ qfn_1_1_glColor4us(nativehandle, red, green, blue, alpha); }
        public void glColor4uiv(/*IN*/ int  [] v){ qfn_1_1_glColor4uiv(nativehandle, v); }
        public void glColor4ui(int red, int green, int blue, int alpha){ qfn_1_1_glColor4ui(nativehandle, red, green, blue, alpha); }
        public void glColor4ubv(/*IN*/ byte  [] v){ qfn_1_1_glColor4ubv(nativehandle, v); }
        public void glColor4ub(byte red, byte green, byte blue, byte alpha){ qfn_1_1_glColor4ub(nativehandle, red, green, blue, alpha); }
        public void glColor4sv(/*IN*/ short  [] v){ qfn_1_1_glColor4sv(nativehandle, v); }
        public void glColor4s(short red, short green, short blue, short alpha){ qfn_1_1_glColor4s(nativehandle, red, green, blue, alpha); }
        public void glColor4iv(/*IN*/ int  [] v){ qfn_1_1_glColor4iv(nativehandle, v); }
        public void glColor4i(int red, int green, int blue, int alpha){ qfn_1_1_glColor4i(nativehandle, red, green, blue, alpha); }
        public void glColor4fv(/*IN*/ float  [] v){ qfn_1_1_glColor4fv(nativehandle, v); }
        public void glColor4f(float red, float green, float blue, float alpha){ qfn_1_1_glColor4f(nativehandle, red, green, blue, alpha); }
        public void glColor4dv(/*IN*/ double  [] v){ qfn_1_1_glColor4dv(nativehandle, v); }
        public void glColor4d(double red, double green, double blue, double alpha){ qfn_1_1_glColor4d(nativehandle, red, green, blue, alpha); }
        public void glColor4bv(/*IN*/ byte  [] v){ qfn_1_1_glColor4bv(nativehandle, v); }
        public void glColor4b(byte red, byte green, byte blue, byte alpha){ qfn_1_1_glColor4b(nativehandle, red, green, blue, alpha); }
        public void glColor3usv(/*IN*/ short  [] v){ qfn_1_1_glColor3usv(nativehandle, v); }
        public void glColor3us(short red, short green, short blue){ qfn_1_1_glColor3us(nativehandle, red, green, blue); }
        public void glColor3uiv(/*IN*/ int  [] v){ qfn_1_1_glColor3uiv(nativehandle, v); }
        public void glColor3ui(int red, int green, int blue){ qfn_1_1_glColor3ui(nativehandle, red, green, blue); }
        public void glColor3ubv(/*IN*/ byte  [] v){ qfn_1_1_glColor3ubv(nativehandle, v); }
        public void glColor3ub(byte red, byte green, byte blue){ qfn_1_1_glColor3ub(nativehandle, red, green, blue); }
        public void glColor3sv(/*IN*/ short  [] v){ qfn_1_1_glColor3sv(nativehandle, v); }
        public void glColor3s(short red, short green, short blue){ qfn_1_1_glColor3s(nativehandle, red, green, blue); }
        public void glColor3iv(/*IN*/ int  [] v){ qfn_1_1_glColor3iv(nativehandle, v); }
        public void glColor3i(int red, int green, int blue){ qfn_1_1_glColor3i(nativehandle, red, green, blue); }
        public void glColor3fv(/*IN*/ float  [] v){ qfn_1_1_glColor3fv(nativehandle, v); }
        public void glColor3f(float red, float green, float blue){ qfn_1_1_glColor3f(nativehandle, red, green, blue); }
        public void glColor3dv(/*IN*/ double  [] v){ qfn_1_1_glColor3dv(nativehandle, v); }
        public void glColor3d(double red, double green, double blue){ qfn_1_1_glColor3d(nativehandle, red, green, blue); }
        public void glColor3bv(/*IN*/ byte  [] v){ qfn_1_1_glColor3bv(nativehandle, v); }
        public void glColor3b(byte red, byte green, byte blue){ qfn_1_1_glColor3b(nativehandle, red, green, blue); }
        public void glBitmap(int width, int height, float xorig, float yorig, float xmove, float ymove, /*IN*/ byte  [] bitmap){ qfn_1_1_glBitmap(nativehandle, width, height, xorig, yorig, xmove, ymove, bitmap); }
        public void glBegin(int mode){ qfn_1_1_glBegin(nativehandle, mode); }
        public void glListBase(int base){ qfn_1_1_glListBase(nativehandle, base); }
        public int glGenLists(int range){ return qfn_1_1_glGenLists(nativehandle, range); }
        public void glDeleteLists(int list, int range){ qfn_1_1_glDeleteLists(nativehandle, list, range); }
        public void glCallLists(int n, int type, /*IN*/ byte  [] lists){ qfn_1_1_glCallLists(nativehandle, n, type, lists); }
        public void glCallList(int list){ qfn_1_1_glCallList(nativehandle, list); }
        public void glEndList(){ qfn_1_1_glEndList(nativehandle); }
        public void glNewList(int list, int mode){ qfn_1_1_glNewList(nativehandle, list, mode); }
        public void glPushClientAttrib(int mask){ qfn_1_1_glPushClientAttrib(nativehandle, mask); }
        public void glPopClientAttrib(){ qfn_1_1_glPopClientAttrib(nativehandle); }
        public void glPrioritizeTextures(int n, /*IN*/ int  [] textures, /*IN*/ float  [] priorities){ qfn_1_1_glPrioritizeTextures(nativehandle, n, textures, priorities); }
        public bool glAreTexturesResident(int n, /*IN*/ int  [] textures, bool  [] residences){ return qfn_1_1_glAreTexturesResident(nativehandle, n, textures, residences); }
        public void glVertexPointer(int size, int type, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glVertexPointer(nativehandle, size, type, stride, pointer); }
        public void glTexCoordPointer(int size, int type, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glTexCoordPointer(nativehandle, size, type, stride, pointer); }
        public void glNormalPointer(int type, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glNormalPointer(nativehandle, type, stride, pointer); }
        public void interleavedArrays(int format, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glInterleavedArrays(nativehandle, format, stride, pointer); }
        public void glIndexPointer(int type, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glIndexPointer(nativehandle, type, stride, pointer); }
        public void glEnableClientState(int array){ qfn_1_1_glEnableClientState(nativehandle, array); }
        public void glEdgeFlagPointer(int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glEdgeFlagPointer(nativehandle, stride, pointer); }
        public void glDisableClientState(int array){ qfn_1_1_glDisableClientState(nativehandle, array); }
        public void glColorPointer(int size, int type, int stride, /*IN*/ byte  [] pointer){ qfn_1_1_glColorPointer(nativehandle, size, type, stride, pointer); }
        public void glArrayElement(int i){ qfn_1_1_glArrayElement(nativehandle, i); }
        
        
        public import "libQXLibrary"{
            void cdecl qfn_1_1_glViewport(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_1_1_glDepthRange(long nativehandle, double nearVal, double farVal) ;
            bool cdecl qfn_1_1_glIsEnabled(long nativehandle, int cap) ;
            void cdecl qfn_1_1_glGetTexLevelParameteriv(long nativehandle, int target, int level, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetTexLevelParameterfv(long nativehandle, int target, int level, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetTexParameteriv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetTexParameterfv(long nativehandle, int target, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetTexImage(long nativehandle, int target, int level, int format, int type, byte  * pixels) ;
            String cdecl qfn_1_1_glGetString(long nativehandle, int name) ;
            void cdecl qfn_1_1_glGetIntegerv(long nativehandle, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetFloatv(long nativehandle, int pname, float  * params) ;
            int cdecl qfn_1_1_glGetError(long nativehandle) ;
            void cdecl qfn_1_1_glGetDoublev(long nativehandle, int pname, double  * params) ;
            void cdecl qfn_1_1_glGetBooleanv(long nativehandle, int pname, bool  * params) ;
            void cdecl qfn_1_1_glReadPixels(long nativehandle, int x, int y, int width, int height, int format, int type, byte  * pixels) ;
            void cdecl qfn_1_1_glReadBuffer(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glPixelStorei(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_1_glPixelStoref(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_1_glDepthFunc(long nativehandle, int func) ;
            void cdecl qfn_1_1_glStencilOp(long nativehandle, int fail, int zfail, int zpass) ;
            void cdecl qfn_1_1_glStencilFunc(long nativehandle, int func, int ref, int mask) ;
            void cdecl qfn_1_1_glLogicOp(long nativehandle, int opcode) ;
            void cdecl qfn_1_1_glBlendFunc(long nativehandle, int sfactor, int dfactor) ;
            void cdecl qfn_1_1_glFlush(long nativehandle) ;
            void cdecl qfn_1_1_glFinish(long nativehandle) ;
            void cdecl qfn_1_1_glEnable(long nativehandle, int cap) ;
            void cdecl qfn_1_1_glDisable(long nativehandle, int cap) ;
            void cdecl qfn_1_1_glDepthMask(long nativehandle, bool flag) ;
            void cdecl qfn_1_1_glColorMask(long nativehandle, bool red, bool green, bool blue, bool alpha) ;
            void cdecl qfn_1_1_glStencilMask(long nativehandle, int mask) ;
            void cdecl qfn_1_1_glClearDepth(long nativehandle, double depth) ;
            void cdecl qfn_1_1_glClearStencil(long nativehandle, int s) ;
            void cdecl qfn_1_1_glClearColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_1_glClear(long nativehandle, int mask) ;
            void cdecl qfn_1_1_glDrawBuffer(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, /*IN*/ byte  * pixels) ;
            void cdecl qfn_1_1_glTexImage1D(long nativehandle, int target, int level, int internalformat, int width, int border, int format, int type, /*IN*/ byte  * pixels) ;
            void cdecl qfn_1_1_glTexParameteriv(long nativehandle, int target, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glTexParameteri(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_1_1_glTexParameterfv(long nativehandle, int target, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glTexParameterf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_1_1_glScissor(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_1_1_glPolygonMode(long nativehandle, int face, int mode) ;
            void cdecl qfn_1_1_glPointSize(long nativehandle, float size) ;
            void cdecl qfn_1_1_glLineWidth(long nativehandle, float width) ;
            void cdecl qfn_1_1_glHint(long nativehandle, int target, int mode) ;
            void cdecl qfn_1_1_glFrontFace(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glCullFace(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glIndexubv(long nativehandle, /*IN*/ byte  * c) ;
            void cdecl qfn_1_1_glIndexub(long nativehandle, byte c) ;
            bool cdecl qfn_1_1_glIsTexture(long nativehandle, int texture) ;
            void cdecl qfn_1_1_glGenTextures(long nativehandle, int n, int  * textures) ;
            void cdecl qfn_1_1_glDeleteTextures(long nativehandle, int n, /*IN*/ int  * textures) ;
            void cdecl qfn_1_1_glBindTexture(long nativehandle, int target, int texture) ;
            void cdecl qfn_1_1_glTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, /*IN*/ byte  * pixels) ;
            void cdecl qfn_1_1_glTexSubImage1D(long nativehandle, int target, int level, int xoffset, int width, int format, int type, /*IN*/ byte  * pixels) ;
            void cdecl qfn_1_1_glCopyTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) ;
            void cdecl qfn_1_1_glCopyTexSubImage1D(long nativehandle, int target, int level, int xoffset, int x, int y, int width) ;
            void cdecl qfn_1_1_glCopyTexImage2D(long nativehandle, int target, int level, int internalformat, int x, int y, int width, int height, int border) ;
            void cdecl qfn_1_1_glCopyTexImage1D(long nativehandle, int target, int level, int internalformat, int x, int y, int width, int border) ;
            void cdecl qfn_1_1_glPolygonOffset(long nativehandle, float factor, float units) ;
            void cdecl qfn_1_1_glGetPointerv(long nativehandle, int pname, ObjectPtr params) ;
            void cdecl qfn_1_1_glDrawElements(long nativehandle, int mode, int count, int type, /*IN*/ byte  * indices) ;
            void cdecl qfn_1_1_glDrawArrays(long nativehandle, int mode, int first, int count) ;
            void cdecl qfn_1_1_glTranslatef(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_1_glTranslated(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_1_glScalef(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_1_glScaled(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_1_glRotatef(long nativehandle, float angle, float x, float y, float z) ;
            void cdecl qfn_1_1_glRotated(long nativehandle, double angle, double x, double y, double z) ;
            void cdecl qfn_1_1_glPushMatrix(long nativehandle) ;
            void cdecl qfn_1_1_glPopMatrix(long nativehandle) ;
            void cdecl qfn_1_1_glOrtho(long nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) ;
            void cdecl qfn_1_1_glMultMatrixd(long nativehandle, /*IN*/ double  * m) ;
            void cdecl qfn_1_1_glMultMatrixf(long nativehandle, /*IN*/ float  * m) ;
            void cdecl qfn_1_1_glMatrixMode(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glLoadMatrixd(long nativehandle, /*IN*/ double  * m) ;
            void cdecl qfn_1_1_glLoadMatrixf(long nativehandle, /*IN*/ float  * m) ;
            void cdecl qfn_1_1_glLoadIdentity(long nativehandle) ;
            void cdecl qfn_1_1_glFrustum(long nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) ;
            bool cdecl qfn_1_1_glIsList(long nativehandle, int list) ;
            void cdecl qfn_1_1_glGetTexGeniv(long nativehandle, int coord, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetTexGenfv(long nativehandle, int coord, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetTexGendv(long nativehandle, int coord, int pname, double  * params) ;
            void cdecl qfn_1_1_glGetTexEnviv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetTexEnvfv(long nativehandle, int target, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetPolygonStipple(long nativehandle, byte  * mask) ;
            void cdecl qfn_1_1_glGetPixelMapusv(long nativehandle, int map, short  * values) ;
            void cdecl qfn_1_1_glGetPixelMapuiv(long nativehandle, int map, int  * values) ;
            void cdecl qfn_1_1_glGetPixelMapfv(long nativehandle, int map, float  * values) ;
            void cdecl qfn_1_1_glGetMaterialiv(long nativehandle, int face, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetMaterialfv(long nativehandle, int face, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetMapiv(long nativehandle, int target, int query, int  * v) ;
            void cdecl qfn_1_1_glGetMapfv(long nativehandle, int target, int query, float  * v) ;
            void cdecl qfn_1_1_glGetMapdv(long nativehandle, int target, int query, double  * v) ;
            void cdecl qfn_1_1_glGetLightiv(long nativehandle, int light, int pname, int  * params) ;
            void cdecl qfn_1_1_glGetLightfv(long nativehandle, int light, int pname, float  * params) ;
            void cdecl qfn_1_1_glGetClipPlane(long nativehandle, int plane, double  * equation) ;
            void cdecl qfn_1_1_glDrawPixels(long nativehandle, int width, int height, int format, int type, /*IN*/ byte  * pixels) ;
            void cdecl qfn_1_1_glCopyPixels(long nativehandle, int x, int y, int width, int height, int type) ;
            void cdecl qfn_1_1_glPixelMapusv(long nativehandle, int map, int mapsize, /*IN*/ short  * values) ;
            void cdecl qfn_1_1_glPixelMapuiv(long nativehandle, int map, int mapsize, /*IN*/ int  * values) ;
            void cdecl qfn_1_1_glPixelMapfv(long nativehandle, int map, int mapsize, /*IN*/ float  * values) ;
            void cdecl qfn_1_1_glPixelTransferi(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_1_glPixelTransferf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_1_glPixelZoom(long nativehandle, float xfactor, float yfactor) ;
            void cdecl qfn_1_1_glAlphaFunc(long nativehandle, int func, float ref) ;
            void cdecl qfn_1_1_glEvalPoint2(long nativehandle, int i, int j) ;
            void cdecl qfn_1_1_glEvalMesh2(long nativehandle, int mode, int i1, int i2, int j1, int j2) ;
            void cdecl qfn_1_1_glEvalPoint1(long nativehandle, int i) ;
            void cdecl qfn_1_1_glEvalMesh1(long nativehandle, int mode, int i1, int i2) ;
            void cdecl qfn_1_1_glEvalCoord2fv(long nativehandle, /*IN*/ float  * u) ;
            void cdecl qfn_1_1_glEvalCoord2f(long nativehandle, float u, float v) ;
            void cdecl qfn_1_1_glEvalCoord2dv(long nativehandle, /*IN*/ double  * u) ;
            void cdecl qfn_1_1_glEvalCoord2d(long nativehandle, double u, double v) ;
            void cdecl qfn_1_1_glEvalCoord1fv(long nativehandle, /*IN*/ float  * u) ;
            void cdecl qfn_1_1_glEvalCoord1f(long nativehandle, float u) ;
            void cdecl qfn_1_1_glEvalCoord1dv(long nativehandle, /*IN*/ double  * u) ;
            void cdecl qfn_1_1_glEvalCoord1d(long nativehandle, double u) ;
            void cdecl qfn_1_1_glMapGrid2f(long nativehandle, int un, float u1, float u2, int vn, float v1, float v2) ;
            void cdecl qfn_1_1_glMapGrid2d(long nativehandle, int un, double u1, double u2, int vn, double v1, double v2) ;
            void cdecl qfn_1_1_glMapGrid1f(long nativehandle, int un, float u1, float u2) ;
            void cdecl qfn_1_1_glMapGrid1d(long nativehandle, int un, double u1, double u2) ;
            void cdecl qfn_1_1_glMap2f(long nativehandle, int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, /*IN*/ float  * points) ;
            void cdecl qfn_1_1_glMap2d(long nativehandle, int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, /*IN*/ double  * points) ;
            void cdecl qfn_1_1_glMap1f(long nativehandle, int target, float u1, float u2, int stride, int order, /*IN*/ float  * points) ;
            void cdecl qfn_1_1_glMap1d(long nativehandle, int target, double u1, double u2, int stride, int order, /*IN*/ double  * points) ;
            void cdecl qfn_1_1_glPushAttrib(long nativehandle, int mask) ;
            void cdecl qfn_1_1_glPopAttrib(long nativehandle) ;
            void cdecl qfn_1_1_glAccum(long nativehandle, int op, float value) ;
            void cdecl qfn_1_1_glIndexMask(long nativehandle, int mask) ;
            void cdecl qfn_1_1_glClearIndex(long nativehandle, float c) ;
            void cdecl qfn_1_1_glClearAccum(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_1_glPushName(long nativehandle, int name) ;
            void cdecl qfn_1_1_glPopName(long nativehandle) ;
            void cdecl qfn_1_1_glPassThrough(long nativehandle, float token) ;
            void cdecl qfn_1_1_glLoadName(long nativehandle, int name) ;
            void cdecl qfn_1_1_glInitNames(long nativehandle) ;
            int cdecl qfn_1_1_glRenderMode(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glSelectBuffer(long nativehandle, int size, int  * buffer) ;
            void cdecl qfn_1_1_glFeedbackBuffer(long nativehandle, int size, int type, float  * buffer) ;
            void cdecl qfn_1_1_glTexGeniv(long nativehandle, int coord, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glTexGeni(long nativehandle, int coord, int pname, int param) ;
            void cdecl qfn_1_1_glTexGenfv(long nativehandle, int coord, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glTexGenf(long nativehandle, int coord, int pname, float param) ;
            void cdecl qfn_1_1_glTexGendv(long nativehandle, int coord, int pname, /*IN*/ double  * params) ;
            void cdecl qfn_1_1_glTexGend(long nativehandle, int coord, int pname, double param) ;
            void cdecl qfn_1_1_glTexEnviv(long nativehandle, int target, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glTexEnvi(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_1_1_glTexEnvfv(long nativehandle, int target, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glTexEnvf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_1_1_glShadeModel(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glPolygonStipple(long nativehandle, /*IN*/ byte  * mask) ;
            void cdecl qfn_1_1_glMaterialiv(long nativehandle, int face, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glMateriali(long nativehandle, int face, int pname, int param) ;
            void cdecl qfn_1_1_glMaterialfv(long nativehandle, int face, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glMaterialf(long nativehandle, int face, int pname, float param) ;
            void cdecl qfn_1_1_glLineStipple(long nativehandle, int factor, short pattern) ;
            void cdecl qfn_1_1_glLightModeliv(long nativehandle, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glLightModeli(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_1_glLightModelfv(long nativehandle, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glLightModelf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_1_glLightiv(long nativehandle, int light, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glLighti(long nativehandle, int light, int pname, int param) ;
            void cdecl qfn_1_1_glLightfv(long nativehandle, int light, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glLightf(long nativehandle, int light, int pname, float param) ;
            void cdecl qfn_1_1_glFogiv(long nativehandle, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_1_glFogi(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_1_glFogfv(long nativehandle, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_1_glFogf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_1_glColorMaterial(long nativehandle, int face, int mode) ;
            void cdecl qfn_1_1_glClipPlane(long nativehandle, int plane, /*IN*/ double  * equation) ;
            void cdecl qfn_1_1_glVertex4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glVertex4s(long nativehandle, short x, short y, short z, short w) ;
            void cdecl qfn_1_1_glVertex4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glVertex4i(long nativehandle, int x, int y, int z, int w) ;
            void cdecl qfn_1_1_glVertex4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glVertex4f(long nativehandle, float x, float y, float z, float w) ;
            void cdecl qfn_1_1_glVertex4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glVertex4d(long nativehandle, double x, double y, double z, double w) ;
            void cdecl qfn_1_1_glVertex3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glVertex3s(long nativehandle, short x, short y, short z) ;
            void cdecl qfn_1_1_glVertex3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glVertex3i(long nativehandle, int x, int y, int z) ;
            void cdecl qfn_1_1_glVertex3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glVertex3f(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_1_glVertex3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glVertex3d(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_1_glVertex2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glVertex2s(long nativehandle, short x, short y) ;
            void cdecl qfn_1_1_glVertex2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glVertex2i(long nativehandle, int x, int y) ;
            void cdecl qfn_1_1_glVertex2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glVertex2f(long nativehandle, float x, float y) ;
            void cdecl qfn_1_1_glVertex2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glVertex2d(long nativehandle, double x, double y) ;
            void cdecl qfn_1_1_glTexCoord4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glTexCoord4s(long nativehandle, short s, short t, short r, short q) ;
            void cdecl qfn_1_1_glTexCoord4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glTexCoord4i(long nativehandle, int s, int t, int r, int q) ;
            void cdecl qfn_1_1_glTexCoord4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glTexCoord4f(long nativehandle, float s, float t, float r, float q) ;
            void cdecl qfn_1_1_glTexCoord4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glTexCoord4d(long nativehandle, double s, double t, double r, double q) ;
            void cdecl qfn_1_1_glTexCoord3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glTexCoord3s(long nativehandle, short s, short t, short r) ;
            void cdecl qfn_1_1_glTexCoord3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glTexCoord3i(long nativehandle, int s, int t, int r) ;
            void cdecl qfn_1_1_glTexCoord3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glTexCoord3f(long nativehandle, float s, float t, float r) ;
            void cdecl qfn_1_1_glTexCoord3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glTexCoord3d(long nativehandle, double s, double t, double r) ;
            void cdecl qfn_1_1_glTexCoord2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glTexCoord2s(long nativehandle, short s, short t) ;
            void cdecl qfn_1_1_glTexCoord2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glTexCoord2i(long nativehandle, int s, int t) ;
            void cdecl qfn_1_1_glTexCoord2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glTexCoord2f(long nativehandle, float s, float t) ;
            void cdecl qfn_1_1_glTexCoord2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glTexCoord2d(long nativehandle, double s, double t) ;
            void cdecl qfn_1_1_glTexCoord1sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glTexCoord1s(long nativehandle, short s) ;
            void cdecl qfn_1_1_glTexCoord1iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glTexCoord1i(long nativehandle, int s) ;
            void cdecl qfn_1_1_glTexCoord1fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glTexCoord1f(long nativehandle, float s) ;
            void cdecl qfn_1_1_glTexCoord1dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glTexCoord1d(long nativehandle, double s) ;
            void cdecl qfn_1_1_glRectsv(long nativehandle, /*IN*/ short  * v1, /*IN*/ short  * v2) ;
            void cdecl qfn_1_1_glRects(long nativehandle, short x1, short y1, short x2, short y2) ;
            void cdecl qfn_1_1_glRectiv(long nativehandle, /*IN*/ int  * v1, /*IN*/ int  * v2) ;
            void cdecl qfn_1_1_glRecti(long nativehandle, int x1, int y1, int x2, int y2) ;
            void cdecl qfn_1_1_glRectfv(long nativehandle, /*IN*/ float  * v1, /*IN*/ float  * v2) ;
            void cdecl qfn_1_1_glRectf(long nativehandle, float x1, float y1, float x2, float y2) ;
            void cdecl qfn_1_1_glRectdv(long nativehandle, /*IN*/ double  * v1, /*IN*/ double  * v2) ;
            void cdecl qfn_1_1_glRectd(long nativehandle, double x1, double y1, double x2, double y2) ;
            void cdecl qfn_1_1_glRasterPos4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glRasterPos4s(long nativehandle, short x, short y, short z, short w) ;
            void cdecl qfn_1_1_glRasterPos4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glRasterPos4i(long nativehandle, int x, int y, int z, int w) ;
            void cdecl qfn_1_1_glRasterPos4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glRasterPos4f(long nativehandle, float x, float y, float z, float w) ;
            void cdecl qfn_1_1_glRasterPos4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glRasterPos4d(long nativehandle, double x, double y, double z, double w) ;
            void cdecl qfn_1_1_glRasterPos3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glRasterPos3s(long nativehandle, short x, short y, short z) ;
            void cdecl qfn_1_1_glRasterPos3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glRasterPos3i(long nativehandle, int x, int y, int z) ;
            void cdecl qfn_1_1_glRasterPos3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glRasterPos3f(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_1_glRasterPos3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glRasterPos3d(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_1_glRasterPos2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glRasterPos2s(long nativehandle, short x, short y) ;
            void cdecl qfn_1_1_glRasterPos2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glRasterPos2i(long nativehandle, int x, int y) ;
            void cdecl qfn_1_1_glRasterPos2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glRasterPos2f(long nativehandle, float x, float y) ;
            void cdecl qfn_1_1_glRasterPos2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glRasterPos2d(long nativehandle, double x, double y) ;
            void cdecl qfn_1_1_glNormal3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glNormal3s(long nativehandle, short nx, short ny, short nz) ;
            void cdecl qfn_1_1_glNormal3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glNormal3i(long nativehandle, int nx, int ny, int nz) ;
            void cdecl qfn_1_1_glNormal3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glNormal3f(long nativehandle, float nx, float ny, float nz) ;
            void cdecl qfn_1_1_glNormal3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glNormal3d(long nativehandle, double nx, double ny, double nz) ;
            void cdecl qfn_1_1_glNormal3bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_1_glNormal3b(long nativehandle, byte nx, byte ny, byte nz) ;
            void cdecl qfn_1_1_glIndexsv(long nativehandle, /*IN*/ short  * c) ;
            void cdecl qfn_1_1_glIndexs(long nativehandle, short c) ;
            void cdecl qfn_1_1_glIndexiv(long nativehandle, /*IN*/ int  * c) ;
            void cdecl qfn_1_1_glIndexi(long nativehandle, int c) ;
            void cdecl qfn_1_1_glIndexfv(long nativehandle, /*IN*/ float  * c) ;
            void cdecl qfn_1_1_glIndexf(long nativehandle, float c) ;
            void cdecl qfn_1_1_glIndexdv(long nativehandle, /*IN*/ double  * c) ;
            void cdecl qfn_1_1_glIndexd(long nativehandle, double c) ;
            void cdecl qfn_1_1_glEnd(long nativehandle) ;
            void cdecl qfn_1_1_glEdgeFlagv(long nativehandle, /*IN*/ bool  * flag) ;
            void cdecl qfn_1_1_glEdgeFlag(long nativehandle, bool flag) ;
            void cdecl qfn_1_1_glColor4usv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glColor4us(long nativehandle, short red, short green, short blue, short alpha) ;
            void cdecl qfn_1_1_glColor4uiv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glColor4ui(long nativehandle, int red, int green, int blue, int alpha) ;
            void cdecl qfn_1_1_glColor4ubv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_1_glColor4ub(long nativehandle, byte red, byte green, byte blue, byte alpha) ;
            void cdecl qfn_1_1_glColor4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glColor4s(long nativehandle, short red, short green, short blue, short alpha) ;
            void cdecl qfn_1_1_glColor4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glColor4i(long nativehandle, int red, int green, int blue, int alpha) ;
            void cdecl qfn_1_1_glColor4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glColor4f(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_1_glColor4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glColor4d(long nativehandle, double red, double green, double blue, double alpha) ;
            void cdecl qfn_1_1_glColor4bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_1_glColor4b(long nativehandle, byte red, byte green, byte blue, byte alpha) ;
            void cdecl qfn_1_1_glColor3usv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glColor3us(long nativehandle, short red, short green, short blue) ;
            void cdecl qfn_1_1_glColor3uiv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glColor3ui(long nativehandle, int red, int green, int blue) ;
            void cdecl qfn_1_1_glColor3ubv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_1_glColor3ub(long nativehandle, byte red, byte green, byte blue) ;
            void cdecl qfn_1_1_glColor3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_1_glColor3s(long nativehandle, short red, short green, short blue) ;
            void cdecl qfn_1_1_glColor3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_1_glColor3i(long nativehandle, int red, int green, int blue) ;
            void cdecl qfn_1_1_glColor3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_1_glColor3f(long nativehandle, float red, float green, float blue) ;
            void cdecl qfn_1_1_glColor3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_1_glColor3d(long nativehandle, double red, double green, double blue) ;
            void cdecl qfn_1_1_glColor3bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_1_glColor3b(long nativehandle, byte red, byte green, byte blue) ;
            void cdecl qfn_1_1_glBitmap(long nativehandle, int width, int height, float xorig, float yorig, float xmove, float ymove, /*IN*/ byte  * bitmap) ;
            void cdecl qfn_1_1_glBegin(long nativehandle, int mode) ;
            void cdecl qfn_1_1_glListBase(long nativehandle, int base) ;
            int cdecl qfn_1_1_glGenLists(long nativehandle, int range) ;
            void cdecl qfn_1_1_glDeleteLists(long nativehandle, int list, int range) ;
            void cdecl qfn_1_1_glCallLists(long nativehandle, int n, int type, /*IN*/ byte  * lists) ;
            void cdecl qfn_1_1_glCallList(long nativehandle, int list) ;
            void cdecl qfn_1_1_glEndList(long nativehandle) ;
            void cdecl qfn_1_1_glNewList(long nativehandle, int list, int mode) ;
            void cdecl qfn_1_1_glPushClientAttrib(long nativehandle, int mask) ;
            void cdecl qfn_1_1_glPopClientAttrib(long nativehandle) ;
            void cdecl qfn_1_1_glPrioritizeTextures(long nativehandle, int n, /*IN*/ int  * textures, /*IN*/ float  * priorities) ;
            bool cdecl qfn_1_1_glAreTexturesResident(long nativehandle, int n, /*IN*/ int  * textures, bool  * residences) ;
            void cdecl qfn_1_1_glVertexPointer(long nativehandle, int size, int type, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glTexCoordPointer(long nativehandle, int size, int type, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glNormalPointer(long nativehandle, int type, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glInterleavedArrays(long nativehandle, int format, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glIndexPointer(long nativehandle, int type, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glEnableClientState(long nativehandle, int array) ;
            void cdecl qfn_1_1_glEdgeFlagPointer(long nativehandle, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glDisableClientState(long nativehandle, int array) ;
            void cdecl qfn_1_1_glColorPointer(long nativehandle, int size, int type, int stride, /*IN*/ byte  * pointer) ;
            void cdecl qfn_1_1_glArrayElement(long nativehandle, int i) ;
        };
    };
};