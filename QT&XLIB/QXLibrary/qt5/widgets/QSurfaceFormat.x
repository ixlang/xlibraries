//xlang Source, Name:qt5/widgets/QSurfaceFormat.x 
//Date: Tue Mar 04:55:26 2021 

package Qt{
    public class QSurfaceFormat : QCore{
        public QSurfaceFormat(){
            nativehandle = QtXnl.createNObject(QType.qtSurfaceFormat, 0);
        }
        
        public QSurfaceFormat(long h){
            super(h);
        }
        
        public enum FormatOption {
            StereoBuffers            = 0x0001,
            DebugContext             = 0x0002,
            DeprecatedFunctions      = 0x0004,
            ResetNotification        = 0x0008
        };

        public enum SwapBehavior {
            DefaultSwapBehavior,
            SingleBuffer,
            DoubleBuffer,
            TripleBuffer
        };

        public enum RenderableType {
            DefaultRenderableType = 0x0,
            OpenGL                = 0x1,
            OpenGLES              = 0x2,
            OpenVG                = 0x4
        };

        public enum OpenGLContextProfile {
            NoProfile,
            CoreProfile,
            CompatibilityProfile
        };
 
        public void setDepthBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETDEPTHBUFFERSIZE, size);
        }
        
        public int depthBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_DEPTHBUFFERSIZE);
        }

        public void setStencilBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETSTENCILBUFFERSIZE, size);
        }
        
        public int stencilBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_STENCILBUFFERSIZE);
        }

        public void setRedBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETREDBUFFERSIZE, size);
        }
        
        public int redBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_REDBUFFERSIZE);
        }
        
        public void setGreenBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETGREENBUFFERSIZE, size);
        }
        
        public int greenBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_GREENBUFFERSIZE);
        }
        
        public void setBlueBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETBLUEBUFFERSIZE, size);
        }
        
        public int blueBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_BLUEBUFFERSIZE);
        }
        
        public void setAlphaBufferSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETALPHABUFFERSIZE, size);
        }
        
        public int alphaBufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_ALPHABUFFERSIZE);
        }

        public void setSamples(int numSamples){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETSAMPLES, numSamples);
        }
        
        public int samples() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_SAMPLES);
        }

        public void setSwapBehavior(SwapBehavior behavior){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETSWAPBEHAVIOR, behavior);
        }
        
        public SwapBehavior swapBehavior() {
            return (SwapBehavior)QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_SWAPBEHAVIOR);
        }

        public bool hasAlpha() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QSURFACEFORMAT_HASALPHA);
        }

        /*public void setProfile(OpenGLContextProfile profile){
            
        }
        
        public OpenGLContextProfile profile() {
            
        }*/

        public void setRenderableType(RenderableType type){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETRENDERABLETYPE, type);
        }
        
        public RenderableType renderableType(){
            return (RenderableType)QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_RENDERABLETYPE);
        }

        public void setMajorVersion(int majorVersion){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETMAJORVERSION, majorVersion);
        }
        
        public int majorVersion() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_MAJORVERSION);
        }

        public void setMinorVersion(int minorVersion){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETMINORVERSION, minorVersion);
        }
        
        public int minorVersion(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_MINORVERSION);
        }

        public void setVersion(int major, int minor){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QSURFACEFORMAT_SETVERSION, major, minor);
        }

        public bool stereo(){
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QSURFACEFORMAT_STEREO);
        }
        
        public void setStereo(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QSURFACEFORMAT_SETSTEREO, enable);
        }

        public void setOptions(FormatOption options){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETOPTIONS, options);
        }
        
        public void setOption(FormatOption option, bool on){
            QtXnl.widget_set_int_bool_value(nativehandle, Constant.QSURFACEFORMAT_SETOPTION,option, on);
        }
        
        public bool testOption(FormatOption option){
            return QtXnl.widget_get_int_bool(nativehandle, Constant.QSURFACEFORMAT_TESTOPTION,option);
        }
        
        public FormatOption options() {
            return (FormatOption)QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_OPTIONS);
        }

        public int swapInterval() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QSURFACEFORMAT_SWAPINTERVAL);
        }
        
        public void setSwapInterval(int interval){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QSURFACEFORMAT_SETSWAPINTERVAL, interval);
        }

        public static void setDefaultFormat(QSurfaceFormat format){
            QtXnl.widget_set_native_value(0, Constant.QSURFACEFORMAT_SETDEFAULTFORMAT, format.nativehandle);
        }
        
        public static QSurfaceFormat defaultFormat(){
            return new QSurfaceFormat(QtXnl.long_get(0, Constant.QSURFACEFORMAT_DEFAULTFORMAT));
        }
        
        private final void finalize(){
            if (nativehandle != 0){
                QtXnl.widget_slot(nativehandle, Constant.QSURFACEFORMAT);
            }
        }
    };
};