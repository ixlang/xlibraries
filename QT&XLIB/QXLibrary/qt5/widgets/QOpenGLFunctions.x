//xlang Source, Name:qt5/widgets/QOpenGLFunctions.x 
//Date: Tue Mar 04:20:47 2021 
package Qt{
    public class QOpenGLFunctions : QCore{
        public QOpenGLFunctions(){
            
        }
        public QOpenGLFunctions(long h){
            super(h);       
            if (h == 0){
                throw new IllegalArgumentException("could not new Object");
            }
        }
        public enum OpenGLFeature
        {
            Multitexture          = 0x0001,
            Shaders               = 0x0002,
            Buffers               = 0x0004,
            Framebuffers          = 0x0008,
            BlendColor            = 0x0010,
            BlendEquation         = 0x0020,
            BlendEquationSeparate = 0x0040,
            BlendFuncSeparate     = 0x0080,
            BlendSubtract         = 0x0100,
            CompressedTextures    = 0x0200,
            Multisample           = 0x0400,
            StencilSeparate       = 0x0800,
            NPOTTextures          = 0x1000,
            NPOTTextureRepeat     = 0x2000,
            FixedFunctionPipeline = 0x4000,
            TextureRGFormats      = 0x8000,
            MultipleRenderTargets = 0x10000
        };
        
        public OpenGLFeature openGLFeatures(){
            return (OpenGLFeature)QtXnl.widget_get_int_value(nativehandle, Constant.QOPENGLFUNCTIONS_OPENGLFEATURES);
        }
        
        public bool hasOpenGLFeature(OpenGLFeature feature){
            return QtXnl.widget_get_int_bool(nativehandle, Constant.QOPENGLFUNCTIONS_HASOPENGLFEATURE,feature);
        }
        
        public void initializeOpenGLFunctions(){
            QtXnl.widget_slot(nativehandle,  Constant.QOPENGLFUNCTIONS_INITIALIZEOPENGLFUNCTIONS);
        }
        
        public void glBindTexture(int target, int texture) { qfn_glBindTexture(nativehandle, target, texture); }
        public void glBlendFunc(int sfactor, int dfactor) { qfn_glBlendFunc(nativehandle, sfactor, dfactor); }
        public void glClear(int mask) { qfn_glClear(nativehandle, mask); }
        public void glClearColor(float red, float green, float blue, float alpha) { qfn_glClearColor(nativehandle, red, green, blue, alpha); }
        public void glClearStencil(int s) { qfn_glClearStencil(nativehandle, s); }
        public void glColorMask(bool red, bool green, bool blue, bool alpha) { qfn_glColorMask(nativehandle, red, green, blue, alpha); }
        public void glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) { qfn_glCopyTexImage2D(nativehandle, target, level, internalformat, x, y, width, height, border); }
        public void glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) { qfn_glCopyTexSubImage2D(nativehandle, target, level, xoffset, yoffset, x, y, width, height); }
        public void glCullFace(int mode) { qfn_glCullFace(nativehandle, mode); }
        public void glDeleteTextures(int n, int []  textures) { qfn_glDeleteTextures(nativehandle, n, textures); }
        public void glDepthFunc(int func) { qfn_glDepthFunc(nativehandle, func); }
        public void glDepthMask(bool flag) { qfn_glDepthMask(nativehandle, flag); }
        public void glDisable(int cap) { qfn_glDisable(nativehandle, cap); }
        public void glDrawArrays(int mode, int first, int count) { qfn_glDrawArrays(nativehandle, mode, first, count); }
        public void glDrawElements(int mode, int count, int type, byte []  indices) { qfn_glDrawElements(nativehandle, mode, count, type, indices); }
        public void glEnable(int cap) { qfn_glEnable(nativehandle, cap); }
        public void glFinish() { qfn_glFinish(nativehandle); }
        public void glFlush() { qfn_glFlush(nativehandle); }
        public void glFrontFace(int mode) { qfn_glFrontFace(nativehandle, mode); }
        public void glGenTextures(int []  textures) { qfn_glGenTextures(nativehandle, textures.length, textures); }
        public bool glGetBooleanv(int pname) { return qfn_glGetBooleanv(nativehandle, pname); }
        public int glGetError() { return qfn_glGetError(nativehandle); }
        public float glGetFloatv(int pname) { return qfn_glGetFloatv(nativehandle, pname); }
        public int glGetIntegerv(int pname) { return qfn_glGetIntegerv(nativehandle, pname); }
        public String glGetString(int name) { return qfn_glGetString(nativehandle, name); }
        public float glGetTexParameterfv(int target, int pname) { return qfn_glGetTexParameterfv(nativehandle, target, pname); }
        public int glGetTexParameteriv(int target, int pname) { return qfn_glGetTexParameteriv(nativehandle, target, pname); }
        public void glHint(int target, int mode) { qfn_glHint(nativehandle, target, mode); }
        public bool glIsEnabled(int cap) { return qfn_glIsEnabled(nativehandle, cap); }
        public bool glIsTexture(int texture) { return qfn_glIsTexture(nativehandle, texture); }
        public void glLineWidth(float width) { qfn_glLineWidth(nativehandle, width); }
        public void glPixelStorei(int pname, int param) { qfn_glPixelStorei(nativehandle, pname, param); }
        public void glPolygonOffset(float factor, float units) { qfn_glPolygonOffset(nativehandle, factor, units); }
        public void glReadPixels(int x, int y, int width, int height, int format, int type, byte [] pixels) { qfn_glReadPixels(nativehandle, x, y, width, height, format, type, pixels); }
        public void glScissor(int x, int y, int width, int height) { qfn_glScissor(nativehandle, x, y, width, height); }
        public void glStencilFunc(int func, int ref, int mask) { qfn_glStencilFunc(nativehandle, func, ref, mask); }
        public void glStencilMask(int mask) { qfn_glStencilMask(nativehandle, mask); }
        public void glStencilOp(int fail, int zfail, int zpass) { qfn_glStencilOp(nativehandle, fail, zfail, zpass); }
        public void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, byte [] pixels) { qfn_glTexImage2D(nativehandle, target, level, internalformat, width, height, border, format, type, pixels); }
        public void glTexParameterf(int target, int pname, float param) { qfn_glTexParameterf(nativehandle, target, pname, param); }
        public void glTexParameterfv(int target, int pname, float [] params) { qfn_glTexParameterfv(nativehandle, target, pname, params); }
        public void glTexParameteri(int target, int pname, int param) { qfn_glTexParameteri(nativehandle, target, pname, param); }
        public void glTexParameteriv(int target, int pname, int [] params) { qfn_glTexParameteriv(nativehandle, target, pname, params); }
        public void glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, byte [] pixels) { qfn_glTexSubImage2D(nativehandle, target, level, xoffset, yoffset, width, height, format, type, pixels); }
        public void glViewport(int x, int y, int width, int height) { qfn_glViewport(nativehandle, x, y, width, height); }
        public void glActiveTexture(int texture) { qfn_glActiveTexture(nativehandle, texture); }
        public void glAttachShader(int program, int shader) { qfn_glAttachShader(nativehandle, program, shader); }
        public void glBindAttribLocation(int program, int index, String name) { qfn_glBindAttribLocation(nativehandle, program, index, name); }
        public void glBindBuffer(int target, int buffer) { qfn_glBindBuffer(nativehandle, target, buffer); }
        public void glBindFramebuffer(int target, int framebuffer) { qfn_glBindFramebuffer(nativehandle, target, framebuffer); }
        public void glBindRenderbuffer(int target, int renderbuffer) { qfn_glBindRenderbuffer(nativehandle, target, renderbuffer); }
        public void glBlendColor(float red, float green, float blue, float alpha) { qfn_glBlendColor(nativehandle, red, green, blue, alpha); }
        public void glBlendEquation(int mode) { qfn_glBlendEquation(nativehandle, mode); }
        public void glBlendEquationSeparate(int modeRGB, int modeAlpha) { qfn_glBlendEquationSeparate(nativehandle, modeRGB, modeAlpha); }
        public void glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) { qfn_glBlendFuncSeparate(nativehandle, srcRGB, dstRGB, srcAlpha, dstAlpha); }
        public void glBufferData(int target, int size, Object data, int usage) { qfn_glBufferData(nativehandle, target, size, data, usage); }
        public void glBufferSubData(int target, int offset, int size, byte [] data) { qfn_glBufferSubData(nativehandle, target, offset, size, data); }
        public int glCheckFramebufferStatus(int target) { return qfn_glCheckFramebufferStatus(nativehandle, target); }
        public void glClearDepthf(float depth) { qfn_glClearDepthf(nativehandle, depth); }
        public void glCompileShader(int shader) { qfn_glCompileShader(nativehandle, shader); }
        public void glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, byte [] data) { qfn_glCompressedTexImage2D(nativehandle, target, level, internalformat, width, height, border, imageSize, data); }
        public void glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, byte [] data) { qfn_glCompressedTexSubImage2D(nativehandle, target, level, xoffset, yoffset, width, height, format, imageSize, data); }
        public int glCreateProgram() { return qfn_glCreateProgram(nativehandle); }
        public int glCreateShader(int type) { return qfn_glCreateShader(nativehandle, type); }
        public void glDeleteBuffers(int n, int [] buffers) { qfn_glDeleteBuffers(nativehandle, n, buffers); }
        public void glDeleteFramebuffers(int n, int [] framebuffers) { qfn_glDeleteFramebuffers(nativehandle, n, framebuffers); }
        public void glDeleteProgram(int program) { qfn_glDeleteProgram(nativehandle, program); }
        public void glDeleteRenderbuffers(int n, int [] renderbuffers) { qfn_glDeleteRenderbuffers(nativehandle, n, renderbuffers); }
        public void glDeleteShader(int shader) { qfn_glDeleteShader(nativehandle, shader); }
        public void glDepthRangef(float zNear, float zFar) { qfn_glDepthRangef(nativehandle, zNear, zFar); }
        public void glDetachShader(int program, int shader) { qfn_glDetachShader(nativehandle, program, shader); }
        public void glDisableVertexAttribArray(int index) { qfn_glDisableVertexAttribArray(nativehandle, index); }
        public void glEnableVertexAttribArray(int index) { qfn_glEnableVertexAttribArray(nativehandle, index); }
        public void glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer) { qfn_glFramebufferRenderbuffer(nativehandle, target, attachment, renderbuffertarget, renderbuffer); }
        public void glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level) { qfn_glFramebufferTexture2D(nativehandle, target, attachment, textarget, texture, level); }
        public void glGenBuffers(int n, int []  buffers) { qfn_glGenBuffers(nativehandle, n, buffers); }
        public void glGenerateMipmap(int target) { qfn_glGenerateMipmap(nativehandle, target); }
        public void glGenFramebuffers(int n, int []  framebuffers) { qfn_glGenFramebuffers(nativehandle, n, framebuffers); }
        public void glGenRenderbuffers(int n, int []  renderbuffers) { qfn_glGenRenderbuffers(nativehandle, n, renderbuffers); }
        public void glGetActiveAttrib(int program, int index, int bufsize, int []  length, int []  size, int []  type, byte [] name) { qfn_glGetActiveAttrib(nativehandle, program, index, bufsize, length, size, type, name); }
        public void glGetActiveUniform(int program, int index, int bufsize, int []  length, int []  size, int []  type, byte [] name) { qfn_glGetActiveUniform(nativehandle, program, index, bufsize, length, size, type, name); }
        public void glGetAttachedShaders(int program, int maxcount, int []  count, int []  shaders) { qfn_glGetAttachedShaders(nativehandle, program, maxcount, count, shaders); }
        public int glGetAttribLocation(int program, String name) { return qfn_glGetAttribLocation(nativehandle, program, name); }
        public void glGetBufferParameteriv(int target, int pname, int []  params) { qfn_glGetBufferParameteriv(nativehandle, target, pname, params); }
        public void glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, int []  params) { qfn_glGetFramebufferAttachmentParameteriv(nativehandle, target, attachment, pname, params); }
        public void glGetProgramiv(int program, int pname, int []  params) { qfn_glGetProgramiv(nativehandle, program, pname, params); }
        public void glGetProgramInfoLog(int program, int bufsize, int []  length, byte [] infolog) { qfn_glGetProgramInfoLog(nativehandle, program, bufsize, length, infolog); }
        public void glGetRenderbufferParameteriv(int target, int pname, int []  params) { qfn_glGetRenderbufferParameteriv(nativehandle, target, pname, params); }
        public void glGetShaderiv(int shader, int pname, int []  params) { qfn_glGetShaderiv(nativehandle, shader, pname, params); }
        public void glGetShaderInfoLog(int shader, int bufsize, int []  length, byte [] infolog) { qfn_glGetShaderInfoLog(nativehandle, shader, bufsize, length, infolog); }
        public void glGetShaderPrecisionFormat(int shadertype, int precisiontype, int []  range, int []  precision) { qfn_glGetShaderPrecisionFormat(nativehandle, shadertype, precisiontype, range, precision); }
        public void glGetShaderSource(int shader, int bufsize, int []  length, byte [] source) { qfn_glGetShaderSource(nativehandle, shader, bufsize, length, source); }
        public void glGetUniformfv(int program, int location, float []  params) { qfn_glGetUniformfv(nativehandle, program, location, params); }
        public void glGetUniformiv(int program, int location, int []  params) { qfn_glGetUniformiv(nativehandle, program, location, params); }
        public int glGetUniformLocation(int program, String name) { return qfn_glGetUniformLocation(nativehandle, program, name); }
        public void glGetVertexAttribfv(int index, int pname, float []  params) { qfn_glGetVertexAttribfv(nativehandle, index, pname, params); }
        public void glGetVertexAttribiv(int index, int pname, int []  params) { qfn_glGetVertexAttribiv(nativehandle, index, pname, params); }
        public void glGetVertexAttribPointerv(int index, int pname, long [] pointer) { qfn_glGetVertexAttribPointerv(nativehandle, index, pname, pointer); }
        public bool glIsBuffer(int buffer) { return qfn_glIsBuffer(nativehandle, buffer); }
        public bool glIsFramebuffer(int framebuffer) { return qfn_glIsFramebuffer(nativehandle, framebuffer); }
        public bool glIsProgram(int program) { return qfn_glIsProgram(nativehandle, program); }
        public bool glIsRenderbuffer(int renderbuffer) { return qfn_glIsRenderbuffer(nativehandle, renderbuffer); }
        public bool glIsShader(int shader) { return qfn_glIsShader(nativehandle, shader); }
        public void glLinkProgram(int program) { qfn_glLinkProgram(nativehandle, program); }
        public void glReleaseShaderCompiler() { qfn_glReleaseShaderCompiler(nativehandle); }
        public void glRenderbufferStorage(int target, int internalformat, int width, int height) { qfn_glRenderbufferStorage(nativehandle, target, internalformat, width, height); }
        public void glSampleCoverage(float value, bool invert) { qfn_glSampleCoverage(nativehandle, value, invert); }
        public void glShaderBinary(int n, int [] shaders, int binaryformat, byte [] binary, int length) { qfn_glShaderBinary(nativehandle, n, shaders, binaryformat, binary, length); }
        public void glShaderSource(int shader, int count, String string, int [] length) { qfn_glShaderSource(nativehandle, shader, count, string, length); }
        public void glStencilFuncSeparate(int face, int func, int ref, int mask) { qfn_glStencilFuncSeparate(nativehandle, face, func, ref, mask); }
        public void glStencilMaskSeparate(int face, int mask) { qfn_glStencilMaskSeparate(nativehandle, face, mask); }
        public void glStencilOpSeparate(int face, int fail, int zfail, int zpass) { qfn_glStencilOpSeparate(nativehandle, face, fail, zfail, zpass); }
        public void glUniform1f(int location, float x) { qfn_glUniform1f(nativehandle, location, x); }
        public void glUniform1fv(int location, int count, float [] v) { qfn_glUniform1fv(nativehandle, location, count, v); }
        public void glUniform1i(int location, int x) { qfn_glUniform1i(nativehandle, location, x); }
        public void glUniform1iv(int location, int count, int [] v) { qfn_glUniform1iv(nativehandle, location, count, v); }
        public void glUniform2f(int location, float x, float y) { qfn_glUniform2f(nativehandle, location, x, y); }
        public void glUniform2fv(int location, int count, float [] v) { qfn_glUniform2fv(nativehandle, location, count, v); }
        public void glUniform2i(int location, int x, int y) { qfn_glUniform2i(nativehandle, location, x, y); }
        public void glUniform2iv(int location, int count, int [] v) { qfn_glUniform2iv(nativehandle, location, count, v); }
        public void glUniform3f(int location, float x, float y, float z) { qfn_glUniform3f(nativehandle, location, x, y, z); }
        public void glUniform3fv(int location, int count, float [] v) { qfn_glUniform3fv(nativehandle, location, count, v); }
        public void glUniform3i(int location, int x, int y, int z) { qfn_glUniform3i(nativehandle, location, x, y, z); }
        public void glUniform3iv(int location, int count, int [] v) { qfn_glUniform3iv(nativehandle, location, count, v); }
        public void glUniform4f(int location, float x, float y, float z, float w) { qfn_glUniform4f(nativehandle, location, x, y, z, w); }
        public void glUniform4fv(int location, int count, float [] v) { qfn_glUniform4fv(nativehandle, location, count, v); }
        public void glUniform4i(int location, int x, int y, int z, int w) { qfn_glUniform4i(nativehandle, location, x, y, z, w); }
        public void glUniform4iv(int location, int count, int [] v) { qfn_glUniform4iv(nativehandle, location, count, v); }
        public void glUniformMatrix2fv(int location, int count, bool transpose, float [] value) { qfn_glUniformMatrix2fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix3fv(int location, int count, bool transpose, float [] value) { qfn_glUniformMatrix3fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix4fv(int location, int count, bool transpose, float [] value) { qfn_glUniformMatrix4fv(nativehandle, location, count, transpose, value); }
        public void glUseProgram(int program) { qfn_glUseProgram(nativehandle, program); }
        public void glValidateProgram(int program) { qfn_glValidateProgram(nativehandle, program); }
        public void glVertexAttrib1f(int indx, float x) { qfn_glVertexAttrib1f(nativehandle, indx, x); }
        public void glVertexAttrib1fv(int indx, float [] values) { qfn_glVertexAttrib1fv(nativehandle, indx, values); }
        public void glVertexAttrib2f(int indx, float x, float y) { qfn_glVertexAttrib2f(nativehandle, indx, x, y); }
        public void glVertexAttrib2fv(int indx, float [] values) { qfn_glVertexAttrib2fv(nativehandle, indx, values); }
        public void glVertexAttrib3f(int indx, float x, float y, float z) { qfn_glVertexAttrib3f(nativehandle, indx, x, y, z); }
        public void glVertexAttrib3fv(int indx, float [] values) { qfn_glVertexAttrib3fv(nativehandle, indx, values); }
        public void glVertexAttrib4f(int indx, float x, float y, float z, float w) { qfn_glVertexAttrib4f(nativehandle, indx, x, y, z, w); }
        public void glVertexAttrib4fv(int indx, float [] values) { qfn_glVertexAttrib4fv(nativehandle, indx, values); }
        public void glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, Object ptr){ qfn_glVertexAttribPointer(nativehandle, indx, size, type, normalized, stride, ptr); }

        public import "libQXLibrary"{
            void cdecl qfn_glBindTexture(long nativehandle, int target, int texture) ;
            void cdecl qfn_glBlendFunc(long nativehandle, int sfactor, int dfactor) ;
            void cdecl qfn_glClear(long nativehandle, int mask) ;
            void cdecl qfn_glClearColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_glClearStencil(long nativehandle, int s) ;
            void cdecl qfn_glColorMask(long nativehandle, bool red, bool green, bool blue, bool alpha) ;
            void cdecl qfn_glCopyTexImage2D(long nativehandle, int target, int level, int internalformat, int x, int y, int width, int height, int border) ;
            void cdecl qfn_glCopyTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) ;
            void cdecl qfn_glCullFace(long nativehandle, int mode) ;
            void cdecl qfn_glDeleteTextures(long nativehandle, int n, int *  textures) ;
            void cdecl qfn_glDepthFunc(long nativehandle, int func) ;
            void cdecl qfn_glDepthMask(long nativehandle, bool flag) ;
            void cdecl qfn_glDisable(long nativehandle, int cap) ;
            void cdecl qfn_glDrawArrays(long nativehandle, int mode, int first, int count) ;
            void cdecl qfn_glDrawElements(long nativehandle, int mode, int count, int type, byte *  indices) ;
            void cdecl qfn_glEnable(long nativehandle, int cap) ;
            void cdecl qfn_glFinish(long nativehandle) ;
            void cdecl qfn_glFlush(long nativehandle) ;
            void cdecl qfn_glFrontFace(long nativehandle, int mode) ;
            void cdecl qfn_glGenTextures(long nativehandle, int n, int *  textures) ;
            bool cdecl qfn_glGetBooleanv(long nativehandle, int pname) ;
            int cdecl qfn_glGetError(long nativehandle) ;
            float cdecl qfn_glGetFloatv(long nativehandle, int pname) ;
            int cdecl qfn_glGetIntegerv(long nativehandle, int pname) ;
            String cdecl qfn_glGetString(long nativehandle, int name) ;
            float cdecl qfn_glGetTexParameterfv(long nativehandle, int target, int pname) ;
            int cdecl qfn_glGetTexParameteriv(long nativehandle, int target, int pname) ;
            void cdecl qfn_glHint(long nativehandle, int target, int mode) ;
            bool cdecl qfn_glIsEnabled(long nativehandle, int cap) ;
            bool cdecl qfn_glIsTexture(long nativehandle, int texture) ;
            void cdecl qfn_glLineWidth(long nativehandle, float width) ;
            void cdecl qfn_glPixelStorei(long nativehandle, int pname, int param) ;
            void cdecl qfn_glPolygonOffset(long nativehandle, float factor, float units) ;
            void cdecl qfn_glReadPixels(long nativehandle, int x, int y, int width, int height, int format, int type, byte * pixels) ;
            void cdecl qfn_glScissor(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_glStencilFunc(long nativehandle, int func, int ref, int mask) ;
            void cdecl qfn_glStencilMask(long nativehandle, int mask) ;
            void cdecl qfn_glStencilOp(long nativehandle, int fail, int zfail, int zpass) ;
            void cdecl qfn_glTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, byte * pixels) ;
            void cdecl qfn_glTexParameterf(long nativehandle, int target, int pname, float param) ;
            void cdecl qfn_glTexParameterfv(long nativehandle, int target, int pname, float * params) ;
            void cdecl qfn_glTexParameteri(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_glTexParameteriv(long nativehandle, int target, int pname, int * params) ;
            void cdecl qfn_glTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, byte * pixels) ;
            void cdecl qfn_glViewport(long nativehandle, int x, int y, int width, int height) ;
            void cdecl qfn_glActiveTexture(long nativehandle, int texture) ;
            void cdecl qfn_glAttachShader(long nativehandle, int program, int shader) ;
            void cdecl qfn_glBindAttribLocation(long nativehandle, int program, int index, String name) ;
            void cdecl qfn_glBindBuffer(long nativehandle, int target, int buffer) ;
            void cdecl qfn_glBindFramebuffer(long nativehandle, int target, int framebuffer) ;
            void cdecl qfn_glBindRenderbuffer(long nativehandle, int target, int renderbuffer) ;
            void cdecl qfn_glBlendColor(long nativehandle, float red, float green, float blue, float alpha) ;
            void cdecl qfn_glBlendEquation(long nativehandle, int mode) ;
            void cdecl qfn_glBlendEquationSeparate(long nativehandle, int modeRGB, int modeAlpha) ;
            void cdecl qfn_glBlendFuncSeparate(long nativehandle, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) ;
            void cdecl qfn_glBufferData(long nativehandle, int target, int size, ObjectPtr data, int usage) ;
            void cdecl qfn_glBufferSubData(long nativehandle, int target, int offset, int size, byte * data) ;
            int cdecl qfn_glCheckFramebufferStatus(long nativehandle, int target) ;
            void cdecl qfn_glClearDepthf(long nativehandle, float depth) ;
            void cdecl qfn_glCompileShader(long nativehandle, int shader) ;
            void cdecl qfn_glCompressedTexImage2D(long nativehandle, int target, int level, int internalformat, int width, int height, int border, int imageSize, byte * data) ;
            void cdecl qfn_glCompressedTexSubImage2D(long nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, byte * data) ;
            int cdecl qfn_glCreateProgram(long nativehandle) ;
            int cdecl qfn_glCreateShader(long nativehandle, int type) ;
            void cdecl qfn_glDeleteBuffers(long nativehandle, int n, int * buffers) ;
            void cdecl qfn_glDeleteFramebuffers(long nativehandle, int n, int * framebuffers) ;
            void cdecl qfn_glDeleteProgram(long nativehandle, int program) ;
            void cdecl qfn_glDeleteRenderbuffers(long nativehandle, int n, int * renderbuffers) ;
            void cdecl qfn_glDeleteShader(long nativehandle, int shader) ;
            void cdecl qfn_glDepthRangef(long nativehandle, float zNear, float zFar) ;
            void cdecl qfn_glDetachShader(long nativehandle, int program, int shader) ;
            void cdecl qfn_glDisableVertexAttribArray(long nativehandle, int index) ;
            void cdecl qfn_glEnableVertexAttribArray(long nativehandle, int index) ;
            void cdecl qfn_glFramebufferRenderbuffer(long nativehandle, int target, int attachment, int renderbuffertarget, int renderbuffer) ;
            void cdecl qfn_glFramebufferTexture2D(long nativehandle, int target, int attachment, int textarget, int texture, int level) ;
            void cdecl qfn_glGenBuffers(long nativehandle, int n, int *  buffers) ;
            void cdecl qfn_glGenerateMipmap(long nativehandle, int target) ;
            void cdecl qfn_glGenFramebuffers(long nativehandle, int n, int *  framebuffers) ;
            void cdecl qfn_glGenRenderbuffers(long nativehandle, int n, int *  renderbuffers) ;
            void cdecl qfn_glGetActiveAttrib(long nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, byte * name) ;
            void cdecl qfn_glGetActiveUniform(long nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, byte * name) ;
            void cdecl qfn_glGetAttachedShaders(long nativehandle, int program, int maxcount, int *  count, int *  shaders) ;
            int cdecl qfn_glGetAttribLocation(long nativehandle, int program, String name) ;
            void cdecl qfn_glGetBufferParameteriv(long nativehandle, int target, int pname, int *  params) ;
            void cdecl qfn_glGetFramebufferAttachmentParameteriv(long nativehandle, int target, int attachment, int pname, int *  params) ;
            void cdecl qfn_glGetProgramiv(long nativehandle, int program, int pname, int *  params) ;
            void cdecl qfn_glGetProgramInfoLog(long nativehandle, int program, int bufsize, int *  length, byte * infolog) ;
            void cdecl qfn_glGetRenderbufferParameteriv(long nativehandle, int target, int pname, int *  params) ;
            void cdecl qfn_glGetShaderiv(long nativehandle, int shader, int pname, int *  params) ;
            void cdecl qfn_glGetShaderInfoLog(long nativehandle, int shader, int bufsize, int *  length, byte * infolog) ;
            void cdecl qfn_glGetShaderPrecisionFormat(long nativehandle, int shadertype, int precisiontype, int *  range, int *  precision) ;
            void cdecl qfn_glGetShaderSource(long nativehandle, int shader, int bufsize, int *  length, byte * source) ;
            void cdecl qfn_glGetUniformfv(long nativehandle, int program, int location, float *  params) ;
            void cdecl qfn_glGetUniformiv(long nativehandle, int program, int location, int *  params) ;
            int cdecl qfn_glGetUniformLocation(long nativehandle, int program, String name) ;
            void cdecl qfn_glGetVertexAttribfv(long nativehandle, int index, int pname, float *  params) ;
            void cdecl qfn_glGetVertexAttribiv(long nativehandle, int index, int pname, int *  params) ;
            void cdecl qfn_glGetVertexAttribPointerv(long nativehandle, int index, int pname, long * pointer) ;
            bool cdecl qfn_glIsBuffer(long nativehandle, int buffer) ;
            bool cdecl qfn_glIsFramebuffer(long nativehandle, int framebuffer) ;
            bool cdecl qfn_glIsProgram(long nativehandle, int program) ;
            bool cdecl qfn_glIsRenderbuffer(long nativehandle, int renderbuffer) ;
            bool cdecl qfn_glIsShader(long nativehandle, int shader) ;
            void cdecl qfn_glLinkProgram(long nativehandle, int program) ;
            void cdecl qfn_glReleaseShaderCompiler(long nativehandle) ;
            void cdecl qfn_glRenderbufferStorage(long nativehandle, int target, int internalformat, int width, int height) ;
            void cdecl qfn_glSampleCoverage(long nativehandle, float value, bool invert) ;
            void cdecl qfn_glShaderBinary(long nativehandle, int n, int * shaders, int binaryformat, byte * binary, int length) ;
            void cdecl qfn_glShaderSource(long nativehandle, int shader, int count, String string, int * length) ;
            void cdecl qfn_glStencilFuncSeparate(long nativehandle, int face, int func, int ref, int mask) ;
            void cdecl qfn_glStencilMaskSeparate(long nativehandle, int face, int mask) ;
            void cdecl qfn_glStencilOpSeparate(long nativehandle, int face, int fail, int zfail, int zpass) ;
            void cdecl qfn_glUniform1f(long nativehandle, int location, float x) ;
            void cdecl qfn_glUniform1fv(long nativehandle, int location, int count, float * v) ;
            void cdecl qfn_glUniform1i(long nativehandle, int location, int x) ;
            void cdecl qfn_glUniform1iv(long nativehandle, int location, int count, int * v) ;
            void cdecl qfn_glUniform2f(long nativehandle, int location, float x, float y) ;
            void cdecl qfn_glUniform2fv(long nativehandle, int location, int count, float * v) ;
            void cdecl qfn_glUniform2i(long nativehandle, int location, int x, int y) ;
            void cdecl qfn_glUniform2iv(long nativehandle, int location, int count, int * v) ;
            void cdecl qfn_glUniform3f(long nativehandle, int location, float x, float y, float z) ;
            void cdecl qfn_glUniform3fv(long nativehandle, int location, int count, float * v) ;
            void cdecl qfn_glUniform3i(long nativehandle, int location, int x, int y, int z) ;
            void cdecl qfn_glUniform3iv(long nativehandle, int location, int count, int * v) ;
            void cdecl qfn_glUniform4f(long nativehandle, int location, float x, float y, float z, float w) ;
            void cdecl qfn_glUniform4fv(long nativehandle, int location, int count, float * v) ;
            void cdecl qfn_glUniform4i(long nativehandle, int location, int x, int y, int z, int w) ;
            void cdecl qfn_glUniform4iv(long nativehandle, int location, int count, int * v) ;
            void cdecl qfn_glUniformMatrix2fv(long nativehandle, int location, int count, bool transpose, float * value) ;
            void cdecl qfn_glUniformMatrix3fv(long nativehandle, int location, int count, bool transpose, float * value) ;
            void cdecl qfn_glUniformMatrix4fv(long nativehandle, int location, int count, bool transpose, float * value) ;
            void cdecl qfn_glUseProgram(long nativehandle, int program) ;
            void cdecl qfn_glValidateProgram(long nativehandle, int program) ;
            void cdecl qfn_glVertexAttrib1f(long nativehandle, int indx, float x) ;
            void cdecl qfn_glVertexAttrib1fv(long nativehandle, int indx, float * values) ;
            void cdecl qfn_glVertexAttrib2f(long nativehandle, int indx, float x, float y) ;
            void cdecl qfn_glVertexAttrib2fv(long nativehandle, int indx, float * values) ;
            void cdecl qfn_glVertexAttrib3f(long nativehandle, int indx, float x, float y, float z) ;
            void cdecl qfn_glVertexAttrib3fv(long nativehandle, int indx, float * values) ;
            void cdecl qfn_glVertexAttrib4f(long nativehandle, int indx, float x, float y, float z, float w) ;
            void cdecl qfn_glVertexAttrib4fv(long nativehandle, int indx, float * values) ;
            void cdecl qfn_glVertexAttribPointer(long nativehandle, int indx, int size, int type, bool normalized, int stride, ObjectPtr ptr) ;
        };
        

    };
};