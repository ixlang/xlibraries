//xlang Source, Name:qt5/multimedia/QMediaObject.x 
//Date: Thu Mar 14:21:38 2021 
package Qt{ 
    public class QMediaObject : QObject{
        public QMediaObject(){
        }
        public QMediaObject(long handle){
            super(handle);
        }
        onMediaObjectCallback __callback = nilptr;
        
        public void setOnMediaObjectCallback(onMediaObjectCallback _l){
            __callback = _l;
        }
        public onMediaObjectCallback getOnMediaObjectCallback(){
            return __callback;
        }
        
        public bool isAvailable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAOBJECT_ISAVAILABLE);
        }
        
        public AvailabilityStatus availability() {
            return (AvailabilityStatus)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAOBJECT_AVAILABILITY);
        }

        public QMediaService service() {
            return (QMediaService)QtXnl.widget_get_object(nativehandle, Constant.QMEDIAOBJECT_SERVICE);
        }

        public int notifyInterval() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAOBJECT_NOTIFYINTERVAL);
        }
        public void setNotifyInterval(int milliSeconds){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QMEDIAOBJECT_SETNOTIFYINTERVAL, milliSeconds);
        }

        public bool bind(QObject o){
            return QtXnl.core_getintlong(nativehandle, Constant.QMEDIAOBJECT_BIND, o.nativehandle) ==  1;
        }
        
        public void unbind(QObject o){
            QtXnl.core_getintlong(nativehandle, Constant.QMEDIAOBJECT_UNBIND, o.nativehandle);
        }

        public bool isMetaDataAvailable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAOBJECT_ISMETADATAAVAILABLE);
        }
        
        // SIGNAL
        public void notifyIntervalChanged(int milliSeconds){
            if (__callback != nilptr){
                __callback.notifyIntervalChanged(this,milliSeconds);
            }
        }

        public void metaDataAvailableChanged(bool available){
            if (__callback != nilptr){
                __callback.metaDataAvailableChanged(this,available);
            }
        }
        
        public void metaDataChanged(){
            if (__callback != nilptr){
                __callback.metaDataChanged(this);
            }
        }

        public void availabilityChanged(bool available){
            if (__callback != nilptr){
                __callback.availabilityChanged(this, available);
            }
        }
        
        public void availabilityChanged(AvailabilityStatus availability){
            if (__callback != nilptr){
                __callback.availabilityChanged(this, availability);
            }
        }
    };
};