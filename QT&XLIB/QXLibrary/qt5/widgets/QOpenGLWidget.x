//xlang Source, Name:qt5/widgets/QOpenGLWidget.x 
//Date: Tue Mar 04:13:15 2021 
package Qt{
    public class QOpenGLWidget : QWidget{
        onOpenGLEventListener _listener = nilptr;
        
        public enum UpdateBehavior {
            NoPartialUpdate,
            PartialUpdate
        };
        
        public QOpenGLWidget() {
        }
        
        public QOpenGLWidget(long h) {
            super(h);
        }
        
        public bool create() {
            nativehandle = QtXnl.createQObject(QType.qtOpenGLWidget, this, 0);
            if (nativehandle == 0) {
                return false;
            }
            return true;
        }

        public bool create(@NotNilptr QWidget parent) {
            nativehandle = QtXnl.createQObject(QType.qtOpenGLWidget, this, parent.nativehandle);
            if (nativehandle == 0) {
                return false;
            }
            return true;
        }
        
        public void setUpdateBehavior(UpdateBehavior updateBehavior){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QOPENGLWIDGET_SETUPDATEBEHAVIOR, updateBehavior);
        }
        
        public UpdateBehavior updateBehavior(){
            return (UpdateBehavior)QtXnl.widget_get_int_value(nativehandle, Constant.QOPENGLWIDGET_UPDATEBEHAVIOR);
        }

        public void setFormat(QSurfaceFormat format){
            QtXnl.widget_set_native_value(nativehandle, Constant.QOPENGLWIDGET_SETFORMAT, format.nativehandle);
        }
        
        public QSurfaceFormat format() {
            return new QSurfaceFormat(QtXnl.long_get(nativehandle, Constant.QOPENGLWIDGET_FORMAT));
        }

        public bool isvalid(){
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QOPENGLWIDGET_ISVALID);
        }

        public void makeCurrent(){
            QtXnl.widget_slot(nativehandle,  Constant.QOPENGLWIDGET_MAKECURRENT);
        }
        
        public void doneCurrent(){
            QtXnl.widget_slot(nativehandle,  Constant.QOPENGLWIDGET_DONECURRENT);
        }

        public QOpenGLContext context(){
            return (QOpenGLContext)(QtXnl.widget_get_object(nativehandle, Constant.QOPENGLWIDGET_CONTEXT));
        }
        
        public int defaultFramebufferObject() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QOPENGLWIDGET_DEFAULTFRAMEBUFFEROBJECT);
        }

        public QImage grabFramebuffer(){
            return new QImage(QtXnl.long_get(nativehandle, Constant.QOPENGLWIDGET_GRABFRAMEBUFFER));
        }
        
        public void setOnOpenGLEventListener(onOpenGLEventListener l){
            _listener = l;
        }
        
        public onOpenGLEventListener getOnOpenGLEventListener(){
            return _listener;
        }
        
        protected void aboutToCompose(){
            if (_listener != nilptr){
                _listener.aboutToCompose(this);
            }
        }
        protected void frameSwapped(){
            if (_listener != nilptr){
                _listener.frameSwapped(this);
            }
        }
        protected void aboutToResize(){
            if (_listener != nilptr){
                _listener.aboutToResize(this);
            }
        }
        protected void resized(){
            if (_listener != nilptr){
                _listener.resized(this);
            }
        }
        
        protected void initializeGL(){
            if (_listener != nilptr){
                _listener.initializeGL(this);
            }
        }
        protected void resizeGL(int w, int h){
            if (_listener != nilptr){
                _listener.resizeGL(this, w, h);
            }
        }
        protected void paintGL(){
            if (_listener != nilptr){
                _listener.paintGL(this);
            }
        }
    };
};