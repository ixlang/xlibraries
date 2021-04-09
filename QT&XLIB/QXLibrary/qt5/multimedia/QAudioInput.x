//xlang Source, Name:qt5/multimedia/QAudioInput.x 
//Date: Sat Mar 00:51:44 2021 
package Qt{
    public class QAudioInput : QObject{
        public QAudioInput(){
        }
        
        public QAudioInput(long handle){
            super(handle);
        }
                
        public bool create(@NotNilptr QObject parent, QAudioFormat f) {
            nativehandle = QtXnl.createQPObject(QType.qtAudioInput, this, parent == nilptr ? 0l : parent.nativehandle, f == nilptr ? 0l : f.nativehandle, 0l, 0l, 0l);
            if (nativehandle == 0){
                return false;
            }
            return true;
        } 
        
        public QAudioFormat format() {
            return new QAudioFormat(QtXnl.long_get(nativehandle, Constant.QAUDIOINPUT_FORMAT));
        }

        public long read(byte [] data, int ofst, int len){
            return QtXnl.widget_set_int2_object_value(nativehandle, Constant.QAUDIOINPUT_READ, ofst, len, data);
        }
        
        public void start(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOINPUT_START);
        }

        public void stop(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOINPUT_STOP);
        }
        
        public void reset(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOINPUT_RESET);
        }
        
        public void suspend(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOINPUT_SUSPEND);
        }
        
        public void resume(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOINPUT_RESUME);
        }

        public void setBufferSize(int bytes){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOINPUT_SETBUFFERSIZE, bytes);
        }
        
        public int bufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOINPUT_BUFFERSIZE);
        }
        
        public int periodSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOINPUT_PERIODSIZE);
        }

        public void setNotifyInterval(int milliSeconds){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOINPUT_SETNOTIFYINTERVAL, milliSeconds);
        }
        
        public int notifyInterval(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOINPUT_NOTIFYINTERVAL);
        }

        public long processedUSecs() {
            return QtXnl.long_get(nativehandle, Constant.QAUDIOINPUT_PROCESSEDUSECS);
        }
        
        public long elapsedUSecs() {
            return QtXnl.long_get(nativehandle, Constant.QAUDIOINPUT_ELAPSEDUSECS);
        }

        public QAudio.Error error() {
            return (QAudio.Error)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOINPUT_ERROR);
        }
        
        public QAudio.State state() {
            return (QAudio.State)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOINPUT_STATE);
        }

        public void setVolume(double v){
            QtXnl.widget_set_double_value(nativehandle, Constant.QAUDIOINPUT_SETVOLUME, v);
        }
        
        public double volume() {
            return QtXnl.widget_get_double_value(nativehandle, Constant.QAUDIOINPUT_VOLUME);
        }
        
        //signal 
        onAudioInputListener _lis;
        public void setOnAudioInputListener(onAudioInputListener l ){
            _lis = l;
        }
        public onAudioInputListener getOnAudioInputListener(){
            return _lis;
        }
        
        public void stateChanged(QAudio.State s){
            if (_lis != nilptr){
                _lis.stateChanged(this, s);
            }
        }
        
        public void notify(){
            if (_lis != nilptr){
                _lis.notify(this);
            }
        }
    };
};
