//xlang Source, Name:qt5/widgets/QOpenGLExtraFunctions.x 
//Date: Tue Mar 14:49:50 2021 

package Qt{
    public class QOpenGLExtraFunctions : QOpenGLFunctions{
        public QOpenGLExtraFunctions(){
            
        }
        public QOpenGLExtraFunctions(long h){
            super(h);
            if (h == 0){
                throw new IllegalArgumentException("could not new Object");
            }
        }
        // GLES3
        public void glReadBuffer(int mode){ qfn_glReadBuffer(nativehandle, mode); }
        public void glDrawRangeElements(int mode, int start, int end, int count, int type,  byte  [] indices){ qfn_glDrawRangeElements(nativehandle, mode, start, end, count, type, indices); }
        public void glTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int format, int type,  byte  [] pixels){ qfn_glTexImage3D(nativehandle, target, level, internalformat, width, height, depth, border, format, type, pixels); }
        public void glTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type,  byte  [] pixels){ qfn_glTexSubImage3D(nativehandle, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
        public void glCopyTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int x, int y, int width, int height){ qfn_glCopyTexSubImage3D(nativehandle, target, level, xoffset, yoffset, zoffset, x, y, width, height); }
        public void glCompressedTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int imageSize,  byte  [] data){ qfn_glCompressedTexImage3D(nativehandle, target, level, internalformat, width, height, depth, border, imageSize, data); }
        public void glCompressedTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int imageSize,  byte  [] data){ qfn_glCompressedTexSubImage3D(nativehandle, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
        public void glGenQueries(int n, int  [] ids){ qfn_glGenQueries(nativehandle, n, ids); }
        public void glDeleteQueries(int n,  int  [] ids){ qfn_glDeleteQueries(nativehandle, n, ids); }
        public bool glIsQuery(int id){ return qfn_glIsQuery(nativehandle, id); }
        public void glBeginQuery(int target, int id){ qfn_glBeginQuery(nativehandle, target, id); }
        public void glEndQuery(int target){ qfn_glEndQuery(nativehandle, target); }
        public void glGetQueryiv(int target, int pname, int  [] params){ qfn_glGetQueryiv(nativehandle, target, pname, params); }
        public void glGetQueryObjectuiv(int id, int pname, int  [] params){ qfn_glGetQueryObjectuiv(nativehandle, id, pname, params); }
        public bool glUnmapBuffer(int target){ return qfn_glUnmapBuffer(nativehandle, target); }
        public void glGetBufferPointerv(int target, int pname, long  [] params){ qfn_glGetBufferPointerv(nativehandle, target, pname, params); }
        public void glDrawBuffers(int n,  int  [] bufs){ qfn_glDrawBuffers(nativehandle, n, bufs); }
        public void glUniformMatrix2x3fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix2x3fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix3x2fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix3x2fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix2x4fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix2x4fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix4x2fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix4x2fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix3x4fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix3x4fv(nativehandle, location, count, transpose, value); }
        public void glUniformMatrix4x3fv(int location, int count, bool transpose,  float  [] value){ qfn_glUniformMatrix4x3fv(nativehandle, location, count, transpose, value); }
        public void glBlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter){ qfn_glBlitFramebuffer(nativehandle, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
        public void glRenderbufferStorageMultisample(int target, int samples, int internalformat, int width, int height){ qfn_glRenderbufferStorageMultisample(nativehandle, target, samples, internalformat, width, height); }
        public void glFramebufferTextureLayer(int target, int attachment, int texture, int level, int layer){ qfn_glFramebufferTextureLayer(nativehandle, target, attachment, texture, level, layer); }
        public Pointer glMapBufferRange(int target, long offset, Pointer length, int access){ return qfn_glMapBufferRange(nativehandle, target, offset, length, access); }
        public void glFlushMappedBufferRange(int target, long offset, Pointer length){ qfn_glFlushMappedBufferRange(nativehandle, target, offset, length); }
        public void glBindVertexArray(int array){ qfn_glBindVertexArray(nativehandle, array); }
        public void glDeleteVertexArrays(int n,  int  [] arrays){ qfn_glDeleteVertexArrays(nativehandle, n, arrays); }
        public void glGenVertexArrays(int n, int  [] arrays){ qfn_glGenVertexArrays(nativehandle, n, arrays); }
        public bool glIsVertexArray(int array){ return qfn_glIsVertexArray(nativehandle, array); }
        public void glGetIntegeri_v(int target, int index, int  [] data){ qfn_glGetIntegeri_v(nativehandle, target, index, data); }
        public void glBeginTransformFeedback(int primitiveMode){ qfn_glBeginTransformFeedback(nativehandle, primitiveMode); }
        public void glEndTransformFeedback(){ qfn_glEndTransformFeedback(nativehandle); }
        public void glBindBufferRange(int target, int index, int buffer, long offset, Pointer size){ qfn_glBindBufferRange(nativehandle, target, index, buffer, offset, size); }
        public void glBindBufferBase(int target, int index, int buffer){ qfn_glBindBufferBase(nativehandle, target, index, buffer); }
        public void glTransformFeedbackVaryings(int program, int count, String varyings, int bufferMode){ qfn_glTransformFeedbackVaryings(nativehandle, program, count, varyings, bufferMode); }
        public void glGetTransformFeedbackVarying(int program, int index, int bufSize, int  [] length, int  [] size, int  [] type, byte  [] name){ qfn_glGetTransformFeedbackVarying(nativehandle, program, index, bufSize, length, size, type, name); }
        public void glVertexAttribIPointer(int index, int size, int type, int stride,  byte  [] pointer){ qfn_glVertexAttribIPointer(nativehandle, index, size, type, stride, pointer); }
        public void glGetVertexAttribIiv(int index, int pname, int  [] params){ qfn_glGetVertexAttribIiv(nativehandle, index, pname, params); }
        public void glGetVertexAttribIuiv(int index, int pname, int  [] params){ qfn_glGetVertexAttribIuiv(nativehandle, index, pname, params); }
        public void glVertexAttribI4i(int index, int x, int y, int z, int w){ qfn_glVertexAttribI4i(nativehandle, index, x, y, z, w); }
        public void glVertexAttribI4ui(int index, int x, int y, int z, int w){ qfn_glVertexAttribI4ui(nativehandle, index, x, y, z, w); }
        public void glVertexAttribI4iv(int index,  int  [] v){ qfn_glVertexAttribI4iv(nativehandle, index, v); }
        public void glVertexAttribI4uiv(int index,  int  [] v){ qfn_glVertexAttribI4uiv(nativehandle, index, v); }
        public void glGetUniformuiv(int program, int location, int  [] params){ qfn_glGetUniformuiv(nativehandle, program, location, params); }
        public int glGetFragDataLocation(int program,  String name){ return qfn_glGetFragDataLocation(nativehandle, program, name); }
        public void glUniform1ui(int location, int v0){ qfn_glUniform1ui(nativehandle, location, v0); }
        public void glUniform2ui(int location, int v0, int v1){ qfn_glUniform2ui(nativehandle, location, v0, v1); }
        public void glUniform3ui(int location, int v0, int v1, int v2){ qfn_glUniform3ui(nativehandle, location, v0, v1, v2); }
        public void glUniform4ui(int location, int v0, int v1, int v2, int v3){ qfn_glUniform4ui(nativehandle, location, v0, v1, v2, v3); }
        public void glUniform1uiv(int location, int count,  int  [] value){ qfn_glUniform1uiv(nativehandle, location, count, value); }
        public void glUniform2uiv(int location, int count,  int  [] value){ qfn_glUniform2uiv(nativehandle, location, count, value); }
        public void glUniform3uiv(int location, int count,  int  [] value){ qfn_glUniform3uiv(nativehandle, location, count, value); }
        public void glUniform4uiv(int location, int count,  int  [] value){ qfn_glUniform4uiv(nativehandle, location, count, value); }
        public void glClearBufferiv(int buffer, int drawbuffer,  int  [] value){ qfn_glClearBufferiv(nativehandle, buffer, drawbuffer, value); }
        public void glClearBufferuiv(int buffer, int drawbuffer,  int  [] value){ qfn_glClearBufferuiv(nativehandle, buffer, drawbuffer, value); }
        public void glClearBufferfv(int buffer, int drawbuffer,  float  [] value){ qfn_glClearBufferfv(nativehandle, buffer, drawbuffer, value); }
        public void glClearBufferfi(int buffer, int drawbuffer, float depth, int stencil){ qfn_glClearBufferfi(nativehandle, buffer, drawbuffer, depth, stencil); }
        public String glGetStringi(int name, int index){ return qfn_glGetStringi(nativehandle, name, index); }
        public void glCopyBufferSubData(int readTarget, int writeTarget, long readOffset, long writeOffset, Pointer size){ qfn_glCopyBufferSubData(nativehandle, readTarget, writeTarget, readOffset, writeOffset, size); }
        public void glGetUniformIndices(int program, int uniformCount,  String uniformNames, int  [] uniformIndices){ qfn_glGetUniformIndices(nativehandle, program, uniformCount, uniformNames, uniformIndices); }
        public void glGetActiveUniformsiv(int program, int uniformCount,  int  [] uniformIndices, int pname, int  [] params){ qfn_glGetActiveUniformsiv(nativehandle, program, uniformCount, uniformIndices, pname, params); }
        public int glGetUniformBlockIndex(int program,  String uniformBlockName){ return qfn_glGetUniformBlockIndex(nativehandle, program, uniformBlockName); }
        public void glGetActiveUniformBlockiv(int program, int uniformBlockIndex, int pname, int  [] params){ qfn_glGetActiveUniformBlockiv(nativehandle, program, uniformBlockIndex, pname, params); }
        public void glGetActiveUniformBlockName(int program, int uniformBlockIndex, int bufSize, int  [] length, byte  [] uniformBlockName){ qfn_glGetActiveUniformBlockName(nativehandle, program, uniformBlockIndex, bufSize, length, uniformBlockName); }
        public void glUniformBlockBinding(int program, int uniformBlockIndex, int uniformBlockBinding){ qfn_glUniformBlockBinding(nativehandle, program, uniformBlockIndex, uniformBlockBinding); }
        public void glDrawArraysInstanced(int mode, int first, int count, int instancecount){ qfn_glDrawArraysInstanced(nativehandle, mode, first, count, instancecount); }
        public void glDrawElementsInstanced(int mode, int count, int type,  byte  [] indices, int instancecount){ qfn_glDrawElementsInstanced(nativehandle, mode, count, type, indices, instancecount); }
        public Pointer glFenceSync(int condition, int flags){ return qfn_glFenceSync(nativehandle, condition, flags); }
        public bool glIsSync(Pointer sync){ return qfn_glIsSync(nativehandle, sync); }
        public void glDeleteSync(Pointer sync){ qfn_glDeleteSync(nativehandle, sync); }
        public int glClientWaitSync(Pointer sync, int flags, long timeout){ return qfn_glClientWaitSync(nativehandle, sync, flags, timeout); }
        public void glWaitSync(Pointer sync, int flags, long timeout){ qfn_glWaitSync(nativehandle, sync, flags, timeout); }
        public void glGetInteger64v(int pname, long  [] data){ qfn_glGetInteger64v(nativehandle, pname, data); }
        public void glGetSynciv(Pointer sync, int pname, int bufSize, int  [] length, int  [] values){ qfn_glGetSynciv(nativehandle, sync, pname, bufSize, length, values); }
        public void glGetInteger64i_v(int target, int index, long  [] data){ qfn_glGetInteger64i_v(nativehandle, target, index, data); }
        public void glGetBufferParameteri64v(int target, int pname, long  [] params){ qfn_glGetBufferParameteri64v(nativehandle, target, pname, params); }
        public void glGenSamplers(int count, int  [] samplers){ qfn_glGenSamplers(nativehandle, count, samplers); }
        public void glDeleteSamplers(int count,  int  [] samplers){ qfn_glDeleteSamplers(nativehandle, count, samplers); }
        public bool glIsSampler(int sampler){ return qfn_glIsSampler(nativehandle, sampler); }
        public void glBindSampler(int unit, int sampler){ qfn_glBindSampler(nativehandle, unit, sampler); }
        public void glSamplerParameteri(int sampler, int pname, int param){ qfn_glSamplerParameteri(nativehandle, sampler, pname, param); }
        public void glSamplerParameteriv(int sampler, int pname,  int  [] param){ qfn_glSamplerParameteriv(nativehandle, sampler, pname, param); }
        public void glSamplerParameterf(int sampler, int pname, float param){ qfn_glSamplerParameterf(nativehandle, sampler, pname, param); }
        public void glSamplerParameterfv(int sampler, int pname,  float  [] param){ qfn_glSamplerParameterfv(nativehandle, sampler, pname, param); }
        public void glGetSamplerParameteriv(int sampler, int pname, int  [] params){ qfn_glGetSamplerParameteriv(nativehandle, sampler, pname, params); }
        public void glGetSamplerParameterfv(int sampler, int pname, float  [] params){ qfn_glGetSamplerParameterfv(nativehandle, sampler, pname, params); }
        public void glVertexAttribDivisor(int index, int divisor){ qfn_glVertexAttribDivisor(nativehandle, index, divisor); }
        public void glBindTransformFeedback(int target, int id){ qfn_glBindTransformFeedback(nativehandle, target, id); }
        public void glDeleteTransformFeedbacks(int n,  int  [] ids){ qfn_glDeleteTransformFeedbacks(nativehandle, n, ids); }
        public void glGenTransformFeedbacks(int n, int  [] ids){ qfn_glGenTransformFeedbacks(nativehandle, n, ids); }
        public bool glIsTransformFeedback(int id){ return qfn_glIsTransformFeedback(nativehandle, id); }
        public void glPauseTransformFeedback(){ qfn_glPauseTransformFeedback(nativehandle); }
        public void glResumeTransformFeedback(){ qfn_glResumeTransformFeedback(nativehandle); }
        public void glGetProgramBinary(int program, int bufSize, int  [] length, int  [] binaryFormat, byte  [] binary){ qfn_glGetProgramBinary(nativehandle, program, bufSize, length, binaryFormat, binary); }
        public void glProgramBinary(int program, int binaryFormat,  byte  [] binary, int length){ qfn_glProgramBinary(nativehandle, program, binaryFormat, binary, length); }
        public void glProgramParameteri(int program, int pname, int value){ qfn_glProgramParameteri(nativehandle, program, pname, value); }
        public void glInvalidateFramebuffer(int target, int numAttachments,  int  [] attachments){ qfn_glInvalidateFramebuffer(nativehandle, target, numAttachments, attachments); }
        public void glInvalidateSubFramebuffer(int target, int numAttachments,  int  [] attachments, int x, int y, int width, int height){ qfn_glInvalidateSubFramebuffer(nativehandle, target, numAttachments, attachments, x, y, width, height); }
        public void glTexStorage2D(int target, int levels, int internalformat, int width, int height){ qfn_glTexStorage2D(nativehandle, target, levels, internalformat, width, height); }
        public void glTexStorage3D(int target, int levels, int internalformat, int width, int height, int depth){ qfn_glTexStorage3D(nativehandle, target, levels, internalformat, width, height, depth); }
        public void glGetInternalformativ(int target, int internalformat, int pname, int bufSize, int  [] params){ qfn_glGetInternalformativ(nativehandle, target, internalformat, pname, bufSize, params); }
        public void glDispatchCompute(int num_groups_x, int num_groups_y, int num_groups_z){ qfn_glDispatchCompute(nativehandle, num_groups_x, num_groups_y, num_groups_z); }
        public void glDispatchComputeIndirect(long indirect){ qfn_glDispatchComputeIndirect(nativehandle, indirect); }
        public void glDrawArraysIndirect(int mode,  byte  [] indirect){ qfn_glDrawArraysIndirect(nativehandle, mode, indirect); }
        public void glDrawElementsIndirect(int mode, int type,  byte  [] indirect){ qfn_glDrawElementsIndirect(nativehandle, mode, type, indirect); }
        public void glFramebufferParameteri(int target, int pname, int param){ qfn_glFramebufferParameteri(nativehandle, target, pname, param); }
        public void glGetFramebufferParameteriv(int target, int pname, int  [] params){ qfn_glGetFramebufferParameteriv(nativehandle, target, pname, params); }
        public void glGetProgramInterfaceiv(int program, int programInterface, int pname, int  [] params){ qfn_glGetProgramInterfaceiv(nativehandle, program, programInterface, pname, params); }
        public int glGetProgramResourceIndex(int program, int programInterface,  String name){ return qfn_glGetProgramResourceIndex(nativehandle, program, programInterface, name); }
        public void glGetProgramResourceName(int program, int programInterface, int index, int bufSize, int  [] length, byte  [] name){ qfn_glGetProgramResourceName(nativehandle, program, programInterface, index, bufSize, length, name); }
        public void glGetProgramResourceiv(int program, int programInterface, int index, int propCount,  int  [] props, int bufSize, int  [] length, int  [] params){ qfn_glGetProgramResourceiv(nativehandle, program, programInterface, index, propCount, props, bufSize, length, params); }
        public int glGetProgramResourceLocation(int program, int programInterface,  String name){ return qfn_glGetProgramResourceLocation(nativehandle, program, programInterface, name); }
        public void glUseProgramStages(int pipeline, int stages, int program){ qfn_glUseProgramStages(nativehandle, pipeline, stages, program); }
        public void glActiveShaderProgram(int pipeline, int program){ qfn_glActiveShaderProgram(nativehandle, pipeline, program); }
        public int glCreateShaderProgramv(int type, int count,  String strings){ return qfn_glCreateShaderProgramv(nativehandle, type, count, strings); }
        public void glBindProgramPipeline(int pipeline){ qfn_glBindProgramPipeline(nativehandle, pipeline); }
        public void glDeleteProgramPipelines(int n,  int  [] pipelines){ qfn_glDeleteProgramPipelines(nativehandle, n, pipelines); }
        public void glGenProgramPipelines(int n, int  [] pipelines){ qfn_glGenProgramPipelines(nativehandle, n, pipelines); }
        public bool glIsProgramPipeline(int pipeline){ return qfn_glIsProgramPipeline(nativehandle, pipeline); }
        public void glGetProgramPipelineiv(int pipeline, int pname, int  [] params){ qfn_glGetProgramPipelineiv(nativehandle, pipeline, pname, params); }
        public void glProgramUniform1i(int program, int location, int v0){ qfn_glProgramUniform1i(nativehandle, program, location, v0); }
        public void glProgramUniform2i(int program, int location, int v0, int v1){ qfn_glProgramUniform2i(nativehandle, program, location, v0, v1); }
        public void glProgramUniform3i(int program, int location, int v0, int v1, int v2){ qfn_glProgramUniform3i(nativehandle, program, location, v0, v1, v2); }
        public void glProgramUniform4i(int program, int location, int v0, int v1, int v2, int v3){ qfn_glProgramUniform4i(nativehandle, program, location, v0, v1, v2, v3); }
        public void glProgramUniform1ui(int program, int location, int v0){ qfn_glProgramUniform1ui(nativehandle, program, location, v0); }
        public void glProgramUniform2ui(int program, int location, int v0, int v1){ qfn_glProgramUniform2ui(nativehandle, program, location, v0, v1); }
        public void glProgramUniform3ui(int program, int location, int v0, int v1, int v2){ qfn_glProgramUniform3ui(nativehandle, program, location, v0, v1, v2); }
        public void glProgramUniform4ui(int program, int location, int v0, int v1, int v2, int v3){ qfn_glProgramUniform4ui(nativehandle, program, location, v0, v1, v2, v3); }
        public void glProgramUniform1f(int program, int location, float v0){ qfn_glProgramUniform1f(nativehandle, program, location, v0); }
        public void glProgramUniform2f(int program, int location, float v0, float v1){ qfn_glProgramUniform2f(nativehandle, program, location, v0, v1); }
        public void glProgramUniform3f(int program, int location, float v0, float v1, float v2){ qfn_glProgramUniform3f(nativehandle, program, location, v0, v1, v2); }
        public void glProgramUniform4f(int program, int location, float v0, float v1, float v2, float v3){ qfn_glProgramUniform4f(nativehandle, program, location, v0, v1, v2, v3); }
        public void glProgramUniform1iv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform1iv(nativehandle, program, location, count, value); }
        public void glProgramUniform2iv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform2iv(nativehandle, program, location, count, value); }
        public void glProgramUniform3iv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform3iv(nativehandle, program, location, count, value); }
        public void glProgramUniform4iv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform4iv(nativehandle, program, location, count, value); }
        public void glProgramUniform1uiv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform1uiv(nativehandle, program, location, count, value); }
        public void glProgramUniform2uiv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform2uiv(nativehandle, program, location, count, value); }
        public void glProgramUniform3uiv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform3uiv(nativehandle, program, location, count, value); }
        public void glProgramUniform4uiv(int program, int location, int count,  int  [] value){ qfn_glProgramUniform4uiv(nativehandle, program, location, count, value); }
        public void glProgramUniform1fv(int program, int location, int count,  float  [] value){ qfn_glProgramUniform1fv(nativehandle, program, location, count, value); }
        public void glProgramUniform2fv(int program, int location, int count,  float  [] value){ qfn_glProgramUniform2fv(nativehandle, program, location, count, value); }
        public void glProgramUniform3fv(int program, int location, int count,  float  [] value){ qfn_glProgramUniform3fv(nativehandle, program, location, count, value); }
        public void glProgramUniform4fv(int program, int location, int count,  float  [] value){ qfn_glProgramUniform4fv(nativehandle, program, location, count, value); }
        public void glProgramUniformMatrix2fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix2fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix3fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix3fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix4fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix4fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix2x3fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix2x3fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix3x2fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix3x2fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix2x4fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix2x4fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix4x2fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix4x2fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix3x4fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix3x4fv(nativehandle, program, location, count, transpose, value); }
        public void glProgramUniformMatrix4x3fv(int program, int location, int count, bool transpose,  float  [] value){ qfn_glProgramUniformMatrix4x3fv(nativehandle, program, location, count, transpose, value); }
        public void glValidateProgramPipeline(int pipeline){ qfn_glValidateProgramPipeline(nativehandle, pipeline); }
        public void glGetProgramPipelineInfoLog(int pipeline, int bufSize, int  [] length, byte  [] infoLog){ qfn_glGetProgramPipelineInfoLog(nativehandle, pipeline, bufSize, length, infoLog); }
        public void glBindImageTexture(int unit, int texture, int level, bool layered, int layer, int access, int format){ qfn_glBindImageTexture(nativehandle, unit, texture, level, layered, layer, access, format); }
        public void glGetBooleani_v(int target, int index, bool  [] data){ qfn_glGetBooleani_v(nativehandle, target, index, data); }
        public void glMemoryBarrier(int barriers){ qfn_glMemoryBarrier(nativehandle, barriers); }
        public void glMemoryBarrierByRegion(int barriers){ qfn_glMemoryBarrierByRegion(nativehandle, barriers); }
        public void glTexStorage2DMultisample(int target, int samples, int internalformat, int width, int height, bool fixedsamplelocations){ qfn_glTexStorage2DMultisample(nativehandle, target, samples, internalformat, width, height, fixedsamplelocations); }
        public void glGetMultisamplefv(int pname, int index, float  [] val){ qfn_glGetMultisamplefv(nativehandle, pname, index, val); }
        public void glSampleMaski(int maskNumber, int mask){ qfn_glSampleMaski(nativehandle, maskNumber, mask); }
        public void glGetTexLevelParameteriv(int target, int level, int pname, int  [] params){ qfn_glGetTexLevelParameteriv(nativehandle, target, level, pname, params); }
        public void glGetTexLevelParameterfv(int target, int level, int pname, float  [] params){ qfn_glGetTexLevelParameterfv(nativehandle, target, level, pname, params); }
        public void glBindVertexBuffer(int bindingindex, int buffer, long offset, int stride){ qfn_glBindVertexBuffer(nativehandle, bindingindex, buffer, offset, stride); }
        public void glVertexAttribFormat(int attribindex, int size, int type, bool normalized, int relativeoffset){ qfn_glVertexAttribFormat(nativehandle, attribindex, size, type, normalized, relativeoffset); }
        public void glVertexAttribIFormat(int attribindex, int size, int type, int relativeoffset){ qfn_glVertexAttribIFormat(nativehandle, attribindex, size, type, relativeoffset); }
        public void glVertexAttribBinding(int attribindex, int bindingindex){ qfn_glVertexAttribBinding(nativehandle, attribindex, bindingindex); }
        public void glVertexBindingDivisor(int bindingindex, int divisor){ qfn_glVertexBindingDivisor(nativehandle, bindingindex, divisor); }
        
        public import "libQXLibrary"{
            void cdecl qfn_glReadBuffer(long nativehandle, int mode) ;
            void cdecl qfn_glDrawRangeElements(long nativehandle, int mode, int start, int end, int count, int type, byte  * indices) ;
            void cdecl qfn_glTexImage3D(long nativehandle, int target, int level, int internalformat, int width, int height, int depth, int border, int format, int type, byte  * pixels) ;
            void cdecl qfn_glTexSubImage3D(long nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type, byte  * pixels) ;
            void cdecl qfn_glCopyTexSubImage3D(long nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int x, int y, int width, int height) ;
            void cdecl qfn_glCompressedTexImage3D(long nativehandle, int target, int level, int internalformat, int width, int height, int depth, int border, int imageSize, byte  * data) ;
            void cdecl qfn_glCompressedTexSubImage3D(long nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int imageSize, byte  * data) ;
            void cdecl qfn_glGenQueries(long nativehandle, int n, int  * ids) ;
            void cdecl qfn_glDeleteQueries(long nativehandle, int n, int  * ids) ;
            bool cdecl qfn_glIsQuery(long nativehandle, int id) ;
            void cdecl qfn_glBeginQuery(long nativehandle, int target, int id) ;
            void cdecl qfn_glEndQuery(long nativehandle, int target) ;
            void cdecl qfn_glGetQueryiv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_glGetQueryObjectuiv(long nativehandle, int id, int pname, int  * params) ;
            bool cdecl qfn_glUnmapBuffer(long nativehandle, int target) ;
            void cdecl qfn_glGetBufferPointerv(long nativehandle, int target, int pname, long* params) ;
            void cdecl qfn_glDrawBuffers(long nativehandle, int n, int  * bufs) ;
            void cdecl qfn_glUniformMatrix2x3fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glUniformMatrix3x2fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glUniformMatrix2x4fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glUniformMatrix4x2fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glUniformMatrix3x4fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glUniformMatrix4x3fv(long nativehandle, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glBlitFramebuffer(long nativehandle, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter) ;
            void cdecl qfn_glRenderbufferStorageMultisample(long nativehandle, int target, int samples, int internalformat, int width, int height) ;
            void cdecl qfn_glFramebufferTextureLayer(long nativehandle, int target, int attachment, int texture, int level, int layer) ;
            Pointer cdecl qfn_glMapBufferRange(long nativehandle, int target, long offset, Pointer length, int access) ;
            void cdecl qfn_glFlushMappedBufferRange(long nativehandle, int target, long offset, Pointer length) ;
            void cdecl qfn_glBindVertexArray(long nativehandle, int array) ;
            void cdecl qfn_glDeleteVertexArrays(long nativehandle, int n, int  * arrays) ;
            void cdecl qfn_glGenVertexArrays(long nativehandle, int n, int  * arrays) ;
            bool cdecl qfn_glIsVertexArray(long nativehandle, int array) ;
            void cdecl qfn_glGetIntegeri_v(long nativehandle, int target, int index, int  * data) ;
            void cdecl qfn_glBeginTransformFeedback(long nativehandle, int primitiveMode) ;
            void cdecl qfn_glEndTransformFeedback(long nativehandle) ;
            void cdecl qfn_glBindBufferRange(long nativehandle, int target, int index, int buffer, long offset, Pointer size) ;
            void cdecl qfn_glBindBufferBase(long nativehandle, int target, int index, int buffer) ;
            void cdecl qfn_glTransformFeedbackVaryings(long nativehandle, int program, int count, String varyings, int bufferMode) ;
            void cdecl qfn_glGetTransformFeedbackVarying(long nativehandle, int program, int index, int bufSize, int  * length, int  * size, int  * type, byte  * name) ;
            void cdecl qfn_glVertexAttribIPointer(long nativehandle, int index, int size, int type, int stride, byte  * pointer) ;
            void cdecl qfn_glGetVertexAttribIiv(long nativehandle, int index, int pname, int  * params) ;
            void cdecl qfn_glGetVertexAttribIuiv(long nativehandle, int index, int pname, int  * params) ;
            void cdecl qfn_glVertexAttribI4i(long nativehandle, int index, int x, int y, int z, int w) ;
            void cdecl qfn_glVertexAttribI4ui(long nativehandle, int index, int x, int y, int z, int w) ;
            void cdecl qfn_glVertexAttribI4iv(long nativehandle, int index, int  * v) ;
            void cdecl qfn_glVertexAttribI4uiv(long nativehandle, int index, int  * v) ;
            void cdecl qfn_glGetUniformuiv(long nativehandle, int program, int location, int  * params) ;
            int cdecl qfn_glGetFragDataLocation(long nativehandle, int program, String name) ;
            void cdecl qfn_glUniform1ui(long nativehandle, int location, int v0) ;
            void cdecl qfn_glUniform2ui(long nativehandle, int location, int v0, int v1) ;
            void cdecl qfn_glUniform3ui(long nativehandle, int location, int v0, int v1, int v2) ;
            void cdecl qfn_glUniform4ui(long nativehandle, int location, int v0, int v1, int v2, int v3) ;
            void cdecl qfn_glUniform1uiv(long nativehandle, int location, int count, int  * value) ;
            void cdecl qfn_glUniform2uiv(long nativehandle, int location, int count, int  * value) ;
            void cdecl qfn_glUniform3uiv(long nativehandle, int location, int count, int  * value) ;
            void cdecl qfn_glUniform4uiv(long nativehandle, int location, int count, int  * value) ;
            void cdecl qfn_glClearBufferiv(long nativehandle, int buffer, int drawbuffer, int  * value) ;
            void cdecl qfn_glClearBufferuiv(long nativehandle, int buffer, int drawbuffer, int  * value) ;
            void cdecl qfn_glClearBufferfv(long nativehandle, int buffer, int drawbuffer, float  * value) ;
            void cdecl qfn_glClearBufferfi(long nativehandle, int buffer, int drawbuffer, float depth, int stencil) ;
            String cdecl qfn_glGetStringi(long nativehandle, int name, int index) ;
            void cdecl qfn_glCopyBufferSubData(long nativehandle, int readTarget, int writeTarget, long readOffset, long writeOffset, Pointer size) ;
            void cdecl qfn_glGetUniformIndices(long nativehandle, int program, int uniformCount, String uniformNames, int  * uniformIndices) ;
            void cdecl qfn_glGetActiveUniformsiv(long nativehandle, int program, int uniformCount, int  * uniformIndices, int pname, int  * params) ;
            int cdecl qfn_glGetUniformBlockIndex(long nativehandle, int program, String uniformBlockName) ;
            void cdecl qfn_glGetActiveUniformBlockiv(long nativehandle, int program, int uniformBlockIndex, int pname, int  * params) ;
            void cdecl qfn_glGetActiveUniformBlockName(long nativehandle, int program, int uniformBlockIndex, int bufSize, int  * length, byte  * uniformBlockName) ;
            void cdecl qfn_glUniformBlockBinding(long nativehandle, int program, int uniformBlockIndex, int uniformBlockBinding) ;
            void cdecl qfn_glDrawArraysInstanced(long nativehandle, int mode, int first, int count, int instancecount) ;
            void cdecl qfn_glDrawElementsInstanced(long nativehandle, int mode, int count, int type, byte  * indices, int instancecount) ;
            Pointer cdecl qfn_glFenceSync(long nativehandle, int condition, int flags) ;
            bool cdecl qfn_glIsSync(long nativehandle, Pointer sync) ;
            void cdecl qfn_glDeleteSync(long nativehandle, Pointer sync) ;
            int cdecl qfn_glClientWaitSync(long nativehandle, Pointer sync, int flags, long timeout) ;
            void cdecl qfn_glWaitSync(long nativehandle, Pointer sync, int flags, long timeout) ;
            void cdecl qfn_glGetInteger64v(long nativehandle, int pname, long  * data) ;
            void cdecl qfn_glGetSynciv(long nativehandle, Pointer sync, int pname, int bufSize, int  * length, int  * values) ;
            void cdecl qfn_glGetInteger64i_v(long nativehandle, int target, int index, long  * data) ;
            void cdecl qfn_glGetBufferParameteri64v(long nativehandle, int target, int pname, long  * params) ;
            void cdecl qfn_glGenSamplers(long nativehandle, int count, int  * samplers) ;
            void cdecl qfn_glDeleteSamplers(long nativehandle, int count, int  * samplers) ;
            bool cdecl qfn_glIsSampler(long nativehandle, int sampler) ;
            void cdecl qfn_glBindSampler(long nativehandle, int unit, int sampler) ;
            void cdecl qfn_glSamplerParameteri(long nativehandle, int sampler, int pname, int param) ;
            void cdecl qfn_glSamplerParameteriv(long nativehandle, int sampler, int pname, int  * param) ;
            void cdecl qfn_glSamplerParameterf(long nativehandle, int sampler, int pname, float param) ;
            void cdecl qfn_glSamplerParameterfv(long nativehandle, int sampler, int pname, float  * param) ;
            void cdecl qfn_glGetSamplerParameteriv(long nativehandle, int sampler, int pname, int  * params) ;
            void cdecl qfn_glGetSamplerParameterfv(long nativehandle, int sampler, int pname, float  * params) ;
            void cdecl qfn_glVertexAttribDivisor(long nativehandle, int index, int divisor) ;
            void cdecl qfn_glBindTransformFeedback(long nativehandle, int target, int id) ;
            void cdecl qfn_glDeleteTransformFeedbacks(long nativehandle, int n, int  * ids) ;
            void cdecl qfn_glGenTransformFeedbacks(long nativehandle, int n, int  * ids) ;
            bool cdecl qfn_glIsTransformFeedback(long nativehandle, int id) ;
            void cdecl qfn_glPauseTransformFeedback(long nativehandle) ;
            void cdecl qfn_glResumeTransformFeedback(long nativehandle) ;
            void cdecl qfn_glGetProgramBinary(long nativehandle, int program, int bufSize, int  * length, int  * binaryFormat, byte  * binary) ;
            void cdecl qfn_glProgramBinary(long nativehandle, int program, int binaryFormat, byte  * binary, int length) ;
            void cdecl qfn_glProgramParameteri(long nativehandle, int program, int pname, int value) ;
            void cdecl qfn_glInvalidateFramebuffer(long nativehandle, int target, int numAttachments, int  * attachments) ;
            void cdecl qfn_glInvalidateSubFramebuffer(long nativehandle, int target, int numAttachments, int  * attachments, int x, int y, int width, int height) ;
            void cdecl qfn_glTexStorage2D(long nativehandle, int target, int levels, int internalformat, int width, int height) ;
            void cdecl qfn_glTexStorage3D(long nativehandle, int target, int levels, int internalformat, int width, int height, int depth) ;
            void cdecl qfn_glGetInternalformativ(long nativehandle, int target, int internalformat, int pname, int bufSize, int  * params) ;
            void cdecl qfn_glDispatchCompute(long nativehandle, int num_groups_x, int num_groups_y, int num_groups_z) ;
            void cdecl qfn_glDispatchComputeIndirect(long nativehandle, long indirect) ;
            void cdecl qfn_glDrawArraysIndirect(long nativehandle, int mode, byte  * indirect) ;
            void cdecl qfn_glDrawElementsIndirect(long nativehandle, int mode, int type, byte  * indirect) ;
            void cdecl qfn_glFramebufferParameteri(long nativehandle, int target, int pname, int param) ;
            void cdecl qfn_glGetFramebufferParameteriv(long nativehandle, int target, int pname, int  * params) ;
            void cdecl qfn_glGetProgramInterfaceiv(long nativehandle, int program, int programInterface, int pname, int * params) ;
            int cdecl qfn_glGetProgramResourceIndex(long nativehandle, int program, int programInterface, String name) ;
            void cdecl qfn_glGetProgramResourceName(long nativehandle, int program, int programInterface, int index, int bufSize, int  * length, byte  * name) ;
            void cdecl qfn_glGetProgramResourceiv(long nativehandle, int program, int programInterface, int index, int propCount, int  * props, int bufSize, int  * length, int  * params) ;
            int cdecl qfn_glGetProgramResourceLocation(long nativehandle, int program, int programInterface, String name) ;
            void cdecl qfn_glUseProgramStages(long nativehandle, int pipeline, int stages, int program) ;
            void cdecl qfn_glActiveShaderProgram(long nativehandle, int pipeline, int program) ;
            int cdecl qfn_glCreateShaderProgramv(long nativehandle, int type, int count, String strings) ;
            void cdecl qfn_glBindProgramPipeline(long nativehandle, int pipeline) ;
            void cdecl qfn_glDeleteProgramPipelines(long nativehandle, int n, int  * pipelines) ;
            void cdecl qfn_glGenProgramPipelines(long nativehandle, int n, int  * pipelines) ;
            bool cdecl qfn_glIsProgramPipeline(long nativehandle, int pipeline) ;
            void cdecl qfn_glGetProgramPipelineiv(long nativehandle, int pipeline, int pname, int  * params) ;
            void cdecl qfn_glProgramUniform1i(long nativehandle, int program, int location, int v0) ;
            void cdecl qfn_glProgramUniform2i(long nativehandle, int program, int location, int v0, int v1) ;
            void cdecl qfn_glProgramUniform3i(long nativehandle, int program, int location, int v0, int v1, int v2) ;
            void cdecl qfn_glProgramUniform4i(long nativehandle, int program, int location, int v0, int v1, int v2, int v3) ;
            void cdecl qfn_glProgramUniform1ui(long nativehandle, int program, int location, int v0) ;
            void cdecl qfn_glProgramUniform2ui(long nativehandle, int program, int location, int v0, int v1) ;
            void cdecl qfn_glProgramUniform3ui(long nativehandle, int program, int location, int v0, int v1, int v2) ;
            void cdecl qfn_glProgramUniform4ui(long nativehandle, int program, int location, int v0, int v1, int v2, int v3) ;
            void cdecl qfn_glProgramUniform1f(long nativehandle, int program, int location, float v0) ;
            void cdecl qfn_glProgramUniform2f(long nativehandle, int program, int location, float v0, float v1) ;
            void cdecl qfn_glProgramUniform3f(long nativehandle, int program, int location, float v0, float v1, float v2) ;
            void cdecl qfn_glProgramUniform4f(long nativehandle, int program, int location, float v0, float v1, float v2, float v3) ;
            void cdecl qfn_glProgramUniform1iv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform2iv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform3iv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform4iv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform1uiv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform2uiv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform3uiv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform4uiv(long nativehandle, int program, int location, int count, int  * value) ;
            void cdecl qfn_glProgramUniform1fv(long nativehandle, int program, int location, int count, float  * value) ;
            void cdecl qfn_glProgramUniform2fv(long nativehandle, int program, int location, int count, float  * value) ;
            void cdecl qfn_glProgramUniform3fv(long nativehandle, int program, int location, int count, float  * value) ;
            void cdecl qfn_glProgramUniform4fv(long nativehandle, int program, int location, int count, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix2fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix3fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix4fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix2x3fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix3x2fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix2x4fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix4x2fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix3x4fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glProgramUniformMatrix4x3fv(long nativehandle, int program, int location, int count, bool transpose, float  * value) ;
            void cdecl qfn_glValidateProgramPipeline(long nativehandle, int pipeline) ;
            void cdecl qfn_glGetProgramPipelineInfoLog(long nativehandle, int pipeline, int bufSize, int  * length, byte  * infoLog) ;
            void cdecl qfn_glBindImageTexture(long nativehandle, int unit, int texture, int level, bool layered, int layer, int access, int format) ;
            void cdecl qfn_glGetBooleani_v(long nativehandle, int target, int index, bool  * data) ;
            void cdecl qfn_glMemoryBarrier(long nativehandle, int barriers) ;
            void cdecl qfn_glMemoryBarrierByRegion(long nativehandle, int barriers) ;
            void cdecl qfn_glTexStorage2DMultisample(long nativehandle, int target, int samples, int internalformat, int width, int height, bool fixedsamplelocations) ;
            void cdecl qfn_glGetMultisamplefv(long nativehandle, int pname, int index, float  * val) ;
            void cdecl qfn_glSampleMaski(long nativehandle, int maskNumber, int mask) ;
            void cdecl qfn_glGetTexLevelParameteriv(long nativehandle, int target, int level, int pname, int  * params) ;
            void cdecl qfn_glGetTexLevelParameterfv(long nativehandle, int target, int level, int pname, float  * params) ;
            void cdecl qfn_glBindVertexBuffer(long nativehandle, int bindingindex, int buffer, long offset, int stride) ;
            void cdecl qfn_glVertexAttribFormat(long nativehandle, int attribindex, int size, int type, bool normalized, int relativeoffset) ;
            void cdecl qfn_glVertexAttribIFormat(long nativehandle, int attribindex, int size, int type, int relativeoffset) ;
            void cdecl qfn_glVertexAttribBinding(long nativehandle, int attribindex, int bindingindex) ;
            void cdecl qfn_glVertexBindingDivisor(long nativehandle, int bindingindex, int divisor) ;
        };
        

    };
};