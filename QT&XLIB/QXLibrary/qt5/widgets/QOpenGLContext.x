//xlang Source, Name:qt5/widgets/QOpenGLContext.x 
//Date: Tue Mar 04:21:59 2021 

package Qt{
    public class QOpenGLContext : QObject{
        public enum OpenGLModuleType {
            LibGL,
            LibGLES
        };
        
        public QOpenGLContext(){
            
        }
        
        public QOpenGLContext(long h){
            super(h);
        }
       
        public void setFormat(QSurfaceFormat format){
            QtXnl.widget_set_native_value(nativehandle, Constant.QOPENGLCONTEXT_SETFORMAT, format.nativehandle);
        }
        
        public void setShareContext(QOpenGLContext shareContext){
            QtXnl.widget_set_native_value(nativehandle, Constant.QOPENGLCONTEXT_SETSHARECONTEXT, shareContext.nativehandle);
        }
        
        public bool create(){
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QOPENGLCONTEXT_CREATE);
        }
        
        public bool isvalid() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QOPENGLCONTEXT_ISVALID);
        }

        public QSurfaceFormat format() {
            return new QSurfaceFormat(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_FORMAT));
        }
        
        public QOpenGLContext shareContext() {
            return (QOpenGLContext)(QtXnl.widget_get_object(nativehandle, Constant.QOPENGLCONTEXT_SHARECONTEXT));
        }

        public int defaultFramebufferObject(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QOPENGLCONTEXT_DEFAULTFRAMEBUFFEROBJECT);
        }
        
        public void doneCurrent(){
            QtXnl.widget_slot(nativehandle,  Constant.QOPENGLCONTEXT_DONECURRENT);
        }

        public static QOpenGLContext currentContext(){
            return (QOpenGLContext)(QtXnl.widget_get_object(0, Constant.QOPENGLCONTEXT_CURRENTCONTEXT));
        }
        
        public static bool areSharing(QOpenGLContext first, QOpenGLContext second){
            return QtXnl.long_intlong2(0, Constant.QOPENGLCONTEXT_ARESHARING,first.nativehandle, second.nativehandle) != 0;
        }

        public QOpenGLFunctions functions() {
            return new QOpenGLFunctions(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_FUNCTIONS));
        }
        
        public QOpenGLExtraFunctions extraFunctions() {
            return new QOpenGLExtraFunctions(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_EXTRAFUNCTIONS));
        }
        
        public QOpenGLFunctions_1_0 functions_1_0(){
            return new QOpenGLFunctions_1_0(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_FUNCTIONS_1_0));
        }
        
        public QOpenGLFunctions_1_1 functions_1_1(){
            return new QOpenGLFunctions_1_1(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_FUNCTIONS_1_1));
        }
        
        public QOpenGLFunctions_ES2 functions_ES2(){
            return new QOpenGLFunctions_ES2(QtXnl.long_get(nativehandle, Constant.QOPENGLCONTEXT_FUNCTIONS_ES2));
        }
        
        public OpenGLModuleType openGLModuleType(){
            return (OpenGLModuleType)QtXnl.widget_get_int_value(nativehandle, Constant.QOPENGLCONTEXT_OPENGLMODULETYPE);
        }

        public bool isOpenGLES() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QOPENGLCONTEXT_ISOPENGLES);
        }

        public static bool supportsThreadedOpenGL(){
            return QtXnl.widget_get_bool_value(0, Constant.QOPENGLCONTEXT_SUPPORTSTHREADEDOPENGL);
        }
        public static QOpenGLContext globalShareContext(){
            return (QOpenGLContext)(QtXnl.widget_get_object(0, Constant.QOPENGLCONTEXT_GLOBALSHARECONTEXT));
        }
    };
};