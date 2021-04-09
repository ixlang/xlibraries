//xlang Source, Name:qt5/widgets/QOpenGLFunctions_1_0.x 
//Date: Tue Mar 21:31:32 2021 

package Qt{
    public class QOpenGLFunctions_1_0 : QAbstractOpenGLFunctions{
        public QOpenGLFunctions_1_0(){
            
        }
        public QOpenGLFunctions_1_0(long h){
            super(h);
        }
        
        public bool initializeOpenGLFunctions() {
            return QtXnl.widget_get_bool_value(nativehandle,  Constant.QOPENGLFUNCTIONS_1_0_INITIALIZEOPENGLFUNCTIONS);
        }
        // OpenGL 1.0 core functions
        public void glViewport(int x, int y, int width, int height){ qfn_1_0_glViewport(nativehandle, x, y, width, height); }
        public void glDepthRange(double nearVal, double farVal){ qfn_1_0_glDepthRange(nativehandle, nearVal, farVal); }
        public bool glIsEnabled(int cap){ return qfn_1_0_glIsEnabled(nativehandle, cap); }
        public void glGetTexLevelParameteriv(int target, int level, int pname, int  [] params){ qfn_1_0_glGetTexLevelParameteriv(nativehandle, target, level, pname, params); }
        public void glGetTexLevelParameterfv(int target, int level, int pname, float  [] params){ qfn_1_0_glGetTexLevelParameterfv(nativehandle, target, level, pname, params); }
        public void glGetTexParameteriv(int target, int pname, int  [] params){ qfn_1_0_glGetTexParameteriv(nativehandle, target, pname, params); }
        public void glGetTexParameterfv(int target, int pname, float  [] params){ qfn_1_0_glGetTexParameterfv(nativehandle, target, pname, params); }
        public void glGetTexImage(int target, int level, int format, int type, Object pixels){ qfn_1_0_glGetTexImage(nativehandle, target, level, format, type, pixels); }
        public String glGetString(int name){ return qfn_1_0_glGetString(nativehandle, name); }
        public void glGetIntegerv(int pname, int  [] params){ qfn_1_0_glGetIntegerv(nativehandle, pname, params); }
        public void glGetFloatv(int pname, float  [] params){ qfn_1_0_glGetFloatv(nativehandle, pname, params); }
        public int glGetError(){ return qfn_1_0_glGetError(nativehandle); }
        public void glGetDoublev(int pname, double  [] params){ qfn_1_0_glGetDoublev(nativehandle, pname, params); }
        public void glGetBooleanv(int pname, bool  [] params){ qfn_1_0_glGetBooleanv(nativehandle, pname, params); }
        public void glReadPixels(int x, int y, int width, int height, int format, int type, Object pixels){ qfn_1_0_glReadPixels(nativehandle, x, y, width, height, format, type, pixels); }
        public void glReadBuffer(int mode){ qfn_1_0_glReadBuffer(nativehandle, mode); }
        public void glPixelStorei(int pname, int param){ qfn_1_0_glPixelStorei(nativehandle, pname, param); }
        public void glPixelStoref(int pname, float param){ qfn_1_0_glPixelStoref(nativehandle, pname, param); }
        public void glDepthFunc(int func){ qfn_1_0_glDepthFunc(nativehandle, func); }
        public void glStencilOp(int fail, int zfail, int zpass){ qfn_1_0_glStencilOp(nativehandle, fail, zfail, zpass); }
        public void glStencilFunc(int func, int ref, int mask){ qfn_1_0_glStencilFunc(nativehandle, func, ref, mask); }
        public void glLogicOp(int opcode){ qfn_1_0_glLogicOp(nativehandle, opcode); }
        public void glBlendFunc(int sfactor, int dfactor){ qfn_1_0_glBlendFunc(nativehandle, sfactor, dfactor); }
        public void glFlush(){ qfn_1_0_glFlush(nativehandle); }
        public void glFinish(){ qfn_1_0_glFinish(nativehandle); }
        public void glEnable(int cap){ qfn_1_0_glEnable(nativehandle, cap); }
        public void glDisable(int cap){ qfn_1_0_glDisable(nativehandle, cap); }
        public void glDepthMask(bool flag){ qfn_1_0_glDepthMask(nativehandle, flag); }
        public void glColorMask(bool red, bool green, bool blue, bool alpha){ qfn_1_0_glColorMask(nativehandle, red, green, blue, alpha); }
        public void glStencilMask(int mask){ qfn_1_0_glStencilMask(nativehandle, mask); }
        public void glClearDepth(double depth){ qfn_1_0_glClearDepth(nativehandle, depth); }
        public void glClearStencil(int s){ qfn_1_0_glClearStencil(nativehandle, s); }
        public void glClearColor(float red, float green, float blue, float alpha){ qfn_1_0_glClearColor(nativehandle, red, green, blue, alpha); }
        public void glClear(int mask){ qfn_1_0_glClear(nativehandle, mask); }
        public void glDrawBuffer(int mode){ qfn_1_0_glDrawBuffer(nativehandle, mode); }
        public void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type,  Object pixels){ qfn_1_0_glTexImage2D(nativehandle, target, level, internalformat, width, height, border, format, type, pixels); }
        public void glTexImage1D(int target, int level, int internalformat, int width, int border, int format, int type,  Object pixels){ qfn_1_0_glTexImage1D(nativehandle, target, level, internalformat, width, border, format, type, pixels); }
        public void glTexParameteriv(int target, int pname,  int  [] params){ qfn_1_0_glTexParameteriv(nativehandle, target, pname, params); }
        public void glTexParameteri(int target, int pname, int param){ qfn_1_0_glTexParameteri(nativehandle, target, pname, param); }
        public void glTexParameterfv(int target, int pname,  float  [] params){ qfn_1_0_glTexParameterfv(nativehandle, target, pname, params); }
        public void glTexParameterf(int target, int pname, float param){ qfn_1_0_glTexParameterf(nativehandle, target, pname, param); }
        public void glScissor(int x, int y, int width, int height){ qfn_1_0_glScissor(nativehandle, x, y, width, height); }
        public void glPolygonMode(int face, int mode){ qfn_1_0_glPolygonMode(nativehandle, face, mode); }
        public void glPointSize(float size){ qfn_1_0_glPointSize(nativehandle, size); }
        public void glLineWidth(float width){ qfn_1_0_glLineWidth(nativehandle, width); }
        public void glHint(int target, int mode){ qfn_1_0_glHint(nativehandle, target, mode); }
        public void glFrontFace(int mode){ qfn_1_0_glFrontFace(nativehandle, mode); }
        public void glCullFace(int mode){ qfn_1_0_glCullFace(nativehandle, mode); }
        public void glTranslatef(float x, float y, float z){ qfn_1_0_glTranslatef(nativehandle, x, y, z); }
        public void glTranslated(double x, double y, double z){ qfn_1_0_glTranslated(nativehandle, x, y, z); }
        public void glScalef(float x, float y, float z){ qfn_1_0_glScalef(nativehandle, x, y, z); }
        public void glScaled(double x, double y, double z){ qfn_1_0_glScaled(nativehandle, x, y, z); }
        public void glRotatef(float angle, float x, float y, float z){ qfn_1_0_glRotatef(nativehandle, angle, x, y, z); }
        public void glRotated(double angle, double x, double y, double z){ qfn_1_0_glRotated(nativehandle, angle, x, y, z); }
        public void glPushMatrix(){ qfn_1_0_glPushMatrix(nativehandle); }
        public void glPopMatrix(){ qfn_1_0_glPopMatrix(nativehandle); }
        public void glOrtho(double left, double right, double bottom, double top, double zNear, double zFar){ qfn_1_0_glOrtho(nativehandle, left, right, bottom, top, zNear, zFar); }
        public void glMultMatrixd( double  [] m){ qfn_1_0_glMultMatrixd(nativehandle, m); }
        public void glMultMatrixf( float  [] m){ qfn_1_0_glMultMatrixf(nativehandle, m); }
        public void glMatrixMode(int mode){ qfn_1_0_glMatrixMode(nativehandle, mode); }
        public void glLoadMatrixd( double  [] m){ qfn_1_0_glLoadMatrixd(nativehandle, m); }
        public void glLoadMatrixf( float  [] m){ qfn_1_0_glLoadMatrixf(nativehandle, m); }
        public void glLoadIdentity(){ qfn_1_0_glLoadIdentity(nativehandle); }
        public void glFrustum(double left, double right, double bottom, double top, double zNear, double zFar){ qfn_1_0_glFrustum(nativehandle, left, right, bottom, top, zNear, zFar); }
        public bool glIsList(int list){ return qfn_1_0_glIsList(nativehandle, list); }
        public void glGetTexGeniv(int coord, int pname, int  [] params){ qfn_1_0_glGetTexGeniv(nativehandle, coord, pname, params); }
        public void glGetTexGenfv(int coord, int pname, float  [] params){ qfn_1_0_glGetTexGenfv(nativehandle, coord, pname, params); }
        public void glGetTexGendv(int coord, int pname, double  [] params){ qfn_1_0_glGetTexGendv(nativehandle, coord, pname, params); }
        public void glGetTexEnviv(int target, int pname, int  [] params){ qfn_1_0_glGetTexEnviv(nativehandle, target, pname, params); }
        public void glGetTexEnvfv(int target, int pname, float  [] params){ qfn_1_0_glGetTexEnvfv(nativehandle, target, pname, params); }
        public void glGetPolygonStipple(byte  [] mask){ qfn_1_0_glGetPolygonStipple(nativehandle, mask); }
        public void glGetPixelMapusv(int map, short  [] values){ qfn_1_0_glGetPixelMapusv(nativehandle, map, values); }
        public void glGetPixelMapuiv(int map, int  [] values){ qfn_1_0_glGetPixelMapuiv(nativehandle, map, values); }
        public void glGetPixelMapfv(int map, float  [] values){ qfn_1_0_glGetPixelMapfv(nativehandle, map, values); }
        public void glGetMaterialiv(int face, int pname, int  [] params){ qfn_1_0_glGetMaterialiv(nativehandle, face, pname, params); }
        public void glGetMaterialfv(int face, int pname, float  [] params){ qfn_1_0_glGetMaterialfv(nativehandle, face, pname, params); }
        public void glGetMapiv(int target, int query, int  [] v){ qfn_1_0_glGetMapiv(nativehandle, target, query, v); }
        public void glGetMapfv(int target, int query, float  [] v){ qfn_1_0_glGetMapfv(nativehandle, target, query, v); }
        public void glGetMapdv(int target, int query, double  [] v){ qfn_1_0_glGetMapdv(nativehandle, target, query, v); }
        public void glGetLightiv(int light, int pname, int  [] params){ qfn_1_0_glGetLightiv(nativehandle, light, pname, params); }
        public void glGetLightfv(int light, int pname, float  [] params){ qfn_1_0_glGetLightfv(nativehandle, light, pname, params); }
        public void glGetClipPlane(int plane, double  [] equation){ qfn_1_0_glGetClipPlane(nativehandle, plane, equation); }
        public void glDrawPixels(int width, int height, int format, int type,  Object pixels){ qfn_1_0_glDrawPixels(nativehandle, width, height, format, type, pixels); }
        public void glCopyPixels(int x, int y, int width, int height, int type){ qfn_1_0_glCopyPixels(nativehandle, x, y, width, height, type); }
        public void glPixelMapusv(int map, int mapsize,  short [] values){ qfn_1_0_glPixelMapusv(nativehandle, map, mapsize, values); }
        public void glPixelMapuiv(int map, int mapsize,  int  [] values){ qfn_1_0_glPixelMapuiv(nativehandle, map, mapsize, values); }
        public void glPixelMapfv(int map, int mapsize,  float  [] values){ qfn_1_0_glPixelMapfv(nativehandle, map, mapsize, values); }
        public void glPixelTransferi(int pname, int param){ qfn_1_0_glPixelTransferi(nativehandle, pname, param); }
        public void glPixelTransferf(int pname, float param){ qfn_1_0_glPixelTransferf(nativehandle, pname, param); }
        public void glPixelZoom(float xfactor, float yfactor){ qfn_1_0_glPixelZoom(nativehandle, xfactor, yfactor); }
        public void glAlphaFunc(int func, float ref){ qfn_1_0_glAlphaFunc(nativehandle, func, ref); }
        public void glEvalPoint2(int i, int j){ qfn_1_0_glEvalPoint2(nativehandle, i, j); }
        public void glEvalMesh2(int mode, int i1, int i2, int j1, int j2){ qfn_1_0_glEvalMesh2(nativehandle, mode, i1, i2, j1, j2); }
        public void glEvalPoint1(int i){ qfn_1_0_glEvalPoint1(nativehandle, i); }
        public void glEvalMesh1(int mode, int i1, int i2){ qfn_1_0_glEvalMesh1(nativehandle, mode, i1, i2); }
        public void glEvalCoord2fv( float  [] u){ qfn_1_0_glEvalCoord2fv(nativehandle, u); }
        public void glEvalCoord2f(float u, float v){ qfn_1_0_glEvalCoord2f(nativehandle, u, v); }
        public void glEvalCoord2dv( double  [] u){ qfn_1_0_glEvalCoord2dv(nativehandle, u); }
        public void glEvalCoord2d(double u, double v){ qfn_1_0_glEvalCoord2d(nativehandle, u, v); }
        public void glEvalCoord1fv( float  [] u){ qfn_1_0_glEvalCoord1fv(nativehandle, u); }
        public void glEvalCoord1f(float u){ qfn_1_0_glEvalCoord1f(nativehandle, u); }
        public void glEvalCoord1dv( double  [] u){ qfn_1_0_glEvalCoord1dv(nativehandle, u); }
        public void glEvalCoord1d(double u){ qfn_1_0_glEvalCoord1d(nativehandle, u); }
        public void glMapGrid2f(int un, float u1, float u2, int vn, float v1, float v2){ qfn_1_0_glMapGrid2f(nativehandle, un, u1, u2, vn, v1, v2); }
        public void glMapGrid2d(int un, double u1, double u2, int vn, double v1, double v2){ qfn_1_0_glMapGrid2d(nativehandle, un, u1, u2, vn, v1, v2); }
        public void glMapGrid1f(int un, float u1, float u2){ qfn_1_0_glMapGrid1f(nativehandle, un, u1, u2); }
        public void glMapGrid1d(int un, double u1, double u2){ qfn_1_0_glMapGrid1d(nativehandle, un, u1, u2); }
        public void glMap2f(int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder,  float  [] points){ qfn_1_0_glMap2f(nativehandle, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
        public void glMap2d(int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder,  double  [] points){ qfn_1_0_glMap2d(nativehandle, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
        public void glMap1f(int target, float u1, float u2, int stride, int order,  float  [] points){ qfn_1_0_glMap1f(nativehandle, target, u1, u2, stride, order, points); }
        public void glMap1d(int target, double u1, double u2, int stride, int order,  double  [] points){ qfn_1_0_glMap1d(nativehandle, target, u1, u2, stride, order, points); }
        public void glPushAttrib(int mask){ qfn_1_0_glPushAttrib(nativehandle, mask); }
        public void glPopAttrib(){ qfn_1_0_glPopAttrib(nativehandle); }
        public void glAccum(int op, float value){ qfn_1_0_glAccum(nativehandle, op, value); }
        public void glIndexMask(int mask){ qfn_1_0_glIndexMask(nativehandle, mask); }
        public void glClearIndex(float c){ qfn_1_0_glClearIndex(nativehandle, c); }
        public void glClearAccum(float red, float green, float blue, float alpha){ qfn_1_0_glClearAccum(nativehandle, red, green, blue, alpha); }
        public void glPushName(int name){ qfn_1_0_glPushName(nativehandle, name); }
        public void glPopName(){ qfn_1_0_glPopName(nativehandle); }
        public void glPassThrough(float token){ qfn_1_0_glPassThrough(nativehandle, token); }
        public void glLoadName(int name){ qfn_1_0_glLoadName(nativehandle, name); }
        public void glInitNames(){ qfn_1_0_glInitNames(nativehandle); }
        public int glRenderMode(int mode){ return qfn_1_0_glRenderMode(nativehandle, mode); }
        public void glSelectBuffer(int size, int  [] buffer){ qfn_1_0_glSelectBuffer(nativehandle, size, buffer); }
        public void glFeedbackBuffer(int size, int type, float  [] buffer){ qfn_1_0_glFeedbackBuffer(nativehandle, size, type, buffer); }
        public void glTexGeniv(int coord, int pname,  int  [] params){ qfn_1_0_glTexGeniv(nativehandle, coord, pname, params); }
        public void glTexGeni(int coord, int pname, int param){ qfn_1_0_glTexGeni(nativehandle, coord, pname, param); }
        public void glTexGenfv(int coord, int pname,  float  [] params){ qfn_1_0_glTexGenfv(nativehandle, coord, pname, params); }
        public void glTexGenf(int coord, int pname, float param){ qfn_1_0_glTexGenf(nativehandle, coord, pname, param); }
        public void glTexGendv(int coord, int pname,  double  [] params){ qfn_1_0_glTexGendv(nativehandle, coord, pname, params); }
        public void glTexGend(int coord, int pname, double param){ qfn_1_0_glTexGend(nativehandle, coord, pname, param); }
        public void glTexEnviv(int target, int pname,  int  [] params){ qfn_1_0_glTexEnviv(nativehandle, target, pname, params); }
        public void glTexEnvi(int target, int pname, int param){ qfn_1_0_glTexEnvi(nativehandle, target, pname, param); }
        public void glTexEnvfv(int target, int pname,  float  [] params){ qfn_1_0_glTexEnvfv(nativehandle, target, pname, params); }
        public void glTexEnvf(int target, int pname, float param){ qfn_1_0_glTexEnvf(nativehandle, target, pname, param); }
        public void glShadeModel(int mode){ qfn_1_0_glShadeModel(nativehandle, mode); }
        public void glPolygonStipple( byte  [] mask){ qfn_1_0_glPolygonStipple(nativehandle, mask); }
        public void glMaterialiv(int face, int pname,  int  [] params){ qfn_1_0_glMaterialiv(nativehandle, face, pname, params); }
        public void glMateriali(int face, int pname, int param){ qfn_1_0_glMateriali(nativehandle, face, pname, param); }
        public void glMaterialfv(int face, int pname,  float  [] params){ qfn_1_0_glMaterialfv(nativehandle, face, pname, params); }
        public void glMaterialf(int face, int pname, float param){ qfn_1_0_glMaterialf(nativehandle, face, pname, param); }
        public void glLineStipple(int factor, short pattern){ qfn_1_0_glLineStipple(nativehandle, factor, pattern); }
        public void glLightModeliv(int pname,  int  [] params){ qfn_1_0_glLightModeliv(nativehandle, pname, params); }
        public void glLightModeli(int pname, int param){ qfn_1_0_glLightModeli(nativehandle, pname, param); }
        public void glLightModelfv(int pname,  float  [] params){ qfn_1_0_glLightModelfv(nativehandle, pname, params); }
        public void glLightModelf(int pname, float param){ qfn_1_0_glLightModelf(nativehandle, pname, param); }
        public void glLightiv(int light, int pname,  int  [] params){ qfn_1_0_glLightiv(nativehandle, light, pname, params); }
        public void glLighti(int light, int pname, int param){ qfn_1_0_glLighti(nativehandle, light, pname, param); }
        public void glLightfv(int light, int pname,  float  [] params){ qfn_1_0_glLightfv(nativehandle, light, pname, params); }
        public void glLightf(int light, int pname, float param){ qfn_1_0_glLightf(nativehandle, light, pname, param); }
        public void glFogiv(int pname,  int  [] params){ qfn_1_0_glFogiv(nativehandle, pname, params); }
        public void glFogi(int pname, int param){ qfn_1_0_glFogi(nativehandle, pname, param); }
        public void glFogfv(int pname,  float  [] params){ qfn_1_0_glFogfv(nativehandle, pname, params); }
        public void glFogf(int pname, float param){ qfn_1_0_glFogf(nativehandle, pname, param); }
        public void glColorMaterial(int face, int mode){ qfn_1_0_glColorMaterial(nativehandle, face, mode); }
        public void glClipPlane(int plane,  double  [] equation){ qfn_1_0_glClipPlane(nativehandle, plane, equation); }
        public void glVertex4sv( short  [] v){ qfn_1_0_glVertex4sv(nativehandle, v); }
        public void glVertex4s(short x, short y, short z, short w){ qfn_1_0_glVertex4s(nativehandle, x, y, z, w); }
        public void glVertex4iv( int  [] v){ qfn_1_0_glVertex4iv(nativehandle, v); }
        public void glVertex4i(int x, int y, int z, int w){ qfn_1_0_glVertex4i(nativehandle, x, y, z, w); }
        public void glVertex4fv( float  [] v){ qfn_1_0_glVertex4fv(nativehandle, v); }
        public void glVertex4f(float x, float y, float z, float w){ qfn_1_0_glVertex4f(nativehandle, x, y, z, w); }
        public void glVertex4dv( double  [] v){ qfn_1_0_glVertex4dv(nativehandle, v); }
        public void glVertex4d(double x, double y, double z, double w){ qfn_1_0_glVertex4d(nativehandle, x, y, z, w); }
        public void glVertex3sv( short  [] v){ qfn_1_0_glVertex3sv(nativehandle, v); }
        public void glVertex3s(short x, short y, short z){ qfn_1_0_glVertex3s(nativehandle, x, y, z); }
        public void glVertex3iv( int  [] v){ qfn_1_0_glVertex3iv(nativehandle, v); }
        public void glVertex3i(int x, int y, int z){ qfn_1_0_glVertex3i(nativehandle, x, y, z); }
        public void glVertex3fv( float  [] v){ qfn_1_0_glVertex3fv(nativehandle, v); }
        public void glVertex3f(float x, float y, float z){ qfn_1_0_glVertex3f(nativehandle, x, y, z); }
        public void glVertex3dv( double  [] v){ qfn_1_0_glVertex3dv(nativehandle, v); }
        public void glVertex3d(double x, double y, double z){ qfn_1_0_glVertex3d(nativehandle, x, y, z); }
        public void glVertex2sv( short  [] v){ qfn_1_0_glVertex2sv(nativehandle, v); }
        public void glVertex2s(short x, short y){ qfn_1_0_glVertex2s(nativehandle, x, y); }
        public void glVertex2iv( int  [] v){ qfn_1_0_glVertex2iv(nativehandle, v); }
        public void glVertex2i(int x, int y){ qfn_1_0_glVertex2i(nativehandle, x, y); }
        public void glVertex2fv( float  [] v){ qfn_1_0_glVertex2fv(nativehandle, v); }
        public void glVertex2f(float x, float y){ qfn_1_0_glVertex2f(nativehandle, x, y); }
        public void glVertex2dv( double  [] v){ qfn_1_0_glVertex2dv(nativehandle, v); }
        public void glVertex2d(double x, double y){ qfn_1_0_glVertex2d(nativehandle, x, y); }
        public void glTexCoord4sv( short  [] v){ qfn_1_0_glTexCoord4sv(nativehandle, v); }
        public void glTexCoord4s(short s, short t, short r, short q){ qfn_1_0_glTexCoord4s(nativehandle, s, t, r, q); }
        public void glTexCoord4iv( int  [] v){ qfn_1_0_glTexCoord4iv(nativehandle, v); }
        public void glTexCoord4i(int s, int t, int r, int q){ qfn_1_0_glTexCoord4i(nativehandle, s, t, r, q); }
        public void glTexCoord4fv( float  [] v){ qfn_1_0_glTexCoord4fv(nativehandle, v); }
        public void glTexCoord4f(float s, float t, float r, float q){ qfn_1_0_glTexCoord4f(nativehandle, s, t, r, q); }
        public void glTexCoord4dv( double  [] v){ qfn_1_0_glTexCoord4dv(nativehandle, v); }
        public void glTexCoord4d(double s, double t, double r, double q){ qfn_1_0_glTexCoord4d(nativehandle, s, t, r, q); }
        public void glTexCoord3sv( short  [] v){ qfn_1_0_glTexCoord3sv(nativehandle, v); }
        public void glTexCoord3s(short s, short t, short r){ qfn_1_0_glTexCoord3s(nativehandle, s, t, r); }
        public void glTexCoord3iv( int  [] v){ qfn_1_0_glTexCoord3iv(nativehandle, v); }
        public void glTexCoord3i(int s, int t, int r){ qfn_1_0_glTexCoord3i(nativehandle, s, t, r); }
        public void glTexCoord3fv( float  [] v){ qfn_1_0_glTexCoord3fv(nativehandle, v); }
        public void glTexCoord3f(float s, float t, float r){ qfn_1_0_glTexCoord3f(nativehandle, s, t, r); }
        public void glTexCoord3dv( double  [] v){ qfn_1_0_glTexCoord3dv(nativehandle, v); }
        public void glTexCoord3d(double s, double t, double r){ qfn_1_0_glTexCoord3d(nativehandle, s, t, r); }
        public void glTexCoord2sv( short  [] v){ qfn_1_0_glTexCoord2sv(nativehandle, v); }
        public void glTexCoord2s(short s, short t){ qfn_1_0_glTexCoord2s(nativehandle, s, t); }
        public void glTexCoord2iv( int  [] v){ qfn_1_0_glTexCoord2iv(nativehandle, v); }
        public void glTexCoord2i(int s, int t){ qfn_1_0_glTexCoord2i(nativehandle, s, t); }
        public void glTexCoord2fv( float  [] v){ qfn_1_0_glTexCoord2fv(nativehandle, v); }
        public void glTexCoord2f(float s, float t){ qfn_1_0_glTexCoord2f(nativehandle, s, t); }
        public void glTexCoord2dv( double  [] v){ qfn_1_0_glTexCoord2dv(nativehandle, v); }
        public void glTexCoord2d(double s, double t){ qfn_1_0_glTexCoord2d(nativehandle, s, t); }
        public void glTexCoord1sv( short  [] v){ qfn_1_0_glTexCoord1sv(nativehandle, v); }
        public void glTexCoord1s(short s){ qfn_1_0_glTexCoord1s(nativehandle, s); }
        public void glTexCoord1iv( int  [] v){ qfn_1_0_glTexCoord1iv(nativehandle, v); }
        public void glTexCoord1i(int s){ qfn_1_0_glTexCoord1i(nativehandle, s); }
        public void glTexCoord1fv( float  [] v){ qfn_1_0_glTexCoord1fv(nativehandle, v); }
        public void glTexCoord1f(float s){ qfn_1_0_glTexCoord1f(nativehandle, s); }
        public void glTexCoord1dv( double  [] v){ qfn_1_0_glTexCoord1dv(nativehandle, v); }
        public void glTexCoord1d(double s){ qfn_1_0_glTexCoord1d(nativehandle, s); }
        public void glRectsv( short  [] v1,  short  [] v2){ qfn_1_0_glRectsv(nativehandle, v1, v2); }
        public void glRects(short x1, short y1, short x2, short y2){ qfn_1_0_glRects(nativehandle, x1, y1, x2, y2); }
        public void glRectiv( int  [] v1,  int  [] v2){ qfn_1_0_glRectiv(nativehandle, v1, v2); }
        public void glRecti(int x1, int y1, int x2, int y2){ qfn_1_0_glRecti(nativehandle, x1, y1, x2, y2); }
        public void glRectfv( float  [] v1,  float  [] v2){ qfn_1_0_glRectfv(nativehandle, v1, v2); }
        public void glRectf(float x1, float y1, float x2, float y2){ qfn_1_0_glRectf(nativehandle, x1, y1, x2, y2); }
        public void glRectdv( double  [] v1,  double  [] v2){ qfn_1_0_glRectdv(nativehandle, v1, v2); }
        public void glRectd(double x1, double y1, double x2, double y2){ qfn_1_0_glRectd(nativehandle, x1, y1, x2, y2); }
        public void glRasterPos4sv( short  [] v){ qfn_1_0_glRasterPos4sv(nativehandle, v); }
        public void glRasterPos4s(short x, short y, short z, short w){ qfn_1_0_glRasterPos4s(nativehandle, x, y, z, w); }
        public void glRasterPos4iv( int  [] v){ qfn_1_0_glRasterPos4iv(nativehandle, v); }
        public void glRasterPos4i(int x, int y, int z, int w){ qfn_1_0_glRasterPos4i(nativehandle, x, y, z, w); }
        public void glRasterPos4fv( float  [] v){ qfn_1_0_glRasterPos4fv(nativehandle, v); }
        public void glRasterPos4f(float x, float y, float z, float w){ qfn_1_0_glRasterPos4f(nativehandle, x, y, z, w); }
        public void glRasterPos4dv( double  [] v){ qfn_1_0_glRasterPos4dv(nativehandle, v); }
        public void glRasterPos4d(double x, double y, double z, double w){ qfn_1_0_glRasterPos4d(nativehandle, x, y, z, w); }
        public void glRasterPos3sv( short  [] v){ qfn_1_0_glRasterPos3sv(nativehandle, v); }
        public void glRasterPos3s(short x, short y, short z){ qfn_1_0_glRasterPos3s(nativehandle, x, y, z); }
        public void glRasterPos3iv( int  [] v){ qfn_1_0_glRasterPos3iv(nativehandle, v); }
        public void glRasterPos3i(int x, int y, int z){ qfn_1_0_glRasterPos3i(nativehandle, x, y, z); }
        public void glRasterPos3fv( float  [] v){ qfn_1_0_glRasterPos3fv(nativehandle, v); }
        public void glRasterPos3f(float x, float y, float z){ qfn_1_0_glRasterPos3f(nativehandle, x, y, z); }
        public void glRasterPos3dv( double  [] v){ qfn_1_0_glRasterPos3dv(nativehandle, v); }
        public void glRasterPos3d(double x, double y, double z){ qfn_1_0_glRasterPos3d(nativehandle, x, y, z); }
        public void glRasterPos2sv( short  [] v){ qfn_1_0_glRasterPos2sv(nativehandle, v); }
        public void glRasterPos2s(short x, short y){ qfn_1_0_glRasterPos2s(nativehandle, x, y); }
        public void glRasterPos2iv( int  [] v){ qfn_1_0_glRasterPos2iv(nativehandle, v); }
        public void glRasterPos2i(int x, int y){ qfn_1_0_glRasterPos2i(nativehandle, x, y); }
        public void glRasterPos2fv( float  [] v){ qfn_1_0_glRasterPos2fv(nativehandle, v); }
        public void glRasterPos2f(float x, float y){ qfn_1_0_glRasterPos2f(nativehandle, x, y); }
        public void glRasterPos2dv( double  [] v){ qfn_1_0_glRasterPos2dv(nativehandle, v); }
        public void glRasterPos2d(double x, double y){ qfn_1_0_glRasterPos2d(nativehandle, x, y); }
        public void glNormal3sv( short  [] v){ qfn_1_0_glNormal3sv(nativehandle, v); }
        public void glNormal3s(short nx, short ny, short nz){ qfn_1_0_glNormal3s(nativehandle, nx, ny, nz); }
        public void glNormal3iv( int  [] v){ qfn_1_0_glNormal3iv(nativehandle, v); }
        public void glNormal3i(int nx, int ny, int nz){ qfn_1_0_glNormal3i(nativehandle, nx, ny, nz); }
        public void glNormal3fv( float  [] v){ qfn_1_0_glNormal3fv(nativehandle, v); }
        public void glNormal3f(float nx, float ny, float nz){ qfn_1_0_glNormal3f(nativehandle, nx, ny, nz); }
        public void glNormal3dv( double  [] v){ qfn_1_0_glNormal3dv(nativehandle, v); }
        public void glNormal3d(double nx, double ny, double nz){ qfn_1_0_glNormal3d(nativehandle, nx, ny, nz); }
        public void glNormal3bv( byte  [] v){ qfn_1_0_glNormal3bv(nativehandle, v); }
        public void glNormal3b(byte nx, byte ny, byte nz){ qfn_1_0_glNormal3b(nativehandle, nx, ny, nz); }
        public void glIndexsv( short  [] c){ qfn_1_0_glIndexsv(nativehandle, c); }
        public void glIndexs(short c){ qfn_1_0_glIndexs(nativehandle, c); }
        public void glIndexiv( int  [] c){ qfn_1_0_glIndexiv(nativehandle, c); }
        public void glIndexi(int c){ qfn_1_0_glIndexi(nativehandle, c); }
        public void glIndexfv( float  [] c){ qfn_1_0_glIndexfv(nativehandle, c); }
        public void glIndexf(float c){ qfn_1_0_glIndexf(nativehandle, c); }
        public void glIndexdv( double  [] c){ qfn_1_0_glIndexdv(nativehandle, c); }
        public void glIndexd(double c){ qfn_1_0_glIndexd(nativehandle, c); }
        public void glEnd(){ qfn_1_0_glEnd(nativehandle); }
        public void glEdgeFlagv( bool  [] flag){ qfn_1_0_glEdgeFlagv(nativehandle, flag); }
        public void glEdgeFlag(bool flag){ qfn_1_0_glEdgeFlag(nativehandle, flag); }
        public void glColor4usv( short  [] v){ qfn_1_0_glColor4usv(nativehandle, v); }
        public void glColor4us(short red, short green, short blue, short alpha){ qfn_1_0_glColor4us(nativehandle, red, green, blue, alpha); }
        public void glColor4uiv( int  [] v){ qfn_1_0_glColor4uiv(nativehandle, v); }
        public void glColor4ui(int red, int green, int blue, int alpha){ qfn_1_0_glColor4ui(nativehandle, red, green, blue, alpha); }
        public void glColor4ubv( byte  [] v){ qfn_1_0_glColor4ubv(nativehandle, v); }
        public void glColor4ub(byte red, byte green, byte blue, byte alpha){ qfn_1_0_glColor4ub(nativehandle, red, green, blue, alpha); }
        public void glColor4sv( short  [] v){ qfn_1_0_glColor4sv(nativehandle, v); }
        public void glColor4s(short red, short green, short blue, short alpha){ qfn_1_0_glColor4s(nativehandle, red, green, blue, alpha); }
        public void glColor4iv( int  [] v){ qfn_1_0_glColor4iv(nativehandle, v); }
        public void glColor4i(int red, int green, int blue, int alpha){ qfn_1_0_glColor4i(nativehandle, red, green, blue, alpha); }
        public void glColor4fv( float  [] v){ qfn_1_0_glColor4fv(nativehandle, v); }
        public void glColor4f(float red, float green, float blue, float alpha){ qfn_1_0_glColor4f(nativehandle, red, green, blue, alpha); }
        public void glColor4dv( double  [] v){ qfn_1_0_glColor4dv(nativehandle, v); }
        public void glColor4d(double red, double green, double blue, double alpha){ qfn_1_0_glColor4d(nativehandle, red, green, blue, alpha); }
        public void glColor4bv( byte  [] v){ qfn_1_0_glColor4bv(nativehandle, v); }
        public void glColor4b(byte red, byte green, byte blue, byte alpha){ qfn_1_0_glColor4b(nativehandle, red, green, blue, alpha); }
        public void glColor3usv( short  [] v){ qfn_1_0_glColor3usv(nativehandle, v); }
        public void glColor3us(short red, short green, short blue){ qfn_1_0_glColor3us(nativehandle, red, green, blue); }
        public void glColor3uiv( int  [] v){ qfn_1_0_glColor3uiv(nativehandle, v); }
        public void glColor3ui(int red, int green, int blue){ qfn_1_0_glColor3ui(nativehandle, red, green, blue); }
        public void glColor3ubv( byte  [] v){ qfn_1_0_glColor3ubv(nativehandle, v); }
        public void glColor3ub(byte red, byte green, byte blue){ qfn_1_0_glColor3ub(nativehandle, red, green, blue); }
        public void glColor3sv( short  [] v){ qfn_1_0_glColor3sv(nativehandle, v); }
        public void glColor3s(short red, short green, short blue){ qfn_1_0_glColor3s(nativehandle, red, green, blue); }
        public void glColor3iv( int  [] v){ qfn_1_0_glColor3iv(nativehandle, v); }
        public void glColor3i(int red, int green, int blue){ qfn_1_0_glColor3i(nativehandle, red, green, blue); }
        public void glColor3fv( float  [] v){ qfn_1_0_glColor3fv(nativehandle, v); }
        public void glColor3f(float red, float green, float blue){ qfn_1_0_glColor3f(nativehandle, red, green, blue); }
        public void glColor3dv( double  [] v){ qfn_1_0_glColor3dv(nativehandle, v); }
        public void glColor3d(double red, double green, double blue){ qfn_1_0_glColor3d(nativehandle, red, green, blue); }
        public void glColor3bv( byte  [] v){ qfn_1_0_glColor3bv(nativehandle, v); }
        public void glColor3b(byte red, byte green, byte blue){ qfn_1_0_glColor3b(nativehandle, red, green, blue); }
        public void glBitmap(int width, int height, float xorig, float yorig, float xmove, float ymove,  byte  [] bitmap){ qfn_1_0_glBitmap(nativehandle, width, height, xorig, yorig, xmove, ymove, bitmap); }
        public void glBegin(int mode){ qfn_1_0_glBegin(nativehandle, mode); }
        public void glListBase(int base){ qfn_1_0_glListBase(nativehandle, base); }
        public int glGenLists(int range){ return qfn_1_0_glGenLists(nativehandle, range); }
        public void glDeleteLists(int list, int range){ qfn_1_0_glDeleteLists(nativehandle, list, range); }
        public void glCallLists(int n, int type, Object lists){ qfn_1_0_glCallLists(nativehandle, n, type, lists); }
        public void glCallList(int list){ qfn_1_0_glCallList(nativehandle, list); }
        public void glEndList(){ qfn_1_0_glEndList(nativehandle); }
        public void glNewList(int list, int mode){ qfn_1_0_glNewList(nativehandle, list, mode); }
        
        
        public import "libQXLibrary"{
            void cdecl qfn_1_0_glViewport(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_1_0_glDepthRange(long nativehandle, double nearVal, double farVal) ;
            bool cdecl qfn_1_0_glIsEnabled(long nativehandle, int cap) ;
            void cdecl qfn_1_0_glGetTexLevelParameteriv(long nativehandle, int target, int level, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetTexLevelParameterfv(long nativehandle, int target, int level, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetTexParameteriv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetTexParameterfv(long nativehandle, int target, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetTexImage(long nativehandle, int target, int level, int format, int type, ObjectPtr pixels) ;
            String cdecl qfn_1_0_glGetString(long nativehandle, int name) ;
            void cdecl qfn_1_0_glGetIntegerv(long nativehandle, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetFloatv(long nativehandle, int pname, float  * params) ;
            int cdecl qfn_1_0_glGetError(long nativehandle) ;
            void cdecl qfn_1_0_glGetDoublev(long nativehandle, int pname, double  * params) ;
            void cdecl qfn_1_0_glGetBooleanv(long nativehandle, int pname, bool  * params) ;
            void cdecl qfn_1_0_glReadPixels(long nativehandle, int x, int y, int width, int height, int format, int type, ObjectPtr pixels) ;
            void cdecl qfn_1_0_glReadBuffer(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glPixelStorei(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_0_glPixelStoref(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_0_glDepthFunc(long nativehandle, int func) ;
            void cdecl qfn_1_0_glStencilOp(long nativehandle, int fail, int zfail, int zpass) ;
            void cdecl qfn_1_0_glStencilFunc(long nativehandle, int func, int ref, int mask) ;
            void cdecl qfn_1_0_glLogicOp(long nativehandle, int opcode) ;
            void cdecl qfn_1_0_glBlendFunc(long nativehandle, int sfactor, int dfactor) ;
            void cdecl qfn_1_0_glFlush(long nativehandle) ;
            void cdecl qfn_1_0_glFinish(long nativehandle) ;
            void cdecl qfn_1_0_glEnable(long nativehandle, int cap) ;
            void cdecl qfn_1_0_glDisable(long nativehandle, int cap) ;
            void cdecl qfn_1_0_glDepthMask(long nativehandle, bool flag) ;
            void cdecl qfn_1_0_glColorMask(long nativehandle, bool red, bool green, bool blue, bool alpha) ;
            void cdecl qfn_1_0_glStencilMask(long nativehandle, int mask) ;
            void cdecl qfn_1_0_glClearDepth(long nativehandle, double depth) ;
            void cdecl qfn_1_0_glClearStencil(long nativehandle, int s) ;
            void cdecl qfn_1_0_glClearColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_0_glClear(long nativehandle, int mask) ;
            void cdecl qfn_1_0_glDrawBuffer(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, /*IN*/ ObjectPtr pixels) ;
            void cdecl qfn_1_0_glTexImage1D(long nativehandle, int target, int level, int internalformat, int width, int border, int format, int type, /*IN*/ ObjectPtr pixels) ;
            void cdecl qfn_1_0_glTexParameteriv(long nativehandle, int target, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glTexParameteri(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_1_0_glTexParameterfv(long nativehandle, int target, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glTexParameterf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_1_0_glScissor(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_1_0_glPolygonMode(long nativehandle, int face, int mode) ;
            void cdecl qfn_1_0_glPointSize(long nativehandle, float size) ;
            void cdecl qfn_1_0_glLineWidth(long nativehandle, float width) ;
            void cdecl qfn_1_0_glHint(long nativehandle, int target, int mode) ;
            void cdecl qfn_1_0_glFrontFace(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glCullFace(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glTranslatef(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_0_glTranslated(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_0_glScalef(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_0_glScaled(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_0_glRotatef(long nativehandle, float angle, float x, float y, float z) ;
            void cdecl qfn_1_0_glRotated(long nativehandle, double angle, double x, double y, double z) ;
            void cdecl qfn_1_0_glPushMatrix(long nativehandle) ;
            void cdecl qfn_1_0_glPopMatrix(long nativehandle) ;
            void cdecl qfn_1_0_glOrtho(long nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) ;
            void cdecl qfn_1_0_glMultMatrixd(long nativehandle, /*IN*/ double  * m) ;
            void cdecl qfn_1_0_glMultMatrixf(long nativehandle, /*IN*/ float  * m) ;
            void cdecl qfn_1_0_glMatrixMode(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glLoadMatrixd(long nativehandle, /*IN*/ double  * m) ;
            void cdecl qfn_1_0_glLoadMatrixf(long nativehandle, /*IN*/ float  * m) ;
            void cdecl qfn_1_0_glLoadIdentity(long nativehandle) ;
            void cdecl qfn_1_0_glFrustum(long nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) ;
            bool cdecl qfn_1_0_glIsList(long nativehandle, int list) ;
            void cdecl qfn_1_0_glGetTexGeniv(long nativehandle, int coord, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetTexGenfv(long nativehandle, int coord, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetTexGendv(long nativehandle, int coord, int pname, double  * params) ;
            void cdecl qfn_1_0_glGetTexEnviv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetTexEnvfv(long nativehandle, int target, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetPolygonStipple(long nativehandle, byte  * mask) ;
            void cdecl qfn_1_0_glGetPixelMapusv(long nativehandle, int map, short  * values) ;
            void cdecl qfn_1_0_glGetPixelMapuiv(long nativehandle, int map, int  * values) ;
            void cdecl qfn_1_0_glGetPixelMapfv(long nativehandle, int map, float  * values) ;
            void cdecl qfn_1_0_glGetMaterialiv(long nativehandle, int face, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetMaterialfv(long nativehandle, int face, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetMapiv(long nativehandle, int target, int query, int  * v) ;
            void cdecl qfn_1_0_glGetMapfv(long nativehandle, int target, int query, float  * v) ;
            void cdecl qfn_1_0_glGetMapdv(long nativehandle, int target, int query, double  * v) ;
            void cdecl qfn_1_0_glGetLightiv(long nativehandle, int light, int pname, int  * params) ;
            void cdecl qfn_1_0_glGetLightfv(long nativehandle, int light, int pname, float  * params) ;
            void cdecl qfn_1_0_glGetClipPlane(long nativehandle, int plane, double  * equation) ;
            void cdecl qfn_1_0_glDrawPixels(long nativehandle, int width, int height, int format, int type, /*IN*/ ObjectPtr pixels) ;
            void cdecl qfn_1_0_glCopyPixels(long nativehandle, int x, int y, int width, int height, int type) ;
            void cdecl qfn_1_0_glPixelMapusv(long nativehandle, int map, int mapsize, /*IN*/ short  * values) ;
            void cdecl qfn_1_0_glPixelMapuiv(long nativehandle, int map, int mapsize, /*IN*/ int  * values) ;
            void cdecl qfn_1_0_glPixelMapfv(long nativehandle, int map, int mapsize, /*IN*/ float  * values) ;
            void cdecl qfn_1_0_glPixelTransferi(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_0_glPixelTransferf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_0_glPixelZoom(long nativehandle, float xfactor, float yfactor) ;
            void cdecl qfn_1_0_glAlphaFunc(long nativehandle, int func, float ref) ;
            void cdecl qfn_1_0_glEvalPoint2(long nativehandle, int i, int j) ;
            void cdecl qfn_1_0_glEvalMesh2(long nativehandle, int mode, int i1, int i2, int j1, int j2) ;
            void cdecl qfn_1_0_glEvalPoint1(long nativehandle, int i) ;
            void cdecl qfn_1_0_glEvalMesh1(long nativehandle, int mode, int i1, int i2) ;
            void cdecl qfn_1_0_glEvalCoord2fv(long nativehandle, /*IN*/ float  * u) ;
            void cdecl qfn_1_0_glEvalCoord2f(long nativehandle, float u, float v) ;
            void cdecl qfn_1_0_glEvalCoord2dv(long nativehandle, /*IN*/ double  * u) ;
            void cdecl qfn_1_0_glEvalCoord2d(long nativehandle, double u, double v) ;
            void cdecl qfn_1_0_glEvalCoord1fv(long nativehandle, /*IN*/ float  * u) ;
            void cdecl qfn_1_0_glEvalCoord1f(long nativehandle, float u) ;
            void cdecl qfn_1_0_glEvalCoord1dv(long nativehandle, /*IN*/ double  * u) ;
            void cdecl qfn_1_0_glEvalCoord1d(long nativehandle, double u) ;
            void cdecl qfn_1_0_glMapGrid2f(long nativehandle, int un, float u1, float u2, int vn, float v1, float v2) ;
            void cdecl qfn_1_0_glMapGrid2d(long nativehandle, int un, double u1, double u2, int vn, double v1, double v2) ;
            void cdecl qfn_1_0_glMapGrid1f(long nativehandle, int un, float u1, float u2) ;
            void cdecl qfn_1_0_glMapGrid1d(long nativehandle, int un, double u1, double u2) ;
            void cdecl qfn_1_0_glMap2f(long nativehandle, int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, /*IN*/ float  * points) ;
            void cdecl qfn_1_0_glMap2d(long nativehandle, int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, /*IN*/ double  * points) ;
            void cdecl qfn_1_0_glMap1f(long nativehandle, int target, float u1, float u2, int stride, int order, /*IN*/ float  * points) ;
            void cdecl qfn_1_0_glMap1d(long nativehandle, int target, double u1, double u2, int stride, int order, /*IN*/ double  * points) ;
            void cdecl qfn_1_0_glPushAttrib(long nativehandle, int mask) ;
            void cdecl qfn_1_0_glPopAttrib(long nativehandle) ;
            void cdecl qfn_1_0_glAccum(long nativehandle, int op, float value) ;
            void cdecl qfn_1_0_glIndexMask(long nativehandle, int mask) ;
            void cdecl qfn_1_0_glClearIndex(long nativehandle, float c) ;
            void cdecl qfn_1_0_glClearAccum(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_0_glPushName(long nativehandle, int name) ;
            void cdecl qfn_1_0_glPopName(long nativehandle ) ;
            void cdecl qfn_1_0_glPassThrough(long nativehandle, float token) ;
            void cdecl qfn_1_0_glLoadName(long nativehandle, int name) ;
            void cdecl qfn_1_0_glInitNames(long nativehandle ) ;
            int cdecl qfn_1_0_glRenderMode(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glSelectBuffer(long nativehandle, int size, int  * buffer) ;
            void cdecl qfn_1_0_glFeedbackBuffer(long nativehandle, int size, int type, float  * buffer) ;
            void cdecl qfn_1_0_glTexGeniv(long nativehandle, int coord, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glTexGeni(long nativehandle, int coord, int pname, int param) ;
            void cdecl qfn_1_0_glTexGenfv(long nativehandle, int coord, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glTexGenf(long nativehandle, int coord, int pname, float param) ;
            void cdecl qfn_1_0_glTexGendv(long nativehandle, int coord, int pname, /*IN*/ double  * params) ;
            void cdecl qfn_1_0_glTexGend(long nativehandle, int coord, int pname, double param) ;
            void cdecl qfn_1_0_glTexEnviv(long nativehandle, int target, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glTexEnvi(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_1_0_glTexEnvfv(long nativehandle, int target, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glTexEnvf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_1_0_glShadeModel(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glPolygonStipple(long nativehandle, /*IN*/ byte  * mask) ;
            void cdecl qfn_1_0_glMaterialiv(long nativehandle, int face, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glMateriali(long nativehandle, int face, int pname, int param) ;
            void cdecl qfn_1_0_glMaterialfv(long nativehandle, int face, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glMaterialf(long nativehandle, int face, int pname, float param) ;
            void cdecl qfn_1_0_glLineStipple(long nativehandle, int factor, short pattern) ;
            void cdecl qfn_1_0_glLightModeliv(long nativehandle, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glLightModeli(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_0_glLightModelfv(long nativehandle, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glLightModelf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_0_glLightiv(long nativehandle, int light, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glLighti(long nativehandle, int light, int pname, int param) ;
            void cdecl qfn_1_0_glLightfv(long nativehandle, int light, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glLightf(long nativehandle, int light, int pname, float param) ;
            void cdecl qfn_1_0_glFogiv(long nativehandle, int pname, /*IN*/ int  * params) ;
            void cdecl qfn_1_0_glFogi(long nativehandle, int pname, int param) ;
            void cdecl qfn_1_0_glFogfv(long nativehandle, int pname, /*IN*/ float  * params) ;
            void cdecl qfn_1_0_glFogf(long nativehandle, int pname, float param) ;
            void cdecl qfn_1_0_glColorMaterial(long nativehandle, int face, int mode) ;
            void cdecl qfn_1_0_glClipPlane(long nativehandle, int plane, /*IN*/ double  * equation) ;
            void cdecl qfn_1_0_glVertex4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glVertex4s(long nativehandle, short x, short y, short z, short w) ;
            void cdecl qfn_1_0_glVertex4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glVertex4i(long nativehandle, int x, int y, int z, int w) ;
            void cdecl qfn_1_0_glVertex4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glVertex4f(long nativehandle, float x, float y, float z, float w) ;
            void cdecl qfn_1_0_glVertex4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glVertex4d(long nativehandle, double x, double y, double z, double w) ;
            void cdecl qfn_1_0_glVertex3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glVertex3s(long nativehandle, short x, short y, short z) ;
            void cdecl qfn_1_0_glVertex3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glVertex3i(long nativehandle, int x, int y, int z) ;
            void cdecl qfn_1_0_glVertex3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glVertex3f(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_0_glVertex3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glVertex3d(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_0_glVertex2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glVertex2s(long nativehandle, short x, short y) ;
            void cdecl qfn_1_0_glVertex2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glVertex2i(long nativehandle, int x, int y) ;
            void cdecl qfn_1_0_glVertex2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glVertex2f(long nativehandle, float x, float y) ;
            void cdecl qfn_1_0_glVertex2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glVertex2d(long nativehandle, double x, double y) ;
            void cdecl qfn_1_0_glTexCoord4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glTexCoord4s(long nativehandle, short s, short t, short r, short q) ;
            void cdecl qfn_1_0_glTexCoord4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glTexCoord4i(long nativehandle, int s, int t, int r, int q) ;
            void cdecl qfn_1_0_glTexCoord4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glTexCoord4f(long nativehandle, float s, float t, float r, float q) ;
            void cdecl qfn_1_0_glTexCoord4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glTexCoord4d(long nativehandle, double s, double t, double r, double q) ;
            void cdecl qfn_1_0_glTexCoord3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glTexCoord3s(long nativehandle, short s, short t, short r) ;
            void cdecl qfn_1_0_glTexCoord3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glTexCoord3i(long nativehandle, int s, int t, int r) ;
            void cdecl qfn_1_0_glTexCoord3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glTexCoord3f(long nativehandle, float s, float t, float r) ;
            void cdecl qfn_1_0_glTexCoord3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glTexCoord3d(long nativehandle, double s, double t, double r) ;
            void cdecl qfn_1_0_glTexCoord2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glTexCoord2s(long nativehandle, short s, short t) ;
            void cdecl qfn_1_0_glTexCoord2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glTexCoord2i(long nativehandle, int s, int t) ;
            void cdecl qfn_1_0_glTexCoord2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glTexCoord2f(long nativehandle, float s, float t) ;
            void cdecl qfn_1_0_glTexCoord2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glTexCoord2d(long nativehandle, double s, double t) ;
            void cdecl qfn_1_0_glTexCoord1sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glTexCoord1s(long nativehandle, short s) ;
            void cdecl qfn_1_0_glTexCoord1iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glTexCoord1i(long nativehandle, int s) ;
            void cdecl qfn_1_0_glTexCoord1fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glTexCoord1f(long nativehandle, float s) ;
            void cdecl qfn_1_0_glTexCoord1dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glTexCoord1d(long nativehandle, double s) ;
            void cdecl qfn_1_0_glRectsv(long nativehandle, /*IN*/ short  * v1, /*IN*/ short  * v2) ;
            void cdecl qfn_1_0_glRects(long nativehandle, short x1, short y1, short x2, short y2) ;
            void cdecl qfn_1_0_glRectiv(long nativehandle, /*IN*/ int  * v1, /*IN*/ int  * v2) ;
            void cdecl qfn_1_0_glRecti(long nativehandle, int x1, int y1, int x2, int y2) ;
            void cdecl qfn_1_0_glRectfv(long nativehandle, /*IN*/ float  * v1, /*IN*/ float  * v2) ;
            void cdecl qfn_1_0_glRectf(long nativehandle, float x1, float y1, float x2, float y2) ;
            void cdecl qfn_1_0_glRectdv(long nativehandle, /*IN*/ double  * v1, /*IN*/ double  * v2) ;
            void cdecl qfn_1_0_glRectd(long nativehandle, double x1, double y1, double x2, double y2) ;
            void cdecl qfn_1_0_glRasterPos4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glRasterPos4s(long nativehandle, short x, short y, short z, short w) ;
            void cdecl qfn_1_0_glRasterPos4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glRasterPos4i(long nativehandle, int x, int y, int z, int w) ;
            void cdecl qfn_1_0_glRasterPos4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glRasterPos4f(long nativehandle, float x, float y, float z, float w) ;
            void cdecl qfn_1_0_glRasterPos4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glRasterPos4d(long nativehandle, double x, double y, double z, double w) ;
            void cdecl qfn_1_0_glRasterPos3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glRasterPos3s(long nativehandle, short x, short y, short z) ;
            void cdecl qfn_1_0_glRasterPos3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glRasterPos3i(long nativehandle, int x, int y, int z) ;
            void cdecl qfn_1_0_glRasterPos3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glRasterPos3f(long nativehandle, float x, float y, float z) ;
            void cdecl qfn_1_0_glRasterPos3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glRasterPos3d(long nativehandle, double x, double y, double z) ;
            void cdecl qfn_1_0_glRasterPos2sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glRasterPos2s(long nativehandle, short x, short y) ;
            void cdecl qfn_1_0_glRasterPos2iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glRasterPos2i(long nativehandle, int x, int y) ;
            void cdecl qfn_1_0_glRasterPos2fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glRasterPos2f(long nativehandle, float x, float y) ;
            void cdecl qfn_1_0_glRasterPos2dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glRasterPos2d(long nativehandle, double x, double y) ;
            void cdecl qfn_1_0_glNormal3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glNormal3s(long nativehandle, short nx, short ny, short nz) ;
            void cdecl qfn_1_0_glNormal3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glNormal3i(long nativehandle, int nx, int ny, int nz) ;
            void cdecl qfn_1_0_glNormal3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glNormal3f(long nativehandle, float nx, float ny, float nz) ;
            void cdecl qfn_1_0_glNormal3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glNormal3d(long nativehandle, double nx, double ny, double nz) ;
            void cdecl qfn_1_0_glNormal3bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_0_glNormal3b(long nativehandle, byte nx, byte ny, byte nz) ;
            void cdecl qfn_1_0_glIndexsv(long nativehandle, /*IN*/ short  * c) ;
            void cdecl qfn_1_0_glIndexs(long nativehandle, short c) ;
            void cdecl qfn_1_0_glIndexiv(long nativehandle, /*IN*/ int  * c) ;
            void cdecl qfn_1_0_glIndexi(long nativehandle, int c) ;
            void cdecl qfn_1_0_glIndexfv(long nativehandle, /*IN*/ float  * c) ;
            void cdecl qfn_1_0_glIndexf(long nativehandle, float c) ;
            void cdecl qfn_1_0_glIndexdv(long nativehandle, /*IN*/ double  * c) ;
            void cdecl qfn_1_0_glIndexd(long nativehandle, double c) ;
            void cdecl qfn_1_0_glEnd(long nativehandle) ;
            void cdecl qfn_1_0_glEdgeFlagv(long nativehandle, /*IN*/ bool  * flag) ;
            void cdecl qfn_1_0_glEdgeFlag(long nativehandle, bool flag) ;
            void cdecl qfn_1_0_glColor4usv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glColor4us(long nativehandle, short red, short green, short blue, short alpha) ;
            void cdecl qfn_1_0_glColor4uiv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glColor4ui(long nativehandle, int red, int green, int blue, int alpha) ;
            void cdecl qfn_1_0_glColor4ubv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_0_glColor4ub(long nativehandle, byte red, byte green, byte blue, byte alpha) ;
            void cdecl qfn_1_0_glColor4sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glColor4s(long nativehandle, short red, short green, short blue, short alpha) ;
            void cdecl qfn_1_0_glColor4iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glColor4i(long nativehandle, int red, int green, int blue, int alpha) ;
            void cdecl qfn_1_0_glColor4fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glColor4f(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_1_0_glColor4dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glColor4d(long nativehandle, double red, double green, double blue, double alpha) ;
            void cdecl qfn_1_0_glColor4bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_0_glColor4b(long nativehandle, byte red, byte green, byte blue, byte alpha) ;
            void cdecl qfn_1_0_glColor3usv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glColor3us(long nativehandle, short red, short green, short blue) ;
            void cdecl qfn_1_0_glColor3uiv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glColor3ui(long nativehandle, int red, int green, int blue) ;
            void cdecl qfn_1_0_glColor3ubv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_0_glColor3ub(long nativehandle, byte red, byte green, byte blue) ;
            void cdecl qfn_1_0_glColor3sv(long nativehandle, /*IN*/ short  * v) ;
            void cdecl qfn_1_0_glColor3s(long nativehandle, short red, short green, short blue) ;
            void cdecl qfn_1_0_glColor3iv(long nativehandle, /*IN*/ int  * v) ;
            void cdecl qfn_1_0_glColor3i(long nativehandle, int red, int green, int blue) ;
            void cdecl qfn_1_0_glColor3fv(long nativehandle, /*IN*/ float  * v) ;
            void cdecl qfn_1_0_glColor3f(long nativehandle, float red, float green, float blue) ;
            void cdecl qfn_1_0_glColor3dv(long nativehandle, /*IN*/ double  * v) ;
            void cdecl qfn_1_0_glColor3d(long nativehandle, double red, double green, double blue) ;
            void cdecl qfn_1_0_glColor3bv(long nativehandle, /*IN*/ byte  * v) ;
            void cdecl qfn_1_0_glColor3b(long nativehandle, byte red, byte green, byte blue) ;
            void cdecl qfn_1_0_glBitmap(long nativehandle, int width, int height, float xorig, float yorig, float xmove, float ymove, /*IN*/ byte  * bitmap) ;
            void cdecl qfn_1_0_glBegin(long nativehandle, int mode) ;
            void cdecl qfn_1_0_glListBase(long nativehandle, int base) ;
            int cdecl qfn_1_0_glGenLists(long nativehandle, int range) ;
            void cdecl qfn_1_0_glDeleteLists(long nativehandle, int list, int range) ;
            void cdecl qfn_1_0_glCallLists(long nativehandle, int n, int type, ObjectPtr lists) ;
            void cdecl qfn_1_0_glCallList(long nativehandle, int list) ;
            void cdecl qfn_1_0_glEndList(long nativehandle) ;
            void cdecl qfn_1_0_glNewList(long nativehandle, int list, int mode) ;
        };
    };
};