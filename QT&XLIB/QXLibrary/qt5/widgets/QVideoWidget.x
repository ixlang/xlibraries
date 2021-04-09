//xlang Source, Name:qt5/widgets/QVideoWidget.x 
//Date: Thu Mar 14:55:11 2021 
package Qt{
    public class QVideoWidget : QWidget{
    
        onVideoWidgetListener _l;
        
        public void setOnVideoWidgetListener(onVideoWidgetListener l){
            _l = l;            
        }
        public onVideoWidgetListener getOnVideoWidgetListener(){
            return _l;
        }
        
        public bool create() override{
            nativehandle = QtXnl.createQObject(QType.qtVideoWidget, this, 0);
            if (nativehandle == 0) {
                return false;
            }
            return true;
        }

        public bool create(@NotNilptr QWidget parent) override{
            nativehandle = QtXnl.createQObject(QType.qtVideoWidget, this, parent.nativehandle);
            if (nativehandle == 0) {
                return false;
            }
            return true;
        }
        
        public QVideoWidget(){
            
        }
        public QVideoWidget(long h){
            super(h);
        }
        
        QMediaObject mediaObject(){
            return (QMediaObject)QtXnl.widget_get_object(nativehandle, Constant.QVIDEOWIDGET_MEDIAOBJECT);
        }
        
        public AspectRatioMode aspectRatioMode(){
            return (AspectRatioMode)QtXnl.widget_get_int_value(nativehandle, Constant.QVIDEOWIDGET_ASPECTRATIOMODE);
        }

        public int brightness(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QVIDEOWIDGET_BRIGHTNESS);
        }
        public int contrast(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QVIDEOWIDGET_CONTRAST);
        }
        public int hue(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QVIDEOWIDGET_HUE);
        }
        public int saturation() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QVIDEOWIDGET_SATURATION);
        }

        public QSize sizeHint(){
            long lsize = QtXnl.long_get(nativehandle, Constant.QVIDEOWIDGET_SIZEHINT);
            return new QSize(lsize >> 32 & 0xffffffff, lsize  & 0xffffffff);
        }


        public void setFullScreen(bool fullScreen){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QVIDEOWIDGET_SETFULLSCREEN, fullScreen);
        }
        public void setAspectRatioMode(AspectRatioMode mode){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QVIDEOWIDGET_SETASPECTRATIOMODE, mode);
        }
        public void setBrightness(int brightness){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QVIDEOWIDGET_SETBRIGHTNESS, brightness);
        }
        public void setContrast(int contrast){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QVIDEOWIDGET_SETCONTRAST, contrast);
        }
        public void setHue(int hue){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QVIDEOWIDGET_SETHUE, hue);
        }
        public void setSaturation(int saturation){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QVIDEOWIDGET_SETSATURATION, saturation);
        }

        //SIGNAL
        public void fullScreenChanged(bool fullScreen){
            if (_l != nilptr){
                _l.fullScreenChanged(this, fullScreen);
            }
        }
        public void brightnessChanged(int brightness){
            if (_l != nilptr){
                _l.brightnessChanged(this, brightness);
            }
        }
        public void contrastChanged(int contrast){
            if (_l != nilptr){
                _l.contrastChanged(this, contrast);
            }
        }
        public void hueChanged(int hue){
            if (_l != nilptr){
                _l.hueChanged(this, hue);
            }
        }
        public void saturationChanged(int saturation){
            if (_l != nilptr){
                _l.saturationChanged(this, saturation);
            }
        }
    };
};