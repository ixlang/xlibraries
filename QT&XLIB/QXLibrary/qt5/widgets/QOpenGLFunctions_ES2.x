//xlang Source, Name:qt5/widgets/QOpenGLFunctions_1_0.x 
//Date: Tue Mar 21:31:32 2021 

package Qt{
    public class QOpenGLFunctions_ES2 : QAbstractOpenGLFunctions{
        public QOpenGLFunctions_ES2(){
            
        }
        public QOpenGLFunctions_ES2(long h){
            super(h);
        }
        
        public bool initializeOpenGLFunctions() {
            return QtXnl.widget_get_bool_value(nativehandle,  Constant.QOPENGLFUNCTIONS_ES2_INITIALIZEOPENGLFUNCTIONS);
        }
        
        void glActiveTexture(int texture){ qfn_ES2_glActiveTexture(nativehandle, texture); }
        void glAttachShader(int program, int shader){ qfn_ES2_glAttachShader(nativehandle, program, shader); }
        void glBindAttribLocation(int program, int index, /*IN*/ String name){ qfn_ES2_glBindAttribLocation(nativehandle, program, index, name); }
        void glBindBuffer(int target, int buffer){ qfn_ES2_glBindBuffer(nativehandle, target, buffer); }
        void glBindFramebuffer(int target, int framebuffer){ qfn_ES2_glBindFramebuffer(nativehandle, target, framebuffer); }
        void glBindRenderbuffer(int target, int renderbuffer){ qfn_ES2_glBindRenderbuffer(nativehandle, target, renderbuffer); }
        void glBindTexture(int target, int texture){ qfn_ES2_glBindTexture(nativehandle, target, texture); }
        void glBlendColor(float red, float green, float blue, float alpha){ qfn_ES2_glBlendColor(nativehandle, red, green, blue, alpha); }
        void glBlendEquation(int mode){ qfn_ES2_glBlendEquation(nativehandle, mode); }
        void glBlendEquationSeparate(int modeRGB, int modeAlpha){ qfn_ES2_glBlendEquationSeparate(nativehandle, modeRGB, modeAlpha); }
        void glBlendFunc(int sfactor, int dfactor){ qfn_ES2_glBlendFunc(nativehandle, sfactor, dfactor); }
        void glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha){ qfn_ES2_glBlendFuncSeparate(nativehandle, srcRGB, dstRGB, srcAlpha, dstAlpha); }
        void glBufferData(int target, int size, /*IN*/ byte []  data, int usage){ qfn_ES2_glBufferData(nativehandle, target, size, data, usage); }
        void glBufferSubData(int target, int offset, int size, /*IN*/ byte []  data){ qfn_ES2_glBufferSubData(nativehandle, target, offset, size, data); }
        int glCheckFramebufferStatus(int target){ return qfn_ES2_glCheckFramebufferStatus(nativehandle, target); }
        void glClear(int mask){ qfn_ES2_glClear(nativehandle, mask); }
        void glClearColor(float red, float green, float blue, float alpha){ qfn_ES2_glClearColor(nativehandle, red, green, blue, alpha); }
        void glClearDepthf(float depth){ qfn_ES2_glClearDepthf(nativehandle, depth); }
        void glClearStencil(int s){ qfn_ES2_glClearStencil(nativehandle, s); }
        void glColorMask(bool red, bool green, bool blue, bool alpha){ qfn_ES2_glColorMask(nativehandle, red, green, blue, alpha); }
        void glCompileShader(int shader){ qfn_ES2_glCompileShader(nativehandle, shader); }
        void glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, /*IN*/ byte []  data){ qfn_ES2_glCompressedTexImage2D(nativehandle, target, level, internalformat, width, height, border, imageSize, data); }
        void glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, /*IN*/ byte []  data){ qfn_ES2_glCompressedTexSubImage2D(nativehandle, target, level, xoffset, yoffset, width, height, format, imageSize, data); }
        void glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border){ qfn_ES2_glCopyTexImage2D(nativehandle, target, level, internalformat, x, y, width, height, border); }
        void glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height){ qfn_ES2_glCopyTexSubImage2D(nativehandle, target, level, xoffset, yoffset, x, y, width, height); }
        int glCreateProgram(){ return qfn_ES2_glCreateProgram(nativehandle); }
        int glCreateShader(int type){ return qfn_ES2_glCreateShader(nativehandle, type); }
        void glCullFace(int mode){ qfn_ES2_glCullFace(nativehandle, mode); }
        void glDeleteBuffers(int n, /*IN*/ int []  buffers){ qfn_ES2_glDeleteBuffers(nativehandle, n, buffers); }
        void glDeleteFramebuffers(int n, /*IN*/ int []  framebuffers){ qfn_ES2_glDeleteFramebuffers(nativehandle, n, framebuffers); }
        void glDeleteProgram(int program){ qfn_ES2_glDeleteProgram(nativehandle, program); }
        void glDeleteRenderbuffers(int n, /*IN*/ int []  renderbuffers){ qfn_ES2_glDeleteRenderbuffers(nativehandle, n, renderbuffers); }
        void glDeleteShader(int shader){ qfn_ES2_glDeleteShader(nativehandle, shader); }
        void glDeleteTextures(int n, /*IN*/ int []  textures){ qfn_ES2_glDeleteTextures(nativehandle, n, textures); }
        void glDepthFunc(int func){ qfn_ES2_glDepthFunc(nativehandle, func); }
        void glDepthMask(bool flag){ qfn_ES2_glDepthMask(nativehandle, flag); }
        void glDepthRangef(float zNear, float zFar){ qfn_ES2_glDepthRangef(nativehandle, zNear, zFar); }
        void glDetachShader(int program, int shader){ qfn_ES2_glDetachShader(nativehandle, program, shader); }
        void glDisable(int cap){ qfn_ES2_glDisable(nativehandle, cap); }
        void glDisableVertexAttribArray(int index){ qfn_ES2_glDisableVertexAttribArray(nativehandle, index); }
        void glDrawArrays(int mode, int first, int count){ qfn_ES2_glDrawArrays(nativehandle, mode, first, count); }
        void glDrawElements(int mode, int count, int type, /*IN*/ byte []  indices){ qfn_ES2_glDrawElements(nativehandle, mode, count, type, indices); }
        void glEnable(int cap){ qfn_ES2_glEnable(nativehandle, cap); }
        void glEnableVertexAttribArray(int index){ qfn_ES2_glEnableVertexAttribArray(nativehandle, index); }
        void glFinish(){ qfn_ES2_glFinish(nativehandle); }
        void glFlush(){ qfn_ES2_glFlush(nativehandle); }
        void glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer){ qfn_ES2_glFramebufferRenderbuffer(nativehandle, target, attachment, renderbuffertarget, renderbuffer); }
        void glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level){ qfn_ES2_glFramebufferTexture2D(nativehandle, target, attachment, textarget, texture, level); }
        void glFrontFace(int mode){ qfn_ES2_glFrontFace(nativehandle, mode); }
        void glGenBuffers(int n, int []  buffers){ qfn_ES2_glGenBuffers(nativehandle, n, buffers); }
        void glGenerateMipmap(int target){ qfn_ES2_glGenerateMipmap(nativehandle, target); }
        void glGenFramebuffers(int n, int []  framebuffers){ qfn_ES2_glGenFramebuffers(nativehandle, n, framebuffers); }
        void glGenRenderbuffers(int n, int []  renderbuffers){ qfn_ES2_glGenRenderbuffers(nativehandle, n, renderbuffers); }
        void glGenTextures(int n, int []  textures){ qfn_ES2_glGenTextures(nativehandle, n, textures); }
        void glGetActiveAttrib(int program, int index, int bufsize, int []  length, int []  size, int []  type, byte []  name){ qfn_ES2_glGetActiveAttrib(nativehandle, program, index, bufsize, length, size, type, name); }
        void glGetActiveUniform(int program, int index, int bufsize, int []  length, int []  size, int []  type, byte []  name){ qfn_ES2_glGetActiveUniform(nativehandle, program, index, bufsize, length, size, type, name); }
        void glGetAttachedShaders(int program, int maxcount, int []  count, int []  shaders){ qfn_ES2_glGetAttachedShaders(nativehandle, program, maxcount, count, shaders); }
        int glGetAttribLocation(int program, /*IN*/ byte []  name){ return qfn_ES2_glGetAttribLocation(nativehandle, program, name); }
        void glGetBooleanv(int pname, bool []  params){ qfn_ES2_glGetBooleanv(nativehandle, pname, params); }
        void glGetBufferParameteriv(int target, int pname, int []  params){ qfn_ES2_glGetBufferParameteriv(nativehandle, target, pname, params); }
        int glGetError(){ return qfn_ES2_glGetError(nativehandle); }
        void glGetFloatv(int pname, float []  params){ qfn_ES2_glGetFloatv(nativehandle, pname, params); }
        void glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, int []  params){ qfn_ES2_glGetFramebufferAttachmentParameteriv(nativehandle, target, attachment, pname, params); }
        void glGetIntegerv(int pname, int []  params){ qfn_ES2_glGetIntegerv(nativehandle, pname, params); }
        void glGetProgramiv(int program, int pname, int []  params){ qfn_ES2_glGetProgramiv(nativehandle, program, pname, params); }
        void glGetProgramInfoLog(int program, int bufsize, int []  length, byte []  infolog){ qfn_ES2_glGetProgramInfoLog(nativehandle, program, bufsize, length, infolog); }
        void glGetRenderbufferParameteriv(int target, int pname, int []  params){ qfn_ES2_glGetRenderbufferParameteriv(nativehandle, target, pname, params); }
        void glGetShaderiv(int shader, int pname, int []  params){ qfn_ES2_glGetShaderiv(nativehandle, shader, pname, params); }
        void glGetShaderInfoLog(int shader, int bufsize, int []  length, byte []  infolog){ qfn_ES2_glGetShaderInfoLog(nativehandle, shader, bufsize, length, infolog); }
        void glGetShaderPrecisionFormat(int shadertype, int precisiontype, int []  range, int []  precision){ qfn_ES2_glGetShaderPrecisionFormat(nativehandle, shadertype, precisiontype, range, precision); }
        void glGetShaderSource(int shader, int bufsize, int []  length, byte []  source){ qfn_ES2_glGetShaderSource(nativehandle, shader, bufsize, length, source); }
        String glGetString(int name){ return qfn_ES2_glGetString(nativehandle, name); }
        void glGetTexParameterfv(int target, int pname, float []  params){ qfn_ES2_glGetTexParameterfv(nativehandle, target, pname, params); }
        void glGetTexParameteriv(int target, int pname, int []  params){ qfn_ES2_glGetTexParameteriv(nativehandle, target, pname, params); }
        void glGetUniformfv(int program, int location, float []  params){ qfn_ES2_glGetUniformfv(nativehandle, program, location, params); }
        void glGetUniformiv(int program, int location, int []  params){ qfn_ES2_glGetUniformiv(nativehandle, program, location, params); }
        int glGetUniformLocation(int program, /*IN*/ String  name){ return qfn_ES2_glGetUniformLocation(nativehandle, program, name); }
        void glGetVertexAttribfv(int index, int pname, float []  params){ qfn_ES2_glGetVertexAttribfv(nativehandle, index, pname, params); }
        void glGetVertexAttribiv(int index, int pname, int []  params){ qfn_ES2_glGetVertexAttribiv(nativehandle, index, pname, params); }
        void glGetVertexAttribPointerv(int index, int pname, long  pointer){ qfn_ES2_glGetVertexAttribPointerv(nativehandle, index, pname, pointer); }
        void glHint(int target, int mode){ qfn_ES2_glHint(nativehandle, target, mode); }
        bool glIsBuffer(int buffer){ return qfn_ES2_glIsBuffer(nativehandle, buffer); }
        bool glIsEnabled(int cap){ return qfn_ES2_glIsEnabled(nativehandle, cap); }
        bool glIsFramebuffer(int framebuffer){ return qfn_ES2_glIsFramebuffer(nativehandle, framebuffer); }
        bool glIsProgram(int program){ return qfn_ES2_glIsProgram(nativehandle, program); }
        bool glIsRenderbuffer(int renderbuffer){ return qfn_ES2_glIsRenderbuffer(nativehandle, renderbuffer); }
        bool glIsShader(int shader){ return qfn_ES2_glIsShader(nativehandle, shader); }
        bool glIsTexture(int texture){ return qfn_ES2_glIsTexture(nativehandle, texture); }
        void glLineWidth(float width){ qfn_ES2_glLineWidth(nativehandle, width); }
        void glLinkProgram(int program){ qfn_ES2_glLinkProgram(nativehandle, program); }
        void glPixelStorei(int pname, int param){ qfn_ES2_glPixelStorei(nativehandle, pname, param); }
        void glPolygonOffset(float factor, float units){ qfn_ES2_glPolygonOffset(nativehandle, factor, units); }
        void glReadPixels(int x, int y, int width, int height, int format, int type, byte []  pixels){ qfn_ES2_glReadPixels(nativehandle, x, y, width, height, format, type, pixels); }
        void glReleaseShaderCompiler(){ qfn_ES2_glReleaseShaderCompiler(nativehandle); }
        void glRenderbufferStorage(int target, int internalformat, int width, int height){ qfn_ES2_glRenderbufferStorage(nativehandle, target, internalformat, width, height); }
        void glSampleCoverage(float value, bool invert){ qfn_ES2_glSampleCoverage(nativehandle, value, invert); }
        void glScissor(int x, int y, int width, int height){ qfn_ES2_glScissor(nativehandle, x, y, width, height); }
        void glShaderBinary(int n, /*IN*/ int []  shaders, int binaryformat, /*IN*/ byte []  binary, int length){ qfn_ES2_glShaderBinary(nativehandle, n, shaders, binaryformat, binary, length); }
        void glShaderSource(int shader, int count, /*IN*/ String string, /*IN*/ int []  length){ qfn_ES2_glShaderSource(nativehandle, shader, count, string, length); }
        void glStencilFunc(int func, int ref, int mask){ qfn_ES2_glStencilFunc(nativehandle, func, ref, mask); }
        void glStencilFuncSeparate(int face, int func, int ref, int mask){ qfn_ES2_glStencilFuncSeparate(nativehandle, face, func, ref, mask); }
        void glStencilMask(int mask){ qfn_ES2_glStencilMask(nativehandle, mask); }
        void glStencilMaskSeparate(int face, int mask){ qfn_ES2_glStencilMaskSeparate(nativehandle, face, mask); }
        void glStencilOp(int fail, int zfail, int zpass){ qfn_ES2_glStencilOp(nativehandle, fail, zfail, zpass); }
        void glStencilOpSeparate(int face, int fail, int zfail, int zpass){ qfn_ES2_glStencilOpSeparate(nativehandle, face, fail, zfail, zpass); }
        void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, /*IN*/ byte []  pixels){ qfn_ES2_glTexImage2D(nativehandle, target, level, internalformat, width, height, border, format, type, pixels); }
        void glTexParameterf(int target, int pname, float param){ qfn_ES2_glTexParameterf(nativehandle, target, pname, param); }
        void glTexParameterfv(int target, int pname, /*IN*/ float []  params){ qfn_ES2_glTexParameterfv(nativehandle, target, pname, params); }
        void glTexParameteri(int target, int pname, int param){ qfn_ES2_glTexParameteri(nativehandle, target, pname, param); }
        void glTexParameteriv(int target, int pname, /*IN*/ int []  params){ qfn_ES2_glTexParameteriv(nativehandle, target, pname, params); }
        void glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, /*IN*/ byte []  pixels){ qfn_ES2_glTexSubImage2D(nativehandle, target, level, xoffset, yoffset, width, height, format, type, pixels); }
        void glUniform1f(int location, float x){ qfn_ES2_glUniform1f(nativehandle, location, x); }
        void glUniform1fv(int location, int count, /*IN*/ float []  v){ qfn_ES2_glUniform1fv(nativehandle, location, count, v); }
        void glUniform1i(int location, int x){ qfn_ES2_glUniform1i(nativehandle, location, x); }
        void glUniform1iv(int location, int count, /*IN*/ int []  v){ qfn_ES2_glUniform1iv(nativehandle, location, count, v); }
        void glUniform2f(int location, float x, float y){ qfn_ES2_glUniform2f(nativehandle, location, x, y); }
        void glUniform2fv(int location, int count, /*IN*/ float []  v){ qfn_ES2_glUniform2fv(nativehandle, location, count, v); }
        void glUniform2i(int location, int x, int y){ qfn_ES2_glUniform2i(nativehandle, location, x, y); }
        void glUniform2iv(int location, int count, /*IN*/ int []  v){ qfn_ES2_glUniform2iv(nativehandle, location, count, v); }
        void glUniform3f(int location, float x, float y, float z){ qfn_ES2_glUniform3f(nativehandle, location, x, y, z); }
        void glUniform3fv(int location, int count, /*IN*/ float []  v){ qfn_ES2_glUniform3fv(nativehandle, location, count, v); }
        void glUniform3i(int location, int x, int y, int z){ qfn_ES2_glUniform3i(nativehandle, location, x, y, z); }
        void glUniform3iv(int location, int count, /*IN*/ int []  v){ qfn_ES2_glUniform3iv(nativehandle, location, count, v); }
        void glUniform4f(int location, float x, float y, float z, float w){ qfn_ES2_glUniform4f(nativehandle, location, x, y, z, w); }
        void glUniform4fv(int location, int count, /*IN*/ float []  v){ qfn_ES2_glUniform4fv(nativehandle, location, count, v); }
        void glUniform4i(int location, int x, int y, int z, int w){ qfn_ES2_glUniform4i(nativehandle, location, x, y, z, w); }
        void glUniform4iv(int location, int count, /*IN*/ int []  v){ qfn_ES2_glUniform4iv(nativehandle, location, count, v); }
        void glUniformMatrix2fv(int location, int count, bool transpose, /*IN*/ float []  value){ qfn_ES2_glUniformMatrix2fv(nativehandle, location, count, transpose, value); }
        void glUniformMatrix3fv(int location, int count, bool transpose, /*IN*/ float []  value){ qfn_ES2_glUniformMatrix3fv(nativehandle, location, count, transpose, value); }
        void glUniformMatrix4fv(int location, int count, bool transpose, /*IN*/ float []  value){ qfn_ES2_glUniformMatrix4fv(nativehandle, location, count, transpose, value); }
        void glUseProgram(int program){ qfn_ES2_glUseProgram(nativehandle, program); }
        void glValidateProgram(int program){ qfn_ES2_glValidateProgram(nativehandle, program); }
        void glVertexAttrib1f(int indx, float x){ qfn_ES2_glVertexAttrib1f(nativehandle, indx, x); }
        void glVertexAttrib1fv(int indx, /*IN*/ float []  values){ qfn_ES2_glVertexAttrib1fv(nativehandle, indx, values); }
        void glVertexAttrib2f(int indx, float x, float y){ qfn_ES2_glVertexAttrib2f(nativehandle, indx, x, y); }
        void glVertexAttrib2fv(int indx, /*IN*/ float []  values){ qfn_ES2_glVertexAttrib2fv(nativehandle, indx, values); }
        void glVertexAttrib3f(int indx, float x, float y, float z){ qfn_ES2_glVertexAttrib3f(nativehandle, indx, x, y, z); }
        void glVertexAttrib3fv(int indx, /*IN*/ float []  values){ qfn_ES2_glVertexAttrib3fv(nativehandle, indx, values); }
        void glVertexAttrib4f(int indx, float x, float y, float z, float w){ qfn_ES2_glVertexAttrib4f(nativehandle, indx, x, y, z, w); }
        void glVertexAttrib4fv(int indx, /*IN*/ float []  values){ qfn_ES2_glVertexAttrib4fv(nativehandle, indx, values); }
        void glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, /*IN*/ Object  ptr){ qfn_ES2_glVertexAttribPointer(nativehandle, indx, size, type, normalized, stride, ptr); }
        void glViewport(int x, int y, int width, int height){ qfn_ES2_glViewport(nativehandle, x, y, width, height); }
        
        
        import "libQXLibrary"{
            void cdecl qfn_ES2_glActiveTexture(long nativehandle, int texture) ;
            void cdecl qfn_ES2_glAttachShader(long nativehandle, int program, int shader) ;
            void cdecl qfn_ES2_glBindAttribLocation(long nativehandle, int program, int index, String  name) ;
            void cdecl qfn_ES2_glBindBuffer(long nativehandle, int target, int buffer) ;
            void cdecl qfn_ES2_glBindFramebuffer(long nativehandle, int target, int framebuffer) ;
            void cdecl qfn_ES2_glBindRenderbuffer(long nativehandle, int target, int renderbuffer) ;
            void cdecl qfn_ES2_glBindTexture(long nativehandle, int target, int texture) ;
            void cdecl qfn_ES2_glBlendColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_ES2_glBlendEquation(long nativehandle, int mode) ;
            void cdecl qfn_ES2_glBlendEquationSeparate(long nativehandle, int modeRGB, int modeAlpha) ;
            void cdecl qfn_ES2_glBlendFunc(long nativehandle, int sfactor, int dfactor) ;
            void cdecl qfn_ES2_glBlendFuncSeparate(long nativehandle, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) ;
            void cdecl qfn_ES2_glBufferData(long nativehandle, int target, int* size, /*IN*/ byte *  data, int usage) ;
            void cdecl qfn_ES2_glBufferSubData(long nativehandle, int target, int* offset, int* size, /*IN*/ byte *  data) ;
            int cdecl qfn_ES2_glCheckFramebufferStatus(long nativehandle, int target) ;
            void cdecl qfn_ES2_glClear(long nativehandle, int mask) ;
            void cdecl qfn_ES2_glClearColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_ES2_glClearDepthf(long nativehandle, float depth) ;
            void cdecl qfn_ES2_glClearStencil(long nativehandle, int s) ;
            void cdecl qfn_ES2_glColorMask(long nativehandle, bool red, bool green, bool blue, bool alpha) ;
            void cdecl qfn_ES2_glCompileShader(long nativehandle, int shader) ;
            void cdecl qfn_ES2_glCompressedTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int imageSize, /*IN*/ byte *  data) ;
            void cdecl qfn_ES2_glCompressedTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, /*IN*/ byte *  data) ;
            void cdecl qfn_ES2_glCopyTexImage2D(long nativehandle, int target, int level, int internalformat, int x, int y, int width, int height, int border) ;
            void cdecl qfn_ES2_glCopyTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) ;
            int cdecl qfn_ES2_glCreateProgram(long nativehandle) ;
            int cdecl qfn_ES2_glCreateShader(long nativehandle, int type) ;
            void cdecl qfn_ES2_glCullFace(long nativehandle, int mode) ;
            void cdecl qfn_ES2_glDeleteBuffers(long nativehandle, int n, /*IN*/ int *  buffers) ;
            void cdecl qfn_ES2_glDeleteFramebuffers(long nativehandle, int n, /*IN*/ int *  framebuffers) ;
            void cdecl qfn_ES2_glDeleteProgram(long nativehandle, int program) ;
            void cdecl qfn_ES2_glDeleteRenderbuffers(long nativehandle, int n, /*IN*/ int *  renderbuffers) ;
            void cdecl qfn_ES2_glDeleteShader(long nativehandle, int shader) ;
            void cdecl qfn_ES2_glDeleteTextures(long nativehandle, int n, /*IN*/ int *  textures) ;
            void cdecl qfn_ES2_glDepthFunc(long nativehandle, int func) ;
            void cdecl qfn_ES2_glDepthMask(long nativehandle, bool flag) ;
            void cdecl qfn_ES2_glDepthRangef(long nativehandle, float zNear, float zFar) ;
            void cdecl qfn_ES2_glDetachShader(long nativehandle, int program, int shader) ;
            void cdecl qfn_ES2_glDisable(long nativehandle, int cap) ;
            void cdecl qfn_ES2_glDisableVertexAttribArray(long nativehandle, int index) ;
            void cdecl qfn_ES2_glDrawArrays(long nativehandle, int mode, int first, int count) ;
            void cdecl qfn_ES2_glDrawElements(long nativehandle, int mode, int count, int type, /*IN*/ byte *  indices) ;
            void cdecl qfn_ES2_glEnable(long nativehandle, int cap) ;
            void cdecl qfn_ES2_glEnableVertexAttribArray(long nativehandle, int index) ;
            void cdecl qfn_ES2_glFinish(long nativehandle) ;
            void cdecl qfn_ES2_glFlush(long nativehandle) ;
            void cdecl qfn_ES2_glFramebufferRenderbuffer(long nativehandle, int target, int attachment, int renderbuffertarget, int renderbuffer) ;
            void cdecl qfn_ES2_glFramebufferTexture2D(long nativehandle, int target, int attachment, int textarget, int texture, int level) ;
            void cdecl qfn_ES2_glFrontFace(long nativehandle, int mode) ;
            void cdecl qfn_ES2_glGenBuffers(long nativehandle, int n, int *  buffers) ;
            void cdecl qfn_ES2_glGenerateMipmap(long nativehandle, int target) ;
            void cdecl qfn_ES2_glGenFramebuffers(long nativehandle, int n, int *  framebuffers) ;
            void cdecl qfn_ES2_glGenRenderbuffers(long nativehandle, int n, int *  renderbuffers) ;
            void cdecl qfn_ES2_glGenTextures(long nativehandle, int n, int *  textures) ;
            void cdecl qfn_ES2_glGetActiveAttrib(long nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, byte *  name) ;
            void cdecl qfn_ES2_glGetActiveUniform(long nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, byte *  name) ;
            void cdecl qfn_ES2_glGetAttachedShaders(long nativehandle, int program, int maxcount, int *  count, int *  shaders) ;
            int cdecl qfn_ES2_glGetAttribLocation(long nativehandle, int program, /*IN*/ byte *  name) ;
            void cdecl qfn_ES2_glGetBooleanv(long nativehandle, int pname, bool *  params) ;
            void cdecl qfn_ES2_glGetBufferParameteriv(long nativehandle, int target, int pname, int *  params) ;
            int cdecl qfn_ES2_glGetError(long nativehandle) ;
            void cdecl qfn_ES2_glGetFloatv(long nativehandle, int pname, float *  params) ;
            void cdecl qfn_ES2_glGetFramebufferAttachmentParameteriv(long nativehandle, int target, int attachment, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetIntegerv(long nativehandle, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetProgramiv(long nativehandle, int program, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetProgramInfoLog(long nativehandle, int program, int bufsize, int *  length, byte *  infolog) ;
            void cdecl qfn_ES2_glGetRenderbufferParameteriv(long nativehandle, int target, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetShaderiv(long nativehandle, int shader, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetShaderInfoLog(long nativehandle, int shader, int bufsize, int *  length, byte *  infolog) ;
            void cdecl qfn_ES2_glGetShaderPrecisionFormat(long nativehandle, int shadertype, int precisiontype, int *  range, int *  precision) ;
            void cdecl qfn_ES2_glGetShaderSource(long nativehandle, int shader, int bufsize, int *  length, byte *  source) ;
            String cdecl qfn_ES2_glGetString(long nativehandle, int name) ;
            void cdecl qfn_ES2_glGetTexParameterfv(long nativehandle, int target, int pname, float *  params) ;
            void cdecl qfn_ES2_glGetTexParameteriv(long nativehandle, int target, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetUniformfv(long nativehandle, int program, int location, float *  params) ;
            void cdecl qfn_ES2_glGetUniformiv(long nativehandle, int program, int location, int *  params) ;
            int cdecl qfn_ES2_glGetUniformLocation(long nativehandle, int program, String  name) ;
            void cdecl qfn_ES2_glGetVertexAttribfv(long nativehandle, int index, int pname, float *  params) ;
            void cdecl qfn_ES2_glGetVertexAttribiv(long nativehandle, int index, int pname, int *  params) ;
            void cdecl qfn_ES2_glGetVertexAttribPointerv(long nativehandle, int index, int pname, long *  pointer) ;
            void cdecl qfn_ES2_glHint(long nativehandle, int target, int mode) ;
            bool cdecl qfn_ES2_glIsBuffer(long nativehandle, int buffer) ;
            bool cdecl qfn_ES2_glIsEnabled(long nativehandle, int cap) ;
            bool cdecl qfn_ES2_glIsFramebuffer(long nativehandle, int framebuffer) ;
            bool cdecl qfn_ES2_glIsProgram(long nativehandle, int program) ;
            bool cdecl qfn_ES2_glIsRenderbuffer(long nativehandle, int renderbuffer) ;
            bool cdecl qfn_ES2_glIsShader(long nativehandle, int shader) ;
            bool cdecl qfn_ES2_glIsTexture(long nativehandle, int texture) ;
            void cdecl qfn_ES2_glLineWidth(long nativehandle, float width) ;
            void cdecl qfn_ES2_glLinkProgram(long nativehandle, int program) ;
            void cdecl qfn_ES2_glPixelStorei(long nativehandle, int pname, int param) ;
            void cdecl qfn_ES2_glPolygonOffset(long nativehandle, float factor, float units) ;
            void cdecl qfn_ES2_glReadPixels(long nativehandle, int x, int y, int width, int height, int format, int type, byte *  pixels) ;
            void cdecl qfn_ES2_glReleaseShaderCompiler(long nativehandle) ;
            void cdecl qfn_ES2_glRenderbufferStorage(long nativehandle, int target, int internalformat, int width, int height) ;
            void cdecl qfn_ES2_glSampleCoverage(long nativehandle, float value, bool invert) ;
            void cdecl qfn_ES2_glScissor(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_ES2_glShaderBinary(long nativehandle, int n, /*IN*/ int *  shaders, int binaryformat, /*IN*/ byte *  binary, int length) ;
            void cdecl qfn_ES2_glShaderSource(long nativehandle, int shader, int count, String string, /*IN*/ int *  length) ;
            void cdecl qfn_ES2_glStencilFunc(long nativehandle, int func, int ref, int mask) ;
            void cdecl qfn_ES2_glStencilFuncSeparate(long nativehandle, int face, int func, int ref, int mask) ;
            void cdecl qfn_ES2_glStencilMask(long nativehandle, int mask) ;
            void cdecl qfn_ES2_glStencilMaskSeparate(long nativehandle, int face, int mask) ;
            void cdecl qfn_ES2_glStencilOp(long nativehandle, int fail, int zfail, int zpass) ;
            void cdecl qfn_ES2_glStencilOpSeparate(long nativehandle, int face, int fail, int zfail, int zpass) ;
            void cdecl qfn_ES2_glTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, /*IN*/ byte *  pixels) ;
            void cdecl qfn_ES2_glTexParameterf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_ES2_glTexParameterfv(long nativehandle, int target, int pname, /*IN*/ float *  params) ;
            void cdecl qfn_ES2_glTexParameteri(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_ES2_glTexParameteriv(long nativehandle, int target, int pname, /*IN*/ int *  params) ;
            void cdecl qfn_ES2_glTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, /*IN*/ byte *  pixels) ;
            void cdecl qfn_ES2_glUniform1f(long nativehandle, int location, float x) ;
            void cdecl qfn_ES2_glUniform1fv(long nativehandle, int location, int count, /*IN*/ float *  v) ;
            void cdecl qfn_ES2_glUniform1i(long nativehandle, int location, int x) ;
            void cdecl qfn_ES2_glUniform1iv(long nativehandle, int location, int count, /*IN*/ int *  v) ;
            void cdecl qfn_ES2_glUniform2f(long nativehandle, int location, float x, float y) ;
            void cdecl qfn_ES2_glUniform2fv(long nativehandle, int location, int count, /*IN*/ float *  v) ;
            void cdecl qfn_ES2_glUniform2i(long nativehandle, int location, int x, int y) ;
            void cdecl qfn_ES2_glUniform2iv(long nativehandle, int location, int count, /*IN*/ int *  v) ;
            void cdecl qfn_ES2_glUniform3f(long nativehandle, int location, float x, float y, float z) ;
            void cdecl qfn_ES2_glUniform3fv(long nativehandle, int location, int count, /*IN*/ float *  v) ;
            void cdecl qfn_ES2_glUniform3i(long nativehandle, int location, int x, int y, int z) ;
            void cdecl qfn_ES2_glUniform3iv(long nativehandle, int location, int count, /*IN*/ int *  v) ;
            void cdecl qfn_ES2_glUniform4f(long nativehandle, int location, float x, float y, float z, float w) ;
            void cdecl qfn_ES2_glUniform4fv(long nativehandle, int location, int count, /*IN*/ float *  v) ;
            void cdecl qfn_ES2_glUniform4i(long nativehandle, int location, int x, int y, int z, int w) ;
            void cdecl qfn_ES2_glUniform4iv(long nativehandle, int location, int count, /*IN*/ int *  v) ;
            void cdecl qfn_ES2_glUniformMatrix2fv(long nativehandle, int location, int count, bool transpose, /*IN*/ float *  value) ;
            void cdecl qfn_ES2_glUniformMatrix3fv(long nativehandle, int location, int count, bool transpose, /*IN*/ float *  value) ;
            void cdecl qfn_ES2_glUniformMatrix4fv(long nativehandle, int location, int count, bool transpose, /*IN*/ float *  value) ;
            void cdecl qfn_ES2_glUseProgram(long nativehandle, int program) ;
            void cdecl qfn_ES2_glValidateProgram(long nativehandle, int program) ;
            void cdecl qfn_ES2_glVertexAttrib1f(long nativehandle, int indx, float x) ;
            void cdecl qfn_ES2_glVertexAttrib1fv(long nativehandle, int indx, /*IN*/ float *  values) ;
            void cdecl qfn_ES2_glVertexAttrib2f(long nativehandle, int indx, float x, float y) ;
            void cdecl qfn_ES2_glVertexAttrib2fv(long nativehandle, int indx, /*IN*/ float *  values) ;
            void cdecl qfn_ES2_glVertexAttrib3f(long nativehandle, int indx, float x, float y, float z) ;
            void cdecl qfn_ES2_glVertexAttrib3fv(long nativehandle, int indx, /*IN*/ float *  values) ;
            void cdecl qfn_ES2_glVertexAttrib4f(long nativehandle, int indx, float x, float y, float z, float w) ;
            void cdecl qfn_ES2_glVertexAttrib4fv(long nativehandle, int indx, /*IN*/ float *  values) ;
            void cdecl qfn_ES2_glVertexAttribPointer(long nativehandle, int indx, int size, int type, bool normalized, int stride, /*IN*/ ObjectPtr  ptr) ;
            void cdecl qfn_ES2_glViewport(long nativehandle, int x, int y, int width, int height) ;

        };
    };
};